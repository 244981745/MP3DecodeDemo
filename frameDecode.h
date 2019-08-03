#ifndef	_FRAMEDECODE_H
#define	_FRAMEDECODE_H

typedef struct frameHead
{
	unsigned int SyncWord;			// : 12 ; / / 同步信息
	unsigned int Version;			// : 1 ; / / 版本
	unsigned int Layer;				// : 2 ; / / 层
	unsigned int ErrorProtection;	// : 1 ; / / CRC 校正 
	unsigned int BitRateIndex;		// : 4 ; / / 位率索引
	unsigned int SampleRateIndex;	// : 2 ; / / 采样率索引
	unsigned int Padding;			// : 1 ; / / 空白字
	unsigned int Extension;			// : 1 ; / / 私有标志 
	unsigned int ChannelMode;		// : 2 ; / / 立体声模式 
	unsigned int ModeExtension;		// : 2 ; / / 保留
	unsigned int CopyRight;			// : 1 ; / / 版权标志
	unsigned int Original;			// : 1 ; / / 原始媒体
	unsigned int Emphasis;			// : 2 ; / / 强调方式
}FrameHeader;

typedef struct IIISideInfo{
	unsigned int	MainDataBegin;		/* 	主数据开始指针		9bits		*/
	unsigned int	PrivateBits;			/*	私有保留位			5 or 3 bits */
	/*	声道部分,每个声道含两个颗粒	*/
	struct{
		unsigned Scfsi[4];					/*	颗粒共有的选择信息	4bits		*/
		/*	颗粒信息部分	*/
		struct gr_info_s {
			unsigned Part2_3Length;			/*	主数据位数			12bits		*/
			unsigned BigValues;				/*	大值区				9bits		*/
			unsigned GlobalGain;			/*	全局增益因子		8bits		*/
			unsigned ScalefacCompress;		/*	比例因子压缩		4bits		*/
			unsigned WindowSwitchingFlag;	/*	窗口切换标志位		1bit		*/
			unsigned BlockType;				/*	窗口切换类型		2bits		*/
			unsigned MixedBlockFlag;		/*	混窗标志			1bit		*/
			unsigned TableSelect[3];		/*	使用哈夫曼表索引	5bits		*/
			unsigned SubblockGain[3];		/*	切窗标志为1时使用	3bits		*/
			unsigned Region0Count;			/*	切窗标志为0时使用 	4bits		*/
			unsigned Region1Count;			/* 	切窗标志为0时使用 	3bits		*/
			unsigned PreFlag;				/* 						1bit		*/
			unsigned ScalefacScale;			/* 						1bit		*/
			unsigned Count1tableSelect;		/* 						1bit		*/
			
			unsigned Slen[2];
			unsigned int Part2Length;
			 
		} gr[2];
	} ch[2];
} IIISideInfo_t;

#endif
