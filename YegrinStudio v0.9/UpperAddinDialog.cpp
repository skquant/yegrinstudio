// UpperAddinDialog.cpp : implementation file
//

#include "stdafx.h"
#include "yegrinstudio.h"
#include "UpperAddinDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUpperAddinDialog dialog


CUpperAddinDialog::CUpperAddinDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CUpperAddinDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpperAddinDialog)
	//}}AFX_DATA_INIT
}


void CUpperAddinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpperAddinDialog)
	DDX_Control(pDX, IDC_SPIN_DEVB2INFO, m_SpinDevB2Info);
	DDX_Control(pDX, IDC_SPIN_DEVB1INFO, m_SpinDevB1Info);
	DDX_Control(pDX, IDC_SPIN_DEVAINFO, m_SpinDevAInfo);
	DDX_Control(pDX, IDC_STATIC_DEVB2INFO, m_LcdB2DevInfo);
	DDX_Control(pDX, IDC_STATIC_DEVB1INFO, m_LcdB1DevInfo);
	DDX_Control(pDX, IDC_STATIC_DEVAINFO, m_LcdADevInfo);
	DDX_Control(pDX, IDC_STATIC_FUNCTIONS, m_ImageFunctions);
	DDX_Control(pDX, IDC_STATIC_CHARGE2, m_ImageCharge2);
	DDX_Control(pDX, IDC_STATIC_CHARGE1, m_ImageCharge1);
	DDX_Control(pDX, IDC_STATIC_MODE, m_ImageMode);
	DDX_Control(pDX, IDC_STATIC_HOLD, m_ImageHold);
	DDX_Control(pDX, IDC_STATIC_TEST, m_ImageTest);
	DDX_Control(pDX, IDC_STATIC_SOUND, m_ImageSound);
	DDX_Control(pDX, IDC_STATIC_RF, m_ImageRF);
	DDX_Control(pDX, IDC_STATIC_PCELL, m_ImagePCell);
	DDX_Control(pDX, IDC_STATIC_MODL4, m_ImageModl4);
	DDX_Control(pDX, IDC_STATIC_MODL3, m_ImageModl3);
	DDX_Control(pDX, IDC_STATIC_MODL2, m_ImageModl2);
	DDX_Control(pDX, IDC_STATIC_MODL1, m_ImageModl1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpperAddinDialog, CDialog)
	//{{AFX_MSG_MAP(CUpperAddinDialog)
	ON_BN_CLICKED(IDC_MODL_BUTTON, OnModlButton)
	ON_BN_CLICKED(IDC_SOUND_BUTTON, OnSoundButton)
	ON_BN_CLICKED(IDC_MODE_BUTTON, OnModeButton)
	ON_BN_CLICKED(IDC_HOLD_BUTTON, OnHoldButton)
	ON_BN_CLICKED(IDC_PCELL_BUTTON, OnPcellButton)
	ON_BN_CLICKED(IDC_RF_BUTTON, OnRfButton)
	ON_BN_CLICKED(IDC_CHARGE_BUTTON, OnChargeButton)
	ON_BN_CLICKED(IDC_TEST_BUTTON, OnTestButton)
	ON_BN_CLICKED(IDC_BUTTON_A, OnButtonA)
	ON_BN_CLICKED(IDC_BUTTON_B1, OnButtonB1)
	ON_BN_CLICKED(IDC_BUTTON_B2, OnButtonB2)
	ON_WM_PAINT()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DEVAINFO, OnDeltaposSpinDevainfo)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DEVB1INFO, OnDeltaposSpinDevb1info)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DEVB2INFO, OnDeltaposSpinDevb2info)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpperAddinDialog message handlers

BOOL CUpperAddinDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

