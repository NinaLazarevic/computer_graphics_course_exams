
// RG-I-Kol-2017.h : main header file for the RG-I-Kol-2017 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRGIKol2017App:
// See RG-I-Kol-2017.cpp for the implementation of this class
//

class CRGIKol2017App : public CWinApp
{
public:
	CRGIKol2017App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRGIKol2017App theApp;
