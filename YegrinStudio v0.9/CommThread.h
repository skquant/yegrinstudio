
//���� �߿��մϴ�. �� ������ ������ Ŭ���� ������ ��� �ȴٰ�  �����޼����� ��ϴ�.
//����� �Ʒ�ó�� �Ͻð��.. ����� ������ ���ڸ� �����ø� �˴ϴ�. 
//���� �� �ƹ��ų�..

#if !defined(AFX_COMMTHREAD_H__BKMIR__INCLUDED_)
#define AFX_COMMTHREAD_H__BKMIR__INCLUDED_

// Thread�� �θ� ���μ����� �����͸� �ְ� ���� Bufferũ�� 
#define	BUFF_SIZE		8192				
#define	WM_COMM_READ		(WM_USER+1)	
#define	WM_COMM_READDATA	(WM_USER+1)	
#define	ASCII_LF		0x0a
#define	ASCII_CR		0x0d
#define	ASCII_XON		0x11
#define	ASCII_XOFF		0x13
#define	ON				TRUE;
#define	OFF				FALSE;								

class CQueue
{
public:
	BYTE	buff[BUFF_SIZE];		// Queue Buffer
	int		m_iHead;				// Queue Head �� Tail Position
	int		m_iTail;
	int		GetSize();				// Queue�� ����ִ� �������� ���̸� Return�Ѵ� 

	BOOL	PutByte(BYTE byte);		// Queue�� 1 byte �ֱ�
	BOOL	GetByte(BYTE *pbyte);	// Queue�� 1 byte ������

	CQueue();			
	void	Clear();				// Queue�� ������ ����� 
};

//	��� Ŭ����	CCommThread 
//	��Ʈ ���� : OpenPort("COM1", CBR_9600);
//	��Ʈ �б� : ��Ʈ�� �� �Ŀ� ��Ʈ�� �ڷᰡ �����ϸ� WM_COMM_READ �޽�����
//				���� �����쿡 ���޵ȴ�. ON_MESSAGE ��ũ�θ� �̿�, �Լ��� 
//				�����ϰ� m_ReadData String�� ����� �����͸� �̿��ؼ� �д´�
//	��Ʈ ���� : WriteComm(buff, 30)�� ���� ���ۿ� �� ũ�⸦ �ǳ׸� �ȴ�.

class CCommThread
{
public:
	void ProcessRcvData( BYTE *byBuf, int nSize );
	CCommThread();

	HANDLE		m_hComm;			// ��� ��Ʈ ���� �ڵ�
	CString		m_sPortName;		// ��Ʈ �̸� (COM1 ..)
	BOOL		m_bPortOnOff;		// ��Ʈ�� ���ȴ��� ������ ��Ÿ��.
	OVERLAPPED	m_osRead;			// ��Ʈ ���� Overlapped structure
	OVERLAPPED	m_osWrite;
	HANDLE		m_hThreadWatchComm;	// Watch�Լ� Thread �ڵ�.
	WORD		m_wPortID;			// WM_COMM_READ�� �Բ� ������ �μ�.

	CQueue	m_QueueRead;

//=============================================================================
	BOOL	OpenPort(CString sPortName, DWORD dwBaud, WORD wParam);
//=============================================================================
	DWORD	WriteComm(BYTE *pBuff, DWORD nToWrite);
	DWORD	ReadComm(BYTE *pBuff, DWORD nToRead);

	int		m_intInQueue;
	int		m_intOutQueue;
	
	void ClosePort();
};

// Thread�� ����� �Լ� 
DWORD	ThreadWatchComm(CCommThread* pComm);

//���� �ִ� ���ǰ� ��ġ�ϰ�..
#endif // !defined(AFX_COMMTHREAD_H__BKMIR__INCLUDED_)