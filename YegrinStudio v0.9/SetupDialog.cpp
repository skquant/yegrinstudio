// SetupDialog.cpp : implementation file
//

#include "stdafx.h"
#include "yegrinstudio.h"
#include "SetupDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDialog dialog


CSetupDialog::CSetupDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDialog)
		// NOTE: the ClassWizard will add member initialization here
	m_strEdt_RvcData = _T("");
	m_strEdt_SendData = _T("");
	m_strCbo_Port = _T("");
	m_strCbo_Baud = _T("");
	m_strEdt_SendHis = _T("");
	m_strCob_Command = _T("");
	m_CheckHexa = FALSE;
	//}}AFX_DATA_INIT
}


void CSetupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_CHECK_HEXA, m_ctlCheckHexa);
	DDX_Control(pDX, IDC_READ_RADIO, m_rCheckRadio);
	DDX_Control(pDX, IDC_EDT_SENDHIS, m_ctlEdt_SendHis);
	DDX_Control(pDX, IDC_EDT_RVCDATA, m_ctlEdt_RcvData);
	DDX_Control(pDX, IDC_EDT_SENDDATA, m_ctlEdt_SendData);
	DDX_Control(pDX, IDC_COB_STOP, m_ctlCob_Stop);
	DDX_Control(pDX, IDC_COB_PTY, m_ctlCob_Pty);
	DDX_Control(pDX, IDC_COB_PORT, m_ctlCob_Port);
	DDX_Control(pDX, IDC_COB_DATA, m_ctlCob_Data);
	DDX_Control(pDX, IDC_COB_BAUD, m_ctlCob_Baud);
	DDX_Control(pDX, IDC_CMD_COMBO, m_ctlCob_Command);
	DDX_Text(pDX, IDC_EDT_RVCDATA, m_strEdt_RvcData);
	DDX_Text(pDX, IDC_EDT_SENDDATA, m_strEdt_SendData);
	DDX_CBString(pDX, IDC_COB_PORT, m_strCbo_Port);
	DDX_CBString(pDX, IDC_COB_BAUD, m_strCbo_Baud);
	DDX_Text(pDX, IDC_EDT_SENDHIS, m_strEdt_SendHis);
	DDX_CBString(pDX, IDC_CMD_COMBO, m_strCob_Command);
	DDX_Check(pDX, IDC_CHECK_HEXA, m_CheckHexa);
		
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDialog, CDialog)
	//{{AFX_MSG_MAP(CSetupDialog)
		// NOTE: the ClassWizard will add message map macros here
	ON_BN_CLICKED(IDC_BTN_SENDING, OnBtnSending)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_READ_RADIO, OnReadRadio)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_WRITE_RADIO, OnWriteRadio)
	//}}AFX_MSG_MAP
	//ON_MESSAGE(WM_COMM_READ,OnRxData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDialog message handlers
BOOL CSetupDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	UpdateData(TRUE);
	//포트설정 코보박스에 들어갈 내용을들 넣는다.
	m_ctlCob_Baud.AddString(g_strBaud[0]);
	m_ctlCob_Baud.AddString(g_strBaud[1]);
	m_ctlCob_Baud.AddString(g_strBaud[2]);
	m_ctlCob_Baud.AddString(g_strBaud[3]);
	m_ctlCob_Baud.AddString(g_strBaud[4]);

	m_ctlCob_Port.AddString(g_strCOM[0]);
	m_ctlCob_Port.AddString(g_strCOM[1]);
	m_ctlCob_Port.AddString(g_strCOM[2]);
	m_ctlCob_Port.AddString(g_strCOM[3]);
	m_ctlCob_Port.AddString(g_strCOM[4]);

	m_ctlCob_Data.AddString(g_strData[0]);
	m_ctlCob_Data.AddString(g_strData[1]);
	m_ctlCob_Data.AddString(g_strData[2]);
	m_ctlCob_Data.AddString(g_strData[3]);
	m_ctlCob_Data.AddString(g_strData[4]);

	m_ctlCob_Pty.AddString(g_strPty[0]);
