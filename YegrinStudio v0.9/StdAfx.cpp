// stdafx.cpp : source file that includes just the standard includes
//	YeginStudio.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

HWND hCommWnd , MyhCommWnd;

BYTE g_byRcvBuf[MAX_RECEIVE];
BYTE g_byRcvData[4];
BYTE g_bySendBuf[MAX_SEND];
BYTE SendBuf[MAX_FILE];

char	g_strBaud[5][10]={"9600","14400","19200","38400","57600"};
char	g_strCOM[5][10]={"COM1","COM2","COM3","COM4","COM5"};
char	g_strData[5][2]={"4","5","6","7","8"};
char	g_strPty[3][5]={"����","¦��","Ȧ��"};
char	g_strStop[3][5]={"1","1.5","2"};
BOOL	g_ComPortCheck;

CCommThread	m_CommPort1;	// Port 1

char rid[3]="A0";
CString		rd;
int		RcvSize;

CString CharHex(char str) //CString m_input)
{
	int      ii = 0;
	//unsigned char    str;
	CString  TempStr,ConvStr;

	TempStr.Empty();
	ConvStr.Empty();

	//ii  = m_input.GetLength();

	//AfxMessageBox(m_input);
	//for(int kk = 0;kk < ii;kk++)
	//{
		//str = m_input.GetAt(kk);
		TempStr.Format("%02X",str);
		//if(!(kk ==  0))
		//	if(!(kk%10))
		//		ConvStr = ConvStr + "\n"; 

		ConvStr = ConvStr + " " + TempStr;

	//}

	 return ConvStr; 
}
/********************************************************************************
��� : ������ ��ư ������ ó���ȴ�
�ۼ���:2005�� 5�� 15��	 
********************************************************************************/

BYTE byCode2AsciiValue( char cData )
{
	BYTE byAsciiValue;

	//--> '0' ~ '9' => 0 ~ 9
	if( ('0' <= cData) && (cData <= '9') )
	{
		byAsciiValue = cData - '0';
	}	//--> 'A' ~ 'F' => 10 ~ 15
	else if( ('A' <= cData) && (cData <= 'F') )
	{
		byAsciiValue = (cData - 'A') + 10;
	}	//--> 'a' ~ 'f' => 10 ~ 15
	else if( ('a' <= cData) && (cData <= 'f') )
	{
		byAsciiValue = (cData - 'a') + 10;
	}
	else	//--> �߸��� ����... 0 ���� ó��
	{
		byAsciiValue = 0;
	}

	//--> ��ȯ���� ��������..
	return byAsciiValue;

}

int nMakeSendCode_Hexa(CString strInputData, int xPortNo)
{
	//--> ���ڿ��� ���̸� ��..
 	int nStrLength = strInputData.GetLength();
 	
 	//--> ����Ʈ ������..�Է� ������ 1/3
 	int nLimit = (MAX_SEND - 1) * 3;
 	
 	//--> ���ڿ� ���̰� ���Ѱ����� ũ��..���� 2��
 	if( nStrLength >= nLimit )				return -2;

	//--> Clear Send Buf..������ ������� Ŭ����..0������ Ƚ�� �������� ���ǹǷ�..����
	for( int i=1; i<MAX_SEND; i++ )
	{
		g_bySendBuf[i] = NULL;
	}
 
 	BYTE byHigh, byLow;
 
 	//--> ���� �Է� ������..
 	int nBufPos = 1;
 
 	//--> �Է°��� �����ؼ�.. ����Ʈ ������ ó���ϱ�..
 	for(i=0; (i + 1)<nStrLength; i+=3 )
 	{
 		byHigh = byCode2AsciiValue( strInputData[i] );
 		byLow  = byCode2AsciiValue( strInputData[i + 1] );

		g_bySendBuf[nBufPos++] = (byHigh << 4) | byLow;
 	}
 
 	//--> ��������.
 	//�������� ������.. /3���� �ؾ��ϳ�?
 	int nNmg = nStrLength % 3;
 	
 	//--> ���� ��ȯ�� ����Ʈ ���� ��ü ������ ������ ����.. �� ������ ������..
 	//    ��..�̷� �������..����������..
 	int nSendSu = ( nNmg <= 1 )  ?  (nStrLength / 3) : (INT)((nStrLength + 1) / 3);
 
 
 	//--> ���� ��ȯ�� ����Ʈ ��..�ѱ��..
 	return nSendSu;
}

int nMakeSendCode( CString strInputData, int xPortNo )
{
	//--> ���ڿ��� ���̸� ��..
	int nStrLength = strInputData.GetLength();
	
	//--> ���ڿ� ���̰� ���Ѱ����� ũ��..���� 2��
	if( nStrLength >= MAX_SEND )			return -2;


	//--> Clear Send Buf..������ ������� Ŭ����..0������ Ƚ�� �������� ���ǹǷ�..����
	for( int i=1; i<MAX_SEND; i++ )
	{
		g_bySendBuf[i] = NULL;
	}

	//--> ���ڿ� ����... ��.. �ٸ� ���� ����� �����͵� ������..^^;;;
	for( i=0; i<nStrLength; i++ )
	{
		g_bySendBuf[i + 1] = strInputData[i];
	}
	
	//--> ��������... ���� ��ȯ�� �ڵ尹�� �ѱ�..
	return nStrLength;
}

