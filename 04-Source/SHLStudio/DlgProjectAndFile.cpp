/* ***************************************************************************
 * Arquivo: DlgProjectAndFile.cpp                                            *
 *                                                                           *
 * Classe de tela criada para criar uma nova solução no SHLStudio.           *
 *                                                                           *
 * Data:26/03/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */

#include "stdafx.h"
#include "SHLStudio.h"
#include "DlgProjectAndFile.h"
#include "afxdialogex.h"
#include "ProjectWrapper.h"
#include "Markup.h"

int CALLBACK SetSelProcDlgProject(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

BEGIN_ANCHOR_MAP(CDlgProjectAndFile)
    ANCHOR_MAP_ENTRY(IDC_TREE_GROUP_PROJECT_FILE,       ANF_TOP | ANF_BOTTOM | ANF_LEFT)
    ANCHOR_MAP_ENTRY(IDC_LIST_PROJECT_FILE,				ANF_TOP | ANF_BOTTOM | ANF_LEFT | ANF_RIGHT)
    ANCHOR_MAP_ENTRY(IDC_EDIT_DESCRIPTION,				ANF_TOP | ANF_BOTTOM | ANF_RIGHT)

    ANCHOR_MAP_ENTRY(IDC_STATIC_NAME,					ANF_BOTTOM | ANF_LEFT)
    ANCHOR_MAP_ENTRY(IDC_EDIT_NAME,						ANF_BOTTOM | ANF_LEFT | ANF_RIGHT)
    ANCHOR_MAP_ENTRY(IDC_STATIC_LOCATION,				ANF_BOTTOM | ANF_LEFT)
    ANCHOR_MAP_ENTRY(IDC_EDIT_LOCATION,					ANF_BOTTOM | ANF_LEFT | ANF_RIGHT)
    ANCHOR_MAP_ENTRY(IDC_BUTTON_BROWSER_LOCATION,		ANF_BOTTOM | ANF_RIGHT)

    ANCHOR_MAP_ENTRY(IDOK,								ANF_BOTTOM | ANF_RIGHT)
    ANCHOR_MAP_ENTRY(IDCANCEL,							ANF_BOTTOM | ANF_RIGHT)
END_ANCHOR_MAP()

// CDlgProjectAndFile dialog

IMPLEMENT_DYNAMIC(CDlgProjectAndFile, CDialogEx)

CDlgProjectAndFile::CDlgProjectAndFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgProjectAndFile::IDD, pParent)
{
	m_targetPath = _T("");
	m_projectType	= _T("");
	m_dialogType	= SHLTYPEDLGPROJECTANDFILE_PROJECT;
	m_elements = NULL;
	m_image = NULL;
	m_ItemList = NULL;
	m_Item = NULL;
	m_ProjectList = NULL;
	m_Project = NULL;
	m_mapIcons = NULL;
}

CDlgProjectAndFile::~CDlgProjectAndFile()
{
	Release();
}

void CDlgProjectAndFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_GROUP_PROJECT_FILE, m_ctrlGroupProjectItem);
	DDX_Control(pDX, IDC_LIST_PROJECT_FILE, m_ctrlProjectItem);
	DDX_Control(pDX, IDC_EDIT_DESCRIPTION, m_txtDescription);
	DDX_Control(pDX, IDC_EDIT_NAME, m_txtName);
	DDX_Control(pDX, IDC_EDIT_LOCATION, m_txtLocation);
	DDX_Control(pDX, IDC_BUTTON_BROWSER_LOCATION, m_cmdBrowse);
	DDX_Control(pDX, IDC_COMBO_CATEGORY, m_cmbCategory);
}


BEGIN_MESSAGE_MAP(CDlgProjectAndFile, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BROWSER_LOCATION, OnBnClickedButtonBrowserLocation)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)

	ON_NOTIFY(NM_CLICK, IDC_TREE_GROUP_PROJECT_FILE,  OnButtonDown)
	ON_CBN_SELCHANGE(IDC_COMBO_CATEGORY, &CDlgProjectAndFile::OnCbnSelchangeComboCategory)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PROJECT_FILE, &CDlgProjectAndFile::OnNMClickListProjectFile)
END_MESSAGE_MAP()

