#include "stdafx.h"
#include "CommThread.h"

//	Message�� ���� Window Handle
//	�� ũ������ ����ϴ� �������� HWND hCommWnd = this->m_hWnd�� ������ �ش� 

extern HWND hCommWnd;
extern HWND MyhCommWnd;

CQueue::CQueue()
{
	Clear();
}

//	Queue Buffer�� ���� �������� ������ ����ų Position
//	�� �ʱ�ȭ�ϰ� Queue����� Buffer�� 0���� �ʱ�ȭ �Ѵ� 
//	memset()�Լ��� buff�迭�� BUFF_SIZEũ�⸸ŭ 0���� ä���

void CQueue::Clear()
{
	m_iHead = m_iTail = 0;
	memset(buff,0,BUFF_SIZE);
}

//	Queue�� ��� �ִ� �ڷ� ������ Return�Ѵ� 
//	BUFF_SIZE % BUFF_SIZE�� ���� BUFF_SIZE���� ���� �ǰ� 
//	m_intHead - mintTail ��� ���� return�ϰ� �ȴ�.
//	��, ������ ũ�� �������� ��ȭ�� ������ ������ �˼� �ִ� 

int CQueue::GetSize()
{	
	return (m_iHead - m_iTail + BUFF_SIZE) % BUFF_SIZE;
}

//	Queue�� 1 byte�� �ִ´� 
//	[1]	ó���� Queue Buffer�� �����Ͱ�  �� á���� �˻�
//	[2] Queue Buffer�� 1 byte�� �����ϰ� m_iHead Position�� ������Ų��
//	[3] ������ �����ڿ� ���� m_intHead ũ�Ⱑ BUFF_SIZE���� ũ�� 0����
//		Clear�Ǹ� BUFF_SIZEũ�⸦ ������������ ��ȭ�� ���� 

BOOL CQueue::PutByte(BYTE byte)
{
	if(GetSize() == (BUFF_SIZE-1)) return FALSE;
	buff[m_iHead++] = byte;
	m_iHead %= BUFF_SIZE;

	return TRUE;
}

//	Queue�� 1 byte�� ������ 
//	[1]	ó���� Queue Buffer�� �����Ͱ�  �� á���� �˻�
//	[2] Queue Buffer�� 1 byte�� ����Ʈ �Ű����� ����Ű�� ���� �����ϰ�
//		m_iTail Position�� ������Ų��
//	[3] ������ �����ڿ� ���� m_intTail ũ�Ⱑ BUFF_SIZE���� ũ�� 0����
//		Clear�Ǹ� BUFF_SIZEũ�⸦ ������������ ��ȭ�� ���� 

BOOL CQueue::GetByte(BYTE* pbyte)
{
	if(GetSize() == 0) return FALSE;
	*pbyte = buff[m_iTail++];
	m_iTail %= BUFF_SIZE;

	return TRUE;
}

//#############################################################################
// ��Ʈ sPortName�� dwBaud �ӵ��� ����.
// ThreadWatchComm �Լ����� ��Ʈ�� ���� ������ �� MainWnd�� �˸���
// ���� WM_COMM_READ�޽����� ������ ���� ���� wPortID���� ���� �޴´�.
//#############################################################################

CCommThread::CCommThread()
{
	m_intInQueue = 4096;
	m_intOutQueue = 4096;
	m_bPortOnOff = false;
}

//#############################################################################

//								Comm 1 Open

//#############################################################################