int CommInterface(int rw, char *id, char *Command, CString Data)
{

	int nCount =0, nSendSu = 0;
	BYTE R=0x52;	// 'R'
	BYTE W=0x57;	// 'W'

	int		i=0, j=0;

	PROTOCOL SendData;
	BYTE SUM_HIGH, SUM_LOW;

	char SndData[MAX_PATH]="";

	if (g_ComPortCheck) {//COM ��Ʈ�� ���� ���� ���
		SndData[0]	= SendData.STX		= 0x02;	
		SndData[1]	= SendData.ID[0]	= id[0];
		SndData[2]	= SendData.ID[1]	= id[1];

		SndData[4]	= Command[0];
		SndData[5]	= Command[1];

		SendData.ETX= 0x03;

		if(rw == 0){//�б�
			SndData[3]	= R;
			
			SendData.SUM = SndData[1] + SndData[2] + SndData[3] + SndData[4] + SndData[5];
				
			SUM_HIGH	= (SendData.SUM >> 4) &0x0f;// & 0xf0)>>4;
			SUM_LOW		= SendData.SUM & 0x0f;

			SndData[6]	= SUM_HIGH	+ 0x30;
			SndData[7]	= SUM_LOW	+ 0x30;

			SndData[8]	= SendData.ETX;	
			nCount =nMakeSendCode( SndData, 1 );
		
			nSendSu = m_CommPort1.WriteComm( (&g_bySendBuf[1]), nCount );
		}
		if(rw == 1){//����	
			int DataLen		= Data.GetLength();
			CString DataStr;
			char *LocalData;
			DataStr.Format("%s",Data);
			LocalData		= DataStr.GetBuffer(DataStr.GetLength());

			SndData[3]	= W;
			SendData.SUM = SndData[1] + SndData[2] + SndData[3] + SndData[4] + SndData[5];

			for (i=6; i < (DataLen+6) ;i++){
					SndData[i]		= LocalData[j];
					SendData.SUM	+=SndData[i];
					j++;
			}
			SUM_HIGH			= (SendData.SUM >> 4) & 0x0f;// 0xf0)>>4;
			SUM_LOW				= SendData.SUM & 0x0f;

			SndData[DataLen+6]	= SUM_HIGH	+ 0x30;
			SndData[DataLen+7]	= SUM_LOW	+ 0x30;

			SndData[DataLen+8]	= SendData.ETX;	

			nCount =nMakeSendCode( SndData, 1 );
		
			nSendSu = m_CommPort1.WriteComm( (&g_bySendBuf[1]), nCount );
		}		
		//CString aaa;
		//aaa.Format("%s",g_bySendBuf);
		//AfxMessageBox(aaa);
		
	} else 
		::MessageBox(NULL,"No Open Port","Port Error",MB_OK);

	return nSendSu;
}

//----- ���Ű��� ��� ���ڿ��� ��ȯ�ؼ� �ѱ��.. �Լ� -----
CString strRcvData(int nRcvSize )
{
	//--> ��� �ڵ��� ǥ��.. 
	CString strData, reternData;
	//strData.Format( "%0d: ", g_byRcvData[0] );

	CString strTemp;
	BYTE byData[4];
	
	int i=0, j=0, stx=0, dataStart=0, etx=0;

	for(i=1 ; i<=nRcvSize ; i++) {
		if(g_byRcvData[i] == 0x02)
			stx			= i;
		if(g_byRcvData[i] == 0x52 || g_byRcvData[i] == 0x57  )
			dataStart	= i+2;
		if(g_byRcvData[i] == 0x03)
			etx			= i;
	}
	//--> �� ����Ʈ�� ���ڶ��� ��� �ڵ�� ǥ��..���� ó��.
	//dataStart �����Ͱ� ���۵Ǵ� �ּ�
	for( i=dataStart+1; i< etx-2; i++ )
	{
		
		//--> �ϳ��� ������..
		byData[j] = g_byRcvBuf[i] - 0x30;

		//--> ���ڸ� ��� �ڵ�..���� ���ڸ�..
		strTemp.Format( "%x", byData[j] );

		//M(strTemp);
		//--> ���� ���� ����Ĵ�.. �ٹٲ�..??...���� ������..
		strData += strTemp;		
		
		j++;
		for (int i=0; i<100000; i++);
	}

	//--> �ٹٲ�..���� �߰�..
	//strData += _T( "\r\n" );
	
	//--> �ٲ� ���ڿ� �ѱ��..
	return strData;
}

void MyAfxMessageBox(int count, BYTE *Data)
{
	char szBuf[MAX_PATH];
	for(int i=0 ; i < count ; i++){			
		sprintf(szBuf,"0x%02X| ", Data[i]); 
		AfxMessageBox(szBuf); 
	}
	AfxMessageBox(szBuf);
}