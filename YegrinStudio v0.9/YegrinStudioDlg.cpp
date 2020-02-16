// YegrinStudioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "YegrinStudio.h"
#include "YegrinStudioDlg.h"
#include "SetupDialog.h"

COMMSETUP commsetup;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_GROUP_NUM		4

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYegrinStudioDlg dialog

CYegrinStudioDlg::CYegrinStudioDlg(CWnd* pParent /*=NULL*/)
	: CImageDialog(CYegrinStudioDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CYegrinStudioDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CYegrinStudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CImageDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYegrinStudioDlg)
	DDX_Control(pDX, IDC_EDIT_RCVTEST, m_RcvTest);
	DDX_Control(pDX, IDC_UPPER_TAB, m_UppperTabCtrl);
	DDX_Control(pDX, IDC_LOWER_TAB, m_LowerTabCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CYegrinStudioDlg, CImageDialog)
	//{{AFX_MSG_MAP(CYegrinStudioDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENUITEM_SETTUP, OnMenuitemSettup)
	ON_UPDATE_COMMAND_UI(ID_MENUITEM_SETTUP, OnUpdateMenuitemSettup)
	ON_COMMAND(ID_MENUITEM_CONNECT, OnMenuitemConnect)
	ON_UPDATE_COMMAND_UI(ID_MENUITEM_CONNECT, OnUpdateMenuitemConnect)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_COMM_READ,OnRxData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYegrinStudioDlg message handlers

