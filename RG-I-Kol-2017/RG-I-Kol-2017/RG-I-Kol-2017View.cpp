
// RG-I-Kol-2017View.cpp : implementation of the CRGIKol2017View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RG-I-Kol-2017.h"
#endif

#include "RG-I-Kol-2017Doc.h"
#include "RG-I-Kol-2017View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRGIKol2017View

IMPLEMENT_DYNCREATE(CRGIKol2017View, CView)

BEGIN_MESSAGE_MAP(CRGIKol2017View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CRGIKol2017View construction/destruction

CRGIKol2017View::CRGIKol2017View()
{
	// TODO: add construction code here

	Background = new DImage();
	Body = new DImage();
	Leg1 = new DImage();
	Leg2 = new DImage();
	Leg3 = new DImage();


	Background->Load(CString("Back2.jpg"));

	Body->Load(CString("Body.png"));

	Leg1->Load(CString("Leg1.png"));
	Leg2->Load(CString("Leg2.png"));
	Leg3->Load(CString("Leg3.png"));


	gore = levo  = -200;
	dole = desno = 200;
	
	sc = 1.0;

	desnoRobot = 0;
	ugaoPrednjeNoge = 20;
	ugaoZadnjeNoge = 0;
    
	smerP = -1; // prednje -- 
	smerZ = 1; //zadnje++

	//stanje = 0 => Prednje = 20 Zadnje = 0
	//stanje = 1 => Prednje = 10 Zadnje = 10
	//stanje = 2 => Prednje = 0 Zadnje = 20
	//stanje = 3 => Prednje = -10 Zadnje = 10
	//stanje = 4 => Prednje = -20 Zadnje = 0
	//stanje = 5 => Prednje = -10 Zadnje = -10
	//stanje = 6 => Prednje = 0 Zadnje = -20
	//stanje = 6 => Prednje = 10 Zadnje = -10
	//stanje = 7 => Prednje = 20 Zadnje = 0
	//stanje = 7 => Prednje = 10 Zadnje = 10
}

CRGIKol2017View::~CRGIKol2017View()
{
	delete Background;
	delete Body;
	delete Leg1;
	delete Leg2;
	delete Leg3;

}

BOOL CRGIKol2017View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRGIKol2017View drawing

void CRGIKol2017View::OnDraw(CDC* pDC)
{
	CRGIKol2017Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	CRect rect;
	GetClientRect(rect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap bitm;
	bitm.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(&bitm);

	int prevMode = SetGraphicsMode(memDC->m_hDC, GM_ADVANCED);
	//pomeranje pozadine
	CRect pozadinaDST(levo, gore, rect.right + desno, rect.bottom + dole);
	DrawScene(memDC, pozadinaDST);

	SetGraphicsMode(memDC->m_hDC, prevMode);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;

}


// CRGIKol2017View printing

BOOL CRGIKol2017View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRGIKol2017View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRGIKol2017View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CRGIKol2017View::LoadIdentity(CDC * pDC)
{
	XFORM ident;

	ident.eM11 = 1;
	ident.eM12 = 0;
	ident.eM21 = 0;
	ident.eM22 = 1;
	ident.eDx = 0;
	ident.eDy = 0;

	pDC->SetWorldTransform(&ident);
}

void CRGIKol2017View::Translate(CDC * pDC, float dX, float dY, bool rightMultiply)
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

void CRGIKol2017View::Rotate(CDC * pDC, float angle, bool rightMultiply)
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

void CRGIKol2017View::Scale(CDC * pDC, float sX, float sY, bool rightMultiply)
{
	XFORM scale;

	scale.eM11 = sX;
	scale.eM12 = 0;
	scale.eM21 = 0;
	scale.eM22 = sY;
	scale.eDx = 0;
	scale.eDx = 0;

	if (rightMultiply)
	{
		pDC->ModifyWorldTransform(&scale, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&scale, MWT_LEFTMULTIPLY);
	}
}

void CRGIKol2017View::DrawScene(CDC * pDC, CRect rect)
{
	//iscrtavanje pozadine
	CRect pozadinaSRC(0, 0, Background->Width(), Background->Height());
	Background->Draw(pDC, pozadinaSRC, rect);

	pDC->SetViewportOrg(100 + desnoRobot, 100);
	/*XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	Scale(pDC, sc, sc, false);*/

	//iscrtavanje tela roborta
	
	//DrawTransparentBitmap(pDC, *Body);
	CRect body(0, 0, Body->Width(), Body->Height());

	Body->Draw(pDC, body, body);

	//pDC->SetWorldTransform(&oldForm);

	pDC->SetViewportOrg(0, 0);

	//iscrtavanje nogu
	
	//zadnje noge , brojke za pomeraj se nesto ne slazu u zadatku
	int pomerajZadnjihX = 100 + desnoRobot + 50;
	int pomerajZadnjihY = 100 + 177;
	DrawLeg(pDC, ugaoZadnjeNoge, pomerajZadnjihX, pomerajZadnjihY);
	DrawLeg(pDC, -ugaoZadnjeNoge, pomerajZadnjihX, pomerajZadnjihY);

	//prednje noge 
	int pomerajPrednjihX = 100 + desnoRobot + 264;
	int pomerajPrednjihY = 100 + 177;
	DrawLeg(pDC, ugaoPrednjeNoge, pomerajPrednjihX, pomerajPrednjihY);
	DrawLeg(pDC, -ugaoPrednjeNoge, pomerajPrednjihX, pomerajPrednjihY);

	
}

void CRGIKol2017View::DrawLeg(CDC * pDC, double alpha, double dx, double dy)
{
	//gornji deo
	pDC->SetViewportOrg(dx + 26, dy + 29);
	XFORM oldF;
	pDC->GetWorldTransform(&oldF);

	Rotate(pDC, alpha, true);
	CRect leg(0, 0, Leg1->Width(), Leg1->Height());
	CRect leg1(-26, -29, Leg1->Width()-26, Leg1->Height()-29);
	Leg1->Draw(pDC, leg, leg1);

	pDC->SetWorldTransform(&oldF);

	pDC->SetViewportOrg(0, 0);
	//prvi donji deo
	pDC->SetViewportOrg(dx, dy);

	pDC->GetWorldTransform(&oldF);

	//sin(alpha) = dx / Leg1->Height();  cos(alpha) = dy / Leg1->Height();
	float dxx = sin(alpha*toRad)*(Leg1->Height()-40); 
	float dyy = cos(alpha*toRad)*Leg1->Height()-40;// 40 - deo gde se gonji i donji de0 noge preklapaju

	Translate(pDC, dxx, dyy, true);

	CRect leg2(0, 0, Leg2->Width(), Leg2->Height());
	Leg2->Draw(pDC, leg2, leg2);

	pDC->SetWorldTransform(&oldF);
	pDC->SetViewportOrg(0, 0);

	//drugi donji deo

	pDC->SetViewportOrg(dx, dy);

	pDC->GetWorldTransform(&oldF);

	//sin(alpha) = dx / Leg1->Height();  cos(alpha) = dy / Leg1->Height();
	dxx = sin(alpha*toRad)*(Leg1->Height() - 40) - 35; //35 - pomeraj zadnjeg dela u odnosu na dela u sredini
	dyy = cos(alpha*toRad)*Leg1->Height() - 44 + Leg2->Height() - 14;
	//14- deo gde se zadnji i srednji deo noge preklapaju

	Translate(pDC, dxx, dyy, true);

	CRect leg3(0, 0, Leg3->Width(), Leg3->Height());
	Leg3->Draw(pDC, leg3, leg3);

	pDC->SetWorldTransform(&oldF);
	pDC->SetViewportOrg(0, 0);

}

void CRGIKol2017View::DrawTransparentBitmap(CDC * pDC, DImage bitmapa)
{
	CRect bitmapRect(0, 0, bitmapa.Width(), bitmapa.Height());

	CDC* srcDC = new CDC();
	srcDC->CreateCompatibleDC(pDC);
	CDC* dstDC = new CDC();
	dstDC->CreateCompatibleDC(pDC);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, bitmapRect.Width(), bitmapRect.Height());
	srcDC->SelectObject(&bitmap);

	bitmapa.Draw(srcDC, bitmapRect, bitmapRect);

	CBitmap bmpMask;
	bmpMask.CreateBitmap(bitmapRect.Width(), bitmapRect.Height(), 1, 1, NULL);
	dstDC->SelectObject(&bmpMask);

	COLORREF clrTopLeft = srcDC->GetPixel(0, 0);	//prvipiksel slike => pozadina(njena boja)
	COLORREF cleSavebkBk = srcDC->SetBkColor(clrTopLeft);

	dstDC->BitBlt(0, 0, bitmapRect.Width(), bitmapRect.Height(), srcDC, 0, 0, SRCCOPY);

	COLORREF clrSaveDstText = srcDC->SetTextColor(RGB(255, 255, 255));
	srcDC->SetBkColor(RGB(0, 0, 0));
	srcDC->BitBlt(0, 0, bitmapRect.Width(), bitmapRect.Height(), dstDC, 0, 0, SRCAND);

	//priprema prikaza
	pDC->BitBlt(0, 0, bitmapRect.Width(), bitmapRect.Height(), dstDC, 0, 0, SRCAND);

	//prikaz
	pDC->BitBlt(0, 0, bitmapa.Width(), bitmapa.Height(), srcDC, 0, 0, SRCPAINT);

	dstDC->DeleteDC();
	delete dstDC;
	srcDC->DeleteDC();
	delete srcDC;
	pDC->SetViewportOrg(0, 0);
}


// CRGIKol2017View diagnostics

#ifdef _DEBUG
void CRGIKol2017View::AssertValid() const
{
	CView::AssertValid();
}

void CRGIKol2017View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRGIKol2017Doc* CRGIKol2017View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRGIKol2017Doc)));
	return (CRGIKol2017Doc*)m_pDocument;
}
#endif //_DEBUG


