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
char	g_strPty[3][5]={"없음","짝수","홀수"};
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
기능 : 보내기 버튼 눌르면 처리된당
작성일:2005년 5월 15일	 
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
	else	//--> 잘못된 값을... 0 으로 처리
	{
		byAsciiValue = 0;
	}

	//--> 변환값을 리턴하죠..
	return byAsciiValue;

}

int nMakeSendCode_Hexa(CString strInputData, int xPortNo)
{
	//--> 문자열의 길이를 얻어서..
 	int nStrLength = strInputData.GetLength();
 	
 	//--> 바이트 갯수는..입력 갯수의 1/3
 	int nLimit = (MAX_SEND - 1) * 3;
 	
 	//--> 문자열 길이가 제한값보다 크면..오류 2번
 	if( nStrLength >= nLimit )				return -2;

	//--> Clear Send Buf..데이터 저장버퍼 클리어..0번지는 횟수 저장으로 사용되므로..제외
	for( int i=1; i<MAX_SEND; i++ )
	{
		g_bySendBuf[i] = NULL;
	}
 
 	BYTE byHigh, byLow;
 
 	//--> 버퍼 입력 포지션..
 	int nBufPos = 1;
 
 	//--> 입력값을 구분해서.. 바이트 단위로 처리하기..
 	for(i=0; (i + 1)<nStrLength; i+=3 )
 	{
 		byHigh = byCode2AsciiValue( strInputData[i] );
 		byLow  = byCode2AsciiValue( strInputData[i + 1] );

		g_bySendBuf[nBufPos++] = (byHigh << 4) | byLow;
 	}
 
 	//--> 오류없음.
 	//데이터의 갯수를.. /3으로 해야하나?
 	int nNmg = nStrLength % 3;
 	
 	//--> 실제 변환된 바이트 수는 전체 데이터 갯수에 따라서.. 잘 생각해 보세여..
 	//    왜..이런 연산식이..나오는지는..
 	int nSendSu = ( nNmg <= 1 )  ?  (nStrLength / 3) : (INT)((nStrLength + 1) / 3);
 
 
 	//--> 실제 변환된 바이트 수..넘기기..
 	return nSendSu;
}

int nMakeSendCode( CString strInputData, int xPortNo )
{
	//--> 문자열의 길이를 얻어서..
	int nStrLength = strInputData.GetLength();
	
	//--> 문자열 길이가 제한값보다 크면..오류 2번
	if( nStrLength >= MAX_SEND )			return -2;


	//--> Clear Send Buf..데이터 저장버퍼 클리어..0번지는 횟수 저장으로 사용되므로..제외
	for( int i=1; i<MAX_SEND; i++ )
	{
		g_bySendBuf[i] = NULL;
	}

	//--> 문자열 복사... 흠.. 다른 좋은 방법이 있을것도 같은데..^^;;;
	for( i=0; i<nStrLength; i++ )
	{
		g_bySendBuf[i + 1] = strInputData[i];
	}
	
	//--> 오류없음... 실제 변환된 코드갯수 넘김..
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

	if (g_ComPortCheck) {//COM 포트가 동작 중일 경우
		SndData[0]	= SendData.STX		= 0x02;	
		SndData[1]	= SendData.ID[0]	= id[0];
		SndData[2]	= SendData.ID[1]	= id[1];

		SndData[4]	= Command[0];
		SndData[5]	= Command[1];

		SendData.ETX= 0x03;

		if(rw == 0){//읽기
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
		if(rw == 1){//쓰기	
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

//----- 수신값을 헥사 문자열로 변환해서 넘기기.. 함수 -----
CString strRcvData(int nRcvSize )
{
	//--> 헥사 코드라는 표시.. 
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
	//--> 한 바이트를 두자라의 헥사 코드로 표시..공백 처리.
	//dataStart 데이터가 시작되는 주소
	for( i=dataStart+1; i< etx-2; i++ )
	{
		
		//--> 하나씩 꺼내서..
		byData[j] = g_byRcvBuf[i] - 0x30;

		//--> 두자리 헥사 코드..공백 한자리..
		strTemp.Format( "%x", byData[j] );

		//M(strTemp);
		//--> 일정 갯수 출력후는.. 줄바꿈..??...아직 안했음..
		strData += strTemp;		
		
		j++;
		for (int i=0; i<100000; i++);
	}

	//--> 줄바꿈..문자 추가..
	//strData += _T( "\r\n" );
	
	//--> 바뀐 문자열 넘기기..
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