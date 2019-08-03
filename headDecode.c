#include "headDecode.h"
#include "base.h"
#include <stdio.h>
#include <stdlib.h>

int getID3V2Head(BitStream *bs, HeadLab *hdr)
{
	fread((void *)hdr,1,10,bs->fp);
	
	if(hdr->FileIdentifier[0] == 'I' && hdr->FileIdentifier[1] == 'D' && hdr->FileIdentifier[2] == '3')
	{
		hdr->Unsynchronisation		=	(hdr->Flag >> 7 & 0x1);
		hdr->ExtendedHeader			=	(hdr->Flag >> 6 & 0x1);
		hdr->ExperimentalIndicator	=	(hdr->Flag >> 5 & 0x1);
		
		//解码size
		 hdr->size	=	0;
		 hdr->size	|=	(hdr->Size[0]&0x7f) << 21;
		 hdr->size	|=	(hdr->Size[1]&0x7f) << 14;
		 hdr->size	|=	(hdr->Size[2]&0x7f) << 7;
		 hdr->size	|=	(hdr->Size[3]&0x7f) << 0;
		 
		 bs->headSize	=	hdr->size;
	}
	else
	{
		return -1;
	}
	return 0;
}

TagLinkNode*
creatNode1(void)
{
	TagLinkNode *node;
	node = (TagLinkNode *)malloc(sizeof(TagLinkNode));
	if(node == NULL)return NULL;
	memset((void*)node,'\0',sizeof(TagLinkNode));
	return node;
}


int getID3V2Tag(BitStream *bs)
{
	unsigned char	buff[255];
	int i;
	int j;
	fseek(bs->fp, 10, SEEK_SET);
	
	TagLinkNode	*p1,*p2;
	
	for(i = 0; i < bs->headSize;)
	{
		p1	=	creatNode1();
			
		if(p1 == NULL)
		{
			printf("creat tag node error.\n");
			return -1;
		}
		
		i	+=	fread((void*)p1,1,10,bs->fp);	//读帧头10字节 
		
		//解码size 
		p1->size	=	p1->Size[0]<<24;
		p1->size	|=	p1->Size[1]<<16;
		p1->size	|=	p1->Size[2]<<8;
		p1->size	|=	p1->Size[3]<<0;

		//过滤错误帧及pic帧   图片和非T开头的帧，如comm帧将不加入表中 
		if(p1->FrameID[0] != 'T')
		{
			i	+=	p1->size;
			fseek(bs->fp,p1->size,SEEK_CUR);
			free(p1);
			continue;
		}
		
		i	+=	fread((void *)&(p1->charcode),1,1,bs->fp);		//读内容编码标识
		
		if(p1->charcode == 0x00) //iso 8859-1编码 
		{
			p1->data	=	(unsigned char*)malloc(p1->size - 1);
			if(p1->FrameID[0] != 'T')continue;
			memset((void *)p1->data,'\0',p1->size-1);
			i += fread((void *)p1->data,1,p1->size -1,bs->fp);
		}
		else if(p1->charcode == 0x01)	//utf16编码
		{
			p1->data =	(unsigned char*)malloc(p1->size -3);
			memset((void *)p1->data,'\0',p1->size-3);
			i += fread((void *)p1->bigorlittle,1,2,bs->fp);
			i += fread((void *)p1->data,1,p1->size-3,bs->fp);
		}
		else if(p1->charcode == 0x02)	//utf16-be编码
		{
			p1->data =	(unsigned char*)malloc(p1->size -3);
			memset((void *)p1->data,'\0',p1->size-3);
			i += fread((void *)p1->bigorlittle,1,2,bs->fp);
			i += fread((void *)p1->data,1,p1->size-3,bs->fp);	
		}
		else if(p1->charcode == 0x03)	//utf-8编码 
		{
			p1->data =	(unsigned char*)malloc(p1->size -4);
			memset((void *)p1->data,'\0',p1->size-4);
			i += fread((void *)p1->bigorlittle,1,3,bs->fp);
			i += fread((void *)p1->data,1,p1->size-4,bs->fp);
		}
		else	//错误值 
		{
			break;
		}
		
		//插入到标签帧链	
		listTailInsert(bs->tagL, p1);
	}

	return 0;
}

int getID3V1Tag(BitStream *bs)
{
	ID3V1	*p1;
	p1	=	malloc(sizeof(ID3V1));
	
	if(p1 == NULL)return -1;
	
	fseek(bs->fp,-128,SEEK_END);
	fread((void*)p1,1,128,bs->fp);
	
	if(strcmp(p1->Tag,"TAG") != 0)
	{
		free(p1);
		return -1;
	}
	else
	{
		bs->id3v1inf	=	p1;
	}
	
	return 0;
}