#pragma region EVENTS
// CDlgProjectAndFile message handlers
BOOL CDlgProjectAndFile::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rcWnd;
	GetWindowRect(&rcWnd);

	m_nMinSizeX = rcWnd.right - rcWnd.left ;
	m_nMinSizeY = rcWnd.bottom - rcWnd.top;
                   
	InitAnchors(ANIF_SIZEGRIP);

	::SetWindowTheme(m_ctrlGroupProjectItem.GetSafeHwnd(), L"Explorer", NULL);

	m_ctrlProjectItem.InsertColumn(0, _T("Type"));

	SetDialog();

	SelectProjectItemTemplate();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgProjectAndFile::OnNMClickListProjectFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	SelectedList();

	*pResult = 0;
}

void CDlgProjectAndFile::OnBnClickedButtonBrowserLocation()
{
	BrowserLocation();
}

void CDlgProjectAndFile::OnCbnSelchangeComboCategory()
{
	CategorySelChanged();
}

void CDlgProjectAndFile::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rcWnd;
	GetWindowRect(&rcWnd);
  
	HandleAnchors(&rcWnd);     // you can alternatively pass NULL for &rcWnd
	Invalidate(false);         // this is for ensuring the controls to be redrawn correctly 
}


void CDlgProjectAndFile::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	
    // Set the Minimum Track Size. Used while resizing.
    lpMMI->ptMinTrackSize.x = m_nMinSizeX;
    lpMMI->ptMinTrackSize.y = m_nMinSizeY;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


BOOL CDlgProjectAndFile::OnEraseBkgnd(CDC* pDC)
{
	return(m_bpfxAnchorMap.EraseBackground(pDC->m_hDC));
}

void CDlgProjectAndFile::OnButtonDown(NMHDR* pNMHDR, LRESULT* pResult)
{
	HTREEITEM  item = GetItemSelected();

	m_hItemselected = item;

	ButtonDown(item);

	*pResult = 0;
}

void CDlgProjectAndFile::OnBnClickedOk()
{
	if(!AddNew())
		return;

	CDialogEx::OnOK();
}
#pragma endregion EVENTS

