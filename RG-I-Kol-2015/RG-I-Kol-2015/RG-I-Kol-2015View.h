
// RG-I-Kol-2015View.h : interface of the CRGIKol2015View class
//

#pragma once
#include "DImage.h"

class CRGIKol2015View : public CView
{
protected: // create from serialization only
	CRGIKol2015View();
	DECLARE_DYNCREATE(CRGIKol2015View)

// Attributes
public:
	CRGIKol2015Doc* GetDocument() const;

	double pi = 3.1415926535897932384626433832795;

	double toRad = pi / 180;

	DImage bitmapa;

	bool end;
	bool gore;
	bool dole;
	bool levo;

	bool otvorenaUsta;

	int pomerajX;
	int pomerajY;

	float packman_angle;

	CPoint centarPackmana;
	CPoint centarDuha;

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

	virtual void DrawPacman(CDC* pDC, CRect rect, float angle);
	virtual void DrawGhost(CDC* pDC, CRect rect);

	virtual void Translate(CDC* pDC, float x, float y);
	virtual void Rotate(CDC* pDC, float angle);
	virtual void Reflect(CDC* pDC, bool levo);

	virtual void DrawEnd(CDC*pDC, CRect rect);

// Implementation
public:
	virtual ~CRGIKol2015View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in RG-I-Kol-2015View.cpp
inline CRGIKol2015Doc* CRGIKol2015View::GetDocument() const
   { return reinterpret_cast<CRGIKol2015Doc*>(m_pDocument); }
#endif

