
// ZadaciSaIspitaGDIView.cpp : implementation of the CZadaciSaIspitaGDIView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ZadaciSaIspitaGDI.h"
#endif

#include "ZadaciSaIspitaGDIDoc.h"
#include "ZadaciSaIspitaGDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CZadaciSaIspitaGDIView

IMPLEMENT_DYNCREATE(CZadaciSaIspitaGDIView, CView)

BEGIN_MESSAGE_MAP(CZadaciSaIspitaGDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CZadaciSaIspitaGDIView construction/destruction

CZadaciSaIspitaGDIView::CZadaciSaIspitaGDIView()
{
	// TODO: add construction code here

}

CZadaciSaIspitaGDIView::~CZadaciSaIspitaGDIView()
{
}

BOOL CZadaciSaIspitaGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CZadaciSaIspitaGDIView drawing

void CZadaciSaIspitaGDIView::OnDraw(CDC* pDC)
{
	CZadaciSaIspitaGDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CPen newPen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* oldP = pDC->SelectObject(&newPen);

	CBrush crvenaB(RGB(255, 0, 0));
	CBrush* oldB = pDC->SelectObject(&crvenaB);

	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);

	CPoint p;
	p.x = 500;
	p.y = 250;

	//DrawBackground(pDC, p, 100, CString("grey.jpg"));
	//DrawCoin(pDC, p, 100, CString("Narodna banka Republike Srbije"), 20, CString("50"), 40, RGB(0, 0, 0));

	//SaveBMP(CString("Nova.jpg"), pDC, p, 100);
	COLORREF col[3] = { RGB(138,43,226),RGB(255,99,71),RGB(143,188,143) };
	//pDC->SetViewportOrg(p);
	//DrawComplexFigure(pDC, 100, col, RGB(255, 69, 0), 0.2, CString("10"));
	//DrawFigure(pDC, 80, RGB(173, 255, 47), RGB(255, 69, 0));

	DrawPicture(pDC, 40, col, RGB(255, 69, 0), 0.2, 3, 3);

	SetGraphicsMode(pDC->m_hDC, prevMode);
	pDC->SelectObject(&oldP);
	pDC->SelectObject(*oldB);

	crvenaB.DeleteObject();
	newPen.DeleteObject();


}


// CZadaciSaIspitaGDIView printing

BOOL CZadaciSaIspitaGDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CZadaciSaIspitaGDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CZadaciSaIspitaGDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CZadaciSaIspitaGDIView::Translate(CDC * pDC, float x, float y)
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

void CZadaciSaIspitaGDIView::Rotate(CDC * pDC, float angle)
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

////03.06.2015.
void CZadaciSaIspitaGDIView::DrawBackground(CDC * pDC, CPoint ptCenter, int radius, CString strPicture)
{
	//učitava sliku pod nazivom strPicture i iscrtava je tako da bude
	//vidljiva samo unutar kruga poluprečnika radius sa centrom u tački ptCenter

	DImage bitmapa;
	bitmapa.Load(strPicture);

	CRect coin(ptCenter.x - radius, ptCenter.y - radius, ptCenter.x + radius, ptCenter.y + radius);
	CRect greyRect(0, 0, bitmapa.Width(), bitmapa.Height());
	

	CRgn eclipse;
	eclipse.CreateEllipticRgn(ptCenter.x - radius, ptCenter.y - radius, ptCenter.x + radius, ptCenter.y + radius);
	CRgn coinRgn;
	coinRgn.CreateRectRgn(ptCenter.x - radius, ptCenter.y - radius, ptCenter.x + radius, ptCenter.y + radius);

	CRgn finalRgn;
	finalRgn.CreateRectRgn(0, 0, 0, 0);
	finalRgn.CombineRgn(&coinRgn, &eclipse, RGN_AND);

	pDC->SelectObject(finalRgn);
	bitmapa.Draw(pDC, greyRect, coin);

	pDC->SelectClipRgn(NULL);

}

