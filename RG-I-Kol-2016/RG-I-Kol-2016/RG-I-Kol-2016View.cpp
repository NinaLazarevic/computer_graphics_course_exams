
// RG-I-Kol-2016View.cpp : implementation of the CRGIKol2016View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RG-I-Kol-2016.h"
#endif

#include "RG-I-Kol-2016Doc.h"
#include "RG-I-Kol-2016View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRGIKol2016View

IMPLEMENT_DYNCREATE(CRGIKol2016View, CView)

BEGIN_MESSAGE_MAP(CRGIKol2016View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CRGIKol2016View construction/destruction

CRGIKol2016View::CRGIKol2016View()
{
	okvir.Load(CString("wood.jpg"));
	povrsinaStola.Load(CString("felt2.jpg"));

	kuglaDodirnuta = false;
	prviPutDodirnuta = true;
	angle = 0;
	angleKugla = 0;

	angleRotiranjaKugle = 0;

	pomerajKugla = 0;
	pomerajStap = 0;
	poluprecnikKugle = 0;

}

CRGIKol2016View::~CRGIKol2016View()
{
}

BOOL CRGIKol2016View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRGIKol2016View drawing

void CRGIKol2016View::OnDraw(CDC* pDC)
{
	CRGIKol2016Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	CRect clRect;
	GetClientRect(clRect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap glavna;
	glavna.CreateCompatibleBitmap(pDC, clRect.Width(), clRect.Height());

	int prevMode = SetGraphicsMode(memDC->m_hDC, GM_ADVANCED);
	memDC->SelectObject(&glavna);


	//iscrtavanje
	DrawBorder(memDC, clRect, 40);

	XFORM oldForm;

	GetWorldTransform(memDC->m_hDC, &oldForm);

	//kugla
	memDC->SetViewportOrg(600, 400);

	if (kuglaDodirnuta)
	{
		Rotate(memDC, angleKugla, false);
		Translate(memDC, pomerajKugla, 0, false);
		Rotate(memDC, angleRotiranjaKugle, false);
	}
	else
	{
		Rotate(memDC, angleRotiranjaKugle, false);
	}

	DrawBall(memDC, 30);

	memDC->SetViewportOrg(0, 0);
	SetWorldTransform(memDC->m_hDC, &oldForm);
	


	//stap

	GetWorldTransform(memDC->m_hDC,&oldForm);
	memDC->SetViewportOrg(600, 400);

	Translate(memDC, pomerajStap, 0, true);
	Rotate(memDC, angle, true);
	

	DrawStick(memDC, 590);

	memDC->SetViewportOrg(0, 0);
	SetWorldTransform(memDC->m_hDC, &oldForm);

	

	SetGraphicsMode(memDC->m_hDC, prevMode);
	pDC->BitBlt(0, 0, clRect.Width(), clRect.Height(), memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;

}


// CRGIKol2016View printing

BOOL CRGIKol2016View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRGIKol2016View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRGIKol2016View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CRGIKol2016View::DrawStick(CDC * pDC, int w)
{

	CPen braonP(PS_SOLID, 1, RGB(139, 69, 19));
	CPen* oldP = pDC->SelectObject(&braonP);
	CBrush okerB(RGB(222, 184, 135));
	CBrush* oldB = pDC->SelectObject(&okerB);

	CBrush braonB(RGB(77, 26, 0));

	CPen belaP(PS_SOLID, 1, RGB(255, 255, 255));

	//prva trecina
	/*CPoint prvaTrecina[] = { {-70,-w / 200},{-70,w / 200},{-2 * w / 3,2 * w / 300} ,{ -2 * w / 3,-2 * w / 300 } };

	pDC->Polygon(prvaTrecina, 4);*/

	pDC->BeginPath();

	pDC->MoveTo(70, -w / 200);
	pDC->LineTo(70, w / 200);
	pDC->LineTo(2 * w / 3, 2 * w / 300);
	pDC->LineTo(2 * w / 3, -2 * w / 300);
	pDC->LineTo(70, -w / 200);

	pDC->EndPath();

	pDC->StrokeAndFillPath();

	//druga trecina
	pDC->SelectObject(&braonB);

	//CPoint drugaTrecina[] = { { -2 * w / 3,2 * w / 300 },{ -2 * w / 3,-2 * w / 300 },{-w,-w / 100},{-w,w / 100} };
	//
	//pDC->Polygon(drugaTrecina, 4);

	pDC->SetArcDirection(AD_CLOCKWISE);

	pDC->BeginPath();

	pDC->MoveTo(2 * w / 3, -2 * w / 300);
	pDC->LineTo(w, -w / 100);
	pDC->ArcTo(CRect(w - w / 200, -w / 100, w + w / 200, w / 100), { w, -w / 100 }, { w,w / 100 });
	pDC->LineTo(2 * w / 3, 2 * w / 300);
	pDC->LineTo(2 * w / 3, -2 * w / 300);

	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(&belaP);

	pDC->MoveTo(70, w / 200 - 2);
	pDC->LineTo(w, w / 100 - 2);

	pDC->SelectObject(oldB);
	pDC->SelectObject(oldP);
	okerB.DeleteObject();
	braonB.DeleteObject();
	braonP.DeleteObject();
	belaP.DeleteObject();

}

void CRGIKol2016View::DrawBall(CDC * pDC, int w)
{
	CBrush belaB(RGB(255, 255, 255));

	CBrush tamnoCrvenaB(RGB(139, 0, 0));
	CBrush* oldB = pDC->SelectObject(&tamnoCrvenaB);

	CPen tamnoCrvenaP(PS_SOLID, 1, RGB(139, 0, 0));
	CPen* oldP = pDC->SelectObject(&tamnoCrvenaP);

	pDC->Ellipse(-w/2, -w/2, w/2, w/2);

	pDC->SelectObject(&belaB);
	int wm = w / 3;

	pDC->Ellipse(2, -wm, 2 + wm, 0);

	poluprecnikKugle = w / 2;

	pDC->SelectObject(oldB);
	pDC->SelectObject(oldP);
	tamnoCrvenaB.DeleteObject();
	tamnoCrvenaP.DeleteObject();
	belaB.DeleteObject();
}

void CRGIKol2016View::Translate(CDC * pDC, float dX, float dY, bool rightMultiply)
{

	XFORM trans;

	trans.eM11 = 1;
	trans.eM12 = 0;
	trans.eM21 = 0;
	trans.eM22 = 1;
	trans.eDx = dX;
	trans.eDy = dY;

	if (rightMultiply)
	{
		pDC->ModifyWorldTransform(&trans, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&trans, MWT_LEFTMULTIPLY);
	}

}

void CRGIKol2016View::Rotate(CDC * pDC, float angle, bool rightMultiply)
{
	XFORM rot;

	rot.eM11 = cos(angle*toRad);
	rot.eM12 = sin(angle*toRad);
	rot.eM21 = -sin(angle*toRad);
	rot.eM22 = cos(angle*toRad);
	rot.eDx = 0;
	rot.eDy = 0;


	if (rightMultiply)
	{
		pDC->ModifyWorldTransform(&rot, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&rot, MWT_LEFTMULTIPLY);
	}

}

void CRGIKol2016View::DrawTable(CDC * pDC, CRect rect)
{

	int brW = rect.Width() / povrsinaStola.Width() ;
	int brH = rect.Height() / povrsinaStola.Height() ;

	CRect povMali(0, 0, povrsinaStola.Width(), povrsinaStola.Height());
	int pW = 0;
	int pH = 0;
	for (int i = 0; i < brW; i++)
	{
		for (int j = 0; j < brH; j++)
		{
			
			CRect mali(rect.left+ pW, rect.top+pH, rect.left + pW + povrsinaStola.Width(), rect.top + pH + povrsinaStola.Height());
			povrsinaStola.Draw(pDC, povMali, mali);

			pH += povrsinaStola.Height();
		}

		pW += povrsinaStola.Width();
		pH = 0;
	}
	
	//jos jedan red za svaki slucaj

	pW = 0;

	for (int i = 0; i < brW; i++)
	{
		CRect mali(rect.left + pW, rect.bottom - povrsinaStola.Height(), rect.left + pW + povrsinaStola.Width(), rect.bottom);
		povrsinaStola.Draw(pDC, povMali, mali);

		pW += povrsinaStola.Width();
	}

	pH = 0;
	for (int i = 0; i < brH; i++)
	{
		CRect mali(rect.right - povrsinaStola.Width(), rect.top + pH, rect.right, rect.top + pH + povrsinaStola.Height());
		povrsinaStola.Draw(pDC, povMali, mali);

		pH += povrsinaStola.Height();
	}

	//donji desni ugao

	CRect mali(rect.right - povrsinaStola.Width(), rect.bottom - povrsinaStola.Height(), rect.right, rect.bottom);
	povrsinaStola.Draw(pDC, povMali, mali);
}

void CRGIKol2016View::DrawBorder(CDC * pDC, CRect rect, int w)
{
	okvir.Draw(pDC, rect, rect);

	CRect tableRect(rect.left + w, rect.top + w, rect.right - w, rect.bottom - w);
	DrawTable(pDC, tableRect);

	DrawHoles(pDC, rect, 40);


}

void CRGIKol2016View::DrawHoles(CDC * pDC, CRect rect, int size)
{
	CBrush crnaB(RGB(0, 0, 0));
	CBrush* oldB = pDC->SelectObject(&crnaB);

	CPen crnaP(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldP = pDC->SelectObject(&crnaP);

	int w = 20;
	int h = 20;

	for (int i = 0; i < 3; i++)
	{
		pDC->SetViewportOrg(rect.left + w, rect.top + h);

		pDC->Ellipse(0, 0, size, size);

		pDC->SetViewportOrg(0, 0);

		pDC->SetViewportOrg(rect.left + w, rect.bottom - h - size);

		pDC->Ellipse(0, 0, size, size);

		pDC->SetViewportOrg(0, 0);

		w += rect.Width() / 2 - 40;
	}

	pDC->SelectObject(oldB);
	pDC->SelectObject(oldP);

	crnaB.DeleteObject();
	crnaP.DeleteObject();

}


// CRGIKol2016View diagnostics

#ifdef _DEBUG
void CRGIKol2016View::AssertValid() const
{
	CView::AssertValid();
}

void CRGIKol2016View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRGIKol2016Doc* CRGIKol2016View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRGIKol2016Doc)));
	return (CRGIKol2016Doc*)m_pDocument;
}
#endif //_DEBUG


