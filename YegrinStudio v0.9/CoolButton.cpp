// CoolButton.cpp : implementation file
//

#include "stdafx.h"
#include "CoolButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoolButton

// 손 모양의 마우스 커서 ID
#define IDC_HAND            MAKEINTRESOURCE(32649)

// 버튼의 외곽에서 이미지와 텍스트까지의 여백(픽셀)
#define CONST_GAP			4

CCoolButton::CCoolButton()
{
	// 손모양 마우스 커서를 로드한다
	m_hCursor		= ::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND));

	// 각종 변수들을 초기화한다
	m_hIcon			= NULL;

	m_nImageType	= IMG_BMP;
	m_bFlat			= TRUE;
	m_bHover		= FALSE;

	m_clrColors[COLOR_TEXT]		= ::GetSysColor(COLOR_BTNTEXT);
	m_clrColors[COLOR_BKGND]	= ::GetSysColor(COLOR_BTNFACE);
	m_clrColors[COLOR_TEXT_IN]	= ::GetSysColor(COLOR_BTNTEXT);
	m_clrColors[COLOR_BKGND_IN] = ::GetSysColor(COLOR_BTNFACE);

	m_nTextAlign	= ALIGN_RIGHT;
}

CCoolButton::~CCoolButton()
{
	// 각종 리소스들을 반환한다
	if(m_hCursor)				::DeleteObject(m_hCursor);
	if(m_hIcon)					::DeleteObject(m_hIcon);

	if(m_bmpImage.m_hObject)	m_bmpImage.DeleteObject();
	if(m_bmpMask.m_hObject)		m_bmpMask.DeleteObject();
}


BEGIN_MESSAGE_MAP(CCoolButton, CButton)
	//{{AFX_MSG_MAP(CCoolButton)
	ON_WM_SETCURSOR()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoolButton message handlers

void CCoolButton::PreSubclassWindow() 
{
	// 현재 버튼의 크기를 저장한다
	GetClientRect(&m_rcClient);
	// 기본 텍스트 위치는 버튼의 중앙으로 설정한다
	m_rcText = m_rcClient;
	
	// BS_OWNERDRAW 속성을 설정한다
	ModifyStyle(0, BS_OWNERDRAW);

	// 기본 텍스트를 버튼의 캡션으로 설정한다
	GetWindowText(m_strToolTip);

	// 툴팁 컨트롤을 생성한다
	m_wndToolTip.Create(this, TTS_ALWAYSTIP);
	m_wndToolTip.Activate(FALSE);
	m_wndToolTip.AddTool(this, m_strToolTip, m_rcClient, 1);
	m_wndToolTip.Activate(TRUE);

	CButton::PreSubclassWindow();
}

BOOL CCoolButton::PreTranslateMessage(MSG* pMsg) 
{
	// 툴팁 컨트롤에게 마우스 이벤트를 전달한다
	m_wndToolTip.RelayEvent(pMsg);
	
	return CButton::PreTranslateMessage(pMsg);
}

// 버튼 사용자 정의 그리기 함수
void CCoolButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// 인자의 DC 핸들로 CDC 객체를 생성한다
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	// 부드러운 화면 출력을 위해 메모리 DC를 생성하고 더블 버퍼링을 구현한다
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap MemBmp, *pOldBmp;

	MemBmp.CreateCompatibleBitmap(pDC, m_rcClient.Width(), m_rcClient.Height());
	pOldBmp = MemDC.SelectObject(&MemBmp);

	// 버튼의 아래쪽 배경을 출력한다.
	MemDC.BitBlt(0, 0, m_rcClient.Width(), m_rcClient.Height(), pDC, 0, 0, SRCCOPY);

	// 배경을 그린다
	DrawBkgnd(&MemDC, lpDrawItemStruct->itemState & ODS_SELECTED, 
		!(lpDrawItemStruct->itemState & ODS_DISABLED));

	// 이미지를 그린다
	DrawImage(&MemDC, lpDrawItemStruct->itemState & ODS_SELECTED);

	// 텍스트를 그린다
	DrawText(&MemDC, lpDrawItemStruct->itemState & ODS_SELECTED,
		!(lpDrawItemStruct->itemState & ODS_DISABLED));

	// 테두리를 그린다
	DrawBorder(&MemDC, lpDrawItemStruct->itemState & ODS_SELECTED,
		lpDrawItemStruct->itemState & ODS_FOCUS);

	// 메모리 DC에 출력된 모든 내용을 화면에 출력한다
	pDC->BitBlt(0, 0, m_rcClient.Width(), m_rcClient.Height(), &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBmp);
	MemDC.DeleteDC();
	MemBmp.DeleteObject();
}

