#if !defined(AFX_SETUPDIALOG_H__9829F9AA_71F0_452E_A8BC_EE909A09F8F0__INCLUDED_)
#define AFX_SETUPDIALOG_H__9829F9AA_71F0_452E_A8BC_EE909A09F8F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupDialog.h : header file
//
#include "CommThread.h"
/////////////////////////////////////////////////////////////////////////////
// CSPortTestDlg dialog

#define  MAX_STR  MAX_PATH //10 //전송할수있는 최대 문자갯수

class CSetupDialog : public CDialog
{
// Construction
public:
	CSetupDialog(CWnd* pParent = NULL);   // standard constructor

	int			m_BaudRate;
	BOOL	bCheck;	

// Dialog Data
	//{{AFX_DATA(CSetupDialog)
	enum { IDD = IDD_SETUP_DIALOG };
	CButton	m_ctlCheckHexa;
	CButton	m_rCheckRadio;
	CEdit	m_ctlEdt_SendHis;
	CEdit	m_ctlEdt_RcvData;
	CEdit	m_ctlEdt_SendData;	
	CComboBox	m_ctlCob_Stop;
	CComboBox	m_ctlCob_Pty;
	CComboBox	m_ctlCob_Port;
	CComboBox	m_ctlCob_Data;
	CComboBox	m_ctlCob_Baud;
	CComboBox	m_ctlCob_Command;
	CString	m_strEdt_RvcData;
	CString	m_strEdt_SendData;
	CString	m_strCbo_Port;
	CString	m_strCbo_Baud;
	CString	m_strEdt_SendHis;
	CString	m_strCob_Command;
	BOOL	m_CheckHexa;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSPortTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSending();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnBtnConnect();
	afx_msg void OnBtnExit();
	afx_msg void OnReadRadio();
	afx_msg void OnWriteRadio();
	//}}AFX_MSG
	//afx_msg void OnRcvMessage(WPARAM wParam, LPARAM lParam); 
	afx_msg LONG OnRcvData(UINT,LONG);
	CString strRcvData2Char(int nRcvSize );
	CString strRcvData2Hexa(int nRcvSize );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPDIALOG_H__9829F9AA_71F0_452E_A8BC_EE909A09F8F0__INCLUDED_)