//	m_ctlCob_Pty.AddString("짝수");
//	m_ctlCob_Pty.AddString("홀수");

	m_ctlCob_Stop.AddString(g_strStop[0]);
	m_ctlCob_Stop.AddString(g_strStop[1]);
	m_ctlCob_Stop.AddString(g_strStop[2]);

	m_ctlCob_Command.AddString("TR");	m_ctlCob_Command.AddString("IV");
	m_ctlCob_Command.AddString("BK");	m_ctlCob_Command.AddString("NW");
	m_ctlCob_Command.AddString("PD");	m_ctlCob_Command.AddString("ML");
	m_ctlCob_Command.AddString("FC");	m_ctlCob_Command.AddString("MP");
	m_ctlCob_Command.AddString("MS");	m_ctlCob_Command.AddString("RS");
	m_ctlCob_Command.AddString("TC");	m_ctlCob_Command.AddString("LD");
	m_ctlCob_Command.AddString("MD");	m_ctlCob_Command.AddString("CA");
	m_ctlCob_Command.AddString("CB");	m_ctlCob_Command.AddString("CC");
	m_ctlCob_Command.AddString("LA");	m_ctlCob_Command.AddString("LB");
	m_ctlCob_Command.AddString("LC");	m_ctlCob_Command.AddString("DA");
	m_ctlCob_Command.AddString("DB");	m_ctlCob_Command.AddString("DC");
	m_ctlCob_Command.AddString("KD");	m_ctlCob_Command.AddString("TD");
	m_ctlCob_Command.AddString("SN");	m_ctlCob_Command.AddString("M0");
	/////////////////////////////////////////////
	m_ctlCob_Baud.SetCurSel(3);
	m_ctlCob_Port.SetCurSel(0);
	m_ctlCob_Data.SetCurSel(4);
	m_ctlCob_Pty.SetCurSel(0);
	m_ctlCob_Stop.SetCurSel(0);
	m_ctlCob_Command.SetCurSel(0);
	//CButton *pCheck;
	//pCheck=(CButton *)GetDlgItem(IDC_READ_RADIO);
	//pCheck->SetCheck(TRUE);
	m_rCheckRadio.SetCheck(TRUE);
	m_ctlCheckHexa.SetCheck(TRUE);
	m_CheckHexa = FALSE;

	if(g_ComPortCheck){ //연결되어 있다면...
		m_ctlEdt_RcvData.ReplaceSel("Connect Success\r\n");
		SetDlgItemText(IDC_BTN_CONNECT,"해  제");
		m_ctlCob_Port.EnableWindow(FALSE);
		m_ctlCob_Baud.EnableWindow(FALSE);
		m_ctlCob_Data.EnableWindow(FALSE);
		m_ctlCob_Pty.EnableWindow(FALSE);
		m_ctlCob_Stop.EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_SENDDATA)->SetFocus();
		GetDlgItem(IDC_BTN_SENDING)->EnableWindow(TRUE);
	} else{
		m_ctlEdt_RcvData.ReplaceSel("Not Connect\r\n");
		SetDlgItemText(IDC_BTN_CONNECT,"연  결");
		m_ctlCob_Port.EnableWindow(TRUE);
		m_ctlCob_Baud.EnableWindow(TRUE);
		m_ctlCob_Data.EnableWindow(TRUE);
		m_ctlCob_Pty.EnableWindow(TRUE);
		m_ctlCob_Stop.EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SENDING)->EnableWindow(FALSE);
	} 
	hCommWnd = m_hWnd;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/*
void CSetupDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
*/
/*******************************************************************************
기능 : 연결 버튼 눌르면 처리된당
작성일:2005년 5월 15일		 
********************************************************************************/
void CSetupDialog::OnBtnConnect() 
{
}

