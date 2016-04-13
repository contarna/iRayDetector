/******************************************************************
**  FileName   : FpdStructs.h
**
**  Description: This file is the structures and related enums.
**  
**  Copyright  : iRay Technology (Shanghai) Ltd.
******************************************************************/

#ifndef _FPD_STRUCTS_
#define _FPD_STRUCTS_

#define PATHLENGTH	260
#define CHARLEN		260

/*=========================================================================
/*NAME		    : DRCallback
/*DESCRIPTION   : Callback function definition flat panel detector feedback information and image data.
=========================================================================*/
typedef int (CALLBACK* DRCallback)(HANDLE, int, WORD*, int, int, int, int, int, float, float, void*);

/*=========================================================================
/*NAME		    : SyncBoxCallback
/*DESCRIPTION   : Callback function definition synchronization controlbox feedback information.
=========================================================================*/
typedef int (CALLBACK* SyncBoxCallback)(int, int, int, int);

/*=========================================================================
/*NAME		    : DetectorMode
/*DESCRIPTION   : Detector mode
/*MEMBER	    : 
/*FPD_DYNAMIC	: Dynamic detector
/*FPD_STATIC	: Static detector
=========================================================================*/
enum DetectorMode
{
	FPD_DYNAMIC,
	FPD_STATIC,
};

/*=========================================================================
/*NAME		    : ConnectionMode
/*DESCRIPTION   : The detector connection mode
/*MEMBER	    : 
/*FPD_COM_CONN	: COM connection
/*FPD_NET_CONN	: Net connection
=========================================================================*/
enum ConnectionMode
{
	FPD_COM_CONN,
	FPD_NET_CONN,
};

/*=========================================================================
/*NAME		    : ImageFlipRotateMode
/*DESCRIPTION   : Image flip rotate mode
/*MEMBER	    : 
/*FPD_MODE1		: Image flip rotate mode 1
/*FPD_MODE2		: Image flip rotate mode 2
/*FPD_MODE3		: Image flip rotate mode 3
/*FPD_MODE4		: Image flip rotate mode 4
=========================================================================*/
enum ImageFlipRotateMode
{
	FPD_MODE1,
	FPD_MODE2,
	FPD_MODE3,
	FPD_MODE4,
};

/*=========================================================================
/*NAME		    : CorrectMode
/*DESCRIPTION   : Set correct mode
/*MEMBER	    	: 
/*FPD_CORR_NULL	  : Do not correct
/* FPD_CORR_CURRENT: Set current correct mode
/* FPD_CORR_DEFAULT: Set default correct mode
=========================================================================*/
enum CorrectMode
{
	FPD_CORR_NULL,
	FPD_CORR_CURRENT,
	FPD_CORR_DEFAULT,
};

/*=========================================================================
/*NAME		    : ConfigMode
/*DESCRIPTION   : Write detector configuration mode
/*MEMBER	    : 
/*FPD_CONFIG_RAM	 : The configuration information is written to the detector in RAM
/*FPD_CONFIG_ROM	 : The configuration information is written to the detector in ROM
/*FPD_CONFIG_INITIAL: The configuration information is written to the original parameters area of the detector
=========================================================================*/
enum ConfigMode
{
	FPD_CONFIG_RAM,
	FPD_CONFIG_ROM,
	FPD_CONFIG_INITIAL,
};

/*=========================================================================
/*NAME		    : UptFirmwareMode
/*DESCRIPTION   : Update firmware mode
/*MEMBER	    : 
/* FPD_UPT_FW_NULL		  : Do not update
/*FPD_UPT_MAIN			  : Update main board firmware
/*FPD_UPT_READ			  : Update read board firmware
/*FPD_UPT_CONTROL_BOX: Update controlbox firmware
=========================================================================*/
enum UptFirmwareMode
{
	FPD_UPT_FW_NULL,
	FPD_UPT_MAIN,
	FPD_UPT_READ,
	FPD_UPT_READ_2,
	FPD_UPT_CONTROL_BOX,
	FPD_UPT_SYNC_BOX,
};

/*=========================================================================
/*NAME		    : UptCorrectMode
/*DESCRIPTION   : Update correct template mode
/*MEMBER	    : 
/*FPD_UPT_NULL	: Do not update
/*FPD_UPT_OFFSET: Update offset correct template
/*FPD_UPT_GAIN	: Update gain correct template
/*FPD_UPT_DEFECT: Update defect correct template
=========================================================================*/
enum UptCorrectMode
{
	FPD_UPT_CORR_NULL,
	FPD_UPT_OFFSET,
	FPD_UPT_GAIN,
	FPD_UPT_DEFECT,
};

