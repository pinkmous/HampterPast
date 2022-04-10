
// F2 mouse.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CF2mouseApp:
// See F2 mouse.cpp for the implementation of this class
//

class CF2mouseApp : public CWinApp
{
public:
	CF2mouseApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CF2mouseApp theApp;