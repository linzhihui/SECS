/**************************************************
*  This source is used to define some classes.This header
*  file is mainly for SECSII-based application development.
*  All copyright reserved.If you have any questions or
*  Author: peixuewen  Addr:Shenzhen.China
*  CreationTime:2019.08.15
**************************************************/

#ifndef _SECSII_FUNCS_PEIXUEWEN_H_
#define _SECSII_FUNCS_PEIXUEWEN_H_

#include <TCHAR.h>
#include <windows.h>
#include <winsock2.h>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

typedef unsigned long  DWORD;
typedef int                    BOOL;
typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef float                FLOAT;
typedef FLOAT             *PFLOAT;
typedef BOOL near      *PBOOL;
typedef BOOL far         *LPBOOL;
typedef BYTE near       *PBYTE;
typedef BYTE far          *LPBYTE;
typedef int near           *PINT;
typedef int far             *LPINT;
typedef WORD near    *PWORD;
typedef WORD far       *LPWORD;
typedef long far          *LPLONG;
typedef DWORD near *PDWORD;
typedef DWORD far    *LPDWORD;
typedef void far          *LPVOID;
typedef CONST void far *LPCVOID;
typedef int                 INT;
typedef unsigned int UINT;
typedef unsigned int *PUINT;

#pragma warning (disable:4267)
#pragma warning (disable:4244)
#pragma warning (disable:4800)


#ifdef SECS_EXPORTS
#define SECS_API __declspec(dllexport)
#else
#define SECS_API __declspec(dllimport)
#endif

#define WM_S6F1_TRACEDATA (WM_USER+976)
#define WM_S5F1_ALARMREPORT (WM_USER+977)


//SType=Session Type
#define SType_0             0         //Data Message
#define SType_1             1         //select.req
#define SType_2             2         //select.rsp
#define SType_3             3         //deselect.req
#define SType_4             4         //deselect.rsp
#define SType_5             5         //linktest.req
#define SType_6             6         //linktest.rsp
#define SType_7             7         //reject.req
#define SType_8             8         //not used
#define SType_9             9         //separate.req
#define SType_10           10       //not used.
#define SType_11           11       //11-127:reserved for subsidiary standards
#define SType_128         128     //128-255:reserved.not used

//PType=Presentation Type
#define PType_0             0         //SECS_II Encoding
#define PType_1_127      1         //reserved for subsidiary standards
#define PType_128_255  2         //reserved,not used

//Reject Reason Code
#define REJECT_CODE_0 0         //SType not supported
#define REJECT_CODE_1 1         //PType not supported
#define REJECT_CODE_2 2         //Transaction not open
#define REJECT_CODE_3 3         //Entity not selected
#define REJECT_CODE_4 4         //4-127:subsidiary standard-specific
#define REJECT_CODE_128 128 //128-255:local entity-specific reasons

//SelectStatus
#define SELECT_STATUS_0 0     //successfully
#define SELECT_STATUS_1 1     //already has Selected
#define SELECT_STATUS_2 2     //Connection not ready
#define SELECT_STATUS_3 3     //connection exhausted
#define SELECT_STATUS_4 4     //4-127:subsidiary standard-specific
#define SELECT_STATUS_5 128  //128-255:local entity-specific reasons

//DeselectStatus
#define DESELECT_STATUS_0 0 //successfully
#define DESELECT_STATUS_1 1 //communication not established
#define DESELECT_STATUS_2 2 //communication busy
#define DESELECT_STATUS_3 3 //3-127:subsidiary standard-specific
#define DESELECT_STATUS_4 4 //128-255:local entity-specific reasons

//Utility  Macros
#define FORMAT_NO(a)    (a&0x03)  //Get No. of length
#define FORMAT_CODE(a) (eFormatCode)(a&0xFC) //Get Format Code bit2-bit7
#define GetFormatCode(a) ((a&0xFC)>>2) //Shift 2bits to the right
#define Message(a)  {TCHAR strtmp[256]={0};	sprintf(strtmp,"%s \r\n %s, %d", a , __FILE__, __LINE__ ); ::MessageBox(0, strtmp,  strtmp, 0);}
#define TLI(n) (((n>>21)&0x80)|((n>>18)&0x40)|((n>>15)&0x20)|((n>>12)&0x10)|((n>>9)&0x08)|((n>>6)&0x04)|((n>>3)&0x02)|((n)&0x01))
#define B(n) TLI(0x##n##l)
#define SnFn(Sn, Fn)   ((Sn << 8) | (Fn & 0xff))
#define SHIFT2B(value) ((value &0xff) << 8 | (value &0xff00) >> 8) 
#define SHIFT4B(value) ((value &0x00ff) << 24 | (value &0x0000ff00)<< 8 | (value &0x00ff0000)>> 8 | (value &0xff000000)>> 24) 
#define arrayof(v) (sizeof(v)/sizeof(v[0]))
#define MAX_IDS   2000   //Max for each IDs
#define MAX_ITEMS   200   //for Report Variable Items,Trace SVIDs, Max ReportCount of Collection Events.

