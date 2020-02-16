#if !defined(AFX_FLASHOPTIONS_H__8EB7AB3A_80C1_49A7_8EC4_FE356907499A__INCLUDED_)
#define AFX_FLASHOPTIONS_H__8EB7AB3A_80C1_49A7_8EC4_FE356907499A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlashOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlashOptions dialog

class CFlashOptions : public CDialog
{
// Construction
public:
	CFlashOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFlashOptions)
	enum { IDD = IDD_LOWER_FLASH_OPTION_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlashOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFlashOptions)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLASHOPTIONS_H__8EB7AB3A_80C1_49A7_8EC4_FE356907499A__INCLUDED_)
