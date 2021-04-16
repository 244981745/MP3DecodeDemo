#ifndef	_TAGLINK_H
#define	_TAGLINK_H

#define	true	1
#define	false	0
 
typedef struct taglinknode
{
	unsigned char	FrameID[4];
	unsigned char	Size[4];
	unsigned char	Flag[2];
	
	unsigned long	size;
	unsigned char	charcode;		//text encoding
	unsigned char	bigorlittle[3];	//
	unsigned char	*data;
	
	struct taglinknode		*next;
}TagLinkNode;

typedef struct tagLink
{
	int			link_len;
	TagLinkNode	*head;
}TagLink;

#endif
