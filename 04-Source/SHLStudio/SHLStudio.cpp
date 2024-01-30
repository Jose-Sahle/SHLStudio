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

// SHLStudio.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "SHLStudio.h"
#include "MainFrm.h"
#include "Library.h"
#include "ChildFrm.h"
#include "SHLStudioDoc.h"
#include "SHLStudioView.h"

#include "DlgProjectAndFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSHLStudioApp

BEGIN_MESSAGE_MAP(CSHLStudioApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CSHLStudioApp::OnAppAbout)
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CSHLStudioApp construction

CSHLStudioApp::CSHLStudioApp()
{
	m_bHiColorIcons = TRUE;

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("SHLInfo.SHLStudio.1.0"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CSHLStudioApp object

CSHLStudioApp theApp;


// CSHLStudioApp initialization

BOOL CSHLStudioApp::InitInstance()
{
	CPath path;

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	if(!AfxInitRichEdit2( ))
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("SHLStudio-Settings"));

	CString registryBase;
	path.SetPath(GetApplicationDirectory()); 
	registryBase = path.GetPath();
	registryBase.Replace(_T(":"), _T("_"));
	registryBase.Replace(_T("\\"), _T("_"));
	SetRegistryBase(registryBase);

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	InitContextMenuManager();
	InitShellManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate*	pDocTemplate = new CMultiDocTemplate(IDR_SHLStudioTYPE,
		RUNTIME_CLASS(CSHLStudioDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSHLStudioView));

	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CSHLStudioApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CSHLStudioApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CSHLStudioApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSHLStudioApp customization load/save methods

void CSHLStudioApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;

	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);

	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER_SOLUTION);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER_PROJECT);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER_ITEM);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER_FOLDER);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER_DEPENDENCY);

	bNameValid = strName.LoadString(IDS_DATA_CONNECTION);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_DATA_CONNECTION_NULL);
	GetContextMenuManager()->AddMenu(strName, IDR_DATA_CONNECTION);
	GetContextMenuManager()->AddMenu(strName, IDR_DATA_CONNECTION_QUERY);
}

bool CSHLStudioApp::LookupTemplate(CDocTemplate* pDocTemplate)
{
	bool bRet = false;
	POSITION	posTemplate = NULL;
	HMODULE hmod = NULL;
	CString key;
	CMultiDocTemplate* DocTemplate = NULL;

	try
	{
		posTemplate = m_multidoctemplatelist.GetStartPosition();

		while(posTemplate != NULL)
		{
			m_multidoctemplatelist.GetNextAssoc( posTemplate, key, DocTemplate );

			if(posTemplate != NULL && pDocTemplate == DocTemplate)
			{
				bRet = true;
				break;
			}
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);
		AfxMessageBox(szMessage);
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		AfxMessageBox(szMessage);
	}

	return bRet;
}

void CSHLStudioApp::LoadCustomState()
{
}

void CSHLStudioApp::SaveCustomState()
{
}

// CSHLStudioApp message handlers
