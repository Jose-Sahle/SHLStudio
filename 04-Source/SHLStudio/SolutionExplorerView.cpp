/* ***************************************************************************
 * Arquivo: SolutionExplorerView                                             *
 *                                                                           *
 * Classe treeview contendo as soluões, projetos, itens, etc.                *
 *                                                                           *
 * Data:26/03/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#include "stdafx.h"
#include "mainfrm.h"
#include "SolutionExplorerView.h"
#include "Resource.h"
#include "SHLStudio.h"
#include "ISHLStudioProject.h"
#include "Library.h"
#include "GUID.h"
#include "ChildFrm.h"
#include "SHLStudioDoc.h"
#include "DlgProjectAndFile.h"
#include "ConfigurationManager.h"
#include "ProjectWrapper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void  SendOutPutMessage(HWND hwndOutput, CString message);

/////////////////////////////////////////////////////////////////////////////
// CSolutionExplorerView

CSolutionExplorerView::CSolutionExplorerView()
{
	m_bEditLabelMode = FALSE;
	m_bLDragging = FALSE;
	m_hThreadStarter = NULL;

	m_buildnextproject		= TRUE;
	m_buildprojectresultok	= FALSE;
	m_stopbuild				= FALSE;

}

CSolutionExplorerView::~CSolutionExplorerView()
{
}

BEGIN_MESSAGE_MAP(CSolutionExplorerView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()

	ON_MESSAGE(WM_SETBUILDPROJECTRESULT, OnSetBuildProjectResult)
	ON_MESSAGE(WM_SETNEXTBUILDPROJECTRESULT, OnSetNextBuildProject)

	ON_NOTIFY(NM_CLICK, IDD_TREE_VIEW,  OnButtonDown)
	ON_NOTIFY(NM_DBLCLK, IDD_TREE_VIEW,  OnDBButtonDown)
	ON_NOTIFY(TVN_BEGINDRAG, IDD_TREE_VIEW, OnBeginDrag)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDD_TREE_VIEW, OnBeginLabelEdit)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDD_TREE_VIEW, OnEndLabelEdit)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()

	ON_COMMAND(ID_EDIT_PASTE, &CSolutionExplorerView::OnEditPaste)

	ON_COMMAND(ID_ADD_ADDNEWITEM, OnExplorerAddNew)
	ON_COMMAND(ID_ADD_ADDEXISTINGITEM, OnExplorerAddExisting)
	ON_COMMAND(ID_EXPLORER_ADDFOLDER, OnExplorerAddfolder)
	ON_COMMAND(ID_EXPLORER_BUILD, OnExplorerBuild)
	ON_COMMAND(ID_EXPLORER_GENERATE, OnExplorerGenerate)
	ON_COMMAND(ID_EXPLORER_CONFIGURATIONMANAGER, OnExplorerConfigurationManager)
	ON_COMMAND(ID_EXPLORER_OPENFOLDERINFILEEXPLORER, OnExplorerOpenFolderInExplorer)
	ON_COMMAND(ID_EXPLORER_RENAME, OnExplorerRename)
	ON_COMMAND(ID_EXPLORER_REMOVE, OnExplorerRemove)
	ON_COMMAND(ID_EXPLORER_CLOSE, OnExplorerClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers
//////////////////////////////////////////////////////////////////////////////////////////////
// 
//  E V E N T S 
//
//////////////////////////////////////////////////////////////////////////////////////////////
#pragma region Region_Events
int CSolutionExplorerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	InitVars();

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create view:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_EDITLABELS;

	if (!m_wndSolutionView.Create(dwViewStyle, rectDummy, this, IDD_TREE_VIEW))
	{
		TRACE0("Failed to create solution explorer\n");
		return -1;      // fail to create
	}

	// Load view images:
	m_SolutionViewImages.Create(IDB_SOLUTION_EXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, 0, IMAGEMASKSOLUTIONEXPLORER);
	m_wndSolutionView.SetImageList(&m_SolutionViewImages, TVSIL_NORMAL);
	int nCount = m_SolutionViewImages.GetImageCount();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();

	::SetWindowTheme(m_wndSolutionView.m_hWnd, L"Explorer", NULL);

	return 0;
}

BOOL CSolutionExplorerView::PreTranslateMessage(MSG* pMsg)
{
	if(m_bEditLabelMode && WM_KEYDOWN == pMsg->message && (VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
	{
		m_wndSolutionView.PostMessage(TVM_ENDEDITLABELNOW);

		return TRUE;
	}
	return CDockablePane::PreTranslateMessage(pMsg);
}

LRESULT CSolutionExplorerView::OnSetBuildProjectResult(WPARAM wParam, LPARAM lParam)
{
	m_buildprojectresultok = (BOOL)wParam;

	return 0;
}

LRESULT CSolutionExplorerView::OnSetNextBuildProject(WPARAM wParam, LPARAM lParam)
{
	m_buildnextproject = TRUE;

	return 0;
}

void CSolutionExplorerView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	AdjustLayout();
}

void CSolutionExplorerView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndSolutionView;
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

	ButtonDown(hTreeItem);
	ContextMenu(hTreeItem, point);
}

void CSolutionExplorerView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndSolutionView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CSolutionExplorerView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndSolutionView.SetFocus();
}

void CSolutionExplorerView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Locked */);

	m_SolutionViewImages.DeleteImageList();

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

	m_SolutionViewImages.Create(IMAGELISTSIZESOLUTIONEXPLORER, bmpObj.bmHeight, nFlags, 0, 0);
	m_SolutionViewImages.Add(&bmp, IMAGEMASKSOLUTIONEXPLORER);

	m_wndSolutionView.SetImageList(&m_SolutionViewImages, TVSIL_NORMAL);
}

void CSolutionExplorerView::OnProperties()
{
	ShowProperties();		
}

void CSolutionExplorerView::OnFileOpen()
{
	OpenFile();	
}

void CSolutionExplorerView::OnFileOpenWith()
{
	OpenFileWith();
}

void CSolutionExplorerView::OnEditCut()
{
	EditCut();
}

void CSolutionExplorerView::OnEditCopy()
{
	EditCopy();
}

void CSolutionExplorerView::OnEditClear()
{
	EditClear();
}

void CSolutionExplorerView::OnEditPaste()
{
	EditPaste();	
}

void CSolutionExplorerView::OnButtonDown(NMHDR* pNMHDR, LRESULT* pResult)
{
	HTREEITEM  item = GetItemSelected();

	m_hItemselected = item;

	ButtonDown(item);

	*pResult = 0;
}

void CSolutionExplorerView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bLDragging)
	{
		MouseMove(nFlags, point);
	}
	else 
	{
		CDockablePane::OnMouseMove(nFlags, point);
		m_wndSolutionView.SetCursorArr();
	}	
}

void CSolutionExplorerView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDockablePane::OnLButtonUp(nFlags, point);

	LeftButtonUp(nFlags, point);
}

void CSolutionExplorerView::OnDBButtonDown(NMHDR* pNMHDR, LRESULT* pResult)
{
	HTREEITEM  item = GetItemSelected();

	DoubleClickDown(item);

	*pResult = 0;
}

void CSolutionExplorerView::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	BeginDrag(pNMTreeView);	

	*pResult = 0;
}

void CSolutionExplorerView::OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_bEditLabelMode = TRUE;

	*pResult = 0;
}

void CSolutionExplorerView::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	m_bEditLabelMode = FALSE;

	EndLabelEdit(pTVDispInfo);	

	*pResult = 0;
}

void CSolutionExplorerView::OnExplorerAddNew()
{
	AddNew();	
}

void CSolutionExplorerView::OnExplorerAddExisting()
{
	AddExisting();	
}

void CSolutionExplorerView::OnExplorerAddfolder()
{
	AddFolder();
}

void CSolutionExplorerView::OnExplorerBuild()
{
	Build();
}

void CSolutionExplorerView::OnExplorerGenerate()
{
	Generate();
}

void CSolutionExplorerView::OnExplorerConfigurationManager()
{
	ConfigurationManager();
}


void CSolutionExplorerView::OnExplorerOpenFolderInExplorer()
{
	OpenFolderInFileExplorer();
}

void CSolutionExplorerView::OnExplorerRename()
{
	Rename();	
}

void CSolutionExplorerView::OnExplorerRemove()
{
	Remove();	
}

void CSolutionExplorerView::OnExplorerClose()
{
	CloseSolution();	
}
#pragma endregion Region_Events

//////////////////////////////////////////////////////////////////////////////////////////////
// 
//  P R I V A T E   M E T H O D S 
//
//////////////////////////////////////////////////////////////////////////////////////////////
#pragma region REGION_PRIVATE_METHODS
void CSolutionExplorerView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndSolutionView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CSolutionExplorerView::InitVars()
{
	m_hItemselected = NULL;
	m_hContextMenuItemselected = NULL;
}

