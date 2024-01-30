/* ***************************************************************************
 * Arquivo: SolutionExplorerView                                             *
 *                                                                           *
 * Classe treeview contendo as soluões, projetos, itens, etc.                *
 *                                                                           *
 * Data:26/03/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "ViewTree.h"
#include "PropertiesWnd.h"
#include "OutputWnd.h"
#include "SolutionEntity.h"
#include "Property.h"

class BUILPROJECTINFO
{
public:
	CProjectEntity *Project;
	CItemEntity *Item;
	SHLSTUDIOPROJECTHANDLE ptrSHLStudioProject;
	HANDLE	*hThreadStarter;
	HWND  hwndOutput;
	HWND  hwndParent;
};

class CSolutionExplorerViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CSolutionExplorerView : public CDockablePane
{
// Construction
public:
	CSolutionExplorerView();

	void AdjustLayout();
	void OnChangeVisualStyle();

	friend HRESULT BuildProjectThread(BUILPROJECTINFO *projectInfo);
// Attributes
protected:

	CViewTree m_wndSolutionView;
	CImageList m_SolutionViewImages;
	CSolutionExplorerViewToolBar m_wndToolBar;
	MAPICONS m_mapIcons;
	MAPTYPEICONS m_mapTypeIcons;

	HANDLE	m_hThreadStarter;
	DWORD   m_dwThreadStarter;

protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
public:
	virtual ~CSolutionExplorerView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	afx_msg void OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnButtonDown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDBButtonDown(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnEditPaste();
	afx_msg void OnExplorerAddNew();
	afx_msg void OnExplorerAddExisting();
	afx_msg void OnExplorerAddfolder();
	afx_msg void OnExplorerBuild();
	afx_msg void OnExplorerGenerate();
	afx_msg void OnExplorerConfigurationManager();
	afx_msg void OnExplorerRename();
	afx_msg void OnExplorerRemove();
	afx_msg void OnExplorerClose();
	afx_msg void OnExplorerOpenFolderInExplorer();

	afx_msg LRESULT OnSetBuildProjectResult(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetNextBuildProject(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

public:
	CViewTree& 	GetTreeView();
	CImageList& GetImageList();
	MAPICONS& GetMapIcon();
	MAPTYPEICONS& GetMapTypeIcon();
	void NewProject();

private:
	void ContextMenu(HTREEITEM itemSelected, CPoint& point);
	void ButtonDown(HTREEITEM itemSelected);
	void DoubleClickDown(HTREEITEM itemSelected);
	void LeftButtonUp(UINT nFlags, CPoint point);
	void MouseMove(UINT nFlags, CPoint point);

	void		BeginDrag(NM_TREEVIEW* pNMTreeView);
	HTREEITEM	MoveChildItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter);

	void ShowProperties();

	void ShowSolutionPropertiesView(BOOL bComplete, BOOL showPane);
	void ShowProjectPropertiesView(BOOL bComplete, BOOL showPane);
	void ShowFolderPropertiesView(BOOL bComplete, BOOL showPane);
	void ShowItemPropertiesView(BOOL bComplete, BOOL showPane);
	
	void ShowItemDependencyFiles();

	void OpenFolderInFileExplorerSolution();
	void OpenFolderInFileExplorerProject();
	void OpenFolderInFileExplorerItem();

	void OpenFile();
	void OpenFileWith();

	void BuildSolution();
	void BuildProject(HTREEITEM item, BOOL clearOutput = TRUE);

	void EditCut();
	void EditCopy();
	void EditClear();
	void EditPaste();

	void AddNew();
	void AddNewItem(CProjectEntity* Project, CItemEntity *ItemAdd, CString folderID, CString PathFile, HTREEITEM hParentItem);
	void AddNewProject();
	void AddNewProject(CProjectEntity* Project, CString PathFile);
	void AddNewSolution();
	void AddNewItemFromProject(HTREEITEM hItemselected);
	void AddNewItemFromFolder(HTREEITEM hItemselected);
	void AddNewDependency(HTREEITEM hItemselected);

	void AddExisting();
	void AddExistingProject();
	void AddExistingItemFromProject(HTREEITEM hItemselected);
	void AddExistingItemFromFolder(HTREEITEM hItemselected);
	void AddExistingDependency(HTREEITEM hItemselected);


	void AddFolder();
	void AddProjectFolder(HTREEITEM hItemselected);

	BOOL ExistsItem(CProjectEntity* project, CString itemName);

	void Build();
	void Generate();
	void ConfigurationManager();
	void OpenFolderInFileExplorer();
	
	void Rename();
	void EndLabelEdit(TV_DISPINFO* pTVDispInfo);	
	void RenameSolution(CString solutionName);
	void RenameProject(CString projectName);
	void RenameFolder(CString folderName);
	void RenameItem(CString itemName);

	void Remove();
	void RemoveProject(HTREEITEM hItemselected);
	void RemoveFolder(HTREEITEM hItemselected);
	void RemoveItem(HTREEITEM hItemselected);
	void RemoveDependency(HTREEITEM hItemselected);

	void CloseSolution();
	void CloseAllDocuments(CString dllName);

	void GenerateItem();

	void SaveProject(HTREEITEM hItemselected);
	void SaveSolution();
	void SaveSolutionAndAllProjects();

	void InitVars();
	HTREEITEM GetItemSelected();

	void SendOutPutMessage(HWND hwndOutput, CString message);
	//Properties
public:
	PROPERTY(CSolutionEntity*, SolutionEntity)
  	GET(SolutionEntity) 
 	{ 
 		return m_solution; 
	}
 	SET(SolutionEntity)
 	{
 		m_solution = value;
 	} 

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

	// Private Members
private:
	CPropertiesWnd*		m_wndproperties;
	COutputWnd*			m_wndOutput;
	CSolutionEntity*	m_solution;
	HTREEITEM			m_hItemselected;
	HTREEITEM			m_hContextMenuItemselected;

	BOOL				m_buildnextproject;
	BOOL				m_buildprojectresultok;
	BOOL				m_stopbuild;

protected:
	CImageList*	m_pDragImage;
	BOOL		m_bLDragging;
	HTREEITEM	m_hitemDrag,m_hitemDrop;
	BOOL		m_bEditLabelMode;
};