BOOL CCommThread::OpenPort(CString sPortName, DWORD dwBaud, WORD wPortID)
{
	COMMTIMEOUTS	timeouts;
	DCB				dcb;
	DWORD			dwThreadID;
	m_bPortOnOff = OFF;
	m_wPortID	= wPortID;

/******************************************************************************
	overlapped structure ���� �ʱ�ȭ.

	typedef struct_OVERLAPPED{
		DWORD	Internal;		
		DWORD	InternalHigh;
		DWORD	Offset;			- File���� �б� ������ ��ġ�� ���� 32��Ʈ�� 
		DWORD	OffsetHigh;
		HANDLE	hEvent;
	}OVERLAPPED;

	Internal...� üü�� ����ϵ��� ����Ǿ� �ִ�
	InternalHigh...� üü�� ����ϵ��� ����Ǿ� �ִ� 	
	Offset...File���� �б� ������ ��ġ�� ���� 32��Ʈ��. ȣ�� ���μ����� ReadFile
			 �Ǵ� WriteFile �Լ��� ȣ���ϱ� ���� �� ����� ���� �����־�� �Ѵ�
			 ���ӵ� �������� ��� ��ġ�κ��� �аų� �̵鿡 ������ �̸���� ���� 
			 0 �� �Ǿ�� �Ѵ� 
	Offset...File���� �б� ������ ��ġ�� ���� 32��Ʈ��. ȣ�� ���μ����� ReadFile
			 �Ǵ� WriteFile �Լ��� ȣ���ϱ� ���� �� ����� ���� �����־�� �Ѵ�
			 ���ӵ� �������� ��� ��ġ�κ��� �аų� �̵鿡 ������ �̸���� ���� 
			 0 �� �Ǿ�� �Ѵ� 	
	hEvent...�о ������ ����Ǿ��� �� ��ȣ�� �޴� ���·� ������ �־�� �� 
			 Event�� Handle. ȣ�� ���μ����� ReadFile, WriteFile, ConnectNamePipe
			 �Ǵ� TransactNamedPipe �Լ��� ȣ���ϱ� ���� �� ����� ���� ���� 
			 �־�� �Ѵ� 
*******************************************************************************
	CreateEvent()

	SetEvent�Լ��� ����ؼ� ���α׷��� ���� ��ȣ �Ǵ� ���ȣ ���°� �ɼ� �ִ�
	�������α׷��� �̺�Ʈ�� ����ؼ� Ȱ������ ������� �������� ����ȭ�� �����Ѵ� 

******************************************************************************/
	m_osRead.Offset = 0;
	m_osRead.OffsetHigh = 0;
	if (!(m_osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))	
		return FALSE;

	m_osWrite.Offset = 0;
	m_osWrite.OffsetHigh = 0;
	if (!(m_osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)))
		return FALSE;
/******************************************************************************
	[1]	��Ʈ�� ����

  	m_sPortName...�������ϴ� Device Port String���� ����
	GENERIC_READ | GENERIC_WRITE...Device���� Access�� ��弳��,
	�а� ���� ��� ����
	0...File�� Only Read �� Read/Write ���� Device File���� �ǹ� ����
	NULL...File�� ������ ���� Device File������ ��� ����
	OPEN_EXISTING...File�� �����Ҷ� ����,�����Ϳ� +,�̹������Ұ�츸 ���� 
	�� ���� Device File������ ������ ������ ���� ���ϹǷ� OPEN_EXISTING
	FILE_ATTRIBUTE_NORMAL...�Ϲ� File
	FILE_FLAG_OVERLAPPED...Device Buffer���� �б⳪ ���Ⱑ ������ �˷��ش�
	�а��� �Լ����� OVERAPPED structure�� �̿��Ͽ� Overapped Read/Write ���ش� 
	NULL...NT������ ������ 
******************************************************************************/
	m_sPortName = sPortName;	// <<---- COM1,COM2
	m_hComm = CreateFile(	
				m_sPortName, 
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
				NULL
			  );
	// OK...Handle return, NO...INVALID_HANDLE_VALUE(-1) return
	if (m_hComm == (HANDLE)INVALID_HANDLE_VALUE) return FALSE;
/******************************************************************************
	[2] ��Ʈ ���¸� ��������

	����ϰ��� �ϴ� Event���� �����ϰ� 0 �ϰ�� ��� Event�� ��ҵȴ� 

  	EV_BREAK - A break was detected on input. 
	EV_CTS	- The CTS (clear-to-send) signal changed state. 
	EV_DSR	- The DSR (data-set-ready) signal changed state. 
	EV_ERR	- A line-status error occurred.
			  Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY. 
	EV_RING	- A ring indicator was detected. 
	EV_RLSD	- The RLSD (receive-line-signal-detect) signal changed state. 
	EV_RXCHAR - A character was received and placed in the input buffer. 
	EV_RXFLAG - The event character was received and placed in the input buffer.
				The event character is specified in the device��s DCB structure,
				which is applied to a serial port by using the SetCommState function. 
	EV_TXEMPTY - The last character in the output buffer was sent. 
******************************************************************************/
	SetCommMask( 
		m_hComm,EV_RXCHAR
	);	
/******************************************************************************
	[3] ����� Queue�� ũ�⸦ ������
	
	�ԷµǴ� Buffer�� ũ��� �ְ� �޴� �������� �翡 ���� �����ǹǷ� DialogBox
	���� ���� �Ҽ� �ֵ��� int�� ������ ����Ѵ�
	�Ϲ������� 4096(80*25*4)�� ũ�⸦ �����°� ���� 
******************************************************************************/
	SetupComm( 
		m_hComm,
		m_intInQueue,
		m_intOutQueue
	);	