/*
	// 아이콘을 입힌 버튼
	m_btnIconA.SetButtonBmp(IDB_BITMAP_A);
	//m_btnIconA.SetButtonIcon(IDI_DEVICE_ICON);					// 비트맵을 설정한다
	m_btnIconA.SetFlat(TRUE);										// 입체 버튼을 설정한다
	m_btnIconA.SetButtonColor(COLOR_TEXT, RGB(50, 50, 50));			// 글자색을 설정한다 
	m_btnIconA.SetButtonColor(COLOR_BKGND, RGB(192, 192, 192));		// 배경색을 설정한다
	m_btnIconA.SetButtonColor(COLOR_TEXT_IN, RGB(66, 168, 255));		// 마우스가 진입 했을 때의 글자색을 설정한다
	m_btnIconA.SetButtonColor(COLOR_BKGND_IN, RGB(220, 220, 220));	// 마우스가 진입 했을 때의 배경색을 설정한다

	m_BtnIconB1.SetButtonBmp(IDB_BITMAP_B1);						// 비트맵을 설정한다
	m_BtnIconB1.SetFlat(TRUE);										// 입체 버튼을 설정한다
	m_BtnIconB1.SetButtonColor(COLOR_TEXT, RGB(50, 50, 50));			// 글자색을 설정한다 
	m_BtnIconB1.SetButtonColor(COLOR_BKGND, RGB(192, 192, 192));		// 배경색을 설정한다
	m_BtnIconB1.SetButtonColor(COLOR_TEXT_IN, RGB(66, 168, 255));		// 마우스가 진입 했을 때의 글자색을 설정한다
	m_BtnIconB1.SetButtonColor(COLOR_BKGND_IN, RGB(220, 220, 220));	// 마우스가 진입 했을 때의 배경색을 설정한다

	m_BtnIconB2.SetButtonBmp(IDB_BITMAP_B2);						// 비트맵을 설정한다
	m_BtnIconB2.SetFlat(TRUE);										// 입체 버튼을 설정한다
	m_BtnIconB2.SetButtonColor(COLOR_TEXT, RGB(50, 50, 50));			// 글자색을 설정한다 
	m_BtnIconB2.SetButtonColor(COLOR_BKGND, RGB(192, 192, 192));		// 배경색을 설정한다
	m_BtnIconB2.SetButtonColor(COLOR_TEXT_IN, RGB(66, 168, 255));		// 마우스가 진입 했을 때의 글자색을 설정한다
	m_BtnIconB2.SetButtonColor(COLOR_BKGND_IN, RGB(220, 220, 220));	// 마우스가 진입 했을 때의 배경색을 설정한다

	m_UppwerPlusBtn.SetButtonBmp(IDB_BITMAP_PLUS);	
	//m_UppwerPlusBtn.SetButtonIcon(IDI_PLUS_ICON);							// 아이콘을 설정한다
	m_UppwerPlusBtn.SetFlat(TRUE);										// 입체 버튼을 설정한다
	m_UppwerPlusBtn.SetButtonColor(COLOR_TEXT, RGB(50, 50, 50));			// 글자색을 설정한다 
	m_UppwerPlusBtn.SetButtonColor(COLOR_BKGND, RGB(192, 192, 192));		// 배경색을 설정한다
	m_UppwerPlusBtn.SetButtonColor(COLOR_TEXT_IN, RGB(66, 168, 255));		// 마우스가 진입 했을 때의 글자색을 설정한다
	m_UppwerPlusBtn.SetButtonColor(COLOR_BKGND_IN, RGB(220, 220, 220));	// 마우스가 진입 했을 때의 배경색을 설정한다

	m_UppwerMinusBtn.SetButtonBmp(IDB_BITMAP_MINUS);							// 아이콘을 설정한다
	m_UppwerMinusBtn.SetFlat(TRUE);										// 입체 버튼을 설정한다
	m_UppwerMinusBtn.SetButtonColor(COLOR_TEXT, RGB(50, 50, 50));			// 글자색을 설정한다 
	m_UppwerMinusBtn.SetButtonColor(COLOR_BKGND, RGB(192, 192, 192));		// 배경색을 설정한다
	m_UppwerMinusBtn.SetButtonColor(COLOR_TEXT_IN, RGB(66, 168, 255));		// 마우스가 진입 했을 때의 글자색을 설정한다
	m_UppwerMinusBtn.SetButtonColor(COLOR_BKGND_IN, RGB(220, 220, 220));	// 마우스가 진입 했을 때의 배경색을 설정한다

	m_LowerPlusBtn.SetButtonBmp(IDB_BITMAP_PLUS);							// 아이콘을 설정한다
	m_LowerPlusBtn.SetFlat(TRUE);										// 입체 버튼을 설정한다
	m_LowerPlusBtn.SetButtonColor(COLOR_TEXT, RGB(50, 50, 50));			// 글자색을 설정한다 
	m_LowerPlusBtn.SetButtonColor(COLOR_BKGND, RGB(192, 192, 192));		// 배경색을 설정한다
	m_LowerPlusBtn.SetButtonColor(COLOR_TEXT_IN, RGB(66, 168, 255));		// 마우스가 진입 했을 때의 글자색을 설정한다
	m_LowerPlusBtn.SetButtonColor(COLOR_BKGND_IN, RGB(220, 220, 220));	// 마우스가 진입 했을 때의 배경색을 설정한다

	m_LowerMinusBtn.SetButtonBmp(IDB_BITMAP_MINUS);							// 아이콘을 설정한다
	m_LowerMinusBtn.SetFlat(TRUE);										// 입체 버튼을 설정한다
	m_LowerMinusBtn.SetButtonColor(COLOR_TEXT, RGB(50, 50, 50));			// 글자색을 설정한다 
	m_LowerMinusBtn.SetButtonColor(COLOR_BKGND, RGB(192, 192, 192));		// 배경색을 설정한다
	m_LowerMinusBtn.SetButtonColor(COLOR_TEXT_IN, RGB(66, 168, 255));		// 마우스가 진입 했을 때의 글자색을 설정한다
	m_LowerMinusBtn.SetButtonColor(COLOR_BKGND_IN, RGB(220, 220, 220));	// 마우스가 진입 했을 때의 배경색을 설정한다

	COLORREF	crBtnColor;
	// Calculate a color effect for hilighting the button
	crBtnColor = ::GetSysColor(COLOR_BTNFACE) + RGB(30, 30, 30);

	m_ModlBtn.SetIcon(IDI_ICON_MODLON, IDI_ICON_MODLOFF);
	m_ModlBtn.DrawBorder(FALSE);
	m_ModlBtn.SetBtnCursor(IDC_HAND);
	m_ModlBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_ModlBtn.SetTooltipText(_T("MOD.L"));

	m_SoundBtn.SetIcon(IDI_ICON_SOUNDON,IDI_ICON_SOUNDOFF );
	m_SoundBtn.DrawBorder(FALSE);
	m_SoundBtn.SetBtnCursor(IDC_HAND);	
	m_SoundBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_SoundBtn.SetTooltipText(_T("Sound"));

	m_ModeBtn.SetIcon(IDI_ICON_MODEON,IDI_ICON_MODEOFF );
	m_ModeBtn.DrawBorder(FALSE);
	m_ModeBtn.SetBtnCursor(IDC_HAND);	
	m_ModeBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_ModeBtn.SetTooltipText(_T("Mode"));

	m_HoldBtn.SetIcon(IDI_ICON_HOLDON,IDI_ICON_HOLDOFF );
	m_HoldBtn.DrawBorder(FALSE);
	m_HoldBtn.SetBtnCursor(IDC_HAND);	
	m_HoldBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_HoldBtn.SetTooltipText(_T("Hold"));

	m_PCellBtn.SetIcon(IDI_ICON_PCELLON,IDI_ICON_PCELLOFF );
	m_PCellBtn.DrawBorder(FALSE);
	m_PCellBtn.SetBtnCursor(IDC_HAND);	
	m_PCellBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_PCellBtn.SetTooltipText(_T("P.Cell"));

	m_RFBtn.SetIcon(IDI_ICON_RFON,IDI_ICON_RFOFF );
	m_RFBtn.DrawBorder(FALSE);
	m_RFBtn.SetBtnCursor(IDC_HAND);	
	m_RFBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_RFBtn.SetTooltipText(_T("R/F"));

	m_ChargeBtn.SetIcon(IDI_ICON_CHARGEON,IDI_ICON_CHARGEOFF );
	m_ChargeBtn.DrawBorder(FALSE);
	m_ChargeBtn.SetBtnCursor(IDC_HAND);	
	m_ChargeBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_ChargeBtn.SetTooltipText(_T("CHARGE"));

	m_TestBtn.SetIcon(IDI_ICON_TESTON,IDI_ICON_TESTOFF );
	m_TestBtn.DrawBorder(FALSE);
	m_TestBtn.SetBtnCursor(IDC_HAND);	
	m_TestBtn.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_TestBtn.SetTooltipText(_T("TEST"));
*/
	//조건을 읽어서 삽입
	//Picture Control Bitmap 삽입	
	//m_ImageModl1.SetBitmap(m_ImageON);
	
	nBodlCheck = 0;
	bSound	= TRUE;
	bMode	= TRUE;
	bHold	= TRUE;
	bPcell	= TRUE;
	bRf		= TRUE;
	Charge1 = TRUE;
	bTest	= TRUE;

	SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageModl1);
	SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl2);
	SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl3);
	SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl4);
	SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageSound);
	SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageMode);
	SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageHold);
	SetBitmap(IDB_BITMAP_FUNCTIONSON, &m_OnOffImage,&m_ImageFunctions);
	SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImagePCell);
	SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageRF);
	SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageCharge1);
	SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageCharge2);
	SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageTest);

	m_SpinDevAInfo.SetPos(40);
	m_SpinDevAInfo.SetRange(40, 90);
	m_SpinDevB1Info.SetPos(40);
	m_SpinDevB1Info.SetRange(40, 90);
	m_SpinDevB2Info.SetPos(40);
	m_SpinDevB2Info.SetRange(40, 90);

	m_LcdADevInfo.SetNumberOfLines(1);
	m_LcdADevInfo.SetXCharsPerLine(16);
	m_LcdADevInfo.SetSize(CMatrixStatic::LARGE);
	m_LcdADevInfo.SetDisplayColors(RGB(0, 0, 0), RGB(255, 60, 0), RGB(103, 30, 0));
	m_LcdADevInfo.AdjustClientXToSize(3);
	m_LcdADevInfo.AdjustClientYToSize(1);
	m_LcdADevInfo.SetText(_T("- -"));
	m_LcdADevInfo.SetAutoPadding(true);

	m_LcdB1DevInfo.SetNumberOfLines(1);
	m_LcdB1DevInfo.SetXCharsPerLine(16);
	m_LcdB1DevInfo.SetSize(CMatrixStatic::LARGE);
	m_LcdB1DevInfo.SetDisplayColors(RGB(0, 0, 0), RGB(255, 60, 0), RGB(103, 30, 0));
	m_LcdB1DevInfo.AdjustClientXToSize(3);
	m_LcdB1DevInfo.AdjustClientYToSize(1);
	m_LcdB1DevInfo.SetText(_T("7.5"));
	m_LcdB1DevInfo.SetAutoPadding(true);

	m_LcdB2DevInfo.SetNumberOfLines(1);
	m_LcdB2DevInfo.SetXCharsPerLine(16);
	m_LcdB2DevInfo.SetSize(CMatrixStatic::LARGE);
	m_LcdB2DevInfo.SetDisplayColors(RGB(0, 0, 0), RGB(255, 60, 0), RGB(103, 30, 0));
	m_LcdB2DevInfo.AdjustClientXToSize(3);
	m_LcdB2DevInfo.AdjustClientYToSize(1);
	m_LcdB2DevInfo.SetText(_T("7.5"));
	m_LcdB2DevInfo.SetAutoPadding(true);

	//if(g_ComPortCheck) {
		//CommInterface(0, "A0", "LD", rd);
	//}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CUpperAddinDialog::SetBitmap(UINT nID, CBitmap* BitmapObject,CStatic* PictureObject )
{
	BitmapObject->LoadBitmap(nID);
	PictureObject->ModifyStyle(SS_CENTER, SS_BITMAP|SS_CENTERIMAGE,0);	
	PictureObject->SetBitmap(*BitmapObject); 
	BitmapObject->Detach();
	BitmapObject->DeleteObject();
}

