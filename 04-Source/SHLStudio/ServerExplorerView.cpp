/* ***************************************************************************
 * Arquivo: SolutionExplorerView                                             *
 *                                                                           *
 * Classe treeview contendo os banco de das para a ação de Query Analyzer    *
 * do SHLStudio                                                              *
 *                                                                           *
 * Data:28/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#include "stdafx.h"
#include "SHLStudio.h"
#include "ServerExplorerView.h"
#include "SHLDataConnection.h"
#include "ISHLQuery.h"
#include "ChildFrm.h"

#pragma warning(disable:4800)

// CServerExplorerView

IMPLEMENT_DYNAMIC(CServerExplorerView, CDockablePane)

CServerExplorerView::CServerExplorerView()
{
	m_bEditLabelMode = FALSE;
	m_hItem = NULL;
	m_hContextMenuItemselected = NULL;
	m_hAccel = NULL;
}

CServerExplorerView::~CServerExplorerView()
{
	if(m_hAccel)
		DestroyAcceleratorTable(m_hAccel);

	Reset();
}

BEGIN_MESSAGE_MAP(CServerExplorerView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()

	ON_NOTIFY(NM_CLICK, IDD_TREE_VIEW,  OnButtonDown)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDD_TREE_VIEW,  OnTreeViewExpanding)

	ON_COMMAND(ID_DATACONNECTION_CONNECT, OnConnectContextMenu)	
	ON_UPDATE_COMMAND_UI(ID_DATACONNECTION_CONNECT, OnUpdateConnectContextMenu)

	ON_COMMAND(ID_DATACONNECTION_DISCONNECT, OnDisconnectContextMenu)
	ON_UPDATE_COMMAND_UI(ID_DATACONNECTION_DISCONNECT, OnUpdateDisconnectContextMenu)

	ON_COMMAND(ID_DATACONNECTION_REFRESH, OnRefreshContextMenu)
	ON_UPDATE_COMMAND_UI(ID_DATACONNECTION_REFRESH, OnUpdateRefreshContextMenu)

	ON_COMMAND(ID_DATACONNECTION_ADDNEWCONNECTION, OnAddConnection)
	ON_COMMAND(ID_DATACONNECTION_REMOVECONNECTION, OnRemoveConnection)
	ON_COMMAND(ID_DATACONNECTION_SAVECONNECTIONS, OnSaveConnections)

	ON_COMMAND(ID_DATACONNECTION_CONNECT_SERVER_EXPLORER_TOOLBAR, OnConnect)	
	ON_COMMAND(ID_DATACONNECTION_DISCONNECT_SERVER_EXPLORER_TOOLBAR, OnDisconnect)
	ON_COMMAND(ID_DATACONNECTION_REFRESH_SERVER_EXPLORER_TOOLBAR, OnRefresh)

	ON_UPDATE_COMMAND_UI(ID_DATACONNECTION_CONNECT_SERVER_EXPLORER_TOOLBAR, OnUpdateConnect)
	ON_UPDATE_COMMAND_UI(ID_DATACONNECTION_DISCONNECT_SERVER_EXPLORER_TOOLBAR, OnUpdateDisconnect)
	ON_UPDATE_COMMAND_UI(ID_DATACONNECTION_REFRESH_SERVER_EXPLORER_TOOLBAR, OnUpdateRefresh)

	ON_COMMAND(ID_DATACONNECTION_PROPERTIES, OnProperties)
	ON_COMMAND(ID_DATACONNECTION_NEWQUERY, OnNewQuery)

	ON_COMMAND(ID_FILE_NEW, OnNewQueryAccel)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)

	ON_NOTIFY(TVN_BEGINLABELEDIT, IDD_TREE_VIEW, OnBeginLabelEdit)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDD_TREE_VIEW, OnEndLabelEdit)

	ON_COMMAND(ID_DATACONNECTION_RENAME, OnRenameConnection)
END_MESSAGE_MAP()


// CServerExplorerView message handlers
#pragma region REGION_EVENTS
int CServerExplorerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	HINSTANCE hInst = ::GetModuleHandle(NULL);

	ASSERT(m_hAccel == NULL);
	m_hAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));
	ASSERT(m_hAccel != NULL);

	return InitControls();
}

BOOL CServerExplorerView::PreTranslateMessage(MSG* pMsg)
{
	if(m_bEditLabelMode && WM_KEYDOWN == pMsg->message && (VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
	{
		m_wndServerView.PostMessage(TVM_ENDEDITLABELNOW);

		return TRUE;
	}

	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if (m_hAccel != NULL)
		{
			if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
				return TRUE;
		}
	}

	return CDockablePane::PreTranslateMessage(pMsg);
}

void CServerExplorerView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	AdjustLayout();
}

void CServerExplorerView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndServerView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CServerExplorerView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndServerView.SetFocus();
}

void CServerExplorerView::OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_bEditLabelMode = TRUE;

	*pResult = 0;
}

void CServerExplorerView::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	m_bEditLabelMode = FALSE;

	EndLabelEdit(pTVDispInfo);	

	*pResult = 0;
}

void CServerExplorerView::OnUpdateConnect(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(EnableConnect(ValidItem(m_hItem)));
}

void CServerExplorerView::OnUpdateDisconnect(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(EnableDisconnect(ValidItem(m_hItem)));
}

void CServerExplorerView::OnUpdateRefresh(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(EnableRefresh(ValidItem(m_hItem)));
}

void CServerExplorerView::OnUpdateConnectContextMenu(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(EnableConnect(m_hContextMenuItemselected));
}

void CServerExplorerView::OnUpdateDisconnectContextMenu(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(EnableDisconnect(m_hContextMenuItemselected));
}

void CServerExplorerView::OnUpdateRefreshContextMenu(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(EnableRefresh(m_hContextMenuItemselected));
}

void CServerExplorerView::OnConnect()
{
	ConnectDatabaseServer(m_hItem);
}

void CServerExplorerView::OnDisconnect()
{
	DisconnectDatabaseServer(m_hItem);
}

void CServerExplorerView::OnRefresh()
{
	Refresh(m_hItem);
}

void CServerExplorerView::OnConnectContextMenu()
{
	ConnectDatabaseServer(m_hContextMenuItemselected);
}

void CServerExplorerView::OnDisconnectContextMenu()
{
	DisconnectDatabaseServer(m_hContextMenuItemselected);
}

void CServerExplorerView::OnRefreshContextMenu()
{
	Refresh(m_hContextMenuItemselected);
}

void CServerExplorerView::OnAddConnection()
{
	AddConnection();
}

void CServerExplorerView::OnRemoveConnection()
{
	RemoveConnection(m_hContextMenuItemselected);
}

void CServerExplorerView::OnSaveConnections()
{
	SaveConnections();
}

void CServerExplorerView::OnProperties()
{
	ShowProperties(m_hContextMenuItemselected, TRUE);
}

void CServerExplorerView::OnNewQueryAccel()
{
	NewQuery(m_wndServerView.GetSelectedItem());
}

void CServerExplorerView::OnRenameConnection()
{
	RenameConnection();
}

void CServerExplorerView::OnNewQuery()
{
	if(m_hContextMenuItemselected)
		NewQuery(m_hContextMenuItemselected);
	else
		NewQuery(m_wndServerView.GetSelectedItem());
}

void CServerExplorerView::OnUpdateFileNew(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CServerExplorerView::OnTreeViewExpanding(NMHDR* pNMHDR, LRESULT* pResult)
{
	FillChildrenTreeViewItems();

	if(m_hItem == NULL || m_hItem == m_wndServerView.GetRootItem() || !IsValidItem(m_hItem))
		return;

	if(m_wndServerView.GetChildItem(m_hItem) == NULL)
		m_wndServerView.SetItemState(m_hItem, 0, TVIS_EXPANDED);

	*pResult = 0;
}

void CServerExplorerView::OnButtonDown(NMHDR* pNMHDR, LRESULT* pResult)
{
	PressedButtonTreeView();

	*pResult = 0;
}

void CServerExplorerView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndServerView;
	ASSERT_VALID(pWndTree);
	HTREEITEM hTreeItem = NULL;

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Select clicked item:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	ContextMenu(hTreeItem, point);
}
#pragma endregion REGION_EVENTS

#pragma region REGION_PUBLIC_METHODS
void CServerExplorerView::AddConnection()
{
	HTREEITEM hNewItem;
	bool bAddConnection = false;

	try
	{
		bAddConnection = m_ptrSHLQuery->AddConnection(m_wndServerView, m_dataconnection, hNewItem);
		if(!bAddConnection )
		{
			if(!m_ptrSHLQuery->GetLastError().IsEmpty())
				AfxMessageBox(m_ptrSHLQuery->GetLastError());

			return;
		}

		ConnectDatabaseServer(hNewItem);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::SaveConnections()
{
	HTREEITEM hRoot;
	HTREEITEM hSibbling;
	CString rootText;

	try
	{
		hRoot = m_wndServerView.GetRootItem();

		if(!m_ptrSHLQuery->SaveConnections(m_dataconnection))
		{
			AfxMessageBox(m_ptrSHLQuery->GetLastError());
			return;
		}

		rootText = m_wndServerView.GetItemText(hRoot);
		rootText.Replace(_T("*"), _T(""));
		m_wndServerView.SetItemText(hRoot, rootText);
		m_wndServerView.SetItemState(hRoot, 0, TVIS_BOLD);

		hSibbling = m_wndServerView.GetChildItem(hRoot);

		while(hSibbling != NULL)
		{
			rootText = m_wndServerView.GetItemText(hSibbling);
			rootText.Replace(_T("*"), _T(""));
			m_wndServerView.SetItemText(hSibbling, rootText);

			hSibbling = m_wndServerView.GetNextSiblingItem(hSibbling);
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::NewQuery(CQueryDataConnectionEntity* dataconnection, CString databasename)
{
	CDocument* pDoc = NULL;
	CMultiDocTemplate* pDocTemplate = NULL;
	CString strKeyMultiDocTemplate;
	CString strDatabase;

	try
	{
		strKeyMultiDocTemplate = _T("shlquery.dll");

		theApp.MultiDocTemplateList.Lookup(strKeyMultiDocTemplate, pDocTemplate);

		pDoc = (CDocument*)pDocTemplate->OpenDocumentFile(NULL);
		pDoc->OnNewDocument();
		pDoc->UpdateAllViews(NULL, NULL, NULL);
		pDoc->UpdateFrameCounts();
		m_ptrSHLQuery->NewQuery(dataconnection, pDoc, databasename);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::OnChangeVisualStyle()
{
	//m_wndToolBar.CleanUpLockedImages();
	//m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Locked */);

	m_ServerViewImages.DeleteImageList();

	UINT uiBmpId = IDB_SOLUTION_EXPLORER;//theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_ServerViewImages.Create(IMAGELISTSIZESOLUTIONEXPLORER, bmpObj.bmHeight, nFlags, 0, 0);
	m_ServerViewImages.Add(&bmp, IMAGEMASKSOLUTIONEXPLORER);

	m_wndServerView.SetImageList(&m_ServerViewImages, TVSIL_NORMAL);
}

