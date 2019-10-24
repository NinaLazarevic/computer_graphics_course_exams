
// RG-I-Kol-2015View.cpp : implementation of the CRGIKol2015View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RG-I-Kol-2015.h"
#endif

#include "RG-I-Kol-2015Doc.h"
#include "RG-I-Kol-2015View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRGIKol2015View

IMPLEMENT_DYNCREATE(CRGIKol2015View, CView)

BEGIN_MESSAGE_MAP(CRGIKol2015View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CRGIKol2015View construction/destruction

CRGIKol2015View::CRGIKol2015View()
{

	bitmapa.Load(CString("blue.png"));

	end = gore = dole = levo  = false;
	pomerajX = pomerajY = 0;
	packman_angle = 0;
	otvorenaUsta = true;

	centarPackmana.x = 400;
	centarPackmana.y = 400;

	centarDuha.x = 148;
	centarDuha.y = 168;

}

CRGIKol2015View::~CRGIKol2015View()
{
}

BOOL CRGIKol2015View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRGIKol2015View drawing

void CRGIKol2015View::OnDraw(CDC* pDC)
{
	CRGIKol2015Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(rect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	int prevMode = SetGraphicsMode(memDC->m_hDC, GM_ADVANCED);

	CBitmap bitm;
	bitm.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(&bitm);
	//iscrtavanje pozadine
	CRect blueRect(0, 0, bitmapa.Width(), bitmapa.Height());
	CRect pozadina(0, 0, rect.right, rect.bottom);
	bitmapa.Draw(memDC, blueRect, pozadina);
	///////////////////

	XFORM oldForm;
	bool b = memDC->GetWorldTransform(&oldForm);
	memDC->SetViewportOrg(centarPackmana.x, centarPackmana.y);
	if (dole)
	{
		packman_angle = 90;
	}
	else {
		if (gore)
		{
			packman_angle = -90;
		}
		else
		{
			packman_angle = 0;
		}
	}

	Translate(memDC, pomerajX, pomerajY);
	
	if (levo)
	{
		Reflect(memDC, true);
	}
	else
	{
		Reflect(memDC, false);
	}

	Rotate(memDC, packman_angle);

	CRect packman_rect(-50, -50, 50, 50);
	if(otvorenaUsta)
		DrawPacman(memDC, packman_rect, 15);
	else
		DrawPacman(memDC, packman_rect, 0);

	memDC->SetViewportOrg(0, 0);
	SetWorldTransform(memDC->m_hDC,&oldForm);

	CRect ghost_rect(100, 120, 196, 216);
	DrawGhost(memDC, ghost_rect);

	if (end)
	{
		DrawEnd(memDC, rect);
	}

	SetGraphicsMode(memDC->m_hDC, prevMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;

}


// CRGIKol2015View printing

BOOL CRGIKol2015View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRGIKol2015View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRGIKol2015View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CRGIKol2015View::DrawPacman(CDC * pDC, CRect rect, float angle)
{

	/*XFORM oldF;
	bool bb = GetWorldTransform(pDC->m_hDC, &oldF);

	Translate(pDC, 400, 400);*/

	CBrush zutaB(RGB(255, 255, 0));
	CPen zutaP(PS_SOLID, 1, RGB(255, 255, 0));

	CPen* oldP = pDC->SelectObject(&zutaP);
	CBrush* oldB = pDC->SelectObject(&zutaB);

	//pDC->Ellipse(rect);

	float b = rect.right / 2; //poluprecnik packman-a
	float a = b* tan(angle*toRad);

	CPoint start;
	start.x = b; start.y = -a;

	CPoint end;
	end.x = b; end.y = a;

	pDC->Pie(rect, start, end);

	CBrush oko(RGB(0, 0, 0));
	pDC->SelectObject(&oko);

	pDC->Ellipse(b - 3, -a - 20, b + 13, -a - 6);

	//SetWorldTransform(pDC->m_hDC, &oldF);
	pDC->SelectObject(&oldP);
	pDC->SelectObject(*oldB);

	zutaB.DeleteObject();
	zutaP.DeleteObject();
	oko.DeleteObject();

}

void CRGIKol2015View::DrawGhost(CDC * pDC, CRect rect)
{
	CBrush crvenaB(RGB(255, 0, 0));
	CPen crvenaP(PS_SOLID, 1, RGB(255, 0, 0));

	CPen* oldP = pDC->SelectObject(&crvenaP);
	CBrush* oldB = pDC->SelectObject(&crvenaB);

	int brDonjihLukova = 5;

	//pDC->BeginPath();
	pDC->MoveTo(rect.right, rect.bottom);
	pDC->LineTo(rect.right, rect.bottom - rect.bottom / 5);

	CPoint start;
	start.x = rect.right; start.y = rect.bottom - rect.bottom / 5;

	CPoint end;
	end.x = rect.left; end.y = rect.bottom - rect.bottom / 5;

	pDC->Arc(rect, start, end);

	pDC->MoveTo(end);
	pDC->LineTo(rect.left, rect.bottom);

	float deoZaLuk = (rect.right - rect.left - 8) / brDonjihLukova;
	pDC->LineTo(rect.left + 5, rect.bottom - deoZaLuk / 2 - 1);

	for (int i = 0; i < brDonjihLukova; i++)
	{
		CRect luk((rect.left + 4 + i*deoZaLuk), rect.bottom - deoZaLuk, (rect.left + 4 + (i + 1)*deoZaLuk), rect.bottom);

		if (i % 2 == 0)
		{
			SetArcDirection(pDC->m_hDC, AD_CLOCKWISE);
		}
		else
		{
			SetArcDirection(pDC->m_hDC, AD_COUNTERCLOCKWISE);
		}

		start.x = rect.left + 4 + i*deoZaLuk;
		start.y = rect.bottom - deoZaLuk / 2;

		end.x = rect.left + 4 + (i + 1)*deoZaLuk;
		end.y = rect.bottom - deoZaLuk / 2;

		pDC->Arc(luk, start, end);


	}

	pDC->MoveTo(rect.right - 6, rect.bottom - deoZaLuk / 2);
	pDC->LineTo(rect.right + 1, rect.bottom + 1);

	//pDC->EndPath();
	//pDC->StrokePath();
	//pDC->FillPath();

	//pDC->FloodFill(148,168,RGB(255,0,0));

	pDC->FloodFill(rect.right - (rect.Width() / 2), rect.bottom - (rect.Height() / 2), RGB(255, 0, 0));

	CBrush beloB(RGB(255, 255, 255));
	CPen beloP(PS_SOLID, 1, RGB(255, 255, 255));

	pDC->SelectObject(&beloB);
	pDC->SelectObject(&beloP);

	pDC->Ellipse(rect.right - (rect.Width() / 2) - 10, rect.bottom - (rect.Height() / 2) - 10, rect.right - (rect.Width() / 2) + 10, rect.bottom - (rect.Height() / 2) + 10);
	pDC->Ellipse(rect.right - (rect.Width() / 2) + 30 - 10, rect.bottom - (rect.Height() / 2) - 10, rect.right - (rect.Width() / 2) + 30 + 10, rect.bottom - (rect.Height() / 2) + 10);

	CBrush plavaB(RGB(0, 0, 255));
	CPen plavaP(PS_SOLID, 1, RGB(0, 0, 255));

	pDC->SelectObject(&plavaB);
	pDC->SelectObject(&plavaP);

	pDC->Ellipse(rect.right - (rect.Width() / 2) - 4, rect.bottom - (rect.Height() / 2) - 4, rect.right - (rect.Width() / 2) + 4, rect.bottom - (rect.Height() / 2) + 4);
	pDC->Ellipse(rect.right - (rect.Width() / 2) + 30 - 4, rect.bottom - (rect.Height() / 2) - 4, rect.right - (rect.Width() / 2) + 30 + 4, rect.bottom - (rect.Height() / 2) + 4);


	pDC->SelectObject(&oldP);
	pDC->SelectObject(*oldB);

	crvenaB.DeleteObject();
	crvenaP.DeleteObject();
	beloP.DeleteObject();
	beloB.DeleteObject();
	plavaP.DeleteObject();
	plavaB.DeleteObject();
}


void CRGIKol2015View::Translate(CDC * pDC, float x, float y)
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

void CRGIKol2015View::Rotate(CDC * pDC, float angle)
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

void CRGIKol2015View::Reflect(CDC * pDC, bool levo)
{
	XFORM refl;

	if (levo)
		refl.eM11 = -1;
	else
		refl.eM11 = 1;
	refl.eM12 = 0;
	refl.eM21 = 0;
	refl.eM22 = 1;
	refl.eDx = 0;
	refl.eDy = 0;

	pDC->ModifyWorldTransform(&refl, MWT_LEFTMULTIPLY);
}

void CRGIKol2015View::DrawEnd(CDC * pDC, CRect rect)
{
	int nHeight = 72; // OVO MORA DA SE NAVEDE
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
	CString sFaceName = CString("Arial"); // OVO MORA DA SE NAVEDE
	CFont font;
	font.CreateFont(nHeight, nWidth, nEsc, nOrient, nWeight, bItalic, bUnderline, cStrikeOut,
		nCharSet, nOutPrecision, nClipPrecision, nQuality, nPitchAndFamily, sFaceName);

	CFont* oldFont = pDC->SelectObject(&font);

	SetTextColor(pDC->m_hDC, RGB(255, 255, 255));
	pDC->SetBkMode(TRANSPARENT);
	CSize ret;
	GetTextExtentPoint32(pDC->m_hDC, CString("The End"), 7, &ret);

	pDC->TextOutW((rect.Width() - ret.cx) / 2, (rect.Height() - ret.cy) / 2, CString("The End"));

	pDC->SelectObject(&oldFont);
	font.DeleteObject();

}


// CRGIKol2015View diagnostics

#ifdef _DEBUG
void CRGIKol2015View::AssertValid() const
{
	CView::AssertValid();
}

void CRGIKol2015View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRGIKol2015Doc* CRGIKol2015View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRGIKol2015Doc)));
	return (CRGIKol2015Doc*)m_pDocument;
}
#endif //_DEBUG


