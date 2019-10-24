
// RG-I-Kol-2017View.h : interface of the CRGIKol2017View class
//

#pragma once
#include "DImage.h"

class CRGIKol2017View : public CView
{
protected: // create from serialization only
	CRGIKol2017View();
	DECLARE_DYNCREATE(CRGIKol2017View)

// Attributes
public:
	CRGIKol2017Doc* GetDocument() const;

	double pi = 3.1415926535897932384626433832795;

	double toRad = pi / 180;

	//pomeranje pozadinske slike
	int gore;
	int dole;
	int levo;
	int desno;

	//pomeranje robota
	int desnoRobot;
	int ugaoPrednjeNoge;
	int ugaoZadnjeNoge;

	int smerP;
	int smerZ;

	//uvecanje robota
	float sc;

	DImage* Background;
	DImage* Body;
	DImage* Leg1;
	DImage* Leg2;
	DImage* Leg3;


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

	void LoadIdentity(CDC* pDC);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);

	void DrawScene(CDC* pDC, CRect rect);
	void DrawLeg(CDC* pDC, double alpha, double dx, double dy);
	void DrawTransparentBitmap(CDC * pDC, DImage bitmapa);

// Implementation
public:
	virtual ~CRGIKol2017View();
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

#ifndef _DEBUG  // debug version in RG-I-Kol-2017View.cpp
inline CRGIKol2017Doc* CRGIKol2017View::GetDocument() const
   { return reinterpret_cast<CRGIKol2017Doc*>(m_pDocument); }
#endif

