// GroupSyncAddinDialog.cpp : implementation file
//

#include "stdafx.h"
#include "yegrinstudio.h"
#include "GroupSyncAddinDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupSyncAddinDialog dialog


CGroupSyncAddinDialog::CGroupSyncAddinDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGroupSyncAddinDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGroupSyncAddinDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGroupSyncAddinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupSyncAddinDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroupSyncAddinDialog, CDialog)
	//{{AFX_MSG_MAP(CGroupSyncAddinDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroupSyncAddinDialog message handlers

BOOL CGroupSyncAddinDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

#ifdef _USE_SKIN
	theApp.m_pSkin = GetDlgItem(IDC_SKIN_L3)->GetControlUnknown();
	theApp.m_pSkin->ApplySkin((long)m_hWnd);
	USES_CONVERSION;

	theApp.m_pSkin->LoadSkin(L"winaqua.skn");
	theApp.m_pSkin->ApplySkin((int)m_hWnd);
#endif //_USE_SKIN

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
