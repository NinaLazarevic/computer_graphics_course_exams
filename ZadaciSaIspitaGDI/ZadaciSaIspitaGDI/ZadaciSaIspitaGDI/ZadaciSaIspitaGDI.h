
// ZadaciSaIspitaGDI.h : main header file for the ZadaciSaIspitaGDI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CZadaciSaIspitaGDIApp:
// See ZadaciSaIspitaGDI.cpp for the implementation of this class
//

class CZadaciSaIspitaGDIApp : public CWinApp
{
public:
	CZadaciSaIspitaGDIApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CZadaciSaIspitaGDIApp theApp;
