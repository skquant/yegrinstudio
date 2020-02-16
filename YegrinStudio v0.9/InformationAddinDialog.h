#if !defined(AFX_InformationAddinDialog_H__E493EBAF_6DCB_4AAF_83AE_833DAECF66D3__INCLUDED_)
#define AFX_InformationAddinDialog_H__E493EBAF_6DCB_4AAF_83AE_833DAECF66D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InformationAddinDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInformationAddinDialog dialog
class CXTabCtrl;
class CInformationAddinDialog : public CDialog
{
// Construction
public:
	CInformationAddinDialog(CWnd* pParent = NULL);   // standard constructor
	CXTabCtrl* m_pTab;
// Dialog Data
	//{{AFX_DATA(CInformationAddinDialog)
	enum { IDD = IDD_LOWER_INFORMATION_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInformationAddinDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInformationAddinDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_InformationAddinDialog_H__E493EBAF_6DCB_4AAF_83AE_833DAECF66D3__INCLUDED_)
