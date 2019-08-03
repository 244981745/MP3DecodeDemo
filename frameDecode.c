#include <stdio.h>
#include "frameDecode.h"
#include "base.h"

int frameHeaderDecode(BitStream *bs, FrameHeader *hdr)
{
	int retry,frist = 1;
	
	if(bs->fp	==	NULL)return -1;

	if(frist)
	{
		fseek(bs->fp,bs->headSize,SEEK_SET);	//跳转至首帧
		for(retry = 0; retry < 2; retry++)
		{
			hdr->SyncWord	=	getNbits(bs, 12);
			if(hdr->SyncWord != 0xfff)
			{
				bs->bufBitIndex		=	8;
				bs->bufByteIndex	-=	9;
			}
			frist = 0;
		}
	}

	if(hdr->SyncWord != 0xfff) return -1;
	
	hdr->Version			=	getNbits(bs,	1);
	hdr->Layer				=	getNbits(bs,	2);
	hdr->ErrorProtection	=	getNbits(bs,	1);
	hdr->BitRateIndex		=	getNbits(bs,	4);
	hdr->SampleRateIndex	=	getNbits(bs,	2);
	hdr->Padding			=	getNbits(bs,	1);
	hdr->Extension			=	getNbits(bs,	1);
	hdr->ChannelMode		=	getNbits(bs,	2);
	hdr->ModeExtension		=	getNbits(bs,	2);
	hdr->CopyRight			=	getNbits(bs,	1);
	hdr->Original			=	getNbits(bs,	1);
	hdr->Emphasis			=	getNbits(bs,	2);
	
	return 0;	
}

int sideInfoDecode(BitStream *bs,FrameHeader *hdr,IIISideInfo_t *sinfo)
{
	int gr,ch,nch,i;
	gr=ch=nch=i =0;
	sinfo->MainDataBegin		=	getNbits(bs,	9);
	if(hdr->ChannelMode	==	0x03)	//单声道
	{
		sinfo->PrivateBits		=	getNbits(bs,	5);
		for(i = 0; i < 4; i++)
			sinfo->ch[0].Scfsi[i]	=	getNbits(bs,	1);
		
		nch						=	1;
	}
	else		//双声道和立体声
	{
		sinfo->PrivateBits		=	getNbits(bs,	3);
		for(i = 0; i < 4; i++)
			sinfo->ch[0].Scfsi[i]	=	getNbits(bs,	1);
		for(i = 0; i < 4; i++)
			sinfo->ch[1].Scfsi[i]	=	getNbits(bs,	1);
			
		nch						=	2;
	}
	
	for(gr = 0; gr < 2; gr++)
	{
		for(ch = 0; ch < nch; ch++)
		{
			sinfo->gr[gr].ch[ch].Part2_3Length	=	getNbits(bs,	3);
		}
	}
	
	
	return 0;
}