// 배경을 그리는 함수
void CCoolButton::DrawBkgnd(CDC *pDC, BOOL bPressed, BOOL bEnable)
{
	// 비활성화 상태인지 평면 버튼인지 입체 버튼인지에 따라 배경색을 칠한다
	if(m_bHover && bEnable)
	{
		pDC->FillSolidRect(&m_rcClient, m_clrColors[COLOR_BKGND_IN]);
	}
	else
	{
		if(m_bFlat)	pDC->FillSolidRect(&m_rcClient,
					::GetSysColor(COLOR_BTNFACE));
		else		pDC->FillSolidRect(&m_rcClient,
					m_clrColors[COLOR_BKGND]);
	}
}

// 테두리를 그리는 함수
void CCoolButton::DrawBorder(CDC *pDC, BOOL bPressed, BOOL bFocus)
{
	// 만약 마우스가 진입해 있거나 평면 버튼이 아니라면
	if(m_bHover || !m_bFlat)
	{
		// 현재 눌려진 상태라면 
		if(bPressed)
			// 눌려진 모양의 3차원 테두리를 그린다
			pDC->Draw3dRect(m_rcClient, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DHILIGHT));
		else
			// 튀어나온 모양의 3차원 테두리를 그린다
			pDC->Draw3dRect(m_rcClient, ::GetSysColor(COLOR_3DHILIGHT), ::GetSysColor(COLOR_3DSHADOW));
	}

	// 만약 현재 버튼이 포커스를 갖고 있다면
	if(bFocus)
	{
		// 버튼의 영역에서 안쪽 3픽셀씩 이동하여 포커스 사각형을 그린다
		CRect rcTemp = m_rcClient;
		rcTemp.DeflateRect(3, 3);
		pDC->DrawFocusRect(&rcTemp);
	}
}

