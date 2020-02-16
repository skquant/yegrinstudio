// MemoryAddinDialog.cpp : implementation file
//

#include "stdafx.h"
#include "yegrinstudio.h"
#include "MemoryAddinDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemoryAddinDialog dialog


CMemoryAddinDialog::CMemoryAddinDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMemoryAddinDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMemoryAddinDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMemoryAddinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMemoryAddinDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMemoryAddinDialog, CDialog)
	//{{AFX_MSG_MAP(CMemoryAddinDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoryAddinDialog message handlers

BOOL CMemoryAddinDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

#ifdef _USE_SKIN
	theApp.m_pSkin = GetDlgItem(IDC_SKIN_L4)->GetControlUnknown();
	theApp.m_pSkin->ApplySkin((long)m_hWnd);
	USES_CONVERSION;

	theApp.m_pSkin->LoadSkin(L"winaqua.skn");
	theApp.m_pSkin->ApplySkin((int)m_hWnd);
#endif	//_USE_SKIN

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
