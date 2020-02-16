#if !defined(AFX_STATICEX_H__83C6540A_9745_45A5_B1DD_D8CE0E1FE11C__INCLUDED_)
#define AFX_STATICEX_H__83C6540A_9745_45A5_B1DD_D8CE0E1FE11C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticEx window

class CStaticEx : public CStatic
{
// Construction
public:
	CStaticEx();

// Attributes
public:
	COLORREF m_textColor;
	CBrush m_backBrush;
	COLORREF m_backColor;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticEx)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetBitmap(UINT nID, BOOL bStretch=FALSE, COLORREF transColor=::GetSysColor(COLOR_BTNFACE));
	void SetBkColor(COLORREF Color);
	void SetTextColor(COLORREF Color);
	virtual ~CStaticEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticEx)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICEX_H__83C6540A_9745_45A5_B1DD_D8CE0E1FE11C__INCLUDED_)
