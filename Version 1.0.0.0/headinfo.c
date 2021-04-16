#include "datastruct.h"
#include <stdio.h>

int getID3V2Info(FILE *fp)
{
	HeadLab hlab;
	TagLab	tlab;
	if(fp == NULL) return -1;
	
	fread((void *)&hlab,1,10,fp);
	
	if(hlab.FileIdentifier[0] == 'I' && hlab.FileIdentifier[1] == 'D' && hlab.FileIdentifier[2] == '3')//头标识 
	{
		printf("%.3s\n",hlab.FileIdentifier);

		
		//解码Flag 
		hlab.Unsynchronisation		=	(hlab.Flag >> 7 & 0x1);
		hlab.ExtendedHeader			=	(hlab.Flag >> 6 & 0x1);
		hlab.ExperimentalIndicator	=	(hlab.Flag >> 5 & 0x1);
		
		//解码size
		 hlab.size	=	0;
		 hlab.size	|=	(hlab.Size[0]&0x7f) << 21;
		 hlab.size	|=	(hlab.Size[1]&0x7f) << 14;
		 hlab.size	|=	(hlab.Size[2]&0x7f) << 7;
		 hlab.size	|=	(hlab.Size[3]&0x7f) << 0;

		printf("headsize:%d\n",hlab.size);
		if(hlab.Version	==	3)
		{
			printf("2.3.%x\n",hlab.Revision);
			getID3V2Tag3Info(fp, hlab.size,&tlab);
		}
		else if(hlab.Version == 4)
		{
			printf("2.4.%x\n",hlab.Revision);	//unicode编码
			getID3V2Tag4Info(fp ,hlab.size);
		}		 
		 return hlab.size;
		
	}
	else	//头标识对不上，不存在tag v3 
	{
		printf("not exist id3\n");
		return -1;
	}
	
	return 0;
}

int getID3V1Info(FILE *fp)
{
	
	return 0;
}

int getID3V2Tag3Info(FILE *fp, int headsize,TagLab *frame)
{
	int j;
	int i = headsize;

	
	for(i = headsize; i > 0;)
	{
		//read head
		i -= fread((void *)frame,1,10,fp);
		printf("%.4s\n",frame->FrameID);
		printf("%x,%x,%x,%x\n",frame->Size[0],frame->Size[1],frame->Size[2],frame->Size[3]);
//		getch();
		frame->size	=	0;
		frame->size	|=	frame->Size[0]<<24;
		frame->size	|=	frame->Size[1]<<16;
		frame->size	|=	frame->Size[2]<<8;
		frame->size	|=	frame->Size[3]<<0;
		
		if(frame->size  <= 0)
		{
			// id3 padding
			//ftell(fp); 计算padding大小，frame offset- ftell + 10； 
			break;
		}
		
/*		if(((frame->FrameID[0])<<24 | (frame->FrameID[1])<<16 | (frame->FrameID[2])<<8 | (frame->FrameID[3])) == 0x434f4d4d)
		{
			//读备注
			
			continue;
		}
		
		if(((frame->FrameID[0])<<24 | (frame->FrameID[1])<<16 | (frame->FrameID[2])<<8 | (frame->FrameID[3])) != 0x41504943 )
		{
			//读专辑图片
			
			continue;
		}
*/
		printf("frame size:%d\n",frame->size);
//解码frame data  1个字节表示编码，0-3字节表示大小端 
		i -= fread((void *)&frame->charcode,1,1,fp);
		printf("charcode:%x\n",frame->charcode);
		if(frame->charcode == 0x00) //iso 8859-1编码 
		{
			frame->data	=	(unsigned char*)malloc(frame->size - 1);
			memset((void *)frame->data,'\0',frame->size-1);
			i -= fread((void *)frame->data,1,frame->size -1,fp);
		}
		else if(frame->charcode == 0x01)	//utf16编码
		{
			frame->data =	(unsigned char*)malloc(frame->size -3);
			memset((void *)frame->data,'\0',frame->size-3);
			i -= fread((void *)frame->bigorlittle,1,2,fp);
			i -= fread((void *)frame->data,1,frame->size-3,fp);
		}
		else if(frame->charcode == 0x02)	//utf16-be编码
		{
			frame->data =	(unsigned char*)malloc(frame->size -3);
			memset((void *)frame->data,'\0',frame->size-3);
			i -= fread((void *)frame->bigorlittle,1,2,fp);
			i -= fread((void *)frame->data,1,frame->size-3,fp);	
		}
		else if(frame->charcode == 0x03)	//utf-8编码 
		{
			frame->data =	(unsigned char*)malloc(frame->size -4);
			memset((void *)frame->data,'\0',frame->size-4);
			i -= fread((void *)frame->bigorlittle,1,3,fp);
			i -= fread((void *)frame->data,1,frame->size-4,fp);
		}
		else	//错误值 
		{
			return -1;
		}
		
		printf("%x\n",(long)(frame->FrameID[0])<<24 | (frame->FrameID[1])<<16 | (frame->FrameID[2])<<8 | (frame->FrameID[3]));
		if(frame->charcode != 0x0 && *frame->FrameID != 0x434f4d4d && *frame->FrameID != 0x54504943)
		{
			printf("frame data:%S\n",frame->data);
		}
		else if(((frame->FrameID[0])<<24 | (frame->FrameID[1])<<16 | (frame->FrameID[2])<<8 | (frame->FrameID[3])) != 0x434f4d4d \
		&& ((frame->FrameID[0])<<24 | (frame->FrameID[1])<<16 | (frame->FrameID[2])<<8 | (frame->FrameID[3])) != 0x41504943)
			printf("frame data:\t%s\n",frame->data);
		int j;
//		for(j = 0; j < frame->size; j++)
//			printf("%x\t",frame->data[j]);
		printf("\n");
		getch();
	}
//	free(frame->data);
	return 0;
}

int getID3V2Tag4Info(FILE *fp, int headsize)
{
	int i =headsize;
	for(i = headsize; i > 0;)
	{
		//read head
		
		//read lab
		
		
	}
	return 0;
}