//Format Code
#define FORMAT_ITEM         -1       //ITEM
#define FORMAT_LIST           0x0      //LIST 
#define FORMAT_BINARY     0x20     //BINARY
#define FORMAT_BOOLEAN 0x24     //Boolean
#define FORMAT_ASCII         0x40     //ASCII
#define FORMAT_JIS8           0x44     //JIS-8
#define FORMAT_2B_CH       0x48     //2-byte character
#define FORMAT_8B_INT      0x60     //8-byte integer(signed)
#define FORMAT_1B_INT      0x64     //1-byte integer(signed)
#define FORMAT_2B_INT      0x68     //2-byte integer(signed)
#define FORMAT_4B_INT      0x70     //4-byte integer(signed)
#define FORMAT_8B_FLOAT 0x80     //8-byte floating point
#define FORMAT_4B_FLOAT 0x90     //4-byte floating point
#define FORMAT_8B_UINT   0xA0     //8-byte integer(unsigned)
#define FORMAT_1B_UINT   0xA4     //1-byte integer(unsigned)
#define FORMAT_2B_UINT   0xA8     //2-byte integer(unsigned)
#define FORMAT_4B_UINT   0xB0     //4-byte integer(unsigned)

//Format Code, As aboves,it is the same.
#define FORMAT_CODE_LIST           00      //LIST 
#define FORMAT_CODE_BINARY     010    //BINARY
#define FORMAT_CODE_BOOLEAN_ 011   //Boolean
#define FORMAT_CODE_ASCII         020     //ASCII
#define FORMAT_CODE_JIS8           021     //JIS-8
#define FORMAT_CODE_2B_CH       022     //2-byte character
#define FORMAT_CODE_8B_INT      030     //8-byte integer(signed)
#define FORMAT_CODE_1B_INT      031     //1-byte integer(signed)
#define FORMAT_CODE_2B_INT      032     //2-byte integer(signed)
#define FORMAT_CODE_4B_INT      034     //4-byte integer(signed)
#define FORMAT_CODE_8B_FLOAT 040     //8-byte floating point
#define FORMAT_CODE_4B_FLOAT 044     //4-byte floating point
#define FORMAT_CODE_8B_UINT   050     //8-byte integer(unsigned)
#define FORMAT_CODE_1B_UINT   051     //1-byte integer(unsigned)
#define FORMAT_CODE_2B_UINT   052     //2-byte integer(unsigned)
#define FORMAT_CODE_4B_UINT   054     //4-byte integer(unsigned)

//The length of types
#define FORMAT_2B_CH_LENGTH       2     //2-byte character
#define FORMAT_8B_INT_LENGTH      8     //8-byte integer(signed)
#define FORMAT_1B_INT_LENGTH      1     //1-byte integer(signed)
#define FORMAT_2B_INT_LENGTH      2     //2-byte integer(signed)
#define FORMAT_4B_INT_LENGTH      4     //4-byte integer(signed)
#define FORMAT_8B_FLOAT_LENGTH 8     //8-byte floating point
#define FORMAT_4B_FLOAT_LENGTH 4     //4-byte floating point
#define FORMAT_8B_UINT_LENGTH   8     //8-byte integer(unsigned)
#define FORMAT_1B_UINT_LENGTH   1     //1-byte integer(unsigned)
#define FORMAT_2B_UINT_LENGTH   2     //2-byte integer(unsigned)
#define FORMAT_4B_UINT_LENGTH   4     //4-byte integer(unsigned)

//LSH=Localized String Header
#define LSH_NONE            0            //reserved
#define LSH_ISO_10646     1            //Unicode 2.0 = UCS-2
#define LSH_UTF8              2            //UTF-8
#define LSH_ISO_646         3            //ASCII,7-bit
#define LSH_ISO_8859_1    4            //ISO Latin-1, Western Europe
#define LSH_ISO_8859_11  5            //Thai
#define LSH_TIS_620          6            //Thai
#define LSH_IS_13194        7            //ISC88
#define LSH_SHIFT_JIS        8            //Shift JIS
#define LSH_EUC_JP           9            //Japanese EUC-JP
#define LSH_EUC_KR         10           //Korean EUC-KR
#define LSH_SIMPLIFIED   11           //Simplified Chinese GB
#define LSH_EUC_CN        12           //Simplified Chinese EUC-CN
#define LSH_TRAD_BIG5   13           //Traditional Chinese Big5
#define LSH_EUC_TW         14          //Traditional Chinese EUC-TW
//15-32767 are reserved.
//32767-65535 for custom purposes.

//ALCD
//Alarm Code Byte.
#define ALCD_AlarmSet(a)           (a=(a|0x80))
#define ALCD_AlarmClear(a)        (a=(a&0x7f))
#define ALCD_AlarmCategory(a)  (a=(a&0x7f))

//ALED  Alarm enable/disable code,1byte
#define ALED_EnableAlarm(a)     (a=(a|0x80))
#define ALED_DisableAlarm(a)    (a=(a&0x7f))

// ------------------ Alarm ID -------------
#define IDX_ALID_START 1000
#define IDX_ALID_END   1998

// ------------SVID =  Status variable ID--------------
#define IDX_SVID_START  1999 
#define IDX_SVID_END  2999

//   ----DVVAL = Data Variable ID ------------
#define IDX_DVID_START          2999
#define IDX_DVID_END  5999

// --------ECID = Equipment Constant ID -------
//Abbr.
#define IDX_ECID_START    5999
#define IDX_ECID_END      6999

// ----------------- Process Program ID --------------
// 处理程序 的 ID，加工文件的ID
#define IDX_PPID_1				1
#define IDX_PPID_2				2
#define IDX_PPID_3				3

// ------------------ Collected Event ID ------------

//------------  事件 ---------


// ------------------ Report ID -------------

#pragma pack(push)

