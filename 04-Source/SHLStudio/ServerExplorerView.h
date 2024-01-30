/* ***************************************************************************
 * Arquivo: ServerExplorerView                                               *
 *                                                                           *
 * Classe treeview contendo os banco de das para a ação de Query Analyzer    *
 * do SHLStudio                                                              *
 *                                                                           *
 * Data:28/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "ISHLQuery.h"
#include "QueryDataConnectionEntity.h"
#include "SHLTreeNode.h"
#include "ViewTree.h"
#include "SHLDataConnection.h"
#include "PropertiesWnd.h"
#include "OutputWnd.h"
#include "Property.h"

// CServerExplorerView
class CServerExplorerViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }

public:
	void InsertNewButton(UINT nID, int image)
	{		
		CMFCToolBarButton *button = new CMFCToolBarButton(nID, image);

		button->m_bImage = TRUE;
		button->m_bText = FALSE;
		button->SetStyle(BTNS_AUTOSIZE | BTNS_BUTTON);

		int nIndexButton = InsertButton(button);

		SetButtonInfo(nIndexButton, nID, TBBS_BUTTON, image);

		AdjustLocations();
		Invalidate();
		RecalcLayout();
	}

	BOOL InsertNewButtonEx(UINT nID, UINT uiHotResID, BOOL bUserButton = FALSE, UINT uiColdResID = 0, UINT uiDisabledResID = 0, UINT uiMenuResID = 0, UINT uiMenuDisabledResID = 0)
	{	
		CMFCToolBarInfo params;

		params.m_uiHotResID = uiHotResID;
		params.m_uiColdResID = uiColdResID!=0?uiColdResID:uiHotResID;
		params.m_uiDisabledResID = uiDisabledResID!=0?uiDisabledResID:uiHotResID;
		params.m_uiMenuResID = uiMenuResID!=0?uiMenuResID:uiHotResID;
		params.m_uiMenuDisabledResID = uiMenuDisabledResID!=0?uiMenuDisabledResID:uiHotResID;

		if(!LoadBitmapEx(params, TRUE))
			return FALSE;

		int image = m_ImagesLocked.GetCount()-1;

		CMFCToolBarButton *button = new CMFCToolBarButton(nID, image);
		button->m_bUserButton = bUserButton;
		button->m_bImage = TRUE;
		button->m_bText = FALSE;
		button->SetStyle(TBSTYLE_AUTOSIZE);

		int nIndexButton = InsertButton(button);

		SetButtonInfo( nIndexButton, nID, TBBS_BUTTON, image);

		AdjustLocations();
		Invalidate();
		RecalcLayout();

		return TRUE;
	}
};

class CServerExplorerView : public CDockablePane
{
	DECLARE_DYNAMIC(CServerExplorerView)

public:
	CServerExplorerView();
	virtual ~CServerExplorerView();

	void AdjustLayout();
	void OnChangeVisualStyle();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	afx_msg void OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnButtonDown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTreeViewExpanding(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnUpdateConnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRefresh(CCmdUI* pCmdUI);

	afx_msg void OnUpdateConnectContextMenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDisconnectContextMenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRefreshContextMenu(CCmdUI* pCmdUI);

	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);

	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	afx_msg void OnRefresh();

	afx_msg void OnConnectContextMenu();
	afx_msg void OnDisconnectContextMenu();
	afx_msg void OnRefreshContextMenu();

	afx_msg void OnAddConnection();
	afx_msg void OnRemoveConnection();
	afx_msg void OnSaveConnections();
	afx_msg void OnProperties();
	afx_msg void OnNewQuery();
	afx_msg void OnNewQueryAccel();
	afx_msg void OnRenameConnection();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

protected:
	CServerExplorerViewToolBar m_wndToolBar;
	CImageList m_ServerViewImages;
	CViewTree m_wndServerView;
	ISHLQuery* m_ptrSHLQuery;
	CSHLTreeNode<CQueryDataConnectionEntity> m_dataconnection;
	HTREEITEM m_hItem;
	HTREEITEM m_hContextMenuItemselected;
	HACCEL m_hAccel;

	CPropertiesWnd*		m_wndproperties;
	COutputWnd*			m_wndOutput;

	BOOL	m_bEditLabelMode;

public:
	PROPERTY(CPropertiesWnd*, Properties)
  	GET(Properties) 
 	{ 
 		return m_wndproperties; 
	}
 	SET(Properties)
 	{
 		m_wndproperties = value;
 	} 

	PROPERTY(COutputWnd*, Output)
  	GET(Output) 
 	{ 
 		return m_wndOutput; 
	}
 	SET(Output)
 	{
 		m_wndOutput = value;
 	} 

public:
	void NewQuery(CQueryDataConnectionEntity*  dataconnection, CString databasename);
	void AddConnection();
	void SaveConnections();

private:
	int InitControls();
	void InitExplorerTreeView();
	void LoadShlQuery();
	void LoadConnections();

	BOOL EnableConnect(HTREEITEM itemSelected);
	BOOL EnableDisconnect(HTREEITEM itemSelected);
	BOOL EnableRefresh(HTREEITEM itemSelected);

	void UpdateToolBarServerExplorer(UINT nID, INT index);

	void PressedButtonTreeView();
	void FillChildrenTreeViewItems();

	void ContextMenu(HTREEITEM itemSelected, CPoint& point);

	CQueryDataConnectionEntity* GetDataConnection(HTREEITEM phItem);
	HTREEITEM GetParentTreeItem(HTREEITEM phItem, SHLDATACONNECTION target, BOOL bUpDirection = 1);

	void ConnectDatabaseServer(HTREEITEM phItem);
	void RefreshDatabaseServer(HTREEITEM phItem);
	void DisconnectDatabaseServer(HTREEITEM phItem);
	bool DeleteChildItemTreeView(HTREEITEM phItem);

	void RemoveConnection(HTREEITEM phItem);

	void Refresh(HTREEITEM phItem);
	void ShowProperties(HTREEITEM phItem, BOOL showPane);

	void ShowPropertiesConnection(HTREEITEM phItem, BOOL showPane);
	void ShowPropertiesDatabase(HTREEITEM phItem, BOOL showPane);
	void ShowSysPropertiesElements(HTREEITEM phItem, SHLDATACONNECTION nType, BOOL showPane);
	void ShowUserPropertiesElements(HTREEITEM phItem, SHLDATACONNECTION nType, BOOL showPane);

	void NewQuery(HTREEITEM phItem);

	// SYSTEM
	void ShowSysElements(HTREEITEM phItem);
	void ShowSysDatabases(HTREEITEM phItem);
	void ShowSysTables(HTREEITEM phItem);
	void ShowSysColumns(HTREEITEM phItem);
	void ShowSysViews(HTREEITEM phItem);
	void ShowSysSequences(HTREEITEM phItem);
	void ShowSysConstraints(HTREEITEM phItem);
	void ShowSysTriggers(HTREEITEM phItem);
	void ShowSysIndexes(HTREEITEM phItem);
	void ShowSysProcedures(HTREEITEM phItem);
	void ShowSysFunctions(HTREEITEM phItem);
	void ShowSysTableColumns(HTREEITEM phItem);
	void ShowSysColumnsDetail(HTREEITEM phItem);
	void ShowSysTablePrimeryKeys(HTREEITEM phItem);
	void ShowSysTableConstraints(HTREEITEM phItem);
	void ShowSysTableTriggers(HTREEITEM phItem);
	void ShowSysTableIndexes(HTREEITEM phItem);
	void ShowSysTableSequences(HTREEITEM phItem);
	void ShowSysView(HTREEITEM phItem);
	void ShowSysViewParameters(HTREEITEM phItem);
	void ShowSysProcedure(HTREEITEM phItem);
	void ShowSysProcedureParameters(HTREEITEM phItem);
	void ShowSysFunction(HTREEITEM phItem);
	void ShowSysFunctionParameters(HTREEITEM phItem);

	// USER
	void ShowUserElements(HTREEITEM phItem);
	void ShowUserDatabases(HTREEITEM phItem);
	void ShowUserTables(HTREEITEM phItem);
	void ShowUserColumns(HTREEITEM phItem);
	void ShowUserViews(HTREEITEM phItem);
	void ShowUserSequences(HTREEITEM phItem);
	void ShowUserConstraints(HTREEITEM phItem);
	void ShowUserTriggers(HTREEITEM phItem);
	void ShowUserIndexes(HTREEITEM phItem);
	void ShowUserProcedures(HTREEITEM phItem);
	void ShowUserFunctions(HTREEITEM phItem);
	void ShowUserTableColumns(HTREEITEM phItem);
	void ShowUserColumnsDetail(HTREEITEM phItem);
	void ShowUserTablePrimeryKeys(HTREEITEM phItem);
	void ShowUserTableConstraints(HTREEITEM phItem);
	void ShowUserTableTriggers(HTREEITEM phItem);
	void ShowUserTableIndexes(HTREEITEM phItem);
	void ShowUserTableSequences(HTREEITEM phItem);
	void ShowUserView(HTREEITEM phItem);
	void ShowUserViewParameters(HTREEITEM phItem);
	void ShowUserProcedure(HTREEITEM phItem);
	void ShowUserProcedureParameters(HTREEITEM phItem);
	void ShowUserFunction(HTREEITEM phItem);
	void ShowUserFunctionParameters(HTREEITEM phItem);

	void Reset();

	CString InitWaitCursor(HTREEITEM pItem, CString message);
	void FinalizeWaitCursor(HTREEITEM pItem, CString originaltext);
	void LoadDatabaseElementsByNode(SHLDATACONNECTION nType, HTREEITEM pItem, BOOL brefresh);

	HTREEITEM ValidItem(HTREEITEM item);
	BOOL IsValidItem(HTREEITEM item);

	void EndLabelEdit(TV_DISPINFO* pTVDispInfo);
	void RenameConnection();
};