// 이미지를 그리는 함수
void CCoolButton::DrawImage(CDC *pDC, BOOL bPressed)
{
	// 이미지 위치를 임시 저장한다
	CPoint ptImage = m_ptImage;

	// 만약 현재 버튼이 눌려진 상태라면
	// 이미지를 대각선 아래로 1픽셀씩 이동시킨다
	if(bPressed)
	{
		ptImage.x += 1;
		ptImage.y += 1;
	}

	// 현재 버튼의 이미지 타입에 따라 화면에 이미지를 출력한다
	switch(m_nImageType)
	{
	case IMG_BMP:
		// 비트맵이 설정되었다면
		if(m_bmpImage.m_hObject)
		{
			// 비트맵을 버튼의 이미지 출력 영역에 출력한다
			CDC BmpDC;
			BmpDC.CreateCompatibleDC(NULL);

			CBitmap *pOldBmp = BmpDC.SelectObject(&m_bmpImage);

			// 만약 투명색이 적용되어 있다면
			if(m_bmpMask.m_hObject)
			{
				// 마스크 비트맵을 사용해서 투명 처리를 하여
				// 비트맵을 출력한다
				CDC MaskDC;
				MaskDC.CreateCompatibleDC(NULL);
				CBitmap *pOldMask = MaskDC.SelectObject(&m_bmpMask);

				// 마스크 비트맵은 흑백이기 때문에,
				// 1은 윈도우 기본 배경색인 하얀색으로 바뀌고 0은 글자색인 검정색으로 바뀐다.
				// 그리고 화면의 내용과 AND 되어,
				// 마스크의 투명 영역은 배경이 그대로 드러나고 마스크의 이미지 영역은 검정색으로 배경이 지워진다.
				pDC->BitBlt(ptImage.x, ptImage.y, m_bmpInfo.bmWidth, m_bmpInfo.bmHeight, &MaskDC, 0, 0, SRCAND);
				// 원본 비트맵의 투명 부분은 이미 검정색으로 처리되었기 때문에
				// 투명 부분은 배경과 OR 되어 배경을 그대로 유지하고,
				// 원본 비트맵의 비투명 부분은 그대로 유지되어 있으므로
				// 배경의 검정색과 OR 되어 원본 이미지를 그대로 출력한다.
				pDC->BitBlt(ptImage.x, ptImage.y, m_bmpInfo.bmWidth, m_bmpInfo.bmHeight, &BmpDC, 0, 0, SRCPAINT);

				MaskDC.SelectObject(pOldMask);
				MaskDC.DeleteDC();
			}
			else
			{
				// 투명색이 적용되지 않았다면 이미지를 그냥 출력한다
				pDC->BitBlt(ptImage.x, ptImage.y, m_bmpInfo.bmWidth, m_bmpInfo.bmHeight, &BmpDC, 0, 0, SRCCOPY);
			}

			BmpDC.SelectObject(pOldBmp);
			BmpDC.DeleteDC();
		}
		break;
	case IMG_ICON:
		// 만약에 아이콘이 설정되었다면
		if(m_hIcon)
		{
			// 아이콘을 이미지 영역에 출력한다
			pDC->DrawIcon(ptImage, m_hIcon);
		}
		break;
	}
}

// 텍스트를 그리는 함수
void CCoolButton::DrawText(CDC *pDC, BOOL bPressed, BOOL bEnable)
{
	// 버튼의 텍스트를 읽는다
	GetWindowText(m_strText);

	// 텍스트 위치를 임시 저장한다
	CRect rcTemp = m_rcText;

	// 만약 현재 버튼이 눌려진 상태라면
	// 텍스트를 대각선 아래로 1픽셀씩 이동시킨다
	if(bPressed)
	{
		rcTemp.OffsetRect(1, 1);
	}

	// 텍스트의 배경을 투명하게 설정한다
	int nBkMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF clrText;

	// 만약 버튼이 비활성화된 상태라면 회색으로 텍스트 색상을 설정한다
	if(!bEnable)
	{
		clrText = pDC->SetTextColor(RGB(200, 200, 200));
	}
	else
	{
		// 마우스가 버튼에 진입해 있느냐에 따라 텍스트 색상을 설정한다
		if(m_bHover)
			clrText = pDC->SetTextColor(m_clrColors[COLOR_TEXT_IN]);
		else
			clrText = pDC->SetTextColor(m_clrColors[COLOR_TEXT]);
	}

	// 부모 다이얼로그의 폰트를 얻거나 시스템의 폰트를 사용해서 텍스트를 출력한다
	CFont *pFont = GetParent()->GetFont(), *pOldFont;
	if(pFont == NULL)
		pFont = CFont::FromHandle((HFONT)GetStockObject( DEFAULT_GUI_FONT));
	pOldFont = pDC->SelectObject(pFont);

	pDC->DrawText(m_strText, &rcTemp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	pDC->SelectObject(pOldFont);
	pDC->SetBkMode(nBkMode);
	pDC->SetTextColor(clrText);
}

BOOL CCoolButton::OnEraseBkgnd(CDC* pDC) 
{
	// 깜빡임을 없애기 위해 배경은 칠하지 않는다
	return TRUE;	
//	return CButton::OnEraseBkgnd(pDC);
}

BOOL CCoolButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// 버튼에서의 마우스 커서를 바꾼다
	::SetCursor(m_hCursor);

	return TRUE;
//	return CButton::OnSetCursor(pWnd, nHitTest, message);
}