#pragma region PRIVATE_METHODS
void CDlgProjectAndFile::ButtonDown(HTREEITEM hItemSelected)
{
	try
	{
		switch(m_dialogType)
		{
			case SHLTYPEDLGPROJECTANDFILE_PROJECT:
				ShowProjectTemplates(hItemSelected);
				break;

			case SHLTYPEDLGPROJECTANDFILE_ITEM:
				ShowItemTemplates(hItemSelected);
				break;

			case SHLTYPEDLGPROJECTANDFILE_DEPENDENCY:
				ShowDependencyTemplates(hItemSelected);
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

HTREEITEM CDlgProjectAndFile::GetItemSelected()
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

		m_ctrlGroupProjectItem.ScreenToClient(&cursorPosCliente);
		hItem = m_ctrlGroupProjectItem.HitTest(cursorPosCliente, &uFlags);
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

PROJECTITEMINFO* CDlgProjectAndFile::GetProjectItemInfo(HTREEITEM hItemSelected)
{
	PROJECTITEMINFO* projectitemInfo = NULL;
	try
	{
		for(UINT nIndex = 0; nIndex < m_elements->GetItemCount(); nIndex++)
		{
			projectitemInfo = m_elements->GetItemAt(nIndex);

			if(projectitemInfo->TreeNode == hItemSelected)
				break;

			projectitemInfo = NULL;
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

	return projectitemInfo;
}

void CDlgProjectAndFile::SetDialog()
{
	CString title;

	try
	{
		switch(m_dialogType)
		{
			case SHLTYPEDLGPROJECTANDFILE_PROJECT:
				title = _T("Add New Project");
				break;

			case SHLTYPEDLGPROJECTANDFILE_ITEM:
				title = _T("Add New Item");
				break;

			case SHLTYPEDLGPROJECTANDFILE_DEPENDENCY:
				title = _T("Add New Dependency");
				break;
		}

		if(m_image)
			m_ctrlProjectItem.SetImageList(m_image, 0);

		m_txtLocation.SetWindowText(m_targetPath);
		SetWindowText(title);
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

void CDlgProjectAndFile::SelectProjectItemTemplate()
{
	CProjectWrapper project;

	try
	{
		m_elements = project.PopulateTreeViewProjectFileTemplate(m_ctrlGroupProjectItem, m_projectType, m_dialogType);
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

void CDlgProjectAndFile::ShowProjectTemplates(HTREEITEM hItemSelected)
{
	PROJECTITEMINFO *projectitemInfo = NULL;

	CPath path;
	CString pathSource;
	CMarkup xml;
	CString fullfilename;
	CString categoryName;
	CString categoryDescription;

	CString strAux;
	CProjectEntity *project;
	CItemEntity *item;
		
	int nIndexImage;
	int nIndexItem;

	try
	{
		if(m_ProjectList)
		{
			delete m_ProjectList;
			m_ProjectList = NULL;
		}

		m_txtName.SetWindowText(_T(""));

		m_Project = NULL;

		m_ctrlProjectItem.DeleteAllItems();
		m_cmbCategory.ResetContent();

		projectitemInfo = GetProjectItemInfo(hItemSelected);

		if(!projectitemInfo)
			return;

		path.AddPath(2, projectitemInfo->Path, _T("Project.xml"));
		fullfilename = path.GetPath();

		if(!path.ExistFile())
			return;

		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		if(!xml.Load(fullfilename))
		{
			AfxMessageBox(xml.GetError());
			throw -1;
		}

		m_ProjectList = new CSHLTreeNode<CProjectEntity>();

		m_cmbCategory.AddString(_T("All Categories"));

		while(xml.FindChildElem(_T("Categories")))
		{
			xml.IntoElem();

			xml.FindChildElem(_T("Name"));
			categoryName = xml.GetChildData();

			xml.FindChildElem(_T("Description"));
			categoryDescription = xml.GetChildData();

			m_cmbCategory.AddString(categoryName);

			xml.OutOfElem();
		}

		m_cmbCategory.SetCurSel(0);

		while(xml.FindChildElem(_T("Project")))
		{
			project = new CProjectEntity();

			xml.IntoElem();

			xml.FindChildElem(_T("Name"));
			strAux = xml.GetChildData();
			project->Name = strAux;

			xml.FindChildElem(_T("ProjectName"));
			strAux = xml.GetChildData();
			project->Template = strAux;

			xml.FindChildElem(_T("Icon"));
			strAux = xml.GetChildData();
			project->Icon = strAux;

			xml.FindChildElem(_T("Category"));
			strAux = xml.GetChildData();
			project->Category = strAux;

			if(m_mapIcons)
				nIndexImage = (*m_mapIcons)[project->Icon];
			else
				nIndexImage = 0;

			nIndexItem = m_ctrlProjectItem.InsertItem(m_ctrlProjectItem.GetItemCount(), project->Name, nIndexImage);

			project->Numeric = nIndexItem;

			m_ProjectList->AddItem(project);

			while(xml.FindChildElem(_T("Items")))
			{
				xml.IntoElem();

				while(xml.FindChildElem(_T("File")))
				{
					item = new CItemEntity();

					strAux = xml.GetChildData();
					path.AddPath(2, projectitemInfo->Path, strAux);
					item->FileName = path.GetPath();

					project->Items->AddItem(item);
				}

				xml.OutOfElem();
			}

			xml.OutOfElem();
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

void CDlgProjectAndFile::ShowItemTemplates(HTREEITEM hItemSelected)
{
	PROJECTITEMINFO *projectitemInfo = NULL;

	CPath path;
	CString pathSource;
	CMarkup xml;
	CString fullfilename;
	CString categoryName;
	CString categoryDescription;

	CString strAux;
	CItemEntity *item;
	CItemEntity *dependency;
		
	int nIndexImage;
	int nIndexItem;

	try
	{
		if(m_ItemList)
		{
			delete m_ItemList;
			m_ItemList = NULL;
		}

		m_txtName.SetWindowText(_T(""));

		m_Item = NULL;

		m_ctrlProjectItem.DeleteAllItems();
		m_cmbCategory.ResetContent();

		projectitemInfo = GetProjectItemInfo(hItemSelected);

		if(!projectitemInfo)
			return;

		path.AddPath(2, projectitemInfo->Path, _T("Item.xml"));
		fullfilename = path.GetPath();

		if(!path.ExistFile())
			return;

		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		if(!xml.Load(fullfilename))
		{
			AfxMessageBox(xml.GetError());
			throw -1;
		}

		m_ItemList = new CSHLTreeNode<CItemEntity>();

		m_cmbCategory.AddString(_T("All Categories"));

		while(xml.FindChildElem(_T("Categories")))
		{
			xml.IntoElem();

			xml.FindChildElem(_T("Name"));
			categoryName = xml.GetChildData();

			xml.FindChildElem(_T("Description"));
			categoryDescription = xml.GetChildData();

			m_cmbCategory.AddString(categoryName);

			xml.OutOfElem();
		}

		m_cmbCategory.SetCurSel(0);

		while(xml.FindChildElem(_T("Item")))
		{
			item = new CItemEntity();

			xml.IntoElem();

			xml.FindChildElem(_T("Name"));
			strAux = xml.GetChildData();
			item->Name = strAux;

			xml.FindChildElem(_T("Icon"));
			strAux = xml.GetChildData();
			item->Icon = strAux;

			xml.FindChildElem(_T("Type"));
			strAux = xml.GetChildData();
			item->Type = strAux;

			xml.FindChildElem(_T("Category"));
			strAux = xml.GetChildData();
			item->Category = strAux;

			xml.FindChildElem(_T("TemplateFile"));
			strAux = xml.GetChildData();
			path.AddPath(2, projectitemInfo->Path, strAux);
			strAux = path.GetPath();
			item->TemplateFile = strAux;
			pathSource = GetPartOf(strAux, _A_DIR);

			xml.FindChildElem(_T("TemplatePropertyFile"));
			strAux = xml.GetChildData();
			path.AddPath(2, projectitemInfo->Path, strAux);
			strAux = path.GetPath();
			item->TemplateProperties = strAux;

			xml.FindChildElem(_T("Description"));
			strAux = xml.GetChildData();
			item->Description = strAux;

			if(m_mapIcons)
				nIndexImage = (*m_mapIcons)[item->Icon];
			else
				nIndexImage = 0;

			nIndexItem = m_ctrlProjectItem.InsertItem(m_ctrlProjectItem.GetItemCount() ,item->Name, nIndexImage);

			item->Numeric = nIndexItem;

			m_ItemList->AddItem(item);

			while(xml.FindChildElem(_T("Dependency")))
			{
				xml.IntoElem();

				while(xml.FindChildElem(_T("File")))
				{
					dependency = new CItemEntity();

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

					path.AddPath(2, pathSource, strAux);
					strAux = path.GetPath();
					dependency->TemplateFile = strAux;

					xml.FindChildElem(_T("ICON"));
					strAux = xml.GetChildData();
					dependency->Icon = strAux;

					item->Dependencies->AddItem(dependency);

					xml.OutOfElem();
				}

				xml.OutOfElem();
			}

			xml.OutOfElem();
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

void CDlgProjectAndFile::ShowDependencyTemplates(HTREEITEM hItemSelected)
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

void CDlgProjectAndFile::CategorySelChanged()
{
	try
	{
		switch(m_dialogType)
		{
			case SHLTYPEDLGPROJECTANDFILE_PROJECT:
				ProjectCategorySelChanged();
				break;

			case SHLTYPEDLGPROJECTANDFILE_ITEM:
				ItemCategorySelChanged();
				break;

			case SHLTYPEDLGPROJECTANDFILE_DEPENDENCY:
				DependencyCategorySelChanged();
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

void CDlgProjectAndFile::ProjectCategorySelChanged()
{
	CString categoryName;
	CProjectEntity* project = NULL;

	int nIndexItem;
	int nIndexImage;

	try
	{
		m_cmbCategory.GetWindowText(categoryName);

		m_ctrlProjectItem.DeleteAllItems();

		for(UINT nIndex = 0; nIndex < m_ProjectList->GetItemCount(); nIndex++)
		{
			project = m_ProjectList->GetItemAt(nIndex);

			project->Numeric = -1;

			if(project->Category == categoryName || categoryName == _T("All Categories"))
			{
				if(m_mapIcons)
					nIndexImage = (*m_mapIcons)[project->Icon];
				else
					nIndexImage = 0;

				nIndexItem = m_ctrlProjectItem.InsertItem(m_ctrlProjectItem.GetItemCount() ,project->Name, nIndexImage);
				project->Numeric = nIndexItem;

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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

void CDlgProjectAndFile::ItemCategorySelChanged()
{
	CString categoryName;
	CItemEntity* item = NULL;

	int nIndexItem;
	int nIndexImage;

	try
	{
		m_cmbCategory.GetWindowText(categoryName);

		m_ctrlProjectItem.DeleteAllItems();

		for(UINT nIndex = 0; nIndex < m_ItemList->GetItemCount(); nIndex++)
		{
			item = m_ItemList->GetItemAt(nIndex);

			item->Numeric = -1;

			if(item->Category == categoryName || categoryName == _T("All Categories"))
			{
				if(m_mapIcons)
					nIndexImage = (*m_mapIcons)[item->Icon];
				else
					nIndexImage = 0;

				nIndexItem = m_ctrlProjectItem.InsertItem(m_ctrlProjectItem.GetItemCount() ,item->Name, nIndexImage);
				item->Numeric = nIndexItem;
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

void CDlgProjectAndFile::DependencyCategorySelChanged()
{
	CString categoryName;

	try
	{
		m_cmbCategory.GetWindowText(categoryName);
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

void CDlgProjectAndFile::SelectedList()
{
	try
	{
		switch(m_dialogType)
		{
			case SHLTYPEDLGPROJECTANDFILE_PROJECT:
				ProjectSelectedList();
				break;

			case SHLTYPEDLGPROJECTANDFILE_ITEM:
				ItemSelectedList();
				break;

			case SHLTYPEDLGPROJECTANDFILE_DEPENDENCY:
				DependencySelectedList();
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

void CDlgProjectAndFile::ProjectSelectedList()
{
	POSITION pos;
	int nItem;

	try
	{
		pos = m_ctrlProjectItem.GetFirstSelectedItemPosition();

		if(pos == NULL)
			m_Item = NULL;

		nItem = m_ctrlProjectItem.GetNextSelectedItem(pos);

		m_Project = GetProject(nItem);

		m_txtName.SetFocus();
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

void CDlgProjectAndFile::ItemSelectedList()
{
	POSITION pos;
	int nItem;

	try
	{
		pos = m_ctrlProjectItem.GetFirstSelectedItemPosition();

		if(pos == NULL)
			m_Item = NULL;

		nItem = m_ctrlProjectItem.GetNextSelectedItem(pos);

		m_Item = GetItem(nItem);

		m_txtName.SetFocus();
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}
void CDlgProjectAndFile::DependencySelectedList()
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

CProjectEntity* CDlgProjectAndFile::GetProject(int nIndex)
{
	CProjectEntity* project = NULL;

	try
	{
		for(UINT nIndexItem = 0; nIndexItem < m_ProjectList->GetItemCount(); nIndexItem++)
		{
			project = m_ProjectList->GetItemAt(nIndexItem);

			if(project->Numeric == nIndex)
				break;

			project = NULL;
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}

	return project;
}

CItemEntity* CDlgProjectAndFile::GetItem(int nIndex)
{
	CItemEntity* item = NULL;

	try
	{
		for(UINT nIndexItem = 0; nIndexItem < m_ItemList->GetItemCount(); nIndexItem++)
		{
			item = m_ItemList->GetItemAt(nIndexItem);

			if(item->Numeric == nIndex)
				break;

			item = NULL;
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}

	return item;
}

BOOL CDlgProjectAndFile::AddNew()
{
	BOOL bRet = FALSE;

	try
	{
		switch(m_dialogType)
		{
			case SHLTYPEDLGPROJECTANDFILE_PROJECT:
				bRet = ProjectAddNew();
				break;

			case SHLTYPEDLGPROJECTANDFILE_ITEM:
				bRet = ItemAddNew();
				break;

			case SHLTYPEDLGPROJECTANDFILE_DEPENDENCY:
				bRet = DependencyAddNew();
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}

	return bRet;
}

BOOL CDlgProjectAndFile::ProjectAddNew()
{
	BOOL bRet = FALSE;

	CString name;
	CPath path;
	CString fileName;

	try
	{
		m_txtName.GetWindowText(name);
		m_txtLocation.GetWindowText(m_targetPath);

		if(name.IsEmpty())
		{
			AfxMessageBox(_T("Invalid Name"));
			return FALSE;
		}

		if(m_Project == NULL)
		{
			AfxMessageBox(_T("Selected a template Project in the list."));
			return FALSE;

		}

		m_Project->Name = name;
		m_Project->FileName = name + _T(".jpj");
		m_Project->PropertyFile = name + _T(".prt");
		m_Project->TemplateFile = m_Project->Template + _T(".jpj");
		m_Project->TemplateProperties = m_Project->Template + _T(".prt");
		m_Project->Path = m_targetPath;

		bRet = TRUE;
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}

	return bRet;
}

BOOL CDlgProjectAndFile::ItemAddNew()
{
	BOOL bRet = FALSE;

	CString name;
	CPath path;
	CString fileName;

	try
	{
		m_txtName.GetWindowText(name);
		m_txtLocation.GetWindowText(m_targetPath);

		if(name.IsEmpty())
		{
			AfxMessageBox(_T("Invalid Name"));
			return FALSE;
		}

		if(m_Item == NULL)
		{
			AfxMessageBox(_T("Selected a template Item in the list."));
			return FALSE;

		}

		path.SetPath(m_Item->TemplateFile);

		fileName = name + path.GetExtension();

		m_Item->Name = name;
		m_Item->FileName = fileName;
		m_Item->PropertyFile = fileName + _T(".prt");

		bRet = TRUE;
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}

	return bRet;
}

BOOL CDlgProjectAndFile::DependencyAddNew()
{
	BOOL bRet = FALSE;

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
		MessageBox(szMessage, _T("Critial Error!"));	
	}

	return bRet;
}

void CDlgProjectAndFile::BrowserLocation()
{
	CString sPath;
	UINT nFlags;

	TCHAR szDisplayName[_MAX_PATH];
	LPTSTR lpBuffer;


	LPITEMIDLIST lpItemIDList;
	LPMALLOC pMalloc;

	BROWSEINFO browseInfo;

	try
	{
		m_txtLocation.GetWindowText(sPath);

		memset(szDisplayName, NULL, sizeof(TCHAR) * _MAX_PATH);
		Copychar(sPath.GetBuffer(), szDisplayName, sPath.GetLength());

		nFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI  | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;

		if (!SUCCEEDED (SHGetMalloc (&pMalloc)))
		{
			MessageBox(_T("Unable to link to Shell IMalloc interface"), _T("Critical Error"));
			return;
		}

		lpBuffer = (LPTSTR) (pMalloc->Alloc (_MAX_PATH));

		if (lpBuffer == NULL)
			return;

		ZeroMemory(&browseInfo, sizeof(browseInfo));

		browseInfo.hwndOwner = GetSafeHwnd();
		browseInfo.pidlRoot = NULL; 
		browseInfo.pszDisplayName = szDisplayName;
		browseInfo.lpszTitle = _T("Select a path and click OK");
		browseInfo.ulFlags = nFlags; 
		browseInfo.lpfn = SetSelProcDlgProject; 
		browseInfo.lParam = (LPARAM)(sPath.GetBuffer(1));
		sPath.ReleaseBuffer();

		if ((lpItemIDList = ::SHBrowseForFolder(&browseInfo)) != NULL)
		{
			if (::SHGetPathFromIDList(lpItemIDList, lpBuffer))
			{
				if (lpBuffer != '\0')
				{
					sPath = lpBuffer;
					m_txtLocation.SetWindowText(sPath);
				}

				pMalloc->Free(lpItemIDList);
			}
		}

		pMalloc->Free(lpBuffer);
		// Free our task allocator
		pMalloc->Release();
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}

int CALLBACK SetSelProcDlgProject(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
   if (uMsg==BFFM_INITIALIZED)
   {
      ::SendMessage (hWnd, BFFM_SETSELECTION, TRUE, lpData);
   }
   return 0;
}

void CDlgProjectAndFile::Release()
{
	try
	{
		if(m_ProjectList)
			delete m_ProjectList;

		if(m_ItemList)
			delete m_ItemList;

		if(m_elements)
			delete m_elements;
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
		MessageBox(szMessage, _T("Critial Error!"));	
	}
}
#pragma endregion PRIVATE_METHODS
