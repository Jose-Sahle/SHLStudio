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

#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "SHLStudio.h"
#include "MFCPropertyGridPropertyMask.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	ResetToNull();
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers
#pragma region Region_Events
int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create combo:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, ID_PROPERTY_COMBO))
	{
		TRACE0("Failed to create Properties Combo \n");
		return -1;      // fail to create
	}

	//m_wndObjectCombo.AddString(_T("Application"));
	//m_wndObjectCombo.AddString(_T("Properties Window"));
	//m_wndObjectCombo.SetCurSel(0);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, ID_PROPERTY_LIST))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	//InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	//m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* Is locked */);
	//m_wndToolBar.CleanUpLockedImages();
	//m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* Locked */);

	//m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	//m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	//m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	//m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();

	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

LRESULT CPropertiesWnd::OnPropertyChanged( WPARAM wParam, LPARAM lParam )
{
    CMFCPropertyGridPropertyMask* pProp = (CMFCPropertyGridPropertyMask*) lParam;

	PropertyChanged(pProp);	

    return 0;
}
#pragma endregion Region_Events

#pragma region Region_Private_Methods
void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}

void CPropertiesWnd::PropertyChanged(CMFCPropertyGridPropertyMask* pProp)
{
	CString strValue;
	CString strTag;

	try
	{
		strValue = pProp->GetValue();
		strTag   = pProp->Tag;

		m_itementity->Properties[strTag] = strValue;

		SaveProperties();
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

void CPropertiesWnd::SaveProperties()
{
	if(m_solutionentity == NULL)
	{
		SHLSTUDIOARGLIST Arguments;
		Arguments.AddItem(m_itementity);
		m_ptrSHLStudioProject->RunMethods(SHLSTUDIOMETHODS_SAVEPROPERTIESITEM, &Arguments);
		Arguments.RemoveAllItems(false);
	}
}

#pragma endregion Region_Private_Methods

#pragma region Region_Public_Methods
void CPropertiesWnd::ShowProperties(BOOL showPane)
{
	SHLSTUDIOARGLIST Arguments;

	try
	{
		m_solutionentity = NULL;
		m_wndPropList.ShowWindow(SW_SHOW);

		m_wndObjectCombo.ResetContent();
		m_wndObjectCombo.AddString(m_namesourceproperty);
		m_wndObjectCombo.SetCurSel(0);
		AdjustLayout();

		Arguments.AddItem(m_projectentity);
		Arguments.AddItem(m_itementity);
		Arguments.AddItem(&m_wndPropList);
		
		if(!m_ptrSHLStudioProject->RunMethods(SHLSTUDIOMETHODS_LOADPROPERTIESITEM, &Arguments))
		{
			MessageBox(m_ptrSHLStudioProject->GetLastError(), _T("Critical Error!"));
		}

		Arguments.RemoveAllItems(false);
		if(showPane)
			ShowPane(true, true, true);
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

void CPropertiesWnd::ShowSolutionProperties(BOOL showPane)
{
	CMFCPropertyGridProperty* pGroup;
	CMFCPropertyGridPropertyMask* pProp;

	CString strName;
	CString strVersion;
	CString strDescription;
	CString strFullFileName;
	CPath path;

	try
	{		
		m_wndPropList.ShowWindow(SW_SHOW);

		m_wndObjectCombo.ResetContent();
		m_wndObjectCombo.AddString(m_namesourceproperty);
		m_wndObjectCombo.SetCurSel(0);
		AdjustLayout();

		strName				= m_solutionentity->Name;
		strVersion			= m_solutionentity->Version;
		strDescription		= m_solutionentity->Description;

		path.AddPath(2, m_solutionentity->Path, m_solutionentity->FileName);
		strFullFileName		= path.GetPath();

		m_wndPropList.RemoveAll();

		m_wndPropList.EnableHeaderCtrl(FALSE);
		m_wndPropList.EnableDescriptionArea();
		m_wndPropList.SetVSDotNetLook();
		m_wndPropList.MarkModifiedProperties();

		pGroup = new CMFCPropertyGridProperty(_T("Misc"));
		pGroup->SetDescription(_T("Solution properties"));

		pProp = new CMFCPropertyGridPropertyMask(_T("Name"), strName, _T("Solution name"));
		pProp->Tag = _T("Name");
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		pProp = new CMFCPropertyGridPropertyMask(_T("Description"), strDescription, _T("Solution description"));
		pProp->Tag = _T("Description");
		pProp->AllowEdit(TRUE);
		pGroup->AddSubItem(pProp);

		pProp = new CMFCPropertyGridPropertyMask(_T("FullFileName"), strFullFileName, _T("Complete file name"));
		pProp->Tag = _T("FullFileName");
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		pProp = new CMFCPropertyGridPropertyMask(_T("Version"), strVersion, _T("Solution version"));
		pProp->Tag = _T("Version");
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		m_wndPropList.AddProperty(pGroup);

		if(showPane)
			ShowPane(true, true, true);
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

void CPropertiesWnd::ShowConnectionProperties(BOOL showPane)
{
	CMFCPropertyGridProperty* pGroup;
	CMFCPropertyGridPropertyMask* pProp;
	CString strCaption;
	CString strTagName;
	CString strValue;
	CString strDescription;

	try
	{
		m_wndPropList.ShowWindow(SW_SHOW);

		m_wndPropList.RemoveAll();

		m_wndObjectCombo.ResetContent();
		m_wndObjectCombo.AddString(m_namesourceproperty);
		m_wndObjectCombo.SetCurSel(0);
		AdjustLayout();

		pGroup = new CMFCPropertyGridProperty(_T("Connection"));
		pGroup->SetDescription(_T(""));

		strCaption			= _T("Connection Name");
		strTagName			= _T("ConnectionName");
		strValue			= m_dataconnection->ConnectionName;
		strDescription		= _T("");
		pProp = new CMFCPropertyGridPropertyMask(strCaption, strValue, strDescription);
		pProp->GroupParent = pGroup;
		pProp->Tag = strTagName;
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		strCaption			= _T("Connection String");
		strTagName			= _T("ConnectionString");
		strValue			= m_dataconnection->ConnectionString;
		strDescription		= _T("");
		pProp = new CMFCPropertyGridPropertyMask(strCaption, strValue, strDescription);
		pProp->GroupParent = pGroup;
		pProp->Tag = strTagName;
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		strCaption			= _T("DataSource");
		strTagName			= _T("DataSource");
		strValue			= m_dataconnection->DataSource;
		strDescription		= _T("");
		pProp = new CMFCPropertyGridPropertyMask(strCaption, strValue, strDescription);
		pProp->GroupParent = pGroup;
		pProp->Tag = strTagName;
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		strCaption			= _T("DBMS");
		strTagName			= _T("DBMSName");
		strValue			= m_dataconnection->DBMSName;
		strDescription		= _T("");
		pProp = new CMFCPropertyGridPropertyMask(strCaption, strValue, strDescription);
		pProp->GroupParent = pGroup;
		pProp->Tag = strTagName;
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		strCaption			= _T("Default Database");
		strTagName			= _T("DefaultDatabase");
		strValue			= m_dataconnection->DefaultDatabase;
		strDescription		= _T("");
		pProp = new CMFCPropertyGridPropertyMask(strCaption, strValue, strDescription);
		pProp->GroupParent = pGroup;
		pProp->Tag = strTagName;
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		strCaption			= _T("Driver");
		strTagName			= _T("DriveName");
		strValue			= m_dataconnection->DriveName;
		strDescription		= _T("");
		pProp = new CMFCPropertyGridPropertyMask(strCaption, strValue, strDescription);
		pProp->GroupParent = pGroup;
		pProp->Tag = strTagName;
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		strCaption			= _T("Provider");
		strTagName			= _T("ProviderName");
		strValue			= m_dataconnection->ProviderName;
		strDescription		= _T("");
		pProp = new CMFCPropertyGridPropertyMask(strCaption, strValue, strDescription);
		pProp->GroupParent = pGroup;
		pProp->Tag = strTagName;
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		strCaption			= _T("Server");
		strTagName			= _T("ServerName");
		strValue			= m_dataconnection->ServerName;
		strDescription		= _T("");
		pProp = new CMFCPropertyGridPropertyMask(strCaption, strValue, strDescription);
		pProp->GroupParent = pGroup;
		pProp->Tag = strTagName;
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		strCaption			= _T("User Name");
		strTagName			= _T("UserID");
		strValue			= m_dataconnection->UserID;
		strDescription		= _T("");
		pProp = new CMFCPropertyGridPropertyMask(strCaption, strValue, strDescription);
		pProp->GroupParent = pGroup;
		pProp->Tag = strTagName;
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		m_wndPropList.AddProperty(pGroup);

		if(showPane)
			ShowPane(true, true, true);
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

void CPropertiesWnd::ClearAndHide()
{
	try
	{
		m_solutionentity = NULL;
		m_itementity = NULL;
		m_ptrSHLStudioProject = NULL;
		m_projectentity = NULL;

		m_wndObjectCombo.ResetContent();
		m_wndPropList.RemoveAll();

		ResetToNull();
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

void CPropertiesWnd::ResetToNull()
{
	m_solutionentity = NULL;
	m_itementity = NULL;
	m_ptrSHLStudioProject = NULL;
	m_nComboHeight = 0;
	m_projectentity = NULL;
	m_dataconnection = NULL;
	m_ptrSHLQuery = NULL;
	m_namesourceproperty = _T("");
}
#pragma endregion Region_Public_Methods