
// ZadaciSaIspitaGDIView.h : interface of the CZadaciSaIspitaGDIView class
//

#pragma once
#include <string>
#include "DImage.h"


class CZadaciSaIspitaGDIView : public CView
{
protected: // create from serialization only
	CZadaciSaIspitaGDIView();
	DECLARE_DYNCREATE(CZadaciSaIspitaGDIView)

// Attributes
public:
	CZadaciSaIspitaGDIDoc* GetDocument() const;

	double pi = 3.1415926535897932384626433832795;

	double toRad = pi / 180;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


	virtual void Translate(CDC* pDC, float x, float y);
	virtual void Rotate(CDC* pDC, float angle);

	////03.06.2015.
	void DrawBackground(CDC *pDC, CPoint ptCenter, int radius, CString strPicture);
	void DrawCoin(CDC *pDC, CPoint ptCenter, int radius, CString strText, int fsizeText, CString strCoin, int fsizeCoin,
		COLORREF clrText);
	void SaveBMP(CString name, CDC *pDC, CPoint ptCenter, int radius);

	////05.10.2011.
	void DrawFigure(CDC *pDC, int size, COLORREF colFill, COLORREF colLine);
	void DrawComplexFigure(CDC *pDC, int size, COLORREF colFill[], COLORREF colLine, double ratio, CString str);
	void DrawPicture(CDC *pDC, int size, COLORREF colFill[], COLORREF colLine, double ratio, int row, int col);

// Implementation
public:
	virtual ~CZadaciSaIspitaGDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ZadaciSaIspitaGDIView.cpp
inline CZadaciSaIspitaGDIDoc* CZadaciSaIspitaGDIView::GetDocument() const
   { return reinterpret_cast<CZadaciSaIspitaGDIDoc*>(m_pDocument); }
#endif

