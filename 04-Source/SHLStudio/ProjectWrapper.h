/* ***************************************************************************
 * Arquivo: ProjectWrapper.h                                                 *
 *                                                                           *
 * Classe criada encapsular operações de soluções e projetos do SHLStudio    *
 *                                                                           *
 * Data:26/03/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

#include "FileDirectoryInfo.h"
#include "ICtrlDir.h"
#include "Property.h"
#include "SHLTreeNode.h"
#include "SolutionEntity.h"

class CProjectWrapper
{
public:
	CProjectWrapper(void);
	virtual ~CProjectWrapper(void);

public:
 	READONLY_PROPERTY(CString, Error)
  	GET(Error) 
 	{ 
 		return m_Error; 
	}

private:
	CString m_TemplatesProjectItemDirectory;
	CString m_BinaryDirectory;
	CString m_Error;

public:
	CSHLTreeNode<PROJECTITEMINFO>* PopulateTreeViewProjectFileTemplate(CTreeCtrl& ctrlTreeView, CString projectType, SHLTYPEDLGPROJECTANDFILE type);
	CSHLTreeNode<PROJECTITEMINFO>* PopulateTreeViewProjectTemplate(CTreeCtrl& ctrlTreeView);
	CSHLTreeNode<PROJECTITEMINFO>* PopulateTreeViewItemTemplate(CTreeCtrl& ctrlTreeView, CString projectType);
	CSHLTreeNode<PROJECTITEMINFO>* PopulateTreeViewDependencyTemplate(CTreeCtrl& ctrlTreeView, CString projectType);
	void MountTreeExplorer(CTreeCtrl& ctrlTreeView, CSHLTreeNode<FILEPATHINFO>* parentnode, HTREEITEM parenttreeitem, CSHLTreeNode<PROJECTITEMINFO>* elements, CString parentpath);

	bool LoadSolution(CString strFullFileName, CTreeCtrl& ctrlTreeView, CSolutionEntity& solution, MAPICONS& mapIcons, CImageList& solutionViewImages);
	bool LoadIcons(MAPICONS& mapIcons, CImageList& solutionViewImages, MAPTYPEICONS& mapTypeIcons);
	bool AddProjectItems(CProjectEntity* project, CTreeCtrl& ctrlTreeView, HTREEITEM& hItemSolution, MAPICONS& mapIcons, CImageList& solutionViewImages);

	BOOL SaveProject(CProjectEntity* project);
	BOOL SaveSolution(CSolutionEntity* solution, BOOL saveAllProjects);

	CProjectEntity* GetProject(CSolutionEntity* solution, HTREEITEM hItemselected);
	CItemEntity* GetItem(CSolutionEntity* solution, HTREEITEM hItemselected);
	CFolderEntity* GetFolder(CSolutionEntity* solution, HTREEITEM hItemselected);

	CString SelectFile(CString strFileName, CString strDefaultExt, CString strFilter);
	CProjectEntity* LoadProject(CSolutionEntity* solution, CString SolutionFullName);

private:
	HTREEITEM GetFolderTree(CSHLTreeNode<CFolderEntity>* Folders, CString strfolderID);
	ICtrlDir * GetCtrlDir(HMODULE &h_mod);

	void BeginWaitCursor();
	void EndWaitCursor();
};