/*=========================================================================
/*NAME				: DefectModifyMode
/*DESCRIPTION		: Modify defect pixel mode
/*MEMBER			: 
/*FPD_DEFECT_ADD	: Add
/*FPD_DEFECT_DELETE : Delete
=========================================================================*/
enum DefectModifyMode
{
	FPD_DEFECT_ADD,
	FPD_DEFECT_DELETE,
};

/*=========================================================================
/*NAME				: DefectType
/*DESCRIPTION		: Defect point/line type
/*MEMBER			: 
/*FPD_POINT			: Defect point
/*FPD_LINE			: Defect line
/*FPD_DATASCAN_LINE: DataScandefect line
=========================================================================*/
enum DefectType
{
	FPD_POINT,
	FPD_LINE,
	FPD_DATASCAN_LINE,
};

/*=========================================================================
/*NAME		    : InitializeInfo
/*DESCRIPTION   : Initialize information of the detector
/*MEMBER	    	: 
/*strFullPathConfigFile	: Full path of the config.ini file
/*strCorrectPath		: The path of correct file
/*bSetLogInfo			: To set create log file
/*strLogPath			: The log file path
/*connMode				: The detector connection mode structure members
/*bConnSyncBox			: To set connection sync controlbox (No use)
/*bIsDoubleDetector		: To set connection double detector
/*strIP1				: A detector IP address (Use of network)
/*strIP2				: B detector IP address (Use of network)
/*nPort1				: A detector port
/*nPort2				: B detector port
/*strCom1				: A detector COM name (Use of COM)
/*strCom2				: B detector COM name (Use of COM)
/*strDetectorSN1		: A detector SN
/*strDetectorSN2		: B detector SN
/*nReserved1			: Reserved 1
/*nReserved2			: Reserved 2
=========================================================================*/
#pragma pack(push, 1)
struct InitializeInfo 
{
	char strFullPathConfigFile[PATHLENGTH];
	char strCorrectPath[PATHLENGTH];
	bool bSetLogInfo;
	char strLogPath[PATHLENGTH];
	char strDllPath[PATHLENGTH];
	ConnectionMode connMode;
	bool bIsDoubleDetector;
	char strIP1[CHARLEN];
	char strIP2[CHARLEN];
	int nPort1;
	int nPort2;
	char strCom1[CHARLEN];
	char strCom2[CHARLEN];
	char strDetectorSN1[CHARLEN];
	char strDetectorSN2[CHARLEN];
	char strUserId[CHARLEN];
	char strPasswordId[CHARLEN];
	int nMultCorrFolder;
	int nReserved1;
	int nReserved2;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		    : IdInfo
/*DESCRIPTION   : The return information of detector
/*MEMBER	    : 
/*hID			: Detector ID
/*detectorMode	: The detector mode structure members
/*bIsSync		: The return information of connection sync controlbox
/*nReserved1	: Reserved 1
/*nReserved2	: Reserved 2
=========================================================================*/
#pragma pack(push, 1)
struct IdInfo
{
	HANDLE hID[2];
	DetectorMode detectorMode;
	bool bIsSync;
	int nReserved1;
	int nReserved2;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		    : NetInfo
/*DESCRIPTION   : Network Information
/*MEMBER	    : 
/*Speed			: Network speed
/*ConnStatus	: Network connection status
/*nReserved1	: Reserved 1
/*nReserved2	: Reserved 2
=========================================================================*/
#pragma pack(push, 1)
struct NetInfo 
{
	int Speed;
	int ConnStatus;
	int nReserved1;
	int nReserved2;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		   : TemperatureInfo
/*DESCRIPTION  : Sensor temperature information of the detector
/*MEMBER	   : 
/*TempLT	   : left top sensor temperature
/*TempRT	   : Right top sensor temperature
/*TempLB	   : Left bottom sensor temperature
/*TempRB	   : Right bottom sensor temperature
/*TempM		   : Middle sensor temperature
=========================================================================*/
#pragma pack(push, 1)
struct TemperatureInfo
{
	char TempLT[CHARLEN];
	char TempRT[CHARLEN];
	char TempLB[CHARLEN];
	char TempRB[CHARLEN];
	char TempM[CHARLEN];
};
#pragma pack(pop)

/*=========================================================================
/*NAME		   : HumidityInfo
/*DESCRIPTION  : Sensor humidity information of the detector
/*MEMBER	   : 
/*Humidity1	   : Sensor 1 humidity
/*Humidity2	   : Sensor 2 humidity
/*Humidity3	   : Sensor 3 humidity
/*Humidity4	   : Sensor 4 humidity
/*Humidity5	   : Sensor 5 humidity
=========================================================================*/
#pragma pack(push, 1)
struct HumidityInfo
{
	float Humidity1;
	float Humidity2;
	float Humidity3;
	float Humidity4;
	float Humidity5;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		    : DetectorInfo
/*DESCRIPTION   : The detector information, the information read-only
/*MEMBER	    : 
/*ImageWidth	: Image width
/*ImageHeight	: Image heigth
/*ProductNo		: Detector product number
/*SerialNumber	: Detector serial number
/*DllVersion	: Acquire library dll version
/*MainVersion	: firmware version 1
/*ReadVersion	: firmware version 2
/*InnerDelayTime: Inner delay time, Unit: ms
/*tempInfo		: Temperature structure members
/*humiInfo		: Humidity structure members
/*nReserved1	: Reserved 1
/*nReserved2	: Reserved 2
/*nReserved3	: Reserved 3
/*nReserved4	: Reserved 4
/*nReserved5	: Reserved 5
=========================================================================*/
#pragma pack(push, 1)
struct DetectInfo
{
	int ImageWidth;
	int ImageHeight;
	int ProductNo;
	char SerialNumber[CHARLEN];
	char DllVersion[CHARLEN];
	char MainVersion[CHARLEN];
	char ReadVersion[CHARLEN];
	int InnerDelayTime;
	TemperatureInfo tempInfo;
	HumidityInfo humiInfo;
	int nReserved1;
	int nReserved2;
	int nReserved3;
	int nReserved4;
	int nReserved5;
};
#pragma pack(pop)

/*=========================================================================
/*NAME			: DynamicInfo
/*DESCRIPTION	: The dynamic detector information
/*MEMBER			: 
/*DynamicType		: Dynamic mode: 0: static; 1: dynamic
/*Binning			: Detector binning mode
/*FluroSync			: Fluro mode: 0:free run; 1: out; 2: inner
/*AfeMode			: AFE saving Mode: 0: High-power; 1: Low-power
/*AfeConfig			: AFE configuration parameters
/*SyncExpDelayTime	: The exposure trigger delay time: Unit: us
/*SyncExpTime		: Sync exposure time: Unit: us
/*InnerSyncValid	: Dynamic Inner Sync Valid Level		
/*OuterSyncValid	: Dynamic Outer Sync Valid Level

=========================================================================*/
#pragma pack(push, 1)
struct DynamicInfo 
{
	int DynamicType;
	int Binning;
	int FluroSync;
	int AfeMode;
	int AfeConfig;
	int SyncExpDelayTime;
	int SyncExpTime;
	int InnerSyncValid;
	int OuterSyncValid;
	int ContinuCapFrameNum;
	int ZoomSelect;
	int BinningW;
	int BinningH;
	int ZoomW;
	int ZoomH;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		    : DetectorNetInfo
/*DESCRIPTION   : Detecotr network informaiton
/*MEMBER	    : 
/*SrcMAC		: Detector MAC address
/*DestMAC		: Computer MAC address
/*SrcIP			: Detector IP address
/*DestIP		: Computer IP address
/*SrcPort		: Detector Port address
/*DestPort		: Computer Port address
/*nReserved1	: Reserved 1
/*nReserved2	: Reserved 2
=========================================================================*/
#pragma pack(push, 1)
struct DetectorNetInfo 
{
	char SrcMAC[CHARLEN];
	char DestMAC[CHARLEN];
	char SrcIP[CHARLEN];
	char DestIP[CHARLEN];
	int SrcPort;
	int DestPort;
	int nReserved1;
	int nReserved2;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		    : WirelessInfo
/*DESCRIPTION   : Wireless detector configuration information
/*MEMBER	    : 
/*PreMode		: Image preview Mode: 0: Full image; 1: Preview image and Full image
/*PreSampling	: Preview image mode control: 0: 2x2; 1: 4x4:
/*OffsetType	: Offset Mode: 0: Post offset; 1: Pre offset; 2: No offset correct
/*ImgChannel	: Image Channel: 0: UDP; 1: TCP/IP;
/*nReserved1	: Reserved 1
/*nReserved2	: Reserved 2
/*nReserved3	: Reserved 3
/*nReserved4	: Reserved 4
/*nReserved5	: Reserved 5
=========================================================================*/
#pragma pack(push, 1)
struct WirelessInfo 
{
	int PreMode;
	int PreSampling;
	int OffsetType;
	int ImgChannel;
	int nReserved1;
	int nReserved2;
	int nReserved3;
	int nReserved4;
	int nReserved5;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		    : ControlboxInfo
/*DESCRIPTION   : Controlbox configuration informaiton
/*MEMBER	    	: 
/*Version		: Controlbox firmware version
/*SN			: Serial number
/*SrcMAC		: Controlbox MAC address
/*DestMAC		: Computer MAC address
/*SrcIP			: Controlbox IP address
/*DestIP		: Computer IP address
/*SrcPort		: Controlbox Port
/*DestPort		: Computer Port
/*HvgPrepOn		: Generator x_ray_prep signal valid level; 1: high level 0: low level
/*HvgXRayEnable : Generator x_ray_ensignal valid level; 1: high level 0: low level
/*HvgXRayOn		: Generator x_ray_on signal valid level; 1: high level 0: low level
/*HvgXRaySyncOut: Generator fluoroscopy sync out signal valid level; 1: high level 0: low level
/*HvgXRaySyncIn : Generator fluoroscopy sync in signal valid level; 1: high level 0: low level
/*TriggerMode	: Trigger mode: 0:Outer; 1:Inner; 2:Software; 3: Prep
/*nReserved1	: Reserved 1
/*nReserved2	: Reserved 2
=========================================================================*/
#pragma pack(push, 1)
struct ControlboxInfo 
{
	char Version[CHARLEN];
	char SN[CHARLEN];
	int ProductNo;
	char SrcMAC[CHARLEN];
	char DestMAC[CHARLEN];
	char SrcIP[CHARLEN];
	char DestIP[CHARLEN];
	int SrcPort;
	int DestPort;
	int HvgPrepOn;
	int HvgXRayEnable;
	int HvgXRayOn;
	int HvgXRaySyncOut;
	int HvgXRaySyncIn;
	int TriggerMode;
	int nReserved1;
	int nReserved2;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		    : ConfigInfod
/*DESCRIPTION   : Detector configuration information
/*MEMBER	    	: 
/*SequenceIntervalTime	: Sequence acquire interval time (Unit: ms)
/*VT					: Voltage: Unit: ms, Range: 1.25~4.5
/*PGA					: VT, Value: 0, 1, 2, 3, 4, 5, 6, 7
/*DetectorYear			: Year
/*DetectorMonth			: Month
/*DetectorDay			: Day
/*TriggerMode			: Trigger mode, 0: Outer; 1: Inner; 2: Software; 3: PREP Mode
/*IntegrateTime			: IntegrateTime, Unit: ms
/*AcquireDelayTime		: Acquire delay time, Unit: ms
/*ClearTime				: Clear time, Unit: ms
/*SetDelayTime			: Set delay time, Unit: ms
/*ExpWindowTime			: Exposure window time, Unit: ms
/*AutoClearSpanTime		: Auto clear span time, Unit: ms
/*TftInteDelayTime		: TFT Integrate delay Time, Unit: ms
/*TubeReadyTime			: Tube ready time, Unit: ms
/*AutoClear				: Auto clear, 0: do not clear; 1: do clear
/*LevelSignal			: RAD Enable signal, 0: Low Valid; 1: High Valid
/*detectorInfo			: The detector informaiton structure members
/*netInfo				: The detector network informaiton structure members
/*dynamicInfo			: The ynamic detector informaiton structure members
/*wirelessInfo			: The wireless detector informaiton structure members
/*AecMainTime			: time gap between the ending of pre-exposure and the starting of main-exposure
/*ExpMode				: set the outer exposure mode for Mamo; 0: Manual; 1:AEC; 2:Normal
/*DynaOffsetGapTime		: time gap between two dynamic offset process
/*DynaOffsetMode		: to enable the function of capturing dynamic offset template:0:disable; 1:enable
=========================================================================*/
#pragma pack(push, 1)
struct ConfigInfo 
{
	int SequenceIntervalTime;
	float VT;
	int PGA;
	int DetectorYear;
	int DetectorMonth;
	int DetectorDay;
	int TriggerMode;
	int IntegrateTime;
	int AcquireDelayTime;
	int ClearTime;
	int SetDelayTime;
	int ExpWindowTime;
	int AutoClearSpanTime;
	int TftInteDelayTime;
	int TubeReadyTime;
	int AutoClear;
	int LevelSignal;
	int RowPreDelayTime;
	int RowPostDelayTime;
	DetectInfo detectorInfo;
	DetectorNetInfo netInfo;
	DynamicInfo dynamicInfo;
	WirelessInfo wirelessInfo;
	int AecMainTime;
	int ExpMode;
	int DynaOffsetGapTime;
	int DynaOffsetMode;
	int ImagePktGapTime;
	ControlboxInfo controlBoxInfo;
	int OuterTriggerSignal;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		    : SyncboxInfo
/*DESCRIPTION   : Sync controlbox configuration informaiton
/*MEMBER	    : 
/*Version		: Sync controlbox Version
/*SN			: Sync controlbox serial number
/*SyncReadyTime : Sync controlbox ready time, Unit: ms
/*nReserved1	: Reserved 1
/*nReserved2	: Reserved 2
/*nReserved3	: Reserved 3
/*nReserved4	: Reserved 4
/*nReserved5	: Reserved 5
=========================================================================*/
#pragma pack(push, 1)
struct SyncboxInfo 
{
	char Version[CHARLEN];
	char SN[CHARLEN];
	int SyncReadyTime;
	int nReserved1;
	int nReserved2;
	int nReserved3;
	int nReserved4;
	int nReserved5;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		    : DetectorLogInfo
/*DESCRIPTION   : Detailed log information of the detector
/*MEMBER	    : 
/*Cmd			: Command word
/*Year			: Year
/*Month			: Month
/*day			: Day
/*week			: Week
/*Hour			: Hour
/*Minute		: Minute
/*Second		: Second
/*nReserved1	: Reserved 1
/*nReserved2	: Reserved 2
=========================================================================*/
#pragma pack(push, 1)
struct DetectorLogInfo
{
	char Cmd[CHARLEN];
	int Year;
	int Month;
	int day;
	int week;
	int Hour;
	int Minute;
	int Second;
	int nReserved1;
	int nReserved2;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		    : DetectorLog
/*DESCRIPTION   : Detector log information
/*MEMBER	    : 
/*Number		: Number of logs
/*logInfo		: Detector log detailed information structure members
=========================================================================*/
#pragma pack(push, 1)
struct DetectorLog 
{
	int Number;
	DetectorLogInfo logInfo;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		    : ExposureInfo
/*DESCRIPTION   : Detector exposure information
/*MEMBER	    : 
/*ExpTimes		: The total number of exposures of the detector
/*UseTime		: The total use time of the detector unit: ms
/*TotalDose		: The total dose of the detector
/*nReserved1	: Reserved 1
/*nReserved2	: Reserved 2
/*nReserved3	: Reserved 3
/*nReserved4	: Reserved 4
/*nReserved5	: Reserved 5
=========================================================================*/
#pragma pack(push, 1)
struct ExposureInfo 
{
	int ExpTimes;
	int UseTime;
	int TotalDose;
	int nReserved1;
	int nReserved2;
	int nReserved3;
	int nReserved4;
	int nReserved5;
};
#pragma pack(pop)

/*=========================================================================
/*NAME		    : WiFiStatusInfo
/*DESCRIPTION   : Detector WiFi (client mode) work status information
/*MEMBER	    : 
/*ESSID			: The active SSID of current AP 
/*Frequency		: The active WiFi channel of AP, unit: GHz
/*SignalLevel	: The signal level of AP, unit:dBm
/*LinkQuality	: The link quality, range: 0(no signal) ~ 5(very good)
/*TxPower		: Current channel power, unit: dBm
/*nReserved1	: Reserved 1
/*nReserved2	: Reserved 2
=========================================================================*/
#pragma pack(push, 1)
struct WiFiStatusInfo
{
	char ESSID[CHARLEN];
	int Frequency;
	int SignalLevel;
	int LinkQuality;
	int TxPower;	
	int nReserved1;
	int nReserved2;
};
#pragma pack(pop)

#endif