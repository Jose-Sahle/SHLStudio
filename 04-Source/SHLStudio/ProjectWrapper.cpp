/* ***************************************************************************
 * Arquivo: ProjectWrapper.cpp                                               *
 *                                                                           *
 * Classe criada encapsular operações de soluções e projetos do SHLStudio    *
 *                                                                           *
 * Data:26/03/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#include "stdafx.h"
#include "ProjectWrapper.h"
#include "Markup.h"
#include "Library.h"
#include "FolderEntity.h"
#include "Resource.h"

CProjectWrapper::CProjectWrapper(void)
{
	CPath path;
	m_TemplatesProjectItemDirectory  = ::GetApplicationDirectory();
	m_TemplatesProjectItemDirectory += _T("Templates\\");
	path.SetPath(m_TemplatesProjectItemDirectory);
	m_TemplatesProjectItemDirectory = path.GetPath();

	m_BinaryDirectory  = ::GetApplicationDirectory();
	m_BinaryDirectory += _T("Binaries\\");
	path.SetPath(m_BinaryDirectory);
	m_BinaryDirectory = path.GetPath();
}


CProjectWrapper::~CProjectWrapper(void)
{
}


ICtrlDir * CProjectWrapper::GetCtrlDir(HMODULE &h_mod)
{
	ICtrlDir *ptrCltrDir = NULL;
	LPFNGETCTRLDIRINSTANCE pCtrlDirIntance;
	CString strCtrlDirDLL;
	CString dll;
	CPath path;

	try
	{
		dll = _T("SHLDir32u.dll");

		path.AddPath(2, m_BinaryDirectory, dll);
		strCtrlDirDLL = path.GetPath();

		h_mod = ::LoadLibrary (strCtrlDirDLL);
	
		if(!h_mod)
			throw -1;

		pCtrlDirIntance = (LPFNGETCTRLDIRINSTANCE)::GetProcAddress(h_mod, "GetCtrlDirInstance");
		ptrCltrDir = (CTRLDIRHANDLE)pCtrlDirIntance();
	}
	catch(...)
	{
		CString errorMessage;
		errorMessage.Format(_T("%s\\%s not be found!\n\nThe will be terminate!"), m_BinaryDirectory, dll);
		::MessageBox(NULL, errorMessage, _T("Error: Load library"), MB_OK);
		exit(-10);
	}

	return ptrCltrDir;
}

CSHLTreeNode<PROJECTITEMINFO>* CProjectWrapper::PopulateTreeViewProjectFileTemplate(CTreeCtrl& ctrlTreeView, CString projectType, SHLTYPEDLGPROJECTANDFILE type)
{
	CSHLTreeNode<PROJECTITEMINFO>* elements;

	try
	{
		switch(type)
		{
			case SHLTYPEDLGPROJECTANDFILE_PROJECT:
				elements = PopulateTreeViewProjectTemplate(ctrlTreeView);
				break;

			case SHLTYPEDLGPROJECTANDFILE_ITEM:
				elements = PopulateTreeViewItemTemplate(ctrlTreeView, projectType);
				break;

			case SHLTYPEDLGPROJECTANDFILE_DEPENDENCY:
				elements = PopulateTreeViewDependencyTemplate(ctrlTreeView, projectType);
				break;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error = CString(szMessage);
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}

	return elements;
}

CSHLTreeNode<PROJECTITEMINFO>* CProjectWrapper::PopulateTreeViewProjectTemplate(CTreeCtrl& ctrlTreeView)
{
	ICtrlDir *ptrCltrDir = NULL;
	ICtrlDir *ptrCltrDirProject = NULL;

	CString strTemplatePath;
	CString parentPath;
	HTREEITEM hItem;
	HTREEITEM hItemProject;

	CSHLTreeNode<FILEPATHINFO>* root;
	CSHLTreeNode<FILEPATHINFO>* rootProject;

	CPath path;

	HMODULE h_mod = NULL;

	CSHLTreeNode<PROJECTITEMINFO>* elements;

	PROJECTITEMINFO *projectiteminfo;

	try
	{
		elements = new CSHLTreeNode<PROJECTITEMINFO>();

		path.AddPath(2, m_TemplatesProjectItemDirectory, _T("*.*"));
		strTemplatePath = path.GetPath();

		ptrCltrDir = GetCtrlDir(h_mod);
		ptrCltrDirProject = GetCtrlDir(h_mod);

		ptrCltrDir->SetMask(strTemplatePath);
		ptrCltrDir->SetSearchInSub(FALSE);
		ptrCltrDir->SetIncludeMask(FALSE);
		ptrCltrDir->SetType(_A_DIR);
		ptrCltrDir->SetUseDate(FALSE);

		ptrCltrDir->Refresh();

		root = ptrCltrDir->GetFilePathInfo();

		hItem = ctrlTreeView.InsertItem(_T("Projects Types"), NULL, NULL, NULL);
			
		for(UINT nIndex = 0; nIndex < root->GetNodeCount(); nIndex++)
		{
			CString rootName = root->GetNodeAt(nIndex)->Name;
			path.AddPath(3, m_TemplatesProjectItemDirectory, rootName, _T("Project\\*.*"));
			strTemplatePath = path.GetPath();

			path.AddPath(3, m_TemplatesProjectItemDirectory, rootName, _T("Project"));
			parentPath = path.GetPath();

			ptrCltrDirProject->SetMask(strTemplatePath);
			ptrCltrDirProject->SetSearchInSub(TRUE);
			ptrCltrDirProject->SetIncludeMask(FALSE);
			ptrCltrDirProject->SetType(_A_DIR);
			ptrCltrDirProject->SetUseDate(FALSE);

			ptrCltrDirProject->Refresh();

			rootProject = ptrCltrDirProject->GetFilePathInfo();

			hItemProject = ctrlTreeView.InsertItem(root->GetNodeAt(nIndex)->Name, NULL, NULL, hItem);

			projectiteminfo = new PROJECTITEMINFO();
			projectiteminfo->TreeNode = hItemProject;
			projectiteminfo->Path = parentPath;
			elements->AddItem(projectiteminfo);

			MountTreeExplorer(ctrlTreeView, rootProject, hItemProject, elements, parentPath);

			ptrCltrDirProject->Clear();
		}

		ctrlTreeView.Expand(hItem, TVE_EXPAND);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error = CString(szMessage);
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}
	   
	if (ptrCltrDir)
		ptrCltrDir->Release();

	if(ptrCltrDirProject)
		ptrCltrDirProject->Release();

	if(h_mod)
		::FreeLibrary(h_mod);

	return elements;
}

CSHLTreeNode<PROJECTITEMINFO>* CProjectWrapper::PopulateTreeViewItemTemplate(CTreeCtrl& ctrlTreeView, CString projectType)
{
	ICtrlDir *ptrCltrDir = NULL;

	CString strTemplatePath;
	CString parentPath;
	HTREEITEM hItem;

	CSHLTreeNode<FILEPATHINFO>* root;
	CPath path;

	HMODULE h_mod = NULL;

	CSHLTreeNode<PROJECTITEMINFO>* elements;

	PROJECTITEMINFO *projectiteminfo;

	try
	{
		elements = new CSHLTreeNode<PROJECTITEMINFO>();

		path.AddPath(4, m_TemplatesProjectItemDirectory, projectType, _T("Item"), _T("*.*"));
		strTemplatePath = path.GetPath();

		path.AddPath(3, m_TemplatesProjectItemDirectory, projectType, _T("Item"));
		parentPath = path.GetPath();

		ptrCltrDir = GetCtrlDir(h_mod);

		ptrCltrDir->SetMask(strTemplatePath);
		ptrCltrDir->SetSearchInSub(TRUE);
		ptrCltrDir->SetIncludeMask(FALSE);
		ptrCltrDir->SetType(_A_DIR);
		ptrCltrDir->SetUseDate(FALSE);

		ptrCltrDir->Refresh();

		root = ptrCltrDir->GetFilePathInfo();

		hItem = ctrlTreeView.InsertItem(_T("Items Types"), NULL, NULL, NULL);		
		
		projectiteminfo = new PROJECTITEMINFO();
		projectiteminfo->TreeNode = hItem;
		projectiteminfo->Path = parentPath;
		elements->AddItem(projectiteminfo);

		MountTreeExplorer(ctrlTreeView, root, hItem, elements, parentPath);

		ctrlTreeView.Expand(hItem, TVE_EXPAND);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error = CString(szMessage);
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}
	   
	if(ptrCltrDir)
		ptrCltrDir->Release();

	if(h_mod)
		::FreeLibrary(h_mod);

	return elements;
}

CSHLTreeNode<PROJECTITEMINFO>* CProjectWrapper::PopulateTreeViewDependencyTemplate(CTreeCtrl& ctrlTreeView, CString projectType)
{
	ICtrlDir *ptrCltrDir = NULL;
	HMODULE h_mod = NULL;

	CString strTemplatePath;
	CString parentPath;
	HTREEITEM hItem;

	CSHLTreeNode<FILEPATHINFO>* root;
	CPath path;

	CSHLTreeNode<PROJECTITEMINFO>* elements;


	try
	{
		elements = new CSHLTreeNode<PROJECTITEMINFO>();

		path.AddPath(4, m_TemplatesProjectItemDirectory, projectType, _T("Dependency"), _T("*.*"));
		strTemplatePath = path.GetPath();

		path.AddPath(3, m_TemplatesProjectItemDirectory, projectType, _T("Dependency"));
		parentPath = path.GetPath();

		ptrCltrDir = GetCtrlDir(h_mod);

		ptrCltrDir->SetMask(strTemplatePath);
		ptrCltrDir->SetSearchInSub(TRUE);
		ptrCltrDir->SetIncludeMask(FALSE);
		ptrCltrDir->SetType(_A_DIR);
		ptrCltrDir->SetUseDate(FALSE);

		ptrCltrDir->Refresh();

		root = ptrCltrDir->GetFilePathInfo();

		hItem = ctrlTreeView.InsertItem(_T("Dependency Types"), NULL, NULL, NULL);
		
		MountTreeExplorer(ctrlTreeView, root, hItem, elements, parentPath);

		ctrlTreeView.Expand(hItem, TVE_EXPAND);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error = CString(szMessage);
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}
	   
	if(ptrCltrDir)
		ptrCltrDir->Release();

	if(h_mod)
		::FreeLibrary(h_mod);

	return elements;
}

void CProjectWrapper::MountTreeExplorer(CTreeCtrl& ctrlTreeView, CSHLTreeNode<FILEPATHINFO>* parentnode, HTREEITEM parenttreeitem, CSHLTreeNode<PROJECTITEMINFO>* elements, CString parentpath)
{
	HTREEITEM hItem;
	CPath path;

	for(UINT nIndex = 0; nIndex < parentnode->GetNodeCount(); nIndex++)
	{
		if(parentnode->GetNodeAt(nIndex)->Name != _T("Icons"))
		{
			hItem = ctrlTreeView.InsertItem(parentnode->GetNodeAt(nIndex)->Name, -1, -1, parenttreeitem);
		
			path.AddPath(2, parentpath, parentnode->GetNodeAt(nIndex)->Name);

			PROJECTITEMINFO *projectiteminfo = new PROJECTITEMINFO();
			projectiteminfo->TreeNode = hItem;
			projectiteminfo->Path = path.GetPath();
			elements->AddItem(projectiteminfo);

			if(parentnode->GetNodeAt(nIndex)->HasChild)
			{
				MountTreeExplorer(ctrlTreeView, parentnode->GetNodeAt(nIndex), hItem, elements, path.GetPath());		
				ctrlTreeView.Expand(hItem, TVE_EXPAND);
			}			
		}
	}
}

BOOL CProjectWrapper::SaveProject(CProjectEntity* project)
{
	BOOL bRet = FALSE;
	CMarkup xml = NULL;
	CFolderEntity* folder;
	CItemEntity* item;
	CItemEntity* dependency;
	CString strProjectFileName;
	CPath path;
	CString sPath;

	try
	{
		path.AddPath(2, project->Path, project->FileName);
		strProjectFileName = path.GetPath();

		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		xml.AddElem(_T("Settings"));

		xml.IntoElem();

		xml.AddElem(_T("Version"), project->Version);
		xml.AddElem(_T("Name"), project->Name);
		xml.AddElem(_T("Type"), project->Type);
		xml.AddElem(_T("Class"), project->ClassDll);
		xml.AddElem(_T("PropertyFile"), project->PropertyFile);
		xml.AddElem(_T("ICONProject"), project->Icon);

		for(UINT nIndexFolder = 0; nIndexFolder < project->Folders->GetItemCount(); nIndexFolder++)
		{
			folder = project->Folders->GetItemAt(nIndexFolder);

			xml.AddElem(_T("Folder"));

			xml.IntoElem();

			xml.AddElem(_T("Name"), folder->Name);
			xml.AddElem(_T("ID"), folder->ID);
			xml.AddElem(_T("Type"), folder->Type);
			xml.AddElem(_T("Parent"), folder->Parent);
			xml.AddElem(_T("ICON"), folder->Icon);

			xml.OutOfElem();
		}

		for(UINT nIndexItem = 0; nIndexItem < project->Items->GetItemCount(); nIndexItem++)
		{
			item = project->Items->GetItemAt(nIndexItem);

			xml.AddElem(_T("Item"));

			xml.IntoElem();

			xml.AddElem(_T("Name"), item->Name);
			xml.AddElem(_T("FolderID"), item->FolderID);
			xml.AddElem(_T("Type"), item->Type);
			xml.AddElem(_T("FileName"), item->FileName);
			xml.AddElem(_T("PathType"), item->PathType);
			if(item->PathType == _T("Relative"))
			{
				path.SetPath(item->Path);
				sPath = path.GetRelativePath(project->Path);
			}
			else
			{
				sPath = item->Path;
			}
			xml.AddElem(_T("Path"), sPath);
			xml.AddElem(_T("PropertyFile"), item->PropertyFile);
			xml.AddElem(_T("ICON"), item->Icon);

			if(item->Dependencies->GetItemCount() > 0)
			{
				xml.AddElem(_T("Dependency"));

				xml.IntoElem();

				for(UINT nIndexDependency = 0; nIndexDependency < item->Dependencies->GetItemCount(); nIndexDependency++)
				{
					dependency = item->Dependencies->GetItemAt(nIndexDependency);

					xml.AddElem(_T("File"));

					xml.IntoElem();

					xml.AddElem(_T("Name"), dependency->Name);
					xml.AddElem(_T("Type"), dependency->Type);
					xml.AddElem(_T("FileName"), dependency->FileName);
					xml.AddElem(_T("ICON"), dependency->Icon);

					xml.OutOfElem();
				}

				xml.OutOfElem();
			}

			xml.OutOfElem();
		}

		xml.Save(strProjectFileName);		

		bRet = TRUE;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error = CString(szMessage);
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}

	return bRet;
}

BOOL CProjectWrapper::SaveSolution(CSolutionEntity* solution, BOOL saveAllProjects)
{
	CProjectEntity* project;
	CString solutionFile;
	BOOL bRet = FALSE;
	CPath path;
	CString sPath;
	CMarkup xml;

	try
	{
		path.AddPath(2, solution->Path, solution->FileName);
		solutionFile = path.GetPath();

		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		xml.AddElem(_T("Settings"));

		xml.IntoElem();

		xml.AddElem(_T("Version"), solution->Version);
		xml.AddElem(_T("Name"), solution->Name);
		xml.AddElem(_T("Description"), solution->Description);

		for(UINT nIndexProject = 0; nIndexProject < solution->Projects->GetItemCount(); nIndexProject++)
		{
			project = solution->Projects->GetItemAt(nIndexProject);

			xml.AddElem(_T("Project"));
			
			xml.IntoElem();

			path.SetPath(project->Path);
			sPath = path.GetRelativePath(solution->Path);

			xml.AddElem(_T("ProjectName"), project->Name);
			xml.AddElem(_T("ProjectFileName"), project->FileName);
			xml.AddElem(_T("ProjectPath"), sPath);
			if(project->CanBuild)
				xml.AddElem(_T("CanBuild"), _T("1"));
			else
				xml.AddElem(_T("CanBuild"), _T("0"));

			xml.OutOfElem();

			if(saveAllProjects)
				SaveProject(project);
		}
		
		xml.Save(solutionFile);

		bRet = TRUE;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error = CString(szMessage);
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}

	return bRet;
}

bool CProjectWrapper::LoadSolution(CString strFullFileName, CTreeCtrl& ctrlTreeView, CSolutionEntity& solution, MAPICONS& mapIcons, CImageList& solutionViewImages)
{
	HTREEITEM hItemSolution;
	CMarkup xml = NULL;
	CString strAux;
	CProjectEntity* project;
	bool bRet = false;
	CPath Path;

	try
	{
		solution.Reset();
		ctrlTreeView.DeleteAllItems();

		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		if(!xml.Load(strFullFileName))
		{
			AfxMessageBox(xml.GetError());
			throw -1;
		}

		xml.FindChildElem(_T("Version"));
		strAux = xml.GetChildData();
		solution.Version = strAux;

		xml.FindChildElem(_T("Name"));
		strAux = xml.GetChildData();
		solution.Name = strAux;

		xml.FindChildElem(_T("Description"));
		strAux = xml.GetChildData();
		solution.Description = strAux;

		solution.Path     = GetPartOf(strFullFileName, _A_DIR);
		solution.FileName = GetPartOf(strFullFileName, _A_ARQ);

		hItemSolution = ctrlTreeView.InsertItem(solution.Name, 0, 0, NULL);
		ctrlTreeView.SetItemData(hItemSolution, ID_TREE_VIEW_TAB_SOLUTION);

		while(xml.FindChildElem(_T("Project")))
		{
			project = new CProjectEntity();

			xml.IntoElem();

			xml.FindChildElem(_T("ProjectName"));
			strAux = xml.GetChildData();
			project->Name = strAux;

			xml.FindChildElem(_T("ProjectFileName"));
			strAux = xml.GetChildData();
			project->FileName = strAux;

			xml.FindChildElem(_T("ProjectPath"));
			strAux = xml.GetChildData();
			Path.AddPath(2, solution.Path, strAux);
			project->Path = Path.GetPath();

			xml.FindChildElem(_T("CanBuild"));
			strAux = xml.GetChildData();
			if(strAux == _T("1"))
				project->CanBuild = true;
			else
				project->CanBuild = false;

			if(!AddProjectItems(project, ctrlTreeView, hItemSolution, mapIcons, solutionViewImages))
				throw -1;

			xml.OutOfElem();

			solution.Projects->AddItem(project);
		}

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error = CString(szMessage);

		solution.Reset();
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;

		solution.Reset();
	}

	return bRet;
}

bool CProjectWrapper::LoadIcons(MAPICONS& mapIcons, CImageList& solutionViewImages, MAPTYPEICONS& mapTypeIcons)
{
	bool bRet = false;
	
	CString typeProject;
	CString strName;
	CString strAuxEx;
	CString strAux;
	CMarkup xml = NULL;
	ICtrlDir *ptrCltrDir = NULL;
	ICtrlDir *ptrCltrDirIcons = NULL;
	HMODULE h_mod = NULL;
	HMODULE h_modICons = NULL;
	CPath path;
	CString strTemplatePath;
	CString strIcon;
	CBitmap bm;
	CString strFullFileName;
	CString strDir;
	int nIndex;

	try
	{
		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		path.AddPath(2, m_TemplatesProjectItemDirectory, _T("*.*"));
		strTemplatePath = path.GetPath();

		ptrCltrDir = GetCtrlDir(h_mod);
		ptrCltrDirIcons = GetCtrlDir(h_modICons);

		ptrCltrDir->SetMask(strTemplatePath);
		ptrCltrDir->SetSearchInSub(TRUE);
		ptrCltrDir->SetIncludeMask(FALSE);
		ptrCltrDir->SetType(_A_DIR);
		ptrCltrDir->SetUseDate(FALSE);

		ptrCltrDir->Refresh();

		ptrCltrDir->MoveFirst();
		while(!ptrCltrDir->Eof())
		{
			typeProject = GetPartOf(ptrCltrDir->GetExName(), _A_ARQ);
			path.AddPath(2, ptrCltrDir->GetExName(), _T("Icons.xml"));
			strTemplatePath = path.GetPath();

			ptrCltrDirIcons->SetMask(strTemplatePath);
			ptrCltrDirIcons->SetSearchInSub(TRUE);
			ptrCltrDirIcons->SetIncludeMask(FALSE);
			ptrCltrDirIcons->SetType(_A_ARQ);
			ptrCltrDirIcons->SetUseDate(FALSE);

			ptrCltrDirIcons->Refresh();

			ptrCltrDirIcons->MoveFirst();

			while(!ptrCltrDirIcons->Eof())
			{
				strFullFileName = ptrCltrDirIcons->GetExName();
				strDir = GetPartOf(strFullFileName, _A_DIR);

				if(!xml.Load(strFullFileName))
				{
					AfxMessageBox(xml.GetError());
					throw -1;
				}
				else
				{
					while(xml.FindChildElem(_T("ICON")))
					{
						xml.IntoElem();

						xml.FindChildElem(_T("NAME"));
						strName.Format(_T("%s-%s"), typeProject, xml.GetChildData());

						xml.FindChildElem(_T("FILENAME"));
						strAuxEx = xml.GetChildData();

						xml.FindChildElem(_T("ID"));
						strAux = xml.GetChildData();

						if(!mapTypeIcons.Lookup(strName, strAux))
						{
							mapTypeIcons[strName] =strAux;
						}

						if(!mapIcons.Lookup(strAux, nIndex))
						{				
							int nCount = solutionViewImages.GetImageCount();

							strIcon.Format(_T("%sIcons\\1_%s"), strDir, strAuxEx);
							if((bm.m_hObject=(HBITMAP)::LoadImage(NULL, strIcon, IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_LOADFROMFILE)) == NULL)
							{
								nIndex = GetLastError();
								CString errorMessage;
								errorMessage.Format(_T("%s\n\n%s"), ErrorMessage(nIndex), strIcon);
								::MessageBox(NULL, errorMessage, _T("Load Icons"), MB_OK);
								continue;
							}
							nIndex = solutionViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
							nCount = solutionViewImages.GetImageCount();
							mapIcons[strAux] = nIndex;

							strIcon.Format(_T("%sIcons\\2_%s"), strDir, strAuxEx);
							if((bm.m_hObject=(HBITMAP)::LoadImage(NULL, strIcon, IMAGE_BITMAP, IMAGELISTSIZESOLUTIONEXPLORER, IMAGELISTSIZESOLUTIONEXPLORER, LR_LOADFROMFILE)) == NULL)
							{
								nIndex = GetLastError();
								CString errorMessage = ErrorMessage(nIndex);
								AfxMessageBox(errorMessage);
								continue;
							}

							nIndex = solutionViewImages.Add(&bm, IMAGEMASKSOLUTIONEXPLORER);
							nCount = solutionViewImages.GetImageCount();
						}

						xml.OutOfElem();
					}
				}

				ptrCltrDirIcons->MoveNext();
			}

			ptrCltrDir->MoveNext();
		}

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error = CString(szMessage);
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}

	if(ptrCltrDir)
		ptrCltrDir->Release();

	if(ptrCltrDirIcons)
		ptrCltrDirIcons->Release();

	if(h_mod)
		::FreeLibrary(h_mod);

	if(h_modICons)
		::FreeLibrary(h_modICons);

	return bRet;
}

bool CProjectWrapper::AddProjectItems(CProjectEntity* project, CTreeCtrl& ctrlTreeView, HTREEITEM& hItemSolution, MAPICONS& mapIcons, CImageList& solutionViewImages)
{
	HTREEITEM hItemFile;
	HTREEITEM hItemProject;
	HTREEITEM hFolder;
	HTREEITEM hDependency;
	CMarkup xml = NULL;
	CString strAux, strAuxEx, strIcon;
	CItemEntity* item;
	CFolderEntity* folder;
	CItemEntity* dependency;

	bool bRet = false;
	int nIndexImage, nIndexSelectImage;
	CPath path;

	try
	{
		path.AddPath(2, project->Path, project->FileName);
		strAux = path.GetPath();

		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		if(!xml.Load(strAux))
		{
			AfxMessageBox(xml.GetError());
			throw -1;
		}

		xml.FindChildElem(_T("Version"));
		strAux = xml.GetChildData();
		project->Version = strAux;

		xml.FindChildElem(_T("Name"));
		strAux = xml.GetChildData();
		project->Name = strAux;

		xml.FindChildElem(_T("Type"));
		strAux = xml.GetChildData();
		project->Type = strAux;

		xml.FindChildElem(_T("Class"));
		strAux = xml.GetChildData();
		project->ClassDll = strAux;

		xml.FindChildElem(_T("PropertyFile"));
		strAux = xml.GetChildData();
		project->PropertyFile = strAux;

		xml.FindChildElem(_T("ICONProject"));
		strAux = xml.GetChildData();
		project->Icon = strAux;

		nIndexImage			= mapIcons[project->Icon];
		nIndexSelectImage	= nIndexImage + 1;

		hItemProject = ctrlTreeView.InsertItem(project->Name, nIndexImage, nIndexSelectImage, hItemSolution);
		ctrlTreeView.SetItemData(hItemProject, ID_TREE_VIEW_TAB_PROJECT);
		project->TreeNode = hItemProject;

		while(xml.FindChildElem(_T("Folder")))
		{
			xml.IntoElem();
			folder = new CFolderEntity();

			xml.FindChildElem(_T("Name"));
			strAux = xml.GetChildData();
			folder->Name = strAux;

			xml.FindChildElem(_T("ID"));
			strAux = xml.GetChildData();
			folder->ID = strAux;

			xml.FindChildElem(_T("Type"));
			strAux = xml.GetChildData();
			folder->Type = strAux;

			xml.FindChildElem(_T("Parent"));
			strAux = xml.GetChildData();
			folder->Parent = strAux;

			xml.FindChildElem(_T("ICON"));
			strAux = xml.GetChildData();
			folder->Icon = strAux;

			nIndexImage			= mapIcons[folder->Icon];
			nIndexSelectImage	= nIndexImage + 1;
			hFolder = ctrlTreeView.InsertItem(folder->Name, nIndexImage, nIndexSelectImage, hItemProject);
			folder->TreeItem = hFolder;
			ctrlTreeView.SetItemData(hFolder, ID_TREE_VIEW_TAB_FOLDER);

			project->Folders->AddItem(folder);
			
			xml.OutOfElem();
		}

		while(xml.FindChildElem(_T("Item")))
		{
			item = new CItemEntity();

			item->Project = project;

			xml.IntoElem();

			xml.FindChildElem(_T("Name"));
			strAux = xml.GetChildData();
			item->Name = strAux;

			xml.FindChildElem(_T("FolderID"));
			strAux = xml.GetChildData();
			item->FolderID = strAux;

			xml.FindChildElem(_T("Type"));
			strAux = xml.GetChildData();
			item->Type = strAux;

			xml.FindChildElem(_T("FileName"));
			strAux = xml.GetChildData();
			item->FileName = strAux;

			xml.FindChildElem(_T("PathType"));
			strAux = xml.GetChildData();
			item->PathType = strAux;

			xml.FindChildElem(_T("Path"));
			strAux = xml.GetChildData();
			if(item->PathType == _T("Relative"))
			{
				path.AddPath(2, project->Path, strAux);
				strAux = path.GetPath();
			}
			item->Path = strAux;

			xml.FindChildElem(_T("PropertyFile"));
			strAux = xml.GetChildData();
			item->PropertyFile = strAux;

			xml.FindChildElem(_T("ICON"));
			strAux = xml.GetChildData();
			item->Icon = strAux;

			nIndexImage			= mapIcons[item->Icon];
			nIndexSelectImage	= nIndexImage + 1;

			if(item->FolderID == _T(""))
				hItemFile = ctrlTreeView.InsertItem(item->Name, nIndexImage, nIndexSelectImage, hItemProject);
			else
			{
				hFolder = GetFolderTree(project->Folders, item->FolderID);
				hItemFile = ctrlTreeView.InsertItem(item->Name, nIndexSelectImage, nIndexSelectImage, hFolder);
			}

			ctrlTreeView.SetItemData(hItemFile, ID_TREE_VIEW_TAB_ITEM);
			item->TreeNode = hItemFile;

			while(xml.FindChildElem(_T("Dependency")))
			{
				xml.IntoElem();

				while(xml.FindChildElem(_T("File")))
				{
					dependency = new CItemEntity();

					dependency->Project = project;

					xml.IntoElem();

					dependency->Path = item->Path;

					xml.FindChildElem(_T("Name"));
					strAux = xml.GetChildData();
					dependency->Name = strAux;

					xml.FindChildElem(_T("Type"));
					strAux = xml.GetChildData();
					dependency->Type = strAux;

					xml.FindChildElem(_T("FileName"));
					strAux = xml.GetChildData();
					dependency->FileName = strAux;

					xml.FindChildElem(_T("ICON"));
					strAux = xml.GetChildData();
					dependency->Icon = strAux;

					nIndexImage			= mapIcons[dependency->Icon];
					nIndexSelectImage	= nIndexImage + 1;

					hDependency = ctrlTreeView.InsertItem(dependency->Name, nIndexSelectImage, nIndexSelectImage, hItemFile);

					dependency->TreeNode = hDependency;
					item->Dependencies->AddItem(dependency);
					ctrlTreeView.SetItemData(hDependency, ID_TREE_VIEW_TAB_DEPENDENCY);

					xml.OutOfElem();
				}

				xml.OutOfElem();
			}

			xml.OutOfElem();

			project->Items->AddItem(item);
		}

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error = CString(szMessage);
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}

	return bRet;
}

HTREEITEM CProjectWrapper::GetFolderTree(CSHLTreeNode<CFolderEntity>* Folders, CString strfolderID)
{
	HTREEITEM hItem = NULL;
	UINT nCount;
	UINT nIndex;
	CString strID;

	try
	{
		nCount = Folders->GetItemCount();

		for(nIndex = 0; nIndex < nCount; nIndex++)
		{
			strID = Folders->GetItemAt(nIndex)->ID;
			if(strfolderID == strID)
			{
				hItem = Folders->GetItemAt(nIndex)->TreeItem;
				break;
			}
		}
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}

	return hItem;
}

CProjectEntity* CProjectWrapper::GetProject(CSolutionEntity* solution, HTREEITEM hItemselected)
{
	BOOL bFound = FALSE;
	CProjectEntity* Project = NULL;
	CFolderEntity* folder;
	CItemEntity* item;
	CItemEntity* dependency;

	try
	{
		for(UINT nIndex = 0; nIndex < solution->Projects->GetItemCount(); nIndex++)
		{
			Project = solution->Projects->GetItemAt(nIndex);
			if(Project->TreeNode == hItemselected)
				break;

			for(UINT nIndexFolder = 0;nIndexFolder < Project->Folders->GetItemCount(); nIndexFolder++)
			{
				folder = Project->Folders->GetItemAt(nIndexFolder);
				if(folder->TreeItem == hItemselected)
				{
					bFound = TRUE;
					break;
				}
			}

			if(bFound)
				break;

			for(UINT nIndexItem = 0;nIndexItem < Project->Items->GetItemCount(); nIndexItem++)
			{
				item = Project->Items->GetItemAt(nIndexItem);
				if(item->TreeNode == hItemselected)
				{
					bFound = TRUE;
					break;
				}
				else
				{
					for(UINT nIndexDependency = 0;nIndexDependency < item->Dependencies->GetItemCount(); nIndexDependency++)
					{
						dependency = item->Dependencies->GetItemAt(nIndexDependency);
						if(dependency->TreeNode == hItemselected)
						{
							bFound = TRUE;
							break;
						}
					}

					if(bFound)
						break;
				}
			}

			if(bFound)
				break;

			Project = NULL;
		}
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}

	return Project;
}

CItemEntity* CProjectWrapper::GetItem(CSolutionEntity* solution, HTREEITEM hItemselected)
{
	CProjectEntity* Project = NULL;
	CItemEntity* Item = NULL;
	CItemEntity* Dependency = NULL;
	CItemEntity* RetItem = NULL;

	bool bFound = false;

	try
	{
		for(UINT nIndexProject = 0; nIndexProject < solution->Projects->GetItemCount(); nIndexProject++)
		{
			Project = solution->Projects->GetItemAt(nIndexProject);

			for(UINT nIndexItem = 0; nIndexItem < Project->Items->GetItemCount(); nIndexItem++)
			{
				Item = Project->Items->GetItemAt(nIndexItem);

				if(Item->TreeNode == hItemselected)
				{
					RetItem = Item;
					bFound = true;
					break;
				}

				if(Item->Dependencies->GetItemCount())
				{					
					for(UINT nIndexDependency = 0; nIndexDependency < Item->Dependencies->GetItemCount(); nIndexDependency++)
					{
						Dependency = Item->Dependencies->GetItemAt(nIndexDependency);

						if(Dependency->TreeNode == hItemselected)
						{
							RetItem = Dependency;
							bFound = true;
							break;
						}
					}
				}

				if (bFound)
					break;
			}

			if (bFound)
				break;

		}
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}

	return RetItem;
}

CFolderEntity* CProjectWrapper::GetFolder(CSolutionEntity* solution, HTREEITEM hItemselected)
{
	CProjectEntity* Project = NULL;
	CFolderEntity* folder = NULL;
	CFolderEntity* RetFolder = NULL;

	bool bFound = false;

	try
	{
		for(UINT nIndexProject = 0; nIndexProject < solution->Projects->GetItemCount(); nIndexProject++)
		{
			Project = solution->Projects->GetItemAt(nIndexProject);

			for(UINT nIndexItem = 0; nIndexItem < Project->Folders->GetItemCount(); nIndexItem++)
			{
				folder = Project->Folders->GetItemAt(nIndexItem);

				if(folder->TreeItem == hItemselected)
				{
					RetFolder = folder;
					bFound = true;
					break;
				}

				if (bFound)
					break;
			}

			if (bFound)
				break;
		}
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}

	return RetFolder;
}

CString CProjectWrapper::SelectFile(CString strFileName, CString strDefaultExt, CString strFilter)
{
	CFileDialog* dlg = NULL;
	int iRet;
	CString strFullFileName = _T("");

	try
	{
		dlg = new CFileDialog(TRUE, strFileName, strDefaultExt, OFN_READONLY, strFilter);

		iRet = dlg->DoModal();

		if(iRet == IDOK)
			strFullFileName = dlg->GetPathName();
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}

	if(dlg)
		delete dlg;

	return strFullFileName;
}

CProjectEntity* CProjectWrapper::LoadProject(CSolutionEntity* solution, CString SolutionFullName)
{
	CPath path;
	CProjectEntity* Project = NULL;

	try
	{
		path.SetPath(SolutionFullName);
		if(!path.ExistFile())
		{
			CString msg;
			msg.Format(_T("File %s don't exists."), SolutionFullName);
			AfxMessageBox(msg);
			return NULL;
		}

		Project = new CProjectEntity();
		Project->FileName = path.GetFileName();
		Project->Path = path.GetLocation();
		Project->CanBuild = true;
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
		AfxMessageBox(m_Error);

		if(Project)
			delete Project;

		Project = NULL;
	}

	return Project;
}