// CRGIKol2017View message handlers


BOOL CRGIKol2017View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}


void CRGIKol2017View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar != VK_UP && nChar != VK_DOWN  && nChar != VK_RIGHT
		&& nChar != 0x57 && nChar != 0x53 && nChar != 0x41 && nChar != 0x44)
		return;

	if (nChar == VK_UP)
	{
		sc += 0.1;
	}
	if (nChar == VK_DOWN)
	{
		sc -= 0.1;
	}

	if (nChar == VK_RIGHT)
	{
		desnoRobot += 10;
		//smerP = -1  prednje -- ; smerP = 1 prednje++
		//smerZ = 1 zadnje++ ; smerZ = -1 zadnje --
		if (smerP == -1 && ugaoPrednjeNoge > -20 )
		{
			ugaoPrednjeNoge -= 10;
		}
		if (smerP == -1 && ugaoPrednjeNoge == -20)
		{
			smerP = 1;
			ugaoPrednjeNoge += 10;
		}
		if (smerP == 1 && ugaoPrednjeNoge < 20)
		{
			ugaoPrednjeNoge += 10;
		}
		if (smerP == 1 && ugaoPrednjeNoge == 20)
		{
			smerP = -1;
			ugaoPrednjeNoge -= 10;
		}

		///////

		if (smerZ == -1 && ugaoZadnjeNoge > -20)
		{
			ugaoZadnjeNoge -= 10;
		}
		if (smerZ == -1 && ugaoZadnjeNoge == -20)
		{
			smerZ = 1;
			ugaoZadnjeNoge += 10;
		}
		if (smerZ == 1 && ugaoZadnjeNoge < 20)
		{
			ugaoZadnjeNoge += 10;
		}
		if (smerZ == 1 && ugaoZadnjeNoge == 20)
		{
			smerZ = -1;
			ugaoZadnjeNoge -= 10;
		}
	}

	//W=0x57 S=0x53  A=0x41 D=0x44
	if (nChar == 0x57 && gore != 0)
	{
		gore += 200;
		dole += 200;
	}
	if (nChar == 0x53 && dole != 0)
	{
		gore -= 200;
		dole -= 200;
	}
	if (nChar == 0x41 && levo != 0)
	{
		levo += 200;
		desno += 200;
	}
	if (nChar == 0x44 && desno != 0)
	{
		levo -= 200;
		desno -= 200;
	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
