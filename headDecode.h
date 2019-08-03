#ifndef	_HEADDECODE_H
#define	_HEADDECODE_H

#ifndef	NULL
#define	NULL	((void *)0)
#endif

#define GENRE_INDEX_MAX		148

typedef struct headlable
{
    char	FileIdentifier[3];		// ����Ϊ�ַ���"ID3",������Ϊ��ǩ������ ��Ӧ16���ƣ�49 44 33
    char	Version;			// �汾��ID3V2.3 �ͼ�¼0x03
    char	Revision;		// ���汾�Ŵ˰汾��¼Ϊ0x00
    char	Flag;			// ��ű�־���ֽ�,����汾ֻ������3bit
    char	Size[4];		// ��ǩ֡�Ĵ�С,��������ǩͷ��10���ֽ�
    
    char	Unsynchronisation;		//��ͬ�� 
    char	ExtendedHeader;			//��չͷ���Ƿ���� 
    char	ExperimentalIndicator;	//ʵ��ָʾ��,�����λ��1,��֡Ϊ����֡
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
	
	//Winamp����
	"Folk","Folk-Rock","NationalFolk","Swing","FastFusion","Bebob","Latin","Revival",
	"Celtic","Bluegrass","Avantgarde","GothicRock","ProgessiveRock","PsychedelicRock","SymphonicRock","SlowRock",
	"BigBand","Chorus","EasyListening","Acoustic","Humour","Speech","Chanson","Opera",
	"ChamberMusic","Sonata","Symphony","BootyBass","Primus","PornGroove","Satire","SlowJam",
	"Club","Tango","Samba","Folklore","Ballad","PowerBallad","RhythmicSoul","Freestyle",
	"Duet","PunkRock","DrumSolo","Acapella","Euro-House","DanceHall",
	
	//��������
	"Goa","Drum&Bass","Club-House","Hardcore","Terror","Indie","BritPop","Negerpunk",
	"PolskPunk","Beat","ChristianGangstaRap","Heavyl","Blackl","Crossover","ContemporaryChristian","ChristianRock",
	"Merengue","Salsa","Trashl","Anime","JPop","Synthpop"
};

#endif