void CZadaciSaIspitaGDIView::DrawCoin(CDC * pDC, CPoint ptCenter, int radius, CString strText, int fsizeText, CString strCoin, int fsizeCoin, COLORREF clrText)
{
	//iscrtava novčić kružnog oblika poluprečnika radius, bez ispune sa crnom linijom debljine 3.
		//Duž oboda unutar novčića je ispisan tekst strText fontom
		//veličine fsizeText.U centru novčića je ispisana vrednost
	//	novčića strCoin podebljanim fontom veličine fsizeCoin.
	//	Tekst na novčiću treba da bude boje clrText i ispisan fontom Arial.Smatrati da je font fiksne širine.

	CPen newPen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen* oldP = pDC->SelectObject(&newPen);

	DrawBackground(pDC, ptCenter, radius, CString("grey.jpg"));

	pDC->SetViewportOrg(ptCenter.x, ptCenter.y);
	CFont fontTekst;
	fontTekst.CreateFontW(fsizeText, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));

	CFont fontVrednost;
	fontVrednost.CreateFontW(fsizeCoin, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));

	CFont* oldFont = pDC->SelectObject(&fontTekst);

	SetTextColor(pDC->m_hDC, clrText);
	pDC->SetBkMode(TRANSPARENT);

	//
	
	float ugaoSlova = 10;

	int length = strText.GetLength();

	for (int i = 0; i < length; i++)
	{
		XFORM oldForm;
		bool b = pDC->GetWorldTransform(&oldForm);

		/*CFont fontTekst2;
		fontTekst2.CreateFontW(fsizeText, 0, ugaoSlova, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));

		oldFont = pDC->SelectObject(&fontTekst2);*/

		CSize text;
		GetTextExtentPoint32(pDC->m_hDC, CString(strText.GetAt(i)), 1, &text);

		Rotate(pDC, -180 + ugaoSlova);
		Translate(pDC, radius - text.cy / 2, 0);
		Rotate(pDC, -90 + ugaoSlova);

		pDC->TextOutW(-( text.cx) / 2, - (text.cy) / 2, CString(strText.GetAt(i)));

		pDC->SelectObject(&oldFont);
		pDC->SetWorldTransform(&oldForm);
		ugaoSlova += 10;

		//fontTekst2.DeleteObject();
	}


	pDC->SelectObject(&fontVrednost);
	CSize textR;
	GetTextExtentPoint32(pDC->m_hDC, CString("A"), 1, &textR);
	GetTextExtentPoint32(pDC->m_hDC, strCoin, strCoin.GetLength(), &textR);
	pDC->TextOutW(-(textR.cx) / 2, -(textR.cy) / 2, strCoin);

	pDC->SelectObject(&oldP);
	pDC->SelectObject(&oldFont);

	pDC->SetViewportOrg(0,0);

	fontTekst.DeleteObject();
	fontVrednost.DeleteObject();
	newPen.DeleteObject();
}

void CZadaciSaIspitaGDIView::SaveBMP(CString name, CDC * pDC, CPoint ptCenter, int radius)
{
	//novčić iscrtan u pDC kopira u novi memorijski kontekst i snima u datoteku name.

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CRect rect;
	GetClientRect(rect);

	CBitmap bitm;
	bitm.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(&bitm);

	int prevMode = SetGraphicsMode(memDC->m_hDC, GM_ADVANCED);

	memDC->SetBkColor(RGB(255, 255, 255));
	DrawCoin(memDC, ptCenter, 100, CString("Narodna banka Republike Srbije"), 20, CString("50"), 40, RGB(0, 0, 0));

	DImage img(bitm);
	img.Save(name);

	SetGraphicsMode(memDC->m_hDC, prevMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	bitm.DeleteObject();
	memDC->DeleteDC();
}


////05.10.2011.

void CZadaciSaIspitaGDIView::DrawFigure(CDC * pDC, int size, COLORREF colFill, COLORREF colLine)
{
	//isrtava figuru sa slike 1 (okvirni
	//kvadrat je samo pomoćna slika za crtanje).Dužina stranica
	//pomoćnog kvadrata je size, dok colFill predstavlja ispunu figure i
		//colLine predstavlja boju linije.

	CPen newPen(PS_SOLID, 1, colLine);
	CPen* oldP=pDC->SelectObject(&newPen);

	CBrush newBrush(colFill);
	CBrush* oldB = pDC->SelectObject(&newBrush);

	//// prethodno je pomeren koordinatni pocetak

	pDC->BeginPath();
	CPoint p;
	p.x = -size/4;
	p.y = -size / 2;

	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->MoveTo(p);

	pDC->ArcTo(-size / 4, -(3 * size / 4), size / 4, -size / 4, -size / 4, -size / 2, size / 4, -size / 2);
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(size / 4, -(3 * size / 4), 3 * size / 4, -size / 4, size / 4, -size / 2, size / 2, -size / 4);
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(size / 4, -size / 4, 3 * size / 4, size / 4, size / 2, -size / 4, size / 2, size / 4);
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(size / 4, size / 4, 3 * size / 4, 3 * size / 4, size / 2, size / 4, size / 4, size / 2);
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(-size / 4, size / 4, size / 4, 3 * size / 4, size / 4, size / 2, -size / 4, size / 2);
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(-(3 * size / 4), size / 4, -size / 4, 3 * size / 4, -size / 4, size / 2, -size / 2, size / 4);
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(-(3 * size / 4), -size / 4, -size / 4, size / 4, -size / 2, size / 4, -size / 2, -size / 4);
	pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->ArcTo(-(3 * size / 4), -(3 * size / 4), -size / 4, -size / 4, -size / 2, -size / 4, -size / 4, -size / 2);

	pDC->EndPath();

	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldB);
	pDC->SelectObject(oldP);

	newBrush.DeleteObject();
	newPen.DeleteObject();

}

