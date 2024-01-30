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

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SHLStudio.h"
#include "ProjectWrapper.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, OnUpdateApplicationLook)

	ON_COMMAND(ID_VIEW_CAPTION_BAR, OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, OnUpdateViewCaptionBar)

	ON_COMMAND(ID_TOOLS_OPTIONS, OnOptions)

	ON_COMMAND(ID_VIEW_BUTTON_SOLUTION_EXPLORER, OnViewSolutionView)

	ON_COMMAND(ID_VIEW_BUTTON_SERVER_EXPLORER, OnViewServerExplorerView)

	ON_COMMAND(ID_VIEW_BUTTON_OUTPUT, OnViewOutputWindow)

	ON_COMMAND(ID_VIEW_BUTTON_PROPERTIES, OnViewPropertiesWindow)

	ON_WM_SETTINGCHANGE()

	ON_COMMAND(ID_BUTTON_NEW_QUERY, OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_NEW_QUERY, OnUpdateFileNew)

	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)

	ON_COMMAND(ID_BUTTON_NEW_SOLUTION, OnNewSolution)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_NEW_SOLUTION, OnUpdateNewSolution)

	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)

	ON_COMMAND(ID_BUTTON_OPEN_SOLUTION, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_OPEN_SOLUTION, OnUpdateFileOpen)

	ON_COMMAND(ID_BUTTON_CONNECTIONS_NEW, OnAddNewConnection)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CONNECTIONS_NEW, OnUpdateAddNewConnection)
	ON_COMMAND(ID_BUTTON_CONNECTIONS_SAVE, OnSaveConnections)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CONNECTIONS_SAVE, OnUpdateSaveConnections)

	ON_MESSAGE(WM_NEW_QUERY, OnNewQuery)
	ON_MESSAGE(WM_GET_RIBBONBAR, OnGetRibbonBar)

	ON_REGISTERED_MESSAGE(AFX_WM_ON_BEFORE_SHOW_RIBBON_ITEM_MENU, OnDropDownDatabase)

	ON_UPDATE_COMMAND_UI(ID_COMBO_SQL_DATABASES, OnUpdateComboDatabase)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Navigation pane will be created at left, so temporary disable docking at the left side:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);

	// Create a caption bar:
	if (!CreateCaptionBar())
	{
		TRACE0("Failed to create caption bar\n");
		return -1;      // fail to create
	}

	// Outlook bar is created and docking on the left side should be allowed.
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);

	// Load menu item image (not placed on any standard toolbars):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// create docking windows
	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}

	m_wndServerExploereView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndServerExploereView);

	m_wndSolutionView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndSolutionView);

	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);

	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);

	CProjectWrapper prjWrapper;
	prjWrapper.LoadIcons(m_wndSolutionView.GetMapIcon(), m_wndSolutionView.GetImageList(), m_wndSolutionView.GetMapTypeIcon());

	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	// Enable enhanced windows management dialog
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// Switch the order of document name and application name on the window title bar. This
	// improves the usability of the taskbar because the document name is visible with the thumbnail.
	ModifyStyle(0, FWS_PREFIXTITLE);

	m_wndServerExploereView.Properties = &m_wndProperties;
	m_wndServerExploereView.Output = &m_wndOutput;

	m_wndSolutionView.Properties = &m_wndProperties;
	m_wndSolutionView.Output = &m_wndOutput;

	/*CMFCRibbonButton* pButton = (CMFCRibbonButton*)m_wndRibbonBar.FindByID(ID_BUTTON_RESULT_GRID, FALSE, FALSE);
	CMFCRibbonPanel *pPanel = pButton->GetParentPanel();
	
	pPanel->Remove(1, FALSE);
	pPanel->Remove(0, FALSE);
	*/
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// Create Solution Explorer
	CString strSolutionView;
	bNameValid = strSolutionView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndSolutionView.Create(strSolutionView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_SolutionView, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Solution Explorer window\n");
		return FALSE; // failed to create
	}
	
	// Create Server Explorer
	CString strServerExplorer;
	bNameValid = strServerExplorer.LoadString(IDS_SERVEREXPLORER);
	ASSERT(bNameValid);
	if (!m_wndServerExploereView.Create(strServerExplorer, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_SERVER_EXPLOERE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Solution Explorer window\n");
		return FALSE; // failed to create
	}

	// Create output window
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Output window\n");
		return FALSE; // failed to create
	}

	// Create properties window
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties window\n");
		return FALSE; // failed to create
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);

	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hSolutionViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndSolutionView.SetIcon(hSolutionViewIcon, FALSE);

	//TODO mudar Icons
	HICON hServerViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndServerExploereView.SetIcon(hServerViewIcon, FALSE);
	
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

	UpdateMDITabbedBarsIcons();
}

BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("Failed to create caption bar\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_bTabIcons = FALSE;    // set to TRUE to enable document icons on MDI taba
	mdiTabParams.m_bAutoColor = FALSE;    // set to FALSE to disable auto-coloring of MDI tabs
	mdiTabParams.m_bDocumentMenu = TRUE; // enable the document menu at the right edge of the tab area

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
		case ID_VIEW_APPLOOK_WIN_2000:
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
			m_wndRibbonBar.SetWindows7Look(FALSE);
			mdiTabParams.m_bActiveTabCloseButton = FALSE;      // set to FALSE to place close button at right of tab area
			mdiTabParams.m_style = CMFCTabCtrl::STYLE_FLAT_SHARED_HORZ_SCROLL;
			break;

		case ID_VIEW_APPLOOK_OFF_XP:
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
			m_wndRibbonBar.SetWindows7Look(FALSE);
			mdiTabParams.m_bActiveTabCloseButton = FALSE;      // set to FALSE to place close button at right of tab area
			mdiTabParams.m_style = CMFCTabCtrl::STYLE_FLAT_SHARED_HORZ_SCROLL;
			break;

		case ID_VIEW_APPLOOK_WIN_XP:
			CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
			m_wndRibbonBar.SetWindows7Look(FALSE);
			mdiTabParams.m_bActiveTabCloseButton = FALSE;      // set to FALSE to place close button at right of tab area
			mdiTabParams.m_style = CMFCTabCtrl::STYLE_FLAT_SHARED_HORZ_SCROLL;
			break;

		case ID_VIEW_APPLOOK_OFF_2003:
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
			CDockingManager::SetDockingMode(DT_SMART);
			m_wndRibbonBar.SetWindows7Look(FALSE);
			mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
			mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D;
			break;

		case ID_VIEW_APPLOOK_VS_2005:
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
			CDockingManager::SetDockingMode(DT_SMART);
			m_wndRibbonBar.SetWindows7Look(FALSE);
			mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
			mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_VS2005;
			break;

		case ID_VIEW_APPLOOK_VS_2008:
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
			CDockingManager::SetDockingMode(DT_SMART);
			m_wndRibbonBar.SetWindows7Look(FALSE);
			mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
			mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ROUNDED;
			break;

		case ID_VIEW_APPLOOK_WINDOWS_7:
			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
			CDockingManager::SetDockingMode(DT_SMART);
			m_wndRibbonBar.SetWindows7Look(TRUE);
			mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
			mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // other styles available...
			break;

		default:
			switch (theApp.m_nAppLook)
			{
				case ID_VIEW_APPLOOK_OFF_2007_BLUE:
					CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
					break;

				case ID_VIEW_APPLOOK_OFF_2007_BLACK:
					CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
					break;

				case ID_VIEW_APPLOOK_OFF_2007_SILVER:
					CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
					break;

				case ID_VIEW_APPLOOK_OFF_2007_AQUA:
					CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
					break;
			}

			CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
			CDockingManager::SetDockingMode(DT_SMART);
			m_wndRibbonBar.SetWindows7Look(FALSE);
			break;
	}

	m_wndOutput.UpdateFonts();
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != NULL);

	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}

void CMainFrame::OnViewSolutionView()
{
	// Show or activate the pane, depending on current state.  The
	// pane can only be closed via the [x] button on the pane frame.
	m_wndSolutionView.ShowPane(TRUE, FALSE, TRUE);
	m_wndSolutionView.SetFocus();
}

void CMainFrame::OnViewServerExplorerView()
{
	// Show or activate the pane, depending on current state.  The
	// pane can only be closed via the [x] button on the pane frame.
	m_wndServerExploereView.ShowPane(TRUE, FALSE, TRUE);
	m_wndServerExploereView.SetFocus();
}

void CMainFrame::OnViewOutputWindow()
{
	// Show or activate the pane, depending on current state.  The
	// pane can only be closed via the [x] button on the pane frame.
	m_wndOutput.ShowPane(TRUE, FALSE, TRUE);
	m_wndOutput.SetFocus();
}

void CMainFrame::OnViewPropertiesWindow()
{
	// Show or activate the pane, depending on current state.  The
	// pane can only be closed via the [x] button on the pane frame.
	m_wndProperties.ShowPane(TRUE, FALSE, TRUE);
	m_wndProperties.SetFocus();
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CMDIFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}