#pragma pack (4)
//HSMS Header
typedef struct tagHSMSHeader
{
	BYTE Length[4];
	BYTE  HighDeviceID; //Session ID or Device ID;bit7:0= H->E, 1=E->H
	BYTE LowDeviceID; //Session ID or Device ID;
	BYTE HeaderByte2;//For control msg,it contains 0 or status code; for data msg, it contains the W-Bit & SECS stream
	BYTE HeaderByte3;//control:0 or status code;data msg, secs function
	BYTE PType;         //Presentation Type, E, HighBlock
	BYTE SType;         //Session Type,  LowBlock
	BYTE SystemByte[4];// 0-1: source id, 2-3: transaction id; transaction identifier
}HSMSHeader,*PHSMSHeader,*LPHSMSHeader;

//Data Structure
typedef struct tagDataStructure
{
	BYTE bytes;            //No. of length,use FORMAT_NO to get it
	BYTE FormatCode; //Format of of item data,use FORMAT_CODE to get it
}DS,*PDS,*LPDS;

typedef struct tagSenderBufferItem
{
	void *buf;
	int type;
	int len;
}SenderBufferItem;

#pragma pack ()
#pragma pack(pop)

enum eDeviceType
{
	Equipment = 0,
	Host = 1,
};

enum eCommMethod
{
	E4_RS232 = 0,
	E37_HSMS_TCP = 1,
	NullMethod,
};


enum eCommMode
{
	NullMode = 0,
	Active = 1,
	Passive = 2
};


//used to fill the SType field of Message Header
enum eSType
{   
	Data_message = SType_0,
	Select_req = SType_1,
	Select_rsp = SType_2,
	Deselect_req = SType_3,
	Deselect_rsp = SType_4,
	Linktest_req = SType_5,
	Linktest_rsp = SType_6,
	Reject_req = SType_7,
	Not_used = SType_8,
	Separate_req = SType_9,
};

typedef  eSType eControlMsg;

//used to fill  the PType filed of Message Header
//PType=Presentation Type
enum ePType
{
	SECS_II_Encoding = PType_0, //SECS_II Encoding
	Subsidiary = PType_1_127,    //reserved for subsidiary standards
	Reserved = PType_128_255,   //reserved,not used
};

enum eSelectStatus
{
	Selected = SELECT_STATUS_0,        //communication established.
	AlreadyActive=SELECT_STATUS_1,//Already Active and selected.
	NotReady = SELECT_STATUS_2,     //Not ready to accept select request
	ConnectExhaust=SELECT_STATUS_3,//ip connection is unable to service more.
	NotSelected = 4,
};

enum eCommunicationStates
{
	NOTCOMMUNICATING = 0,
	COMMUNICATING
};

enum eControlStates
{
	OFFLINE = 0,
	ONLINE = 1,
};

enum eProcessingStates
{
	IDLE = 0,
	SETUP,  //Processing
	READY,  //Processing
	EXECUTING,  //Processing
	PAUSE
};

enum eDeselectStatus
{
	Ended = DESELECT_STATUS_0,        //communication Ended.
	NotEstablished=DESELECT_STATUS_1,//communication not established.
	Busy = DESELECT_STATUS_2,               //communication busy
};

enum eRejectReason
{
	STypeNotSupported = REJECT_CODE_0,
	PTypeNotSupported = REJECT_CODE_1,
	TransactionNotOpen= REJECT_CODE_2,
	EntityNotSelected= REJECT_CODE_3,
};

enum IDENTITY_MSG
{
	NORMAL_MSG = 0,
	UNKNOWN_MSG = 1,
	ABORTED_MSG = 2,
	INVALID_MSG = 3,
	RELOAD_MSG = 4,
	COMPOSER_FAILMSG = 5,
	CONNECTED = 6,
	DISCONNECTED = 7,
	TIMEOUT = 8,
	SEQUENCE = 9,
};

enum MultiCharacterEncoding
{
	NONE = 0,
	ISO10646 = 1,
	UTF_8 = 2,
	ISO646 = 3,
	ISO8859_1 = 4,
	ISO8859_11 = 5,
	TIS620 = 6,
	IS13194 = 7,
	SHIFT_JIS = 8,
	JAPANESE = 9,
	KOREAN = 10,
	CHINESE_GB = 11,
	CHINESE_EUC_CN = 12,
	CHINESE_BIG5 = 13,
	CHINESE_EUC_TW = 14,
};

enum eDirection
{
	E2H  = 0,   // Equipment->Host
	H2E  = 1,  //  Host->Equipment
	Both = 2,  //  Host<->Equipment
};

enum eFormatCode
{
	ITEM = FORMAT_ITEM,              //ITEM 
	LIST = FORMAT_LIST,                  //LIST 
	BINARY = FORMAT_BINARY,      //BINARY
	BOOLEAN_=FORMAT_BOOLEAN,//Boolean
	ASCII = FORMAT_ASCII ,              //ASCII
	JIS8 = FORMAT_JIS8,                    //JIS-8
	CHAR_2B = FORMAT_2B_CH,      //2-byte character
	INT_8B = FORMAT_8B_INT,          //8-byte integer(signed)
	INT_1B = FORMAT_1B_INT,          //1-byte integer(signed)
	INT_2B = FORMAT_2B_INT,           //2-byte integer(signed)
	INT_4B = FORMAT_4B_INT,           //4-byte integer(signed)
	FLOAT_8B = FORMAT_8B_FLOAT, //8-byte floating point
	FLOAT_4B = FORMAT_4B_FLOAT, //4-byte floating point
	UINT_8B = FORMAT_8B_UINT,      //8-byte integer(unsigned)
	UINT_1B = FORMAT_1B_UINT ,     //1-byte integer(unsigned)
	UINT_2B = FORMAT_2B_UINT,      //2-byte integer(unsigned)
	UINT_4B = FORMAT_4B_UINT,      //4-byte integer(unsigned)
	HEADER_ONLY,                              //header only.No data
};

