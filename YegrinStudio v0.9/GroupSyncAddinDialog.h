#if !defined(AFX_GROUPSYNCADDINDIALOG_H__D4E5D20E_3934_46FA_8EB4_64931BC037F1__INCLUDED_)
#define AFX_GROUPSYNCADDINDIALOG_H__D4E5D20E_3934_46FA_8EB4_64931BC037F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GroupSyncAddinDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupSyncAddinDialog dialog
class CXTabCtrl;
class CGroupSyncAddinDialog : public CDialog
{
// Construction
public:
	CGroupSyncAddinDialog(CWnd* pParent = NULL);   // standard constructor
	CXTabCtrl* m_pTab;
// Dialog Data
	//{{AFX_DATA(CGroupSyncAddinDialog)
	enum { IDD = IDD_LOWER_GROUP_SYNC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupSyncAddinDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGroupSyncAddinDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPSYNCADDINDIALOG_H__D4E5D20E_3934_46FA_8EB4_64931BC037F1__INCLUDED_)
