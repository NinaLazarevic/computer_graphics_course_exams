
// RG-I-Kol-2013View.h : interface of the CRGIKol2013View class
//

#pragma once
#include "DImage.h"


class CRGIKol2013View : public CView
{
protected: // create from serialization only
	CRGIKol2013View();
	DECLARE_DYNCREATE(CRGIKol2013View)

// Attributes
public:
	CRGIKol2013Doc* GetDocument() const;

	double pi = 3.1415926535897932384626433832;

	double toRad = pi / 180;

	double m_angle;
	double m_pomeraj;
	double granicaZaShuriken;

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

	virtual void DrawBlade(CDC* pDC, int size);
	virtual void Translate(CDC* pDC, double x, double y);
	virtual void Rotate(CDC* pDC, float angle);
	virtual void DrawStar(CDC* pDC, int size);

	virtual void IscrtajBitmapuNebo(CDC* pDC,CRect kraj);
	virtual void IscrtajBitmapuDrvo(CDC* pDC, CRect  kraj);

// Implementation
public:
	virtual ~CRGIKol2013View();
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

#ifndef _DEBUG  // debug version in RG-I-Kol-2013View.cpp
inline CRGIKol2013Doc* CRGIKol2013View::GetDocument() const
   { return reinterpret_cast<CRGIKol2013Doc*>(m_pDocument); }
#endif