enum eFormatCodeLength
{
	CHAR_2B_LEN = FORMAT_2B_CH_LENGTH,    //2-byte character
	INT_8B_LEN = FORMAT_8B_INT_LENGTH,       //8-byte integer(signed)
	INT_1B_LEN = FORMAT_1B_INT_LENGTH,      //1-byte integer(signed)
	INT_2B_LEN = FORMAT_2B_INT_LENGTH,       //2-byte integer(signed)
	INT_4B_LEN = FORMAT_4B_INT_LENGTH,       //4-byte integer(signed)
	FLOAT_8B_LEN = FORMAT_8B_FLOAT_LENGTH, //8-byte floating point
	FLOAT_4B_LEN = FORMAT_4B_FLOAT_LENGTH, //4-byte floating point
	UINT_8B_LEN = FORMAT_8B_UINT_LENGTH,     //8-byte integer(unsigned)
	UINT_1B_LEN = FORMAT_1B_UINT_LENGTH,     //1-byte integer(unsigned)
	UINT_2B_LEN = FORMAT_2B_UINT_LENGTH,     //2-byte integer(unsigned)
	UINT_4B_LEN = FORMAT_4B_UINT_LENGTH ,    //4-byte integer(unsigned)
};

enum SECSInfo
{
	HOST = 0,
	EQUIPMENT = 1,
	ACTIVE = 2,
	PASSIVE = 3,
	MASTER = 4,
	SLAVE = 5,
	HSMS = 6,
	SECS1 = 7,
};

enum eTimeOut
{
	T3 = 1003, //reply timeout
	T5 = 1005, //connect separation timeout
	T6 = 1006, //control timeout
	T7 = 1007, //connection idle timeout
	T8 = 1008, //network intercharacter timeout
};


enum ACKA
{
	eFALSE = 0,
	eTRUE = 1,
};


enum ACKC3
{
	eAccepted = 0,
	eError = 1,
};
typedef ACKC3 ACKC5,ACKC6;

enum ACKC7
{
	eAccepted_ = 0,
	PermissionNotGranted,
	LengthError,
	MatrixOverFlow,
	PPIDNotFound,
	ModeUnsupported,
	OtherError
};


enum ACKC7A
{
	eAccepted__ = 0,
	MDLN_is_inconsistent,
	SOFTREV_is_inconsistent,
	InvalidCCODE,
	InvalidPPARMValue,
	OtherError_,
};


enum ACKC10
{
	eAccepted_for_display = 0,
	MessageWillNotBeDisplayed,
	TerminalNotAvailable,
};


enum ACKC13
{
	OK = 0,
	ERROR_TryLater,
	ERROR_UnknownDataSetName,
	ERROR_illegalCheckPointValue,
	ERROR_TooManyOpenDataSets,
	ERROR_DataSetOpenTooManyTimes,
	ERROR_NoOpenDataSet,
	ERROR_CannotContinue,
	ERROR_EndOfData,
	ERROR_HandleInUse,
	ERROR_PendingTransaction,
};

enum ALCD_Category
{
	ALCD_Not_Used = 0,
	ALCD_PersonalSafety,
	ALCD_EquipmentSafety,
	ALCD_ParamCtrlWarning,
	ALCD_ParamCtrlError,
	ALCD_IrrecoverableError,
	ALCD_EqpStatusWarning,
	ALCD_AttentionFlags,
	ALCD_DataIntegrity,
	ALCD_OtherCategories,
};

typedef struct tagItemData
{
	eFormatCode format;
	int len;
	BYTE *data;
}ItemData;

typedef BYTE ListItemData;


//Alarm ID
typedef struct tagALID
{
	short ALID;
	char ALTX[64];// Alarm Text
	int ALCD;  // category: bit
	eFormatCode format;//use atoi(sv),atof() to convert ECV[]  
	BYTE ALED;  //Enable / Disable
	char EXPLAIN[64];//Explaination
	char Name[32];//Alarm Name
}ALID;

//Process Program ID
typedef struct tagPPID
{
	short PPID;
	char ASCII[64];
	int PPBODY;
	eFormatCode format;
	char EXPLAIN[64];
}PPID;

//Collection Event ID
typedef struct tagCEID
{
	short CEID;
	char ASCII[64];
	int  RPTCOUNT;
	int  nRPTID[MAX_ITEMS];//each ceid can link max=MAX_ITEMS reports
	bool CEED; //Enable / Disable
	char EXPLAIN[64];
}CEID;

//Report ID
typedef struct tagRPTID
{
	short RPTID;
	char ASCII[64];
	int VCOUNT;
	int nVID[MAX_ITEMS];//each rptid can link max=MAX_ITEMS VID,enough
	char EXPLAIN[64];
}RPTID;

//Variable ID
//encompasses SVID, ECID,DVVAL  etc.
typedef struct tagVID
{
	short VID;
	char ASCII[64];      //name
	char V[260];            //SV, ECV, DV, in order to fit any type,according to format
	char DEF[64];       //default value
	char UNITS[32];   //units
	eFormatCode format;//use atoi(sv),atof() to convert ECV[]  
	char EXPLAIN[64];//Explaination
	char MIN[32];  //range
	char MAX[32]; //range
}VID, SVID, ECID, DVVAL,DVID;