/******************************************************************************
	[4] ����� Buffer�� ������ �ʱ�ȭ ����

	ó�� Buffer�� �����ϸ� Serial Port�� ����ϰ� �ִ� ��� ����� �����͸�
	�����ϰ� ���� �� ���� �غ� �ؾ��Ѵ� 

	PURGE_TXABORT - Overapped �����۾��� ��� 
	PURGE_RXABORT - Overapped �����۾��� ���
	PURGE_TXCLEAR - ��� Buffer�� Clear�Ѵ�
	PURGE_RXCLEAR - �Է� Buffer�� Clear�Ѵ�
******************************************************************************/
	PurgeComm( 
		m_hComm,					
		PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR
	);
/******************************************************************************
	[5] Buffer���� �а� ���� �ð� timeout �����Ѵ�

	���� �б� ���� Overapped I/O�� ���� Timeout������ ������ �־�� �� �ܰ��Դϴ�
	MFC���� Serial Port�� Timeout���� �������ֱ� ���� ����ϴ� ����ü��
	COMMTIMEOUT�Դϴ�.

	typedef	struct_COMMTIMEOUTS{
				DWORD	ReadIntervalTimeout;			[1]
				DWORD	ReadTotalTimeoutMultiplier;		[2]
				DWORD	ReadTotalTimeoutConstant;		[3]
				DWORD	WriteTotalTimeoutMultiplier;	[4]
				DWORD	WriteTotalTimeoutConstant;		[5]
			}COMMTIMEOUTS,*LPCOMMTIMEOUTS;

[1]	Data��  ���� �� �� ����Ʈ�� �Է��� �̷������ �ð�����, �� �̻��� �ð���ŭ 
	���� ����Ʈ�� �Է��� ���� ��쿡�� �Է°��� Return�ϰ� RX_CHAR Message�� 
	�߻���ŵ�ϴ�

[2][3]	ReadTotalTimeoutMultiplier*ReadTotalTimeoutConstant 
		�б� ���ۿ� �ɸ��� �ѽð����� �� ���� 0�̸� ������� �ʴ´ٴ� ���Դϴ�

[3][4]	WriteTotalTimeoutMultiplier*ReadTotalTimeoutConstant 
		���� ���ۿ� �ɸ��� �ѽð����� �� ���� 0�̸� ������� �ʴ´ٴ� ���Դϴ�

���� ������ ������ �� SetCommTimeouts()�Լ��� ȣ���Ͽ� Timeout���� �����մϴ�

 BOOL		SetCommTimeouts(
			HANDLE			hFile,
			LPCOMMTIMEOUSTS	lpCommTimeouts
		);

��,  ReadIntervalTimeout��ŭ ��ٸ��� ���� Data�� ������ ���� Data�� Return�ϰ�,  
ReadTotalTimeoutMultiplier  *ReadTotalTimeoutConstant�� �ð���ŭ ��ٷ��� �б��
�� Data �����ŭ ���� ���ϰų� WriteTotalTimeout Multiplier  *WriteTotalTimeoutConstant
�ð� �ȿ� ������ �� �Ұ�� Error event�� �߻��ǵ��� �����ϴ� ���Դϴ�.

******************************************************************************/
	//timeouts.ReadIntervalTimeout		= 0xFFFFFFFF;
	// ���� ���� �ϸ� ������ ó�� �ð��� �ʹ� ���� 13����Ʈ�� �ѹ��� 
	// �ȳ����� 8��, 5���� �ɰ��� �� �ֽ��ϴ�.
	timeouts.ReadIntervalTimeout		= 10;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant	= 0;
	timeouts.WriteTotalTimeoutMultiplier= 2*CBR_9600 / dwBaud;	// <<-- 9600
	timeouts.WriteTotalTimeoutConstant	= 0;

	SetCommTimeouts( m_hComm, &timeouts);