void CSolutionExplorerView::ContextMenu(HTREEITEM itemSelected, CPoint& point)
{
	DWORD nType;

	m_wndSolutionView.SetFocus();
	
	try
	{
		if(itemSelected == NULL)
			return;

		m_hContextMenuItemselected = itemSelected;
		nType = m_wndSolutionView.GetItemData(itemSelected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:				
				theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER_SOLUTION, point.x, point.y, this, TRUE);
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER_PROJECT, point.x, point.y, this, TRUE);
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER_FOLDER, point.x, point.y, this, TRUE);
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER_ITEM, point.x, point.y, this, TRUE);
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
				theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER_DEPENDENCY, point.x, point.y, this, TRUE);
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

HTREEITEM CSolutionExplorerView::MoveChildItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{

	TV_INSERTSTRUCT tvstruct;
	HTREEITEM hNewItem;
	HTREEITEM hNewDependencyItem;

	CString sText;
	CItemEntity* Item;
	CProjectEntity* project;
	CFolderEntity* folder;
	CItemEntity* dependency;
	CProjectWrapper pw;

	Item = pw.GetItem(m_solution, hItem);

	project = (CProjectEntity*)Item->Project;

	if(project->TreeNode == htiNewParent)
		Item->FolderID = _T("");
	else
	{
		folder = pw.GetFolder(m_solution, htiNewParent);
		Item->FolderID = folder->ID;
	}

	// get information of the source item
	tvstruct.item.hItem = hItem;
	tvstruct.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	m_wndSolutionView.GetItem(&tvstruct.item);  
	sText = m_wndSolutionView.GetItemText( hItem );
        
	tvstruct.item.cchTextMax = sText.GetLength();
	tvstruct.item.pszText = sText.LockBuffer();

	//insert the item at proper location
	tvstruct.hParent = htiNewParent;
	tvstruct.hInsertAfter = htiAfter;
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	hNewItem = m_wndSolutionView.InsertItem(&tvstruct);
	sText.ReleaseBuffer();

	//now copy item data and item state.
	m_wndSolutionView.SetItemData(hNewItem, m_wndSolutionView.GetItemData(hItem));
	m_wndSolutionView.SetItemState(hNewItem, m_wndSolutionView.GetItemState(hItem,TVIS_STATEIMAGEMASK),TVIS_STATEIMAGEMASK);

	Item->TreeNode = hNewItem;

	if(Item->Dependencies->GetItemCount())
	{					
		for(UINT nIndexDependency = 0; nIndexDependency < Item->Dependencies->GetItemCount(); nIndexDependency++)
		{
			dependency = Item->Dependencies->GetItemAt(nIndexDependency);

			// get information of the source item
			tvstruct.item.hItem = dependency->TreeNode;
			tvstruct.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
			m_wndSolutionView.GetItem(&tvstruct.item);  
			sText = m_wndSolutionView.GetItemText( dependency->TreeNode );
        
			tvstruct.item.cchTextMax = sText.GetLength();
			tvstruct.item.pszText = sText.LockBuffer();

			//insert the item at proper location
			tvstruct.hParent = hNewItem;
			tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
			hNewDependencyItem = m_wndSolutionView.InsertItem(&tvstruct);
			sText.ReleaseBuffer();

			//now copy item data and item state.
			m_wndSolutionView.SetItemData(hNewDependencyItem, m_wndSolutionView.GetItemData(dependency->TreeNode));

			m_wndSolutionView.SetItemState(hNewDependencyItem, m_wndSolutionView.GetItemState(dependency->TreeNode, TVIS_STATEIMAGEMASK),TVIS_STATEIMAGEMASK);

			dependency->TreeNode = hNewDependencyItem;
		}
	}

	//now delete the old item
	m_wndSolutionView.DeleteItem(hItem);

	return hNewItem;
}