void CUpperAddinDialog::OnModlButton() 
{
	// Calculate a color effect for hilighting the button
	// TODO: Add your control notification handler code here
	CString Data;
	Data.Format("0100");
	CommInterface(1, "A0", "KD", Data);
	// 데이터를 누를때 마다 불이 켜지고 꺼지고 바뀌게 한다.

	//먼저 LED 상태를 읽어 낸다.
	nBodlCheck++;
	nBodlCheck %= 4;

	switch(nBodlCheck)
	{
	case 0:
		SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageModl1);
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl2);
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl3);
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl4);
		break;
	case 1:
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl1);
		SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageModl2);
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl3);
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl4);
		break;
	case 2:
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl1);
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl2);
		SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageModl3);
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl4);
		break;
	case 3:
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl1);
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl2);
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageModl3);
		SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageModl4);
		break;
	}
}

void CUpperAddinDialog::OnSoundButton() 
{
	// TODO: Add your control notification handler code here
	CString Data;
	Data.Format("0080");
	CommInterface(1, "A0", "KD", Data);

	//사운드 LED 상태를 읽어 낸다.
	if(bSound == FALSE) {

		SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageSound);
		bSound = TRUE;
	} else {

		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageSound);
		bSound = FALSE;
	}
}

