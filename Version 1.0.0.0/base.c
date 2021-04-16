#include "base.h"
#include <stdio.h>
#include <stdlib.h>

int OpenBitStream(BitStream *bs)
{
	bs->fp	=	fopen("demo1.mp3","rb");
	if(bs->fp	==	NULL)return -1;
	
	bs->headSize		=	0;
	bs->fileEnd			=	0;
	bs->id3v1inf		=	NULL;
	
	bs->bufByteIndex	=	BUFFSIZE;
	bs->bufBitIndex		=	8;
	bs->bufFillLen		=	0;
	bs->bufeobs			=	1;
	
	initList(bs->tagL);
	
	memset((void *)bs->buff,'\0',BUFFSIZE);
	
	return 0;
}


int CloseBitStream(BitStream *bs)
{
	if(bs->tagL	!= NULL)
	{
		destroyList(bs->tagL);
		bs->tagL	=	NULL;
	}
	
	if(bs->id3v1inf	!= NULL)
	{
		free(bs->id3v1inf);
		bs->id3v1inf	=	NULL;
	}
	
	fclose(bs->fp);
	return 0;
}

int FillBuff(BitStream *bs)
{
	if(bs->fp	== NULL) return -1;
	
	bs->bufFillLen	=	fread((void *)bs->buff, 1, BUFFSIZE,bs->fp);
	
	if(bs->bufFillLen	!=	BUFFSIZE)	bs->fileEnd	=	1;
	
	if(bs->bufFillLen	>0) bs->bufeobs	=	0; 
	bs->bufByteIndex					=	bs->bufFillLen;
	return 0;
}


int putmask[9]={0x0, 0x1, 0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff};
unsigned int getNbits(BitStream *bs, int N)
{
	unsigned int val = 0;
	register int i,j,k,ret;
	if( N > 32 || N < 0) return 0;

	j =	N;
	while(j > 0)
	{
		if(bs->bufeobs) FillBuff(bs);
		
		if(!bs->bufBitIndex)
		{
			bs->bufBitIndex	=	8;
			bs->bufByteIndex--;
		}
		if(!bs->bufByteIndex)
		{
			bs->bufeobs	=	1;
			continue;
		}
		
		k = MIN(j, bs->bufBitIndex);
		ret = bs->buff[bs->bufFillLen - bs->bufByteIndex] & putmask[bs->bufBitIndex];
		ret = ret >> (bs->bufBitIndex - k);
		val |= ret << (j - k);
		
		bs->bufBitIndex -= k;
		j -= k;
	}
	
	return val;
}