// CRGIKol2016View message handlers


BOOL CRGIKol2016View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CRGIKol2016View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != VK_UP && nChar != VK_DOWN && nChar != VK_LEFT && nChar != VK_RIGHT)
		return;

	if (nChar == VK_LEFT)
	{
		angle += 10;
		if (!kuglaDodirnuta)
			angleKugla = angle;
	}
	if (nChar == VK_RIGHT)
	{
		angle -= 10;
		if (!kuglaDodirnuta)
			angleKugla = angle;
	}
	//prvobitna udaljenost od centra loptice je 70
	if (nChar == VK_UP)
	{
		if (pomerajStap == -70 + poluprecnikKugle )
		{
			if (prviPutDodirnuta)
			{
				kuglaDodirnuta = true;
				pomerajKugla -= 10;

				angleRotiranjaKugle += 25;
				if (angleRotiranjaKugle >= 360)
					angleRotiranjaKugle = 0;
			}
			
		}
		else
		{
			pomerajStap -= 5;
		}
	}

	if (nChar == VK_DOWN)
	{
		if (kuglaDodirnuta)
		{
			pomerajKugla += 10;

			angleRotiranjaKugle -= 25;
			if (angleRotiranjaKugle <= 0)
				angleRotiranjaKugle = 360;

			prviPutDodirnuta = false;
			if (pomerajKugla == 0)
			{
				kuglaDodirnuta = false;
				prviPutDodirnuta = true;
				angleKugla = angle;

				angleRotiranjaKugle += angleKugla;
			}
		}

		pomerajStap += 5;
		

	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
