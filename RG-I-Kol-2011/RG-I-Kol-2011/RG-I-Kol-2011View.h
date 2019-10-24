
// RG-I-Kol-2011View.h : interface of the CRGIKol2011View class
//

#pragma once
#include "DImage.h"

class CRGIKol2011View : public CView
{
protected: // create from serialization only
	CRGIKol2011View();
	DECLARE_DYNCREATE(CRGIKol2011View)

// Attributes
public:
	CRGIKol2011Doc* GetDocument() const;

	double pi = 3.1415926535897932384626433832;

	double toRad = pi / 180;

	DImage nebo;

	/*CMetaFileDC clio;
	CMetaFileDC wheel;*/

	HENHMETAFILE clio;
	HENHMETAFILE wheel;

	int pomerajX;
	float angle;

	bool desno;

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

	virtual void Translate(CDC* pDC, double x);
	virtual void Rotate(CDC* pDC, float angle);

	virtual void IscrtajBilbord(CDC* pDC,CRect clrect);

// Implementation
public:
	virtual ~CRGIKol2011View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in RG-I-Kol-2011View.cpp
inline CRGIKol2011Doc* CRGIKol2011View::GetDocument() const
   { return reinterpret_cast<CRGIKol2011Doc*>(m_pDocument); }
#endif