//Trace ID
typedef struct tagTRID
{
	short TRID;
	int DSPER; //data sample period
	int TOTSMP;//total samples
	int REPGSZ; //Reporting Group size;
	short SVIDs[MAX_ITEMS]; //each TRID can link max=100 SVID,enough
	int SVIDCount;// svid count in fact.
}TRID;

typedef unsigned long long HCOMM; //communicate channel.


// 项目内需要更新ID对应的内容值，推荐用 UpdateID
//update the value according to the specified ID
//EQP should update the value on Real-Time.
//e.g.
//UpdateID(SVID_PROCESS_STATUS, 1);
SECS_API bool UpdateID(short ID, int v);
SECS_API bool UpdateID(short ID, float v);
SECS_API bool UpdateID(short ID, double v);
SECS_API bool UpdateID(short ID, char* v);

// --------------   以下内容一般原则上，外部不用调用 -----------------------

//e.g.
//SVID *svid = GetSVID(IDX_SVID_PROCESS_STATUS);
//or.
//SVID *svid = GetSVID("ProcessStatus");
//    _AV_((VID *)svid , 1); 

SECS_API SVID *GetSVID(short ID);
SECS_API SVID *GetSVID(char* NAME);
SECS_API SVID *GetSVIDByIndex(int index);
SECS_API int GetSVIDCount();

//e.g.
//ECID *ecid = GetECID("LASERPOWER");
//or
//ECID *ecid = GetECID(IDX_ECID_LASERPOWER);
//     _AV_((VID *)ecid, 350); 
SECS_API ECID *GetECID(short ID);
SECS_API ECID *GetECID(char* NAME);
SECS_API ECID *GetECIDByIndex(int index);
SECS_API int GetECIDCount();
//e.g.
//DVID *dvid = GetDVVAL(IDX_DVVAL_ID_LOT);
//     _AV_((VID *)dvid, "200"); 
//or.
//DVID *dvid = GetDVVALID("LOT");
//     _AV_((VID *)dvid, 200); 

SECS_API DVID *GetDVID(short ID);
SECS_API DVID *GetDVVAL(short ID);
SECS_API DVID *GetDVVALID(char* NAME);
SECS_API DVID *GetDVVALByIndex(int index);
SECS_API int GetDVVALCount();

SECS_API ALID *GetALID(short ALID);
SECS_API ALID *GetALIDByIndex(int index);
SECS_API int GetALIDCount();

SECS_API PPID *GetPPID(short PPID_NUM);
SECS_API PPID *GetPPID(char* PPID_ASCII);
SECS_API PPID *GetPPIDByIndex(int index);
SECS_API int GetPPIDCount();

SECS_API CEID *GetCEID(short CEID_NUM);
SECS_API CEID *GetCEID(char* CEID_ASCII);
SECS_API CEID *GetCEIDByIndex(int index);
SECS_API int GetCEIDCount();

SECS_API int* GetRPTIDFromCeid(int ceid);
SECS_API RPTID *GetRPTID(short RPTID_NUM);
SECS_API RPTID *GetRPTID(char* RPTID_ASCII);
SECS_API RPTID *GetRPTIDByIndex(int index);
SECS_API int GetRPTIDCount();

SECS_API TRID *GetTRID(short TRID);
SECS_API TRID *GetTRIDByIndex(int index);
SECS_API int GetTRIDCount();

//Assign Value 
SECS_API void _AV_(VID *pVID, int v);
SECS_API void _AV_(VID *pVID, float v);
SECS_API void _AV_(VID *pVID, double v);
SECS_API void _AV_(VID *pVID, char* v);


class CSecsComm;

class SECS_API SenderBuffer
{
public:
	SenderBuffer(CSecsComm *pSecsComm);
	virtual ~SenderBuffer();
public:
	void Add_HSMSHeader(HSMSHeader *pHeader);
	void Begin();
	void End();
	void Send();
public:
	void Add_LIST_Header(int nListCnt);                //LIST
	void BeginList();
	void EndList();
public:
	void Add_ITEM_Header(eFormatCode fc, size_t nCnt);       //ITEM
	void BeginItem();
	void EndItem();
public:
	void Add_BINARY(BYTE v);                  //BINARY=for Add_ITEM_Header(BINARY, 1);1 byte
	void Add_BINARY(void *buf, int len);  //BINARY=for Add_ITEM_Header(BINARY, N);N>=2 bytes
	void Add_BOOLEAN(bool value);        //Boolean
	void Add_ASCII(char *str);                   //ASCII
	void Add_ASCII(char *buf, int len);      //ASCII
	void Add_JIS8(char *buf, int len);        //JIS-8
	void Add_CHAR_2B(wchar_t ch);         //2-byte character
	void Add_INT_8B(long long value);    //8-byte integer(signed)
	void Add_INT_1B(unsigned char value); //1-byte integer(signed)
	void Add_INT_2B(short value);           //2-byte integer(signed)
	void Add_INT_4B(int value);               //4-byte integer(signed)
	void Add_FLOAT_8B(double value);  //8-byte floating point
	void Add_FLOAT_4B(float value);      //4-byte floating point
	void Add_UINT_8B(unsigned long long value); //8-byte integer(unsigned)
	void Add_UINT_1B(unsigned char value);      //1-byte integer(unsigned)
	void Add_UINT_2B(unsigned short value);    //2-byte integer(unsigned)
	void Add_UINT_4B(unsigned int value);        //4-byte integer(unsigned)
public:
	char *getSendBuffer(int &outBufLen);
	void ReleaseBuffer();
private:
	vector<SenderBufferItem> *m_pvtItems;
	CSecsComm *m_pSecsComm;
	void *m_pBuffer;
};