void CUpperAddinDialog::OnModeButton() 
{
	// TODO: Add your control notification handler code here
	CString Data;
	Data.Format("0040");
	CommInterface(1, "A0", "KD", Data);

	if(bMode == FALSE) {

		SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageMode);
		bMode = TRUE;
	} else {


		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageMode);
		bMode = FALSE;
	}
}

void CUpperAddinDialog::OnHoldButton() 
{
	// TODO: Add your control notification handler code here
	CString Data;
	Data.Format("0020");
	CommInterface(1, "A0", "KD", Data);

	if(bHold == FALSE) {
		SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageHold);
		bHold = TRUE;
	} else {
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageHold);
		bHold = FALSE;
	}
}

void CUpperAddinDialog::OnPcellButton() 
{
	// TODO: Add your control notification handler code here
	CString Data;
	Data.Format("0010");
	CommInterface(1, "A0", "KD", Data);

	if(bPcell == FALSE) {

		SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImagePCell);
		bPcell = TRUE;
	} else {

		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImagePCell);
		bPcell = FALSE;
	}
}

void CUpperAddinDialog::OnRfButton() 
{
	// TODO: Add your control notification handler code here
	CString Data;
	Data.Format("0008");
	CommInterface(1, "A0", "KD", Data);

	if(bRf == FALSE) {
		
		SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageRF);
		bRf = TRUE;
	} else {

		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageRF);
		bRf = FALSE;
	}
}

