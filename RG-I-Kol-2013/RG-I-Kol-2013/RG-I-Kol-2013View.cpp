
// RG-I-Kol-2013View.cpp : implementation of the CRGIKol2013View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RG-I-Kol-2013.h"
#endif

#include "RG-I-Kol-2013Doc.h"
#include "RG-I-Kol-2013View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRGIKol2013View

IMPLEMENT_DYNCREATE(CRGIKol2013View, CView)

BEGIN_MESSAGE_MAP(CRGIKol2013View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CRGIKol2013View construction/destruction

CRGIKol2013View::CRGIKol2013View()
{
	m_angle = 0;
	m_pomeraj = 0;

	granicaZaShuriken = 1300;

}

CRGIKol2013View::~CRGIKol2013View()
{
}

BOOL CRGIKol2013View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRGIKol2013View drawing

void CRGIKol2013View::OnDraw(CDC* pDC)
{
	CRGIKol2013Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	
	CRect rect;
	GetClientRect(rect);

	/*pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(1300, 900);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetViewportOrg(0, 0);*/

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	/*memDC->SetMapMode(MM_ANISOTROPIC);
	memDC->SetWindowExt(1300, 900);
	memDC->SetViewportExt(rect.right, rect.bottom);
	memDC->SetViewportOrg(0, 0);*/

	memDC->SelectObject(&memBitmap);

	//iscrtavanje
	int prevMode = SetGraphicsMode(memDC->m_hDC, GM_ADVANCED);

	granicaZaShuriken = rect.right;
	IscrtajBitmapuNebo(memDC,rect);
	
	DrawStar(memDC, 320);
	IscrtajBitmapuDrvo(memDC,rect);

	SetGraphicsMode(memDC->m_hDC, prevMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;



}


// CRGIKol2013View printing

BOOL CRGIKol2013View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRGIKol2013View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRGIKol2013View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CRGIKol2013View::DrawBlade(CDC * pDC, int size)
{

	CPen siva(PS_SOLID, 1, RGB(192, 192, 192));
	CPen* oldPen = pDC->SelectObject(&siva);

	CBrush prviKrak(RGB(211, 211, 211));
	CBrush drugiKrak(RGB(169, 169, 169));
	CBrush* oldBrush = pDC->SelectObject(&prviKrak);

	pDC->SetViewportOrg(100, 200);
	CPoint prviTrougao[3];
	prviTrougao[0].x = 0; prviTrougao[0].y = 0;
	prviTrougao[1].x = 0; prviTrougao[1].y = -4 * size;
	prviTrougao[2].x = - size ; prviTrougao[2].y = -size;

	pDC->Polygon(prviTrougao, 3);

	CPoint drugiTrougao[3];
	drugiTrougao[0].x = 0; drugiTrougao[0].y = 0;
	drugiTrougao[1].x = 0; drugiTrougao[1].y = -4 * size;
	drugiTrougao[2].x = size ; drugiTrougao[2].y = -size;

	pDC->SelectObject(&drugiKrak);
	pDC->Polygon(drugiTrougao, 3);

	int nHeight = 0.7*size; // OVO MORA DA SE NAVEDE
	int nWidth = 0;
	int nEsc = 0;
	int nOrient = 0;
	int nWeight = 0;
	BYTE bItalic = 0;
	BYTE bUnderline = 0;
	BYTE cStrikeOut = 0;
	BYTE nCharSet = 0;
	BYTE nOutPrecision = 0;
	BYTE nClipPrecision = 0;
	BYTE nQuality = 0;
	BYTE nPitchAndFamily = 0;
	CString sFaceName = CString("Monotype Corsiva"); // OVO MORA DA SE NAVEDE
	CFont font;
	font.CreateFont(nHeight, nWidth, nEsc, nOrient, nWeight, bItalic, bUnderline, cStrikeOut,
		nCharSet, nOutPrecision, nClipPrecision, nQuality, nPitchAndFamily, sFaceName);

	CFont* oldFont = pDC->SelectObject(&font);

	XFORM  XformOld;
	bool b = GetWorldTransform(pDC->m_hDC, &XformOld);
	int oldMode = pDC->SetBkMode(TRANSPARENT);
	Rotate(pDC, -90);
	pDC->SetTextColor(RGB(51, 51, 51));
	pDC->TextOut(size / 2, -2 * size / 5, CString("Shuricane"));

	b = SetWorldTransform(pDC->m_hDC, &XformOld);


	pDC->SetViewportOrg(0, 0);
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldFont);
	pDC->SetBkMode(oldMode);

	siva.DeleteObject();
	prviKrak.DeleteObject();
	drugiKrak.DeleteObject();
	font.DeleteObject();

}

void CRGIKol2013View::Translate(CDC * pDC, double x, double y)
{
	XFORM trans;
	trans.eM11 = 1;
	trans.eM12 = 0;
	trans.eM21 = 0;
	trans.eM22 = 1;
	trans.eDx = x;
	trans.eDy = y;

	pDC->ModifyWorldTransform(&trans, MWT_LEFTMULTIPLY);

}

void CRGIKol2013View::Rotate(CDC * pDC, float angle)
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

void CRGIKol2013View::DrawStar(CDC * pDC, int size)
{
	//granicaZaShuriken = granicaZaShuriken - drvo.Width();
	//prethodno smo oduzeli od sirine ekrana (1300) sirinu drveta, sad treba da dodamo 10% precnika

	granicaZaShuriken += size / 10;

	//size - precnik, a u f-ji drawBlade size je 1/4 duzine kraka
	int ang = 0;
	XFORM  XformOld;
	bool b = GetWorldTransform(pDC->m_hDC, &XformOld);

	Translate(pDC, m_pomeraj, 0);
	Rotate(pDC, m_angle);

	for (int i = 0; i < 4; i++)
	{

		XFORM  XformOld;
		bool b = GetWorldTransform(pDC->m_hDC, &XformOld);

		Rotate(pDC, ang);

		DrawBlade(pDC, size/8);
		ang += 90;
		b = SetWorldTransform(pDC->m_hDC, &XformOld);

	}

	b = SetWorldTransform(pDC->m_hDC, &XformOld);

}

void CRGIKol2013View::IscrtajBitmapuNebo(CDC * pDC, CRect  kraj)
{
	DImage nebo;
	nebo.Load(CString("sky.jpg"));
	XFORM  XformOld;
	bool b = GetWorldTransform(pDC->m_hDC, &XformOld);
	XFORM scaleForm;

	scaleForm.eM11 = 1;
	scaleForm.eM12 = 0;
	scaleForm.eM21 = 0;
	scaleForm.eM22 = 1.6; //900/580 = 1,5517..  580-visina do koje je nebo na slici, preko je zeleno polje
	scaleForm.eDx = 0;
	scaleForm.eDy = 0;


	b = ModifyWorldTransform(pDC->m_hDC, &scaleForm, MWT_LEFTMULTIPLY);

	CRect neboRect(0, 0, nebo.Width(), nebo.Height());
	CRect pozadinaRect(0, 0, kraj.right, kraj.bottom);

	nebo.Draw(pDC, neboRect, pozadinaRect);

	b = SetWorldTransform(pDC->m_hDC, &XformOld);

	
}

void CRGIKol2013View::IscrtajBitmapuDrvo(CDC * pDC, CRect  kraj)
{
	DImage drvo;
	drvo.Load(CString("bark.jpg"));
	XFORM  XformOld;
	bool b = GetWorldTransform(pDC->m_hDC, &XformOld);

	XFORM scaleForm;
	scaleForm.eM11 = 1;
	scaleForm.eM12 = 0;
	scaleForm.eM21 = 0;
	scaleForm.eM22 = 1300 / drvo.Height();
	scaleForm.eDx = 0;
	scaleForm.eDy = 0;


	b = ModifyWorldTransform(pDC->m_hDC, &scaleForm, MWT_LEFTMULTIPLY);

	CRect drvoRect(0, 0, drvo.Width(), drvo.Height());
	CRect pozRect(kraj.right - drvo.Width(), 0, kraj.right, drvo.Height());
	drvo.Draw(pDC, drvoRect, pozRect);

	b = SetWorldTransform(pDC->m_hDC, &XformOld);

	granicaZaShuriken = kraj.right - drvo.Width();
}


// CRGIKol2013View diagnostics

#ifdef _DEBUG
void CRGIKol2013View::AssertValid() const
{
	CView::AssertValid();
}

void CRGIKol2013View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRGIKol2013Doc* CRGIKol2013View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRGIKol2013Doc)));
	return (CRGIKol2013Doc*)m_pDocument;
}
#endif //_DEBUG


// CRGIKol2013View message handlers


BOOL CRGIKol2013View::OnEraseBkgnd(CDC* pDC)
{
	 return TRUE;

	/*return CView::OnEraseBkgnd(pDC);*/
}


void CRGIKol2013View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'W' || nChar == 'w')
	{
		if ((m_pomeraj + 20) <= (granicaZaShuriken - 100)) //centar je u 100,200
		{
			m_pomeraj += 20;
			m_angle += 10;
		}
		Invalidate();
	}
	else
		return;

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
