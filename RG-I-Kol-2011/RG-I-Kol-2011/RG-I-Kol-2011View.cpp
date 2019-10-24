
// RG-I-Kol-2011View.cpp : implementation of the CRGIKol2011View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RG-I-Kol-2011.h"
#endif

#include "RG-I-Kol-2011Doc.h"
#include "RG-I-Kol-2011View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRGIKol2011View

IMPLEMENT_DYNCREATE(CRGIKol2011View, CView)

BEGIN_MESSAGE_MAP(CRGIKol2011View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CRGIKol2011View construction/destruction

CRGIKol2011View::CRGIKol2011View()
{
	nebo.Load(CString("sky.jpg"));

	clio = GetEnhMetaFile(CString("clio.emf"));
	wheel = GetEnhMetaFile(CString("tocak.emf"));

	pomerajX = 0;
	angle = 0;
	desno = true;
	

}

CRGIKol2011View::~CRGIKol2011View()
{
}

BOOL CRGIKol2011View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRGIKol2011View drawing

void CRGIKol2011View::OnDraw(CDC* pDC)
{
	CRGIKol2011Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clientRect;
	GetClientRect(&clientRect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap glavna;
	glavna.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());

	memDC->SelectObject(&glavna);
	int prevMode = SetGraphicsMode(memDC->m_hDC, GM_ADVANCED);
	//

	CRect neboRect(0, 0, nebo.Width(), nebo.Height());
	CRect pozadina(0, 0, clientRect.Width(), clientRect.Height());
	nebo.Draw(memDC, neboRect, pozadina);

	IscrtajBilbord(memDC, clientRect);

	//
	SetGraphicsMode(memDC->m_hDC, prevMode);
	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;


}


// CRGIKol2011View printing

BOOL CRGIKol2011View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRGIKol2011View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRGIKol2011View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CRGIKol2011View::Translate(CDC * pDC, double x)
{
	XFORM trans;
	trans.eM11 = 1;
	trans.eM12 = 0;
	trans.eM21 = 0;
	trans.eM22 = 1;
	trans.eDx = x;
	trans.eDy = 0;

	pDC->ModifyWorldTransform(&trans, MWT_LEFTMULTIPLY);
}

void CRGIKol2011View::Rotate(CDC * pDC, float angle)
{
	XFORM rot;
	rot.eM11 = cos(angle*toRad);
	rot.eM12 = sin(angle*toRad);
	rot.eM21 = -sin(angle*toRad);
	rot.eM22 = cos(angle*toRad);
	rot.eDx = 0;
	rot.eDy = 0;

	pDC->ModifyWorldTransform(&rot, MWT_LEFTMULTIPLY);
}

void CRGIKol2011View::IscrtajBilbord(CDC * pDC, CRect clrect)
{
	//dimenzije clio.emf su 645 x 260
	CRect clioRectPom(clrect.Width() / 2 - 645 / 2 + pomerajX, clrect.Height() / 2 - 260 / 2, clrect.Width() / 2 + 645 / 2 + pomerajX,clrect.Height() / 2 + 260 / 2);
	CRect clioRect(clrect.Width() / 2 - 645 / 2, clrect.Height() / 2 - 260 / 2, clrect.Width() / 2 + 645 / 2, clrect.Height() / 2 + 260 / 2);

	//beli okvir
	CRect beliOkvir(clioRect.left - 40, clioRect.top - 40, clioRect.right + 40, clioRect.bottom + 40);
	//sivi okvir
	CRect siviOkvir(clioRect.left - 80, clioRect.top - 80, clioRect.right + 80, clioRect.bottom + 80);

	//crna senka
	CRect crnaSenka(siviOkvir.left + 5, siviOkvir.top + 5, siviOkvir.right + 5, siviOkvir.bottom + 5);

	CRect crnaSenkaManjiOkvir(beliOkvir.left + 5, beliOkvir.top + 5, beliOkvir.right + 5, beliOkvir.bottom + 5);

	//crno postolje
	CRect postolje(clrect.Width() / 2 - 100, clrect.Height() / 2, clrect.Width() / 2 + 100, clrect.Height());

	CBrush sivaB(RGB(169, 169, 169));
	CPen sivaP(PS_SOLID, 1, RGB(169, 169, 169));

	CBrush belaB(RGB(255, 255, 255));
	CPen belaP(PS_SOLID, 1, RGB(255, 255, 255));

	CBrush crnaB(RGB(0, 0, 0));
	CBrush* oldB = pDC->SelectObject(&crnaB);

	CPen crnaP(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldP = pDC->SelectObject(&crnaP);

	pDC->Rectangle(&postolje);

	pDC->RoundRect(crnaSenka.left,crnaSenka.top,crnaSenka.right,crnaSenka.bottom, 30, 30);

	pDC->SelectObject(&sivaB);
	pDC->SelectObject(&sivaP);
	pDC->RoundRect(siviOkvir.left, siviOkvir.top, siviOkvir.right, siviOkvir.bottom, 30, 30);

	pDC->SelectObject(&crnaB);
	pDC->SelectObject(&crnaP);
	pDC->RoundRect(crnaSenkaManjiOkvir.left, crnaSenkaManjiOkvir.top, crnaSenkaManjiOkvir.right,crnaSenkaManjiOkvir.bottom, 30, 30);

	pDC->SelectObject(&belaB);
	pDC->SelectObject(&belaP);
	pDC->RoundRect(beliOkvir.left, beliOkvir.top, beliOkvir.right, beliOkvir.bottom, 30, 30);

	PlayEnhMetaFile(pDC->m_hDC, clio, clioRectPom);

	XFORM oldF;
	pDC->GetWorldTransform(&oldF);
	pDC->SetViewportOrg(clioRect.left + 128, clioRect.top + 236);
	
	Translate(pDC, pomerajX);
	Rotate(pDC, angle);
	

	CRect prviTocak(-50, -50, 50, 50);

	PlayEnhMetaFile(pDC->m_hDC, wheel, prviTocak);


	pDC->SetViewportOrg(clrect.left,clrect.top);

	pDC->SetViewportOrg(clioRect.left + 544, clioRect.top + 236);

	/*Translate(pDC, pomerajX);
	Rotate(pDC, angle);*/

	CRect drugiTocak(-50, -50, 50, 50);

	PlayEnhMetaFile(pDC->m_hDC, wheel, drugiTocak);

	pDC->SetViewportOrg(clrect.left, clrect.top);


	SetWorldTransform(pDC->m_hDC, &oldF);

	pDC->SelectObject(oldB);
	pDC->SelectObject(oldP);

	belaB.DeleteObject();
	belaP.DeleteObject();
	sivaB.DeleteObject();
	sivaP.DeleteObject();
	crnaB.DeleteObject();
	crnaP.DeleteObject();
}


// CRGIKol2011View diagnostics

#ifdef _DEBUG
void CRGIKol2011View::AssertValid() const
{
	CView::AssertValid();
}

void CRGIKol2011View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRGIKol2011Doc* CRGIKol2011View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRGIKol2011Doc)));
	return (CRGIKol2011Doc*)m_pDocument;
}
#endif //_DEBUG


// CRGIKol2011View message handlers


void CRGIKol2011View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != VK_LEFT && nChar != VK_RIGHT)
	{
		return;
	}

	if (nChar == VK_LEFT)
	{
		if (pomerajX <= -40)
			return;
		desno = false;
		angle -= 15;
		pomerajX -= 5;
		Invalidate();
	}
	if (nChar == VK_RIGHT)
	{
		if (pomerajX >= 40)
			return;
		desno = true;
		angle += 15;
		pomerajX += 5;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CRGIKol2011View::OnEraseBkgnd(CDC* pDC)
{

	return TRUE;
}
