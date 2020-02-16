// AuxiliairyAddinDialog.cpp : implementation file
//

#include "stdafx.h"
#include "yegrinstudio.h"
#include "AuxiliairyAddinDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAuxiliairyAddinDialog dialog


CAuxiliairyAddinDialog::CAuxiliairyAddinDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAuxiliairyAddinDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAuxiliairyAddinDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAuxiliairyAddinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAuxiliairyAddinDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAuxiliairyAddinDialog, CDialog)
	//{{AFX_MSG_MAP(CAuxiliairyAddinDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAuxiliairyAddinDialog message handlers

BOOL CAuxiliairyAddinDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

#ifdef _USE_SKIN
	theApp.m_pSkin = GetDlgItem(IDC_SKIN_L2)->GetControlUnknown();
	theApp.m_pSkin->ApplySkin((long)m_hWnd);
	USES_CONVERSION;

	theApp.m_pSkin->LoadSkin(L"winaqua.skn");
	theApp.m_pSkin->ApplySkin((int)m_hWnd);
#endif //_USE_SKIN

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
