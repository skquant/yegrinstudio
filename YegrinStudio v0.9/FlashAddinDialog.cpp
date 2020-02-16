// FlashAddinDialog.cpp : implementation file
//

#include "stdafx.h"
#include "yegrinstudio.h"
#include "FlashAddinDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlashAddinDialog dialog


CFlashAddinDialog::CFlashAddinDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFlashAddinDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlashAddinDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFlashAddinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlashAddinDialog)
	DDX_Control(pDX, IDC_COMBO_BRACKETING, m_ComboBracketing);
	DDX_Control(pDX, IDC_SPIN_DELAY, m_SpinDelay);
	DDX_Control(pDX, IDC_SPIN_FLASH, m_SpinFlash);
	DDX_Control(pDX, IDC_EDIT_DELAY, m_EditDelay);
	DDX_Control(pDX, IDC_EDIT_FLASH, m_EditFlash);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFlashAddinDialog, CDialog)
	//{{AFX_MSG_MAP(CFlashAddinDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlashAddinDialog message handlers

BOOL CFlashAddinDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

#ifdef _USE_SKIN
	theApp.m_pSkin = GetDlgItem(IDC_SKIN_L1)->GetControlUnknown();
	theApp.m_pSkin->ApplySkin((long)m_hWnd);
	USES_CONVERSION;

	theApp.m_pSkin->LoadSkin(L"winaqua.skn");
	theApp.m_pSkin->ApplySkin((int)m_hWnd);
#endif //_USE_SKIN

	char cBuffer[256];

	wsprintf(cBuffer, "%d", 0);
	m_EditFlash.SetWindowText(cBuffer);
	m_SpinFlash.SetPos(0);
	m_SpinFlash.SetRange(0, 4);

	wsprintf(cBuffer, "%d", 0);
	m_EditDelay.SetWindowText(cBuffer);
	m_SpinDelay.SetPos(0);
	m_SpinDelay.SetRange(0, 4);

	//wsprintf(cBuffer, "%d", 0);
	//m_EditBracketing.SetWindowText(cBuffer);
	//m_SpinBracketing.SetPos(0);
	//m_SpinBracketing.SetRange(0, 4);
	m_ComboBracketing.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
