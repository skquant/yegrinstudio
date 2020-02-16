// ImageDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImageDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageDialog dialog


CImageDialog::CImageDialog(UINT nResourceID, CWnd* pParent /*=NULL*/)
	: CDialog(nResourceID, pParent)
{
	//{{AFX_DATA_INIT(CImageDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// 변수들을 초기화합니다.
	m_nBkgndMode = MODE_CENTER;
	m_NullBrush.CreateStockObject(NULL_BRUSH);
	m_clrBkgnd = ::GetSysColor(COLOR_ACTIVEBORDER);
}

CImageDialog::~CImageDialog()
{
	// 객체들을 제거합니다.
	m_bmpBkgnd.DeleteObject();
	m_NullBrush.DeleteObject();
}

void CImageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageDialog, CDialog)
	//{{AFX_MSG_MAP(CImageDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageDialog message handlers

int CImageDialog::GetBkgndMode()
{
	return m_nBkgndMode;
}

void CImageDialog::SetBkgndMode(int nMode)
{
	// 출력 방식이 잘못되었다면, 기본으로 가운데 출력을 설정
	if(nMode < MODE_CENTER || nMode > MODE_STRETCH)	nMode = MODE_CENTER;

	m_nBkgndMode = nMode;

	// 윈도우가 출력 중이라면 화면 갱신
	if(::IsWindowVisible(m_hWnd))		Invalidate();
}

BOOL CImageDialog::SetBitmap(UINT nResourceID)
{
	// 이미 비트맵이 있다면 우선 소멸시킴
	if(m_bmpBkgnd.m_hObject)	m_bmpBkgnd.DeleteObject();

	// 비트맵 로드
	if(m_bmpBkgnd.LoadBitmap(nResourceID))
	{
		m_bmpBkgnd.GetBitmap(&m_bmpInfo);
		return TRUE;
	}
	return FALSE;
}

BOOL CImageDialog::SetBitmap(LPCTSTR pFileName)
{
	ASSERT(pFileName);

	// 이미 비트맵이 있다면 우선 소멸시킴
	if(m_bmpBkgnd.m_hObject)	m_bmpBkgnd.DeleteObject();

	// 비트맵 파일 로드
	HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
			LPCTSTR(pFileName), IMAGE_BITMAP,
			0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	if(hBitmap == NULL)			return FALSE;

	// 비트맵 객체에 설정
	if(m_bmpBkgnd.Attach(hBitmap))
	{
		m_bmpBkgnd.GetBitmap(&m_bmpInfo);
		return TRUE;
	}
	return FALSE;
}

BOOL CImageDialog::OnEraseBkgnd(CDC* pDC) 
{
	// 배경 이미지가 없으면 기본 루틴 실행
	if(m_bmpBkgnd.m_hObject == NULL)
		return CDialog::OnEraseBkgnd(pDC);

	// 메모리 DC를 사용해 더블 버퍼링 실행
	CDC MemDC;
	CBitmap ScreenBmp, *pOldBmp;

	GetClientRect(&m_rcClient);

	MemDC.CreateCompatibleDC(pDC);
	ScreenBmp.CreateCompatibleBitmap(pDC, m_rcClient.Width(), m_rcClient.Height());
	pOldBmp = MemDC.SelectObject(&ScreenBmp);

	CDC BmpDC;
	CBitmap *pOldBmp2;

	BmpDC.CreateCompatibleDC(pDC);
	pOldBmp2 = BmpDC.SelectObject(&m_bmpBkgnd);

	int x, y;

	// 출력 방식에 따른 코드
	switch(m_nBkgndMode)
	{
	case MODE_CENTER:
		MemDC.FillSolidRect(&m_rcClient, m_clrBkgnd);

		x = (m_rcClient.Width() - m_bmpInfo.bmWidth) / 2;
		y = (m_rcClient.Height() - m_bmpInfo.bmHeight) / 2;
		MemDC.BitBlt(x, y, m_bmpInfo.bmWidth, m_bmpInfo.bmHeight,
			&BmpDC, 0, 0, SRCCOPY);
		break;
	case MODE_TILE:
		for(y = 0; y < m_rcClient.Height(); y += m_bmpInfo.bmHeight)
		{
			for(x = 0; x < m_rcClient.Width(); x += m_bmpInfo.bmWidth)
			{
				MemDC.BitBlt(x, y, m_bmpInfo.bmWidth, m_bmpInfo.bmHeight,
					&BmpDC, 0, 0, SRCCOPY);
			}
		}
		break;
	case MODE_STRETCH:
		MemDC.StretchBlt(0, 0, m_rcClient.Width(), m_rcClient.Height(),
			&BmpDC, 0, 0, m_bmpInfo.bmWidth, m_bmpInfo.bmHeight, SRCCOPY);
		break;
	}

	pDC->BitBlt(0, 0, m_rcClient.Width(), m_rcClient.Height(),
		&MemDC, 0, 0, SRCCOPY);

	BmpDC.SelectObject(pOldBmp2);
	BmpDC.DeleteDC();

	MemDC.SelectObject(pOldBmp);
	MemDC.DeleteDC();

	return TRUE;
}

HBRUSH CImageDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	// 배경 이미지가 설정되어 있다면,
	// 각 컨트롤들의 배경을 투명하게 설정한다.
	if(m_bmpBkgnd.m_hObject)
	{
		if(nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_BTN)
		{
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)m_NullBrush;
		}
	}

	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CImageDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	Invalidate();
}
