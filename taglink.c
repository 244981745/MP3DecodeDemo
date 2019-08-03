/*************************************************
Copyright (C), 2019-2019, DREACYOU
File name:	taglink.c
Author:		DREACYOU
Version:	0.0.1.0
Date:		2019.7.8
Description: 包裹系统 
Others: 
Function List: 

History: 

*************************************************/

#include "taglink.h"


/*************************************************
Function: creatNode
Description: 创建链表节点
Calls: 
Called By: 

Input: void
Output: TagLinkNode*
Return: 正确返回所创建的节点指针，出错返回NULL 
Others: 
*************************************************/
TagLinkNode*
creatNode(void)
{
	TagLinkNode *node;
	node = (TagLinkNode *)malloc(sizeof(TagLinkNode));
	if(node == NULL)return NULL;
	memset((void*)node,'\0',sizeof(TagLinkNode));
	return node;
}

/*************************************************
Function: destroyNode
Description: 销毁节点 
Calls: 
Called By: 

Input: TagLinkNode *node
Output: 
Return: void 
Others: 
*************************************************/
void destroyNode(TagLinkNode *node)
{
	if(node->data	!=	NULL)free(node->data);
	free(node);
	node	=	NULL;
}

/*************************************************
Function: initList
Description: 构造一个空链表 (创建头节点) 
Calls: 
Called By: 

Input: TagLink *L
Output: 
Return: 出错返回-1，正确返回0 
Others: 
*************************************************/
int initList(TagLink *L)
{
	L->head			=	(TagLinkNode *)malloc(sizeof(TagLinkNode));
	if(L->head == NULL)return -1;
	memset((void *)L->head,'\0',sizeof(TagLinkNode));
	L->link_len		=	0;
	L->head->next	=	NULL;
	
	return 0;
}

/*************************************************
Function: destroyList
Description: 销毁一个链表
Calls: 
Called By: 

Input: TagLink *L
Output: 
Return: 出错返回-1，正确返回0 
Others: 
*************************************************/
int destroyList(TagLink *L)
{
	TagLinkNode *p1,*p2;
	p1 = L->head->next;
	
	while(p1 != NULL)
	{
		p2 = p1->next;
		destroyNode(p1);
		L->link_len--;
		p1 = p2;
	}
	
	if(L->link_len < 0)return -1;
	free(L->head);
	return 0;
}

/*************************************************
Function: clearList
Description: 清空一个链表
Calls: 
Called By: 

Input: TagLink *L
Output: 
Return: 返回0
Others: 
*************************************************/
int clearList(TagLink *L)			//线性表存在,将L重置为空表
{
	TagLinkNode *p1,*p2;
	p1 = L->head->next;
	
	while(p1 != NULL)
	{
		p2 = p1->next;
		destroyNode(p1);
		L->link_len--;
		p1 = p2;
	}
	
	if(L->link_len != 0)L->link_len = 0;

	return 0;
}

/*************************************************
Function: listEmpty
Description: 查询链表是否为空 
Calls: 
Called By: 

Input: TagLink *L
Output: 
Return: 空链表返回true，非空链表返回false 
Others: 
*************************************************/
int listEmpty(TagLink *L)
{
	if(L->head == NULL)
	{
		L->link_len = 0;
		return true;
	}
	
	return false;
}

/*************************************************
Function: listLength
Description: 查询链表长度
Calls: 
Called By: 

Input: TagLink  *L
Output: 
Return: 返回链表长度 
Others: 
*************************************************/
int listLength(TagLink  *L)
{
	return L->link_len;
}

/*************************************************
Function: listTailInsert
Description: 在链表末尾插入节点e 
Calls: 
Called By: 

Input: TagLink  *L, struct PacketLinkNode *e
Output: 
Return: 出错返回false 正确返回0 
Others: 
*************************************************/
int listTailInsert(TagLink  *L, TagLinkNode *e)
{
	if(e ==	NULL)
		return false;
	
	TagLinkNode *p = L->head;
	while(p->next != NULL)
		p = p->next;

	p->next = e;
	L->link_len += 1;
	
	return 0;
}

/*************************************************
Function: visit
Description: 访问节点信息并输出 
Calls: 
Called By: 

Input: TagLinkNode *node,int offset
Output: 
Return: 返回0 
Others: 
*************************************************/
int visit(TagLinkNode *node,int offset)
{
	int i;
	if(node == NULL)
	{
		printf("node is null\n");
		return -1;
	}
	else
	{
		printf("Tag[%d]->Id:\t%.4s\n",offset,node->FrameID);
		printf("Tag[%d]->Size:\t%d\n",offset,node->size);
		printf("Tag[%d]->code:\t%d\n",offset,node->charcode);
		if(node->charcode	==	0x0)
		{
			printf("\t\tiso 8859-1 is no support.\n");
		}
		else if(node->charcode	==	0x1)
		{
			printf("Tag[%d]->data:\t%S",offset,node->data);
			printf("\n");
		}
		else if(node->charcode	==	0x2)
		{
			printf("Tag[%d]->data:\t%s\n",offset,node->data);
		}
		for(i = 0; i < node->size; i++)
		{
			printf("%x\t",node->data[i]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

/*************************************************
Function: listTraverse
Description: 遍历链表 
Calls: 
Called By: 

Input: TagLink  *L
Output: 
Return: 返回0 
Others: 
*************************************************/
int listTraverse(TagLink  *L)
{
	int i;
	if(L->head->next	==	NULL)return -1; 
	TagLinkNode *p = L->head->next;

	printf("----------------HeadInfo----------------\n");
	for(i = 0; i < L->link_len; i++)
	{

		visit(p,i);
		p=p->next;
	}
	printf("----------------------------------------\n\n");
	return 0;
}

