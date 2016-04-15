// iRayDetectorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "iRayDetector.h"
#include "iRayDetectorDlg.h"

// 用于判断保存路径和创建保存路径 [4/14/2016 lipengsong]
#include <IMAGEHLP.H>
#pragma comment(lib,"imagehlp.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

//全局变量 [4/12/2016]
CString g_sAppPath;
CString g_sAppCfgPath;

int CALLBACK DRInfoCallback(HANDLE hID, int iMsg, WORD *pData, int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, float fValue1, float fValue2, void *pVoid)
{
	
	CIRayDetectorDlg* pFrame=(CIRayDetectorDlg*)AfxGetApp();

	CString strInfo;

	if(iMsg == FPD_EXP_PROHIBIT)
	{
		strInfo = _T("Exposure prohibit");
	}
	else if(iMsg == FPD_EXP_ENABLE)
	{
		strInfo = _T("Exposure enable");
	}
	else if(iMsg == FPD_EXP_TIMEOUT)
	{
		strInfo = _T("Exposure timeout");
		
		int nExpMode = 0;
		FPD_GetExposureMode(pFrame->m_hGigeAdapter, nExpMode);
		if(nExpMode != 0)
		{
			FPD_SetExposureMode(pFrame->m_hGigeAdapter, nExpMode);
		}
	}
	else if(iMsg == FPD_IMAGE_TIME)
	{
		strInfo.Format(_T("Image getting ...(delay time:%d)"), iValue1);
	}
	else if(iMsg == FPD_EXP_PROHIBIT_AUTO)
	{
		strInfo = _T("Exposure prohibit(Auto Clearing)");
	}
	else if(iMsg == FPD_EXP_ENABLE_AUTO)
	{
		strInfo = _T("Exposure enable");
	}
	else if(iMsg == FPD_EXP_PROHIBIT_POST)
	{
		strInfo = _T("Exposure prohibit (post offset)");
	}
	else if(iMsg == FPD_EXP_ENABLE_POST)
	{
		strInfo = _T("Exposure enable (post offset)");
	}
	else if(iMsg == FPD_IMAGE)
	{
		strInfo = _T("got image");
		// 得到正式图像 [4/14/2016 lipengsong]
		CString  str_ImageFileName ="iRayMam.raw";
		CString  str_ImageFilePath =pFrame->m_initInfo.strCorrectPath +str_ImageFileName;
		
		int ImageSize =pFrame->m_configInfo.detectorInfo.ImageHeight * pFrame->m_configInfo.detectorInfo.ImageWidth * sizeof(WORD);
		WORD* ImageData = pData;
		
		DWORD nWriten;
		HANDLE hWriteFile;
		hWriteFile=CreateFileA(str_ImageFilePath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		BOOL result =WriteFile(hWriteFile,ImageData,ImageSize,&nWriten,NULL);
		if (!result)
		{
			strInfo ="Save Image Failed!";
		}
		else
		{
			pFrame->m_rRawImage.m_nWPos =pFrame->m_nWinPos;
			pFrame->m_rRawImage.m_nWWid =pFrame->m_nWinWidth;
			pFrame->m_rRawImage.LoadRawImage(str_ImageFilePath);
		}
		CloseHandle(hWriteFile);		

	}
	else if(iMsg == FPD_IMAGE_BINNING)
	{
		// 得到AEC预曝光图像 [4/14/2016 lipengsong]
		CString  str_AECFileName ="iRayMam_AEC.raw";
		CString  str_AECFilePath =pFrame->m_initInfo.strCorrectPath +str_AECFileName;

		int ImageSize =pFrame->m_configInfo.dynamicInfo.BinningH * pFrame->m_configInfo.dynamicInfo.BinningW*sizeof(WORD);
		WORD* ImageAECData = pData;

		DWORD nWriten;
		HANDLE hWriteFile;
		hWriteFile=CreateFileA(str_AECFilePath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		BOOL result =WriteFile(hWriteFile,ImageAECData,ImageSize,&nWriten,NULL);
		if (!result)
		{
			strInfo ="Save AEC Image Failed!";
		}
		/*AEC图像尺寸特殊
		else
		{
			pFrame->m_rRawImage.LoadRawImage(str_AECFilePath);
		}
		*/
		CloseHandle(hWriteFile);		

	}
	else if(iMsg == FPD_IMAGE_PREV)
	{
		strInfo = _T("got prev image");
		// Mammo 探测器下用不到该反馈 [4/14/2016 lipengsong]
	}
	else if(iMsg == FPD_CONFIG_DETECTOR)
	{
		strInfo = _T("Get Configuration");
		FPD_GetDetectorConfiguration(hID, pFrame->m_configInfo);
	}
	else if(iMsg == FPD_GET_TEMPERATURE)
	{
		strInfo.Format(_T("Get Temperature: %f"), fValue1);
		FPD_GetDetectorConfiguration(hID, pFrame->m_configInfo);
		pFrame->m_strTemp =strInfo;
		pFrame->UpdateData(FALSE);
	}
	else if(iMsg == FPD_GET_HUMIDITY)
	{
		strInfo.Format(_T("Get Humidity: %f"), fValue1);
		FPD_GetDetectorConfiguration(hID, pFrame->m_configInfo);
	}
	else if(iMsg == FPD_SYNC_BOX_SEND_EXPOSURE)
	{
		strInfo = _T("Send exposure to sync-box");
	}
	else if(iMsg == FPD_SYNC_BOX_ENABLE)
	{
		strInfo = _T("Send enable to sync-box");
	}
	else if(iMsg == FPD_STATUS_READY)
	{
		//strInfo.Format(_T("Ready"));
		return 0;
	}
	else if(iMsg == FPD_STATUS_BUSY)
	{
		return 0;
	}
	else if(iMsg == FPD_STATUS_TIMEOUT)
	{
		return 0;
	}
	else if(iMsg == FPD_STATUS_ETHERNET_BREAK)
	{
		return 0;
	}
	else if(iMsg == FPD_IMAGE_LOST_PACKET)
	{
		strInfo.Format(_T("Lost packet, Send replenish CMD: %d)"), iValue1);
	}
	else if(iMsg == FPD_CORR_CREATE_OK)
	{
		strInfo = _T("Create correction ok");
	}
	else if(iMsg == FPD_CORR_CREATE_FAILED)
	{
		strInfo = _T("Create correction failed");
	}
	else if(iMsg == FPD_CORR_GET_OFFSET_IMAGE)
	{
		return 0;
	}
	else if(iMsg == FPD_CORR_THROW_OFFSET_IMAGE)
	{
		return 0;
	}
	else if(iMsg == FPD_CORR_DY_LIGHT_IMAGE)
	{
		return 0;
	}
	else if(iMsg == FPD_STATUS_CMD_TIMEOUT)
	{
		strInfo = _T("CMD timeout");
	}
	else if(iMsg == FPD_CHECK_NET_CONN_BREAK)
	{
		strInfo = _T("Network cable is disconnected");
	}
	else if(iMsg == FPD_CHECK_NET_CONN_OK_READY_FPD_NOT)
	{
		strInfo = _T("Network cable is connected, but FPD is not ready yet");
	}
	else if(iMsg == FPD_CHECK_NET_CONN_OK_READY_FPD_YES)
	{
		strInfo = _T("Network cable is connected and FPD is ready");
	}
	else if(iMsg == FPD_CHECK_NET_CONN_PLUG)
	{
		strInfo = _T("please plug in the net cable again!");
	}
	else if(iMsg == FPD_EVENT_LIGHT_CAL_FRAME_COMPLETE)
	{
		strInfo.Format(_T("Light calibration frame complete"));
	}
	else if(iMsg == FPD_IO_CMD_OK)
	{
		strInfo = _T("OK, FPD Received the Cmd Correctly.");
	}
	else if(iMsg == FPD_IO_CMD_ERROR)
	{
		strInfo = _T("FPD Received the Cmd Correctly,there is no such cmd in the cmd list.");
	}
	else if(iMsg == FPD_IO_CMD_MAIN_TIMEOUT)
	{
		strInfo = _T("Master Receive Cmd Error, Time Out.");
	}
	else if(iMsg == FPD_IO_CMD_MAIN_GET_CHK_ERROR)
	{
		strInfo = _T("Master Receive Cmd Error, Checksum Error.");
	}
	else if(iMsg == FPD_IO_CMD_MAIN_GET_LEN_ERROR)
	{
		strInfo = _T("Master Receive Cmd Error, Length Error.");
	}
	else if(iMsg == FPD_IO_CMD_SEQ_NO_IS_OUT_SYNC_ERROR)
	{
		strInfo = _T("SeqNo is out of sync.");
	}
	else if(iMsg == FPD_IO_CMD_FPD_BUSY_ERROR)
	{
		strInfo = _T("FPD busy.");
	}
	else if(iMsg == FPD_IO_CMD_READ_RESPONSE_ERROR)
	{
		strInfo = _T("No response from the Slave.");
	}
	else if(iMsg == FPD_IO_CMD_READ_TIMEOUT)
	{
		strInfo = _T("Master Receive The Cmd From Slave Error, Time Out.");
	}
	else if(iMsg == FPD_IO_CMD_READ_CHK_ERROR)
	{
		strInfo = _T("Master Receive The Cmd From Slave Error, Checksum Error.");
	}
	else if(iMsg == FPD_IO_CMD_READ_LEN_ERROR)
	{
		strInfo = _T("Master Receive The Cmd From Slave Error, Length Error.");
	}
	else if(iMsg == FPD_IO_CMD_MAIN_READ_TIMEOUT)
	{
		strInfo = _T("Slave Receive The Cmd From Master Error, Time Out.");
	}
	else if(iMsg == FPD_IO_CMD_MAIN_SEND_CHK_ERROR)
	{
		strInfo = _T("Slave Receive The Cmd From Master Error, Checksum Error.");
	}
	else if(iMsg == FPD_IMAGE_ROW_NUMBER_RETURN)
	{
		strInfo.Format(_T("Progress number: %d/%d"), iValue1, iValue2);
	}
	else if(iMsg == FPD_REPLENISH_IMAGE_ROW_NUMBER_RETURN)
	{
		strInfo.Format(_T("Replenish progress number: %d/%d (times:%d)"), iValue1, iValue2, iValue3);
	}
	else if(iMsg == FPD_READ_SHOCK_SENSOR_LOG)
	{
		strInfo.Format(_T("Read Shock Sensor Log"));
	}
	else if(iMsg == FPD_READ_GRID_SENSOR_STATUS)
	{
		if(iValue1 == 0)
		{
			strInfo.Format(_T("Grid Sensor1:[0]; Grid Sensor2:[0]"));
		}
		else if(iValue1 == 1)
		{
			strInfo.Format(_T("Grid Sensor1:[0]; Grid Sensor2:[1]"));
		}
		else if(iValue1 == 2)
		{
			strInfo.Format(_T("Grid Sensor1:[1]; Grid Sensor2:[0]"));
		}
		else if(iValue1 == 3)
		{
			strInfo.Format(_T("Grid Sensor1:[1]; Grid Sensor2:[1]"));
		}
	}
	else if(iMsg == FPD_CLEAR_SHOCK_SENSOR_LOG)
	{
		strInfo.Format(_T("Clear Shock Sensor Log"));
	}
	else if(iMsg == FPD_WRITE_SHOCK_USER_THRESHOLD)
	{
		strInfo.Format(_T("Write shock user threshold"));
	}
	else if(iMsg == FPD_READ_SHOCK_USER_THRESHOLD)
	{
		strInfo.Format(_T("Read shock user threshold: %d"), iValue1);
	}
	else if(iMsg == FPD_RESET_ROM_OK)
	{
		strInfo.Format(_T("Reset ROM is OK"));
	}
	else if(iMsg == FPD_RELOAD_FIRMWARE_OK)
	{
		strInfo.Format(_T("Reload firmware is OK"));
	}
	else if(iMsg == FPD_RECV_EXP_REQ_OK)
	{
		strInfo.Format(_T("Receive exposure request OK"));
	}
	else if(iMsg == FPD_EXP_INTERRUPT)
	{
		strInfo.Format(_T("Exposure Interrupted"));

		int nExpMode = 0;
		FPD_GetExposureMode(pFrame->m_hGigeAdapter, nExpMode);
		if(nExpMode != 0)
		{
			FPD_SetExposureMode(pFrame->m_hGigeAdapter, nExpMode);
		}
	}
	else if(iMsg == FPD_SLAVE_INIT_AFTER_POWER_ON_ERR)
	{
		strInfo.Format(_T("Slave initialization error after power on"));
	}
	else if(iMsg == FPD_DDR_BUFFER_ERROR)
	{
		strInfo.Format(_T("DDR buffer error, doesn't work"));
	}
	else if(iMsg == FPD_MASTER_RECV_CMD_TIMEOUT_FROM_CTLBOX_ERR)
	{
		strInfo.Format(_T("Master receives cmd from control box error, time out error"));
	}
	else if(iMsg == FPD_MASTER_RECV_CMD_LENGTH_FROM_CTLBOX_ERR)
	{
		strInfo.Format(_T("Master receives cmd from control box error, length error"));
	}
	else if(iMsg == FPD_MASTER_RECV_CMD_CHECKSUM_FROM_CTLBOX_ERR)
	{
		strInfo.Format(_T("Master receives cmd from control box error, checksum error"));
	}
	else if(iMsg == FPD_NO_RESPONSE_FROM_CTLBOX)
	{
		strInfo.Format(_T("No response from control box"));
	}
	else if(iMsg == FPD_CTLBOX_RECV_CMD_TIMEOUT_FROM_MASTER_ERR)
	{
		strInfo.Format(_T("Control box receives cmd from master error, time out error"));
	}
	else if(iMsg == FPD_CTLBOX_RECV_CMD_LENGTH_FROM_MASTER_ERR)
	{
		strInfo.Format(_T("Control box receives cmd from master error, length error"));
	}
	else if(iMsg == FPD_CTLBOX_RECV_CMD_CHECKSUM_FROM_MASTER_ERR)
	{
		strInfo.Format(_T("Control box receives cmd from master error, checksum error"));
	}
	else if(iMsg == FPD_CTLBOX_CMD_NOT_SUPPORT)
	{
		strInfo.Format(_T("The cmd is not supported by control box"));
	}
	else if(iMsg == FPD_PACK_NUMBER_OF_UPGRADE_FW_FILE_ERR)
	{
		strInfo.Format(_T("Packet number error of upgrade firmware file"));
	}
	else if(iMsg == FPD_NO_CONTROLLER_NEED_FW_UPGRADE)
	{
		strInfo.Format(_T("No such controller needs firmware upgrade"));
	}
	else if(iMsg == FPD_NO_RESPONSE_FROM_G_SENSOR_MCU)
	{
		strInfo.Format(_T("No response from G-Sensor MCU"));
	}
	else if(iMsg == FPD_MASTER_RECV_CMD_TIMEOUT_FROM_G_SENSOR_MCU_ERR)
	{
		strInfo.Format(_T("Master receives cmd from G-Sensor MCU error, timeout error"));
	}
	else if(iMsg == FPD_MASTER_RECV_CMD_CHECKSUM_FROM_G_SENSOR_MCU_ERR)
	{
		strInfo.Format(_T("Master receives cmd from G-Sensor MCU error, checksum error"));
	}
	else if(iMsg == FPD_MASTER_RECV_CMD_LENGTH_FROM_G_SENSOR_MCU_ERR)
	{
		strInfo.Format(_T("Master receives cmd from G-Sensor MCU error, length error"));
	}
	else if(iMsg == FPD_G_SENSOR_MCU_RECV_CMD_TIMEOUT_FROM_MASTER_ERR)
	{
		strInfo.Format(_T("G-Sensor MCU receives cmd from master error, timeout error"));
	}
	else if(iMsg == FPD_G_SENSOR_MCU_RECV_CMD_CHECKSUM_FROM_MASTER_ERR)
	{
		strInfo.Format(_T("G-Sensor MCU receives cmd from master error, checksum error"));
	}
	else if(iMsg == FPD_G_SENSOR_MCU_RECV_CMD_LENGTH_FROM_MASTER_ERR)
	{
		strInfo.Format(_T("G-Sensor MCU receives cmd from master error, length error"));
	}
	else if(iMsg == FPD_CMD_EXECUTE_TIMEOUT_ERR)
	{
		strInfo.Format(_T("Cmd Execute Timeout error"));
	}
	else if(iMsg == FPD_CMD_EXECUTE_TIMEOUT_ERR)
	{
		strInfo.Format(_T("Cmd Execute Timeout error"));
	}
	else if(iMsg == FPD_WRITE_CONFIG_DETECTOR)
	{
		strInfo.Format(_T("Write Configuration"));
	}
	else if(iMsg == FPD_DISK_FREE_SPACE_INVALID)
	{
		strInfo.Format(_T("Disk available space is lower than 500M."));
	}
	else if(iMsg == FPD_CLOSE_EXP_WINDOW)
	{
		strInfo.Format(_T("Close exp window ok"));
	}
	else if(iMsg == FPD_CLOSE_EXP_WINDOW_FAIL)
	{
		strInfo.Format(_T("Close exp window failed"));
	}

	// 更新探测器状态信息 [4/14/2016 lipengsong]
	pFrame->m_strWorkState =strInfo;
	pFrame->UpdateData(FALSE);

	return 0;
}



class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIRayDetectorDlg dialog
CIRayDetectorDlg::CIRayDetectorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIRayDetectorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIRayDetectorDlg)
	m_strWorkState = _T("");
	m_strTemp = _T("");
	m_RadioExpMode = -1;
	m_RadioTriggerMode = -1;
	m_hGigeAdapter =NULL;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIRayDetectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIRayDetectorDlg)
	DDX_Control(pDX, IDC_STATIC_Image, m_rRawImage);
	DDX_Text(pDX, IDC_STATIC_WorkState, m_strWorkState);
	DDX_Text(pDX, IDC_STATIC_Temp, m_strTemp);
	DDX_Radio(pDX, IDC_RADIO_Manual, m_RadioExpMode);
	DDX_Radio(pDX, IDC_RADIO_Outer, m_RadioTriggerMode);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIRayDetectorDlg, CDialog)
	//{{AFX_MSG_MAP(CIRayDetectorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BtnConnect, OnBtnConnect)
	ON_BN_CLICKED(IDC_RADIO_Manual, OnRADIOManual)
	ON_BN_CLICKED(IDC_RADIO_AEC, OnRadioAec)
	ON_BN_CLICKED(IDC_RADIO_Outer, OnRADIOOuter)
	ON_BN_CLICKED(IDC_RADIO_Inner, OnRADIOInner)
	ON_BN_CLICKED(IDC_RADIO_Soft, OnRADIOSoft)
	ON_BN_CLICKED(IDC_RADIO_Prep, OnRADIOPrep)
	ON_BN_CLICKED(IDC_BUTTON1, OnBtnSaveScreen)
	ON_BN_CLICKED(IDC_BtnClose, OnBtnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIRayDetectorDlg message handlers

BOOL CIRayDetectorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	TCHAR szFilePath[MAX_PATH + 1]={0};
    GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; // 删除文件名，只获得路径字串
	g_sAppPath = szFilePath;  
	g_sAppCfgPath =szFilePath ;
	g_sAppCfgPath +=_T("iRayConfig.ini");


	// 配置文件中的AEC预曝光图像合并模式打开  [4/14/2016 lipengsong]
	CString strFullPathConfigFile= g_sAppPath + "res\\config.ini";
	WritePrivateProfileString("CONFIG","AEC_PREV_BINNING_MODE","1",strFullPathConfigFile);

	// 读取预设窗宽窗位 [4/14/2016 lipengsong]
	m_nWinWidth = GetPrivateProfileInt("Image","Show_WindowWidth",5000,g_sAppCfgPath);
	m_nWinPos   = GetPrivateProfileInt("Image","Show_WindowPos",7000,g_sAppCfgPath);

	m_rRawImage.Init();

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIRayDetectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIRayDetectorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIRayDetectorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


/*探测器连接和初始化*/
void CIRayDetectorDlg::OnBtnConnect() 
{
	// TODO: Add your control notification handler code here
	CString m_str_IP,m_str_SN;
	int     m_n_Port,m_nCorrFodlerNum;
	
	
	m_idInfo.hID[0] = NULL;
	CString strFullPathConfigFile= g_sAppPath + "res\\config.ini";
	CString strCorrectPath=g_sAppPath+"res\\";
	CString strDllPath=g_sAppPath;
	m_initInfo.bIsDoubleDetector =false;
	m_initInfo.bSetLogInfo = true;
	sprintf(m_initInfo.strFullPathConfigFile, "%s", strFullPathConfigFile);
	sprintf(m_initInfo.strCorrectPath, "%s", strCorrectPath);
	sprintf(m_initInfo.strLogPath, "%s", strCorrectPath);
	sprintf(m_initInfo.strDllPath, "%s", strDllPath);
	
	
	//从探测器配置中读取 [4/12/2016 lipengsong]
	//Get IP
	GetPrivateProfileString("CONFIG","SOURCE_IP_1","192.168.8.188",m_str_IP.GetBuffer(MAX_PATH),MAX_PATH,strFullPathConfigFile);
	m_str_IP.ReleaseBuffer();
	
	//Get Port
	m_n_Port =GetPrivateProfileInt("CONFIG","SOURCE_PORT_1",28000,strFullPathConfigFile);
	
	//Get SN 
	GetPrivateProfileString("CONFIG","DETECTOR_SN_1","",m_str_SN.GetBuffer(MAX_PATH),MAX_PATH,strFullPathConfigFile);
	m_str_SN.ReleaseBuffer();
	
	//Get CorrectFodlerNumber,校正文件目录
	m_nCorrFodlerNum =GetPrivateProfileInt("iRay_Connect","MultCorrFolder",0,g_sAppCfgPath);
	
	sprintf(m_initInfo.strIP1,"%s", m_str_IP);
	m_initInfo.nPort1 = m_n_Port;
	m_initInfo.connMode = FPD_NET_CONN;
	m_initInfo.nMultCorrFolder =m_nCorrFodlerNum ;
	sprintf(m_initInfo.strDetectorSN1, "%s", m_str_SN);
	
	//未启用双探测器  [4/12/2016]
	sprintf(m_initInfo.strIP2, "");
	m_initInfo.nPort2 = 0;
	sprintf(m_initInfo.strDetectorSN2, "");
	
	int iResult = FPD_Initialize(m_initInfo, m_idInfo, DRInfoCallback);
	if(iResult == FPD_NO_ERR)
	{
		m_hGigeAdapter = m_idInfo.hID[0];
		FPD_GetDetectorConfiguration(m_hGigeAdapter, m_configInfo);
		
		//探测器模式-动态/静态
		m_detectorMode = m_idInfo.detectorMode;
		
		//曝光模式
		int m_nExpMode =m_configInfo.ExpMode;
		m_RadioExpMode =m_nExpMode-1;

		//触发模式
		int m_nTriggerMode = m_configInfo.TriggerMode;
		m_RadioExpMode =m_nTriggerMode;

		m_strWorkState ="Connect Success!";
		
		UpdateData(FALSE);
	}
	else if(iResult == FPD_A_DETECTOR_CONN_ERR || iResult == FPD_B_DETECTOR_CONN_ERR)
	{
		char strMessage[256] = {0};
		sprintf(strMessage,"Connect double detectors information: ErrCode[%d]: %s", iResult, g_strErrList[iResult]);
		::AfxMessageBox(strMessage, NULL, MB_ICONINFORMATION);
	}
	else
	{
		char strMessage[256] = {0};
		sprintf(strMessage,"Connect detector error! ErrCode[%d]: %s", iResult, g_strErrList[iResult]);
		::AfxMessageBox(strMessage, NULL, MB_ICONERROR);
	}
}


void CIRayDetectorDlg::OnRADIOManual() 
{
	// TODO: Add your control notification handler code here
	ASSERT(m_hGigeAdapter !=NULL);

	int ExpMode_Manual =1;
	int result =FPD_SetExposureMode(m_hGigeAdapter,ExpMode_Manual);
	if (result != FPD_NO_ERR)
	{
		::AfxMessageBox("Set ExpMode Failed!");
	}
}

void CIRayDetectorDlg::OnRadioAec() 
{
	// TODO: Add your control notification handler code here
	ASSERT(m_hGigeAdapter !=NULL);

	int ExpMode_AEC =2;
	int result =FPD_SetExposureMode(m_hGigeAdapter,ExpMode_AEC);
	if (result != FPD_NO_ERR)
	{
		::AfxMessageBox("Set ExpMode Failed!");
	}
}

void CIRayDetectorDlg::OnRADIOOuter() 
{
	// TODO: Add your control notification handler code here
	int TriggerMode_Outer =0;
	iRaySetTriggerMode(TriggerMode_Outer);
}

void CIRayDetectorDlg::OnRADIOInner() 
{
	// TODO: Add your control notification handler code here
	int TriggerMode_Inner =1;
	iRaySetTriggerMode(TriggerMode_Inner);
}

void CIRayDetectorDlg::OnRADIOSoft() 
{
	// TODO: Add your control notification handler code here
	int TriggerMode_Soft =2;
	iRaySetTriggerMode(TriggerMode_Soft);
}

void CIRayDetectorDlg::OnRADIOPrep() 
{
	// TODO: Add your control notification handler code here
	int TriggerMode_Prep =3;
	iRaySetTriggerMode(TriggerMode_Prep);
}

void CIRayDetectorDlg::iRaySetTriggerMode(int m_nTriggerMode)
{
	ASSERT(m_hGigeAdapter !=NULL);

	int result = FPD_GetDetectorConfiguration(m_hGigeAdapter, m_configInfo);
	if (result != FPD_NO_ERR)
	{
		::AfxMessageBox("Get Detector ConfigInfo Failed!");
		return;
	}

	m_configInfo.TriggerMode =m_nTriggerMode;

	result =FPD_WriteConfiguration(m_hGigeAdapter,FPD_CONFIG_ROM,m_configInfo);
	if(result !=FPD_NO_ERR)
	{
		::AfxMessageBox("Write TriggerMode Failed!");
		return;
	}

}

void CIRayDetectorDlg::OnBtnSaveScreen() 
{
	// TODO: Add your control notification handler code here
	CDC *pdeskdc = GetDesktopWindow()->GetDC();    
    CRect re;  
    //获取窗口的大小  
    GetDesktopWindow()->GetClientRect(&re);  
    CBitmap bmp;  
    bmp.CreateCompatibleBitmap(pdeskdc , re.Width() , re.Height());  
    //创建一个兼容的内存画板  
    CDC memorydc;  
    memorydc.CreateCompatibleDC(pdeskdc);  
	
    //选中画笔  
    CBitmap *pold = memorydc.SelectObject(&bmp);  
	
    //绘制图像  
    memorydc.BitBlt(0,0,re.Width() ,re.Height(), pdeskdc , 0 ,0 ,SRCCOPY) ;  
	
    //获取鼠标位置，然后添加鼠标图像  
    CPoint po;  
    GetCursorPos(&po);  
    HICON hinco = (HICON)GetCursor();  
    memorydc.DrawIcon(po.x-10 , po.y - 10 , hinco);  
    //选中原来的画笔  
    memorydc.SelectObject(pold);  
    BITMAP bit;  
    bmp.GetBitmap(&bit);  
	//  DWORD size = bit.bmWidth * bit.bmHeight ;  
	
    //定义 图像大小（单位：byte）  
    DWORD size = bit.bmWidthBytes * bit.bmHeight ;  
    LPSTR lpdata = (LPSTR)GlobalAlloc(GPTR , size) ;  
	
    //后面是创建一个bmp文件的必须文件头，想要了解可以参考msdn  
	
    BITMAPINFOHEADER pbitinfo;  
    pbitinfo.biBitCount = 24 ;   
    pbitinfo.biClrImportant = 0;  
    pbitinfo.biCompression = BI_RGB ;  
    pbitinfo.biHeight = bit.bmHeight ;   
    pbitinfo.biPlanes = 1 ;  
    pbitinfo.biSize = sizeof(BITMAPINFOHEADER);  
    pbitinfo.biSizeImage =size;  
    pbitinfo.biWidth = bit.bmWidth;  
    pbitinfo.biXPelsPerMeter = 0;  
    pbitinfo.biYPelsPerMeter = 0 ;  
	
    GetDIBits(pdeskdc->m_hDC , bmp , 0 , pbitinfo.biHeight , lpdata ,   
        (BITMAPINFO*)&pbitinfo,DIB_RGB_COLORS);  
	
    BITMAPFILEHEADER bfh;  
    bfh.bfReserved1 = bfh.bfReserved2 = 0 ;  
    bfh.bfType = ((WORD)('M'<< 8)|'B');  
    bfh.bfSize = 54 + size ;   
    bfh.bfOffBits = 54 ;  
	
    //写入文件  
	
    CFile file; 
	MakeSureDirectoryPathExists("C:\\Console\\Screen\\");
    if ( file.Open("C:\\Console\\Screen\\ceshi.bmp" , CFile::modeCreate|CFile::modeWrite) )  
    {  
        file.WriteHuge( &bfh , sizeof(BITMAPFILEHEADER) );  
        file.WriteHuge(&pbitinfo , sizeof(BITMAPINFOHEADER));  
        file.WriteHuge(lpdata , size);  
        file.Close();  
    }  
    GlobalFree(lpdata);	

}

void CIRayDetectorDlg::OnBtnClose() 
{
	// TODO: Add your control notification handler code here
	int result = FPD_Close(m_idInfo);
	if (result ==FPD_NO_ERR)
	{
		::AfxMessageBox("Close Connect Success.");
	}
	else
	{
		::AfxMessageBox("Close Failed!");
	}
}
