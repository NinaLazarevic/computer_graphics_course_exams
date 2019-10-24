
// RG-I-Kol-2012View.h : interface of the CRGIKol2012View class
//

#pragma once


class CRGIKol2012View : public CView
{
protected: // create from serialization only
	CRGIKol2012View();
	DECLARE_DYNCREATE(CRGIKol2012View)

// Attributes
public:
	CRGIKol2012Doc* GetDocument() const;

	double pi = 3.1415926535897932384626433832795;
	double toRad = pi / 180;

	float ang;

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

	virtual void Trapez(CDC* pDC, int a, int b, int h);
	virtual void Translate(CDC* pDC, float x, float y);
	virtual void Rotate(CDC* pDC, float a);
	virtual void DrawGear(CDC* pDC, int spokeCount, int spokeWidth);
	virtual void DrawScene(CDC* pDC);

// Implementation
public:
	virtual ~CRGIKol2012View();
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

#ifndef _DEBUG  // debug version in RG-I-Kol-2012View.cpp
inline CRGIKol2012Doc* CRGIKol2012View::GetDocument() const
   { return reinterpret_cast<CRGIKol2012Doc*>(m_pDocument); }
#endif

