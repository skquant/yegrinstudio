#if !defined(AFX_MEMORYADDINDIALOG_H__3F616CBD_3580_47AA_939F_09B9A78761C7__INCLUDED_)
#define AFX_MEMORYADDINDIALOG_H__3F616CBD_3580_47AA_939F_09B9A78761C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MemoryAddinDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMemoryAddinDialog dialog
class CXTabCtrl;
class CMemoryAddinDialog : public CDialog
{
// Construction
public:
	CMemoryAddinDialog(CWnd* pParent = NULL);   // standard constructor
	CXTabCtrl* m_pTab;
// Dialog Data
	//{{AFX_DATA(CMemoryAddinDialog)
	enum { IDD = IDD_LOWER_MEMORY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryAddinDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMemoryAddinDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMORYADDINDIALOG_H__3F616CBD_3580_47AA_939F_09B9A78761C7__INCLUDED_)
