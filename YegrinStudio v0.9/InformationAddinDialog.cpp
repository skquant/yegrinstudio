// InformationAddinDialog.cpp : implementation file
//

#include "stdafx.h"
#include "yegrinstudio.h"
#include "InformationAddinDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInformationAddinDialog dialog


CInformationAddinDialog::CInformationAddinDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInformationAddinDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInformationAddinDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInformationAddinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInformationAddinDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInformationAddinDialog, CDialog)
	//{{AFX_MSG_MAP(CInformationAddinDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInformationAddinDialog message handlers

BOOL CInformationAddinDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

#ifdef _USE_SKIN
	theApp.m_pSkin = GetDlgItem(IDC_SKIN_L5)->GetControlUnknown();
	theApp.m_pSkin->ApplySkin((long)m_hWnd);
	USES_CONVERSION;

	theApp.m_pSkin->LoadSkin(L"winaqua.skn");
	theApp.m_pSkin->ApplySkin((int)m_hWnd);
#endif //_USE_SKIN

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