void CZadaciSaIspitaGDIView::DrawComplexFigure(CDC * pDC, int size, COLORREF colFill[], COLORREF colLine, double ratio, CString str)
{
	//isrtava složenu figuru sa slike 2 u kome je size
	//određuje veličinu figure u sredini.Vrednost ratio predstavlja odnos
	//	najveće i figure srednje veličine.Isti je i odnos figura srednje i
	//	najmanje veličine.Niz colFill predstavlja niz boja figura po veličini.
	//	U sredini figure ispisati tekst str bojom linije colLine, i fontom Arial
	//	veličine 12 i podebljanim.Sminiti ovako isrtanu figuru u metafajl (wmf)
	
	DrawFigure(pDC, size + ratio*size, colFill[0], colLine);
	DrawFigure(pDC, size, colFill[1], colLine);
	DrawFigure(pDC, size - ratio*size, colFill[2], colLine);

	CFont newFont;
	newFont.CreateFontW(12, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));

	CFont* oldF = pDC->SelectObject(&newFont);

	pDC->SetTextColor(colLine);
	pDC->SetBkMode(TRANSPARENT);
	CSize s;
	GetTextExtentPoint32(pDC->m_hDC, str, str.GetLength(), &s);
	pDC->TextOutW( -s.cx / 2, -s.cy / 2, str);


	pDC->SelectObject(oldF);
	newFont.DeleteObject();

	
}

void CZadaciSaIspitaGDIView::DrawPicture(CDC * pDC, int size, COLORREF colFill[], COLORREF colLine, double ratio, int row, int col)
{
	//formira šemu prikazanu na slici 3 pomoću figura iz prethodne stavke.
	//	Rastojanje između dve susedne figure je size / 2. Broj elemenata u
		//prvoj vrsti je col, a broj vrsti row.Oznaka u sredini svake figure
		//sastoji se od broja vrste i rednog broja u koloni

	CPoint p;
	p.x = 250;
	p.y = 250;

	pDC->SetViewportOrg(p);

	for (int i = 1;  i <= col; i++)
	{

		p.y = 250 + (i - 1) * size;
		p.x = 250;
		for (int j = 1; j <= row ; j++)
		{
			if (i == 2 && j == row)
				continue;
			if(i!=2)
			{ 
				p.x += (j - 1) * 2 * size;
			}
			else
			{
				p.x += size/2 + (j - 1) * 2 * size;
			}
			pDC->SetViewportOrg(0, 0);
			pDC->SetViewportOrg(p);

			int k = 0;
			int br = i * 10 + j;
			char t;
			itoa(br, &t, 10);

			DrawComplexFigure(pDC, size, colFill, colLine, 0.2, CString(t));
		}
	}
	pDC->SetViewportOrg(0,0);
}


// CZadaciSaIspitaGDIView diagnostics

#ifdef _DEBUG
void CZadaciSaIspitaGDIView::AssertValid() const
{
	CView::AssertValid();
}

void CZadaciSaIspitaGDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CZadaciSaIspitaGDIDoc* CZadaciSaIspitaGDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CZadaciSaIspitaGDIDoc)));
	return (CZadaciSaIspitaGDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CZadaciSaIspitaGDIView message handlers
