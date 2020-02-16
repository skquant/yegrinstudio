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

// 아래 지정된 플랫폼보다 우선하는 플랫폼을 대상으로 하는 경우 다음 정의를 수정하십시오.
// 다른 플랫폼에 사용되는 해당 값의 최신 정보는 MSDN을 참조하십시오.
#ifndef WINVER				// Windows 95 및 Windows NT 4 이후 버전에서만 기능을 사용할 수 있습니다.
#define WINVER 0x0400		// Windows 98과 Windows 2000 이후 버전에 맞도록 적합한 값으로 변경해 주십시오.
#endif

#ifndef _WIN32_WINNT		// Windows NT 4 이후 버전에서만 기능을 사용할 수 있습니다.
#define _WIN32_WINNT 0x0400		// Windows 98과 Windows 2000 이후 버전에 맞도록 적합한 값으로 변경해 주십시오.
#endif						

/*
#ifndef _WIN32_WINDOWS		// Windows 98 이후 버전에서만 기능을 사용할 수 있습니다.
#define _WIN32_WINDOWS 0x0410 // Windows Me 이후 버전에 맞도록 적합한 값으로 변경해 주십시오.
#endif
*/

//#ifndef _WIN32_IE			// IE 4.0 이후 버전에서만 기능을 사용할 수 있습니다.
//#define _WIN32_IE 0x0400	// IE 5.0 이후 버전에 맞도록 적합한 값으로 변경해 주십시오.
//#endif

//#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 일부 CString 생성자는 명시적으로 선언됩니다.

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

//실제 통신을 위한 프로토콜 A
typedef struct _Protocol{
	//BYTE *DATA;//COMMAND 포함 DATA[0]
	//BYTE DATA[3];		
	BYTE STX;
	BYTE ID[2];		
	BYTE ETX;
	BYTE SUM;
}PROTOCOL, *PPROTOCOL;

//--> 최대 수신 바이트수..버퍼 한계치..
#define  MAX_RECEIVE			(4096 + 1)

//--> 최대 송신 바이트수..버퍼 한계치..
#define  MAX_SEND				(256 + 1)

//--> 최대 화일 바이트수..버퍼 한계치..
#define  MAX_FILE				(32768 + 1)

//extern 변수가 선언된곳은 StdAfx.cpp 안에 있다.
//클래스에 상속되지 않는 API 함수도 포함..

#define M(Test)	AfxMessageBox(Test)

extern BYTE g_byRcvBuf[MAX_RECEIVE];	//수신 버퍼
extern BYTE g_byRcvData[4]; //실제 사용할 수신 데이터 값
extern BYTE g_bySendBuf[MAX_SEND];	//수신 버퍼

extern BYTE SendBuf[MAX_FILE];	//화일 버퍼

extern HWND hCommWnd;
extern HWND MyhCommWnd;
/////////////////시리얼 설정 다이알로그와 연동되기 위한 전역 번수 설정
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

//실제 데이터를 주고 받기 위해 사용한다.
int CommInterface(int rw, char *id, char *Command, CString Data);
CString strRcvData(int nRcvSize );
void MyAfxMessageBox(int count, BYTE *Data);

//테스트를 위한 DEFINE 값들 
extern char rid[3];
extern CString		rd;
extern int		RcvSize;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B1201FD2_83FB_44B7_BE2B_01AB11F21957__INCLUDED_)