void CCoolButton::OnSetFocus(CWnd* pOldWnd) 
{
	CButton::OnSetFocus(pOldWnd);
	
	// 포커스를 버튼이 갖게 되면 화면을 다시 그린다
	Invalidate(FALSE);
}

void CCoolButton::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	// 포커스를 잃게 되면 화면을 다시 그린다
	Invalidate(FALSE);
}

void CCoolButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// 마우스가 버튼 위에서 이동 중이면,
	// 시스템에게 마우스의 버튼 진입과 탈출에 대한 메시지를 보내줄 것을 요청
	TRACKMOUSEEVENT MouseEvent;
	MouseEvent.cbSize		= sizeof(TRACKMOUSEEVENT);
	MouseEvent.dwFlags	= TME_LEAVE | TME_HOVER;
	MouseEvent.hwndTrack	= m_hWnd;
	MouseEvent.dwHoverTime	= 1;
	
	::TrackMouseEvent(&MouseEvent);

	CButton::OnMouseMove(nFlags, point);
}

LRESULT CCoolButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	// 마우스가 버튼에 진입했으므로 버튼 다시 그림
	m_bHover = TRUE;
	Invalidate(FALSE);

	return 0;
}

LRESULT CCoolButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	// 마우스가 버튼에서 탈출했으므로 버튼 다시 그림
	m_bHover = FALSE;
	Invalidate(FALSE);

	return 0;
}

void CCoolButton::OnSize(UINT nType, int cx, int cy) 
{
	CButton::OnSize(nType, cx, cy);
	
	// 버튼의 크기가 변경되었으므로 새 크기를 읽은 후 버튼 다시 그림
	GetClientRect(&m_rcClient);

	RepositionAll();
}

void CCoolButton::RepositionAll()
{
	// 기본 텍스트 위치는 버튼 전체의 중앙
	m_rcText = m_rcClient;

	switch(m_nTextAlign)
	{
	case ALIGN_LEFT:
		// 텍스트를 왼쪽에 배치
		m_ptImage.x = m_rcClient.right - m_bmpInfo.bmWidth - CONST_GAP;
		m_ptImage.y = (m_rcClient.Height() - m_bmpInfo.bmHeight) / 2;
		m_rcText.right = m_ptImage.x;
		break;
	case ALIGN_RIGHT:
		// 텍스트를 오른쪽에 배치
		m_ptImage.x = CONST_GAP;
		m_ptImage.y = (m_rcClient.Height() - m_bmpInfo.bmHeight) / 2;
		m_rcText.left = m_ptImage.x + m_bmpInfo.bmWidth;
		break;
	case ALIGN_TOP:
		// 텍스트를 위쪽에 배치
		m_ptImage.x = (m_rcClient.Width() - m_bmpInfo.bmWidth) / 2;
		m_ptImage.y = m_rcClient.bottom - m_bmpInfo.bmHeight - CONST_GAP;
		m_rcText.bottom = m_ptImage.y;
		break;
	case ALIGN_BOTTOM:
		// 텍스트를 아래쪽에 배치
		m_ptImage.x = (m_rcClient.Width() - m_bmpInfo.bmWidth) / 2;
		m_ptImage.y = CONST_GAP;
		m_rcText.top = m_ptImage.y + m_bmpInfo.bmHeight;
		break;
	case ALIGN_OVER:
		// 텍스트와 이미지를 버튼의 중앙에 배치
		m_ptImage.x = (m_rcClient.Width() - m_bmpInfo.bmWidth) / 2;
		m_ptImage.y = (m_rcClient.Height() - m_bmpInfo.bmHeight) / 2;
		break;
	}

	// 만약 현재 버튼이 윈도우라면 새로 그림
	if(::IsWindow(m_hWnd))		Invalidate(FALSE);
}

