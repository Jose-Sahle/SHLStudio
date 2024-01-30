// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// SHLStudio.h : main header file for the SHLStudio application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "Property.h"


// CSHLStudioApp:
// See SHLStudio.cpp for the implementation of this class
//

class CSHLStudioApp : public CWinAppEx
{
public:
	CSHLStudioApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()

public:
	bool LookupTemplate(CDocTemplate* pDocTemplate);

	// Properties
public:
 	READONLY_PROPERTY(LIBRARYLIST&, LoadedLibraryList)
  	GET(LoadedLibraryList) 
 	{ 
 		return m_loadedlibrarylist; 
	}

 	READONLY_PROPERTY(MULTIDOCTEMPLATELIST&, MultiDocTemplateList)
  	GET(MultiDocTemplateList) 
 	{ 
 		return m_multidoctemplatelist; 
	}

	// Private Methods
private:
	void AtivarJanela();

	// Private Members
private:
	LIBRARYLIST				m_loadedlibrarylist;
	MULTIDOCTEMPLATELIST	m_multidoctemplatelist;

};

extern CSHLStudioApp theApp;
