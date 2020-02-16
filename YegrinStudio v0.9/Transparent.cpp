/**************************************************************************************
  작 성 자 : 안 창근(Prodori)
  작성일자 : 1998-08-04
  수정일자 : 2002-09-04   
  Comments : 
 **************************************************************************************/
#include "stdafx.h"
#include "transparent.h"

// Function Name	: DrawTransparent
// Description	    : 해당 DC에 주어진 CBitmap 개체를 Transparent 처리함
// Arguments		: 
//			CDC*pDC			: 대상 DC
//			int x			: 이미지 출력 좌표(x)
//			int y			: 이미지 출력 좌표(y)
//			CBitmap& orgBMP	: CBitmap 소스
//			COLORREF crColor: 투명 처리 색
void DrawTransparent(CDC*pDC, int x, int y, CBitmap& orgBMP, COLORREF crColor)
{
	BITMAP bm;
	orgBMP.GetObject(sizeof(BITMAP), &bm);
	CPoint size(bm.bmWidth, bm.bmHeight);
	pDC->DPtoLP(&size);
	CPoint org(0, 0);
	pDC->DPtoLP(&org);

	//메모리 DC(dcImage)를 생성하고, 거기에 비트맵을 선택한다.
	CDC dcImage;
	dcImage.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmapImage = dcImage.SelectObject(&orgBMP);
	dcImage.SetMapMode(pDC->GetMapMode());

	//두번째 메모리 DC(dcAn)를 생성하고, 그 안에 AND 마스크를 만든다
	CDC dcAnd;
	dcAnd.CreateCompatibleDC(pDC);
	dcAnd.SetMapMode(pDC->GetMapMode());

	CBitmap bitmapAnd;
	bitmapAnd.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
	CBitmap* pOldBitmapAnd = dcAnd.SelectObject(&bitmapAnd);

	dcImage.SetBkColor(crColor);
	dcAnd.BitBlt(org.x, org.y, size.x, size.y, &dcImage, org.x, org.y, SRCCOPY);

	//세번째 메모리 DC(dcXor)를 생성하고, 그 안에 XOR 마스크를 만든다
	CDC dcXor;
	dcXor.CreateCompatibleDC(pDC);
	dcXor.SetMapMode(pDC->GetMapMode());

	CBitmap bitmapXor;
	bitmapXor.CreateCompatibleBitmap(&dcImage, bm.bmWidth, bm.bmHeight);
	CBitmap* pOldBitmapXor = dcXor.SelectObject(&bitmapXor);

	dcXor.BitBlt(org.x, org.y, size.x, size.y, &dcImage, org.x, org.y, SRCCOPY);

	dcXor.BitBlt(org.x, org.y, size.x, size.y, &dcAnd, org.x, org.y, 0x220326);
	//0x220326 dcXor = (NOT dcAnd) AND dcXor

	//목적 사각형 안의 픽실을 임시 메모리 DC(dcTemp)로 복사한다.
	CDC dcTemp;
	dcTemp.CreateCompatibleDC(pDC);
	dcTemp.SetMapMode(pDC->GetMapMode());

	CBitmap bitmapTemp;
	bitmapTemp.CreateCompatibleBitmap(&dcImage, bm.bmWidth, bm.bmHeight);
	CBitmap* pOldBitmapTemp = dcTemp.SelectObject(&bitmapTemp);

	dcTemp.BitBlt(org.x, org.y, size.x, size.y, pDC, x, y, SRCCOPY);

	//AND와 XOR 마스크를 적용한 마지막 이미지를 임시 메모리 DC안의 이미지로 생성한다.
	dcTemp.BitBlt(org.x, org.y, size.x, size.y, &dcAnd, org.x, org.y, SRCAND);

	dcTemp.BitBlt(org.x, org.y, size.x, size.y, &dcXor, org.x, org.y, SRCINVERT);

	//화면에 결과 이미지를 블릿한다.
	pDC->BitBlt(x, y, size.x, size.y, &dcTemp, org.x, org.y, SRCCOPY);

	//기본 비트맵을 복원한다.
	dcTemp.SelectObject(pOldBitmapTemp);
	dcXor.SelectObject(pOldBitmapXor);
	dcAnd.SelectObject(pOldBitmapAnd);
	dcImage.SelectObject(pOldBitmapImage);
}