void CServerExplorerView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndServerView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}
#pragma endregion REGION_PUBLIC_METHODS

#pragma region REGION_PRIVATE_METHODS
int CServerExplorerView::InitControls()
{
	int nRet = -1;

	try
	{
		// Create view:
		CRect rectDummy;
		rectDummy.SetRectEmpty();

		CBitmap bm;

		const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_EDITLABELS;
                    
		if (!m_wndServerView.Create(dwViewStyle, rectDummy, this, IDD_TREE_VIEW))
		{
			TRACE0("Failed to create solution explorer\n");
			return -1;      // fail to create
		}

		// Load view images:
		///m_ServerViewImages.Create(IDB_SOLUTION_EXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, 0, IMAGEMASKSOLUTIONEXPLORER);
		m_ServerViewImages.Create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 0);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_CONNECTIONS), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_ADD), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_DELETE), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_SAVE), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_CONNECTION), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_CONNECTION_ON), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_TABLE), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_COLUMN), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_FOLDER), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_BASE), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_PROGRAMATICALLY), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);		
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_KEY), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_CONSTRAINT), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_INDEX), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_TRIGGER), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
		bm.m_hObject=(HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_DATA_SEQUENCE), IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_DEFAULTCOLOR);
		m_ServerViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);

		m_wndServerView.SetImageList(&m_ServerViewImages, TVSIL_NORMAL);

		m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
		m_wndToolBar.SetOwner(this);
		//m_wndToolBar.LoadToolBar(IDR_SERVER_EXPLORER, 0, 0, TRUE /* Is locked */);
		
		m_wndToolBar.ResetAllImages();
		m_wndToolBar.RemoveAllButtons();
		m_wndToolBar.SetButtons(NULL, 3);
		//m_wndToolBar.SetGrayDisabledButtons(TRUE);

		m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);		
		m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

		m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

		if(!m_wndToolBar.InsertNewButtonEx(ID_DATACONNECTION_CONNECT_SERVER_EXPLORER_TOOLBAR, IDB_DATA_CONNECTION_16))
			AfxMessageBox(_T("Don't load IDB_DATA_CONNECTION_16"));

		if(!m_wndToolBar.InsertNewButtonEx(ID_DATACONNECTION_DISCONNECT_SERVER_EXPLORER_TOOLBAR, IDB_DATA_DELETE_16))
			AfxMessageBox(_T("Don't load IDB_DATA_DELETE_16"));

		m_wndToolBar.InsertSeparator();

		if(!m_wndToolBar.InsertNewButtonEx(ID_DATACONNECTION_REFRESH_SERVER_EXPLORER_TOOLBAR, IDB_DATA_REFRESH_16))
			AfxMessageBox(_T("Don't load IDB_DATA_REFRESH_16"));
		
		m_wndToolBar.RecalcLayout();

		AdjustLayout();

		::SetWindowTheme(m_wndServerView.m_hWnd, L"Explorer", NULL);

		InitExplorerTreeView();

		nRet = 0;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));

		nRet = -1;
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));

		nRet = -1;
	}

	return nRet;
}

