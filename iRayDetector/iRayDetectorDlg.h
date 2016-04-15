// iRayDetectorDlg.h : header file
//

#if !defined(AFX_IRAYDETECTORDLG_H__16DA368F_A975_48F6_A0DB_CF9E0F65E61C__INCLUDED_)
#define AFX_IRAYDETECTORDLG_H__16DA368F_A975_48F6_A0DB_CF9E0F65E61C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// include acquire lib .h file
#include "include\FpdErrors.h"
#include "include\FpdStatus.h"
#include "include\FpdStructs.h"
#include "include\FpdStructsEx.h"
#include "include\FpdFuncs.h"

#pragma comment(lib,"FpdLib.lib")

#include "iRayDetector.h"

#include "RawDib.h"



/////////////////////////////////////////////////////////////////////////////
// CIRayDetectorDlg dialog

class CIRayDetectorDlg : public CDialog
{
// Construction
public:
	void iRaySetTriggerMode(int m_nTriggerMode);
	CIRayDetectorDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CIRayDetectorDlg)
	enum { IDD = IDD_IRAYDETECTOR_DIALOG };
	CRawDib	m_rRawImage;
	CString	m_strWorkState;
	CString	m_strTemp;
	int		m_RadioExpMode;
	int		m_RadioTriggerMode;
	//}}AFX_DATA

	//ÞÈÈðÌ½²âÆ÷Ìí¼Ó
	InitializeInfo m_initInfo;
	IdInfo m_idInfo;
	HANDLE m_hGigeAdapter;      //ÍøÂçÊÊÅäÆ÷¾ä±ú
	ConfigInfo m_configInfo;
	SyncboxInfo m_syncInfo;
	DetectorMode m_detectorMode;
	int m_nWinPos;
	int m_nWinWidth;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIRayDetectorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIRayDetectorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnConnect();
	afx_msg void OnRADIOManual();
	afx_msg void OnRadioAec();
	afx_msg void OnRADIOOuter();
	afx_msg void OnRADIOInner();
	afx_msg void OnRADIOSoft();
	afx_msg void OnRADIOPrep();
	afx_msg void OnBtnSaveScreen();
	afx_msg void OnBtnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IRAYDETECTORDLG_H__16DA368F_A975_48F6_A0DB_CF9E0F65E61C__INCLUDED_)
