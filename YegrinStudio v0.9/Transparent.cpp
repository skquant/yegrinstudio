/**************************************************************************************
  �� �� �� : �� â��(Prodori)
  �ۼ����� : 1998-08-04
  �������� : 2002-09-04   
  Comments : 
 **************************************************************************************/
#include "stdafx.h"
#include "transparent.h"

// Function Name	: DrawTransparent
// Description	    : �ش� DC�� �־��� CBitmap ��ü�� Transparent ó����
// Arguments		: 
//			CDC*pDC			: ��� DC
//			int x			: �̹��� ��� ��ǥ(x)
//			int y			: �̹��� ��� ��ǥ(y)
//			CBitmap& orgBMP	: CBitmap �ҽ�
//			COLORREF crColor: ���� ó�� ��
void DrawTransparent(CDC*pDC, int x, int y, CBitmap& orgBMP, COLORREF crColor)
{
	BITMAP bm;
	orgBMP.GetObject(sizeof(BITMAP), &bm);
	CPoint size(bm.bmWidth, bm.bmHeight);
	pDC->DPtoLP(&size);
	CPoint org(0, 0);
	pDC->DPtoLP(&org);

	//�޸� DC(dcImage)�� �����ϰ�, �ű⿡ ��Ʈ���� �����Ѵ�.
	CDC dcImage;
	dcImage.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmapImage = dcImage.SelectObject(&orgBMP);
	dcImage.SetMapMode(pDC->GetMapMode());

	//�ι�° �޸� DC(dcAn)�� �����ϰ�, �� �ȿ� AND ����ũ�� �����
	CDC dcAnd;
	dcAnd.CreateCompatibleDC(pDC);
	dcAnd.SetMapMode(pDC->GetMapMode());

	CBitmap bitmapAnd;
	bitmapAnd.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
	CBitmap* pOldBitmapAnd = dcAnd.SelectObject(&bitmapAnd);

	dcImage.SetBkColor(crColor);
	dcAnd.BitBlt(org.x, org.y, size.x, size.y, &dcImage, org.x, org.y, SRCCOPY);

	//����° �޸� DC(dcXor)�� �����ϰ�, �� �ȿ� XOR ����ũ�� �����
	CDC dcXor;
	dcXor.CreateCompatibleDC(pDC);
	dcXor.SetMapMode(pDC->GetMapMode());

	CBitmap bitmapXor;
	bitmapXor.CreateCompatibleBitmap(&dcImage, bm.bmWidth, bm.bmHeight);
	CBitmap* pOldBitmapXor = dcXor.SelectObject(&bitmapXor);

	dcXor.BitBlt(org.x, org.y, size.x, size.y, &dcImage, org.x, org.y, SRCCOPY);

	dcXor.BitBlt(org.x, org.y, size.x, size.y, &dcAnd, org.x, org.y, 0x220326);
	//0x220326 dcXor = (NOT dcAnd) AND dcXor

	//���� �簢�� ���� �Ƚ��� �ӽ� �޸� DC(dcTemp)�� �����Ѵ�.
	CDC dcTemp;
	dcTemp.CreateCompatibleDC(pDC);
	dcTemp.SetMapMode(pDC->GetMapMode());

	CBitmap bitmapTemp;
	bitmapTemp.CreateCompatibleBitmap(&dcImage, bm.bmWidth, bm.bmHeight);
	CBitmap* pOldBitmapTemp = dcTemp.SelectObject(&bitmapTemp);

	dcTemp.BitBlt(org.x, org.y, size.x, size.y, pDC, x, y, SRCCOPY);

	//AND�� XOR ����ũ�� ������ ������ �̹����� �ӽ� �޸� DC���� �̹����� �����Ѵ�.
	dcTemp.BitBlt(org.x, org.y, size.x, size.y, &dcAnd, org.x, org.y, SRCAND);

	dcTemp.BitBlt(org.x, org.y, size.x, size.y, &dcXor, org.x, org.y, SRCINVERT);

	//ȭ�鿡 ��� �̹����� ���Ѵ�.
	pDC->BitBlt(x, y, size.x, size.y, &dcTemp, org.x, org.y, SRCCOPY);

	//�⺻ ��Ʈ���� �����Ѵ�.
	dcTemp.SelectObject(pOldBitmapTemp);
	dcXor.SelectObject(pOldBitmapXor);
	dcAnd.SelectObject(pOldBitmapAnd);
	dcImage.SelectObject(pOldBitmapImage);
}