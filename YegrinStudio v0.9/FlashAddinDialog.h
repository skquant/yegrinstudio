#if !defined(AFX_FLASHADDINDIALOG_H__69FA8BA7_68A3_41AC_BC16_671285E70228__INCLUDED_)
#define AFX_FLASHADDINDIALOG_H__69FA8BA7_68A3_41AC_BC16_671285E70228__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlashAddinDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlashAddinDialog dialog
class CXTabCtrl;
class CFlashAddinDialog : public CDialog
{
// Construction
public:
	CFlashAddinDialog(CWnd* pParent = NULL);   // standard constructor
	CXTabCtrl* m_pTab;
// Dialog Data
	//{{AFX_DATA(CFlashAddinDialog)
	enum { IDD = IDD_LOWER_FLASH_DIALOG };
	CComboBox	m_ComboBracketing;
	CSpinButtonCtrl	m_SpinBracketing;
	CSpinButtonCtrl	m_SpinDelay;
	CSpinButtonCtrl	m_SpinFlash;
	CEdit	m_EditBracketing;
	CEdit	m_EditDelay;
	CEdit	m_EditFlash;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlashAddinDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFlashAddinDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLASHADDINDIALOG_H__69FA8BA7_68A3_41AC_BC16_671285E70228__INCLUDED_)
