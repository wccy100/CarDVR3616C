#ifndef __COMMON_COM_H__
#define __COMMON_COM_H__

#ifdef __cplusplus
extern "C"{
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE  500 
#endif
#include <time.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/vfs.h>
#include <dirent.h>
#include <assert.h>

/* retype  variable types */
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned long ULONG;

typedef  signed char CHAR;
typedef  signed short SHORT;
typedef  signed long LONG;

#define CHAR char

/* for share memory 8kB */
#define COMM_SM_SIZE (1024*8)
typedef enum {
	COMM_SM_STRINGPOOL,
	COMM_SM_RESERVE,
} eCOMM_SM_TYPE;

/* for string pool 4KB */
#define COMM_SP_SIZE (1024 * 4)

/* define success */
typedef enum {
	COMM_RET_SUCCESS,
	COMM_RET_FAIL,
	COMM_RET_SYSQUIT
} eCOMM_RET_STAT;

typedef enum {
	COMM_FILETYPE_SNAP,
	COMM_FILETYPE_REC,
	COMM_FILETYPE_RAW
} eCOMM_FILETYPE;

typedef struct {
	LONG lFrameRate;
	LONG lWidth;
	LONG lHeight;
	CHAR cFilePath[64];
	eCOMM_FILETYPE eFileType;
} sCOMM_FILENAME_INFO;

typedef enum {
	COMM_STRING_EQUAL,
	COMM_STRING_NOTEQUAL,
} eCOMM_STRING_COMPARE;

typedef enum {
	COMM_LIST_NONE,
	COMM_LIST_CLIENT,
} eCOMM_LIST_MESSAGE;

/* define time out */
#define COMM_CFBASETIMEOUT 2
#define COMM_CFCTRLTIMEOUT 1
#define COMM_CFCTRLGUITIMEOUT 3
#define COMM_CFCTRLUARTTIMEOUT 3

/* bit shift */
#define COMM_BIT(x) (1<<(x))
#define COMM_SET(x,y) ((x)|(y))
#define COMM_UNSET(x,y) ((x)&(~y))

/* compare */
#define COMM_MAX(x,y) (((x)>(y)) ? (x) : (y) )
#define COMM_MIN(x,y) (((x)<(y)) ? (x) : (y) )

/* max resolution */
#define COMM_RESOLUTION_WIDTH_MAX 1920
#define COMM_RESOLUTION_HEIGHT_MAX 1080
#define COMM_RESOLUTION_HEIGHT_WIDTH_MIN 16

#define COMM_RESOLUTION_WIDTH_VDA_MAX 720
#define COMM_RESOLUTION_HEIGHT_VDA_MAX 480

/* audio rtp port */
#define COMM_AUDIO_RTP_PORT 7600


/* redefine inter command */
#define INTER_CMD_REDEFINE
/* reconfig time */
#define RECONFIGTIME 1
#define CONFIGTIMEDELTA 1

/* define feedback type */
typedef enum {
	COMM_CF_FEEDBACKFINISHFAIL=-2,		// -2 feed back finish fail
	COMM_CF_FEEDBACKATONCEFAIL,			// -1 feed back at once fail
	COMM_CF_FEEDBACKATONCESUC=1,			// 1 feed back at once success
	COMM_CF_FEEDBACKFINISHSUC,				// 2 feed back finish success
	COMM_CF_FEEDBACKOTHERGUI,				// 3 feed back finish success from other gui
	COMM_CF_FEEDBACKFINISHSYSQUIT,		// 4 feed back system quit
} eCOMM_CF_FEEDBACK;

/* count constrain */
#define COMM_CMDMAXSUBSHIFT 6
#define COMM_CMDMAXSUBCNT ( 1 << COMM_CMDMAXSUBSHIFT )
#define COMM_CMDMAXCMTCHAR 100					// command max comment byte

/* cmd type */
typedef enum {
	COMM_CMD_SYS,
	COMM_CMD_VENC0,
	COMM_CMD_ETH,
	COMM_CMD_ISP0,
	COMM_CMD_RECORD,
	COMM_CMD_VENC1,
	COMM_CMD_RESERVE1,
	COMM_CMD_ISP1,
	COMM_CMD_HDMI,
	COMM_CMD_VENC2,
	COMM_CMD_RESERVE2,
	COMM_CMD_ISP2,
	COMM_CMD_REG,
	COMM_CMD_VDA,
	COMM_CMDMAXCNT
} eCOMM_CMD_TYPE;

#define COMM_CMDCHSTEP 4		// channel step 1->4->7, 2->5->8

/* region sub cmd type */
typedef enum{
	COMM_SUBCMD_OVERLAYRESOLUTION,
	COMM_SUBCMD_OVERLAYSTOP,
	COMM_SUBCMD_OVERLAYX,
	COMM_SUBCMD_OVERLAYY,
	COMM_SUBCMD_OVERLAYSHOWBMP,
	COMM_SUBCMD_OVERLAYNUM,
	COMM_SUBCMD_OVERLAYSHOWTYPE,
	COMM_SUBCMD_OVERLAYFRONTALPHA,
	COMM_SUBCMD_OVERLAYBOTTOMALPHA,
	COMM_SUBCMD_OVERLAYCHANGEATTR,
}eCOMM_SUBCMD_REG;

/* color defination */
typedef enum{
	COMM_COLOR_RED,
	COMM_COLOR_BLUE,
	COMM_COLOR_GREEN,
	COMM_COLOR_WHITE,
	COMM_COLOR_BLACK,
}eCOMM_SUBCMD_REGCOLOR;

/*audio protocol*/
typedef enum{
	COMM_AENC_ADPCMA=49,
	COMM_AENC_G711A=19,
	COMM_AENC_G711U=20,
	COMM_AENC_G726=21,
}eCOMM_AENC_PROTOCOL;

/* system sub cmd type */
typedef enum {
	COMM_SUBCMD_SYSQUIT,						//system->quit
	COMM_SUBCMD_SETTIME = 14,
	COMM_SUBCMD_CLEARSUBCARD,
	COMM_SUBCMD_WIFIUSERNAME,
	COMM_SUBCMD_WIFIPASSWORD,
	COMM_SUBCMD_WIFITYPE,
	COMM_SUBCMD_LED,
	COMM_SUBCMD_THREADSTART,
} eCOMM_SUBCMD_SYSTEM;

/* record sub cmd type */
typedef enum {
	COMM_SUBCMD_RECAUDIORESOLUTION,				//rec->audio resolution
	COMM_SUBCMD_RECAUDIOSTOPRESOLUTION,			//rec->stop audio record resolution
	COMM_SUBCMD_RECSNAP,									//rec->snap
	COMM_SUBCMD_SUBCARDREC,								// subcard rec
	COMM_SUBCMD_BUFFER_TIME,							// subcard rec buffer time
	COMM_SUBCMD_WHOLE_TIME,							// subcard rec whole time
	COMM_SUBCMD_OVERLAY_TYPE,							// subcard rec overlay type
} eCOMM_SUBCMD_RECORD;

/* venc sub cmd type */
typedef enum {
	COMM_SUBCMD_VENCVIDEORESOLUTION,		// video resolution
	COMM_SUBCMD_VENCVIDEOENCODERTYPE ,	// video encoder type
	COMM_SUBCMD_VENCVIDEOBITRATE ,			// video bitrate
	COMM_SUBCMD_VENCVIDEOFRAMERATE ,		// video framerate
	COMM_SUBCMD_VENCVIDEOGOP ,				// video gop
	COMM_SUBCMD_VENCVIDEOCONTROLTYPE ,	// video control type
	COMM_SUBCMD_VENCVIDEOPROFILE ,			// video profile
	COMM_SUBCMD_VENCVIDEOCOVER ,				// video cover
	COMM_SUBCMD_VENCAUDIOTYPE ,				// audio type
} eCOMM_SUBCMD_VENC;

/* eth sub cmd type */
typedef enum {
	COMM_SUBCMD_ETHVIDEOIPADDRESS ,				// video ip address must
	COMM_SUBCMD_ETHVIDEOPORT,					// video port must
	COMM_SUBCMD_ETHVIDEORESOLUTION ,				// video resolution
	COMM_SUBCMD_ETHSTOPRESOLUTION,				// video stop
	COMM_SUBCMD_ETHAUDIOIPADDRESS,				// audio ip address must
	COMM_SUBCMD_ETHAUDIOPORT,					// audio port must
	COMM_SUBCMD_ETHAUDIOSTOP,					// audio stop
	COMM_SUBCMD_ETHAUDIOSTART,					// audio start
} eCOMM_SUBCMD_ETH;

/* isp sub cmd type */
typedef enum {
	COMM_SUBCMD_ISPVIDEOGAMMAPRESET,			//video gamma preset 0
	COMM_SUBCMD_ISPVIDEORESOLUTION,  				//video resolution 1
	COMM_SUBCMD_ISPVIDEOCONTRAST,				// video contrast 2
	COMM_SUBCMD_ISPVIDEOBRIGHTNESS,				//video brightness 3
	COMM_SUBCMD_ISPVIDEOCOLOR,					//video color 4
	COMM_SUBCMD_ISPVIDEOSHARPNESS,				//video sharpness 5
	COMM_SUBCMD_ISPVIDEODDP,						//video DDP 6
	COMM_SUBCMD_ISPVIDEODIS,						//video DIS 7
	COMM_SUBCMD_ISPVIDEOAWB,						//video AWB 8
	COMM_SUBCMD_ISPVIDEOAE,						//video AE 9
	COMM_SUBCMD_ISPVIDEOAF,						//video AF 10
	COMM_SUBCMD_ISPVIDEOAI,						//video AI 11
	COMM_SUBCMD_ISPVIDEOSHADING,					//video shading 12
	COMM_SUBCMD_ISPVIDEOSHADINGGAIN,				//video shading gain 13
	COMM_SUBCMD_ISPVIDEOSHADINGVARIANCE,		//video shading variance 14
	COMM_SUBCMD_ISPVIDEODRC,						//video DRC 15
	COMM_SUBCMD_ISPVIDEODRCLEVEL,				//video DRC level 16
	COMM_SUBCMD_ISPVIDEOANTIFLICKER,				//video anti flicker 17
	COMM_SUBCMD_ISPVIDEOANTIFLICKERFREQ,			//video anti flicker freq 18
	COMM_SUBCMD_ISPVIDEONR,						//video NR 19
	COMM_SUBCMD_ISPVIDEONRTHRESH,				//video NR  threash 20
	COMM_SUBCMD_ISPVIDEOWDR,						//video WDR 21
	COMM_SUBCMD_ISPVIDEOWDROFFSET,				//video WDR offset 22
	COMM_SUBCMD_ISPVIDEOWDRPIXELMAX,			//video WDR pixelmax 23
	COMM_SUBCMD_ISPVIDEOWDRRATIO,				//video WDR ratio 24
	COMM_SUBCMD_ISPVIDEOCRSH,					//video CRS h_strength 25
	COMM_SUBCMD_ISPVIDEOCRSV,						//video CRS v_strength 26
	COMM_SUBCMD_ISPVIDEOISREGADDR,				//video isreg addr 27
	COMM_SUBCMD_ISPVIDEOISREGDATA,				//video isreg data 28
	COMM_SUBCMD_ISPVIDEOGETISREGADDR,			//video get isreg addr 29
	COMM_SUBCMD_ISPVIDEOFPGAADDR,				//video FPGA addr 30
	COMM_SUBCMD_ISPVIDEOFPGADATA,				//video EPGA data 31
	COMM_SUBCMD_ISPVIDEOGETFPGAADDR,				//video get EPGA addr 32
	COMM_SUBCMD_ISPVIDEOINITWIDTH,				//video active width 33
	COMM_SUBCMD_ISPVIDEOINITHEIGHT,				//video active high 34
	COMM_SUBCMD_ISPVIDEOINITFRAME,				//video get EPGA data 35
	COMM_SUBCMD_ISPVIDEOINITBAYER,				//video get EPGA data 36
	COMM_SUBCMD_ISPVIDEOTERM,		 			//video term 37
	COMM_SUBCMD_ISPVIDEOGAMMA,					//video gamma 38
} eCOMM_SUBCMD_ISP;
/* IPv4(16) IPv6(24)*/
#define COMM_IP_ADDRESS_LENGTH 24

typedef enum {
	COMM_CF_SYSTEM=3,
	COMM_CF_VDACOVERDETECTED,
	COMM_CF_SDREMOVE,
	COMM_CF_VDARGNREACHMAX
} eCOMM_CF_RET;

/* struct */
typedef struct {
	/* command */
	LONG lCmd;
	/* option */
	LONG lOpt;
	/* value */
	LONG lVal;
} sCOMM_CMD;

#define DEBUG_SHOW
//#define DEBUG
//#define SHOW_INFO
//#define DEBUG_TERMINAL_REQ
//#define TEST_CHANNEL0_720P
#define CLOSE_TERM_REQ
#define CLOSE_GUI_REQ
#define CLOSE_RTP

/* use resolution 720p as default, if use 1080p, please comment this macro */
//#define USE_720P

// #define DEBUG_MEM
#ifdef DEBUG_MEM
#define MemDebug(str) do { \
	system("echo \'"str" => Mem : \'$(free | awk /Mem/'{print $4}')"); \
} while(0)
#else
#define MemDebug(str)
#endif

