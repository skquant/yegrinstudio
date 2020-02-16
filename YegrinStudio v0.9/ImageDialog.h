#if !defined(AFX_IMAGEDIALOG_H__9B74A250_9077_4E93_8849_C6DA10D751C0__INCLUDED_)
#define AFX_IMAGEDIALOG_H__9B74A250_9077_4E93_8849_C6DA10D751C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageDialog dialog

// 비트맵 다이얼로그의 선조 클래스
class CImageDialog : public CDialog
{
// Construction
public:
	CImageDialog(UINT nResourceID, CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageDialog();

	// 배경 이미지 출력 방식
	enum { MODE_CENTER = 0, MODE_TILE, MODE_STRETCH };

protected:
	int		m_nBkgndMode;					// 배경 이미지 출력 방식

	CBitmap	m_bmpBkgnd;						// 배경 이미지에 대한 비트맵 객체
	CBrush	m_NullBrush;					// 컨트롤들의 투명 배경용 브러쉬
	COLORREF m_clrBkgnd;					// 대화상자 배경색

	BITMAP	m_bmpInfo;						// 배경 이미지에 대한 정보
	CRect	m_rcClient;						// 클라이언트 영역

public:
	int GetBkgndMode();						// 현재 배경 출력 방식 리턴 함수
	void SetBkgndMode(int nMode);			// 새로운 배경 출력 방식 설정 함수

	BOOL SetBitmap(UINT nResourceID);		// 리소스의 비트맵을 배경으로 설정하는 함수
	BOOL SetBitmap(LPCTSTR pFileName);		// 비트맵 파일을 배경으로 설정하는 함수

// Dialog Data
	//{{AFX_DATA(CImageDialog)
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImageDialog)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEDIALOG_H__9B74A250_9077_4E93_8849_C6DA10D751C0__INCLUDED_)