void CUpperAddinDialog::OnChargeButton() 
{
	// TODO: Add your control notification handler code here
	CString Data;
	Data.Format("0004");
	CommInterface(1, "A0", "KD", Data);
	if(Charge1 == FALSE) {
		SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageCharge1);
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageCharge2);
		Charge1 = TRUE;
	} else {
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageCharge1);
		SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageCharge2);
		Charge1 = FALSE;
	}
}
void CUpperAddinDialog::OnTestButton() 
{
	// TODO: Add your control notification handler code here
	CString Data;
	Data.Format("0002");
	CommInterface(1, "A0", "KD", Data);
	if(bTest == FALSE) {
		SetBitmap(IDB_BITMAP_LEDON, &m_OnOffImage,&m_ImageTest);
		bTest = TRUE;
	} else {
		SetBitmap(IDB_BITMAP_LEDOFF, &m_OnOffImage,&m_ImageTest);
		bTest = FALSE;
	}
}

void CUpperAddinDialog::OnButtonA() 
{
	// TODO: Add your control notification handler code here
	CString Data;
	Data.Format("8000");
	CommInterface(1, "A0", "KD", Data);
}

void CUpperAddinDialog::OnButtonB1() 
{
	// TODO: Add your control notification handler code here
	CString Data;
	Data.Format("4000");
	CommInterface(1, "A0", "KD", Data);
}

void CUpperAddinDialog::OnButtonB2() 
{
	// TODO: Add your control notification handler code here
	CString Data;
	Data.Format("2000");
	CommInterface(1, "A0", "KD", Data);
}

void CUpperAddinDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	m_LcdADevInfo.SetText(_T("- -"));
	m_LcdADevInfo.SetAutoPadding(true);

	m_LcdB1DevInfo.SetText(_T("7.5"));
	m_LcdB1DevInfo.SetAutoPadding(true);

	m_LcdB2DevInfo.SetText(_T("7.5"));
	m_LcdB2DevInfo.SetAutoPadding(true);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CUpperAddinDialog::OnDeltaposSpinDevainfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	CString szTmp;

	int nPos = pNMUpDown->iPos + pNMUpDown->iDelta;
	
	nPos = min(nPos, 90);
	nPos = max(nPos, 40);

	szTmp.Format("%d.%d", nPos/10, nPos%10);
	m_LcdADevInfo.SetText(szTmp);
	m_LcdADevInfo.SetAutoPadding(true);

	*pResult = 0;
}

void CUpperAddinDialog::OnDeltaposSpinDevb1info(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	CString szTmp;

	int nPos = pNMUpDown->iPos + pNMUpDown->iDelta;
	
	nPos = min(nPos, 90);
	nPos = max(nPos, 40);

	m_SpinDevB2Info.SetPos(nPos);

	szTmp.Format("%d.%d", nPos/10, nPos%10);
	m_LcdB1DevInfo.SetText(szTmp);
	m_LcdB1DevInfo.SetAutoPadding(true);

	m_LcdB2DevInfo.SetText(szTmp);
	m_LcdB2DevInfo.SetAutoPadding(true);

	*pResult = 0;
}

void CUpperAddinDialog::OnDeltaposSpinDevb2info(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	CString szTmp;

	int nPos = pNMUpDown->iPos + pNMUpDown->iDelta;
	
	nPos = min(nPos, 90);
	nPos = max(nPos, 40);

	m_SpinDevB1Info.SetPos(nPos);

	szTmp.Format("%d.%d", nPos/10, nPos%10);
	m_LcdB1DevInfo.SetText(szTmp);
	m_LcdB1DevInfo.SetAutoPadding(true);

	m_LcdB2DevInfo.SetText(szTmp);
	m_LcdB2DevInfo.SetAutoPadding(true);
	
	*pResult = 0;
}
