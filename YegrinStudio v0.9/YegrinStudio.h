// YegrinStudio.h : main header file for the YEGINSTUDIO application
//

#if !defined(AFX_YEGINSTUDIO_H__0ED9292F_F84B_461E_BEE6_28B0CF01BCF3__INCLUDED_)
#define AFX_YEGINSTUDIO_H__0ED9292F_F84B_461E_BEE6_28B0CF01BCF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CYegrinStudioApp:
// See YegrinStudio.cpp for the implementation of this class
//

class CYegrinStudioApp : public CWinApp
{
public:
	CYegrinStudioApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYegrinStudioApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CYegrinStudioApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
extern CYegrinStudioApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YEGINSTUDIO_H__0ED9292F_F84B_461E_BEE6_28B0CF01BCF3__INCLUDED_)