/******************************************************************************
	[6] dcb ����
	
	������ Port�� ���� �ӵ�, ������ ��Ʈ��, �и�Ƽ, ���� ��Ʈ��, XON / XOFF Flow
	Control�� �������� �����Դϴ�. MFC������ �̷� ������ ���� DCB��� ����ü��
	�����մϴ�.

typedef	  struct_DCB{
	DWORD	DCBlength;				[1] sizeof(DCB)
	DWORD	BaudRate;				[2] baud rate
	DWORD	fBinary: 1;				[3] binary mode, EOF�� Chack���� ����
	DWORD	fParity: 1;				[4] Parity�� Chack��
	DWORD	fOutxCtsFlow: 1;		[5] CTS output flow control�� ��
	DWORD	fOutxDsrFlow: 1;		[6] DSR output flow control�� �� 
	DWORD	fDtrControl: 2;			[7] DTR flow control
	DWORD	fDsrSensitivity: 1;		[8] DSR ����
 	DWORD	fTXContinueOnXoff: 1;	[9] XOFF�� ������ �����
	DWORD	fOutX: 1;				[10]XON / XOFF ���� �帧 ���� 
	DWORD	fInX: 1;				[11] XON / XOFF �Է� �帧 ����
	DWORD	fErrorChar: 1;			[12] ���� ����
	DWORD	fNull: 1;				[13] �Է¹��� ������ �� NULL�� ����
	DWORD	fRtsControl: 2;			[14] RTS flow control
	DWORD	fAbortOnError: 1;		[15] Error �߻��� ����� ���
	DWORD	fDummy2: 17;			[16] reserved
	WORD	wReserved;				[17] ���� ��� ����
	WORD	XonLim;					[18] ���� XON ����ġ
	WORD	XoffLim;				[19] ���� XOFF ����ġ
	BYTE	ByteSize;				[20] �� Byte�� ��Ʈ��
	BYTE	Parity					[21] 0 ~ 4 = no, odd, even, mark, space
	BYTE	StopBits;				[22] 0, 1, 2 = 1, 1.5, 2
	char 	XonChar;				[23] XON���� ����� ���� 
	char 	XoffChar;				[24] XOFF�� ����� ���� 
	char	ErrorChar;				[25] ������ ��ü�� ����
	char	EofChar;				[26] EOF ����
	char	EvtChar;				[27] ���� �̺�Ʈ ����
	WORD	wReserved1;				[28] reserved
}DCB;
	
	���� ������ ��� ������ �����ص� ������ ���Ǹ� ���� GetCommState() �Լ���
	�̿��� ���� �ֽ��ϴ�. �� �Լ��� �ý��ۿ��� �̹� ������� ������ �о� �ɴϴ�
	
	BOOL	GetCommjState( HANDLE hFile, LPDCB lpDCB  );

	�̷��� �о�� ���� �� ���ϴ� ������ �ٲپ� �ְ� SetCommState() �Լ��� �̿��ؼ�
	�ٽ� ������ �ݴϴ�.
	
	BOOL	SetCommjState( HANDLE hFile, LPDCB lpDCB  );

******************************************************************************/
	dcb.DCBlength = sizeof(DCB);	// [1]

	GetCommState( m_hComm, &dcb);	
	
	dcb.BaudRate		= dwBaud;	// [2]	9600
//	dcb.fDtrControl		= 2;		// [7] DTR flow control
//	dcb.fDsrSensitivity = 1;		// [8] DSR ����
	dcb.ByteSize		= 8;		// [20] 8 bit
	dcb.Parity			= 0;		// [21] None
	dcb.StopBits		= 0;		// [22] 1 stop

//	dcb.fInX = dcb.fOutX = 1;		
//	dcb.XonChar = ASCII_XON;
//	dcb.XoffChar = ASCII_XOFF;
//	dcb.XonLim = 100;
//	dcb.XoffLim = 100;
	
	if (!SetCommState(m_hComm, &dcb))	return FALSE;
