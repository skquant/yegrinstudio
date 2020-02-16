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
	//��Ʈ���� �ں��ڽ��� �� �������� �ִ´�.
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
//	m_ctlCob_Pty.AddString("¦��");
//	m_ctlCob_Pty.AddString("Ȧ��");

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

	if(g_ComPortCheck){ //����Ǿ� �ִٸ�...
		m_ctlEdt_RcvData.ReplaceSel("Connect Success\r\n");
		SetDlgItemText(IDC_BTN_CONNECT,"��  ��");
		m_ctlCob_Port.EnableWindow(FALSE);
		m_ctlCob_Baud.EnableWindow(FALSE);
		m_ctlCob_Data.EnableWindow(FALSE);
		m_ctlCob_Pty.EnableWindow(FALSE);
		m_ctlCob_Stop.EnableWindow(FALSE);
		GetDlgItem(IDC_EDT_SENDDATA)->SetFocus();
		GetDlgItem(IDC_BTN_SENDING)->EnableWindow(TRUE);
	} else{
		m_ctlEdt_RcvData.ReplaceSel("Not Connect\r\n");
		SetDlgItemText(IDC_BTN_CONNECT,"��  ��");
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
��� : ���� ��ư ������ ó���ȴ�
�ۼ���:2005�� 5�� 15��		 
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
		//���� ������� �б� ��������� Ȯ���Ͽ� ���� ����� ������ �Ѵ�.	
		BOOL bCheckRadio	= m_rCheckRadio.GetCheck();;
		
		SendData.STX		= 0x02; 		
		SendData.ID[0]		= 'A';
		SendData.ID[1]		= '0';
		//ID_HIGH				= SendData.ID & 
		SendData.ETX		= 0x03;			
		m_strCob_Command	= _T("");		
		m_ctlCob_Command.GetLBText(m_ctlCob_Command.GetCurSel(),m_strCob_Command );		
		//######################## STATIC #########################################
		//���� �����͸� ���� �ؾ��� ����
		//1. m_strEdt_SendData.GetLength() ���� ���ڿ� ���̸� �о�� �Ѵ�.
		//2. m_strCob_Command �� �о�� �Ѵ�.
		char SndData[MAX_PATH]="", ShowData[MAX_PATH]="", szBuf[MAX_PATH]="";;
		char *Command;//Command = (LPSTR)(LPCSTR)str; or Command=str.GetBuffer(str.GetLength());
		char *Data;
		CString CmdReadStr, CmdWriteStr, TestStr;
		//COMMAND �ڵ带 �д´�.
		CmdReadStr.Format("%s",m_strCob_Command);
		Command			= CmdReadStr.GetBuffer(CmdReadStr.GetLength());
		//AfxMessageBox(Command);
		if(bCheckRadio){
			//------------------------>�б� �̸�
			//�б� Command�� �������� ID�� ����� ������ �ƴ�, ���� ID�� �����̸� ����..
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
			//--> ��Ʈ�� ���� ���..��Ʈ�� �������� ������.. 0...
			//    ���ϰ��� ��Ʈ�� ��µ� ����.					
			nSendSu = m_CommPort1.WriteComm( (&g_bySendBuf[1]), nCount );			

		} else {				//------------------------>���� �̸�		
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
			//--> ��Ʈ�� ���� ���..��Ʈ�� �������� ������.. 0...
			//    ���ϰ��� ��Ʈ�� ��µ� ����.					
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
//----- ���Ű��� ��� ���ڿ��� ��ȯ�ؼ� �ѱ��.. �Լ� -----
CString CSetupDialog::strRcvData2Hexa(int nRcvSize )
{
	//--> ��� �ڵ��� ǥ��.. 
	CString strData;
	strData.Format( "%0d: ", g_byRcvBuf[0] );

	CString strTemp;
	BYTE byData;

	//--> �� ����Ʈ�� ���ڶ��� ��� �ڵ�� ǥ��..���� ó��.
	for( int i=1; i<=nRcvSize; i++ )
	{
		//--> �ϳ��� ������..
		byData = g_byRcvBuf[i];

		//--> ���ڸ� ��� �ڵ�..���� ���ڸ�..
		strTemp.Format( "0x%02X| ", byData );

		//--> ���� ���� ����Ĵ�.. �ٹٲ�..??...���� ������..
		strData += strTemp;		
		
		for (int i=0; i<100000; i++);
	}

	//--> �ٹٲ�..���� �߰�..
	strData += _T( "\r\n" );

	//--> �ٲ� ���ڿ� �ѱ��..
	return strData;
}

//----- ���Ű��� �Ϲ��ؽ�Ʈ ���ڿ��� ��ȯ�ؼ� �ѱ��.. �Լ� -----
CString CSetupDialog::strRcvData2Char(int nRcvSize )
{
	//--> ���� Ƚ��..
	CString strData;
	strData.Format( "%5d : ", g_byRcvBuf[0] );

	CString strTemp;
	BYTE byData;

	//--> ���� ������ŭ..
	for( int i=1; i<=nRcvSize; i++ )
	{
		byData = g_byRcvBuf[i];

		//byData �� ���̸�.. ���� ó���ؾ� �Ѵ�..���ڿ��� �Ⱥ��̰ŵ��..
		if( byData == NULL )
		{
			strData += _T( " " );  //--> �ι��ڴ�..�������� ��ü..
			continue;
		}

		//--> char ������..
		strTemp.Format( "%c", byData );
		strData += strTemp;
	}

	//--> �� �ڿ��� �ٹٲ�..������ ���ؼ���...
	strData += _T( "\r\n" );

	//--> ��ȯ�� ���ڿ� �ѱ�.
	return strData;
}

/********************************************************************************
 ��� : �޽����� ������
 �ۼ���:2005�� 5�� 15��	 
 ********************************************************************************/
/*
LONG CSetupDialog::OnRxData(UINT port,LONG lParam)
{
	//BOOL m_CheckHexa=TRUE;
	//-->g_byRcvBuf[0][0]���� ���� Ƚ����..
	//-->g_byRcvBuf[0][1 ~ 4096] ���� ���� �����Ͱ� �ִ�.

	if (g_ComPortCheck) {//m_CommPort_1.m_bPortOnOff) {
		//--> ȭ�� ��Ʈ���� ���� ������ ����.
		UpdateData( TRUE );

		//--> ���ŵ� ����Ʈ�� ������ �����Ƿ�..
		int nRcvSize = (INT)lParam;

		//--> �߸��� ��..
		if( nRcvSize <= 0 )		return -1;


		//--> Hexa �� ǥ���� ������..�Ϲ� �ؽ�Ʈ�� ǥ���� �������� ����..
		//    ��ȯ�Ͽ�.. ���ڿ��� �ѱ��..
		CString strData;
		//strData = ( m_CheckHexa )  ?  strRcvData2Hexa(nRcvSize ) :
		//							  strRcvData2Char(nRcvSize );
		//strData = strRcvData2Hexa(nRcvSize ) ;
		strData = strRcvData(nRcvSize ) ;

		/////////////////////////////////////////////////
		m_ctlEdt_RcvData.ReplaceSel( strData );
		
		//--> ���������� ó���Ǿ���..
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
	//if(m_CommPort_1.m_bPortOnOff){//������ ���ִ� ����		
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
