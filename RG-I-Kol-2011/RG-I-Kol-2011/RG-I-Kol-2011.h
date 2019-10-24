
// RG-I-Kol-2011.h : main header file for the RG-I-Kol-2011 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRGIKol2011App:
// See RG-I-Kol-2011.cpp for the implementation of this class
//

class CRGIKol2011App : public CWinAppEx
{
public:
	CRGIKol2011App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRGIKol2011App theApp;
