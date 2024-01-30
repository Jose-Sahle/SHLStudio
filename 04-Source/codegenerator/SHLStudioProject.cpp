/* ***************************************************************************
 * Arquivo: SHLStudioProject.cpp                                             *
 *                                                                           *
 * Classe plugin de funcionalidade para o SHLStudio                          *
 *                                                                           *
 * Data:29/04/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#include "stdafx.h"

#include "SHLStudioProject.h"

#include "SHLTemplateStateToRead.h"

#include "Library.h"

#include "Markup.h"

#include "ProjectPropertyView.h"
#include "ProjectPropertyDoc.h"
#include "MFCPropertyGridPropertyMask.h"

#include "SHLQueryScintillaDoc.h"
#include "SHLQueryScintillaView.h"
#include "SHLChildScintillaFrm.h"

#include "GenericChildFrame.h"
#include "GenericDoc.h"
#include "DatabaseItemGenerateView.h"

#if !defined(_WIN64)
// This pragma is required only for 32-bit builds. In a 64-bit environment,
// C functions are not decorated.
#pragma comment(linker, "/export:GetSHLStudioProjectInstance=_GetSHLStudioProjectInstance@0")
#endif  // _WIN64

//static AFX_EXTENSION_MODULE classgeneratorsqlserverDLL = { NULL, NULL };

CSHLStudioProject::CSHLStudioProject(void)
{
	#ifdef _DEBUG
		m_hSciDLL = ::LoadLibraryFromApplicationDirectory(_T("SciLexer32ud.dll"), _T("Binaries"));
	#else
		m_hSciDLL = ::LoadLibraryFromApplicationDirectory(_T("SciLexer32u.dll"), _T("Binaries"));
	#endif
	if (m_hSciDLL == NULL)
	{ 
		m_hSciDLL = NULL;
		AfxMessageBox(_T("Scintilla DLL is not installed, Please download the SciTE editor and copy the SciLexer.dll into this application's directory"));
	}	
}

CSHLStudioProject::~CSHLStudioProject(void)
{
}

#pragma region PUBLIC_METHODS
bool CSHLStudioProject::GetDocumentTemplate(SHLSTUDIOMETHODS Method, PSHLSTUDIOARGLIST Arguments, CSolutionEntity *solution, CProjectEntity* Project, CItemEntity* Item, CRuntimeClass*& frame, CRuntimeClass*& view, CRuntimeClass*& docment)
{
	bool bRet = false;

	try
	{
		switch(Method)
		{
			case SHLSTUDIOMETHODS_LOADPROJECTPROPERTIES:
				bRet = LoadProjectProperties(Project, frame, view, docment);
				break;
			case SHLSTUDIOMETHODS_LOAGENERATEITEM:
				bRet = LoadGenerateItem(Project, Item, frame, view, docment);
				break;
			case SHLSTUDIOMETHODS_LOADEDITITEM:
				bRet = LoadEditItem(Project, Item, frame, view, docment);
				break;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLStudioProject::RunMethods(SHLSTUDIOMETHODS Method, PSHLSTUDIOARGLIST Arguments)
{
	bool bRet = false;

	try
	{
		switch(Method)
		{
			case SHLSTUDIOMETHODS_SETPROJECTROPERTIES:
				{
					CProjectEntity* Project = (CProjectEntity*)Arguments->GetItemAt(0);
					CDocument* document = (CDocument*)Arguments->GetItemAt(1);
					bRet = SetProjectProperties(Project, document);
				}
				break;
			case SHLSTUDIOMETHODS_SETITEMPROPERTIES:
				{
					CProjectEntity* Project = (CProjectEntity*)Arguments->GetItemAt(0);
					CItemEntity* Item = (CItemEntity*)Arguments->GetItemAt(1);
					CDocument* document = (CDocument*)Arguments->GetItemAt(2);
					bool newWindow = *((bool*)Arguments->GetItemAt(3));
					bRet = SetItemProperties(Project, Item, document, newWindow);
				}
				break;
			case SHLSTUDIOMETHODS_GENERATEITEM:
				{
					CProjectEntity* Project = (CProjectEntity*)Arguments->GetItemAt(0);
					CItemEntity* Item = (CItemEntity*)Arguments->GetItemAt(1);
					HWND  hwndOutput = *((HWND*)Arguments->GetItemAt(2));
					bRet = GenerateItem(Project, Item, hwndOutput);
				}
				break;
			case SHLSTUDIOMETHODS_SETGENERATEITEM:
				{
					CProjectEntity* Project = (CProjectEntity*)Arguments->GetItemAt(0);
					CItemEntity* Item = (CItemEntity*)Arguments->GetItemAt(1);
					CDocument* document = (CDocument*)Arguments->GetItemAt(2);
					bRet = SetGenerateItem(Project, Item, document);
				}
				break;
			case SHLSTUDIOMETHODS_LOADPROPERTYPROJECT:
				{
					CString&  propertyfile = *((CString*)Arguments->GetItemAt(0));
					PROPERTYVALUE& Properties = *((PROPERTYVALUE*)Arguments->GetItemAt(1));
					HWND  hwndOutput = *((HWND*)Arguments->GetItemAt(2));
					bRet = LoadPropertyProject(propertyfile, Properties, hwndOutput);
				}
				break;
			case SHLSTUDIOMETHODS_LOADPROPERTYFILE:
				{
					CString&  propertyfile = *((CString*)Arguments->GetItemAt(0));
					PROPERTYVALUE& Properties = *((PROPERTYVALUE*)Arguments->GetItemAt(1));
					HWND  hwndOutput = *((HWND*)Arguments->GetItemAt(2));
					bRet = LoadPropertyFile(propertyfile, Properties, hwndOutput);
				}
				break;
			case SHLSTUDIOMETHODS_LOADPROPERTIESITEM:
				{
					CProjectEntity* Project = (CProjectEntity*)Arguments->GetItemAt(0);
					CItemEntity* Item = (CItemEntity*)Arguments->GetItemAt(1);
					CMFCPropertyGridCtrl& wndPropList = *((CMFCPropertyGridCtrl*)Arguments->GetItemAt(2));					
					bRet = LoadPropertiesItem(Project, Item, wndPropList);
				}
				break;
			case SHLSTUDIOMETHODS_SAVEPROPERTIESITEM:
				{
					CItemEntity* Item = (CItemEntity*)Arguments->GetItemAt(0);
					bRet = SavePropertiesItem(Item);
				}
				break;
			case SHLSTUDIOMETHODS_BUILDPROJECT:
				{
					CProjectEntity* Project = (CProjectEntity*)Arguments->GetItemAt(0);
					HWND  hwndOutput = *((HWND*)Arguments->GetItemAt(1));
					bRet = BuildProject(Project, hwndOutput);
				}
				break;
			case SHLSTUDIOMETHODS_ADDEXISTINGITEMFROMPROJECT:
				{
					CProjectEntity* Project = (CProjectEntity*)Arguments->GetItemAt(0);
					CTreeCtrl& ctrlTreeView = *(CTreeCtrl*)Arguments->GetItemAt(1);
					MAPICONS& mapIcons = *(MAPICONS*)Arguments->GetItemAt(2);
					CImageList& solutionViewImages = *(CImageList*)Arguments->GetItemAt(3);
					bRet = AddExistingItemFromProject(Project, ctrlTreeView, mapIcons, solutionViewImages);
				}
				break;
			case SHLSTUDIOMETHODS_ADDEXISTINGITEMFROMFOLDER:
				{
					CProjectEntity* Project = (CProjectEntity*)Arguments->GetItemAt(0);
					CFolderEntity* folder = (CFolderEntity*)Arguments->GetItemAt(1);
					CTreeCtrl& ctrlTreeView = *(CTreeCtrl*)Arguments->GetItemAt(2);
					MAPICONS& mapIcons = *(MAPICONS*)Arguments->GetItemAt(3);
					CImageList& solutionViewImages = *(CImageList*)Arguments->GetItemAt(4);
					bRet = AddExistingItemFromFolder(Project, folder, ctrlTreeView, mapIcons, solutionViewImages);
				}
				break;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

CString CSHLStudioProject::GetLastError()
{
	return m_Error;
}

void CSHLStudioProject::Release()
{
	try
	{
		delete this;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}
}
#pragma endregion PUBLIC_METHODS

#pragma region PRIVATE_METHODS
bool CSHLStudioProject::AddExistingItem(CProjectEntity* Project, CTreeCtrl& ctrlTreeView, MAPICONS& mapIcons, CImageList& solutionViewImages, CString folderID, HTREEITEM hParent)
{
	bool bRet = false;

	CItemEntity* Item = NULL;
	CItemEntity* ItemDependency = NULL;

	CString strSolutionFullName;
	CString strSolutionFullNamePrt;
	CString strDefualt;
	CString strFilter;
	CString strFileName;
	CMarkup xml;
	CPath path;
	CString dependencyIcon, dependencyType;

	int nIndexImage, nIndexSelectImage;
	HTREEITEM hItemFile, hDependency;

	try
	{
		strFileName = _T("");
		strFilter = _T("C# Template Files (*.cs) |*.cs |SQL Script Template Files (*.sql) |*.sql | Metadatabase Template Files (*.dt) |*.dt | All files (*.*)||");
		strDefualt = _T("*.*");
		strSolutionFullName = SelectFile(strFileName, strDefualt, strFilter);

		if(strSolutionFullName == _T(""))
			return false;

		strSolutionFullNamePrt = strSolutionFullName + _T(".prt");
		path.SetPath(strSolutionFullNamePrt);
		if(!path.ExistFile())
		{
			CString msg;
			msg.Format(_T("Property file %s does not exists."), strSolutionFullNamePrt);
			AfxMessageBox(msg);
			return false;
		}
		strSolutionFullNamePrt = path.GetFileName();

		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		if(!xml.Load(path.GetPath()))
		{
			throw -1;
		}

		Item = new CItemEntity();

		Item->Project = Project;
		Item->Path = path.GetLocation();
		Item->PropertyFile = strSolutionFullNamePrt;;
		path.SetPath(strSolutionFullName);
		strSolutionFullName = path.GetFileName();

		Item->FileName = strSolutionFullName;
		strSolutionFullName.Replace(path.GetExtension(), _T(""));
		Item->Name = strSolutionFullName;
		Item->FolderID = folderID;

		xml.FindChildElem(_T("Type"));
		Item->Type = xml.GetChildData();
		xml.FindChildElem(_T("ICON"));
		Item->Icon = xml.GetChildData();

		Item->PathType = _T("Relative");

		nIndexImage			= mapIcons[Item->Icon];
		nIndexSelectImage	= nIndexImage + 1;

		hItemFile = ctrlTreeView.InsertItem(Item->Name, nIndexImage, nIndexSelectImage, hParent);
		Item->TreeNode = hItemFile;
		ctrlTreeView.SetItemData(hItemFile, ID_TREE_VIEW_TAB_ITEM);

		if(Item->Type == _T("CS"))
		{
		}
		else
		if(Item->Type == _T("C++"))
		{
		}
		else
		if(Item->Type == _T("AccessScript"))
		{
		}
		else
		if(Item->Type == _T("SQLServerScript"))
		{
		}
		else
		if(Item->Type == _T("MySQLScript"))
		{
		}
		else
		if(Item->Type == _T("PostGresScript"))
		{
		}
		else
		if(Item->Type == _T("OracleScript"))
		{
		}
		else
		if(Item->Type == _T("DT"))
		{
			CString strAux;

			xml.FindChildElem(_T("ICONDependency"));
			dependencyIcon = xml.GetChildData();

			xml.FindChildElem(_T("SQLServerScript"));
			dependencyType = xml.GetChildData();

			nIndexImage			= mapIcons[dependencyIcon];
			nIndexSelectImage	= nIndexImage + 1;

			xml.FindChildElem(_T("ConnectionDependencySelectCatalog"));
			strAux = xml.GetAttrib(_T("Value"));
			path.SetPath(strAux);
			strAux = path.GetPath();
			strAux.Replace(path.GetExtension(), _T(""));

			ItemDependency = new CItemEntity();
			ItemDependency->Name = strAux;
			ItemDependency->Type = dependencyType;
			ItemDependency->FileName = path.GetFileName();
			ItemDependency->Icon = dependencyIcon;
			ItemDependency->Project = Project;
			Item->Dependencies->AddItem(ItemDependency);

			hDependency = ctrlTreeView.InsertItem(ItemDependency->Name, nIndexSelectImage, nIndexSelectImage, hItemFile);
			ItemDependency->TreeNode = hDependency;
			ctrlTreeView.SetItemData(hDependency, ID_TREE_VIEW_TAB_DEPENDENCY);

			xml.FindChildElem(_T("ConnectionDependencySelectTable"));
			strAux = xml.GetAttrib(_T("Value"));
			path.SetPath(strAux);
			strAux = path.GetPath();
			strAux.Replace(path.GetExtension(), _T(""));

			ItemDependency = new CItemEntity();
			ItemDependency->Name = strAux;
			ItemDependency->Type = dependencyType;
			ItemDependency->FileName = path.GetFileName();
			ItemDependency->Icon = dependencyIcon;
			ItemDependency->Project = Project;
			Item->Dependencies->AddItem(ItemDependency);

			hDependency = ctrlTreeView.InsertItem(ItemDependency->Name, nIndexSelectImage, nIndexSelectImage, hItemFile);
			ItemDependency->TreeNode = hDependency;
			ctrlTreeView.SetItemData(hDependency, ID_TREE_VIEW_TAB_DEPENDENCY);

			xml.FindChildElem(_T("ConnectionDependencySelectColumn"));
			strAux = xml.GetAttrib(_T("Value"));
			path.SetPath(strAux);
			strAux = path.GetPath();
			strAux.Replace(path.GetExtension(), _T(""));

			ItemDependency = new CItemEntity();
			ItemDependency->Name = strAux;
			ItemDependency->Type = dependencyType;
			ItemDependency->FileName = path.GetFileName();
			ItemDependency->Icon = dependencyIcon;
			ItemDependency->Project = Project;
			Item->Dependencies->AddItem(ItemDependency);

			hDependency = ctrlTreeView.InsertItem(ItemDependency->Name, nIndexSelectImage, nIndexSelectImage, hItemFile);
			ItemDependency->TreeNode = hDependency;
			ctrlTreeView.SetItemData(hDependency, ID_TREE_VIEW_TAB_DEPENDENCY);
		}

		Project->Items->AddItem(Item);

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	if(!bRet)
	{
		if(Item)
			delete Item;
	}

	return bRet;
}

bool CSHLStudioProject::AddExistingItemFromProject(CProjectEntity* Project, CTreeCtrl& ctrlTreeView, MAPICONS& mapIcons, CImageList& solutionViewImages)
{
	bool bRet = false;

	try	
	{
		bRet = AddExistingItem(Project, ctrlTreeView, mapIcons, solutionViewImages, _T(""), Project->TreeNode);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLStudioProject::AddExistingItemFromFolder(CProjectEntity* Project, CFolderEntity* folder, CTreeCtrl& ctrlTreeView, MAPICONS& mapIcons, CImageList& solutionViewImages)
{
	bool bRet = false;

	try	
	{
		bRet = AddExistingItem(Project, ctrlTreeView, mapIcons, solutionViewImages, folder->ID, folder->TreeItem);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLStudioProject::BuildProject(CProjectEntity* Project, HWND hwndOutput)
{
	bool bRet = false;
	CItemEntity* Item;
	CPath path;
	CString projetPropertyFile;
	CString itemPropertyFile;
	CString pathType;
	CString strAppendFile;
	CString targetPath;

	CString key;

	bool bComplete = true;

	CString strMsg;

	try
	{
		do
		{			
			path.AddPath(2, Project->Path, Project->PropertyFile);
			if(!path.ExistFile())
			{
				strMsg.Format(_T("> Property Project file '%s' does not exists."), path.GetPath());
				SendOutPutMessage(hwndOutput, strMsg);
				strMsg = _T("> Build canceled.");
				SendOutPutMessage(hwndOutput, strMsg);

				break;
			}
			projetPropertyFile = path.GetPath();
			LoadPropertyProject(projetPropertyFile, Project->Properties, hwndOutput);

			for(UINT nIndexItem = 0; nIndexItem < Project->Items->GetItemCount(); nIndexItem++)
			{
				Item = Project->Items->GetItemAt(nIndexItem);

				if(Item->Type == _T("DT"))
					continue;

				path.AddPath(2, Item->Path, Item->PropertyFile);
				if(!path.ExistFile())
				{
					strMsg.Format(_T("> Property Item file '%s' does not exists."), path.GetPath());
					SendOutPutMessage(hwndOutput, strMsg);
					strMsg = _T("> Build canceled.");
					SendOutPutMessage(hwndOutput, strMsg);

					bComplete = false;
					break;
				}
				itemPropertyFile = path.GetPath();
				if(!LoadPropertyFile(itemPropertyFile, Item->Properties, hwndOutput))
				{
					strMsg.Format(_T("> Can not load property item file."), itemPropertyFile);
					SendOutPutMessage(hwndOutput, strMsg);
					strMsg = _T("> Build canceled.");
					SendOutPutMessage(hwndOutput, strMsg);

					bComplete = false;
					break;
				}

				key = _T("PathType");
				pathType = Item->Properties[key];
				if(pathType.IsEmpty())
				{
					strMsg.Format(_T("> Propety 'PathType' is emtpy."));
					SendOutPutMessage(hwndOutput, strMsg);
					strMsg = _T("> Build canceled.");
					SendOutPutMessage(hwndOutput, strMsg);

					bComplete = false;
					break;
				}
				else
				{
					if(pathType != _T("Absolute") && pathType != _T("Relative"))
					{
						strMsg.Format(_T("> Propety 'PathType' is invalid. Permitted values are: 'Absolute' or 'Relative'. Property value is assign with '%s'"), pathType);
						SendOutPutMessage(hwndOutput, strMsg);
						strMsg = _T("> Build canceled.");
						SendOutPutMessage(hwndOutput, strMsg);

						bComplete = false;
						break;
					}
				}

				key = _T("AppendFile");
				strAppendFile = Item->Properties[key];

				key = _T("TargetPath");
				targetPath = Item->Properties[key];
				if(targetPath.IsEmpty())
				{
					strMsg.Format(_T("> Propety 'TargetPath' is emtpy."));
					SendOutPutMessage(hwndOutput, strMsg);
					strMsg = _T("> Build canceled.");
					SendOutPutMessage(hwndOutput, strMsg);

					bComplete = false;
					break;
				}
				else
				{
					if(pathType == _T("Relative"))
					{
						path.AddPath(3, Project->Path, targetPath, _T(""));
						targetPath = path.GetPath();
					}
					else
					{
						path.AddPath(2, targetPath, _T(""));
					}

					if(!path.ExistLocation())
					{
						strMsg.Format(_T("> Propety 'TargetPath' is invalid path.'%s' does not exists. "), path.GetLocation());
						SendOutPutMessage(hwndOutput, strMsg);
						strMsg = _T("> Build canceled.");
						SendOutPutMessage(hwndOutput, strMsg);

						bComplete = false;
						break;
					}
				}

				path.AddPath(2, targetPath, strAppendFile);
				if(path.ExistFile())
				{
					DeleteFile(path.GetPath());
				}

			}

			if(!bComplete)
				break;

			for(UINT nIndexItem = 0; nIndexItem < Project->Items->GetItemCount(); nIndexItem++)
			{
				Item = Project->Items->GetItemAt(nIndexItem);

				if(Item->Type == _T("DT"))
					continue;

				if(!GenerateItem(Project, Item, hwndOutput))
				{
					bComplete = false;
					break;
				}
			}
		}while(false);

		bRet = bComplete;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;

		SendOutPutMessage(hwndOutput, m_Error);
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());

		SendOutPutMessage(hwndOutput, m_Error);
	}

	return bRet;
}

bool CSHLStudioProject::SavePropertiesItem(CItemEntity* Item)
{
	bool bRet = false;
	CMarkup xml = NULL;
	CString strFileName;

	POSITION	posProperties = NULL;
	CString		strRelationship;
	CString		value;
	CString		key;
	bool bFound = false;

	CPath path;

	try
	{
		path.AddPath(2, Item->Path, Item->PropertyFile);
		strFileName = path.GetPath();

		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		if(!xml.Load(strFileName))
		{
			throw -1;
		}

		posProperties = Item->Properties.GetStartPosition();

		while(posProperties != NULL)
		{
			Item->Properties.GetNextAssoc( posProperties, key, value );

			xml.ResetMainPos();
			xml.ResetPos();
			xml.ResetChildPos();

			bFound = false;

			while(xml.FindChildElem(_T("Group")))
			{
				xml.IntoElem();

				while(xml.FindChildElem(_T("Property")))
				{
					xml.IntoElem();

					CString strName = xml.GetAttrib(_T("Name"));

					if(strName == key)
					{
						xml.SetAttrib(_T("Value"), value);
						bFound = true;
						break;
					}

					xml.OutOfElem();
				}

				if(bFound)
					break;

				xml.OutOfElem();
			}
		}

		xml.Save(strFileName);

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error.Format(_T("WinError:%s\nXMLError:%s"), ErrorMessage(::GetLastError()), xml.GetError());
	}

	return bRet;
}

bool CSHLStudioProject::LoadPropertiesItem(CProjectEntity* Project, CItemEntity* Item, CMFCPropertyGridCtrl& wndPropList)
{
	bool bRet = false;
	CMFCPropertyGridProperty* pGroup;
	CMFCPropertyGridPropertyMask* pProp;
	CMarkup xml = NULL;
	CString strFileName;
	CPath path;

	try
	{
		wndPropList.RemoveAll();

		if(Item->PropertyFile == _T(""))
			return true;

		wndPropList.EnableHeaderCtrl(FALSE);
		wndPropList.EnableDescriptionArea();
		wndPropList.SetVSDotNetLook();
		wndPropList.MarkModifiedProperties();

		path.AddPath(2, Item->Path, Item->PropertyFile);
		strFileName = path.GetPath();		

		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		if(!xml.Load(strFileName))
		{
			throw -1;
		}

		while(xml.FindChildElem(_T("Group")))
		{
			xml.IntoElem();

			CString strGroupName		= xml.GetAttrib(_T("Name"));
			CString strGroupDescription	= xml.GetAttrib(_T("Description"));
			
			pGroup = new CMFCPropertyGridProperty(strGroupName);
			pGroup->SetDescription(strGroupDescription);

			while(xml.FindChildElem(_T("Property")))
			{
				xml.IntoElem();

				CString strName						= xml.GetAttrib(_T("Name"));
				CString strID						= xml.GetAttrib(_T("ID"));
				CString strCaption					= xml.GetAttrib(_T("Caption"));
				CString strType						= xml.GetAttrib(_T("Type"));
				CString strPropertyRelationship		= xml.GetAttrib(_T("PropertyRelationship"));
				CString strDescription				= xml.GetAttrib(_T("Description"));
				CString strValue					= xml.GetAttrib(_T("Value"));

				Item->Properties[strName] = strValue;
				
				pProp = new CMFCPropertyGridPropertyMask(strCaption, strValue, strDescription);

				pProp->GroupParent = pGroup;				
				pProp->BaseFolder  = Project->Path;
				pProp->Tag = strName;
				pProp->Relationship = strPropertyRelationship;
				
				if(strType == _T("Folder"))
				{
					pProp->IsFolder = TRUE;
					pProp->HASBUTTON = TRUE;
				}
				else
				if(strType == _T("Collection"))
				{
					pProp->HASBUTTON = TRUE;

					while(xml.FindChildElem(_T("Option")))
					{
						xml.IntoElem();

						CString strOption = xml.GetAttrib(_T("Value"));

						pProp->AddOption(strOption);

						xml.OutOfElem();
					}

					pProp->AllowEdit(FALSE);	
				}
				else
				if(strType == _T("Dependency"))
				{
					pProp->HASBUTTON = TRUE;
					for(UINT nIndex = 0; nIndex < Item->Dependencies->GetItemCount(); nIndex++)
					{
						CString strOption = Item->Dependencies->GetItemAt(nIndex)->Name;
						pProp->AddOption(strOption);
					}
				}
				else
				if(strType == _T("Password"))
				{
					pProp->PasswordChar = _T("*");
				}
				else
				if(strType == _T("Numeric"))
				{
					pProp->ValidChars = _T("0123456789");
				}
				else
				if(strType == __T("DynamicColletion-DT"))
				{
					pProp->HASBUTTON = TRUE;
					for(UINT nIndex = 0; nIndex < Project->Items->GetItemCount(); nIndex++)
					{
						if(Project->Items->GetItemAt(nIndex)->Type == _T("DT"))
						{
							CString dtName = Project->Items->GetItemAt(nIndex)->Name;
							pProp->AddOption(dtName);
						}
					}
				}

				pGroup->AddSubItem(pProp);

				xml.OutOfElem();
			}

			wndPropList.AddProperty(pGroup);

			xml.OutOfElem();
		}

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error.Format(_T("WinError:%s\nXMLError:%s"), ErrorMessage(::GetLastError()), xml.GetError());
	}

	return bRet;
}

bool CSHLStudioProject::LoadPropertyFile(CString propertyfile, PROPERTYVALUE& Properties, HWND  hwndOutput)
{
	bool bRet = false;

	CMarkup xml = NULL;
	CPath path;

	try
	{
		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		if(!xml.Load(propertyfile))
		{
			throw -1;
		}

		while(xml.FindChildElem(_T("Group")))
		{
			xml.IntoElem();

			while(xml.FindChildElem(_T("Property")))
			{
				xml.IntoElem();

				CString strName						= xml.GetAttrib(_T("Name"));
				CString strValue					= xml.GetAttrib(_T("Value"));

				Properties[strName] = strValue;
				

				xml.OutOfElem();
			}

			xml.OutOfElem();
		}

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error.Format(_T("WinError:%s\nXMLError:%s"), ErrorMessage(::GetLastError()), xml.GetError());
	}

	return bRet;
}

bool CSHLStudioProject::LoadPropertyProject(CString  propertyfile, PROPERTYVALUE& Properties, HWND  hwndOutput)
{
	bool bRet = false;
	CMarkup xml = NULL;
	CString strValue;
	CString strKey;

	try
	{
		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		if(!xml.Load(propertyfile))
		{
			throw -1;
		}

		strKey = _T("VERSION");
		xml.FindChildElem(strKey);
		strValue = xml.GetChildData();
		Properties[strKey] = strValue;

		strKey = _T("AUTHOR");
		xml.FindChildElem(strKey);
		strValue = xml.GetChildData();
		Properties[strKey] = strValue;

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error.Format(_T("WinError:%s\nXMLError:%s"), ErrorMessage(::GetLastError()), xml.GetError());
	}

	return bRet;
}

bool CSHLStudioProject::SetGenerateItem(CProjectEntity* Project, CItemEntity* Item, CDocument* document)
{
	bool bRet = false;
	CString strTitle;

	try
	{
		if(Item->Type == _T("DT"))
		{
			CGenericDoc* pDoc = (CGenericDoc*)document;

			strTitle = Item->Name;

			pDoc->SetTitle(strTitle);

			pDoc->View->SendMessage(WM_SET_PROJECT_ITEM, (WPARAM)Project, (LPARAM)Item);
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLStudioProject::GenerateItem(CProjectEntity* Project, CItemEntity* Item, HWND  hwndOutput)
{
	bool bRet = false;
	CString strTitle;
	CString strMsg;

	try
	{
		if(Item->Type != _T("DT"))
		{
			strMsg.Format(_T("> --------- Project: %s  - Item: %s -----------"), Project->Name, Item->Name);
			SendOutPutMessage(hwndOutput, strMsg);
			bRet = GenerateItemAllTypes(Project, Item, hwndOutput);
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLStudioProject::SetItemProperties(CProjectEntity* Project, CItemEntity* Item, CDocument* document, bool newWindow)
{
	bool bRet = false;
	CSHLQueryScintillaDoc* pPropertyDoc;
	CString strTitle;

	try
	{
		pPropertyDoc = (CSHLQueryScintillaDoc*)document;

		if(!newWindow)
		{
			pPropertyDoc->SetFocus();
			return true;
		}

		pPropertyDoc->SetChild();
		strTitle.Format(_T("%s"), Item->Name);

		pPropertyDoc->SetTitle(strTitle);

		if(Item->Type == _T("CS"))
		{
			pPropertyDoc->SetCPPScript();
			pPropertyDoc->SetFocus();
			bRet = true;
		}
		else
		if(Item->Type == _T("C++"))
		{
			pPropertyDoc->SetCPPScript();
			pPropertyDoc->SetFocus();
			bRet = true;
		}
		else
		if(Item->Type == _T("AccessScript"))
		{
			pPropertyDoc->SetAccessScript();
			pPropertyDoc->SetFocus();
			bRet = true;
		}
		else
		if(Item->Type == _T("SQLServerScript"))
		{
			pPropertyDoc->SetSQLServerScript();
			pPropertyDoc->SetFocus();
			bRet = true;
		}
		else
		if(Item->Type == _T("MySQLScript"))
		{
			pPropertyDoc->SetMySQLScript();
			pPropertyDoc->SetFocus();
			bRet = true;
		}
		else
		if(Item->Type == _T("PostGresScript"))
		{
			pPropertyDoc->SetPostGresScript();
			pPropertyDoc->SetFocus();
			bRet = true;
		}
		else
		if(Item->Type == _T("OracleScript"))
		{
			pPropertyDoc->SetOracleScript();
			pPropertyDoc->SetFocus();
			bRet = true;
		}
		else
		if(Item->Type == _T("DT"))
		{
			pPropertyDoc->SetXMLScript();
			pPropertyDoc->SetFocus();
			bRet = true;
		}
		else
		{
			bRet = false;
		}

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLStudioProject::SetProjectProperties(CProjectEntity* Project, CDocument* document)
{
	bool bRet = false;
	CProjectPropertyDoc* pPropertyDoc;
	CString strTitle;

	try
	{
		strTitle.Format(_T("Property - %s"), Project->Name);

		pPropertyDoc = (CProjectPropertyDoc*)document;
		pPropertyDoc->Project = Project;
		pPropertyDoc->SetTitle(strTitle);

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLStudioProject::LoadEditItem(CProjectEntity* Project, CItemEntity* Item, CRuntimeClass*& frame, CRuntimeClass*& view, CRuntimeClass*& docment)
{
	bool bRet = false;

	try
	{
		if(Item->Type == _T("CS"))
		{
			view = RUNTIME_CLASS(CSHLQueryScintillaView);
			docment = RUNTIME_CLASS(CSHLQueryScintillaDoc);
			frame = RUNTIME_CLASS(CSHLChildScintillaFrame);

			bRet = true;
		}
		else
		if(Item->Type == _T("C++"))
		{
			view = RUNTIME_CLASS(CSHLQueryScintillaView);
			docment = RUNTIME_CLASS(CSHLQueryScintillaDoc);
			frame = RUNTIME_CLASS(CSHLChildScintillaFrame);

			bRet = true;
		}
		else
		if(Item->Type == _T("AccessScript"))
		{
			view = RUNTIME_CLASS(CSHLQueryScintillaView);
			docment = RUNTIME_CLASS(CSHLQueryScintillaDoc);
			frame = RUNTIME_CLASS(CSHLChildScintillaFrame);

			bRet = true;
		}
		if(Item->Type == _T("SQLServerScript"))
		{
			view = RUNTIME_CLASS(CSHLQueryScintillaView);
			docment = RUNTIME_CLASS(CSHLQueryScintillaDoc);
			frame = RUNTIME_CLASS(CSHLChildScintillaFrame);

			bRet = true;
		}
		else
		if(Item->Type == _T("MySQLScript"))
		{
			view = RUNTIME_CLASS(CSHLQueryScintillaView);
			docment = RUNTIME_CLASS(CSHLQueryScintillaDoc);
			frame = RUNTIME_CLASS(CSHLChildScintillaFrame);

			bRet = true;
		}
		else
		if(Item->Type == _T("PostGresScript"))
		{
			view = RUNTIME_CLASS(CSHLQueryScintillaView);
			docment = RUNTIME_CLASS(CSHLQueryScintillaDoc);
			frame = RUNTIME_CLASS(CSHLChildScintillaFrame);

			bRet = true;
		}
		else
		if(Item->Type == _T("OracleScript"))
		{
			view = RUNTIME_CLASS(CSHLQueryScintillaView);
			docment = RUNTIME_CLASS(CSHLQueryScintillaDoc);
			frame = RUNTIME_CLASS(CSHLChildScintillaFrame);

			bRet = true;
		}
		else
		if(Item->Type == _T("DT"))
		{
			view = RUNTIME_CLASS(CSHLQueryScintillaView);
			docment = RUNTIME_CLASS(CSHLQueryScintillaDoc);
			frame = RUNTIME_CLASS(CSHLChildScintillaFrame);

			bRet = true;
		}
		else
		{
			bRet = false;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLStudioProject::LoadGenerateItem(CProjectEntity* Project, CItemEntity* Item, CRuntimeClass*& frame, CRuntimeClass*& view, CRuntimeClass*& docment)
{
	bool bRet = false;

	try
	{
		if(Item->Type == _T("DT"))
		{
			view = RUNTIME_CLASS(CDatabaseItemGenerateView);
			docment = RUNTIME_CLASS(CGenericDoc);
			frame = RUNTIME_CLASS(CGenericChildFrame);

			bRet = true;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLStudioProject::LoadProjectProperties(CProjectEntity* Project, CRuntimeClass*& frame, CRuntimeClass*& view, CRuntimeClass*& docment)
{
	bool bRet = false;

	try
	{
		view = RUNTIME_CLASS(CProjectPropertyView);
		docment = RUNTIME_CLASS(CProjectPropertyDoc);
		frame = RUNTIME_CLASS(CGenericChildFrame);

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLStudioProject::GenerateItemAllTypes(CProjectEntity* Project, CItemEntity* Item, HWND  hwndOutput)
{
	bool bRet = false;
	bool bComplete = true;

	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table = NULL;

	CItemEntity* DatabaseProviderItem = NULL;

	CString key;
	CString DatabaseProvider;
	CString typeOfFileEngine;

	CString sourcecode;

	CString itemPropertyFile;
	CString projetPropertyFile;

	CString pathType;
	CString targetPath;
	CString strTargetFile;
	CString strAppendFile;
	CString strOrigenFile;
	CString prefixTargetFilename;
	CString suffixTargetFilename;
	CString kindFileToWrite;
	CString DatabaseProviderItemFile;

	CString sPrefixTable;
	INT prefixTable;

	CString sFirstUpperCase;
	BOOL firstUpperCase;

	CPath path;
	CFread fread;

	CString strMsg;

	try
	{		
		do
		{
			path.AddPath(2, Project->Path, Project->PropertyFile);
			projetPropertyFile = path.GetPath();
			if(!path.ExistFile())
			{
				strMsg.Format(_T("> File '%s' don't exists."), projetPropertyFile);
				SendOutPutMessage(hwndOutput, strMsg);
				strMsg = _T("> Build canceled.");
				SendOutPutMessage(hwndOutput, strMsg);

				bComplete = false;
				break;
			}
			LoadPropertyProject(projetPropertyFile, Project->Properties, hwndOutput);

			path.AddPath(2, Item->Path, Item->PropertyFile);
			itemPropertyFile = path.GetPath();
			if(!path.ExistFile())
			{
				strMsg.Format(_T("> File '%s' don't exists."), itemPropertyFile);
				SendOutPutMessage(hwndOutput, strMsg);
				strMsg = _T("> Build canceled.");
				SendOutPutMessage(hwndOutput, strMsg);

				bComplete = false;
				break;
			}

			if(!LoadPropertyFile(itemPropertyFile, Item->Properties, hwndOutput))
			{
				strMsg.Format(_T("> Can not load proprieties from '%s' file."), itemPropertyFile);
				SendOutPutMessage(hwndOutput, strMsg);
				strMsg = _T("> Build canceled.");
				SendOutPutMessage(hwndOutput, strMsg);

				bComplete = false;
				break;
			}
			
			key = _T("FilestoGenerate");
			kindFileToWrite = Item->Properties[key];
			if (kindFileToWrite.IsEmpty())
				kindFileToWrite = "Both";

			key = _T("DatabaseProvider");
			DatabaseProvider = Item->Properties[key];
			if(DatabaseProvider.IsEmpty())
			{
				strMsg.Format(_T("> Property Database Provider is empty."));
				SendOutPutMessage(hwndOutput, strMsg);
				strMsg = _T("> Build canceled.");
				SendOutPutMessage(hwndOutput, strMsg);

				bComplete = false;
				break;
			}

			key = _T("PrefixTargetFileName");
			prefixTargetFilename = Item->Properties[key];

			key = _T("SuffixTargetFileName");
			suffixTargetFilename = Item->Properties[key];
			path.SetPath(Item->FileName);
			suffixTargetFilename += path.GetExtension();

			DatabaseProviderItem = FindDatabaseProviderItem(DatabaseProvider, Project);
			if(!DatabaseProviderItem)
			{
				strMsg.Format(_T("> Property Database Provider '%s' is invalid."), DatabaseProvider);
				SendOutPutMessage(hwndOutput, strMsg);
				strMsg = _T("> Build canceled.");
				SendOutPutMessage(hwndOutput, strMsg);

				bComplete = false;
				break;
			}
			path.AddPath(2, DatabaseProviderItem->Path, DatabaseProviderItem->PropertyFile);
			DatabaseProviderItemFile = path.GetPath();
			LoadPropertyFile(DatabaseProviderItemFile, DatabaseProviderItem->Properties, hwndOutput);

			key = _T("PathType");
			pathType = Item->Properties[key];
			if(pathType.IsEmpty())
			{
				strMsg.Format(_T("> Property 'PathType' is empty."));
				SendOutPutMessage(hwndOutput, strMsg);
				strMsg = _T("> Build canceled.");
				SendOutPutMessage(hwndOutput, strMsg);

				bComplete = false;
				break;
			}
			else
			{
				if(pathType != _T("Absolute") && pathType != _T("Relative"))
				{
					strMsg.Format(_T("> Propety 'PathType' is invalid. Permitted values are: 'Absolute' or 'Relative'. Property value is assign with '%s'"), pathType);
					SendOutPutMessage(hwndOutput, strMsg);
					strMsg = _T("> Build canceled.");
					SendOutPutMessage(hwndOutput, strMsg);

					bComplete = false;
					break;
				}
			}

			key = _T("AppendFile");
			strAppendFile = Item->Properties[key];

			key = _T("TargetPath");
			targetPath = Item->Properties[key];
			if(targetPath.IsEmpty())
			{
				strMsg.Format(_T("> Propety 'TargetPath' is empty."));
				SendOutPutMessage(hwndOutput, strMsg);
				strMsg = _T("> Build canceled.");
				SendOutPutMessage(hwndOutput, strMsg);

				bComplete = false;
				break;
			}
			else
			{
				if(pathType == _T("Relative"))
				{
					path.AddPath(3, Project->Path, targetPath, _T(""));
					targetPath = path.GetPath();
				}
				else
				{
					path.AddPath(2, targetPath, _T(""));
				}

				if(!path.ExistLocation())
				{
					strMsg.Format(_T("> Propety 'TargetPath' is invalid path.'%s' don't exists"), path.GetLocation());
					SendOutPutMessage(hwndOutput, strMsg);
					strMsg = _T("> Build canceled.");
					SendOutPutMessage(hwndOutput, strMsg);

					bComplete = false;
					break;
				}
			}

			path.AddPath(2, Item->Path, Item->FileName);
			if(!path.ExistFile())
			{
				strMsg.Format(_T("> File '%s' does not exists"), path.GetPath());
				SendOutPutMessage(hwndOutput, strMsg);
				strMsg = _T("> Build canceled.");
				SendOutPutMessage(hwndOutput, strMsg);

				bComplete = false;
				break;
			}

			key = _T("Engine");
			typeOfFileEngine = Item->Properties[key];

			if(typeOfFileEngine.IsEmpty())
			{
				strMsg.Format(_T("> Property 'Engine' is empty."));
				SendOutPutMessage(hwndOutput, strMsg);
				strMsg = _T("> Build canceled.");
				SendOutPutMessage(hwndOutput, strMsg);

				bComplete = false;
				break;
			}

			if(typeOfFileEngine == _T("Standalone"))
			{
				if(!GenerateSourceCodeStandAlone(Project, Item, DatabaseProviderItem, hwndOutput, sourcecode))
				{
					strMsg = _T("> Build canceled.");
					SendOutPutMessage(hwndOutput, strMsg);

					bComplete = false;
					break;
				}

				if (kindFileToWrite == _T("Both") || kindFileToWrite == _T("Main File"))
				{
					if (!suffixTargetFilename.IsEmpty())
					{
						CString fileWithOutExtension;

						path.SetPath(Item->FileName);
						fileWithOutExtension = Item->FileName;
						fileWithOutExtension.Replace(path.GetExtension(), _T(""));
						path.AddPath(2, targetPath, prefixTargetFilename + fileWithOutExtension + path.GetExtension());
						strTargetFile = path.GetPath();
					}
					else
					{
						path.AddPath(2, targetPath, prefixTargetFilename + Item->FileName);
						strTargetFile = path.GetPath();
					}

					if (path.ExistFile())
					{
						if(ReadUserAreaFromTarget(strTargetFile, hwndOutput, sourcecode))
							DeleteFile(strTargetFile);
					}

					if (fread.SaveFile(strTargetFile, sourcecode))
					{
						strMsg.Format(_T("> Saving '%s' file."), strTargetFile);
						SendOutPutMessage(hwndOutput, strMsg);
					}
					else
					{
						strMsg.Format(_T("> Error Saving '%s' file. - %s"), strTargetFile, fread.GetLastErrorMessage());
						SendOutPutMessage(hwndOutput, strMsg);
						strMsg = _T("> Build canceled.");
						SendOutPutMessage(hwndOutput, strMsg);
						bComplete = false;
						break;
					}
				}


				if ((!strAppendFile.IsEmpty()) && (kindFileToWrite == _T("Both") || kindFileToWrite == _T("Append File")))
				{
					path.AddPath(2, targetPath, (strAppendFile));
					strAppendFile = path.GetPath();

					if (fread.SaveFile(strAppendFile, sourcecode))
					{
						strMsg.Format(_T("> Saving '%s' file."), strAppendFile);
						SendOutPutMessage(hwndOutput, strMsg);
					}
					else
					{
						strMsg.Format(_T("> Error Saving '%s' file. - %s"), strTargetFile, fread.GetLastErrorMessage());
						SendOutPutMessage(hwndOutput, strMsg);
						strMsg = _T("> Build canceled.");
						SendOutPutMessage(hwndOutput, strMsg);
						bComplete = false;
						break;
					}
				}
			}
			else
			{
				reader = LoadDTFileToReader(DatabaseProviderItem);
				if(!reader)
				{
					strMsg.Format(_T("> Can not load properties from '%s' file."), DatabaseProviderItem->Name);
					SendOutPutMessage(hwndOutput, strMsg);
					strMsg = _T("> Build canceled.");
					SendOutPutMessage(hwndOutput, strMsg);

					bComplete = false;
					break;
				}

				key = _T("PrefixTable");
				sPrefixTable = Item->Properties[key];
				if(sPrefixTable.IsEmpty())
					prefixTable = 0;
				else
					Val(sPrefixTable, prefixTable);

				key = _T("FirstUpperCase");
				sFirstUpperCase = Item->Properties[key].MakeUpper();
				if (sFirstUpperCase.IsEmpty() || sFirstUpperCase == "FALSE")
					firstUpperCase = FALSE;
				else
					firstUpperCase = TRUE;

				if(!strAppendFile.IsEmpty())
				{
					path.AddPath(2, targetPath, (strAppendFile));
					strAppendFile = path.GetPath();
				}

				for(UINT nIndexTable = 0; nIndexTable < reader->Tables.GetCount(); nIndexTable++)
				{
					table = reader->Tables.GetAt(nIndexTable);

					path.AddPath(2, targetPath, prefixTargetFilename + (GetTableName(table->TableName, prefixTable, firstUpperCase) + suffixTargetFilename));
					strTargetFile = path.GetPath();

					sourcecode = _T("");
					if(!GenerateSourceCodePerTable(table, Project, Item, DatabaseProviderItem, hwndOutput, sourcecode))
					{
						strMsg = _T("> Build canceled.");
						SendOutPutMessage(hwndOutput, strMsg);

						bComplete = false;
						break;
					}

					if (kindFileToWrite == _T("Both") || kindFileToWrite == _T("Main File"))
					{
						if (path.ExistFile())
						{
							if(ReadUserAreaFromTarget(strTargetFile, hwndOutput, sourcecode))
								DeleteFile(strTargetFile);
						}

						if (fread.SaveFile(strTargetFile, sourcecode))
						{
							strMsg.Format(_T("> Saving '%s' file."), strTargetFile);
							SendOutPutMessage(hwndOutput, strMsg);
						}
						else
						{
							strMsg.Format(_T("> Error Saving '%s' file. - %s"), strTargetFile, fread.GetLastErrorMessage());
							SendOutPutMessage(hwndOutput, strMsg);
							strMsg = _T("> Build canceled.");
							SendOutPutMessage(hwndOutput, strMsg);
							bComplete = false;
							break;
						}
					}

					if (!strAppendFile.IsEmpty() && (kindFileToWrite == _T("Both") || kindFileToWrite == _T("Append File")))
					{
						if (fread.SaveFile(strAppendFile, sourcecode))
						{
							strMsg.Format(_T("> Saving '%s' file."), strAppendFile);
							SendOutPutMessage(hwndOutput, strMsg);
						}
						else
						{
							strMsg.Format(_T("> Error Saving '%s' file. - %s"), strTargetFile, fread.GetLastErrorMessage());
							SendOutPutMessage(hwndOutput, strMsg);
							strMsg = _T("> Build canceled.");
							SendOutPutMessage(hwndOutput, strMsg);
							bComplete = false;
							break;
						}
					}
				}
			}
		}
		while(false);

		bRet = bComplete;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;

		SendOutPutMessage(hwndOutput, m_Error);
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());

		SendOutPutMessage(hwndOutput, m_Error);
	}

	if(reader)
		delete reader;

	return bRet;
}

SHLOleDBReader* CSHLStudioProject::LoadDTFileToReader(CItemEntity* DatabaseProviderItem)
{
	CMarkup xml = NULL;

	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table = NULL;
	SHLDBROW* row = NULL;

	CPath path;
	CString strFileNameDatabaseProviderItem;

	CString value;

	try
	{
		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		path.AddPath(2, DatabaseProviderItem->Path, DatabaseProviderItem->FileName);
		strFileNameDatabaseProviderItem = path.GetPath();		

		if(!xml.Load(strFileNameDatabaseProviderItem))
		{
			throw -1;
		}
		
		while(xml.FindChildElem(_T("Table")))
		{
			if(!reader)
			{
				reader = new SHLOleDBReader();
			}

			xml.IntoElem();

			table = new SHLOleDBTable();

			table->AddColumn(1, _T("Name"), SHLDBType_String, 256, true);
			table->AddColumn(2, _T("PrimaryKey"), SHLDBType_Boolean, 1, true);
			table->AddColumn(3, _T("Identity"), SHLDBType_Boolean, 1, true);
			table->AddColumn(4, _T("DBType"), SHLDBType_String, 20, true);
			table->AddColumn(5, _T("DBSize"), SHLDBType_Int32, 4, true);
			table->AddColumn(6, _T("ForeignKey"), SHLDBType_Boolean, 1, true);
			table->AddColumn(7, _T("TableForeignKey"), SHLDBType_String, 256, true);

			value = xml.GetAttrib(_T("Name"));
			table->TableName = value;

			while(xml.FindChildElem(_T("Field")))
			{
				xml.IntoElem();

				row = new SHLDBROW;
				row->value = new SHLBINDVALUE[7];

				value = xml.GetAttrib(_T("Name"));
				Copychar(value.GetBuffer(), row->value[0].data.szVal, value.GetLength());

				value = xml.GetAttrib(_T("PrimaryKey"));
				row->value[1].data.bolVal = value == _T("1")?true:false;

				value = xml.GetAttrib(_T("Identity"));
				row->value[2].data.bolVal = value == _T("1")?true:false;

				value = xml.GetAttrib(_T("DBType"));
				Copychar(value.GetBuffer(), row->value[3].data.szVal, value.GetLength());

				value = xml.GetAttrib(_T("DBSize"));
				Val(value, row->value[4].data.intVal);

				value = xml.GetAttrib(_T("ForeignKey"));
				row->value[5].data.bolVal = value == _T("1")?true:false;

				value = xml.GetAttrib(_T("TableForeignKey"));
				Copychar(value.GetBuffer(), row->value[6].data.szVal, value.GetLength());

				table->Rows.Add(row);
				xml.OutOfElem();
			}

			reader->Tables.Add(table);
			xml.OutOfElem();
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return reader;
}

CItemEntity* CSHLStudioProject::FindDatabaseProviderItem(CString DatabaseProvider, CProjectEntity* Project)
{
	CItemEntity* DatabaseProviderItem = NULL;

	try
	{
		for(UINT nIndexProject = 0; nIndexProject < Project->Items->GetItemCount(); nIndexProject++)
		{
			DatabaseProviderItem = Project->Items->GetItemAt(nIndexProject);

			if(DatabaseProviderItem->Name == DatabaseProvider)
				break;

			DatabaseProviderItem = NULL;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return DatabaseProviderItem;
}

BOOL CSHLStudioProject::GenerateSourceCodePerTable(SHLOleDBTable* table, CProjectEntity* Project, CItemEntity* Item, CItemEntity* DatabaseProviderItem, HWND  hwndOutput, CString &sourcecode)
{	
	BOOL bRet = FALSE;
	BOOL bComplete = TRUE;

	CPath path;
	CFread fread;
	CString filename;
	CString contentline;
	CString contentlinetotreat;
	SHLTEMPLATESTATETOREAD state = SHLTEMPLATESTATETOREAD_IDLE;
	SHLTEMPLATESTATETOREAD substateforeignkey = SHLTEMPLATESTATETOREAD_IDLE;
	BOOL bStillRead = true;
	BOOL bHasForeignkey = false;
	CString key;
	CString sPrefixTable;
	INT prefixTable;
	CString sFirstUpperCase;
	BOOL firstUpperCase;
	UINT initcount;
	CString strMsg;

	try
	{
		do
		{
			bHasForeignkey = HasTableForeignkey(table);

			key = _T("PrefixTable");
			sPrefixTable = Item->Properties[key];
			if(sPrefixTable.IsEmpty())
				prefixTable = 0;
			else
				Val(sPrefixTable, prefixTable);

			key = _T("FirstUpperCase");
			sFirstUpperCase = Item->Properties[key].MakeUpper();
			if (sFirstUpperCase.IsEmpty() || sFirstUpperCase == "FALSE")
				firstUpperCase = FALSE;
			else
				firstUpperCase = TRUE;

			path.AddPath(2, Item->Path, Item->FileName);
			filename = path.GetPath();

			if(!path.ExistFile())
			{
				strMsg.Format(_T("> File '%s' does not exists."), path.GetPath());
				SendOutPutMessage(hwndOutput, strMsg);

				bComplete = FALSE;
				break;
			}

			if(!fread.Open(filename))
			{
				strMsg.Format(_T("> Can not open '%s' file."), filename);
				SendOutPutMessage(hwndOutput, strMsg);

				bComplete = FALSE;
				break;
			}

			while(bStillRead)
			{
				switch(state)
				{
					case SHLTEMPLATESTATETOREAD_IDLE:
						contentlinetotreat = _T("");
						state = SHLTEMPLATESTATETOREAD_READLINE;
						substateforeignkey = SHLTEMPLATESTATETOREAD_IDLE;

						break;
					case SHLTEMPLATESTATETOREAD_READLINE:
						if(fread.Eof())
						{
							state = SHLTEMPLATESTATETOREAD_IDLE;
							bStillRead = false;
						}
						else
						{
							state = SHLTEMPLATESTATETOREAD_GETLINE;
							fread.Read();
						}

						break;
					case SHLTEMPLATESTATETOREAD_READLINE_ALLFIELDS:
						if(fread.Eof())
						{
							state = SHLTEMPLATESTATETOREAD_IDLE;

							strMsg.Format(_T("> Unexpected end of file. (ALL FIELDS"));
							SendOutPutMessage(hwndOutput, strMsg);

							bComplete = FALSE;
							bStillRead = false;
						}
						else
						{
							state = SHLTEMPLATESTATETOREAD_GETLINE_ALLFIELDS;
							fread.Read();
						}

						break;
					case SHLTEMPLATESTATETOREAD_READLINE_FOREIGNKEY:
						if(fread.Eof())
						{
							state = SHLTEMPLATESTATETOREAD_IDLE;

							strMsg.Format(_T("> Unexpected end of file. (FOREIGN KEY)"));
							SendOutPutMessage(hwndOutput, strMsg);

							bComplete = FALSE;
							bStillRead = false;
						}
						else
						{
							state = SHLTEMPLATESTATETOREAD_GETLINE_FOREIGNKEY;
							fread.Read();
						}

						break;
					case SHLTEMPLATESTATETOREAD_GETLINE:
						contentline = fread.GetContent();
							
						switch(substateforeignkey)
						{
							case SHLTEMPLATESTATETOREAD_IDLE:
								if(contentline.Find(_T("<ifexistforeignkey>")) > -1)
								{
									substateforeignkey = SHLTEMPLATESTATETOREAD_WAITFORENDFOREIGNKEY;
									state = SHLTEMPLATESTATETOREAD_READLINE;
								}
								else
								{
									if(contentline.Find(_T("<allfieldslessprimarykey>"))  > -1)
									{
										state = SHLTEMPLATESTATETOREAD_READLINE_ALLFIELDS;
										contentlinetotreat = _T("");
										initcount = GetInitCount(contentline);
									}
									else
									if(contentline.Find(_T("<allfieldsforeignkey>"))  > -1)
									{
										state = SHLTEMPLATESTATETOREAD_READLINE_FOREIGNKEY;
										contentlinetotreat = _T("");

										initcount = GetInitCount(contentline);
									}
									else
									{
										state = SHLTEMPLATESTATETOREAD_TREATLINE;
										contentlinetotreat = contentline;
									}
								}
								break;
							case SHLTEMPLATESTATETOREAD_WAITFORENDFOREIGNKEY:
								if(contentline.Find(_T("</ifexistforeignkey>")) > -1)
								{
									substateforeignkey = SHLTEMPLATESTATETOREAD_IDLE;
									state = SHLTEMPLATESTATETOREAD_READLINE;
									contentlinetotreat = _T("");
								}
								else
								{
									if(bHasForeignkey)
									{
										if(contentline.Find(_T("<allfieldslessprimarykey>"))  > -1)
										{
											state = SHLTEMPLATESTATETOREAD_READLINE_ALLFIELDS;
											contentlinetotreat = _T("");
											initcount = GetInitCount(contentline);
										}
										else
										if(contentline.Find(_T("<allfieldsforeignkey>"))  > -1)
										{
											state = SHLTEMPLATESTATETOREAD_READLINE_FOREIGNKEY;
											contentlinetotreat = _T("");

											initcount = GetInitCount(contentline);
										}
										else
										{
											contentlinetotreat += contentline;
											state = SHLTEMPLATESTATETOREAD_TREATLINE;
										}
									}
									else
									{
										contentlinetotreat = _T("");
										state = SHLTEMPLATESTATETOREAD_READLINE;
									}
								}
								break;
						}
						break;
					case SHLTEMPLATESTATETOREAD_GETLINE_ALLFIELDS:
						contentline = fread.GetContent();

						if(contentline.Find(_T("</allfieldslessprimarykey>")) > -1)
						{
							state = SHLTEMPLATESTATETOREAD_TREATLINE_ALLFIELDS;
						}
						else
						{
							if(contentlinetotreat.GetLength() > 0)
								contentlinetotreat += _T("\n");

							contentlinetotreat += contentline;
							state = SHLTEMPLATESTATETOREAD_READLINE_ALLFIELDS;
						}

						break;
					case SHLTEMPLATESTATETOREAD_GETLINE_FOREIGNKEY:
						contentline = fread.GetContent();

						if(contentline.Find(_T("</allfieldsforeignkey>")) > -1)
						{
							state = SHLTEMPLATESTATETOREAD_TREATLINE_FOREIGNKEY;
						}
						else
						{
							if(contentlinetotreat.GetLength() > 0)
								contentlinetotreat += _T("\n");

							contentlinetotreat += contentline;
							state = SHLTEMPLATESTATETOREAD_READLINE_FOREIGNKEY;
						}

						break;
					case SHLTEMPLATESTATETOREAD_TREATLINE_ALLFIELDS:
						{
							CString intermediate;
							CString contentlinebyFields;
							CString value;
							BOOL bPrimarykey;
							SHLDBROW *row = NULL;
							UINT nCount = 0;
							UINT nIndex = 0;
							UINT fieldcount = initcount;

							for(UINT nIndexFields = 0; nIndexFields < table->Rows.GetCount(); nIndexFields++)
							{
								bPrimarykey = table->GetBoolean(nIndexFields, table->GetColumnOrdinal(_T("PrimaryKey")));
									
								if(!bPrimarykey)
									nCount++;								
							}

							for(UINT nIndexFields = 0; nIndexFields < table->Rows.GetCount(); nIndexFields++)
							{
								row = table->Rows.GetAt(nIndexFields);

								bPrimarykey = table->GetBoolean(nIndexFields, table->GetColumnOrdinal(_T("PrimaryKey")));
									
								if(!bPrimarykey)
								{
									nIndex++;
									intermediate = _T("");
									if(!ChangeShareTags(Project, Item, DatabaseProviderItem, hwndOutput, contentlinetotreat, intermediate))
									{
										strMsg.Format(_T("> Error 'Share Tags' routine. (ALL FIELDS)"));
										SendOutPutMessage(hwndOutput, strMsg);

										bComplete = FALSE;
										bStillRead = false;
									}

									contentlinebyFields = intermediate;
									intermediate =  _T("");
									if (!ChangeTableTags(Project, Item, table, prefixTable, hwndOutput, contentlinebyFields, intermediate))
									{
										strMsg.Format(_T("> Error 'Table Tags' routine. (ALL FIELDS)"));
										SendOutPutMessage(hwndOutput, strMsg);

										bComplete = FALSE;
										bStillRead = false;
									}

									contentlinebyFields = intermediate;
									intermediate =  _T("");
									if (!ChangeFieldsTags(Project, Item, table, prefixTable, row, nIndex, nCount, hwndOutput, contentlinebyFields, intermediate, fieldcount))
									{
										strMsg.Format(_T("> Error 'Field Tags' routine. (ALL FIELDS)"));
										SendOutPutMessage(hwndOutput, strMsg);

										bComplete = FALSE;
										bStillRead = false;
									}

									sourcecode += intermediate;
									sourcecode += _T("\n");

									fieldcount++;
								}
							}
						}

						state = SHLTEMPLATESTATETOREAD_READLINE;
						break;
					case SHLTEMPLATESTATETOREAD_TREATLINE_FOREIGNKEY:
						{
							CString intermediate;
							CString contentlinebyFields;
							CString value;
							BOOL bForeingkey;
							SHLDBROW *row = NULL;
							UINT nCount = 0;
							UINT nIndex = 0;
							UINT fieldcount = initcount;

							for(UINT nIndexFields = 0; nIndexFields < table->Rows.GetCount(); nIndexFields++)
							{
								bForeingkey = table->GetBoolean(nIndexFields, table->GetColumnOrdinal(_T("ForeignKey")));
									
								if(bForeingkey)
									nCount++;								
							}

							for(UINT nIndexFields = 0; nIndexFields < table->Rows.GetCount(); nIndexFields++)
							{
								row = table->Rows.GetAt(nIndexFields);

								bForeingkey = table->GetBoolean(nIndexFields, table->GetColumnOrdinal(_T("ForeignKey")));
									
								if(bForeingkey)
								{
									nIndex++;
									intermediate = _T("");
									if(!ChangeShareTags(Project, Item, DatabaseProviderItem, hwndOutput, contentlinetotreat, intermediate))
									{
										strMsg.Format(_T("> Error 'Share Tags' routine. (FOREIGN KEY)"));
										SendOutPutMessage(hwndOutput, strMsg);

										bComplete = FALSE;
										bStillRead = false;
									}

									contentlinebyFields = intermediate;
									intermediate =  _T("");
									if (!ChangeTableTags(Project, Item, table, prefixTable, hwndOutput, contentlinebyFields, intermediate))
									{
										strMsg.Format(_T("> Error 'Table Tags' routine. (FOREIGN KEY)"));
										SendOutPutMessage(hwndOutput, strMsg);

										bComplete = FALSE;
										bStillRead = false;
									}

									contentlinebyFields = intermediate;
									intermediate =  _T("");
									if (!ChangeFieldsTags(Project, Item, table, prefixTable, row, nIndex, nCount, hwndOutput, contentlinebyFields, intermediate, fieldcount))
									{
										strMsg.Format(_T("> Error 'Fields Tags' routine. (FOREIGN KEY)"));
										SendOutPutMessage(hwndOutput, strMsg);

										bComplete = FALSE;
										bStillRead = false;
									}

									sourcecode += intermediate;
									sourcecode += _T("\n");

									fieldcount++;
								}
							}
						}

						state = SHLTEMPLATESTATETOREAD_READLINE;
						break;
					case SHLTEMPLATESTATETOREAD_TREATLINE:
						{
							CString intermadiate;
							if(!ChangeShareTags(Project, Item, DatabaseProviderItem, hwndOutput, contentline, intermadiate))
							{
								strMsg.Format(_T("> Error 'Share Tags' routine. (COMMON)"));
								SendOutPutMessage(hwndOutput, strMsg);

								bComplete = FALSE;
								bStillRead = false;
							}

							contentline = intermadiate;
							intermadiate = _T("");
							if (!ChangeTableTags(Project, Item, table, prefixTable, hwndOutput, contentline, intermadiate))
							{
								strMsg.Format(_T("> Error 'Table Tags' routine. (COMMON)"));
								SendOutPutMessage(hwndOutput, strMsg);

								bComplete = FALSE;
								bStillRead = false;
							}

							contentline = intermadiate;
							intermadiate = _T("");
							if (!ChangePrimarykeyTags(Project, Item, table, hwndOutput, contentline, intermadiate))
							{
								strMsg.Format(_T("> Error 'Primary Key Tags' routine. (COMMON)"));
								SendOutPutMessage(hwndOutput, strMsg);

								bComplete = FALSE;
								bStillRead = false;
							}

							sourcecode += intermadiate;
							sourcecode += _T("\n");
						}

						state = SHLTEMPLATESTATETOREAD_READLINE;
						break;
				}
			}
		}
		while(false);

		if (bComplete)
			bComplete = ChangeSpecialTags(hwndOutput, sourcecode);

		bRet = bComplete;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;

		SendOutPutMessage(hwndOutput, m_Error);
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());

		SendOutPutMessage(hwndOutput, m_Error);
	}

	return bRet;
}

UINT CSHLStudioProject::GetInitCount(CString line)
{
	INT init = 1;
	CString newLine;
	CString sNumber = _T("");
	TCHAR caracter;

	try
	{
		line.Replace(_T("\t"), _T(""));
		line.Trim();

		newLine = line.Mid(line.Find(_T(">")));

		for(INT nIndex = 0; nIndex < newLine.GetLength(); nIndex++)
		{
			caracter = newLine[nIndex];

			if(IsNumeric(CString(caracter)))
			{
				sNumber += CString(caracter);
			}
		}

		if(sNumber != _T(""))
		{
			Val(sNumber, init);
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return init;
}

BOOL CSHLStudioProject::HasTableForeignkey(SHLOleDBTable* table)
{
	BOOL bRet = FALSE;
	
	try
	{
		for(UINT nIndex = 0; nIndex < table->Rows.GetCount(); nIndex++)
		{
			if(table->GetBoolean(nIndex, table->GetColumnOrdinal(_T("ForeignKey"))))
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

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

BOOL CSHLStudioProject::ChangeTableTags(CProjectEntity* Project, CItemEntity* Item, SHLOleDBTable* table, INT prefixTable, HWND  hwndOutput, CString contentline, CString &sourcecode)
{
	BOOL bRet = FALSE;

	CString TABLE;
	CString TABLEWITHOUTPREFIXTABLE;

	try
	{
		TABLE = table->TableName;
		contentline.Replace(_T("#TABLE#"), TABLE);

		TABLE = table->TableName;
		contentline.Replace(_T("#TABLEFISTUPPER#"), TABLE);

		TABLE = table->TableName;
		contentline.Replace(_T("#TABLEFISTLOWER#"), TABLE);

		TABLEWITHOUTPREFIXTABLE = GetTableName(table->TableName, prefixTable, FALSE);
		contentline.Replace(_T("#TABLEWITHOUTPREFIXTABLE#"), TABLEWITHOUTPREFIXTABLE);

		TABLEWITHOUTPREFIXTABLE = GetTableName(table->TableName, prefixTable, FALSE);
		contentline.Replace(_T("#TABLEWITHOUTPREFIXTABLEFISTUPPER#"), TABLEWITHOUTPREFIXTABLE);

		TABLEWITHOUTPREFIXTABLE = GetTableName(table->TableName, prefixTable, FALSE);
		contentline.Replace(_T("#TABLEWITHOUTPREFIXTABLEFISTLOWER#"), TABLEWITHOUTPREFIXTABLE);

		sourcecode += contentline;

		bRet = TRUE;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

BOOL CSHLStudioProject::ChangePrimarykeyTags(CProjectEntity* Project, CItemEntity* Item, SHLOleDBTable* table, HWND  hwndOutput, CString contentline, CString &sourcecode)
{
	BOOL bRet = FALSE;

	CString PRIMARYKEY;
	CString TYPEPRIMARYKEY;
	CString TYPEPRIMARYKEY_NULLABLE;
	CString TYPEPRIMARYKEYACCESS;
	CString TYPEPRIMARYKEYSQLSERVER;
	CString TYPEPRIMARYKEYORACLE;
	CString TYPEPRIMARYKEYPOSTGRESQL;
	CString TYPEPRIMARYKEYMYSQL;
	CString DBSIZEPRIMARYKEY;

	BOOL bPrimarykey;

	try
	{

		for(UINT nIndexFields = 0; nIndexFields < table->Rows.GetCount(); nIndexFields++)
		{
			bPrimarykey = table->GetBoolean(nIndexFields, table->GetColumnOrdinal(_T("PrimaryKey")));

			if (bPrimarykey)
			{
				PRIMARYKEY					= table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("Name")), _T(""));

				if (Item->Type == _T("CS"))
				{
					TYPEPRIMARYKEY				= GetTypeCS(table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBType")), _T("")), false);
					TYPEPRIMARYKEY_NULLABLE		= GetTypeCS(table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBType")), _T("")), true);
				}

				if (Item->Type == _T("C++"))
				{
					TYPEPRIMARYKEY				= GetTypePlusPlus(table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBType")), _T("")), false);
					TYPEPRIMARYKEY_NULLABLE		= GetTypePlusPlus(table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBType")), _T("")), true);
				}

				TYPEPRIMARYKEYACCESS		= GetAccessType(table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBType")), _T("")), table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBSize")), _T("")));
				TYPEPRIMARYKEYSQLSERVER		= GetSQLServerType(table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBType")), _T("")), table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBSize")), _T("")));
				TYPEPRIMARYKEYORACLE		= GetOracleType(table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBType")), _T("")), table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBSize")), _T("")));
				TYPEPRIMARYKEYPOSTGRESQL	= GetPostGreSQLType(table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBType")), _T("")), table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBSize")), _T("")));
				TYPEPRIMARYKEYMYSQL			= GetMySQLType(table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBType")), _T("")), table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBSize")), _T("")));

				DBSIZEPRIMARYKEY			= table->GetValueToString(nIndexFields, table->GetColumnOrdinal(_T("DBSize")), _T(""));

				contentline.Replace(_T("#PRIMARYKEY#"), PRIMARYKEY);
				contentline.Replace(_T("#TYPEPRIMARYKEYCS#"), TYPEPRIMARYKEY);
				contentline.Replace(_T("#TYPEPRIMARYKEYCS_NULLABLE#"), TYPEPRIMARYKEY_NULLABLE);
				contentline.Replace(_T("#TYPEPRIMARYKEYACCESS#"), TYPEPRIMARYKEYACCESS);
				contentline.Replace(_T("#TYPEPRIMARYKEYSQLSERVER#"), TYPEPRIMARYKEYSQLSERVER);
				contentline.Replace(_T("#TYPEPRIMARYKEYORACLE#"), TYPEPRIMARYKEYORACLE);
				contentline.Replace(_T("#TYPEPRIMARYKEYPOSTGRESQL#"), TYPEPRIMARYKEYPOSTGRESQL);
				contentline.Replace(_T("#TYPEPRIMARYKEYMYSQL#"), TYPEPRIMARYKEYMYSQL);
				contentline.Replace(_T("#DBSIZEPRIMARYKEY#"), DBSIZEPRIMARYKEY);

				break;
			}
		}

		sourcecode += contentline;

		bRet = TRUE;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

BOOL CSHLStudioProject::ChangeSpecialTags(HWND  hwndOutput, CString &sourcecode)
{
	BOOL bRet = FALSE;
	CString line;
	CString composedline;
	CString auxline;
	CString newsource;
	LONG position = 0;
	INT tagindexini = 0;
	INT tagindexend = 0;

	try
	{
		
		while (position < sourcecode.GetLength())
		{
			line = _T("");
			for (INT lineindex = position; lineindex < sourcecode.GetLength(); lineindex++)
			{
				position++;
				line += sourcecode[lineindex];

				if (sourcecode[lineindex] == '\n')
					break;
			}

			auxline = line;
			composedline = line;
			if (auxline.Find(_T("<upper>")) > -1)
			{
				composedline =_T("");

				while ((tagindexini = auxline.Find(_T("<upper>"))) > -1)
				{
					if ((tagindexend = auxline.Find(_T("</upper>"))) <= -1)
					{
						CString strMsg;
						m_Error = _T("<upper> is not closed");

						strMsg.Format(_T("%s (Special Tags)"), m_Error);
						SendOutPutMessage(hwndOutput, strMsg);

						return FALSE;
					}

					if (tagindexini > 0)
						composedline += auxline.Mid(0, tagindexini);

					for (INT composedlineindex = tagindexini + 7; composedlineindex < tagindexend; composedlineindex++)
					{
						composedline +=  CString(auxline[composedlineindex]).MakeUpper();
					}

					line = auxline.Mid(tagindexend+8);
					auxline = line;
				}

				composedline += line;
			}

			auxline = line = composedline;
			if (auxline.Find(_T("<lower>")) > -1)
			{
				composedline =_T("");

				while ((tagindexini = auxline.Find(_T("<lower>"))) > -1)
				{
					if ((tagindexend = auxline.Find(_T("</lower>"))) <= -1)
					{
						CString strMsg;
						m_Error = _T("<lower> is not closed");

						strMsg.Format(_T("%s (Special Tags)"), m_Error);
						SendOutPutMessage(hwndOutput, strMsg);

						return FALSE;
					}

					if (tagindexini > 0)
						composedline += auxline.Mid(0, tagindexini);

					for (INT composedlineindex = tagindexini + 7; composedlineindex < tagindexend; composedlineindex++)
					{
						composedline +=  CString(auxline[composedlineindex]).MakeLower();;
					}

					line = auxline.Mid(tagindexend+8);
					auxline = line;
				}

				composedline += line;
			}

			auxline = line = composedline;
			if (auxline.Find(_T("<firstupper>")) > -1)
			{
				composedline =_T("");

				while ((tagindexini = auxline.Find(_T("<firstupper>"))) > -1)
				{
					if ((tagindexend = auxline.Find(_T("</firstupper>"))) <= -1)
					{
						CString strMsg;
						m_Error = _T("<firstupper> is not closed");

						strMsg.Format(_T("%s (Special Tags)"), m_Error);
						SendOutPutMessage(hwndOutput, strMsg);

						return FALSE;
					}

					if (tagindexini > 0)
						composedline += auxline.Mid(0, tagindexini);

					BOOL bfirstcaracter = TRUE;
					for (INT composedlineindex = tagindexini + 12; composedlineindex < tagindexend; composedlineindex++)
					{
						if (CString(auxline[composedlineindex]) != _T("_"))
						{
							if (bfirstcaracter)
								composedline += CString(auxline[composedlineindex]).MakeUpper();
							else
								composedline += CString(auxline[composedlineindex]).MakeLower();

							bfirstcaracter = FALSE;
						}
						else
							bfirstcaracter = TRUE;
					}

					line = auxline.Mid(tagindexend+13);
					auxline = line;
				}

				composedline += line;
			}

			newsource += composedline;
		}

		sourcecode = newsource;

		bRet = TRUE;
	}
	catch (CException* ex)
	{
		CString strMsg;
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;

		strMsg.Format(_T("%s (Special Tags)"), m_Error);
		SendOutPutMessage(hwndOutput, strMsg);
	}
	catch (...)
	{
		CString strMsg;
		m_Error = ErrorMessage(::GetLastError());

		strMsg.Format(_T("%s (Special Tags)"), m_Error);
		SendOutPutMessage(hwndOutput, strMsg);
	}

	return bRet;
}

BOOL CSHLStudioProject::ReadUserAreaFromTarget(CString targetfile, HWND  hwndOutput, CString &sourcecode)
{
	BOOL bRet = FALSE;

	CString composedline;
	CString* line;
	CString  readline;
	CFread readtargetfile;
	CSHLList<CString> listUserArea;
	CSHLList<CString> listSourceCode;
	CString tagstart, tagend;
	INT tagpos;
	BOOL btagopen = FALSE;
	
	try
	{
		if (sourcecode.Find(_T("SHLSTUDIO_USER_AREA_START_1")) > -1)
		{
			readtargetfile.Open(targetfile);

			if (readtargetfile.IsOpen())
			{
				line = NULL;
				for (INT lineindex = 0; lineindex < sourcecode.GetLength(); lineindex++)
				{		
					if (line == NULL)
						line = new CString();

					*line += sourcecode[lineindex];

					if (sourcecode[lineindex] == '\n')
					{
						listSourceCode.Add(line);
						line = NULL;
					}
				}

				tagpos = 1;
				tagstart.Format(_T("SHLSTUDIO_USER_AREA_START_%d"), tagpos);
				tagend.Format(_T("SHLSTUDIO_USER_AREA_END_%d"), tagpos);

				while (!readtargetfile.Eof())
				{
					readtargetfile.Read();
					readline = readtargetfile.GetContent();

					if (!btagopen)
					{
						if (readline.Find(tagstart) > -1)
						{
							composedline = _T("");
							btagopen = TRUE;
							continue;
						}
					}

					if (btagopen)
					{
						if (readline.Find(tagend) > -1)
						{
							btagopen = FALSE;
							tagpos++;

							if (composedline.GetLength() > 0)
							{
								line = new CString();

								*line = composedline;

								listUserArea.Add(line);
							}
							else
							{
								line = new CString();

								*line += _T("");

								listUserArea.Add(line);
							}

							tagstart.Format(_T("SHLSTUDIO_USER_AREA_START_%d"), tagpos);
							tagend.Format(_T("SHLSTUDIO_USER_AREA_END_%d"), tagpos);

							continue;
						}
						else
							composedline += readline + _T("\n");
					}
				}

				sourcecode = _T("");
				tagpos = 1;
				tagstart.Format(_T("SHLSTUDIO_USER_AREA_START_%d"), tagpos);
				for (INT listindex = 0; listindex < listSourceCode.GetCount(); listindex++)
				{
					line = listSourceCode.GetAt(listindex);

					sourcecode += *line;

					if ((*line).Find(tagstart) > -1)
					{
						if (listUserArea.GetCount() >= tagpos)
						{
							line = listUserArea.GetAt(tagpos-1);
							sourcecode += *line;
							tagpos++;

							tagstart.Format(_T("SHLSTUDIO_USER_AREA_START_%d"), tagpos);
							tagend.Format(_T("SHLSTUDIO_USER_AREA_END_%d"), tagpos);
						}
					}
				}
			}
			else
			{
				CString strMsg;

				strMsg.Format(_T("Cannot open %s to search USER AREA\n\nError: %s"), targetfile, ErrorMessage(::GetLastError()));
				SendOutPutMessage(hwndOutput, strMsg);

				return FALSE;
			}
		}
		
		bRet = TRUE;
	}
	catch (CException* ex)
	{
		CString strMsg;
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;

		strMsg.Format(_T("%s (Special Tags)"), m_Error);
		SendOutPutMessage(hwndOutput, strMsg);
	}
	catch (...)
	{
		CString strMsg;
		m_Error = ErrorMessage(::GetLastError());

		strMsg.Format(_T("%s (Special Tags)"), m_Error);
		SendOutPutMessage(hwndOutput, strMsg);
	}

	if (readtargetfile.IsOpen())
		readtargetfile.Close();

	return bRet;
}

BOOL CSHLStudioProject::ChangeFieldsTags(CProjectEntity* Project, CItemEntity* Item, SHLOleDBTable* table, INT prefixTable, SHLDBROW *row, UINT nIndex, UINT nCount, HWND  hwndOutput, CString contentline, CString &sourcecode, UINT fieldcount)
{
	BOOL bRet = FALSE;

	BOOL IsForeign = false;

	CString ANDAFTER;
	CString ANDBEFORE;
	CString COMMAAFTER;
	CString COMMABEFORE;

	CString FIELD;
	CString TABLEFOREIGN;
	CString TABLEFOREIGNWITHOUTPREFIXTABLE;

	CString TYPEDATAFIELD;
	CString TYPEDATAFIELD_NULLABLE;

	CString TYPEDBSQLSERVER;
	CString TYPEDBORACLE;
	CString TYPEDBPOSTGRESQL;
	CString TYPEDBMYSQL;

	CString DBSIZE;

	CString COUNT;

	CString strMsg;

	try
	{
		if(nIndex == 0)
		{
			strMsg.Format(_T("> Invalid index. Zero is not permitted. (Share Tags)"));
			SendOutPutMessage(hwndOutput, strMsg);
			return false;
		}

		if(nIndex > nCount)
		{
			strMsg.Format(_T("> Invalid index. Out of range (%i - %i). (Share Tags)"), nIndex, nCount);
			SendOutPutMessage(hwndOutput, strMsg);

			return false;
		}

		ANDAFTER		= _T("AND");
		ANDBEFORE		= _T("AND");
		COMMAAFTER		= _T(",");
		COMMABEFORE		= _T(",");

		if(nIndex == 1)
		{
			ANDBEFORE		= _T("");
			COMMABEFORE		= _T("");
		}

		if(nIndex == nCount)
		{
			ANDAFTER		= _T("");
			COMMAAFTER		= _T("");
		}

		COUNT			    = Str(fieldcount);

		FIELD							= row->value[table->GetColumnOrdinal(_T("Name"))].data.szVal;
		TABLEFOREIGN					= row->value[table->GetColumnOrdinal(_T("TableForeignKey"))].data.szVal;
		TABLEFOREIGNWITHOUTPREFIXTABLE	= GetTableName(TABLEFOREIGN, prefixTable, FALSE);

		if (Item->Type == _T("CS"))
		{
			TYPEDATAFIELD					= GetTypeCS(row->value[table->GetColumnOrdinal(_T("DBType"))].data.szVal, false);
			TYPEDATAFIELD_NULLABLE			= GetTypeCS(row->value[table->GetColumnOrdinal(_T("DBType"))].data.szVal, true);
		}

		if (Item->Type == _T("C++"))
		{
			TYPEDATAFIELD					= GetTypePlusPlus(row->value[table->GetColumnOrdinal(_T("DBType"))].data.szVal, false);
			TYPEDATAFIELD_NULLABLE			= GetTypePlusPlus(row->value[table->GetColumnOrdinal(_T("DBType"))].data.szVal, true);
		}

		TYPEDBSQLSERVER		= GetSQLServerType(row->value[table->GetColumnOrdinal(_T("DBType"))].data.szVal, Str(row->value[table->GetColumnOrdinal(_T("DBSize"))].data.intVal));
		TYPEDBORACLE		= GetOracleType(row->value[table->GetColumnOrdinal(_T("DBType"))].data.szVal, Str(row->value[table->GetColumnOrdinal(_T("DBSize"))].data.intVal));
		TYPEDBPOSTGRESQL	= GetPostGreSQLType(row->value[table->GetColumnOrdinal(_T("DBType"))].data.szVal, Str(row->value[table->GetColumnOrdinal(_T("DBSize"))].data.intVal));
		TYPEDBMYSQL			= GetMySQLType(row->value[table->GetColumnOrdinal(_T("DBType"))].data.szVal, Str(row->value[table->GetColumnOrdinal(_T("DBSize"))].data.intVal));

		DBSIZE				= Str(row->value[table->GetColumnOrdinal(_T("DBSize"))].data.intVal);

		contentline.Replace(_T("#ANDBEFORE#"), ANDBEFORE);
		contentline.Replace(_T("#COMMABEFORE#"), COMMABEFORE);
		contentline.Replace(_T("#ANDAFTER#"), ANDAFTER);
		contentline.Replace(_T("#COMMAAFTER#"), COMMAAFTER);
		contentline.Replace(_T("#FIELD#"), FIELD);
		contentline.Replace(_T("#TABLEFOREIGN#"), TABLEFOREIGN);
		contentline.Replace(_T("#TABLEFOREIGNWITHOUTPREFIXTABLE#"), TABLEFOREIGNWITHOUTPREFIXTABLE);
		contentline.Replace(_T("#TYPECS#"), TYPEDATAFIELD);
		contentline.Replace(_T("#TYPECS_NULLABLE#"), TYPEDATAFIELD_NULLABLE);
		contentline.Replace(_T("#TYPEDBSQLSERVER#"), TYPEDBSQLSERVER);
		contentline.Replace(_T("#TYPEDBORACLE#"), TYPEDBORACLE);
		contentline.Replace(_T("#TYPEDBPOSTGRESQL#"), TYPEDBPOSTGRESQL);
		contentline.Replace(_T("#TYPEDBMYSQL#"), TYPEDBMYSQL);
		contentline.Replace(_T("#COUNT#"), COUNT);
		contentline.Replace(_T("#DBSIZE#"), DBSIZE);

		sourcecode += contentline;

		bRet = TRUE;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;

		strMsg.Format(_T("%s (Share Tags)"), m_Error);
		SendOutPutMessage(hwndOutput, strMsg);
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());

		strMsg.Format(_T("%s (Share Tags)"), m_Error);
		SendOutPutMessage(hwndOutput, strMsg);
	}

	return bRet;
}

BOOL CSHLStudioProject::ChangeShareTags(CProjectEntity* Project, CItemEntity* Item, CItemEntity* DatabaseProviderItem, HWND  hwndOutput, CString contentline, CString &sourcecode)
{
	BOOL bRet = FALSE;

	CString DATABASECATAGLOG;
	CString DATABASECATAGLOGDEBUG;
	CString DATABASEPWD;
	CString DATABASEPWDDEBUG;
	CString DATABASESERVER;
	CString DATABASESERVERDEBUG;
	CString DATABASEUSER;
	CString DATABASEUSERDEBUG;
	CString DATETIME;
	CString GRANTUSER;
	CString GRANTUSERDEBUG;
	CString NAMESPACEDAL;
	CString NAMESPACEBLL;
	CString NAMESPACEENTITY;
	CString NAMESPACECONTROLLER;
	CString PREFIXDAL;
	CString PREFIXBLL;
	CString PREFIXENTITY;
	CString PREFIXCONTROLLER;
	CString SUFFIXDAL;
	CString SUFFIXBLL;
	CString SUFFIXENTITY;
	CString SUFFIXCONTROLLER;
	CString VERSION;
	CString AUTHOR;

	CString key;

	try
	{
		key = _T("ProductionConnectionDatabase");
		DATABASECATAGLOG = DatabaseProviderItem->Properties[key];
		contentline.Replace(_T("#DATABASECATAGLOG#"), DATABASECATAGLOG);

		key = _T("DebugConnectionDatabase");
		DATABASECATAGLOGDEBUG = DatabaseProviderItem->Properties[key];
		contentline.Replace(_T("#DATABASECATAGLOGDEBUG#"), DATABASECATAGLOGDEBUG);

		key = _T("ProductionConnectionPwd");
		DATABASEPWD = DatabaseProviderItem->Properties[key];
		contentline.Replace(_T("#DATABASEPWD#"), DATABASEPWD);

		key = _T("DebugConnectionPwd");
		DATABASEPWDDEBUG = DatabaseProviderItem->Properties[key];
		contentline.Replace(_T("#DATABASEPWDDEBUG#"), DATABASEPWDDEBUG);

		key = _T("ProductionConnectionServer");
		DATABASESERVER = DatabaseProviderItem->Properties[key];
		contentline.Replace(_T("#DATABASESERVER#"), DATABASESERVER);

		key = _T("DebugConnectionServer");
		DATABASESERVERDEBUG = DatabaseProviderItem->Properties[key];
		contentline.Replace(_T("#DATABASESERVERDEBUG#"), DATABASESERVERDEBUG);

		key = _T("ProductionConnectionUser");
		DATABASEUSER = DatabaseProviderItem->Properties[key];
		contentline.Replace(_T("#DATABASEUSER#"), DATABASEUSER);

		key = _T("DebugConnectionUser");
		DATABASEUSERDEBUG = DatabaseProviderItem->Properties[key];
		contentline.Replace(_T("#DATABASEUSERDEBUG#"), DATABASEUSERDEBUG);

		GRANTUSER = DATABASEUSER;
		contentline.Replace(_T("#GRANTUSER#"), GRANTUSER);

		GRANTUSERDEBUG = DATABASEUSERDEBUG;
		contentline.Replace(_T("#GRANTUSERDEBUG#"), GRANTUSERDEBUG);

		CTime tm = CTime::GetCurrentTime();;
		DToC(tm, DATETIME, DT_DATETIME);
		contentline.Replace(_T("#DATETIME#"), DATETIME);

		key = _T("NamespaceDAL");
		NAMESPACEDAL = Item->Properties[key];
		contentline.Replace(_T("#NAMESPACEDAL#"), NAMESPACEDAL);

		key = _T("NamespaceDAL");
		NAMESPACEDAL = Item->Properties[key];
		contentline.Replace(_T("#NAMESPACEDAL#"), NAMESPACEDAL);

		key = _T("NamespaceBLL");
		NAMESPACEBLL = Item->Properties[key];
		contentline.Replace(_T("#NAMESPACEBLL#"), NAMESPACEBLL);

		key = _T("NamespaceEntity");
		NAMESPACEENTITY = Item->Properties[key];
		contentline.Replace(_T("#NAMESPACEENTITY#"), NAMESPACEENTITY);

		key = _T("NamespaceController");
		NAMESPACECONTROLLER = Item->Properties[key];
		contentline.Replace(_T("#NAMESPACECONTROLLER#"), NAMESPACECONTROLLER);

		key = _T("PrefixDAL");
		PREFIXDAL = Item->Properties[key];
		contentline.Replace(_T("#PREFIXDAL#"), PREFIXDAL);

		key = _T("PrefixBLL");
		PREFIXBLL = Item->Properties[key];
		contentline.Replace(_T("#PREFIXBLL#"), PREFIXBLL);

		key = _T("PrefixEntity");
		PREFIXENTITY = Item->Properties[key];
		contentline.Replace(_T("#PREFIXENTITY#"), PREFIXENTITY);

		key = _T("PrefixController");
		PREFIXCONTROLLER = Item->Properties[key];
		contentline.Replace(_T("#PREFIXCONTROLLER#"), PREFIXCONTROLLER);

		key = _T("SuffixDAL");
		SUFFIXDAL = Item->Properties[key];
		contentline.Replace(_T("#SUFFIXDAL#"), SUFFIXDAL);

		key = _T("SuffixBLL");
		SUFFIXBLL = Item->Properties[key];
		contentline.Replace(_T("#SUFFIXBLL#"), SUFFIXBLL);

		key = _T("SuffixEntity");
		SUFFIXENTITY = Item->Properties[key];
		contentline.Replace(_T("#SUFFIXENTITY#"), SUFFIXENTITY);

		key = _T("SuffixController");
		SUFFIXCONTROLLER = Item->Properties[key];
		contentline.Replace(_T("#SUFFIXCONTROLLER#"), SUFFIXCONTROLLER);

		key = _T("VERSION");
		VERSION = Project->Properties[key];
		contentline.Replace(_T("#VERSION#"), VERSION);

		key = _T("AUTHOR");
		AUTHOR = Project->Properties[key];
		contentline.Replace(_T("#AUTHOR#"), AUTHOR);

		key = _T("\t");
		contentline.Replace(_T("#TAB#"), key);
		sourcecode += contentline;

		bRet = TRUE;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

CString CSHLStudioProject::GetTableName(CString tableName, INT prefixTable, BOOL firtUpperCase)
{
	CString tablename;
	CString auxtablename;
	BOOL bfirstcaracter = TRUE;

	try
	{
		if (!firtUpperCase)
		{
			if (tableName.GetLength() > prefixTable && prefixTable != 0)
			{
				tablename = tableName.Mid((prefixTable));
			}
			else
			{
				tablename = tableName;
			}
		}
		else
		{
			if (tableName.GetLength() > prefixTable && prefixTable != 0)
			{
				auxtablename = tableName.Mid((prefixTable));
			}
			else
			{
				auxtablename = tableName;
			}

			for (INT index = 0; index < auxtablename.GetLength(); index++)
			{
				if (CString(auxtablename[index]) != _T("_"))
				{
					if (bfirstcaracter)
						tablename += CString(auxtablename[index]).MakeUpper();
					else
						tablename += CString(auxtablename[index]).MakeLower();

					bfirstcaracter = FALSE;
				}
				else
					bfirstcaracter = TRUE;
			}

		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return tablename;
}

CString CSHLStudioProject::GetTypePlusPlus(CString type, bool nullable)
{
	CString typereturn;
	CString Nullable;

	try
	{
		type.Replace(_T("DateTime2"), _T("DateTime"));
		type.Replace(_T("DateTime3"), _T("DateTime"));
		type.Replace(_T("DateTime4"), _T("DateTime"));

		if (nullable)
			Nullable = _T("*");
		else
			Nullable = _T("");

		if (type == _T("BYTE"))
			typereturn.Format(_T("BYTE%s"), Nullable);

		if(type == _T("Int16"))
			typereturn.Format(_T("SHORT%s"), Nullable);

		if (type == _T("Int32"))
			typereturn.Format(_T("INT%s"), Nullable);

		if (type == _T("Int64"))
			typereturn.Format(_T("LONG%s"), Nullable);

		if (type == _T("Boolean"))
			typereturn.Format(_T("BOOL%s"), Nullable);

		if (type == _T("DateTime"))
			typereturn.Format(_T("CTime%s"), Nullable);

		if (type == _T("Double"))
			typereturn.Format(_T("DOUBLE%s"), Nullable);

		if (type == _T("String"))
			typereturn.Format(_T("%sWSTR"), nullable?_T("LP"):_T(""));
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return typereturn;
}

CString CSHLStudioProject::GetTypeCS(CString type, bool nullable)
{
	CString typereturn;

	try
	{
		type.Replace(_T("DateTime2"), _T("DateTime"));
		type.Replace(_T("DateTime3"), _T("DateTime"));
		type.Replace(_T("DateTime4"), _T("DateTime"));
		type.Replace(_T("Text"), _T("String"));

		typereturn = type;

		if (nullable)
		{
			if (type == _T("Byte") || type == _T("Int16") || type == _T("Int32") || type == _T("Int64") || type == _T("Boolean") || type == _T("DateTime") || type == _T("Double"))
			{
				typereturn.Format(_T("Nullable<%s>"), type);
			}
		}
	}
	catch (CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch (...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return typereturn;
}

CString CSHLStudioProject::GetAccessType(CString type, CString size)
{
	CString accesstype;

	try
	{
		if(type == _T("Byte"))
			accesstype = _T("byte");
		else
		if(type == _T("Int16"))
			accesstype = _T("integer");
		else
		if(type == _T("Int32"))
			accesstype = _T("single");
		else
		if(type == _T("Int64"))
			accesstype = _T("long");
		else
		if(type == _T("Boolean"))
			accesstype = _T("boolean");
		else
		if(type == _T("String"))
			accesstype = _T("string");
		else
		if(type == _T("DateTime"))
			accesstype = _T("date");
		else
		if(type == _T("DateTime2"))
			accesstype = _T("date");
		else
		if(type == _T("DateTime3"))
			accesstype = _T("date");
		else
		if(type == _T("DateTime4"))
			accesstype = _T("date");
		else
		if(type == _T("Double"))
			accesstype = _T("double");
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return accesstype;
}

CString CSHLStudioProject::GetSQLServerType(CString type, CString size)
{
	CString sqlservertype;

	try
	{
		if(type == _T("Byte"))
			sqlservertype = _T("TINYINT");
		else
		if(type == _T("Int16"))
			sqlservertype = _T("SMALLINT");
		else
		if(type == _T("Int32"))
			sqlservertype = _T("INT");
		else
		if(type == _T("Int64"))
			sqlservertype = _T("BIGINT");
		else
		if(type == _T("Boolean"))
			sqlservertype = _T("BIT");
		else
		if(type == _T("Text"))
			sqlservertype = _T("TEXT");
		else
		if(type == _T("String"))
			sqlservertype.Format(_T("VARCHAR(%s)"), size);
		else
		if(type == _T("DateTime"))
			sqlservertype = _T("DATETIME");
		else
		if(type == _T("DateTime2"))
			sqlservertype = _T("DATETIME");
		else
		if(type == _T("DateTime3"))
			sqlservertype = _T("DATETIME");
		else
		if(type == _T("DateTime4"))
			sqlservertype = _T("DATETIME");
		else
		if(type == _T("Double"))
			sqlservertype = _T("FLOAT");
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return sqlservertype;
}

CString CSHLStudioProject::GetOracleType(CString type, CString size)
{
	CString oracletype;

	try
	{
		if(type == _T("Byte"))
			oracletype = _T("INTEGER");
		else
		if(type == _T("Int16"))
			oracletype = _T("INTEGER");
		else
		if(type == _T("Int32"))
			oracletype = _T("INTEGER");
		else
		if(type == _T("Int64"))
			oracletype = _T("LONG");
		else
		if(type == _T("Boolean"))
			oracletype = _T("INTEGER");
		else
		if(type == _T("String"))
			oracletype = _T("VARCHAR2");
		else
		if(type == _T("DateTime"))
			oracletype = _T("DATE");
		else
		if(type == _T("DateTime2"))
			oracletype = _T("TIMESTAMP");
		else
		if(type == _T("DateTime3"))
			oracletype = _T("TIMESTAMP");
		else
		if(type == _T("DateTime4"))
			oracletype = _T("TIMESTAMP");
		else
		if(type == _T("Double"))
			oracletype = _T("BINARY_DOUBLE");
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return oracletype;
}

CString CSHLStudioProject::GetPostGreSQLType(CString type, CString size)
{
	CString postgresqltype;

	try
	{
		if(type == _T("Byte"))
			postgresqltype = _T("integer");
		else
		if(type == _T("Int16"))
			postgresqltype = _T("integer");
		else
		if(type == _T("Int32"))
			postgresqltype = _T("integer");
		else
		if(type == _T("Int64"))
			postgresqltype = _T("bigint");
		else
		if(type == _T("Boolean"))
			postgresqltype = _T("boolean");
		else
		if(type == _T("String"))
		{
			if(size == _T("0"))
				postgresqltype = _T("text");
			else
				postgresqltype.Format(_T("varchar(%s)"), size);
		}
		else
		if(type == _T("DateTime"))
			postgresqltype = _T("date");
		else
		if(type == _T("DateTime2"))
			postgresqltype = _T("time");
		else
		if(type == _T("DateTime3"))
			postgresqltype = _T("timestamp");
		else
		if(type == _T("DateTime4"))
			postgresqltype = _T("time without time zone");
		else
		if(type == _T("Double"))
			postgresqltype = _T("double");
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return postgresqltype;
}

CString CSHLStudioProject::GetMySQLType(CString type, CString size)
{
	CString mysqltype;

	try
	{
		if(type == _T("Byte"))
			mysqltype = _T("TINYINT");
		else
		if(type == _T("Int16"))
			mysqltype = _T("SMALLINT");
		else
		if(type == _T("Int32"))
			mysqltype = _T("MEDIUMINT");
		else
		if(type == _T("Int64"))
			mysqltype = _T("BIGINT");
		else
		if(type == _T("Boolean"))
			mysqltype = _T("BIT");
		else
		if(type == _T("String"))
		{
			if(size == _T("0") || size == 255 )
				mysqltype = _T("TEXT");
			else
				mysqltype.Format(_T("VARCHAR(%s)"), size);
		}
		else
		if(type == _T("DateTime"))
			mysqltype = _T("DATE");
		else
		if(type == _T("DateTime2"))
			mysqltype = _T("TIME");
		else
		if(type == _T("DateTime3"))
			mysqltype = _T("TIMESTAMP");
		else
		if(type == _T("DateTime4"))
			mysqltype = _T("DATETIME");
		else
		if(type == _T("Double"))
			mysqltype = _T("DOUBLE");
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	return mysqltype;
}

BOOL CSHLStudioProject::GenerateSourceCodeStandAlone(CProjectEntity* Project, CItemEntity* Item, CItemEntity* DatabaseProviderItem, HWND  hwndOutput, CString &sourcecode)
{
	BOOL bRet = false;

	CFread fread;
	CPath path;

	CString filename;
	BOOL bComplete = true;
	CString strMsg;
	BOOL bStillRead = true;
	CString contentline;
	CString contentlinetotreat;
	SHLTEMPLATESTATETOREAD state = SHLTEMPLATESTATETOREAD_IDLE;
	SHLTEMPLATESTATETOREAD substateforeignkey = SHLTEMPLATESTATETOREAD_IDLE;

	try
	{
		do
		{
			path.AddPath(2, Item->Path, Item->FileName);
			filename = path.GetPath();

			if(!path.ExistFile())
			{
				strMsg.Format(_T("File '%s' does not exists. (StandAlone)"), path.GetPath());
				SendOutPutMessage(hwndOutput, strMsg);

				break;
			}

			if(!fread.Open(filename))
			{
				strMsg.Format(_T("Can not open '%s' file. (StandAlone)"), filename);
				SendOutPutMessage(hwndOutput, strMsg);

				break;
			}

			while(!fread.Eof())
			{
				fread.Read();

				contentline = fread.GetContent();

				if (contentline.Find(_T("<alltables>")) > -1)
				{
					RepeatCodeToAllTables(fread, Project, Item, DatabaseProviderItem, hwndOutput, sourcecode);
				}
				else
				{
					if (!ChangeShareTags(Project, Item, DatabaseProviderItem, hwndOutput, contentline, sourcecode))
					{
						bComplete = false;
						break;
					}
				}

				sourcecode += _T("\n");
			}
		}
		while(false);

		if (bComplete)
			bComplete = ChangeSpecialTags(hwndOutput, sourcecode);

		bRet = bComplete;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;

		strMsg.Format(_T("%s (StandAlone)"), m_Error);
		SendOutPutMessage(hwndOutput, strMsg);
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());

		strMsg.Format(_T("%s (StandAlone)"), m_Error);
		SendOutPutMessage(hwndOutput, strMsg);
	}

	if(fread.IsOpen())
		fread.Close();

	return bRet;
}

BOOL CSHLStudioProject::RepeatCodeToAllTables(CFread& fread, CProjectEntity* Project, CItemEntity* Item, CItemEntity* DatabaseProviderItem, HWND  hwndOutput, CString &sourcecode)
{
	BOOL bRet = FALSE;
	CStringArray arLines;
	CString contentline;
	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table = NULL;
	CString strMsg;

	CPath path;

	try
	{
		reader = LoadDTFileToReader(DatabaseProviderItem);
		if (!reader)
		{
			strMsg.Format(_T("> Can not load properties from '%s' file."), DatabaseProviderItem->Name);
			SendOutPutMessage(hwndOutput, strMsg);
			strMsg = _T("> Build canceled.");
			SendOutPutMessage(hwndOutput, strMsg);

			return false;
		}

		while (!fread.Eof())
		{
			fread.Read();
			
			contentline = fread.GetContent();

			if (contentline.Find(_T("</alltables>")) > -1)
				break;

			arLines.Add(contentline);
		}

		for (UINT nIndexTable = 0; nIndexTable < reader->Tables.GetCount(); nIndexTable++)
		{
			table = reader->Tables.GetAt(nIndexTable);

			if (!ReadToAllTables(arLines, table, Project, Item, DatabaseProviderItem, hwndOutput, sourcecode))
			{
				strMsg = _T("> Build canceled.");
				SendOutPutMessage(hwndOutput, strMsg);

				return false;
			}
		}

		bRet = TRUE;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;

		SendOutPutMessage(hwndOutput, m_Error);
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());

		SendOutPutMessage(hwndOutput, m_Error);
	}

	if (!reader)
		delete reader;

	return bRet;
}
	
BOOL CSHLStudioProject::ReadToAllTables(CStringArray& arLines, SHLOleDBTable* table, CProjectEntity* Project, CItemEntity* Item, CItemEntity* DatabaseProviderItem, HWND  hwndOutput, CString &sourcecode)
{
	BOOL bRet = FALSE;
	BOOL bComplete = TRUE;

	CPath path;
	CString contentline;
	CString contentlinetotreat;
	SHLTEMPLATESTATETOREAD state = SHLTEMPLATESTATETOREAD_IDLE;
	SHLTEMPLATESTATETOREAD substateforeignkey = SHLTEMPLATESTATETOREAD_IDLE;
	BOOL bStillRead = true;
	BOOL bHasForeignkey = false;
	CString key;
	CString sPrefixTable;
	INT prefixTable;
	UINT initcount;
	CString strMsg;
	int nCurrentLine = -1;

	try
	{
		bComplete = TRUE;
		do
		{
			bHasForeignkey = HasTableForeignkey(table);

			key = _T("PrefixTable");
			sPrefixTable = Item->Properties[key];
			if(sPrefixTable.IsEmpty())
				prefixTable = 0;
			else
				Val(sPrefixTable, prefixTable);

			while(bStillRead)
			{
				switch(state)
				{
					case SHLTEMPLATESTATETOREAD_IDLE:
						contentlinetotreat = _T("");
						state = SHLTEMPLATESTATETOREAD_READLINE;
						substateforeignkey = SHLTEMPLATESTATETOREAD_IDLE;

						break;
					case SHLTEMPLATESTATETOREAD_READLINE:
						if (nCurrentLine >= arLines.GetCount())
						{
							state = SHLTEMPLATESTATETOREAD_IDLE;
							bStillRead = false;
						}
						else
						{
							state = SHLTEMPLATESTATETOREAD_GETLINE;
							nCurrentLine++;
							if (nCurrentLine >= arLines.GetCount())
							{
								state = SHLTEMPLATESTATETOREAD_IDLE;
								//bComplete = FALSE;
								bStillRead = false;
							}
						}

						break;
					case SHLTEMPLATESTATETOREAD_READLINE_ALLFIELDS:
						if (nCurrentLine >= arLines.GetCount())
						{
							state = SHLTEMPLATESTATETOREAD_IDLE;

							strMsg.Format(_T("> Unexpected end of file. (ALL FIELDS"));
							SendOutPutMessage(hwndOutput, strMsg);

							bComplete = FALSE;
							bStillRead = false;
						}
						else
						{
							state = SHLTEMPLATESTATETOREAD_GETLINE_ALLFIELDS;
							nCurrentLine++;
							if (nCurrentLine >= arLines.GetCount())
							{
								state = SHLTEMPLATESTATETOREAD_IDLE;
								bComplete = FALSE;
								bStillRead = false;
							}
						}

						break;
					case SHLTEMPLATESTATETOREAD_READLINE_FOREIGNKEY:
						if (nCurrentLine >= arLines.GetCount())
						{
							state = SHLTEMPLATESTATETOREAD_IDLE;

							strMsg.Format(_T("> Unexpected end of file. (FOREIGN KEY)"));
							SendOutPutMessage(hwndOutput, strMsg);

							bComplete = FALSE;
							bStillRead = false;
						}
						else
						{
							state = SHLTEMPLATESTATETOREAD_GETLINE_FOREIGNKEY;
							nCurrentLine++;
							if (nCurrentLine >= arLines.GetCount())
							{
								state = SHLTEMPLATESTATETOREAD_IDLE;
								bComplete = FALSE;
								bStillRead = false;
							}
						}

						break;
					case SHLTEMPLATESTATETOREAD_GETLINE:
						contentline = arLines.GetAt(nCurrentLine);
							
						switch (substateforeignkey)
						{
							case SHLTEMPLATESTATETOREAD_IDLE:
								if(contentline.Find(_T("<ifexistforeignkey>")) > -1)
								{
									substateforeignkey = SHLTEMPLATESTATETOREAD_WAITFORENDFOREIGNKEY;
									state = SHLTEMPLATESTATETOREAD_READLINE;
								}
								else
								{
									if(contentline.Find(_T("<allfieldslessprimarykey>"))  > -1)
									{
										state = SHLTEMPLATESTATETOREAD_READLINE_ALLFIELDS;
										contentlinetotreat = _T("");
										initcount = GetInitCount(contentline);
									}
									else
									if(contentline.Find(_T("<allfieldsforeignkey>"))  > -1)
									{
										state = SHLTEMPLATESTATETOREAD_READLINE_FOREIGNKEY;
										contentlinetotreat = _T("");

										initcount = GetInitCount(contentline);
									}
									else
									{
										state = SHLTEMPLATESTATETOREAD_TREATLINE;
										contentlinetotreat = contentline;
									}
								}
								break;
							case SHLTEMPLATESTATETOREAD_WAITFORENDFOREIGNKEY:
								if(contentline.Find(_T("</ifexistforeignkey>")) > -1)
								{
									substateforeignkey = SHLTEMPLATESTATETOREAD_IDLE;
									state = SHLTEMPLATESTATETOREAD_READLINE;
									contentlinetotreat = _T("");
								}
								else
								{
									if(bHasForeignkey)
									{
										if(contentline.Find(_T("<allfieldslessprimarykey>"))  > -1)
										{
											state = SHLTEMPLATESTATETOREAD_READLINE_ALLFIELDS;
											contentlinetotreat = _T("");
											initcount = GetInitCount(contentline);
										}
										else
										if(contentline.Find(_T("<allfieldsforeignkey>"))  > -1)
										{
											state = SHLTEMPLATESTATETOREAD_READLINE_FOREIGNKEY;
											contentlinetotreat = _T("");

											initcount = GetInitCount(contentline);
										}
										else
										{
											contentlinetotreat += contentline;
											state = SHLTEMPLATESTATETOREAD_TREATLINE;
										}
									}
									else
									{
										contentlinetotreat = _T("");
										state = SHLTEMPLATESTATETOREAD_READLINE;
									}
								}
								break;
						}
						break;
					case SHLTEMPLATESTATETOREAD_GETLINE_ALLFIELDS:
						contentline = arLines.GetAt(nCurrentLine);

						if(contentline.Find(_T("</allfieldslessprimarykey>")) > -1)
						{
							state = SHLTEMPLATESTATETOREAD_TREATLINE_ALLFIELDS;
						}
						else
						{
							if(contentlinetotreat.GetLength() > 0)
								contentlinetotreat += _T("\n");

							contentlinetotreat += contentline;
							state = SHLTEMPLATESTATETOREAD_READLINE_ALLFIELDS;
						}

						break;
					case SHLTEMPLATESTATETOREAD_GETLINE_FOREIGNKEY:
						contentline = arLines.GetAt(nCurrentLine);

						if(contentline.Find(_T("</allfieldsforeignkey>")) > -1)
						{
							state = SHLTEMPLATESTATETOREAD_TREATLINE_FOREIGNKEY;
						}
						else
						{
							if(contentlinetotreat.GetLength() > 0)
								contentlinetotreat += _T("\n");

							contentlinetotreat += contentline;
							state = SHLTEMPLATESTATETOREAD_READLINE_FOREIGNKEY;
						}

						break;
					case SHLTEMPLATESTATETOREAD_TREATLINE_ALLFIELDS:
						{
							CString intermediate;
							CString contentlinebyFields;
							CString value;
							BOOL bPrimarykey;
							SHLDBROW *row = NULL;
							UINT nCount = 0;
							UINT nIndex = 0;
							UINT fieldcount = initcount;

							for(UINT nIndexFields = 0; nIndexFields < table->Rows.GetCount(); nIndexFields++)
							{
								bPrimarykey = table->GetBoolean(nIndexFields, table->GetColumnOrdinal(_T("PrimaryKey")));
									
								if(!bPrimarykey)
									nCount++;								
							}

							for(UINT nIndexFields = 0; nIndexFields < table->Rows.GetCount(); nIndexFields++)
							{
								row = table->Rows.GetAt(nIndexFields);

								bPrimarykey = table->GetBoolean(nIndexFields, table->GetColumnOrdinal(_T("PrimaryKey")));
									
								if(!bPrimarykey)
								{
									nIndex++;
									intermediate = _T("");
									if(!ChangeShareTags(Project, Item, DatabaseProviderItem, hwndOutput, contentlinetotreat, intermediate))
									{
										strMsg.Format(_T("> Error 'Share Tags' routine. (ALL FIELDS)"));
										SendOutPutMessage(hwndOutput, strMsg);

										bComplete = FALSE;
										bStillRead = false;
									}

									contentlinebyFields = intermediate;
									intermediate =  _T("");
									if (!ChangeTableTags(Project, Item, table, prefixTable, hwndOutput, contentlinebyFields, intermediate))
									{
										strMsg.Format(_T("> Error 'Table Tags' routine. (ALL FIELDS)"));
										SendOutPutMessage(hwndOutput, strMsg);

										bComplete = FALSE;
										bStillRead = false;
									}

									contentlinebyFields = intermediate;
									intermediate =  _T("");
									if (!ChangeFieldsTags(Project, Item, table, prefixTable, row, nIndex, nCount, hwndOutput, contentlinebyFields, intermediate, fieldcount))
									{
										strMsg.Format(_T("> Error 'Field Tags' routine. (ALL FIELDS)"));
										SendOutPutMessage(hwndOutput, strMsg);

										bComplete = FALSE;
										bStillRead = false;
									}

									sourcecode += intermediate;
									sourcecode += _T("\n");

									fieldcount++;
								}
							}
						}

						state = SHLTEMPLATESTATETOREAD_READLINE;
						break;
					case SHLTEMPLATESTATETOREAD_TREATLINE_FOREIGNKEY:
						{
							CString intermediate;
							CString contentlinebyFields;
							CString value;
							BOOL bForeingkey;
							SHLDBROW *row = NULL;
							UINT nCount = 0;
							UINT nIndex = 0;
							UINT fieldcount = initcount;

							for(UINT nIndexFields = 0; nIndexFields < table->Rows.GetCount(); nIndexFields++)
							{
								bForeingkey = table->GetBoolean(nIndexFields, table->GetColumnOrdinal(_T("ForeignKey")));
									
								if(bForeingkey)
									nCount++;								
							}

							for(UINT nIndexFields = 0; nIndexFields < table->Rows.GetCount(); nIndexFields++)
							{
								row = table->Rows.GetAt(nIndexFields);

								bForeingkey = table->GetBoolean(nIndexFields, table->GetColumnOrdinal(_T("ForeignKey")));
									
								if(bForeingkey)
								{
									nIndex++;
									intermediate = _T("");
									if(!ChangeShareTags(Project, Item, DatabaseProviderItem, hwndOutput, contentlinetotreat, intermediate))
									{
										strMsg.Format(_T("> Error 'Share Tags' routine. (FOREIGN KEY)"));
										SendOutPutMessage(hwndOutput, strMsg);

										bComplete = FALSE;
										bStillRead = false;
									}

									contentlinebyFields = intermediate;
									intermediate =  _T("");
									if (!ChangeTableTags(Project, Item, table, prefixTable, hwndOutput, contentlinebyFields, intermediate))
									{
										strMsg.Format(_T("> Error 'Table Tags' routine. (FOREIGN KEY)"));
										SendOutPutMessage(hwndOutput, strMsg);

										bComplete = FALSE;
										bStillRead = false;
									}

									contentlinebyFields = intermediate;
									intermediate =  _T("");
									if (!ChangeFieldsTags(Project, Item, table, prefixTable, row, nIndex, nCount, hwndOutput, contentlinebyFields, intermediate, fieldcount))
									{
										strMsg.Format(_T("> Error 'Fields Tags' routine. (FOREIGN KEY)"));
										SendOutPutMessage(hwndOutput, strMsg);

										bComplete = FALSE;
										bStillRead = false;
									}

									sourcecode += intermediate;
									sourcecode += _T("\n");

									fieldcount++;
								}
							}
						}

						state = SHLTEMPLATESTATETOREAD_READLINE;
						break;
					case SHLTEMPLATESTATETOREAD_TREATLINE:
						{
							CString intermadiate;
							if(!ChangeShareTags(Project, Item, DatabaseProviderItem, hwndOutput, contentline, intermadiate))
							{
								strMsg.Format(_T("> Error 'Share Tags' routine. (COMMON)"));
								SendOutPutMessage(hwndOutput, strMsg);

								bComplete = FALSE;
								bStillRead = false;
							}

							contentline = intermadiate;
							intermadiate = _T("");
							if (!ChangeTableTags(Project, Item, table, prefixTable, hwndOutput, contentline, intermadiate))
							{
								strMsg.Format(_T("> Error 'Table Tags' routine. (COMMON)"));
								SendOutPutMessage(hwndOutput, strMsg);

								bComplete = FALSE;
								bStillRead = false;
							}

							contentline = intermadiate;
							intermadiate = _T("");
							if (!ChangePrimarykeyTags(Project, Item, table, hwndOutput, contentline, intermadiate))
							{
								strMsg.Format(_T("> Error 'Primary Key Tags' routine. (COMMON)"));
								SendOutPutMessage(hwndOutput, strMsg);

								bComplete = FALSE;
								bStillRead = false;
							}

							sourcecode += intermadiate;
							sourcecode += _T("\n");
						}

						state = SHLTEMPLATESTATETOREAD_READLINE;
						break;
				}
			}
		}
		while(false);

		bRet = bComplete;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;

		SendOutPutMessage(hwndOutput, m_Error);
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());

		SendOutPutMessage(hwndOutput, m_Error);
	}

	return bRet;




}

CString CSHLStudioProject::SelectFile(CString strFileName, CString strDefaultExt, CString strFilter)
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
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}

	if(dlg)
		delete dlg;

	return strFullFileName;
}

void  CSHLStudioProject::SendOutPutMessage(HWND hwndOutput, CString message)
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

		m_Error =  szMessage;
	}
	catch(...)
	{
		m_Error = ErrorMessage(::GetLastError());
	}
}
#pragma endregion PRIVATE_METHODS
/***********************************************************************************
 *                                                                                 *
 * Cria um objeto GetSHLStudioProjectInstance.                                     *
 *                                                                                 *
 ***********************************************************************************/
SHLSTUDIOPROJECT_API SHLSTUDIOPROJECTHANDLE APIENTRY GetSHLStudioProjectInstance()
{
	return new CSHLStudioProject;
}
