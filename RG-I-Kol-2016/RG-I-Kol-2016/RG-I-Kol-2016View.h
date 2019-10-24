
// RG-I-Kol-2016View.h : interface of the CRGIKol2016View class
//

#pragma once
#include "DImage.h"

class CRGIKol2016View : public CView
{
protected: // create from serialization only
	CRGIKol2016View();
	DECLARE_DYNCREATE(CRGIKol2016View)

// Attributes
public:
	CRGIKol2016Doc* GetDocument() const;

	double pi = 3.1415926535897932384626433832795;

	double toRad = pi / 180;

	DImage okvir;
	DImage povrsinaStola;

	bool kuglaDodirnuta;
	bool prviPutDodirnuta;

	float angle; //ugao za stap u odnosu na sto
	float angleKugla; //ugao za kuglu u odnosu na sto

	float angleRotiranjaKugle; //ugao za koji se kugla rotira kad se udari

	float pomerajKugla;
	float pomerajStap;

	float poluprecnikKugle;


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

	virtual void DrawStick(CDC* pDC, int w);
	virtual void DrawBall(CDC* pDC, int w);
	virtual void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	virtual void Rotate(CDC* pDC, float angle, bool rightMultiply);

	virtual void DrawTable(CDC* pDC, CRect rect);
	virtual void DrawBorder(CDC* pDC, CRect rect, int w);
	virtual void DrawHoles(CDC* pDC, CRect rect, int size);


// Implementation
public:
	virtual ~CRGIKol2016View();
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

#ifndef _DEBUG  // debug version in RG-I-Kol-2016View.cpp
inline CRGIKol2016Doc* CRGIKol2016View::GetDocument() const
   { return reinterpret_cast<CRGIKol2016Doc*>(m_pDocument); }
#endif

