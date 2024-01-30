/* ***************************************************************************
 * Arquivo: DlgProjectAndFile.h                                              *
 *                                                                           *
 * Classe de tela criada para criar uma nova solução no SHLStudio.           *
 *                                                                           *
 * Data:26/03/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "afxcmn.h"
#include "afxwin.h"
#include "bpctrlanchormap.h"
#include "Property.h"
#include "SHLTreeNode.h"
#include "ProjectEntity.h"
#include "ItemEntity.h"

// CDlgProjectAndFile dialog

class CDlgProjectAndFile : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProjectAndFile)
	DECLARE_ANCHOR_MAP();

public:
	CDlgProjectAndFile(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgProjectAndFile();

// Dialog Data
	enum { IDD = IDD_DIALOG_NEW_PROJECT_AND_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	int		m_nMinSizeY;
	int		m_nMinSizeX;

	CTreeCtrl m_ctrlGroupProjectItem;
	CListCtrl m_ctrlProjectItem;
	CRichEditCtrl m_txtDescription;
	CEdit m_txtName;
	CEdit m_txtLocation;
	CComboBox m_cmbCategory;
	
	CButton m_cmdBrowse;

	CImageList* m_image;

	CString	m_targetPath;
	CString m_projectType;
	SHLTYPEDLGPROJECTANDFILE m_dialogType;

	HTREEITEM m_hItemselected;

	CSHLTreeNode<PROJECTITEMINFO>* m_elements;

	CItemEntity* m_Item;	
	CProjectEntity* m_Project;
	CSHLTreeNode<CItemEntity>* m_ItemList;
	CSHLTreeNode<CProjectEntity>* m_ProjectList;

	MAPICONS* m_mapIcons;

public:
 	PROPERTY(CString, TargetPath)
  	GET(TargetPath) 
 	{ 
 		return m_targetPath; 
	}
 	SET(TargetPath)
 	{
 		m_targetPath = value;
 	} 

 	PROPERTY(CString, ProjectType)
  	GET(ProjectType) 
 	{ 
 		return m_projectType; 
	}
 	SET(ProjectType)
 	{
 		m_projectType = value;
 	} 

 	PROPERTY(SHLTYPEDLGPROJECTANDFILE, DialogType)
  	GET(DialogType) 
 	{ 
 		return m_dialogType; 
	}
 	SET(DialogType)
 	{
 		m_dialogType = value;
 	} 

 	PROPERTY(CImageList*, ImageList)
  	GET(ImageList) 
 	{ 
 		return m_image; 
	}
 	SET(ImageList)
 	{
 		m_image = value;
 	} 

	
 	PROPERTY(MAPICONS*, MapIcons)
  	GET(MapIcons) 
 	{ 
 		return m_mapIcons; 
	}
 	SET(MapIcons)
 	{
 		m_mapIcons = value;
 	} 

 	READONLY_PROPERTY(CProjectEntity*, Project)
  	GET(Project) 
 	{ 
 		return m_Project; 
	}

 	READONLY_PROPERTY(CItemEntity*, Item)
  	GET(Item) 
 	{ 
 		return m_Item; 
	}
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonBrowserLocation();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedOk();

	afx_msg void OnButtonDown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCbnSelchangeComboCategory();
	afx_msg void OnNMClickListProjectFile(NMHDR *pNMHDR, LRESULT *pResult);

private:
	void Release();

	void BrowserLocation();

	void SelectProjectItemTemplate();
	void SetDialog();
	HTREEITEM GetItemSelected();

	void ButtonDown(HTREEITEM hItemSelected);
	PROJECTITEMINFO* GetProjectItemInfo(HTREEITEM hItemSelected);

	void ShowProjectTemplates(HTREEITEM hItemSelected);
	void ShowItemTemplates(HTREEITEM hItemSelected);
	void ShowDependencyTemplates(HTREEITEM hItemSelected);

	void CategorySelChanged();
	void ProjectCategorySelChanged();
	void ItemCategorySelChanged();
	void DependencyCategorySelChanged();

	void SelectedList();
	void ProjectSelectedList();
	void ItemSelectedList();
	void DependencySelectedList();

	CItemEntity* GetItem(int nIndex);
	CProjectEntity* GetProject(int nIndex);

	BOOL AddNew();
	BOOL ProjectAddNew();
	BOOL ItemAddNew();
	BOOL DependencyAddNew();
};