BOOL CYegrinStudioDlg::OnInitDialog()
{
	CImageDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here	
	//SetBitmap(IDB_BKGND_BMP);
	//SetBkgndMode(MODE_STRETCH);

	m_pLowerFlashAddinDialog		= NULL;
	m_pLowerAuxiliairyAddinDialog	= NULL;
	m_pLowerInformationAddinDialog	= NULL;
	m_pLowerMemoryAddinDialog		= NULL;
	m_pLowerGroupSyncAddinDialog	= NULL;

	m_UpperImageTab.Create(IDB_UPPERTAB_IMAGE_SAMPLE, 16, 0, RGB(0, 255, 0));
	m_UppperTabCtrl.SetImageList(&m_UpperImageTab);

	/*
	if(bCheckReading == TRUE){
		//링크드 리스트의 Yegrin정보 
		YegrinStruct = ComPortSettup();
		j = YegrinStruct.Num;
		while(i < j){
			그룹 생성 및 장치 생성
			i++;
		}

	} else {
		모든 이미지 모두.EnableWindow(FALSE);
	}
	*/
	//m_pUpperAddinDialog[0]				= NULL;
	char DeviceNames[5][10]={"A Group","B Group","C Group","D Group","E Group"};

	for(int i=0 ; i<MAX_GROUP_NUM ; i++){		
		m_pUpperAddinDialog[i] = new CUpperAddinDialog;
		m_pUpperAddinDialog[i]->Create(CUpperAddinDialog::IDD, &m_UppperTabCtrl);

		m_UppperTabCtrl.AddTab(m_pUpperAddinDialog[i], DeviceNames[i], 0);
		m_pUpperAddinDialog[i]->m_pTab = &m_UppperTabCtrl;
		
		//** customizing the tab control --------
		m_UppperTabCtrl.SetDisabledColor(RGB(255, 0, 0));
		m_UppperTabCtrl.SetSelectedColor(RGB(0, 0, 255));
		m_UppperTabCtrl.SetMouseOverColor(RGB(255, 255, 255));
		m_UppperTabCtrl.EnableTab(i, TRUE);
	}
	//#######################################################################
	//m_LowerImageTab.Create(IDB_UPPERTAB_IMAGE, 16, 0, RGB(0, 255, 0));
	//m_LowerTabCtrl.SetImageList(&m_LowerImageTab);

	m_pLowerFlashAddinDialog = new CFlashAddinDialog;
	m_pLowerFlashAddinDialog->Create(CFlashAddinDialog::IDD, &m_LowerTabCtrl);
	m_LowerTabCtrl.AddTab(m_pLowerFlashAddinDialog, "Flash Options", 0);
	m_pLowerFlashAddinDialog->m_pTab = &m_LowerTabCtrl;

	m_pLowerAuxiliairyAddinDialog = new CAuxiliairyAddinDialog;
	m_pLowerAuxiliairyAddinDialog->Create(CAuxiliairyAddinDialog::IDD, &m_LowerTabCtrl);
	m_LowerTabCtrl.AddTab(m_pLowerAuxiliairyAddinDialog, "Auxiliairy Options", 1);

	m_pLowerInformationAddinDialog = new CInformationAddinDialog;
	m_pLowerInformationAddinDialog->Create(CInformationAddinDialog::IDD, &m_LowerTabCtrl);
	m_LowerTabCtrl.AddTab(m_pLowerInformationAddinDialog, "Informations", 2);

	m_pLowerMemoryAddinDialog = new CMemoryAddinDialog;
	m_pLowerMemoryAddinDialog->Create(CMemoryAddinDialog::IDD, &m_LowerTabCtrl);
	m_LowerTabCtrl.AddTab(m_pLowerMemoryAddinDialog, "Memory Function", 3);

	m_pLowerGroupSyncAddinDialog = new CGroupSyncAddinDialog;
	m_pLowerGroupSyncAddinDialog->Create(CGroupSyncAddinDialog::IDD, &m_LowerTabCtrl);
	m_LowerTabCtrl.AddTab(m_pLowerGroupSyncAddinDialog, "Group Syncronization", 4);

	//** customizing the tab control --------
	m_LowerTabCtrl.SetDisabledColor(RGB(255, 0, 0));
	m_LowerTabCtrl.SetSelectedColor(RGB(0, 0, 255));
	m_LowerTabCtrl.SetMouseOverColor(RGB(255, 0, 255));
	m_LowerTabCtrl.EnableTab(4, TRUE);

	if(m_CommPort1.m_bPortOnOff)//연결이 되있는 상태
		g_ComPortCheck = TRUE;
	else
		g_ComPortCheck = FALSE;

	MyhCommWnd = m_hWnd;

	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CYegrinStudioDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CImageDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CYegrinStudioDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CImageDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CYegrinStudioDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CYegrinStudioDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	for(int i=0 ; i<MAX_GROUP_NUM ; i++){	
		if (m_pUpperAddinDialog[i])		delete m_pUpperAddinDialog[i];
	}
	if (m_pLowerFlashAddinDialog)		delete m_pLowerFlashAddinDialog;
	if (m_pLowerAuxiliairyAddinDialog)	delete m_pLowerAuxiliairyAddinDialog;
	if (m_pLowerInformationAddinDialog)	delete m_pLowerInformationAddinDialog;
	if (m_pLowerMemoryAddinDialog)		delete m_pLowerMemoryAddinDialog;
	if (m_pLowerGroupSyncAddinDialog)	delete m_pLowerGroupSyncAddinDialog;
	return CImageDialog::DestroyWindow();
}

void CYegrinStudioDlg::OnMenuitemSettup() 
{
	// TODO: Add your command handler code here
	CSetupDialog m_dlg;
	//셋업다이얼로그 오케이 일때.. 캔슬은 만들던지.. 없애던지..
	//m_ComPort와 m_dlg.m_ComPort사이에 1의 차이가 있습니다.. 
	if (m_dlg.DoModal()==IDOK)
	{

		//if(m_CommPort_1.m_bPortOnOff){
		//	AfxMessageBox("연결되어 있음teaaast");
		//} else {

		//}
//		m_ComPort=m_dlg.m_ComPort+1;
//		m_BaudRate=atoi(m_dlg.m_BaudRate);
//		SerialPortSetUp(m_ComPort);
//		m_EditCom.Format("COM %d",m_ComPort);
//		m_EditBaud=m_dlg.m_BaudRate;
//		AfxMessageBox("연결되어 있음teaaast");
		//UpdateData(false);
	} else {
//		AfxMessageBox("test");
	}
}

