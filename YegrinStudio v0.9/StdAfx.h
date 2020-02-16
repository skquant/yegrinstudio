// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B1201FD2_83FB_44B7_BE2B_01AB11F21957__INCLUDED_)
#define AFX_STDAFX_H__B1201FD2_83FB_44B7_BE2B_01AB11F21957__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

// �Ʒ� ������ �÷������� �켱�ϴ� �÷����� ������� �ϴ� ��� ���� ���Ǹ� �����Ͻʽÿ�.
// �ٸ� �÷����� ���Ǵ� �ش� ���� �ֽ� ������ MSDN�� �����Ͻʽÿ�.
#ifndef WINVER				// Windows 95 �� Windows NT 4 ���� ���������� ����� ����� �� �ֽ��ϴ�.
#define WINVER 0x0400		// Windows 98�� Windows 2000 ���� ������ �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#ifndef _WIN32_WINNT		// Windows NT 4 ���� ���������� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_WINNT 0x0400		// Windows 98�� Windows 2000 ���� ������ �µ��� ������ ������ ������ �ֽʽÿ�.
#endif						

/*
#ifndef _WIN32_WINDOWS		// Windows 98 ���� ���������� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_WINDOWS 0x0410 // Windows Me ���� ������ �µ��� ������ ������ ������ �ֽʽÿ�.
#endif
*/

//#ifndef _WIN32_IE			// IE 4.0 ���� ���������� ����� ����� �� �ֽ��ϴ�.
//#define _WIN32_IE 0x0400	// IE 5.0 ���� ������ �µ��� ������ ������ ������ �ֽʽÿ�.
//#endif

//#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <atlbase.h>

#include "CommThread.h"

typedef struct _YegrinDevice{
	unsigned int DeviceNum;
	struct _YegrinDevice *Next;
}YEGRINDEVICE, *PYEGRINDEVICE;

typedef struct _YegrinDeviceGroup{
	unsigned int GroupNum;
	struct _YegrinDevice *YegrinDeviceObject;
	struct _YegrinDeviceGroup *Next;
}YEGRINDEVICEGROUP, *PYEGRINDEVICEGROUP;

typedef struct _CommSetup{
	CString ComPort;
	//char	Baud[5][10]={"9600","14400","19200","38400","57600"};
}COMMSETUP, *PCOMMSETUP;

//���� ����� ���� �������� A
typedef struct _Protocol{
	//BYTE *DATA;//COMMAND ���� DATA[0]
	//BYTE DATA[3];		
	BYTE STX;
	BYTE ID[2];		
	BYTE ETX;
	BYTE SUM;
}PROTOCOL, *PPROTOCOL;

//--> �ִ� ���� ����Ʈ��..���� �Ѱ�ġ..
#define  MAX_RECEIVE			(4096 + 1)

//--> �ִ� �۽� ����Ʈ��..���� �Ѱ�ġ..
#define  MAX_SEND				(256 + 1)

//--> �ִ� ȭ�� ����Ʈ��..���� �Ѱ�ġ..
#define  MAX_FILE				(32768 + 1)

//extern ������ ����Ȱ��� StdAfx.cpp �ȿ� �ִ�.
//Ŭ������ ��ӵ��� �ʴ� API �Լ��� ����..

#define M(Test)	AfxMessageBox(Test)

extern BYTE g_byRcvBuf[MAX_RECEIVE];	//���� ����
extern BYTE g_byRcvData[4]; //���� ����� ���� ������ ��
extern BYTE g_bySendBuf[MAX_SEND];	//���� ����

extern BYTE SendBuf[MAX_FILE];	//ȭ�� ����

extern HWND hCommWnd;
extern HWND MyhCommWnd;
/////////////////�ø��� ���� ���̾˷α׿� �����Ǳ� ���� ���� ���� ����
extern char	g_strBaud[5][10];
extern char	g_strCOM[5][10];
extern char	g_strData[5][2];
extern char	g_strPty[3][5];
extern char	g_strStop[3][5];
extern BOOL g_ComPortCheck;
//////////////////////////////////////////////////////

extern CCommThread	m_CommPort1;	// Port 1


int nMakeSendCode( CString strInputData, int xPortNo );
int nMakeSendCode_Hexa(CString strInputData, int xPortNo);
BYTE byCode2AsciiValue( char cData );
CString CharHex(char str); //CString m_input)

//���� �����͸� �ְ� �ޱ� ���� ����Ѵ�.
int CommInterface(int rw, char *id, char *Command, CString Data);
CString strRcvData(int nRcvSize );
void MyAfxMessageBox(int count, BYTE *Data);

//�׽�Ʈ�� ���� DEFINE ���� 
extern char rid[3];
extern CString		rd;
extern int		RcvSize;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B1201FD2_83FB_44B7_BE2B_01AB11F21957__INCLUDED_)
