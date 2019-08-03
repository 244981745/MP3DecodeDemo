#ifndef	_FRAMEDECODE_H
#define	_FRAMEDECODE_H

typedef struct frameHead
{
	unsigned int SyncWord;			// : 12 ; / / ͬ����Ϣ
	unsigned int Version;			// : 1 ; / / �汾
	unsigned int Layer;				// : 2 ; / / ��
	unsigned int ErrorProtection;	// : 1 ; / / CRC У�� 
	unsigned int BitRateIndex;		// : 4 ; / / λ������
	unsigned int SampleRateIndex;	// : 2 ; / / ����������
	unsigned int Padding;			// : 1 ; / / �հ���
	unsigned int Extension;			// : 1 ; / / ˽�б�־ 
	unsigned int ChannelMode;		// : 2 ; / / ������ģʽ 
	unsigned int ModeExtension;		// : 2 ; / / ����
	unsigned int CopyRight;			// : 1 ; / / ��Ȩ��־
	unsigned int Original;			// : 1 ; / / ԭʼý��
	unsigned int Emphasis;			// : 2 ; / / ǿ����ʽ
}FrameHeader;

typedef struct IIISideInfo{
	unsigned int	MainDataBegin;		/* 	�����ݿ�ʼָ��		9bits		*/
	unsigned int	PrivateBits;			/*	˽�б���λ			5 or 3 bits */
	/*	��������,ÿ����������������	*/
	struct{
		unsigned Scfsi[4];					/*	�������е�ѡ����Ϣ	4bits		*/
		/*	������Ϣ����	*/
		struct gr_info_s {
			unsigned Part2_3Length;			/*	������λ��			12bits		*/
			unsigned BigValues;				/*	��ֵ��				9bits		*/
			unsigned GlobalGain;			/*	ȫ����������		8bits		*/
			unsigned ScalefacCompress;		/*	��������ѹ��		4bits		*/
			unsigned WindowSwitchingFlag;	/*	�����л���־λ		1bit		*/
			unsigned BlockType;				/*	�����л�����		2bits		*/
			unsigned MixedBlockFlag;		/*	�촰��־			1bit		*/
			unsigned TableSelect[3];		/*	ʹ�ù�����������	5bits		*/
			unsigned SubblockGain[3];		/*	�д���־Ϊ1ʱʹ��	3bits		*/
			unsigned Region0Count;			/*	�д���־Ϊ0ʱʹ�� 	4bits		*/
			unsigned Region1Count;			/* 	�д���־Ϊ0ʱʹ�� 	3bits		*/
			unsigned PreFlag;				/* 						1bit		*/
			unsigned ScalefacScale;			/* 						1bit		*/
			unsigned Count1tableSelect;		/* 						1bit		*/
			
			unsigned Slen[2];
			unsigned int Part2Length;
			 
		} gr[2];
	} ch[2];
} IIISideInfo_t;

#endif