/******************************************************************************
	[7] ��Ʈ ���� ������ ����.

  HANDLE	CreateThread(
			LPSECURITY_ATTRIBUTES	lpThreadAttributes,	[1]
			DWORD				dwStackSize,			[2]
			LPTHREAD_START_ROUTINE	lpStartAddress,		[3]
			LPVOID				lpParameter,			[4]
			DWORD				dwCreationFlagz,		[5]
			LPDWORD				lpThreadld				[6]
		);


[1] ������ �����尡 �θ��� Ư���� ������������ ����, �̰�� �츮�� NULL�� ����
	�Ͽ� Ư���� �������� �ʾƵ� ������ �����ϴ�.

[2]	�����Ǵ� �����忡�� ����� ������ ũ��, �̰��� 0���� �����Ͽ� �� ���μ����� 
	ũ�⿡ ���� �ڵ����� �����ǵ��� �س����� �����尡 ����� ��쿡�� �ڵ����� 
	���� �˴ϴ�. ���⼭�� 0���� �����Ͽ� �̷��� Ư¡�� �̿��Ͽ����ϴ�. ���� ����	
	�� ������ ���� �����ŭ�� �޸𸮸� �Ҵ���� ���ϸ� �����尡 �������� �ʽ�
	�ϴ�.

[3]	������� ������ �Լ��� �����͸� �����մϴ�.

[4] �����忡 ������ �Ķ���Ͱ� ���� ��쿡 ����մϴ�. �츮�� ��� �θ� ���μ���
	�� Window Handle�� �̿��Ͽ� ���������ν� �θ� ���μ����� �޽����� �����ϴµ�
	����մϴ�

[5] �̰��� CREATE_SUSPENDED�� �صθ� ResumeThread()�� �̿��Ͽ� Ȱ��ȭ��Ű�� 
	������ �����尡 ������ �ֽ��ϴ�. �츮�� �����尡 �ﰢ �۵��ؾ� �ϹǷ� 0����
	�����մϴ�.

[6] �����带 �Ĺ��ϱ� ���� �ڵ��� �������Դϴ�.

******************************************************************************/	  
	m_bPortOnOff = 1;

	m_hThreadWatchComm = CreateThread(
							NULL,
							0, 
							(LPTHREAD_START_ROUTINE)ThreadWatchComm,
							this,
							0,
							&dwThreadID		// <<--- wPortID
						 );
	if (!m_hThreadWatchComm){
		ClosePort();
		return FALSE;
	}
	return TRUE;
}

/******************************************************************************

������� ������ �Լ��Դϴ� 

��Ʈ�� �����ϰ�, Serial Port���� �޽����� �߻��ϸ� �Է� �޽����ΰ� �˻��ϰ� 
������ ������ m_ReadData�� ������ �ڿ� MainWnd�� �޽����� ������ Buffer�� 
������ �о��� WM_COMM_READ �޼����� ������ 

BYTE	buff[2048];	// InQueue�� �����͸� �о���� ���� Input Buffer
DWORD	dwBufferCounter;	// ���� ����Ʈ��
// ��Ʈ�� �����ϴ� ����	
while(pComm->m_bPortOnOff){	}	
// ��Ʈ �޼����� �߻��Ҷ����� ��ٸ���
WaitCommEvent(pComm->m_hComm, &dwEvent, NULL);
******************************************************************************/

DWORD	ThreadWatchComm(CCommThread* pComm)
{
	DWORD		dwEvent;
	OVERLAPPED	os;
	BOOL		bOk = TRUE;		 
	BYTE		buff[4096];	
	DWORD		dwBufferCounter;			

	// Event, Overap Structure ����.
	memset( &os, 0, sizeof(OVERLAPPED));
	if (!(os.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL))) bOk = FALSE;
	if (! SetCommMask( pComm->m_hComm, EV_RXCHAR)) bOk = FALSE;
	if (!bOk){
		AfxMessageBox("Error while creating ThreadWatchComm," + pComm->m_sPortName);
		return FALSE;
	}

	while (pComm->m_bPortOnOff){
		
		dwEvent = 0;
//=============================================================================		

		WaitCommEvent(pComm->m_hComm, &dwEvent, NULL);

//=============================================================================
		if((dwEvent & EV_RXCHAR) == EV_RXCHAR){
			// ��Ʈ���� ���� �� �ִ� ��ŭ �д´�.

			do{
				dwBufferCounter = pComm->ReadComm(buff, 4096);
				// ReadComm���κ��� ���� ������ ������ ������ ���� �����͸� 
				// �� ����Ʈ�� Queue�� ���� �ִ´�
				/*if (BUFF_SIZE - pComm->m_QueueRead.GetSize() > (int)dwBufferCounter){
					for ( WORD i = 0; i < dwBufferCounter; i++)
						pComm->m_QueueRead.PutByte(buff[i]);
				}
				else
					AfxMessageBox("m_QueueRead FULL!");*/
				for (int i=0; i<100000; i++);
				pComm->ProcessRcvData( buff, (BYTE)dwBufferCounter );
			  
			}while (dwBufferCounter);
			//	�о� ������ �޽����� ������.
			/*::PostMessage(hCommWnd,WM_COMM_READ,pComm->m_wPortID,0);*/
		}
	}// �� ���μ������� �� ���� FALSE�� �ٲ��ָ� while�� ������ 

	// ��Ʈ�� ClosePort�� ���� ������ m_bPortOnOff �� FALSE�� �Ǿ� ����.
	CloseHandle(os.hEvent);
	pComm->m_hThreadWatchComm = NULL;
	return TRUE;
}