void CSetupDialog::OnBtnSending() 
{
	// TODO: Add your control notification handler code here
	int nCount =0, nSendSu = 0;
	
	if (g_ComPortCheck) {
		UpdateData(TRUE);
		PROTOCOL SendData;
		CString x;
	//	DWORD Size;
		int		i=0, j=0;		
		// PowerPack Serial Communication Protocol start
		int len = m_strEdt_SendData.GetLength();			
		//######################## STATIC #########################################
		BYTE R=0x52;	// 'R'
		BYTE W=0x57;	// 'W'
		BYTE SUM_HIGH, SUM_LOW;
		//BYTE ID_HIGH, ID_LOW;
		//쓰기 명령인지 읽기 명령인지를 확인하여 장비로 명령을 보내야 한다.	
		BOOL bCheckRadio	= m_rCheckRadio.GetCheck();;
		
		SendData.STX		= 0x02; 		
		SendData.ID[0]		= 'A';
		SendData.ID[1]		= '0';
		//ID_HIGH				= SendData.ID & 
		SendData.ETX		= 0x03;			
		m_strCob_Command	= _T("");		
		m_ctlCob_Command.GetLBText(m_ctlCob_Command.GetCurSel(),m_strCob_Command );		
		//######################## STATIC #########################################
		//가변 데이터를 위해 해야할 내용
		//1. m_strEdt_SendData.GetLength() 통한 문자열 길이를 읽어야 한다.
		//2. m_strCob_Command 을 읽어야 한다.
		char SndData[MAX_PATH]="", ShowData[MAX_PATH]="", szBuf[MAX_PATH]="";;
		char *Command;//Command = (LPSTR)(LPCSTR)str; or Command=str.GetBuffer(str.GetLength());
		char *Data;
		CString CmdReadStr, CmdWriteStr, TestStr;
		//COMMAND 코드를 읽는다.
		CmdReadStr.Format("%s",m_strCob_Command);
		Command			= CmdReadStr.GetBuffer(CmdReadStr.GetLength());
		//AfxMessageBox(Command);
		if(bCheckRadio){
			//------------------------>읽기 이면
			//읽기 Command를 날릴때는 ID를 빼고는 가변이 아님, 추후 ID가 가변이면 수정..
			SndData[0]	= SendData.STX;	
			SndData[1]	= SendData.ID[0];
			SndData[2]	= SendData.ID[1];
			SndData[3]	= R;
			SndData[4]	= Command[0];
			SndData[5]	= Command[1];					
			SendData.SUM = SndData[1] + SndData[2] + SndData[3] + SndData[4] + SndData[5];
				
			SUM_HIGH	= (SendData.SUM >> 4) & 0x0f;
			SUM_LOW		= SendData.SUM & 0x0f;

			SndData[6]	= SUM_HIGH	+ 0x30;
			SndData[7]	= SUM_LOW	+ 0x30;

			SndData[8]	= SendData.ETX;	
			m_strEdt_SendData = _T("");
			UpdateData(FALSE);		
			
			//sprintf(szBuf,"0x%02X|", SndData[1]); 
			//AfxMessageBox(szBuf); 
			for(i=0 ; i < 9 ; i++){			
				sprintf(szBuf,"0x%02X| ", SndData[i]);

				//AfxMessageBox(szBuf); 
				strcat(ShowData, szBuf);			
			}
			nCount = nMakeSendCode( SndData, 1 );
			//M(SndData);
			//CString aaa;
			//aaa.Format("%d",nCount);
			//M(aaa);
			//--> 포트로 실제 출력..포트가 열려있지 않으면.. 0...
			//    리턴값은 포트로 출력된 갯수.					
			nSendSu = m_CommPort1.WriteComm( (&g_bySendBuf[1]), nCount );			

		} else {				//------------------------>쓰기 이면		
			CmdWriteStr.Format("%s",m_strEdt_SendData);
			M(CmdWriteStr);
			Data		= CmdWriteStr.GetBuffer(CmdWriteStr.GetLength());
			int DataLen	= CmdWriteStr.GetLength();		
			//CString test;		test.Format("%d", DataLen);		AfxMessageBox(test);		
			SndData[0]	= SendData.STX;	
			SndData[1]	= SendData.ID[0];
			SndData[2]	= SendData.ID[1];
			SndData[3]	= W;
			SndData[4]	= Command[0];
			SndData[5]	= Command[1];
			SendData.SUM = SndData[1] + SndData[2] + SndData[3] + SndData[4] + SndData[5];

			CString str, test;
			for (i=6; i < (DataLen+6) ;i++){
			//for (i=(DataLen+6); 6 < i ;i--){					
					SndData[i]		= Data[j];
					SendData.SUM	+=SndData[i];
					j++;
			}
			//AfxMessageBox(szBuf);

			SUM_HIGH			= (SendData.SUM>>4) & 0x0f;// 0xf0;//)>>4;
			SUM_LOW				= SendData.SUM & 0x0f;
	
			SndData[DataLen+6]	= SUM_HIGH	+ 0x30;
			SndData[DataLen+7]	= SUM_LOW	+ 0x30;
			SndData[DataLen+8]	= SendData.ETX;	
			
			m_strEdt_SendData = _T("");
			UpdateData(FALSE);
						
			nCount =nMakeSendCode( SndData, 1 );
			//--> 포트로 실제 출력..포트가 열려있지 않으면.. 0...
			//    리턴값은 포트로 출력된 갯수.					
			nSendSu = m_CommPort1.WriteComm( (&g_bySendBuf[1]), nCount );

			//MyAfxMessageBox(nCount, &g_bySendBuf[1]);

			for(i=0 ; i < DataLen+9 ; i++){			
				sprintf(szBuf,"0x%02X| ", SndData[i]); 
				//AfxMessageBox(szBuf); 
				strcat(ShowData, szBuf);			
			}
			//AfxMessageBox(STRTEST);
		}
		//###########################################################################
		// PowerPack Serial Communication Protocol end
		strcat(ShowData, "\r\n");
		m_ctlEdt_SendHis.ReplaceSel(ShowData);
		m_ctlEdt_SendData.SetFocus();

		
	} else MessageBox("No Open Port","Port Error",MB_OK);
}
//----- 수신값을 헥사 문자열로 변환해서 넘기기.. 함수 -----
CString CSetupDialog::strRcvData2Hexa(int nRcvSize )
{
	//--> 헥사 코드라는 표시.. 
	CString strData;
	strData.Format( "%0d: ", g_byRcvBuf[0] );

	CString strTemp;
	BYTE byData;

	//--> 한 바이트를 두자라의 헥사 코드로 표시..공백 처리.
	for( int i=1; i<=nRcvSize; i++ )
	{
		//--> 하나씩 꺼내서..
		byData = g_byRcvBuf[i];

		//--> 두자리 헥사 코드..공백 한자리..
		strTemp.Format( "0x%02X| ", byData );

		//--> 일정 갯수 출력후는.. 줄바꿈..??...아직 안했음..
		strData += strTemp;		
		
		for (int i=0; i<100000; i++);
	}

	//--> 줄바꿈..문자 추가..
	strData += _T( "\r\n" );

	//--> 바뀐 문자열 넘기기..
	return strData;
}