class SECS_API CHsmsHdrTool
{
protected:
	void PreFillHSMSHeader(HSMSHeader &outHeader, 	BYTE Byte2,BYTE Byte3,
		ePType PType = SECS_II_Encoding, eSType SType = Data_message);
public:
	void get_header_of_Data_message_primary(HSMSHeader &outHeader,
		bool bExpectReply,  BYTE StreamNo, BYTE FuncNo);
	void get_header_of_Data_message_reply(HSMSHeader &outHeader);
public:
	void get_header_of_Select_req(HSMSHeader &outHeader);
	void get_header_of_Select_rsp(HSMSHeader &outHeader,eSelectStatus status);
	void get_header_of_Deselect_req(HSMSHeader &outHeader);
	void get_header_of_Deselect_rsp(HSMSHeader &outHeader,eDeselectStatus status);
	void get_header_of_Linktest_req(HSMSHeader &outHeader);
	void get_header_of_Linktest_rsp(HSMSHeader &outHeader);
	void get_header_of_Reject_req(HSMSHeader &outHeader,eRejectReason reason);
	void get_header_of_Not_used(HSMSHeader &outHeader);
	void get_header_of_Separate_req(HSMSHeader &outHeader);
public:
	void set_header_direction(HSMSHeader &outHeader, eDirection dir);

	int GetTotalLength(HSMSHeader &outHeader);
	int GetBodyLength(HSMSHeader &outHeader);
	void SetBodyLength(HSMSHeader &outHeader,int len = 0) ;

	int  getDeviceId(HSMSHeader &outHeader) ;
	void setDeviceId(HSMSHeader &outHeader,int devid) ;

	void setSessionId(HSMSHeader &outHeader,WORD sessionid);
	WORD  getSessionId(HSMSHeader &outHeader);

	UINT getStreamNum(HSMSHeader &outHeader);
	void setStreamNum(HSMSHeader &outHeader,int num);

	UINT getFunctionNum(HSMSHeader &outHeader) ;
	void setFunctionNum(HSMSHeader &outHeader,int num);

	void setBlockNum(HSMSHeader &outHeader,int n);
	int  getBlockNum(HSMSHeader &outHeader);

	void setSourceNum(HSMSHeader &outHeader,int n);
	int  getSourceNum(HSMSHeader &outHeader);

	void setTransactionNum(HSMSHeader &outHeader,int n);
	int  getTransactionNum(HSMSHeader &outHeader);

	void IncreaseSourceNum(HSMSHeader &outHeader);
	void IncreaseTransactionNum(HSMSHeader &outHeader);
	void IncreaseSessionNum(HSMSHeader &outHeader);

	bool isPrimary(HSMSHeader &outHeader);
	bool isSecondary(HSMSHeader &outHeader) ;

	bool isSession(HSMSHeader &outHeader) ;
	bool wantSessionRsp(HSMSHeader &outHeader) ;

	bool getReplyFlag(HSMSHeader &outHeader) ;
	bool setReplyFlag(HSMSHeader &outHeader, bool bNeedReply) ;

	int isLegalHSMSHdr(char *pAddr,int BufSize, int &Need2Skip) ;
public:
	long long Get_INT_8B(BYTE *buf);       //8-byte integer(signed)
	unsigned char Get_INT_1B(BYTE *buf);   //1-byte integer(signed)
	short Get_INT_2B(BYTE *buf);           //2-byte integer(signed)
	int Get_INT_4B(BYTE *buf);              //4-byte integer(signed)
	double Get_FLOAT_8B(BYTE *buf);          //8-byte floating point
	float Get_FLOAT_4B(BYTE *buf);           //4-byte floating point
	unsigned long long Get_UINT_8B(BYTE *buf); //8-byte integer(unsigned)
	unsigned char Get_UINT_1B(BYTE *buf);     //1-byte integer(unsigned)
	unsigned short Get_UINT_2B(BYTE *buf);    //2-byte integer(unsigned)
	unsigned int Get_UINT_4B(BYTE *buf);      //4-byte integer(unsigned)
public:
	//return: LIST, if List, outCnt=Item Count, else ItemFormat, outCnt=bytes
	ListItemData * GetDataType(HSMSHeader* hdr,eFormatCode &outFC, int &outCnt);
	ListItemData *FindFirstItem(HSMSHeader* hdr, eFormatCode &outFC, int &outLen);
	ListItemData *FindNextItem(eFormatCode &outFC, int &outLen);
	
public:
	//overload， same as above
	// if return true, the data info storaged in the second paramter: item
	// if return false, no data or illegal data
	bool GetDataType(HSMSHeader* hdr,ItemData &item);
	bool  FindFirstItem(HSMSHeader* hdr, ItemData &item);
	bool  FindNextItem(ItemData &item);
	//For Nested List_1.
	ListItemData *GetChildSiblingItem_N(ListItemData* entry, eFormatCode &outFC, int &outLen);
public:
	//Get Int Value
	int GetIntData(eFormatCode format, BYTE *data);
	int GetIntData(ItemData &item);
public:
	UINT GetIniInt(char* lpSection, char* lpKey, INT nDefault);
	DWORD GetIniStr(char* lpSection, char* lpKey, char* lpDef, char* lpReturned, DWORD nSize);
	BOOL SetIniInt(char* lpSection, char* lpKey, INT nValue);
	BOOL SetIniStr(char* lpSectionName, char* lpKeyName, char* lpString);
public:
	WORD m_DeviceId;                  // Equipment
	eDeviceType m_DeviceType;   // Equipment, Host
	eCommMethod m_Method;    // E4_RS232,E37_HSMS_TCP
	eSelectStatus m_SelectStatus;// Selected,AlreadyActive,NotReady,ConnectExhaust
	eCommunicationStates m_eCommState;//Initiated after received S1F13
	eControlStates m_eControlState;   //For Remote Control, On-line, Off-line
	eProcessingStates m_eProcessState; //the Equipment Processing Status
	eCommMode m_Mode;          // Active=0,Passive=1
	volatile HCOMM m_hComm;   // Active Communicate handle; COM Handle,or Socket
	unsigned int m_nUnique;   //Unique Identifier
private:
	HSMSHeader* m_hdr_list;
	ListItemData* m_pCurItem;
	int m_nLeftListCnt;
	BYTE *m_pOffset;
};


