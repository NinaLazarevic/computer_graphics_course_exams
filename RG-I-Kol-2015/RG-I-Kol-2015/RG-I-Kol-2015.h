
// RG-I-Kol-2015.h : main header file for the RG-I-Kol-2015 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRGIKol2015App:
// See RG-I-Kol-2015.cpp for the implementation of this class
//

class CRGIKol2015App : public CWinApp
{
public:
	CRGIKol2015App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRGIKol2015App theApp;