//----- 수신값을 일반텍스트 문자열로 변환해서 넘기기.. 함수 -----
CString CSetupDialog::strRcvData2Char(int nRcvSize )
{
	//--> 수신 횟수..
	CString strData;
	strData.Format( "%5d : ", g_byRcvBuf[0] );

	CString strTemp;
	BYTE byData;

	//--> 수신 갯수만큼..
	for( int i=1; i<=nRcvSize; i++ )
	{
		byData = g_byRcvBuf[i];

		//byData 가 널이면.. 따로 처리해야 한다..문자열이 안보이거든요..
		if( byData == NULL )
		{
			strData += _T( " " );  //--> 널문자는..공백으로 대체..
			continue;
		}

		//--> char 형으로..
		strTemp.Format( "%c", byData );
		strData += strTemp;
	}

	//--> 맨 뒤에는 줄바꿈..다음을 위해서리...
	strData += _T( "\r\n" );

	//--> 변환된 문자열 넘김.
	return strData;
}

/********************************************************************************
 기능 : 메시지를 받을때
 작성일:2005년 5월 15일	 
 ********************************************************************************/
/*
LONG CSetupDialog::OnRxData(UINT port,LONG lParam)
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
		m_ctlEdt_RcvData.ReplaceSel( strData );
		
		//--> 정상적으로 처리되었음..
	}
	return 1;
}
*/
void CSetupDialog::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_strEdt_SendHis = _T("");
	UpdateData(FALSE);
}

void CSetupDialog::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_strEdt_RvcData = _T("");
	UpdateData(FALSE);
}


void CSetupDialog::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	//if(m_CommPort_1.m_bPortOnOff){//연결이 되있는 상태		
	//	m_CommPort_1.ClosePort();
	//}
	//DestroyWindow();
}

void CSetupDialog::OnReadRadio() 
{
	// TODO: Add your control notification handler code here
	//AfxMessageBox(STRTEST);
}

void CSetupDialog::OnWriteRadio() 
{
	// TODO: Add your control notification handler code here
	
}
