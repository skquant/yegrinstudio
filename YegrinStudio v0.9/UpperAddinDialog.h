#if !defined(AFX_UPPERADDINDIALOG_H__4E6B2AF6_94C5_4D2F_8995_0F83681899A7__INCLUDED_)
#define AFX_UPPERADDINDIALOG_H__4E6B2AF6_94C5_4D2F_8995_0F83681899A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpperAddinDialog.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CUpperAddinDialog dialog
#include "CoolButton.h"
#include "BtnST.h"
#include "CCheckSK.h"
#include "StaticEx.h"
#include "MatrixStatic.h"

class CXTabCtrl;
class CCoolButton;
class CMatrixStatic;

class CUpperAddinDialog : public CDialog
{
// Construction
public:
	CUpperAddinDialog(CWnd* pParent = NULL);   // standard constructor
	CXTabCtrl* m_pTab;	
// Dialog Data
	//{{AFX_DATA(CUpperAddinDialog)
	enum { IDD = IDD_UPPER_DIALOG };
	CSpinButtonCtrl	m_SpinDevB2Info;
	CSpinButtonCtrl	m_SpinDevB1Info;
	CSpinButtonCtrl	m_SpinDevAInfo;
	CMatrixStatic	m_LcdB2DevInfo;
	CMatrixStatic	m_LcdB1DevInfo;
	CMatrixStatic	m_LcdADevInfo;
	CStatic	m_ImageFunctions;
	CStatic		m_ImageCharge2;
	CStatic		m_ImageCharge1;
	CStatic		m_ImageMode;
	CStatic		m_ImageHold;
	CStatic		m_ImageTest;
	CStatic		m_ImageSound;
	CStatic		m_ImageRF;
	CStatic		m_ImagePCell;
	CStatic		m_ImageModl4;
	CStatic		m_ImageModl3;
	CStatic		m_ImageModl2;
	CStatic		m_ImageModl1;
	//}}AFX_DATA
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpperAddinDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUpperAddinDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnModlButton();
	afx_msg void OnSoundButton();
	afx_msg void OnModeButton();
	afx_msg void OnHoldButton();
	afx_msg void OnPcellButton();
	afx_msg void OnRfButton();
	afx_msg void OnChargeButton();
	afx_msg void OnTestButton();
	afx_msg void OnButtonA();
	afx_msg void OnButtonB1();
	afx_msg void OnButtonB2();
	afx_msg void OnPaint();
	afx_msg void OnDeltaposSpinDevainfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinDevb1info(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinDevb2info(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBitmap m_OnOffImage;
	void SetBitmap(UINT nID, CBitmap* BitmapObject,CStatic* PictureObject );
	//BOOL bModl[4];
	int	 nBodlCheck;

	BOOL bSound;
	BOOL bMode;
	BOOL bHold;
	BOOL bPcell;
	BOOL bRf;
	BOOL Charge1;
	BOOL bTest;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPPERADDINDIALOG_H__4E6B2AF6_94C5_4D2F_8995_0F83681899A7__INCLUDED_)
