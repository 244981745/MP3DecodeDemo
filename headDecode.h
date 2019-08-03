#ifndef	_HEADDECODE_H
#define	_HEADDECODE_H

#ifndef	NULL
#define	NULL	((void *)0)
#endif

#define GENRE_INDEX_MAX		148

typedef struct headlable
{
    char	FileIdentifier[3];		// 必须为字符串"ID3",否则认为标签不存在 对应16进制：49 44 33
    char	Version;			// 版本号ID3V2.3 就记录0x03
    char	Revision;		// 副版本号此版本记录为0x00
    char	Flag;			// 存放标志的字节,这个版本只定义了3bit
    char	Size[4];		// 标签帧的大小,不包括标签头的10个字节
    
    char	Unsynchronisation;		//非同步 
    char	ExtendedHeader;			//扩展头部是否存在 
    char	ExperimentalIndicator;	//实验指示器,如果该位置1,该帧为测试帧
    unsigned long size;
}HeadLab;

typedef	struct taglable
{
	unsigned char	FrameID[4];
	unsigned char	Size[4];
	unsigned char	Flag[2];
	
	unsigned long	size;
	unsigned char	charcode;		//text encoding
	unsigned char	bigorlittle[3];	//
	unsigned char	*data;
}TagLab;

typedef struct id3v1
{
	char	Tag[3];
	char	Title[30];
	char	Artist[30];
	char	Album[30];
	char	Year[4];
	char	Comment[28];
	unsigned char	Reserved;
	unsigned char	TrackNum;
	unsigned char	GenreIndex;
}ID3V1;

char *Genre[GENRE_INDEX_MAX]=
{
	"Blues","ClassicRock","Country","Dance","Disco","Funk","Grunge","Hip-Hop",
	"Jazz","Metal","NewAge","Oldies","Other","Pop","R&B","Rap",
	"Reggae","Rock","Techno","Industrial","Alternative","Ska","Deathl","Pranks",
	"Soundtrack","Euro-Techno","Ambient","Trip-Hop","Vocal","Jazz+Funk","Fusion","Trance",
	"Classical","Instrumental","Acid","House","Game","SoundClip","Gospel","Noise",
	"AlternRock","Bass","Soul","Punk","Space","Meditative","InstrumentalPop","InstrumentalRock",
	"Ethnic","Gothic","Darkwave","Techno-Industrial","Electronic","Pop-Folk","Eurodance","Dream",
	"SouthernRock","Comedy","Cult","Gangsta","Top40","ChristianRap","Pop/Funk","Jungle",
	"NativeAmerican","Cabaret","NewWave","Psychadelic","Rave","Showtunes","Trailer","Lo-Fi",
	"Tribal","AcidPunk","AcidJazz","Polka","Retro","Musical","Rock&Roll","HardRock",
	
	//Winamp扩充
	"Folk","Folk-Rock","NationalFolk","Swing","FastFusion","Bebob","Latin","Revival",
	"Celtic","Bluegrass","Avantgarde","GothicRock","ProgessiveRock","PsychedelicRock","SymphonicRock","SlowRock",
	"BigBand","Chorus","EasyListening","Acoustic","Humour","Speech","Chanson","Opera",
	"ChamberMusic","Sonata","Symphony","BootyBass","Primus","PornGroove","Satire","SlowJam",
	"Club","Tango","Samba","Folklore","Ballad","PowerBallad","RhythmicSoul","Freestyle",
	"Duet","PunkRock","DrumSolo","Acapella","Euro-House","DanceHall",
	
	//其他扩充
	"Goa","Drum&Bass","Club-House","Hardcore","Terror","Indie","BritPop","Negerpunk",
	"PolskPunk","Beat","ChristianGangstaRap","Heavyl","Blackl","Crossover","ContemporaryChristian","ChristianRock",
	"Merengue","Salsa","Trashl","Anime","JPop","Synthpop"
};

#endif

