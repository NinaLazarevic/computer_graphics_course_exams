
// RG-I-Kol-2013.h : main header file for the RG-I-Kol-2013 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRGIKol2013App:
// See RG-I-Kol-2013.cpp for the implementation of this class
//

class CRGIKol2013App : public CWinApp
{
public:
	CRGIKol2013App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRGIKol2013App theApp;
