#if !defined(AFX_COOLBUTTON_H__98EA5DF5_CFAA_438E_AA18_FE5413E3164E__INCLUDED_)
#define AFX_COOLBUTTON_H__98EA5DF5_CFAA_438E_AA18_FE5413E3164E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CoolButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCoolButton window

// 버튼에 설정한 이미지 타입
enum ENUM_IMAGE_TYPE		{ IMG_BMP = 0, IMG_ICON };

// 버튼에서 텍스트의 위치 타입
enum ENUM_TEXT_ALIGN		{ ALIGN_LEFT = 0, ALIGN_RIGHT, ALIGN_TOP, ALIGN_BOTTOM, ALIGN_OVER };

// 버튼에 색상을 설정할 때 사용하는 색상 타입
enum ENUM_COLOR_TYPE		{ COLOR_TEXT = 0, COLOR_BKGND, COLOR_TEXT_IN, COLOR_BKGND_IN, COLOR_MAX };


// 비트맵과 아이콘을 설정할 수 있는 버튼
class CCoolButton : public CButton
{
// Construction
public:
	CCoolButton();

// Attributes
public:
	HCURSOR				m_hCursor;					// 손모양 커서

	BITMAP				m_bmpInfo;					// 현재 이미지의 정보
	CBitmap				m_bmpImage;					// 버튼의 비트맵 객체
	CBitmap				m_bmpMask;					// 버튼의 비트맵 객체에서 투명 처리를 위한 마스크 비트맵
	HICON				m_hIcon;					// 버튼의 아이콘 객체
	CPoint				m_ptImage;					// 버튼에서 이미지 출력 위치
	ENUM_IMAGE_TYPE		m_nImageType;				// 현재 설정된 이미지 타입

	BOOL				m_bFlat;					// 평면 버튼인지 입체 버튼인지 여부
	BOOL				m_bHover;					// 마우스가 버튼 위에 있는지 여부
	CRect				m_rcClient;					// 버튼의 클라이언트 크기

	CString				m_strText;					// 버튼의 텍스트
	CRect				m_rcText;					// 버튼에서 텍스트 출력 위치

	COLORREF			m_clrColors[COLOR_MAX];		// 버튼에 사용되는 색상 배열
	COLORREF			m_clrTransparent;			// 투명 처리할 색상

	ENUM_TEXT_ALIGN		m_nTextAlign;				// 버튼에서 텍스트의 위치

	CString				m_strToolTip;				// 툴팁 텍스트
	CToolTipCtrl		m_wndToolTip;				// 툴팁 컨트롤

// Operations
public:
	void SetButtonBmp(UINT nBitmapID);				// 버튼에 비트맵을 설정하는 함수
	void SetButtonBmp(UINT nBitmapID, COLORREF clrTransparent);
													// 버튼에 비트맵을 설정하고 투명색을 설정하는 함수
	void SetButtonIcon(UINT nIconID);				// 버튼에 아이콘을 설정하는 함수
	void RepositionAll();							// 버튼에서 이미지와 텍스트의 위치를 계산하는 함수

	// 평면 버튼인지 리턴/설정하는 함수
	BOOL IsFlat()						{ return m_bFlat; }
	void SetFlat(BOOL bFlat);

	// 버튼의 텍스트를 리턴/설정하는 함수
	LPCTSTR GetButtonText()				{ return m_strText; }
	void SetButtonText(LPCTSTR pText);

	// 버튼의 색상을 리턴/설정하는 함수
	COLORREF GetButtonColor(ENUM_COLOR_TYPE nColor);
	void SetButtonColor(ENUM_COLOR_TYPE nColor, COLORREF clrColor);

	// 버튼에서 텍스트 위치를 리턴/설정하는 함수
	ENUM_TEXT_ALIGN GetTextAlign()		{ return m_nTextAlign; }
	void SetTextAlign(ENUM_TEXT_ALIGN nAlign);

	// 버튼의 툴팁을 리턴/설정하는 함수
	LPCTSTR GetToolTipText()			{ return m_strToolTip; }
	void SetToolTipText(LPCTSTR pTip);

	// 배경을 그리는 함수
	virtual void DrawBkgnd(CDC *pDC, BOOL bPressed, BOOL bEnable);
	// 테두리를 그리는 함수
	virtual void DrawBorder(CDC *pDC, BOOL bPressed, BOOL bFocus);
	// 이미지를 그리는 함수
	virtual void DrawImage(CDC *pDC, BOOL bPressed);
	// 텍스트를 그리는 함수
	virtual void DrawText(CDC *pDC, BOOL bPressed, BOOL bEnable);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoolButton)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCoolButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCoolButton)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLBUTTON_H__98EA5DF5_CFAA_438E_AA18_FE5413E3164E__INCLUDED_)
