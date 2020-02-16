/**************************************************************************************
  Comments : Static ��Ʈ�� ���� ���� �� �̹��� ó���� ���ؼ� ���������
 **************************************************************************************/
// StaticEx.cpp : implementation file
//

#include "stdafx.h"
#include "StaticEx.h"
#include "transparent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticEx

CStaticEx::CStaticEx()
{
	m_textColor = ::GetSysColor(COLOR_WINDOWTEXT);
	m_backColor = ::GetSysColor(COLOR_3DFACE);
	m_backBrush.CreateSolidBrush(m_backColor);
}

CStaticEx::~CStaticEx()
{
	m_backBrush.DeleteObject();
}


BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
	//{{AFX_MSG_MAP(CStaticEx)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticEx message handlers

void CStaticEx::SetTextColor(COLORREF Color)
{
	_ASSERT(::IsWindow(m_hWnd));
	m_textColor = Color;
	Invalidate();
}

void CStaticEx::SetBkColor(COLORREF Color)
{
	_ASSERT(::IsWindow(m_hWnd));
	m_backColor = Color;
	
	m_backBrush.DeleteObject();
	m_backBrush.CreateSolidBrush(m_backColor);
	Invalidate();
}

HBRUSH CStaticEx::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	pDC->SetTextColor(m_textColor);
	pDC->SetBkMode(TRANSPARENT);
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	return (HBRUSH)m_backBrush;
}

void CStaticEx::SetBitmap(UINT nID, BOOL bStretch, COLORREF transColor)
{
	if (GetBitmap()) 
		::DeleteObject(GetBitmap());
	//ModifyStyle(0, SS_BITMAP);//|SS_CENTERIMAGE);
	ModifyStyle(SS_CENTER, SS_BITMAP|SS_CENTERIMAGE,0);

	//Bitmap Size�� ��ư ũ�⸦ ����ؼ� Bitmap ������ ������ �ʰ� �����.
	CBitmap BMP;
	BMP.LoadBitmap(nID);
	if (BMP.GetSafeHandle()==NULL) return;
	BITMAP bm;
	BMP.GetBitmap(&bm);
	//Bitmap Size�� ��ư ũ�⸦ ����ؼ� Bitmap ������ ������ �ʰ� �����.
	CSize bsize;
	CRect rect;
	GetClientRect(rect); //Button Size
	
	//rect.DeflateRect(3, 3);
	if (bStretch) { //Bitmap ũ�⸦ Button�� �����.
		long value1, value2;
		double scale;

		//Scale
		bsize.cx = bm.bmWidth;
		bsize.cy = bm.bmHeight;
		if (bsize.cx > bsize.cy) {
			value1 = rect.Width();
			value2 = bsize.cx;
		} else {
			value1 = rect.Height();
			value2 = bsize.cy;
		}
		if (value2)
			scale = (double)value1 / (double)value2;
		else scale = 1;
		bsize.cx = (int)(bsize.cx * scale)-1;
		bsize.cy = (int)(bsize.cy * scale)-1;
	} else {
		bsize.cx = bm.bmWidth;
		bsize.cy = bm.bmHeight;
	} 	

	CClientDC dc(this);

	CDC dcMem1, dcMem2;
	if (!dcMem1.CreateCompatibleDC(&dc)) return;
	if (!dcMem2.CreateCompatibleDC(&dc)) return;
	
	CBitmap tmpBMP, madeBMP;
	//�о���� �̹����� �޸� DC�� ��´�.
	tmpBMP.CreateCompatibleBitmap(&dc, bm.bmWidth, bm.bmHeight);
	dcMem1.SelectObject(&tmpBMP);
	dcMem1.FillSolidRect(0, 0, bm.bmWidth, bm.bmHeight, m_backColor);
	DrawTransparent(&dcMem1, 0, 0, BMP, transColor);
	//���� �̹����� ���� �޸� DC�� �ʱ�ȭ�Ѵ�.
	madeBMP.CreateCompatibleBitmap(&dc, rect.Width(),rect.Height());
	dcMem2.SelectObject(&madeBMP); //m_bitmap�� dcMem2�� �����Ѵ�.
	//��ư ��� �ʱ�ȭ....
	CRect btnRect;
	GetClientRect(&btnRect);
	dcMem2.FillSolidRect(btnRect, m_backColor);
	//�о���� �̹����� ��ư ������ ���ϴ� ���·� ������Ų��.
	dcMem2.StretchBlt((rect.Width() - bsize.cx) / 2, (rect.Height() - bsize.cy) / 2, 
					 bsize.cx, bsize.cy,//rect.Width(), rect.Height(), 
					 &dcMem1, 0, 0, bm.bmWidth, bm.bmHeight,
					 SRCCOPY); //m_bitmap�� stretch�Ǿ ����.
	CStatic::SetBitmap((HBITMAP)madeBMP);
	madeBMP.Detach();
	dcMem1.DeleteDC();
	dcMem2.DeleteDC();
	BMP.DeleteObject(); //�о���� �̹��� ����
	tmpBMP.DeleteObject(); //�߰� ���� �̹��� ����
	madeBMP.DeleteObject(); //���� ���� �̹��� ����
}