LRESULT  CMainFrame::OnGetRibbonBar(WPARAM wParam, LPARAM lParam)
{
	return (LRESULT)&m_wndRibbonBar;
}

LRESULT  CMainFrame::OnNewQuery(WPARAM wParam, LPARAM lParam)
{
	CQueryDataConnectionEntity* dataconnection;

	try
	{
		dataconnection = (CQueryDataConnectionEntity*)wParam;

		if(dataconnection == NULL)
			m_wndServerExploereView.NewQuery(0, _T(""));
		else
			m_wndServerExploereView.NewQuery(dataconnection, dataconnection->DefaultDatabase);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);
		MessageBox(szMessage, _T("Critical Error"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	return 0;
}

void CMainFrame::OnNewQuery()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_NEW_QUERY, 0, 0);
}

void CMainFrame::OnUpdateNewQuery(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnFileNew()
{
	try
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_NEW_QUERY, 0, 0);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);
		MessageBox(szMessage, _T("Critical Error"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}


void CMainFrame::OnUpdateFileNew(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnNewSolution()
{
	NewSolution();
}

void CMainFrame::OnUpdateNewSolution(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnFileOpen()
{
	OpenSolution();
}

void CMainFrame::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CMainFrame::OpenSolution(void)
{
	CString strSolutionFullName;
	CString strDefualt;
	CString strFilter;
	CString strFileName;
	CProjectWrapper prjWrapper;

	try
	{
		strFileName = _T("");
		strFilter = _T("SHLStudio Solution (*.jsl) |*.jsl | All files (*.*)||");
		strDefualt = _T("*.jsl");
		strSolutionFullName = prjWrapper.SelectFile(strFileName, strDefualt, strFilter);

		if(strSolutionFullName != _T(""))
		{
			prjWrapper.LoadSolution(strSolutionFullName, m_wndSolutionView.GetTreeView(), m_solution, m_wndSolutionView.GetMapIcon(), m_wndSolutionView.GetImageList());
			m_wndSolutionView.SolutionEntity = &m_solution;

			ShowPane(&m_wndSolutionView, true,true, true);
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);
		MessageBox(szMessage, _T("Critical Error"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}


void CMainFrame::NewSolution(void)
{
	CString strSolutionFullName;
	CString strDefualt;
	CString strFilter;
	CString strFileName;
	CProjectWrapper prjWrapper;

	try
	{
		m_wndSolutionView.SolutionEntity = &m_solution;
		m_wndSolutionView.Properties = &m_wndProperties;
		m_wndSolutionView.Output = &m_wndOutput;

		m_wndSolutionView.NewProject();

		ShowPane(&m_wndSolutionView, true,true, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);
		MessageBox(szMessage, _T("Critical Error"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}


void CMainFrame::NewProject(void)
{
	try
	{
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);
		MessageBox(szMessage, _T("Critical Error"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}


void CMainFrame::OpenProject(void)
{
	try
	{

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);
		MessageBox(szMessage, _T("Critical Error"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}


void CMainFrame::CallWindow(void)
{
	try
	{
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);
		MessageBox(szMessage, _T("Critical Error"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CMainFrame::OnAddNewConnection()
{
	try
	{
		m_wndServerExploereView.AddConnection();
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);
		MessageBox(szMessage, _T("Critical Error"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CMainFrame::OnUpdateAddNewConnection(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CMainFrame::OnSaveConnections()
{
	try
	{
		m_wndServerExploereView.SaveConnections();
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);
		MessageBox(szMessage, _T("Critical Error"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CMainFrame::OnUpdateComboDatabase(CCmdUI* pCmdUI)
{
	CMFCRibbonComboBox* combo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_COMBO_SQL_DATABASES));
	combo->RemoveAllItems();
	pCmdUI->Enable(FALSE);
}

void CMainFrame::OnUpdateSaveConnections(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

LRESULT CMainFrame::OnDropDownDatabase(WPARAM wParam, LPARAM lParam)
{
	CMDIChildWnd* pChild = NULL;
	CMFCRibbonBaseElement* pElem = (CMFCRibbonBaseElement*) lParam;
	ASSERT_VALID(pElem);

	switch (pElem->GetID())
	{
		case ID_COMBO_SQL_DATABASES:
			pChild = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
			if(pChild)
				::SendMessage(pChild->GetSafeHwnd(), AFX_WM_ON_BEFORE_SHOW_RIBBON_ITEM_MENU, wParam, lParam);
			break;
	}

	return 0;
}