#define CASKY()	fprintf(stdout, "%s : <%d>\n", __func__, __LINE__)
#define SHOWVAL(x) printf("%s : <%ld> @ <%p>\n", #x, (LONG)(x), &(x))
#define SHOWPT(p) printf("%s : %p\n", #p, p)
#define SETDEFAULTVAL(var, val) (var=((var)==0)?(val):(var))
#ifdef DEBUG
#define debug_info(fmt, args...) \
	fprintf(stdout, fmt, ##args)
#else
#define debug_info(fmt, args...) 
#endif

#ifdef DEBUG_SHOW
#define debug_show(fmt, args...) \
	fprintf(stdout, fmt, ##args)
#else
#define debug_show(fmt, args...) 
#endif

// #define DEBUG_MALLOC
#ifdef DEBUG_MALLOC
#define MALLOC(x) fprintf(stdout, "[ MALLOC ] : %s <%d> len <%ld>\n", __func__, __LINE__, (LONG)x)
#else
#define MALLOC(x)
#endif

#define COMM_LONGTYPE_PERMAX 32
typedef struct _sCOMM_LONGTYPE{
	LONG lType0;
	LONG lType1;
} sCOMM_LONGTYPE;

typedef enum {
	COMM_LONGTYPE_NOTSET,
	COMM_LONGTYPE_ISSET
} eCOMM_LONGTYPE_STATE;

#define COMM_GET_STRPOOL() (gsShareMem.pHead + SM_OFFSET[COMM_SM_STRINGPOOL])

/* for configure system time */
#define BOOT_TIMESTAMP "/tmp/boottimestamp.tmp"
#define SAVEFILE_TIMESTAMP "/usr/local/bin/.filetimestamp.tmp"
#define PREVSET_TIMESTAMP "/tmp/prevsettimestamp.tmp"

/* variable */
pthread_mutex_t mutStringPoolWt;

void vCOMM_SetBit(sCOMM_LONGTYPE* psLongType, LONG lBit);
void vCOMM_UnsetBit(sCOMM_LONGTYPE* psLongType, LONG lBit);
LONG vCOMM_IsSetBit(sCOMM_LONGTYPE* psLongType, LONG lBit);
/* time measure */
void vCOMM_TimeMeasure(CHAR* pcCmt);

void vCOMM_PrintTime(CHAR* pcMsg, time_t* psTime);

/* dump function */
void vCOMM_MemPrint(ULONG ulStartMemAddr,LONG lLength,UCHAR *plMemData);

eCOMM_RET_STAT eCOMM_GetFileName(CHAR* pcFilename, sCOMM_FILENAME_INFO* psFileInfo);


#ifdef __cplusplus
}
#endif


#endif /* __COMMON_COM_H__ */