void CServerExplorerView::InitExplorerTreeView()
{
	HTREEITEM hItemDataConnection;

	try
	{
		hItemDataConnection = m_wndServerView.InsertItem(_T("Data Connections"), IMAGE_DATA_CONNECTIONS, IMAGE_DATA_CONNECTIONS, NULL);
		m_wndServerView.SetItemData(hItemDataConnection, SHLDATACONNECTION_ID_TREE_DATA_CONNECTION);

		LoadShlQuery();

		LoadConnections();
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::LoadShlQuery()
{
	CString strDLLName;
	HMODULE hmod = NULL;
	LPFNGETSHLQUERYINSTANCE pGetSHLQueryInstance;
	CString strKeyMultiDocTemplate;

	CRuntimeClass* pNewFrameClass = NULL;
	CRuntimeClass* pNewViewClass = NULL;
	CRuntimeClass* pNewDocClass = NULL;
	CMultiDocTemplate* pDocTemplate = NULL;

	try
	{
		strDLLName = _T("shlquery.dll");
		strKeyMultiDocTemplate.Format(_T("%s"), strDLLName);

		theApp.LoadedLibraryList.Lookup(strDLLName, hmod);

		if(hmod == NULL)
		{
			hmod = ::LoadLibraryFromApplicationDirectory(strDLLName, _T("binaries"));

			if (!hmod)
			{
				CString errorMessage;
				errorMessage.Format(_T("%s\\Binaries\\%s not be found!\n\nThe will be terminate!"), ::GetApplicationDirectory(), strDLLName);
				::MessageBox(NULL, errorMessage, _T("Error: Load library"), MB_OK);
				exit(-30);
			}

			theApp.LoadedLibraryList[strDLLName] = hmod;
		}

		pGetSHLQueryInstance = (LPFNGETSHLQUERYINSTANCE)::GetProcAddress(hmod, "GetSHLQueryInstance");		

		m_ptrSHLQuery = (SHLQUERYHANDLE)pGetSHLQueryInstance();

		theApp.MultiDocTemplateList.Lookup(strKeyMultiDocTemplate, pDocTemplate);

		if(pDocTemplate == NULL)
		{
			m_ptrSHLQuery->LoadDocumentView(pNewFrameClass, pNewViewClass, pNewDocClass);

			pDocTemplate = new CMultiDocTemplate(IDR_GUI_DETYPE,
				pNewDocClass,
				pNewFrameClass, // custom MDI child frame
				NULL);

			if (pDocTemplate == NULL)
				return;

			theApp.MultiDocTemplateList[strKeyMultiDocTemplate] = pDocTemplate;
			theApp.AddDocTemplate(pDocTemplate);
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::LoadConnections()
{
	try
	{
		m_ptrSHLQuery->FillTreeViewConnections(m_wndServerView, m_dataconnection);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::PressedButtonTreeView()
{
	CPoint cursorPos;
	CPoint cursorPosCliente;

	HTREEITEM		hItem;

	UINT uFlags;

	SHLDATACONNECTION nType = SHLDATACONNECTION_ID_TREE_DATA_NO_INFORMATION;

	try
	{	
		cursorPos.x= GetCurrentMessage()->pt.x;
		cursorPos.y= GetCurrentMessage()->pt.y;

		cursorPosCliente.x= GetCurrentMessage()->pt.x;
		cursorPosCliente.y= GetCurrentMessage()->pt.y;

		m_wndServerView.ScreenToClient(&cursorPosCliente);
		hItem = m_wndServerView.HitTest(cursorPosCliente, &uFlags);
		
		if(hItem == NULL)
			return;

		m_hItem = hItem;
		nType = (SHLDATACONNECTION)m_wndServerView.GetItemData(hItem);
		ShowProperties(m_hItem, FALSE);
	}
	catch(...)
	{
		CString strMsg;
		DWORD err = GetLastError();

		strMsg.Format(_T("Erro: %i\r\n%s"), err, ErrorMessage(err));
		MessageBox(strMsg, _T("0x00018"));
	}
}

void CServerExplorerView::ContextMenu(HTREEITEM itemSelected, CPoint& point)
{
	SHLDATACONNECTION nType;

	m_wndServerView.SetFocus();
	
	m_hContextMenuItemselected = itemSelected;

	try
	{
		if(itemSelected == NULL)
			return;

		nType = (SHLDATACONNECTION)m_wndServerView.GetItemData(itemSelected);

		switch(nType)
		{
			case SHLDATACONNECTION_ID_TREE_DATA_CONNECTION:				
				theApp.GetContextMenuManager()->ShowPopupMenu(IDR_DATA_CONNECTION_NULL, point.x, point.y, this, TRUE);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION:
				theApp.GetContextMenuManager()->ShowPopupMenu(IDR_DATA_CONNECTION, point.x, point.y, this, TRUE);
				break;
			default:
				theApp.GetContextMenuManager()->ShowPopupMenu(IDR_DATA_CONNECTION_QUERY, point.x, point.y, this, TRUE);
				break;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::FillChildrenTreeViewItems()
{
	CPoint cursorPos;
	CPoint cursorPosCliente;

	HTREEITEM		hItem;

	SHLDATACONNECTION	nType;

	UINT uFlags;

	try
	{	
		cursorPos.x= GetCurrentMessage()->pt.x;
		cursorPos.y= GetCurrentMessage()->pt.y;

		cursorPosCliente.x= GetCurrentMessage()->pt.x;
		cursorPosCliente.y= GetCurrentMessage()->pt.y;
		
		m_wndServerView.ScreenToClient(&cursorPosCliente);
		hItem = m_wndServerView.HitTest(cursorPosCliente, &uFlags);

		m_hItem = hItem;

		if(hItem == NULL || hItem == m_wndServerView.GetRootItem())
			return;

		nType = (SHLDATACONNECTION)m_wndServerView.GetItemData(hItem);

		LoadDatabaseElementsByNode(nType, hItem, FALSE);
	}
	catch(...)
	{
		CString strMsg;
		DWORD err = GetLastError();

		strMsg.Format(_T("Erro: %i\r\n%s"), err, ErrorMessage(err));
		MessageBox(strMsg, _T("0x00017"));
	}
}

void CServerExplorerView::LoadDatabaseElementsByNode(SHLDATACONNECTION nType, HTREEITEM pItem, BOOL brefresh)
{
	try
	{
		switch(nType)
		{
			// ALL CASES
			case SHLDATACONNECTION_ID_TREE_DATA_CONNECTION:				
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION:
				if(brefresh)
					RefreshDatabaseServer(pItem);
				else
					ConnectDatabaseServer(pItem);
				break;

			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_FOLDER:
				ShowSysTables(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_COLUMN_FOLDER:
				ShowSysColumns(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_VIEW_FOLDER:
				ShowSysViews(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_SEQUENCE_FOLDER:
				ShowSysSequences(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_CONSTRAINT_FOLDER:
				ShowSysConstraints(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TRIGGER_FOLDER:
				ShowSysTriggers(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_INDEX_FOLDER:
				ShowSysIndexes(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_PROCEDURE_FOLDER:
				ShowSysProcedures(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_FUNCTION_FOLDER:
				ShowSysFunctions(pItem);
				break;

			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_FOLDER:
				ShowUserTables(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_COLUMN_FOLDER:
				ShowUserColumns(pItem);
				break;

			case SHLDATACONNECTION_ID_TREE_DATA_USER_VIEW_FOLDER:
				ShowUserViews(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_SEQUENCE_FOLDER:
				ShowUserSequences(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_CONSTRAINT_FOLDER:
				ShowUserConstraints(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TRIGGER_FOLDER:
				ShowUserTriggers(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_INDEX_FOLDER:
				ShowUserIndexes(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_PROCEDURE_FOLDER:
				ShowUserProcedures(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_FUNCTION_FOLDER:
				ShowUserFunctions(pItem);
				break;

			/* ****************** SYSTEM ***************************/
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASES:
				ShowSysDatabases(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME:
				ShowSysElements(pItem);
				break;

			//TABLES & COLUMNS & KEYS & TIGGERS & INDEXES & SEQUENCES 
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE:
				ShowSysTableColumns(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_COLUMNS:
				ShowSysColumnsDetail(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_KEYS:
				ShowSysTablePrimeryKeys(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_CONSTRAINTS:
				ShowSysTableConstraints(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_TRIGGERS:
				ShowSysTableTriggers(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_INDEXES:
				ShowSysTableIndexes(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_SEQUENCES:
				ShowSysTableSequences(pItem);
				break;

			// VIEWS
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_VIEW:
				ShowSysView(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_VIEW_PARAMETERS:
				ShowSysViewParameters(pItem);
				break;

			// PROCEDURE
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_PROCEDURE:
				ShowSysProcedure(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_PROCEDURE_PARAMETERS:
				ShowSysProcedureParameters(pItem);
				break;

			// FUNCTION
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_FUNCTION:
				ShowSysFunction(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_FUNCTION_PARAMETERS:
				ShowSysFunctionParameters(pItem);
				break;

			/* *********************** USER ************************ */
			// DATABASE
			case SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASES:
				ShowUserDatabases(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME:
				ShowUserElements(pItem);
				break;

			//TABLES & COLUMNS & KEYS & TIGGERS & INDEXES & SEQUENCES 
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE:
				ShowUserTableColumns(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_COLUMNS:
				ShowUserColumnsDetail(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_KEYS:
				ShowUserTablePrimeryKeys(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_CONSTRAINTS:
				ShowUserTableConstraints(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_TRIGGERS:
				ShowUserTableTriggers(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_INDEXES:
				ShowUserTableIndexes(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_SEQUENCES:
				ShowUserTableSequences(pItem);
				break;

			// VIEWS
			case SHLDATACONNECTION_ID_TREE_DATA_USER_VIEW:
				ShowUserView(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_VIEW_PARAMETERS:
				ShowUserViewParameters(pItem);
				break;

			// PROCEDURE
			case SHLDATACONNECTION_ID_TREE_DATA_USER_PROCEDURE:
				ShowUserProcedure(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_PROCEDURE_PARAMETERS:
				ShowUserProcedureParameters(pItem);
				break;

			// FUNCTION
			case SHLDATACONNECTION_ID_TREE_DATA_USER_FUNCTION:
				ShowUserFunction(pItem);
				break;
			case SHLDATACONNECTION_ID_TREE_DATA_USER_FUNCTION_PARAMETERS:
				ShowUserFunctionParameters(pItem);
				break;

			default:
				AfxMessageBox(_T("No item selected <FillChildrenTreeViewItems>."));
				break;
		}
	}
	catch(...)
	{
		CString strMsg;
		DWORD err = GetLastError();

		strMsg.Format(_T("Erro: %i\r\n%s"), err, ErrorMessage(err));
		MessageBox(strMsg, _T("0x00017"));
	}
}

CQueryDataConnectionEntity* CServerExplorerView::GetDataConnection(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;

	try
	{
		for(UINT nIndex = 0; nIndex < m_dataconnection.GetItemCount(); nIndex++)
		{
			pDataConnection = m_dataconnection.GetItemAt(nIndex);
			if(pDataConnection->TreeViewItem == phItem)
				break;
			pDataConnection = NULL;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	return pDataConnection;
}

HTREEITEM CServerExplorerView::GetParentTreeItem(HTREEITEM phItem, SHLDATACONNECTION target, BOOL bUpDirection)
{
	HTREEITEM hItem = NULL;
	HTREEITEM hParent;

	try
	{
		hParent = phItem;
		if(bUpDirection)
		{
			do
			{
				if((SHLDATACONNECTION)m_wndServerView.GetItemData(hParent)  == target)
				{
					hItem = hParent;
					break;
				}
				else
					hParent = m_wndServerView.GetParentItem(hParent);

			} while(hItem == NULL && hParent != m_wndServerView.GetRootItem() && hParent != NULL);
		}
		else
		{
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	return hItem;
}

void CServerExplorerView::ConnectDatabaseServer(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strOriginalText;

	try
	{
		if(phItem == NULL)
			return;

		if(!IsValidItem(phItem))
			return;

		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Connecting...") );

		pDataConnection = GetDataConnection(phItem);

		if(pDataConnection->Connection->ConnectionState != SHLCONNECTIONSTATE::Commandstate_Closed)
			pDataConnection->Connection->Close();

		pDataConnection->Connection->ConnectionString = pDataConnection->ConnectionString;
		pDataConnection->Connection->Provider = SHLOLEDBPROVIDER::SHL_PROVIDER_CONNECTIONSTRING;
		if(!pDataConnection->Connection->Open())
		{
			AfxMessageBox(pDataConnection->Connection->ErrorMessage);
			FinalizeWaitCursor(phItem, strOriginalText);
			return;
		}

		m_ptrSHLQuery->LoadSelectQueries(pDataConnection);
		m_ptrSHLQuery->ConnectionDatabaseServer(m_wndServerView, pDataConnection);

		m_wndServerView.SetItemImage(phItem, IMAGE_DATA_CONNECTION_ON, IMAGE_DATA_CONNECTION_ON);
		m_wndServerView.SetItemState(phItem, TVIS_BOLD, TVIS_BOLD);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::RefreshDatabaseServer(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Refreshing...") );

		pDataConnection = GetDataConnection(phItem);

		m_ptrSHLQuery->ConnectionDatabaseServer(m_wndServerView, pDataConnection);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::DisconnectDatabaseServer(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	HTREEITEM hParentDataconnectoin;

	try
	{
		if(phItem == NULL)
			return;

		if(!IsValidItem(phItem))
			return;

		hParentDataconnectoin = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);

		pDataConnection = GetDataConnection(hParentDataconnectoin);

		if(pDataConnection->Connection->ConnectionState == SHLCONNECTIONSTATE::Commandstate_Closed)
			return;

		if(!pDataConnection->Connection->Close())
		{
			AfxMessageBox(pDataConnection->Connection->ErrorMessage);
			return;
		}

		if(!DeleteChildItemTreeView(hParentDataconnectoin))
		{
			AfxMessageBox(_T("Can´t remove children items."));
			return;

		}

		m_wndServerView.SetItemImage(phItem, IMAGE_DATA_CONNECTION, IMAGE_DATA_CONNECTION);
		m_wndServerView.SetItemState(phItem, 0, TVIS_BOLD);
		m_wndServerView.SetItemState(phItem, 0, TVIS_EXPANDED);
}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::ShowSysElements(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;

	HTREEITEM hItem = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);

		pDataConnection = GetDataConnection(hParent);

		if(!pDataConnection->SelectSysTables.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Tables"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectSysViews.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Views"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_VIEW_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectSysSequences.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Sequences"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_SEQUENCE_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectSysConstraints.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Constraints"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_CONSTRAINT_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectSysTriggers.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Triggers"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TRIGGER_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectSysIndexes.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Indexes"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_INDEX_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectSysProcedures.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Procedures"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_PROCEDURE_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectSysFunctions.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Functions"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_FUNCTION_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysDatabases(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);

		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectSysDatabases, _T(""), _T(""), _T(""), _T("DATABASENAME"), SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME, IMAGE_DATA_BASE, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysTables(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);

		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectSysTables, strDatabasename, _T(""), _T(""), _T("TABLENAME"), SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE, IMAGE_DATA_TABLE, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysColumns(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;
	CString strTablename;

	HTREEITEM hItem = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItem = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItem);

		hItem = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE);
		strTablename = m_wndServerView.GetItemText(hItem);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowSystemTableColumns(m_wndServerView, phItem, strDatabasename, strTablename, pDataConnection);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}
void CServerExplorerView::ShowSysViews(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectSysViews, strDatabasename, _T(""), _T(""), _T("VIEWNAME"), SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_VIEW, IMAGE_DATA_TABLE, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysSequences(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectSysSequences, strDatabasename, _T(""), _T(""), _T("SEQUENCENAME"), SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_SEQUENCES, IMAGE_DATA_SEQUENCE, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysConstraints(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectSysConstraints, strDatabasename, _T(""), _T(""), _T("CONSTRAINTNAME"), SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_CONSTRAINTS, IMAGE_DATA_CONSTRAINT, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysTriggers(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectSysTriggers, strDatabasename, _T(""), _T(""), _T("TRIGGERNAME"), SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_TRIGGERS, IMAGE_DATA_TRIGGER, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysIndexes(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectSysIndexes, strDatabasename, _T(""), _T(""), _T("INDEXNAME"), SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_INDEXES, IMAGE_DATA_INDEX, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysProcedures(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectSysProcedures, strDatabasename, _T(""), _T(""), _T("PROCEDURENAME"), SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_PROCEDURE, IMAGE_DATA_PROGRAMATICALLY, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysFunctions(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectSysFunctions, strDatabasename, _T(""), _T(""), _T("FUNCTIONNAME"), SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_FUNCTION, IMAGE_DATA_PROGRAMATICALLY, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysTableColumns(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		hParent = m_wndServerView.InsertItem(_T("Columns"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
		m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_COLUMN_FOLDER);
		m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);

		m_ptrSHLQuery->ShowSystemTableColumns(m_wndServerView, hParent, strDatabasename, strOriginalText, pDataConnection);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysColumnsDetail(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysTablePrimeryKeys(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysTableConstraints(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysTableTriggers(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysTableIndexes(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysTableSequences(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysView(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysViewParameters(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysProcedure(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysProcedureParameters(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysFunction(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowSysFunctionParameters(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserElements(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;

	HTREEITEM hItem = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);

		pDataConnection = GetDataConnection(hParent);

		if(!pDataConnection->SelectUserTables.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Tables"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectUserViews.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Views"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_USER_VIEW_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectUserSequences.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Sequences"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_USER_SEQUENCE_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectUserConstraints.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Constraints"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_USER_CONSTRAINT_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectUserTriggers.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Triggers"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_USER_TRIGGER_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectUserIndexes.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Indexes"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_USER_INDEX_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectUserProcedures.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Procedures"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_USER_PROCEDURE_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}

		if(!pDataConnection->SelectUserFunctions.IsEmpty())
		{
			hParent = m_wndServerView.InsertTreeItem(_T("Functions"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
			m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_USER_FUNCTION_FOLDER);
			m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserTables(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectUserTables, strDatabasename, _T(""), _T(""), _T("TABLENAME"), SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE, IMAGE_DATA_TABLE, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserColumns(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;
	CString strTablename;

	HTREEITEM hItem = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItem = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItem);

		hItem = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE);
		strTablename = m_wndServerView.GetItemText(hItem);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowUserTableColumns(m_wndServerView, phItem, strDatabasename, strTablename, pDataConnection);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserViews(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectUserViews, strDatabasename, _T(""), _T(""), _T("VIEWNAME"), SHLDATACONNECTION_ID_TREE_DATA_USER_VIEW, IMAGE_DATA_TABLE, m_wndServerView, phItem, pDataConnection, true);		
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserSequences(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectUserSequences, strDatabasename, _T(""), _T(""), _T("SEQUENCENAME"), SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_SEQUENCES, IMAGE_DATA_SEQUENCE, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserConstraints(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectUserConstraints, strDatabasename, _T(""), _T(""), _T("CONSTRAINTNAME"), SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_CONSTRAINTS, IMAGE_DATA_CONSTRAINT, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserTriggers(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectUserTriggers, strDatabasename, _T(""), _T(""), _T("TRIGGERNAME"), SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_TRIGGERS, IMAGE_DATA_TRIGGER, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserIndexes(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectUserIndexes, strDatabasename, _T(""), _T(""), _T("INDEXNAME"), SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_INDEXES, IMAGE_DATA_INDEX, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserProcedures(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectUserProcedures, strDatabasename, _T(""), _T(""), _T("PROCEDURENAME"), SHLDATACONNECTION_ID_TREE_DATA_USER_PROCEDURE, IMAGE_DATA_PROGRAMATICALLY, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserFunctions(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectUserFunctions, strDatabasename, _T(""), _T(""), _T("FUNCTIONNAME"), SHLDATACONNECTION_ID_TREE_DATA_USER_FUNCTION, IMAGE_DATA_PROGRAMATICALLY, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserDatabases(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);

		pDataConnection = GetDataConnection(hParent);

		m_ptrSHLQuery->ShowElements(pDataConnection->SelectUserDatabases, _T(""), _T(""), _T(""), _T("DATABASENAME"), SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME, IMAGE_DATA_BASE, m_wndServerView, phItem, pDataConnection, true);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserTableColumns(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

		hParent = m_wndServerView.InsertItem(_T("Columns"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, phItem);
		m_wndServerView.SetItemData(hParent, SHLDATACONNECTION_ID_TREE_DATA_USER_COLUMN_FOLDER);
		m_wndServerView.SetItemState(hParent, 0, TVIS_EXPANDPARTIAL);

		m_ptrSHLQuery->ShowUserTableColumns(m_wndServerView, hParent, strDatabasename, strOriginalText, pDataConnection);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserColumnsDetail(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserTablePrimeryKeys(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserTableConstraints(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserTableTriggers(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserTableIndexes(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserTableSequences(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserView(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserViewParameters(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserProcedure(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserProcedureParameters(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserFunction(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

void CServerExplorerView::ShowUserFunctionParameters(HTREEITEM phItem)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	CString strDatabasename;

	HTREEITEM hItemDatabase = NULL;
	HTREEITEM hParent = NULL;
	CString strOriginalText;

	try
	{
		if(m_wndServerView.GetChildItem(phItem) != NULL)
			return;

		strOriginalText = InitWaitCursor(phItem, _T("Expanding...") );

		hItemDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
		strDatabasename = m_wndServerView.GetItemText(hItemDatabase);

		hParent = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParent);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	FinalizeWaitCursor(phItem, strOriginalText);
}

bool CServerExplorerView::DeleteChildItemTreeView(HTREEITEM phItem)
{
	bool bResultado = TRUE;
	HTREEITEM hNextItem;
	HTREEITEM hChildItem;

	try
	{
		hChildItem = m_wndServerView.GetChildItem(phItem);
		
		while (hChildItem != NULL && bResultado)
		{
			if (m_wndServerView.ItemHasChildren(hChildItem))
				bResultado = DeleteChildItemTreeView(hChildItem);

			if (!bResultado)
				break;

			hNextItem = m_wndServerView.GetNextItem(hChildItem, TVGN_NEXT);
			bResultado = m_wndServerView.DeleteItem(hChildItem);
			hChildItem = hNextItem;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage);
	}
	catch(...)
	{
		MessageBox(ErrorMessage(::GetLastError()));
	}

	return bResultado;
}

void CServerExplorerView::RemoveConnection(HTREEITEM phItem)
{
	bool bResultado = TRUE;

	CString rootText;

	HTREEITEM hRoot;
	HTREEITEM hParentDatabase;

	CQueryDataConnectionEntity* pDataConnection = NULL;

	try
	{
		hRoot = m_wndServerView.GetRootItem();

		hParentDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParentDatabase);
		
		if(!DeleteChildItemTreeView(hParentDatabase))
		{
			AfxMessageBox(_T("Can´t remove this connection."));
			return;
		}

		DisconnectDatabaseServer(hParentDatabase);

		m_wndServerView.DeleteItem(hParentDatabase);

		if(pDataConnection->State == SHLQUERYDATACONNECTIONSTATE::SHLQUERYDATACONNECTIONSTATE_NEW)
		{
			UINT nIndex = 0;
			for(nIndex = 0; nIndex < m_dataconnection.GetItemCount(); nIndex++)
			{
				if(m_dataconnection.GetItemAt(nIndex)->TreeViewItem == hParentDatabase)
					break;

			}

			m_dataconnection.RemoveItemAt(nIndex);
		}
		else
		{
			pDataConnection->State = SHLQUERYDATACONNECTIONSTATE::SHLQUERYDATACONNECTIONSTATE_DELETE;
		}

		rootText = m_wndServerView.GetItemText(hRoot);
		rootText.Replace(_T("*"), _T(""));
		rootText += _T("*");
		m_wndServerView.SetItemText(hRoot, rootText);
		m_wndServerView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage);
	}
	catch(...)
	{
		MessageBox(ErrorMessage(::GetLastError()));
	}
}

void CServerExplorerView::Refresh(HTREEITEM phItem)
{
	HTREEITEM hRoot;
	HTREEITEM hParentDatabase;
	SHLDATACONNECTION nType;

	try
	{
		if(phItem == NULL)
			return;

		if(!IsValidItem(phItem))
			return;

		hRoot = m_wndServerView.GetRootItem();

		hParentDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);

		if(phItem == hRoot)
			return;

		nType = (SHLDATACONNECTION)m_wndServerView.GetItemData(phItem);
		
		DeleteChildItemTreeView(phItem);
		LoadDatabaseElementsByNode(nType, phItem, TRUE);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::ShowProperties(HTREEITEM phItem, BOOL showPane)
{
	SHLDATACONNECTION nType;

	try
	{
		if(phItem == NULL)
			return;

		if(!IsValidItem(phItem))
			return;

		nType = (SHLDATACONNECTION)m_wndServerView.GetItemData(phItem);

		switch(nType)
		{
			// ALL CASES
			case SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION:
				ShowPropertiesConnection(phItem, showPane);
				break;

			/* ****************** SYSTEM ***************************/
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME:
				ShowPropertiesConnection(phItem, showPane);
				//ShowPropertiesDatabase(phItem);
				break;

			//TABLES & COLUMNS & KEYS & TIGGERS & INDEXES & SEQUENCES 
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE:
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_COLUMNS:
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_KEYS:
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_CONSTRAINTS:
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_TRIGGERS:
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_INDEXES:
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_SEQUENCES:
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_VIEW:
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_VIEW_PARAMETERS:
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_PROCEDURE:
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_PROCEDURE_PARAMETERS:
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_FUNCTION:
			case SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_FUNCTION_PARAMETERS:
				ShowPropertiesConnection(phItem, showPane);
				//ShowSysPropertiesElements(phItem, nType);
				break;

			/* *********************** USER ************************ */
			// DATABASE
			case SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME:
				ShowPropertiesConnection(phItem, showPane);
				//ShowPropertiesDatabase(phItem);
				break;

			//TABLES & COLUMNS & KEYS & TIGGERS & INDEXES & SEQUENCES 
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE:
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_COLUMNS:
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_KEYS:
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_CONSTRAINTS:
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_TRIGGERS:
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_INDEXES:
			case SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_SEQUENCES:
			case SHLDATACONNECTION_ID_TREE_DATA_USER_VIEW:
			case SHLDATACONNECTION_ID_TREE_DATA_USER_VIEW_PARAMETERS:
			case SHLDATACONNECTION_ID_TREE_DATA_USER_PROCEDURE:
			case SHLDATACONNECTION_ID_TREE_DATA_USER_PROCEDURE_PARAMETERS:
			case SHLDATACONNECTION_ID_TREE_DATA_USER_FUNCTION:
			case SHLDATACONNECTION_ID_TREE_DATA_USER_FUNCTION_PARAMETERS:
				ShowPropertiesConnection(phItem, showPane);
				//ShowUserPropertiesElements(phItem, nType);
				break;

			default:
				break;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::ShowPropertiesConnection(HTREEITEM phItem, BOOL showPane)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	HTREEITEM hParentDatabase;
	CString nameSourceProperty;
	CString connectionName;

	try
	{
		hParentDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		pDataConnection = GetDataConnection(hParentDatabase);

		connectionName = m_wndServerView.GetItemText(hParentDatabase);

		nameSourceProperty.Format(_T("Connection: %s"), connectionName);

		m_wndproperties->NameSourceProperty = nameSourceProperty;
		m_wndproperties->DataConnection = pDataConnection;
		m_wndproperties->ShowConnectionProperties(showPane);

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::ShowPropertiesDatabase(HTREEITEM phItem, BOOL showPane)
{
	try
	{
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::ShowSysPropertiesElements(HTREEITEM phItem, SHLDATACONNECTION nType, BOOL showPane)
{
	try
	{
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::ShowUserPropertiesElements(HTREEITEM phItem, SHLDATACONNECTION nType, BOOL showPane)
{
	try
	{
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::NewQuery(HTREEITEM phItem)
{
	HTREEITEM hDatabaseItem;
	CQueryDataConnectionEntity* queryEntity = NULL;
	CString strDatabase;
	HTREEITEM hDatabase;

	try
	{
		hDatabaseItem = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		queryEntity = GetDataConnection(hDatabaseItem);

		hDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
		if(!hDatabase)
			hDatabase = GetParentTreeItem(phItem, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);

		if(hDatabase)
			strDatabase = m_wndServerView.GetItemText(hDatabase);

		NewQuery(queryEntity, strDatabase);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::Reset()
{
	try
	{
		if(m_ptrSHLQuery)
			delete m_ptrSHLQuery;

		m_dataconnection.RemoveAllItems();
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

CString CServerExplorerView::InitWaitCursor(HTREEITEM pItem, CString message)
{
	CString originalText;
	CString newText;

	try
	{
		BeginWaitCursor();

		originalText = m_wndServerView.GetItemText(pItem);
		newText.Format(_T("%s (%s)"), originalText, message);
		m_wndServerView.SetItemText(pItem, newText);

		DoEvents();
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}

	return originalText;
}

void CServerExplorerView::FinalizeWaitCursor(HTREEITEM pItem, CString originaltext)
{
	try
	{
		if(originaltext.IsEmpty())
			return;

		m_wndServerView.SetItemText(pItem, originaltext);

		EndWaitCursor();

		DoEvents();
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

BOOL CServerExplorerView::EnableConnect(HTREEITEM itemSelected)
{
	HTREEITEM hDatabaseItem;
	CQueryDataConnectionEntity* queryEntity = NULL;
	BOOL bRet = FALSE;

	try
	{
		if(itemSelected == NULL)
			return FALSE;

		hDatabaseItem = GetParentTreeItem(itemSelected, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		if(hDatabaseItem == NULL)
			return FALSE;

		queryEntity = GetDataConnection(hDatabaseItem);
		if(queryEntity == NULL)
			return FALSE;

		if(queryEntity->Connection->ConnectionState == SHLCONNECTIONSTATE::Commandstate_Closed)
			bRet = TRUE;
		else
			bRet = FALSE;
	}
	catch(...)
	{
	}

	return bRet;
}

BOOL CServerExplorerView::EnableDisconnect(HTREEITEM itemSelected)
{
	HTREEITEM hDatabaseItem;
	CQueryDataConnectionEntity* queryEntity = NULL;
	BOOL bRet = FALSE;

	try
	{
		if(itemSelected == NULL)
			return FALSE;

		hDatabaseItem = GetParentTreeItem(itemSelected, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		if(hDatabaseItem == NULL)
			return FALSE;

		queryEntity = GetDataConnection(hDatabaseItem);
		if(queryEntity == NULL)
			return FALSE;

		if(queryEntity->Connection->ConnectionState == SHLCONNECTIONSTATE::Commandstate_Closed)
			bRet = FALSE;
		else
			bRet = TRUE;
	}
	catch(...)
	{
	}

	return bRet;
}

BOOL CServerExplorerView::EnableRefresh(HTREEITEM itemSelected)
{
	CQueryDataConnectionEntity* pDataConnection = NULL;
	BOOL bRet = FALSE;
	HTREEITEM hParent = NULL;

	try
	{
		if(itemSelected == NULL)
			return FALSE;

		hParent = GetParentTreeItem(itemSelected, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
		if(hParent == NULL)
			return FALSE;

		pDataConnection = GetDataConnection(hParent);
		if(pDataConnection == NULL)
			return FALSE;

		if(pDataConnection->Connection->ConnectionState == SHLCONNECTIONSTATE::Commandstate_Closed)
			bRet = FALSE;
		else
			bRet = TRUE;
	}
	catch(...)
	{
	}

	return bRet;
}

HTREEITEM CServerExplorerView::ValidItem(HTREEITEM item)
{
	HTREEITEM itemReturn = NULL;
	TVITEMW tvitem;
	try
	{
		itemReturn = item;

		if(item == NULL)
			itemReturn = m_wndServerView.GetRootItem();

		if(!m_wndServerView.SelectItem(item))
			itemReturn = m_wndServerView.GetRootItem();
	}
	catch(...)
	{
	}

	return itemReturn;
}

BOOL CServerExplorerView::IsValidItem(HTREEITEM item)
{
	BOOL bRet = FALSE;

	try
	{
		bRet = m_wndServerView.SelectItem(item);
	}
	catch(...)
	{
	}

	return bRet;
}

void CServerExplorerView::EndLabelEdit(TV_DISPINFO* pTVDispInfo)
{
	DWORD nType;
	CString editName;
	HTREEITEM hParentDataconnectoin;
	CQueryDataConnectionEntity* pDataConnection = NULL;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		editName = pTVDispInfo->item.pszText;

		hParentDataconnectoin = GetParentTreeItem(m_hContextMenuItemselected, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);

		pDataConnection = GetDataConnection(hParentDataconnectoin);

		pDataConnection->ConnectionName = editName;
		pDataConnection->State = SHLQUERYDATACONNECTIONSTATE_UPDATE;
		m_wndServerView.SetItemText(m_hContextMenuItemselected, editName);

		SaveConnections();
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CServerExplorerView::RenameConnection()
{
	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		m_wndServerView.EditLabel(m_hContextMenuItemselected);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}
#pragma endregion REGION_PRIVATE_METHODS
