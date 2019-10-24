
// RG-I-Kol-2012View.cpp : implementation of the CRGIKol2012View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RG-I-Kol-2012.h"
#endif

#include "RG-I-Kol-2012Doc.h"
#include "RG-I-Kol-2012View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRGIKol2012View

IMPLEMENT_DYNCREATE(CRGIKol2012View, CView)

BEGIN_MESSAGE_MAP(CRGIKol2012View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CRGIKol2012View construction/destruction

CRGIKol2012View::CRGIKol2012View()
{
	ang = 0;

}

CRGIKol2012View::~CRGIKol2012View()
{
}

BOOL CRGIKol2012View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRGIKol2012View drawing

void CRGIKol2012View::OnDraw(CDC* pDC)
{
	CRGIKol2012Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clRect;
	GetClientRect(&clRect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap glavna;
	glavna.CreateCompatibleBitmap(pDC, clRect.Width(), clRect.Height());
	int prevMode = memDC->SetGraphicsMode(GM_ADVANCED);
	memDC->SelectObject(&glavna);

	CBrush belaB(RGB(255, 255, 255));
	CPen belaP(PS_SOLID, 1, RGB(255, 255, 255));
	CPen* oldP = memDC->SelectObject(&belaP);
	CBrush* oldB = memDC->SelectObject(&belaB);

	memDC->Rectangle(0, 0, clRect.right, clRect.bottom);
	memDC->SelectObject(oldP);
	memDC->SelectObject(oldB);
	//iscrtavnaje
	DrawScene(memDC);

	memDC->SetGraphicsMode(prevMode);
	belaP.DeleteObject();
	belaB.DeleteObject();
	pDC->BitBlt(0, 0, clRect.Width(), clRect.Height(), memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;

}


// CRGIKol2012View printing

BOOL CRGIKol2012View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRGIKol2012View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRGIKol2012View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CRGIKol2012View::Trapez(CDC * pDC, int a, int b, int h)
{
	CPoint tacke[] = { { -a / 2,-h / 2 },{ a / 2,-h / 2 },{ b / 2,h / 2 },{ -b / 2,h / 2 } };
	pDC->Polygon(tacke, 4);
}

void CRGIKol2012View::Translate(CDC * pDC, float x, float y)
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

void CRGIKol2012View::Rotate(CDC * pDC, float a)
{
	XFORM rot;
	rot.eM11 = cos(a*toRad);
	rot.eM12 = sin(a*toRad);
	rot.eM21 = -sin(a*toRad);
	rot.eM22 = cos(a*toRad);
	rot.eDx = 0;
	rot.eDy = 0;

	pDC->ModifyWorldTransform(&rot, MWT_LEFTMULTIPLY);
}

void CRGIKol2012View::DrawGear(CDC * pDC, int spokeCount, int spokeWidth)
{
	/*CPen isprekidana(PS_DASH, 1, RGB(0, 0, 0));
	CPen* oldP = pDC->SelectObject(&isprekidana);
	CBrush belaB(RGB(255, 255, 255));
	CBrush* oldB = pDC->SelectObject(&belaB);*/

	CPen tamnoPlava(PS_SOLID, 2, RGB(70, 130, 180));
	CBrush svetloPlava(RGB(173, 216, 230));


	double ePoluprecnik = spokeCount*spokeWidth / 2.95;
	double cPoluprecnik = ePoluprecnik - spokeWidth / 2;

	////vec je koordinatni poc u centru zupcanika
	//pDC->Ellipse(-ePoluprecnik, -ePoluprecnik, ePoluprecnik, ePoluprecnik);

	CPen* oldP = pDC->SelectObject(&tamnoPlava);
	CBrush* oldB=pDC->SelectObject(&svetloPlava);
	pDC->Ellipse(-cPoluprecnik, -cPoluprecnik, cPoluprecnik, cPoluprecnik);

	pDC->Rectangle(-spokeWidth / 2, -spokeWidth / 2, spokeWidth / 2, spokeWidth / 2);

	CFont novi;
	novi.CreateFont(18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));

	CFont* oldFont = pDC->SelectObject(&novi);
	pDC->SetTextColor(RGB(70, 130, 180));
	pDC->SetBkMode(TRANSPARENT);

	CString* s;
	if (spokeCount == 10)
	{
		s = new CString("10 zubaca");
	}
	else
	{
		s = new CString("20 zubaca");
	}

	CSize size;
	GetTextExtentPoint32(pDC->m_hDC, *s, 9, &size);

	pDC->TextOut(-size.cx / 2, spokeWidth / 2, *s);

	float a = 0;


	for (int i = 0; i < spokeCount; i++)
	{
		XFORM oldF;
		GetWorldTransform(pDC->m_hDC, &oldF);

		Rotate(pDC, a);
		Translate(pDC, 0, -ePoluprecnik);
		Trapez(pDC, spokeWidth / 1.4, spokeWidth*1.4, spokeWidth);

		a += 360 / spokeCount;

		SetWorldTransform(pDC->m_hDC, &oldF);
	}

	pDC->SelectObject(&oldB);
	pDC->SelectObject(&oldP);
	pDC->SelectObject(oldFont);
	novi.DeleteObject();
	/*isprekidana.DeleteObject();
	belaB.DeleteObject();*/
	tamnoPlava.DeleteObject();
	svetloPlava.DeleteObject();

}

void CRGIKol2012View::DrawScene(CDC * pDC)
{

	CPen isprekidana(PS_DASH, 1, RGB(0, 0, 0));
	CPen* oldP = pDC->SelectObject(&isprekidana);
	CBrush belaB(RGB(255, 255, 255));
	CBrush* oldB = pDC->SelectObject(&belaB);

	float ePoluprecnikGlavni = 20 * 20 / 2.9;
	float ePoluprecnikSporedni = 10 * 20 / 2.9;

	//desna isprekidana
	pDC->SetViewportOrg(300 + ePoluprecnikGlavni + ePoluprecnikSporedni, 300);
	pDC->Ellipse(-ePoluprecnikSporedni, -ePoluprecnikSporedni, ePoluprecnikSporedni, ePoluprecnikSporedni);
	
	pDC->SetViewportOrg(0, 0);
	//glavna isprekidana
	pDC->SetViewportOrg(300, 300);
	pDC->Ellipse(-ePoluprecnikGlavni, -ePoluprecnikGlavni, ePoluprecnikGlavni, ePoluprecnikGlavni);
	pDC->SetViewportOrg(0, 0);

	//gore levo isprekidana
	pDC->SetViewportOrg(300 - ePoluprecnikGlavni - 7, 300 - ePoluprecnikGlavni - 9);
	pDC->Ellipse(-ePoluprecnikSporedni, -ePoluprecnikSporedni, ePoluprecnikSporedni, ePoluprecnikSporedni);
	pDC->SetViewportOrg(0, 0);

	pDC->SelectObject(&oldP);
	pDC->SelectObject(&oldB);


	///////////////// I nacin ///////////////////////

	//XFORM oldForm;

	////desno
	//GetWorldTransform(pDC->m_hDC, &oldForm);

	//pDC->SetViewportOrg(300 + ePoluprecnikGlavni + ePoluprecnikSporedni, 300);

	//Rotate(pDC, -2*ang);
	//DrawGear(pDC, 10, 20);

	//SetWorldTransform(pDC->m_hDC, &oldForm);
	//pDC->SetViewportOrg(0, 0);

	////glavni
	//GetWorldTransform(pDC->m_hDC, &oldForm);

	//pDC->SetViewportOrg(300, 300);

	//Rotate(pDC, ang);
	//DrawGear(pDC, 20, 20);

	//SetWorldTransform(pDC->m_hDC, &oldForm);
	//pDC->SetViewportOrg(0, 0);

	////gore levo
	//GetWorldTransform(pDC->m_hDC, &oldForm);

	//pDC->SetViewportOrg(300 - ePoluprecnikGlavni-7, 300 - ePoluprecnikGlavni-9);

	//Rotate(pDC, -2*ang - 8);
	//DrawGear(pDC, 10, 20);

	//SetWorldTransform(pDC->m_hDC, &oldForm);
	//pDC->SetViewportOrg(0, 0);


	//////////////////////// II nacin ////////////////////

	float goreLevoPomerajX = -ePoluprecnikGlavni - 7;
	float goreLevoPomerajY = -ePoluprecnikGlavni - 9;
	float desniPomerajX = ePoluprecnikGlavni + ePoluprecnikSporedni;

	XFORM oldForm;
	for (int i = 0; i < 3; i++)
	{
	
		GetWorldTransform(pDC->m_hDC, &oldForm);
		pDC->SetViewportOrg(300, 300);

		if (i == 0)
		{
			Rotate(pDC, ang);
			DrawGear(pDC, 20, 20);
		}
		if (i == 1)
		{
			Translate(pDC, goreLevoPomerajX, goreLevoPomerajY);
			Rotate(pDC, -2 * ang - 8);
			DrawGear(pDC, 10, 20);
		}
		if (i == 2)
		{
			Translate(pDC, desniPomerajX, 0);
			Rotate(pDC, -2 * ang);
			DrawGear(pDC, 10, 20);
		}

		SetWorldTransform(pDC->m_hDC, &oldForm);
		pDC->SetViewportOrg(0, 0);
	}


	isprekidana.DeleteObject();
	belaB.DeleteObject();

}


// CRGIKol2012View diagnostics

#ifdef _DEBUG
void CRGIKol2012View::AssertValid() const
{
	CView::AssertValid();
}

void CRGIKol2012View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRGIKol2012Doc* CRGIKol2012View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRGIKol2012Doc)));
	return (CRGIKol2012Doc*)m_pDocument;
}
#endif //_DEBUG


// CRGIKol2012View message handlers


BOOL CRGIKol2012View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CRGIKol2012View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != VK_UP)
	{
		return;
	}

	ang += 1;
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
