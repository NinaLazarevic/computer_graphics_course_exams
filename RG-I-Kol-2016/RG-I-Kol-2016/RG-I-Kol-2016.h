
// RG-I-Kol-2016.h : main header file for the RG-I-Kol-2016 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRGIKol2016App:
// See RG-I-Kol-2016.cpp for the implementation of this class
//

class CRGIKol2016App : public CWinAppEx
{
public:
	CRGIKol2016App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRGIKol2016App theApp;