/******************************************************************************
	��Ʈ�� �ݴ´�
	Event�߻��� ��� ������Ű�� Buffer�� ��� ������ ����� 
******************************************************************************/
void CCommThread::ClosePort()
{
	m_bPortOnOff = OFF;
	SetCommMask(m_hComm, 0);
	PurgeComm( 
		m_hComm,
		PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR
	);
	CloseHandle(m_hComm);
}


// ��Ʈ�� pBuff�� ������ nToWrite��ŭ ����.
// ������ ������ Byte���� �����Ѵ�.
DWORD CCommThread::WriteComm(BYTE *pBuff, DWORD nToWrite)
{
	DWORD	dwWritten;
	DWORD	dwError;
	DWORD	dwErrorFlags;

	COMSTAT	comstat;

	if (!WriteFile(m_hComm, pBuff, nToWrite, &dwWritten, &m_osWrite)){
		// Error Code�� �������� �˾ƺ��� 
		if (GetLastError() == ERROR_IO_PENDING){
			//	���� ���ڰ� ���� �ְų� ������ ���ڰ� ���� ���� ��� Overapped IO��
			//	Ư���� ���� ERROR_IO_PENDING ���� �޽����� ���޵ȴ�.
			//	timeouts�� ������ �ð���ŭ ��ٷ��ش�.
			while (!GetOverlappedResult(m_hComm, &m_osWrite, &dwWritten, TRUE)){
				// ���������� �߻��� ErrorMessage
				dwError = GetLastError();
				if (dwError != ERROR_IO_INCOMPLETE){
					ClearCommError( m_hComm, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else{
			dwWritten = 0;
			ClearCommError(m_hComm, &dwErrorFlags, &comstat);
		}
	}
	return dwWritten;
}
/*****************************************************************************
	��Ʈ�κ��� pBuff�� nToRead��ŭ �д´�.
	������ ������ Byte���� �����Ѵ�.

	BOOL	ReadFile(
				HANDLE			hFile,					[1]
				LPVOID			lpBuffer,				[2]
				DWORD			nNumberOfBytesToRead,	[3]
				LPDWORD			lpNumberOfBytesRead,	[4]
				LPOVERLAPPED	lpOverlapped			[5]
			);

[1] Device File�� handle
[2] Data�� ������ Buffer�� ������
[3] ���� ����Ʈ ��
[4] ���� ����Ʈ���� ������ ������ ������
[5] Overapped structure������ ������
******************************************************************************/
DWORD CCommThread::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	DWORD	dwRead;
	DWORD	dwError;
	DWORD	dwErrorFlags;
	COMSTAT	comstat;

	ClearCommError( m_hComm, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;
	
	if (dwRead > 0){
		if (! ReadFile( m_hComm, pBuff, nToRead, &dwRead, &m_osRead)){
			if (GetLastError() == ERROR_IO_PENDING){
				// timeouts�� ������ �ð���ŭ ��ٷ��ش�.
				while (! GetOverlappedResult( m_hComm, &m_osRead, &dwRead, TRUE)){
					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE){
						ClearCommError( m_hComm, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else{
				dwRead = 0;
				ClearCommError( m_hComm, &dwErrorFlags, &comstat);
			}
		}
	}

	return dwRead;
}

void CCommThread::ProcessRcvData(BYTE *byBuf, int nSize)
{
	//--> �߰�....
	if( !nSize )		return;

	//--> Clear Buf
	for( int i=1; i<MAX_RECEIVE; i++ )
	{
		g_byRcvBuf[i] = 0;
		g_byRcvData[i] = 0;
	}

	//--> Buf Copy..
	for( i=0; i<nSize; i++ )
	{
		g_byRcvBuf[i + 1] = byBuf[i];
		g_byRcvData[i + 1] = byBuf[i];
	}

	//--> Receive Total Count
	++g_byRcvBuf[0];
	++g_byRcvData[0];

	//--> �޼��� ��Ʈ�� ����ΰ�??
	//UINT uiMessagePort = ( !(m_wPortID-1) )  ?  (UINT)WM_COMM_READ : 
	//--> View ����..�޼��� ����..���ŵ� ��Ʈ�� �޼���..
	::SendMessage( MyhCommWnd, WM_COMM_READDATA, 0, nSize );
	::SendMessage( hCommWnd, WM_COMM_READ, 0, nSize );		 
}