// CRGIKol2015View message handlers


BOOL CRGIKol2015View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;

	/*return CView::OnEraseBkgnd(pDC);*/
}


void CRGIKol2015View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (end)
		return;

	if (nChar != VK_UP && nChar != VK_DOWN && nChar != VK_LEFT && nChar != VK_RIGHT)
		return;

	if (nChar == VK_UP)
	{
		gore = true;
		dole = false;
		levo = false;

		otvorenaUsta = !otvorenaUsta;
		centarPackmana.y -= 10;
		pomerajY =10;
		pomerajX = 0;

	}
	if (nChar == VK_DOWN)
	{
		gore = false;
		dole = true;
		levo = false;

		otvorenaUsta = !otvorenaUsta;
		centarPackmana.y += 10;
		pomerajY =10;
		pomerajX = 0;


	}
	if (nChar == VK_LEFT)
	{
		gore = false;
		dole = false;
		levo = true;

		otvorenaUsta = !otvorenaUsta;
		centarPackmana.x -= 10;
		pomerajX = 10;
		pomerajY = 0;
	}
	if (nChar == VK_RIGHT)
	{
		gore = false;
		dole = false;
		levo = false;

		otvorenaUsta = !otvorenaUsta;
		centarPackmana.x += 10;
		pomerajX = 10;
		pomerajY = 0;
	}

	//rastojanje 2 tacke u ravni
	float d = sqrt(pow((centarPackmana.x - centarDuha.x), 2) + pow((centarPackmana.y - centarDuha.y), 2));
	//poluprecnik packmana je 50, duha je 48;
	if (d <= 98)
		end = true;
	else
		end = false;

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