// 버튼에 비트맵을 설정하는 함수
void CCoolButton::SetButtonBmp(UINT nBitmapID)
{
	// 이전 비트맵들을 삭제한다
	if(m_bmpImage.m_hObject)			m_bmpImage.DeleteObject();
	if(m_bmpMask.m_hObject)				m_bmpMask.DeleteObject();

	// 새 비트맵을 로드한다
	m_bmpImage.LoadBitmap(nBitmapID);
	m_bmpInfo.bmWidth = m_bmpInfo.bmHeight = 0;

	if(m_bmpImage.m_hObject)
	{
		// 비트맵의 정보를 새로 읽는다
		m_bmpImage.GetBitmap(&m_bmpInfo);
	}

	// 이미지 타입을 비트맵으로 설정한다
	m_nImageType = IMG_BMP;

	// 텍스트와 이미지를 재배치한다
	RepositionAll();
}

// 버튼에 비트맵을 설정하고 투명색을 설정하는 함수
void CCoolButton::SetButtonBmp(UINT nBitmapID, COLORREF clrTransparent)
{
	// 이전 비트맵을 삭제한다
	if(m_bmpImage.m_hObject)		m_bmpImage.DeleteObject();
	if(m_bmpMask.m_hObject)			m_bmpMask.DeleteObject();

	// 새 비트맵을 로드한다
	m_bmpImage.LoadBitmap(nBitmapID);
	m_bmpInfo.bmWidth = m_bmpInfo.bmHeight = 0;

	if(m_bmpImage.m_hObject)
	{
		// 비트맵의 정보를 새로 읽는다
		m_bmpImage.GetBitmap(&m_bmpInfo);
	}

	// 이미지 타입을 비트맵으로 설정한다
	m_nImageType = IMG_BMP;

	COLORREF	clrBmpBk, clrBmpText;

	// 투명색을 저장한다
	m_clrTransparent = clrTransparent;

	CDC BmpDC, MaskDC;
	
	BmpDC.CreateCompatibleDC(NULL);
	MaskDC.CreateCompatibleDC(NULL);

	// 마스크 비트맵을 생성한다 - 마스크 비트맵은 흑백 비트맵이다
	m_bmpMask.CreateBitmap(m_bmpInfo.bmWidth, m_bmpInfo.bmHeight, 1, 1, NULL);

	CBitmap *pOldBmp = BmpDC.SelectObject(&m_bmpImage);
	CBitmap *pOldMask = MaskDC.SelectObject(&m_bmpMask);

	// 원본 비트맵의 DC의 배경색을 투명색으로 설정하고 마스크 비트맵에 복사한다
	// 이때 마스크 비트맵은 흑백이기 때문에,
	// 원본 비트맵 DC의 배경색인 투명색 부분은 1로 설정되고 나머지 부분들은 0으로 설정된다
	clrBmpBk = BmpDC.SetBkColor(m_clrTransparent);
	MaskDC.BitBlt(0, 0, m_bmpInfo.bmWidth, m_bmpInfo.bmHeight, &BmpDC, 0, 0, SRCCOPY);

	// 원본 비트맵의 DC의 글자색을 하얀색으로 하고,
	// 원본 비트맵의 DC의 배경색을 검은색으로 하여 마스크 비트맵과 AND 연산을 한다
	// 마스크 비트맵은 흑백이기 때문에,
	// 1은 배경색인 검정색으로 바뀌고 0은 글자색인 하얀색으로 바뀐다.
	// 결과적으로 원본 비트맵의 투명색 부분과 검정색이 AND되게 되어 검정색이 되고
	// 원본 비트맵의 기타 부분과 하얀색이 AND되게 되어 원본 비트맵을 그대로 유지하게 된다.
	clrBmpText = BmpDC.SetTextColor(RGB(255, 255, 255));
	BmpDC.SetBkColor(RGB(0, 0, 0));
	BmpDC.BitBlt(0, 0, m_bmpInfo.bmWidth, m_bmpInfo.bmHeight, &MaskDC, 0, 0, SRCAND);

	// 원래 색상들을 되돌려 놓는다
	BmpDC.SetTextColor(clrBmpText);
	BmpDC.SetBkColor(clrBmpBk);

	// 원래 비트맵으로 되돌려 놓는다
	BmpDC.SelectObject(pOldBmp);
	MaskDC.SelectObject(pOldMask);

	// DC들을 삭제한다
	BmpDC.DeleteDC();
	MaskDC.DeleteDC();

	// 텍스트와 이미지를 재배치한다
	RepositionAll();
}

