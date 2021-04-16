#ifndef	_BASE_H
#define	_BASE_H

#include "taglink.h"
#include "headDecode.h"

#define	BUFFSIZE	1024

#ifndef	FALSE
#define	FALSE	0
#endif

#ifndef	TRUE
#define	TRUE	1
#endif

#define	MIN(A, B)			((A) < (B) ? (A) : (B))

typedef struct bs
{
	FILE	*fp;
	unsigned char	buff[BUFFSIZE];

	TagLink	*tagL;
	ID3V1	*id3v1inf;
	
	int		fileEnd;
	int		headSize;
	
	//buf操作相关
	int		bufByteIndex;
	int		bufBitIndex;
	int		bufFillLen;		//
	
	int		bufeobs;		//buff里的bit已经解码完标识位
	
}BitStream;


#endif