class SECS_API CSecsComm : public CHsmsHdrTool
{
public:
	CSecsComm();
	virtual ~CSecsComm();
public:
	virtual bool Start();
	virtual void Stop();
	virtual bool LoadConfig();
	virtual bool EstablishConnection()=0;//Active
	virtual bool CreateServer() = 0;//Passive
public:
	virtual int Send(char *buf, int len, HCOMM hComm) = 0;
	virtual int Recv(char *buf, int len, HCOMM hComm) = 0;
public:
	virtual int Send(SenderBuffer &snd,  HCOMM hComm);
public:
	virtual void SetParam(eDeviceType type, eCommMethod method, eCommMode mode);
	virtual void RecvThread();//Active
	virtual void HeartBeat();
	virtual void TimeOut();
public:
	static DWORD RecvProc(LPVOID lp);     //Active-RecvProc
	static DWORD HeartBeatProc(LPVOID lp);//Active-HeartBeat
	static DWORD startPassiveServer(LPVOID lp);//Passive
	static DWORD TimeoutProc(LPVOID lp);//TimeoutProc
public:
	//data-message: SnFn
	virtual int data_message_proc(HSMSHeader *pHdr, HCOMM hComm);
	//control transactions
	virtual int Select_req_proc(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Select_rsp_proc(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Deselect_req_proc(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Deselect_rsp_proc(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Linktest_req_proc(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Linktest_rsp_proc(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Reject_req_proc(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Separate_req_proc(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S1F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F14(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F15(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F16(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F17(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F18(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F19(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S1F20(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S2F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F14(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F15(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F16(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F17(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F18(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F19(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F20(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F21(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F22(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F23(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F24(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F25(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F26(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F27(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F28(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F29(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F30(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F31(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F32(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F33(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F34(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F35(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F36(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F37(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F38(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F39(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F40(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F41(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F42(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F43(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F44(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F45(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F46(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F47(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F48(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F49(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F50(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F51(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F52(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F53(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F54(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F55(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F56(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F57(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F58(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S2F59(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S3F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F14(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F15(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F16(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F17(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F18(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F19(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F20(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F21(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F22(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F23(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F24(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F25(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S3F26(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S4F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F14(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F15(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F16(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F17(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F18(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F19(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F20(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F21(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F22(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F23(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F24(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F25(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F26(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F27(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F28(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F29(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F30(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F31(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F32(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F33(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F34(HSMSHeader *pHdr, HCOMM hComm);
    virtual int S4F35(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F36(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F37(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F38(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F39(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F40(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F41(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S4F42(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S5F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F14(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F15(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F16(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F17(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S5F18(HSMSHeader *pHdr, HCOMM hComm);
protected:
	virtual int S6F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F14(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F15(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F16(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F17(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F18(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F19(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F20(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F21(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F22(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F23(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F24(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F25(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F26(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F27(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F28(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F29(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S6F30(HSMSHeader *pHdr, HCOMM hComm);
protected:
	virtual int S7F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F14(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F15(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F16(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F17(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F18(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F19(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F20(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F21(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F22(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F23(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F24(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F25(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F26(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F27(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F28(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F29(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F30(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F31(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F32(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F33(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F34(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F35(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S7F36(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S8F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S8F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S8F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S8F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S8F4(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S9F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S9F14(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S10F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S10F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S10F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S10F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S10F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S10F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S10F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S10F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S10F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S10F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S10F10(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S12F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F14(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F15(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F16(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F17(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F18(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F19(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S12F20(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S13F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F14(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F15(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S13F16(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S14F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F14(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F15(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F16(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F17(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S14F18(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S15F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F14(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F15(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F16(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F17(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F18(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F19(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F20(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F21(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F22(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F23(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F24(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F25(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F26(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F27(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F28(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F29(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F30(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F31(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F32(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F33(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F34(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F35(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F36(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F37(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F38(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F39(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F40(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F41(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F42(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F43(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F44(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F45(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F46(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F47(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S15F48(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S16F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S16F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S16F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S16F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S16F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S16F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S16F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S16F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S16F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S16F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S16F10(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S17F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S17F14(HSMSHeader *pHdr, HCOMM hComm);
private:
	virtual int S18F0(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F2(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F4(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F6(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F8(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F10(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F12(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F13(HSMSHeader *pHdr, HCOMM hComm);
	virtual int S18F14(HSMSHeader *pHdr, HCOMM hComm);	
public:
	// user-defined SnFn
	virtual int SnFn_UserDef(HSMSHeader *pHdr, HCOMM hComm);
public:
	virtual int Send_Primary_S9F1(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Send_Primary_S9F3(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Send_Primary_S9F5(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Send_Primary_S9F7(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Send_Primary_S9F9(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Send_Primary_S9F11(HSMSHeader *pHdr, HCOMM hComm);
	virtual int Send_Primary_S9F13(HSMSHeader *pHdr, HCOMM hComm);
public:
	virtual void SendPrimaryS1F1();

	virtual void SendPrimaryS1F13();

	virtual void S5F1AlarmReport(bool bAlarm, short ALID);
	
	vector<int>* m_pEventV;
    
	//事件请求
	virtual void S6F5Request(short CEID);
	//事件上报(一个CEID关联一个RPTID)
	virtual void S6F11EventReport(short CEID);

	//S6F1,Trace Data Send
	void SetSecsWnd(HWND hwnd);
	virtual void S6F1TraceData(short TRID);

public:
	//detecting legitimacy
	bool isDeviceIdRecognizable(HSMSHeader *pHdr);
	bool isStreamSupported(HSMSHeader *pHdr);
	bool isFunctionSupported(HSMSHeader *pHdr);
	bool isDataFormatLegal(HSMSHeader *pHdr);
	bool isDataTooLong(HSMSHeader *pHdr);
protected:
	bool AppendSelectedDevice(WORD deviceid);
	bool AppendRegisteredDevID(WORD deviceid);
	void RemoveSelectedDevice(WORD deviceid);
	bool isDeviceInSelectedList(WORD deviceid);
	int  GetSelectedDeviceCount();
	virtual bool ProcessClient(HSMSHeader* pHdr, HCOMM hComm);
private:
	WORD m_vtSelectedDevices[1024];//Selected Devices ID; Max Count=1024;
	WORD m_arrRegisteredDevID[4096];//m_arrRegisteredDevID; Max Count=4096;
	WORD m_nSelectedIndex;
	WORD m_nRegisteredIndex;
	bool  m_bOn_Off_Line;   //true = On line, false = off line status;
protected:
	HANDLE m_hEventStop;
	HWND m_hRecvMsgWnd;  //used to recv msg.
public:
	void startTimerT3();
	void startTimerT5();
	void startTimerT6();
	void startTimerT7();
	void startTimerT8();
	void stopTimerT3();
	void stopTimerT5();
	void stopTimerT6();
	void stopTimerT7();
	void stopTimerT8();
protected:
	virtual void TriggerT3();
	virtual void TriggerT5();
	virtual void TriggerT6();
	virtual void TriggerT7();
	virtual void TriggerT8();
private:
	unsigned int T3;//timer
	unsigned int T5;//timer
	unsigned int T6;//timer
	unsigned int T7;//timer
	unsigned int T8;//timer
	bool m_b_T3_started; //T3 timer started?
	bool m_b_T5_started; //T5 timer started?
	bool m_b_T6_started; //T6 timer started?
	bool m_b_T7_started; //T7 timer started?
	bool m_b_T8_started; //T8 timer started?
	unsigned int m_nTimeout_T3; //T3:reply timeout
	unsigned int m_nTimeout_T5; //T5:connect separation timeout
	unsigned int m_nTimeout_T6; //T6:control timeout
	unsigned int m_nTimeout_T7; //T7:connection idle timeout
	unsigned int m_nTimeout_T8; //T8:network intercharacter timeout
 
};

class SECS_API CSecsRS232 : public CSecsComm
{
public:
	CSecsRS232();
	virtual ~CSecsRS232();
public:
	virtual bool Start();
	virtual void Stop();
	virtual bool LoadConfig();
public:
	virtual bool EstablishConnection();//Active
	virtual bool CreateServer();//Passive
public:
	virtual int Send(char *buf, int len, HCOMM hComm);
	virtual int Recv(char *buf, int len, HCOMM hComm);
private:
	DWORD m_dwBaudRate;
	BYTE m_nDataSize;
	BYTE m_nStopbit;
	HANDLE m_hRS232Com;
	char m_szCom[16];
};


class SECS_API CSecsTCP : public CSecsComm
{
public:
	CSecsTCP();
	virtual ~CSecsTCP();
public:
	virtual bool Start();
	virtual void Stop();
	virtual bool LoadConfig();
public:
	virtual bool EstablishConnection();//Active
	virtual bool CreateServer();//Passive
public:
	static DWORD startCliectProc(LPVOID lp);
	void CliectProc();
public:
	virtual int Send(char *buf, int len, HCOMM hComm);
	virtual int Recv(char *buf, int len, HCOMM hComm);
private:
	char m_szIp[18];
	short m_nPort;
	bool m_bSocketStatus;
	SOCKET m_sock;
	vector<SOCKET> *m_pvtSocks;
	CRITICAL_SECTION m_csCriticalSection;
	CRITICAL_SECTION m_csRecvCriticalSection;
};

class SECS_API CEquipmentRS232 : public CSecsRS232
{
public:
	CEquipmentRS232(eCommMode mode);
	virtual ~CEquipmentRS232();
public:
};

class SECS_API CEquipmentTCP : public CSecsTCP
{
public:
	CEquipmentTCP(eCommMode mode);
	virtual ~CEquipmentTCP();
public:
};


class SECS_API CHostRS232 : public CSecsRS232
{
public:
	CHostRS232(eCommMode mode);
	virtual ~CHostRS232();
};

class SECS_API CHostTCP : public CSecsTCP
{
public:
	CHostTCP(eCommMode mode);
	virtual ~CHostTCP();
};


#endif