// 버튼에 아이콘을 설정하는 함수
void CCoolButton::SetButtonIcon(UINT nIconID)
{
	// 이전 아이콘을 삭제한다
	if(m_hIcon)						::DeleteObject(m_hIcon);

	// 새 아이콘을 로드한다
	m_hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(nIconID));
	m_bmpInfo.bmWidth = m_bmpInfo.bmHeight = 0;

	if(m_hIcon)
	{
		// 아이콘의 크기를 얻어온다
		ICONINFO IconInfo;

		if(::GetIconInfo(m_hIcon, &IconInfo))
		{
			::GetObject(IconInfo.hbmColor, sizeof(BITMAP), &m_bmpInfo);
		}
	}

	// 이미지 타입을 아이콘으로 설정한다
	m_nImageType = IMG_ICON;

	// 텍스트와 이미지를 재배치한다
	RepositionAll();
}

// 평면 버튼인지 설정하는 함수
void CCoolButton::SetFlat(BOOL bFlat)
{
	if(m_bFlat == bFlat)		return;

	m_bFlat = bFlat;

	// 만약 현재 버튼이 윈도우라면 새로 그림
	if(::IsWindow(m_hWnd))		Invalidate(FALSE);
}

// 버튼의 텍스트를 설정하는 함수
void CCoolButton::SetButtonText(LPCTSTR pText)
{
	// 버튼의 텍스트 설정
	m_strText = pText;

	// 텍스트와 이미지를 재배치한다
	RepositionAll();
}

// 버튼의 색상을 리턴하는 함수
COLORREF CCoolButton::GetButtonColor(ENUM_COLOR_TYPE nColor)
{
	if(nColor < 0 || nColor > COLOR_MAX)		return -1;

	return m_clrColors[nColor];
}

// 버튼의 색상을 설정하는 함수
void CCoolButton::SetButtonColor(ENUM_COLOR_TYPE nColor, COLORREF clrColor)
{
	if(nColor < 0 || nColor > COLOR_MAX)		return;

	m_clrColors[nColor] = clrColor;

	// 만약 현재 버튼이 윈도우라면 새로 그림
	if(::IsWindow(m_hWnd))		Invalidate(FALSE);
}

// 버튼에서 텍스트 위치를 설정하는 함수
void CCoolButton::SetTextAlign(ENUM_TEXT_ALIGN nAlign)
{
	m_nTextAlign = nAlign;

	// 텍스트와 이미지를 재배치한다
	RepositionAll();
}

// 버튼의 툴팁을 설정하는 함수
void CCoolButton::SetToolTipText(LPCTSTR pTip)
{
	// 툴팁을 저장하고
	m_strToolTip = pTip;

	// 툴팁 컨트롤을 비활성화 시킨 후
	m_wndToolTip.Activate(FALSE);
	// 툴팁을 갱신하고
	m_wndToolTip.UpdateTipText(m_strToolTip, this, 1);
	// 툴팁 컨트롤을 다시 활성화 시킨다
	m_wndToolTip.Activate(TRUE);
}

void CCoolButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// 버튼이 눌려지지 않은 상태로 만듦
	SendMessage(BM_SETSTATE, FALSE, 0);

	CWnd* pParent = GetParent();
	if( NULL != pParent )
	{
		// 수동으로 클릭 이벤트 발생
		::SendMessage(pParent->m_hWnd, WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
	}
	
	CButton::OnLButtonUp(nFlags, point);
}

void CCoolButton::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// 버튼이 눌려진 상태로 만듦
	SendMessage(BM_SETSTATE, TRUE, 0);
	
	CButton::OnLButtonDblClk(nFlags, point);
}
