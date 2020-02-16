#if !defined(AFX_AUXILIAIRYADDINDIALOG_H__438B88F5_5940_4059_B42A_B486D4C7E276__INCLUDED_)
#define AFX_AUXILIAIRYADDINDIALOG_H__438B88F5_5940_4059_B42A_B486D4C7E276__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AuxiliairyAddinDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAuxiliairyAddinDialog dialog
class CXTabCtrl;
class CAuxiliairyAddinDialog : public CDialog
{
// Construction
public:
	CAuxiliairyAddinDialog(CWnd* pParent = NULL);   // standard constructor
	CXTabCtrl* m_pTab;
// Dialog Data
	//{{AFX_DATA(CAuxiliairyAddinDialog)
	enum { IDD = IDD_LOWER_AUXILIARY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuxiliairyAddinDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAuxiliairyAddinDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUXILIAIRYADDINDIALOG_H__438B88F5_5940_4059_B42A_B486D4C7E276__INCLUDED_)