void CYegrinStudioDlg::OnUpdateMenuitemSettup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CYegrinStudioDlg::OnMenuitemConnect() 
{
	// TODO: Add your command handler code here
	CString Msg;
	if(m_CommPort1.m_bPortOnOff){//연결이 되있는 상태
		m_CommPort1.ClosePort();
		g_ComPortCheck = FALSE;
		Msg.Format("%s 포트 연결 해재!",commsetup.ComPort);
		AfxMessageBox(Msg);
	} else {
		commsetup.ComPort.Format("%s",g_strCOM[0]);
		Msg.Format("%s 포트 연결 성공!",commsetup.ComPort);
		g_ComPortCheck = m_CommPort1.OpenPort( commsetup.ComPort, 38400, 1 );
		if(g_ComPortCheck)
			AfxMessageBox(Msg);
		
	}
}
/********************************************************************************
 기능 : 메시지를 받을때
 작성일:2005년 5월 15일	 
 ********************************************************************************/
/*
LONG CYegrinStudioDlg::OnRcvData(UINT port,LONG lParam)
{
	//BOOL m_CheckHexa=TRUE;
	//-->g_byRcvBuf[0][0]에는 수신 횟수가..
	//-->g_byRcvBuf[0][1 ~ 4096] 에는 수신 데이터가 있다.

	if (g_ComPortCheck) {//m_CommPort_1.m_bPortOnOff) {
		M("test");
		//--> 화면 컨트롤의 값을 얻어오기 위해.
		UpdateData( TRUE );

		//--> 수신된 바이트의 갯수가 있으므로..
		int nRcvSize = (INT)lParam;

		//--> 잘못된 값..
		if( nRcvSize <= 0 )		return -1;


		//--> Hexa 로 표시할 것인지..일반 텍스트로 표시할 것인지를 결정..
		//    변환하여.. 문자열로 넘기기..
		CString strData;
		//strData = ( m_CheckHexa )  ?  strRcvData2Hexa(nRcvSize ) :
		//							  strRcvData2Char(nRcvSize );
		//strData = strRcvData2Hexa(nRcvSize ) ;
		strData = strRcvData(nRcvSize ) ;

		//--> 정상적으로 처리되었음..
		m_RcvTest.ReplaceSel( strData );
	}
	return 1;
}
*/

LONG CYegrinStudioDlg::OnRxData(UINT port,LONG lParam)
{
	//BOOL m_CheckHexa=TRUE;
	//-->g_byRcvBuf[0][0]에는 수신 횟수가..
	//-->g_byRcvBuf[0][1 ~ 4096] 에는 수신 데이터가 있다.

	if (g_ComPortCheck) {//m_CommPort_1.m_bPortOnOff) {
		//--> 화면 컨트롤의 값을 얻어오기 위해.
		UpdateData( TRUE );

		//--> 수신된 바이트의 갯수가 있으므로..
		int nRcvSize = (INT)lParam;

		//--> 잘못된 값..
		if( nRcvSize <= 0 )		return -1;


		//--> Hexa 로 표시할 것인지..일반 텍스트로 표시할 것인지를 결정..
		//    변환하여.. 문자열로 넘기기..
		CString strData;
		//strData = ( m_CheckHexa )  ?  strRcvData2Hexa(nRcvSize ) :
		//							  strRcvData2Char(nRcvSize );
		//strData = strRcvData2Hexa(nRcvSize ) ;
		strData = strRcvData(nRcvSize ) ;

		/////////////////////////////////////////////////
		m_RcvTest.ReplaceSel( strData );
		
		//--> 정상적으로 처리되었음..
	}
	return 1;
}

void CYegrinStudioDlg::OnUpdateMenuitemConnect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
void CYegrinStudioDlg::OnButtonTest() 
{
	// TODO: Add your control notification handler code here
	CString Data;
	Data.Format("8000");
	CommInterface(1, "A0", "KD", Data);

}
