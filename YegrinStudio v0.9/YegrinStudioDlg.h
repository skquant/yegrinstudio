// YegrinStudioDlg.h : header file
//

#if !defined(AFX_YEGINSTUDIODLG_H__E2A1C6EA_048E_4C70_B90E_04E0159AD77B__INCLUDED_)
#define AFX_YEGINSTUDIODLG_H__E2A1C6EA_048E_4C70_B90E_04E0159AD77B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CYegrinStudioDlg dialog
#include "ImageDialog.h"
#include "XTabCtrl.h"
#include "UpperAddinDialog.h"
#include "FlashAddinDialog.h"
#include "AuxiliairyAddinDialog.h"
#include "InformationAddinDialog.h"
#include "MemoryAddinDialog.h"
#include "GroupSyncAddinDialog.h"
#include "CommThread.h"
#include "SetupDialog.h"
#include "CommThread.h"

class CYegrinStudioDlg : public CImageDialog
{
// Construction
public:
	CYegrinStudioDlg(CWnd* pParent = NULL);	// standard constructor	
// Dialog Data
	//{{AFX_DATA(CYegrinStudioDlg)
	enum { IDD = IDD_YEGRINSTUDIO_DIALOG };
	CEdit	m_RcvTest;
	CXTabCtrl	m_UppperTabCtrl;
	CXTabCtrl	m_LowerTabCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYegrinStudioDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	int			m_BaudRate;
	BOOL	bCheck;	
	CSetupDialog	m_SetupDialog;

// Implementation
protected:
	HICON				m_hIcon;
	CImageList			m_UpperImageTab, m_LowerImageTab;
	CUpperAddinDialog*	m_pUpperAddinDialog[5];
	CFlashAddinDialog*  m_pLowerFlashAddinDialog;
	CAuxiliairyAddinDialog*		m_pLowerAuxiliairyAddinDialog;
	CInformationAddinDialog*	m_pLowerInformationAddinDialog;
	CMemoryAddinDialog*			m_pLowerMemoryAddinDialog;
	CGroupSyncAddinDialog*		m_pLowerGroupSyncAddinDialog;
	// Generated message map functions
	//{{AFX_MSG(CYegrinStudioDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMenuitemSettup();
	afx_msg void OnUpdateMenuitemSettup(CCmdUI* pCmdUI);
	afx_msg void OnMenuitemConnect();
	afx_msg void OnUpdateMenuitemConnect(CCmdUI* pCmdUI);
	afx_msg void OnButtonTest();
	//}}AFX_MSG
	afx_msg LONG OnRxData(UINT,LONG);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YEGINSTUDIODLG_H__E2A1C6EA_048E_4C70_B90E_04E0159AD77B__INCLUDED_)