void CSolutionExplorerView::BeginDrag(NM_TREEVIEW* pNMTreeView)
{
	DWORD nType;

	try
	{
		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
			case ID_TREE_VIEW_TAB_PROJECT:
			case ID_TREE_VIEW_TAB_FOLDER:
			case ID_TREE_VIEW_TAB_DEPENDENCY:
				break;
			case ID_TREE_VIEW_TAB_ITEM:
				m_hitemDrag = pNMTreeView->itemNew.hItem;
				m_hitemDrop = NULL;

				m_pDragImage = m_wndSolutionView.CreateDragImage(m_hitemDrag);

				if( !m_pDragImage )
					break;

				m_bLDragging = TRUE;

				m_pDragImage->BeginDrag(0, CPoint(-15,-15));

				POINT pt = pNMTreeView->ptDrag;
				ClientToScreen( &pt );

				m_pDragImage->DragEnter(NULL, pt);

				SetCapture();

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

void CSolutionExplorerView::ButtonDown(HTREEITEM itemSelected)
{
	DWORD nType;

	try
	{
		if(itemSelected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(itemSelected);

		m_hContextMenuItemselected = itemSelected;

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				ShowSolutionPropertiesView(FALSE, FALSE);
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				ShowProjectPropertiesView(FALSE, FALSE);
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				ShowFolderPropertiesView(FALSE, FALSE);
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				ShowItemPropertiesView(FALSE, FALSE);
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
				ShowItemPropertiesView(FALSE, FALSE);
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

void CSolutionExplorerView::MouseMove(UINT nFlags, CPoint point)
{
	HTREEITEM	hitem;
	UINT		flags;
	DWORD		nType;

	try
	{
		POINT pt = point;
		ClientToScreen( &pt );
		CImageList::DragMove(pt);

		if ((hitem = m_wndSolutionView.HitTest(point, &flags)) != NULL)
		{
			CImageList::DragShowNolock(FALSE);

			nType = m_wndSolutionView.GetItemData(hitem);

			switch(nType)
			{
				case ID_TREE_VIEW_TAB_SOLUTION:
				case ID_TREE_VIEW_TAB_DEPENDENCY:
					if(m_wndSolutionView.GetCursorNo() != ::GetCursor())
					{
						m_wndSolutionView.SetCursorNo();
						m_wndSolutionView.SelectDropTarget(NULL);
					}
					break;
				case ID_TREE_VIEW_TAB_PROJECT:
				case ID_TREE_VIEW_TAB_FOLDER:
				case ID_TREE_VIEW_TAB_ITEM:
					if(m_wndSolutionView.GetParentItem(m_hitemDrag) != hitem)
					{
						if (m_wndSolutionView.GetCursorArr() != ::GetCursor()) 
							m_wndSolutionView.SetCursorArr();

						m_wndSolutionView.SelectDropTarget(hitem);
					}
					break;
			}

			m_hitemDrop = hitem;
			CImageList::DragShowNolock(TRUE);
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

void CSolutionExplorerView::LeftButtonUp(UINT nFlags, CPoint point)
{
	DWORD nType;
	HTREEITEM	hitem;
	HTREEITEM htiParent;
	HTREEITEM htiNew;

	try
	{
		if (m_bLDragging)
		{
			m_bLDragging = FALSE;

			CImageList::DragLeave(&m_wndSolutionView);
			CImageList::EndDrag();

			m_wndSolutionView.ReleaseCapt();

			if(m_pDragImage != NULL) 
			{ 
				delete m_pDragImage; 
				m_pDragImage = NULL; 
			} 

			// Remove drop target highlighting
			m_wndSolutionView.SelectDropTarget(NULL);

			if( m_hitemDrag == m_hitemDrop )
				return;

			// Make sure pt is over some item
			if ( ((hitem = m_wndSolutionView.HitTest(point, &nFlags)) == NULL)  ) 
				return ;

			// Make sure dropped item isnt a child
			//if (m_wndSolutionView.GetParentItem(hitem) != NULL) 
			//	return ;

			nType = m_wndSolutionView.GetItemData(m_hitemDrop);
			switch(nType)
			{
				case ID_TREE_VIEW_TAB_SOLUTION:
					return;
				case ID_TREE_VIEW_TAB_PROJECT:
				case ID_TREE_VIEW_TAB_FOLDER:
					break;
				case ID_TREE_VIEW_TAB_ITEM:
					m_hitemDrop = m_wndSolutionView.GetParentItem( m_hitemDrop );
					break;
				case ID_TREE_VIEW_TAB_DEPENDENCY:
					return;
			}

			// If Drag item is an ancestor of Drop item then return
			htiParent = m_hitemDrop;
			while( (htiParent = m_wndSolutionView.GetParentItem( htiParent )) != NULL )
			{
				if( htiParent == m_hitemDrag ) 
					return;
			}

			m_wndSolutionView.Expand( m_hitemDrop, TVE_EXPAND ) ;

			htiNew = MoveChildItem( m_hitemDrag, m_hitemDrop, TVI_LAST );

			m_hItemselected = htiNew;

			m_wndSolutionView.DeleteItem(m_hitemDrag);
			m_wndSolutionView.SelectItem( htiNew );

			SaveProject(htiNew);
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
void CSolutionExplorerView::DoubleClickDown(HTREEITEM itemSelected)
{
	DWORD nType;

	try
	{
		if(itemSelected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(itemSelected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				m_hContextMenuItemselected = itemSelected;
				ShowProjectPropertiesView(TRUE, TRUE);
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				m_hContextMenuItemselected = itemSelected;
				ShowItemDependencyFiles();
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
				m_hContextMenuItemselected = itemSelected;
				ShowItemDependencyFiles();
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

HTREEITEM CSolutionExplorerView::GetItemSelected()
{
	CPoint cursorPos;
	CPoint cursorPosCliente;
	UINT uFlags;
	HTREEITEM		hItem;

	try
	{
		cursorPos.x= GetCurrentMessage()->pt.x;
		cursorPos.y= GetCurrentMessage()->pt.y;

		cursorPosCliente.x= GetCurrentMessage()->pt.x;
		cursorPosCliente.y= GetCurrentMessage()->pt.y;

		m_wndSolutionView.ScreenToClient(&cursorPosCliente);
		hItem = m_wndSolutionView.HitTest(cursorPosCliente, &uFlags);
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

void CSolutionExplorerView::ShowProperties()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				ShowSolutionPropertiesView(TRUE, TRUE);
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				ShowProjectPropertiesView(TRUE, TRUE);
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				ShowFolderPropertiesView(TRUE, TRUE);
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				ShowItemPropertiesView(TRUE, TRUE);
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
				ShowItemPropertiesView(TRUE, TRUE);
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

void CSolutionExplorerView::ShowSolutionPropertiesView(BOOL bComplete, BOOL showPane)
{
	try
	{		
		m_wndproperties->SolutionEntity = m_solution;
		m_wndproperties->NameSourceProperty = _T("Solution: ") + m_solution->Name;
		m_wndproperties->ShowSolutionProperties(showPane);
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

void CSolutionExplorerView::ShowProjectPropertiesView(BOOL bComplete, BOOL showPane)
{
	CProjectEntity* Project;
	CString strDLLName;

	SHLSTUDIOPROJECTHANDLE ptrSHLStudioProject = NULL;
	HMODULE hmod = NULL;
	LPFNGETSHLSTUDIOPROJECTINSTANCE pGetSHLStudioProjectInstance;

	CRuntimeClass* pNewViewClass = NULL;
	CRuntimeClass* pNewDocClass = NULL;
	CRuntimeClass* pNewFrameClass = NULL;
	CDocument* pDoc = NULL;

	CMultiDocTemplate* pDocTemplate = NULL;

	CString strKeyMultiDocTemplate;
	CString strTitle;
	CProjectWrapper pw;

	SHLSTUDIOARGLIST Arguments;

	try
	{
		if(!bComplete)
		{
			m_wndproperties->ClearAndHide();
			return;
		}

		Project = pw.GetProject(m_solution, m_hContextMenuItemselected);	

		strDLLName = Project->ClassDll;
		strKeyMultiDocTemplate.Format(_T("%s_%s"), strDLLName, Project->Type);

		theApp.LoadedLibraryList.Lookup(strDLLName, hmod);

		if(hmod == NULL)
		{
			hmod = ::LoadLibraryFromApplicationDirectory(strDLLName, _T("plugins"));

			if(!hmod)
				throw -1;

			theApp.LoadedLibraryList[strDLLName] = hmod;
		}

		pGetSHLStudioProjectInstance = (LPFNGETSHLSTUDIOPROJECTINSTANCE)::GetProcAddress(hmod, "GetSHLStudioProjectInstance");

		ptrSHLStudioProject = (SHLSTUDIOPROJECTHANDLE)pGetSHLStudioProjectInstance();

		theApp.MultiDocTemplateList.Lookup(strKeyMultiDocTemplate, pDocTemplate);

		if(pDocTemplate == NULL)
		{
			ptrSHLStudioProject->GetDocumentTemplate(SHLSTUDIOMETHODS_LOADPROJECTPROPERTIES, NULL, m_solution, Project, NULL, pNewFrameClass, pNewViewClass, pNewDocClass);

			pDocTemplate = new CMultiDocTemplate(IDR_SHLStudioTYPE,
				pNewDocClass,
				pNewFrameClass, // custom MDI child frame
				pNewViewClass);

			if (!pDocTemplate)
				return;

			theApp.MultiDocTemplateList[strKeyMultiDocTemplate] = pDocTemplate;
			theApp.AddDocTemplate(pDocTemplate);
		}

		pDoc = (CDocument*)pDocTemplate->OpenDocumentFile(NULL);		

		Arguments.AddItem(Project);
		Arguments.AddItem(pDoc);
		ptrSHLStudioProject->RunMethods(SHLSTUDIOMETHODS_SETPROJECTROPERTIES, &Arguments);
		Arguments.RemoveAllItems(false);

		pDoc->OnOpenDocument(NULL);
		pDoc->UpdateAllViews(NULL, NULL, NULL);
		pDoc->UpdateFrameCounts();
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"), MB_OK | MB_ICONERROR);
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
	}
}

void CSolutionExplorerView::ShowFolderPropertiesView(BOOL bComplete, BOOL showPane)
{
	try
	{
		m_wndproperties->ClearAndHide();
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

void CSolutionExplorerView::ShowItemPropertiesView(BOOL bComplete, BOOL showPane)
{
	CProjectEntity* Project;
	CItemEntity* Item;
	CString strDLLName;

	ISHLStudioProject* ptrSHLStudioProject = NULL;
	HMODULE hmod = NULL;
	LPFNGETSHLSTUDIOPROJECTINSTANCE pGetSHLStudioProjectInstance;

	CString strKeyMultiDocTemplate;
	CString strTitle;
	CProjectWrapper pw;

	try
	{
		Item = pw.GetItem(m_solution, m_hContextMenuItemselected);	
		Project = (CProjectEntity*)Item->Project;

		strDLLName = Project->ClassDll;
		strKeyMultiDocTemplate.Format(_T("%s_%s"), strDLLName, Project->Type);
		
		theApp.LoadedLibraryList.Lookup(strDLLName, hmod);

		if(hmod == NULL)
		{
			hmod = ::LoadLibraryFromApplicationDirectory(strDLLName, _T("plugins"));

			if (!hmod)
			{
				DWORD dwError = GetLastError();
				throw dwError;
			}
				
			theApp.LoadedLibraryList[strDLLName] = hmod;
		}

		pGetSHLStudioProjectInstance = (LPFNGETSHLSTUDIOPROJECTINSTANCE)::GetProcAddress(hmod, "GetSHLStudioProjectInstance");		

		ptrSHLStudioProject = (SHLSTUDIOPROJECTHANDLE)pGetSHLStudioProjectInstance();

		m_wndproperties->SHLStudioProject = ptrSHLStudioProject;
		m_wndproperties->ProjectEntity = Project;
		m_wndproperties->ItemEntity = Item;
		m_wndproperties->NameSourceProperty = _T("Item: ") + Item->Name;
		m_wndproperties->ShowProperties(showPane);
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

void CSolutionExplorerView::ShowItemDependencyFiles()
{
	CProjectEntity* Project;
	CItemEntity* Item;
	
	CString strDLLName;

	ISHLStudioProject* ptrSHLStudioProject = NULL;
	HMODULE hmod = NULL;
	LPFNGETSHLSTUDIOPROJECTINSTANCE pGetSHLStudioProjectInstance;

	CRuntimeClass* pNewViewClass = NULL;
	CRuntimeClass* pNewDocClass = NULL;
	CRuntimeClass* pNewChildFrame = NULL;
	CDocument* pDoc = NULL;

	CMultiDocTemplate* pDocTemplate = NULL;

	CString strKeyMultiDocTemplate;
	CString strFullFileName;
	CPath path;
	CProjectWrapper pw;

	SHLSTUDIOARGLIST Arguments;
	BOOL bValue = FALSE;

	try
	{
		Item = pw.GetItem(m_solution, m_hContextMenuItemselected);	
		Project = (CProjectEntity*)Item->Project;

		path.AddPath(2, Item->Path, Item->FileName);
		strFullFileName = path.GetPath();
		
		strDLLName = Project->ClassDll;
		strKeyMultiDocTemplate.Format(_T("%s_%s_SHOWITEM"), strDLLName, Item->Type);

		theApp.LoadedLibraryList.Lookup(strDLLName, hmod);

		if(hmod == NULL)
		{
			hmod = ::LoadLibraryFromApplicationDirectory(strDLLName, _T("plugins"));

			if(!hmod)
				throw -1;

			theApp.LoadedLibraryList[strDLLName] = hmod;
		}

		pGetSHLStudioProjectInstance = (LPFNGETSHLSTUDIOPROJECTINSTANCE)::GetProcAddress(hmod, "GetSHLStudioProjectInstance");

		ptrSHLStudioProject = (SHLSTUDIOPROJECTHANDLE)pGetSHLStudioProjectInstance();

		theApp.MultiDocTemplateList.Lookup(strKeyMultiDocTemplate, pDocTemplate);

		ptrSHLStudioProject->GetDocumentTemplate(SHLSTUDIOMETHODS_LOADEDITITEM, NULL, m_solution, Project, Item, pNewChildFrame, pNewViewClass, pNewDocClass);

		if(pDocTemplate == NULL)
		{
			pDocTemplate = new CMultiDocTemplate(IDR_SHLStudioTYPE,
				pNewDocClass,
				pNewChildFrame, // custom MDI child frame
				pNewViewClass);

			if (!pDocTemplate)
				return;

			theApp.MultiDocTemplateList[strKeyMultiDocTemplate] = pDocTemplate;
			theApp.AddDocTemplate(pDocTemplate);
		}

		for( POSITION pos = pDocTemplate->GetFirstDocPosition(); pos != NULL; )
		{
			CDocument* pDoc = pDocTemplate->GetNextDoc( pos );

			CString strTitle = pDoc->GetTitle();
			CString itemName = Item->FileName;

			if(strTitle.Trim() == itemName.Trim())
			{
				Arguments.AddItem(Project);
				Arguments.AddItem(Item);
				Arguments.AddItem(pDoc);
				Arguments.AddItem(&bValue);
				ptrSHLStudioProject->RunMethods(SHLSTUDIOMETHODS_SETITEMPROPERTIES, &Arguments);
				Arguments.RemoveAllItems(false);
				return;
			}
		}		

		HWND output = m_wndOutput->GetSafeHwnd();
		pDoc = (CDocument*)pDocTemplate->OpenDocumentFile(NULL);
		pDoc->OnOpenDocument(strFullFileName);
		pDoc->UpdateAllViews(NULL, NULL, NULL);
		pDoc->UpdateFrameCounts();
		pDoc->SetPathName(strFullFileName, TRUE);
		bValue = TRUE;
		Arguments.AddItem(Project);
		Arguments.AddItem(Item);
		Arguments.AddItem(pDoc);
		Arguments.AddItem(&bValue);
		Arguments.AddItem(&output);
		ptrSHLStudioProject->RunMethods(SHLSTUDIOMETHODS_SETITEMPROPERTIES, &Arguments);
		Arguments.RemoveAllItems(false);
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

void CSolutionExplorerView::OpenFolderInFileExplorerSolution()
{
	CString folder;

	try
	{
		folder = m_solution->Path;

		ExecutaPrograma(_T("Explorer"), folder);
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

void CSolutionExplorerView::OpenFolderInFileExplorerProject()
{
	CString folder;
	CProjectEntity* Project;
	CProjectWrapper pw;

	try
	{
		Project = pw.GetProject(m_solution, m_hContextMenuItemselected);

		folder = Project->Path;

		ExecutaPrograma(_T("Explorer"), folder);
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

void CSolutionExplorerView::OpenFolderInFileExplorerItem()
{
	CString folder;
	CItemEntity* Item;
	CProjectWrapper pw;

	try
	{
		Item = pw.GetItem(m_solution, m_hContextMenuItemselected);

		folder = Item->Path;

		ExecutaPrograma(_T("Explorer"), folder);
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

void CSolutionExplorerView::OpenFile()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				ShowItemDependencyFiles();
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
				ShowItemDependencyFiles();
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

void CSolutionExplorerView::OpenFileWith()
{
	DWORD nType;

	try
	{
		if( m_hContextMenuItemselected ==  NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
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

void CSolutionExplorerView::EditCut()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
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

void CSolutionExplorerView::EditCopy()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
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

void CSolutionExplorerView::EditClear()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
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

void CSolutionExplorerView::EditPaste()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected  == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
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

void CSolutionExplorerView::AddNew()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				AddNewProject();
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				AddNewItemFromProject(m_hContextMenuItemselected);
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				AddNewItemFromFolder(m_hContextMenuItemselected);
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				AddNewDependency(m_hContextMenuItemselected);
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
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

void CSolutionExplorerView::AddExisting()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				AddExistingProject();
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				AddExistingItemFromProject(m_hContextMenuItemselected);
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				AddExistingItemFromFolder(m_hContextMenuItemselected);
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				AddExistingDependency(m_hContextMenuItemselected);
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
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

void CSolutionExplorerView::AddNewSolution()
{
	CDlgProjectAndFile dlgProjectAndFile;
	CProjectEntity *ProjectAdd;
	INT_PTR nRet = -1;
	CPath path;
	HTREEITEM hItemSolution;

	try
	{
		path.AddPath(2, GetApplicationDirectory(), _T("Projects"));
		dlgProjectAndFile.TargetPath = path.GetPath();
		dlgProjectAndFile.ProjectType = _T("");
		dlgProjectAndFile.DialogType = SHLTYPEDLGPROJECTANDFILE_PROJECT;
		dlgProjectAndFile.ImageList = &m_SolutionViewImages;
		dlgProjectAndFile.MapIcons = &m_mapIcons;

		nRet = dlgProjectAndFile.DoModal();

		if(nRet == IDOK)
		{
			ProjectAdd = dlgProjectAndFile.Project;

			path.AddPath(2, ProjectAdd->Path, _T(""));

			if(!path.ExistLocation())
			{
				path.CreateDirectory();
			}

			m_solution->Name = ProjectAdd->Name;
			m_solution->Version = _T("1.0.0.0");
			m_solution->Description =_T("");
			m_solution->Path = path.GetPath();
			m_solution->FileName = ProjectAdd->Name + _T(".jsl");

			SaveSolution();

			hItemSolution = m_wndSolutionView.InsertItem(m_solution->Name, 0, 0, NULL);
			m_wndSolutionView.SetItemData(hItemSolution, ID_TREE_VIEW_TAB_SOLUTION);

			AddNewProject(ProjectAdd, dlgProjectAndFile.TargetPath);
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

void CSolutionExplorerView::AddExistingProject()
{
	CString strProjectFullName;
	CString strDefualt;
	CString strFilter;
	CString strFileName;
	CProjectWrapper prjWrapper;
	CProjectEntity* Project = NULL;
	HTREEITEM hSolutonItem;

	try
	{
		strFileName = _T("");
		strFilter = _T("SHLStudio Projects (*.pjp) |*.jpj | All files (*.*)||");
		strDefualt = _T("*.jpj");
		strProjectFullName = prjWrapper.SelectFile(strFileName, strDefualt, strFilter);

		if(strProjectFullName != _T(""))
		{
			hSolutonItem = m_wndSolutionView.GetRootItem();
			Project = prjWrapper.LoadProject(m_solution, strProjectFullName);

			prjWrapper.AddProjectItems(Project, m_wndSolutionView, hSolutonItem, m_mapIcons, m_SolutionViewImages);

			m_solution->Projects->AddItem(Project);

			prjWrapper.SaveSolution(m_solution, false);
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));

		if(Project)
			delete Project;

	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		MessageBox(szMessage, _T("Critical Error"));
		if(Project)
			delete Project;
	}
}

void CSolutionExplorerView::AddNewProject()
{
	CDlgProjectAndFile dlgProjectAndFile;
	CProjectEntity *ProjectAdd;
	INT_PTR nRet = -1;

	try
	{
		dlgProjectAndFile.TargetPath = m_solution->Path;
		dlgProjectAndFile.ProjectType = _T("");
		dlgProjectAndFile.DialogType = SHLTYPEDLGPROJECTANDFILE_PROJECT;
		dlgProjectAndFile.ImageList = &m_SolutionViewImages;
		dlgProjectAndFile.MapIcons = &m_mapIcons;

		nRet = dlgProjectAndFile.DoModal();

		if(nRet == IDOK)
		{
			ProjectAdd = dlgProjectAndFile.Project;

			AddNewProject(ProjectAdd, dlgProjectAndFile.TargetPath);
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

void CSolutionExplorerView::AddNewItemFromProject(HTREEITEM hItemselected)
{
	CDlgProjectAndFile dlgProjectAndFile;
	CItemEntity *ItemAdd;
	CProjectEntity *Project;
	INT_PTR nRet = -1;
	CProjectWrapper pw;

	try
	{
		Project = pw.GetProject(m_solution, hItemselected);

		dlgProjectAndFile.TargetPath = Project->Path;
		dlgProjectAndFile.ProjectType = Project->Type;
		dlgProjectAndFile.DialogType = SHLTYPEDLGPROJECTANDFILE_ITEM;
		dlgProjectAndFile.ImageList = &m_SolutionViewImages;
		dlgProjectAndFile.MapIcons = &m_mapIcons;

		nRet = dlgProjectAndFile.DoModal();

		if(nRet == IDOK)
		{
			ItemAdd = dlgProjectAndFile.Item;

			AddNewItem(Project, ItemAdd, _T(""), dlgProjectAndFile.TargetPath, hItemselected);
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

void CSolutionExplorerView::AddExistingItemFromProject(HTREEITEM hItemselected)
{
	CProjectEntity *Project;
	CString strDLLName;
	CProjectWrapper pw;

	ISHLStudioProject* ptrSHLStudioProject = NULL;
	HMODULE hmod = NULL;
	LPFNGETSHLSTUDIOPROJECTINSTANCE pGetSHLStudioProjectInstance;

	SHLSTUDIOARGLIST Arguments;

	try
	{
		Project = pw.GetProject(m_solution, hItemselected);

		strDLLName = Project->ClassDll;

		theApp.LoadedLibraryList.Lookup(strDLLName, hmod);

		if(hmod == NULL)
		{
			hmod = ::LoadLibraryFromApplicationDirectory(strDLLName, _T("plugins"));

			if(!hmod)
				throw -1;

			theApp.LoadedLibraryList[strDLLName] = hmod;
		}

		pGetSHLStudioProjectInstance = (LPFNGETSHLSTUDIOPROJECTINSTANCE)::GetProcAddress(hmod, "GetSHLStudioProjectInstance");

		ptrSHLStudioProject = (SHLSTUDIOPROJECTHANDLE)pGetSHLStudioProjectInstance();
		Arguments.AddItem(Project);
		Arguments.AddItem(&m_wndSolutionView);
		Arguments.AddItem(&m_mapIcons);
		Arguments.AddItem(&m_SolutionViewImages);
		ptrSHLStudioProject->RunMethods(SHLSTUDIOMETHODS_ADDEXISTINGITEMFROMPROJECT, &Arguments);

		pw.SaveProject(Project);
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

	Arguments.RemoveAllItems(false);
}

void CSolutionExplorerView::AddNewItemFromFolder(HTREEITEM hItemselected)
{
	CDlgProjectAndFile dlgProjectAndFile;
	CItemEntity *ItemAdd;
	CFolderEntity* folder;
	CProjectEntity *Project;
	INT_PTR nRet = -1;
	CProjectWrapper pw;

	try
	{
		Project = pw.GetProject(m_solution, hItemselected);
		folder = pw.GetFolder(m_solution, hItemselected);

		dlgProjectAndFile.TargetPath = Project->Path;
		dlgProjectAndFile.ProjectType = Project->Type;
		dlgProjectAndFile.DialogType = SHLTYPEDLGPROJECTANDFILE_ITEM;
		dlgProjectAndFile.ImageList = &m_SolutionViewImages;
		dlgProjectAndFile.MapIcons = &m_mapIcons;

		nRet = dlgProjectAndFile.DoModal();

		if(nRet == IDOK)
		{
			ItemAdd = dlgProjectAndFile.Item;

			AddNewItem(Project, ItemAdd, folder->ID, dlgProjectAndFile.TargetPath, hItemselected);
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

void CSolutionExplorerView::AddExistingItemFromFolder(HTREEITEM hItemselected)
{
	CFolderEntity* folder;
	CProjectEntity *Project;
	CString strDLLName;
	CProjectWrapper pw;

	ISHLStudioProject* ptrSHLStudioProject = NULL;
	HMODULE hmod = NULL;
	LPFNGETSHLSTUDIOPROJECTINSTANCE pGetSHLStudioProjectInstance;

	SHLSTUDIOARGLIST Arguments;

	try
	{
		Project = pw.GetProject(m_solution, hItemselected);
		folder = pw.GetFolder(m_solution, hItemselected);

		strDLLName = Project->ClassDll;

		theApp.LoadedLibraryList.Lookup(strDLLName, hmod);

		if(hmod == NULL)
		{
			hmod = ::LoadLibraryFromApplicationDirectory(strDLLName, _T("plugins"));

			if(!hmod)
				throw -1;

			theApp.LoadedLibraryList[strDLLName] = hmod;
		}

		pGetSHLStudioProjectInstance = (LPFNGETSHLSTUDIOPROJECTINSTANCE)::GetProcAddress(hmod, "GetSHLStudioProjectInstance");

		ptrSHLStudioProject = (SHLSTUDIOPROJECTHANDLE)pGetSHLStudioProjectInstance();
		Arguments.AddItem(Project);
		Arguments.AddItem(folder);
		Arguments.AddItem(&m_wndSolutionView);
		Arguments.AddItem(&m_mapIcons);
		Arguments.AddItem(&m_SolutionViewImages);
		ptrSHLStudioProject->RunMethods(SHLSTUDIOMETHODS_ADDEXISTINGITEMFROMFOLDER, &Arguments);
		pw.SaveProject(Project);
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

	Arguments.RemoveAllItems(false);
}

void CSolutionExplorerView::AddNewDependency(HTREEITEM hItemselected)
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

void CSolutionExplorerView::AddExistingDependency(HTREEITEM hItemselected)
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

void CSolutionExplorerView::NewProject()
{
	try
	{
		if(m_wndSolutionView.GetRootItem() != NULL)
		{
			AddNewProject();
		}
		else
		{
			AddNewSolution();
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

void CSolutionExplorerView::AddFolder()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				AddProjectFolder(m_hContextMenuItemselected);
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
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

void CSolutionExplorerView::AddProjectFolder(HTREEITEM hItemselected)
{
	CProjectEntity* Project;
	CFolderEntity* folder;
	CGUID guid;
	CString GUIDIcon;
	int nIndexImage, nIndexSelectImage;
	CString typeicon;

	HTREEITEM hFolder;
	HTREEITEM hItemProject;

	CProjectWrapper pw;

	try
	{
		Project = pw.GetProject(m_solution, hItemselected);
		hItemProject = Project->TreeNode;

		typeicon.Format(_T("%s-FOLDER"), Project->Type);

		folder = new CFolderEntity();

		guid.NewGuid();
		
		folder->ID = _T("{") + guid.GuidString.MakeUpper() + _T("}");
		folder->Name =_T("Folder");
		folder->Type = _T("Virtual");
		folder->Icon = m_mapTypeIcons[typeicon];

		Project->Folders->AddItem(folder);

		nIndexImage			= m_mapIcons[folder->Icon];
		nIndexSelectImage	= nIndexImage + 1;

		hFolder = m_wndSolutionView.InsertItem(folder->Name, nIndexImage, nIndexSelectImage, hItemProject);
 		folder->TreeItem = hFolder;
		m_wndSolutionView.SetItemData(hFolder, ID_TREE_VIEW_TAB_FOLDER);

		SaveProject(hItemselected);
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

void CSolutionExplorerView::AddNewProject(CProjectEntity* Project, CString PathFile)
{
	CProjectWrapper projectWrapper;

	CItemEntity *Item;
	CString pathSource;
	CString pathTarget;
	CPath path;
	CProjectEntity* projectAdd = NULL;

	HTREEITEM hRoot;

	try
	{
		hRoot = m_wndSolutionView.GetRootItem();

		projectAdd = new CProjectEntity();

		projectAdd->Name = Project->Template;
		projectAdd->FileName = Project->TemplateFile;
		projectAdd->PropertyFile = Project->TemplateProperties;

		projectAdd->Path = Project->Path;

		for(UINT nItemIndex = 0; nItemIndex < Project->Items->GetItemCount(); nItemIndex++)
		{
			Item = Project->Items->GetItemAt(nItemIndex);

			pathSource = Item->FileName;
			path.SetPath(pathSource);

			path.AddPath(2, Project->Path, GetPartOf(pathSource, _A_ARQ) );
			pathTarget = path.GetPath();

			CopyFile(pathSource, pathTarget, FALSE);

		}

		projectWrapper.AddProjectItems(projectAdd, m_wndSolutionView, hRoot, m_mapIcons, m_SolutionViewImages);

		m_hContextMenuItemselected = projectAdd->TreeNode;

		m_solution->Projects->AddItem(projectAdd);
		SaveSolution();

		RenameProject(Project->Name);

		m_wndSolutionView.SetItemText(m_hContextMenuItemselected, Project->Name);
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

void CSolutionExplorerView::AddNewItem(CProjectEntity* Project, CItemEntity *ItemAdd, CString folderID, CString PathFile, HTREEITEM hParentItem)
{
	CItemEntity *Item;
	CItemEntity *Dependency;
	CItemEntity *DependencyAdd;
	CString pathSource;
	CString pathTarget;
	CPath path;

	int nIndexImage, nIndexSelectImage;

	HTREEITEM hItemFile;
	HTREEITEM hDependency;

	try
	{

		if(ExistsItem(Project, ItemAdd->Name))
		{
			CString msg;

			msg.Format(_T("File\n%s already exists in the project."), ItemAdd->Name);

			AfxMessageBox(msg);

			return;
		}

		Item = new CItemEntity();

		Item->Name = ItemAdd->Name;
		Item->FolderID = folderID;
		Item->Icon = ItemAdd->Icon;
		Item->Type = ItemAdd->Type;
		Item->FileName = ItemAdd->FileName;
		Item->PropertyFile = ItemAdd->PropertyFile;
		Item->PathType = _T("Relative");
		path.AddPath(2, PathFile, _T(".\\"));
		Item->Path = path.GetPath();

		path.SetPath(ItemAdd->TemplateFile);
		if(!path.ExistFile())
		{
			CString msg;
			msg.Format(_T("Source file %s does not exists."), path.GetPath());
			AfxMessageBox(msg);
			delete Item;

			return;
		}
		pathSource = path.GetPath();

		path.AddPath(2, PathFile, ItemAdd->FileName);
		pathTarget = path.GetPath();

		if(!CopyFile(pathSource, pathTarget, TRUE))
		{
			CString msg;
			msg.Format(_T("Can not copy %s to %s"), pathSource, pathTarget);
			AfxMessageBox(msg);
			delete Item;

			return;
		}

		path.SetPath(ItemAdd->TemplateProperties);
		if(!path.ExistFile())
		{
			CString msg;
			msg.Format(_T("Source file %s does not exists."), path.GetPath());
			AfxMessageBox(msg);
				
			DeleteFile(pathTarget);

			delete Item;

			return;
		}
		pathSource = path.GetPath();

		path.AddPath(2, PathFile, ItemAdd->PropertyFile);
		pathTarget = path.GetPath();

		CopyFile(pathSource, pathTarget, FALSE);

		nIndexImage			= m_mapIcons[Item->Icon];
		nIndexSelectImage	= nIndexImage + 1;

		hItemFile = m_wndSolutionView.InsertItem(Item->Name, nIndexImage, nIndexSelectImage, hParentItem);
		m_wndSolutionView.SetItemData(hItemFile, ID_TREE_VIEW_TAB_ITEM);
		Item->TreeNode = hItemFile;
		Item->Project = Project;
		
		for(UINT nIndexDependency = 0; nIndexDependency < ItemAdd->Dependencies->GetItemCount(); nIndexDependency++)
		{
			DependencyAdd = ItemAdd->Dependencies->GetItemAt(nIndexDependency);

			Dependency = new CItemEntity();

			Dependency->Name = DependencyAdd->Name;
			Dependency->Type = DependencyAdd->Type;
			Dependency->FileName = DependencyAdd->FileName;
			Dependency->Path = Item->Path;
			Dependency->Icon = DependencyAdd->Icon;
			Dependency->Project = Project;

			path.SetPath(DependencyAdd->TemplateFile);
			pathSource = path.GetPath();

			path.AddPath(2, PathFile, Dependency->FileName);
			pathTarget = path.GetPath();

			CopyFile(pathSource, pathTarget, FALSE);

			nIndexImage			= m_mapIcons[Dependency->Icon];
			nIndexSelectImage	= nIndexImage + 1;

			hDependency = m_wndSolutionView.InsertItem(Dependency->Name, nIndexSelectImage, nIndexSelectImage, Item->TreeNode);
			Dependency->TreeNode = hDependency;
			m_wndSolutionView.SetItemData(hDependency, ID_TREE_VIEW_TAB_DEPENDENCY);

			Item->Dependencies->AddItem(Dependency);
		}

		Project->Items->AddItem(Item);

		SaveProject(Project->TreeNode);
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

void CSolutionExplorerView::Build()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected == NULL || m_hThreadStarter != NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				BuildSolution();
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				BuildProject(m_hContextMenuItemselected);
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
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

void CSolutionExplorerView::BuildSolution()
{
	CProjectEntity* Project;
	INT nTotalProjects = 0;
	INT nTotalBuild = 0;
	INT nTotalSkipped = 0;
	INT nTotalError = 0;
	CString strMsg;

	try
	{
		nTotalProjects = m_solution->Projects->GetItemCount();

		for(UINT nIndexProject = 0; nIndexProject < m_solution->Projects->GetItemCount(); nIndexProject++)
		{
			Project = m_solution->Projects->GetItemAt(nIndexProject);

			if(Project->CanBuild)
			{
				nTotalBuild++;
				m_buildnextproject = FALSE;
				BuildProject(Project->TreeNode, false);
				while(!m_buildnextproject)
				{
					DoEvents();
				}

				Sleep(500);

				if(!m_buildprojectresultok)
					nTotalError++;
			}
			else
			{
				nTotalSkipped++;
			}
		}

		strMsg.Format(_T("==============================================================================================================="));
		SendOutPutMessage(m_wndOutput->GetSafeHwnd(), strMsg);
		strMsg.Format(_T("========== Build: %d project, %d succeeded, %d failed, %d skipped =========="), nTotalProjects, (nTotalBuild-nTotalError), nTotalError, nTotalSkipped);
		SendOutPutMessage(m_wndOutput->GetSafeHwnd(), strMsg);

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

void CSolutionExplorerView::BuildProject(HTREEITEM item, BOOL clearOutput)
{
	CProjectEntity* Project;
	CString strDLLName;

	ISHLStudioProject* ptrSHLStudioProject = NULL;
	HMODULE hmod = NULL;
	LPFNGETSHLSTUDIOPROJECTINSTANCE pGetSHLStudioProjectInstance;

	CString strMsg;

	BUILPROJECTINFO *projectInfo;

	CProjectWrapper pw;

	try
	{
		Project = pw.GetProject(m_solution, item);

		strDLLName = Project->ClassDll;

		theApp.LoadedLibraryList.Lookup(strDLLName, hmod);

		if(hmod == NULL)
		{
			hmod = ::LoadLibraryFromApplicationDirectory(strDLLName, _T("plugins"));

			if(!hmod)
				throw -1;

			theApp.LoadedLibraryList[strDLLName] = hmod;
		}

		pGetSHLStudioProjectInstance = (LPFNGETSHLSTUDIOPROJECTINSTANCE)::GetProcAddress(hmod, "GetSHLStudioProjectInstance");

		ptrSHLStudioProject = (SHLSTUDIOPROJECTHANDLE)pGetSHLStudioProjectInstance();

		projectInfo = new BUILPROJECTINFO();
		projectInfo->Project = Project;
		projectInfo->Item = NULL;
		projectInfo->ptrSHLStudioProject = ptrSHLStudioProject;
		projectInfo->hwndOutput = m_wndOutput->GetSafeHwnd();
		projectInfo->hwndParent = this->GetSafeHwnd();

		if(clearOutput)
			::SendMessage(projectInfo->hwndOutput, WM_CLEAR_STRING_OUTPUT, 0, 0);

		m_hThreadStarter = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)BuildProjectThread, (BUILPROJECTINFO *)projectInfo, CREATE_SUSPENDED, &m_dwThreadStarter);
		projectInfo->hThreadStarter = &m_hThreadStarter;
		ResumeThread(m_hThreadStarter);
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

void CSolutionExplorerView::Generate()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				break;

			case ID_TREE_VIEW_TAB_PROJECT:				
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				GenerateItem();
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
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

void CSolutionExplorerView::GenerateItem()
{
	CProjectEntity* Project;
	CItemEntity* Item;
	CString strDLLName;

	ISHLStudioProject* ptrSHLStudioProject = NULL;
	HMODULE hmod = NULL;
	LPFNGETSHLSTUDIOPROJECTINSTANCE pGetSHLStudioProjectInstance;

	CRuntimeClass* pNewViewClass = NULL;
	CRuntimeClass* pNewDocClass = NULL;
	CRuntimeClass* pNewChildFrame = NULL;
	CDocument* pDoc = NULL;
	CMultiDocTemplate* pDocTemplate = NULL;

	CString strKeyMultiDocTemplate;
	CString strTitle;

	BOOL bUseDocumentView = FALSE;

	CString strMsg;
	CProjectWrapper pw;

	SHLSTUDIOARGLIST Arguments;

	try
	{
		Item = pw.GetItem(m_solution, m_hContextMenuItemselected);	
		Project = (CProjectEntity*)Item->Project;

		strDLLName = Project->ClassDll;
		strKeyMultiDocTemplate.Format(_T("%s_%s_GENERATEITEM"), strDLLName, Item->Type);
		
		theApp.LoadedLibraryList.Lookup(strDLLName, hmod);

		if(hmod == NULL)
		{
			hmod = ::LoadLibraryFromApplicationDirectory(strDLLName, _T("plugins"));

			if(!hmod)
				throw -1;

			theApp.LoadedLibraryList[strDLLName] = hmod;
		}

		pGetSHLStudioProjectInstance = (LPFNGETSHLSTUDIOPROJECTINSTANCE)::GetProcAddress(hmod, "GetSHLStudioProjectInstance");

		ptrSHLStudioProject = (SHLSTUDIOPROJECTHANDLE)pGetSHLStudioProjectInstance();

		theApp.MultiDocTemplateList.Lookup(strKeyMultiDocTemplate, pDocTemplate);

		bUseDocumentView = ptrSHLStudioProject->GetDocumentTemplate(SHLSTUDIOMETHODS_LOAGENERATEITEM, NULL, m_solution, Project, Item, pNewChildFrame, pNewViewClass, pNewDocClass);

		if(bUseDocumentView)
		{
			if(pDocTemplate == NULL)
			{
				pDocTemplate = new CMultiDocTemplate(IDR_SHLStudioTYPE,
					pNewDocClass,
					pNewChildFrame, // custom MDI child frame
					pNewViewClass);

				if (!pDocTemplate)
					return;

				theApp.MultiDocTemplateList[strKeyMultiDocTemplate] = pDocTemplate;
				theApp.AddDocTemplate(pDocTemplate);
			}

			pDoc = (CDocument*)pDocTemplate->OpenDocumentFile(NULL);
			pDoc->OnOpenDocument(NULL);
			pDoc->UpdateAllViews(NULL, NULL, NULL);
			pDoc->UpdateFrameCounts();
			Arguments.AddItem(Project);
			Arguments.AddItem(Item);
			Arguments.AddItem(pDoc);
			ptrSHLStudioProject->RunMethods(SHLSTUDIOMETHODS_SETGENERATEITEM, &Arguments);
			Arguments.RemoveAllItems(false);
		}
		else
		{
			if(m_hThreadStarter != NULL)
				return;

			strMsg.Format(_T("> --------- Build started: Item: %s -----------"), Item->Name);
			SendOutPutMessage(m_wndOutput->GetSafeHwnd(), strMsg);

			HWND output = m_wndOutput->GetSafeHwnd();
			Arguments.AddItem(Project);
			Arguments.AddItem(Item);
			Arguments.AddItem(&output);
			if(ptrSHLStudioProject->RunMethods(SHLSTUDIOMETHODS_GENERATEITEM, &Arguments))
			{
				strMsg.Format(_T("> Build: Succeeded."));
				SendOutPutMessage(m_wndOutput->GetSafeHwnd(), strMsg);
			}
			Arguments.RemoveAllItems(false);

			strMsg.Format(_T("> --------- Build endded: Item: %s -----------"), Item->Name);
			SendOutPutMessage(m_wndOutput->GetSafeHwnd(), strMsg);
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

void CSolutionExplorerView::CloseAllDocuments(CString dllName)
{
	POSITION	posTemplate = NULL;
	CString key;
	CMultiDocTemplate* DocTemplate = NULL;

	try
	{
		posTemplate = theApp.MultiDocTemplateList.GetStartPosition();

		while(posTemplate != NULL)
		{
			theApp.MultiDocTemplateList.GetNextAssoc( posTemplate, key, DocTemplate);
			if(key.Find(dllName) == 0)
			{
				DocTemplate->CloseAllDocuments(TRUE);
			}
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

void CSolutionExplorerView::ConfigurationManager()
{
	DWORD nType;
	CConfigurationManager dlg;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				dlg.Solution = m_solution;
				dlg.DoModal();

				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
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

void CSolutionExplorerView::OpenFolderInFileExplorer()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				OpenFolderInFileExplorerSolution();
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				OpenFolderInFileExplorerProject();
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				OpenFolderInFileExplorerItem();
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
				OpenFolderInFileExplorerItem();
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

void CSolutionExplorerView::Remove()
{
	DWORD nType;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				RemoveProject(m_hContextMenuItemselected);
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				RemoveFolder(m_hContextMenuItemselected);
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				RemoveItem(m_hContextMenuItemselected);
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
				RemoveDependency(m_hContextMenuItemselected);
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

void CSolutionExplorerView::RemoveProject(HTREEITEM hItemselected)
{
	CProjectEntity* project;
	CString strMessage;
	CProjectWrapper pw;

	try
	{
		project = pw.GetProject(m_solution, hItemselected);

		strMessage.Format(_T("Remove project %s from this solution?"), project->Name);
		if(!Yes(strMessage))
			return;

		m_solution->Projects->RemoveItem(project);

		SaveSolution();

		m_wndSolutionView.DeleteItem(hItemselected);
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

void CSolutionExplorerView::RemoveFolder(HTREEITEM hItemselected)
{
	CProjectEntity* project;
	CFolderEntity* folder;
	CItemEntity* item;
	CString folderID;
	UINT nIndex;
	CString strMessage;
	CProjectWrapper pw;

	try
	{
		project = pw.GetProject(m_solution, hItemselected);
		folder = pw.GetFolder(m_solution, hItemselected);
		folderID = folder->ID;

		strMessage.Format(_T("Remove the folder %s and his children items from the %s project?"), folder->Name, project->Name);
		if(!Yes(strMessage))
			return;

		project->Folders->RemoveItem(folder);

		nIndex = 0;
		while(true)
		{
			item = project->Items->GetItemAt(nIndex);

			if(item->FolderID == folderID)
			{
				project->Items->RemoveItem(item);
				nIndex = 0;
			}
			else
				nIndex++;

			if(project->Items->GetItemCount() == 0 || nIndex == project->Items->GetItemCount())
				break;
		}

		SaveProject(project->TreeNode);

		m_wndSolutionView.DeleteItem(hItemselected);
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

void CSolutionExplorerView::RemoveItem(HTREEITEM hItemselected)
{
	CProjectEntity* project;
	CItemEntity* item;
	CString strMessage;
	CProjectWrapper pw;

	try
	{
		project = pw.GetProject(m_solution, hItemselected);
		item = pw.GetItem(m_solution, hItemselected);

		strMessage.Format(_T("Remove %s item from the %s project?"), item->Name, project->Name);
		if(!Yes(strMessage))
			return;

		project->Items->RemoveItem(item);
		
		SaveProject(project->TreeNode);

		m_wndSolutionView.DeleteItem(hItemselected);
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

void CSolutionExplorerView::RemoveDependency(HTREEITEM hItemselected)
{
	CProjectEntity* project;
	CItemEntity* item;
	CItemEntity* dependency;
	HTREEITEM  hItem;
	CString strMessage;
	CProjectWrapper pw;

	try
	{
		project = pw.GetProject(m_solution, hItemselected);
		dependency = pw.GetItem(m_solution, hItemselected);
		hItem = m_wndSolutionView.GetParentItem(hItemselected);
		item = pw.GetItem(m_solution, hItem);

		strMessage.Format(_T("Remove %s dependency item from the parent item %s in the %s project?"),  dependency->Name, item->Name, project->Name);
		if(!Yes(strMessage))
			return;

		item->Dependencies->RemoveItem(dependency);

		SaveProject(project->TreeNode);

		m_wndSolutionView.DeleteItem(hItemselected);
		
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

void CSolutionExplorerView::CloseSolution()
{
	CProjectEntity* Project;
	CString strDLLName;

	try
	{
		if(!Yes(_T("Close this solution?")))
			return;

		for(UINT nIndexSolution = 0; nIndexSolution < m_solution->Projects->GetItemCount(); nIndexSolution++)
		{
			Project = m_solution->Projects->GetItemAt(nIndexSolution);
			strDLLName = Project->ClassDll;

			CloseAllDocuments(strDLLName);
		}


		m_wndSolutionView.DeleteAllItems();
		m_wndproperties->ClearAndHide();

		m_solution->Reset();
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

void CSolutionExplorerView::Rename()
{
	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		m_wndSolutionView.EditLabel(m_hContextMenuItemselected);
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

void CSolutionExplorerView::EndLabelEdit(TV_DISPINFO* pTVDispInfo)
{
	DWORD nType;
	CString editName;

	try
	{
		if(m_hContextMenuItemselected == NULL)
			return;

		editName = pTVDispInfo->item.pszText;

		nType = m_wndSolutionView.GetItemData(m_hContextMenuItemselected);

		switch(nType)
		{
			case ID_TREE_VIEW_TAB_SOLUTION:
				RenameSolution(editName);
				break;

			case ID_TREE_VIEW_TAB_PROJECT:
				RenameProject(editName);
				break;

			case ID_TREE_VIEW_TAB_FOLDER:
				RenameFolder(editName);
				break;

			case ID_TREE_VIEW_TAB_ITEM:
				RenameItem(editName);
				break;

			case ID_TREE_VIEW_TAB_DEPENDENCY:
				RenameItem(editName);
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

void CSolutionExplorerView::RenameSolution(CString solutionName)
{
	CString oldFileName;
	CString newFileName;
	CPath path;
	CString oldSolutionName;

	try
	{
		oldSolutionName = m_wndSolutionView.GetItemText(m_hContextMenuItemselected);

		if(solutionName == _T("") || solutionName == oldSolutionName)
			return;

		path.AddPath(2, m_solution->Path, m_solution->FileName);
		oldFileName = path.GetPath();

		path.AddPath(2, m_solution->Path, (solutionName + _T(".jsl")));
		newFileName = path.GetPath();

		m_solution->Name = solutionName;
		m_solution->FileName = solutionName + _T(".jsl");

		MoveFile(oldFileName, newFileName);

		SaveSolution();

		m_wndSolutionView.SetItemText(m_hContextMenuItemselected, solutionName);
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

void CSolutionExplorerView::RenameProject(CString projectName)
{
	CProjectEntity* project;
	CString oldFileName, oldFileNameProperty;
	CString newFileName, newFileNameProperty;
	CPath path;
	CString oldProjectName;
	CProjectWrapper pw;

	try
	{
		oldProjectName = m_wndSolutionView.GetItemText(m_hContextMenuItemselected);

		if(projectName == _T("") || projectName == oldProjectName)
			return;

		project = pw.GetProject(m_solution, m_hContextMenuItemselected);

		path.AddPath(2, project->Path, project->FileName);
		oldFileName = path.GetPath();

		path.AddPath(2, project->Path, (project->PropertyFile));
		oldFileNameProperty = path.GetPath();

		path.AddPath(2, project->Path, (projectName + _T(".jpj")));
		newFileName = path.GetPath();

		path.AddPath(2, project->Path, (projectName + _T(".prt")));
		newFileNameProperty = path.GetPath();

		project->Name = projectName;
		project->FileName = projectName + _T(".jpj");
		project->PropertyFile = projectName + _T(".prt");

		MoveFile(oldFileName, newFileName);
		MoveFile(oldFileNameProperty, newFileNameProperty);

		SaveSolution();
		SaveProject(m_hContextMenuItemselected);

		m_wndSolutionView.SetItemText(m_hContextMenuItemselected, projectName);
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

void CSolutionExplorerView::RenameFolder(CString folderName)
{
	CFolderEntity* folder;
	CString oldFolderName;
	CProjectWrapper pw;

	try
	{
		oldFolderName = m_wndSolutionView.GetItemText(m_hContextMenuItemselected);

		if(folderName == _T("") || folderName == oldFolderName)
			return;

		folder = pw.GetFolder(m_solution, m_hContextMenuItemselected);

		folder->Name = folderName;

		SaveProject(m_hContextMenuItemselected);

		m_wndSolutionView.SetItemText(m_hContextMenuItemselected, folderName);
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

void CSolutionExplorerView::RenameItem(CString itemName)
{
	CItemEntity* item;
	CString extFile;
	CString oldFileName, oldFileNameProperty;
	CString newFileName, newFileNameProperty;
	CPath path;
	CString olditemName;
	CProjectWrapper pw;

	try
	{
		olditemName = m_wndSolutionView.GetItemText(m_hContextMenuItemselected);

		if(itemName == _T("") || itemName == olditemName)
			return;

		item = pw.GetItem(m_solution, m_hContextMenuItemselected);

		path.AddPath(2, item->Path, item->FileName);
		oldFileName = path.GetPath();

		extFile = oldFileName.Mid(oldFileName.ReverseFind(_T('.')));

		path.AddPath(2, item->Path, (item->FileName + _T(".prt")));
		oldFileNameProperty = path.GetPath();

		path.AddPath(2, item->Path, (itemName + extFile));
		newFileName = path.GetPath();

		path.AddPath(2, item->Path, (itemName + extFile + _T(".prt")));
		newFileNameProperty = path.GetPath();

		item->Name = itemName;
		item->FileName = itemName + extFile;
		item->PropertyFile = itemName + extFile + _T(".prt");

		MoveFile(oldFileName, newFileName);
		MoveFile(oldFileNameProperty, newFileNameProperty);

		SaveProject(m_hContextMenuItemselected);

		m_wndSolutionView.SetItemText(m_hContextMenuItemselected, itemName);
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

void CSolutionExplorerView::SaveProject(HTREEITEM hItemselected)
{
	CProjectWrapper projectwrapper;
	CProjectEntity *project;
	CProjectWrapper pw;

	try
	{
		BeginWaitCursor();

		project = pw.GetProject(m_solution, hItemselected);

		projectwrapper.SaveProject(project);
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

	EndWaitCursor();
}

void CSolutionExplorerView::SaveSolution()
{
	CProjectWrapper projectwrapper;

	try
	{
		BeginWaitCursor();

		projectwrapper.SaveSolution(m_solution, false);
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

	EndWaitCursor();
}

BOOL CSolutionExplorerView::ExistsItem(CProjectEntity* project, CString itemName)
{
	CItemEntity *Item;
	BOOL bRet = FALSE;

	try
	{
		for(UINT nIndexItem = 0; nIndexItem < project->Items->GetItemCount(); nIndexItem++)
		{
			Item = project->Items->GetItemAt(nIndexItem);

			if(Item->Name == itemName)
			{
				bRet = TRUE;
				break;
			}
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

	return bRet;
}

void CSolutionExplorerView::SaveSolutionAndAllProjects()
{
	CProjectWrapper projectwrapper;

	try
	{
		BeginWaitCursor();

		projectwrapper.SaveSolution(m_solution, true);
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

	EndWaitCursor();
}

void  CSolutionExplorerView::SendOutPutMessage(HWND hwndOutput, CString message)
{
	TCHAR *szMessage;
	INT size;
	INT sizecreated;

	try
	{
		size = message.GetLength();
		sizecreated = size + 2;

		if(size == 0)
			return;

		szMessage = new TCHAR[sizecreated];

		memset(szMessage, NULL, sizeof(TCHAR) * sizecreated);

		Copychar(message.GetBuffer(), szMessage, size);

		::SendMessage(hwndOutput, WM_ADD_STRING_OUTPUT, (WPARAM)szMessage, 0);
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

//////////////////////////////////////////////////////////////////////////////////////////////
// 
//  P U B L I C   M E T H O D S 
//
//////////////////////////////////////////////////////////////////////////////////////////////
#pragma region REGION_PUBLIC_METHODS
CViewTree& CSolutionExplorerView::GetTreeView()
{
	return m_wndSolutionView;
}

CImageList& CSolutionExplorerView::GetImageList()
{
	return m_SolutionViewImages;
}

MAPICONS& CSolutionExplorerView::GetMapIcon()
{
	return m_mapIcons;
}

MAPTYPEICONS& CSolutionExplorerView::GetMapTypeIcon()
{
	return m_mapTypeIcons;
}
#pragma region REGION_PUBLIC_METHODS


#pragma region THREAD
HRESULT BuildProjectThread(BUILPROJECTINFO *projectInfo)
{
	CString strMsg;
	bool bSucceeded = false;
	CString DATETIME;
	CTime tm;
	SHLSTUDIOARGLIST Arguments;

	try
	{
		strMsg.Format(_T("> --------- Build started: Project: %s -----------"), projectInfo->Project->Name);
		SendOutPutMessage(projectInfo->hwndOutput, strMsg);

		tm = CTime::GetCurrentTime();;
		DToC(tm, DATETIME, DT_TIME);

		strMsg.Format(_T("> --------- Time: %s -----------"), DATETIME);
		SendOutPutMessage(projectInfo->hwndOutput, strMsg);

		Arguments.AddItem(projectInfo->Project);
		Arguments.AddItem(&projectInfo->hwndOutput);
		bSucceeded = projectInfo->ptrSHLStudioProject->RunMethods(SHLSTUDIOMETHODS_BUILDPROJECT, &Arguments);;
		Arguments.RemoveAllItems(false);

		tm = CTime::GetCurrentTime();;
		DToC(tm, DATETIME, DT_TIME);

		strMsg.Format(_T("> --------- Time: %s -----------"), DATETIME);
		SendOutPutMessage(projectInfo->hwndOutput, strMsg);

		strMsg.Format(_T("> --------- Build endded: Project: %s -----------"), projectInfo->Project->Name);
		SendOutPutMessage(projectInfo->hwndOutput, strMsg);

		if(bSucceeded)
		{
			strMsg.Format(_T("> Build: Succeeded."));
			SendOutPutMessage(projectInfo->hwndOutput, strMsg);
		}

	}
	catch(...)
	{
	}

	SendMessage(projectInfo->hwndParent, WM_SETBUILDPROJECTRESULT, (WPARAM)bSucceeded, 0);
	SendMessage(projectInfo->hwndParent, WM_SETNEXTBUILDPROJECTRESULT, 0, 0);

	CloseHandle(*projectInfo->hThreadStarter);
	*projectInfo->hThreadStarter = NULL;

	delete projectInfo;

	return 0;
}

void  SendOutPutMessage(HWND hwndOutput, CString message)
{
	TCHAR *szMessage;
	INT size;
	INT sizecreated;

	try
	{
		size = message.GetLength();
		sizecreated = size + 2;

		if(size == 0)
			return;

		szMessage = new TCHAR[sizecreated];

		memset(szMessage, NULL, sizeof(TCHAR) * sizecreated);

		Copychar(message.GetBuffer(), szMessage, size);

		::SendMessage(hwndOutput, WM_ADD_STRING_OUTPUT, (WPARAM)szMessage, 0);
	}
	catch(...)
	{
	}
}
#pragma endregion THREAD