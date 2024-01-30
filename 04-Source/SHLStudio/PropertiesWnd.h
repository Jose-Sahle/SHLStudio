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

#pragma once

#include "SolutionEntity.h"
#include "Property.h"
#include "MFCPropertyGridPropertyMask.h"
#include "ItemEntity.h"
#include "ISHLStudioProject.h"
#include "ISHLQuery.h"
#include "QueryDataConnectionEntity.h"

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// Construction
public:
	CPropertiesWnd();

	void AdjustLayout();

	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

	void ShowProperties(BOOL showPane = TRUE);
	void ShowSolutionProperties(BOOL showPane = TRUE);

	void ShowConnectionProperties(BOOL showPane = TRUE);

	void ClearAndHide();

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

	CSolutionEntity* m_solutionentity;
	CProjectEntity* m_projectentity;
	CItemEntity*	m_itementity;
	CQueryDataConnectionEntity* m_dataconnection;

	SHLQUERYHANDLE m_ptrSHLQuery;
	SHLSTUDIOPROJECTHANDLE	m_ptrSHLStudioProject;

	CString m_namesourceproperty;

// Implementation
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT OnPropertyChanged( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()

	void SetPropListFont();

	int m_nComboHeight;

	//Properties
public:
 	PROPERTY(CQueryDataConnectionEntity*, DataConnection)
  	GET(DataConnection) 
 	{ 		 
 		return m_dataconnection; 
	}
	SET(DataConnection)
	{
		m_dataconnection = value;
	}

 	PROPERTY(SHLQUERYHANDLE, SHLQuery)
  	GET(SHLQuery) 
 	{ 		 
 		return m_ptrSHLQuery; 
	}
	SET(SHLQuery)
	{
		m_ptrSHLQuery = value;
	}

 	PROPERTY(CSolutionEntity*, SolutionEntity)
  	GET(SolutionEntity) 
 	{ 		 
 		return m_solutionentity; 
	}
	SET(SolutionEntity)
	{
		m_solutionentity = value;
	}

 	PROPERTY(CProjectEntity*, ProjectEntity)
  	GET(ProjectEntity) 
 	{ 		 
 		return m_projectentity; 
	}
	SET(ProjectEntity)
	{
		m_projectentity = value;
	}

 	PROPERTY(CItemEntity*, ItemEntity)
  	GET(ItemEntity) 
 	{ 		 
 		return m_itementity; 
	}
	SET(ItemEntity)
	{
		m_itementity = value;
	}

 	PROPERTY(SHLSTUDIOPROJECTHANDLE, SHLStudioProject)
  	GET(SHLStudioProject) 
 	{ 		 
 		return m_ptrSHLStudioProject; 
	}
	SET(SHLStudioProject)
	{
		m_ptrSHLStudioProject = value;
	}

 	PROPERTY(CString, NameSourceProperty)
  	GET(NameSourceProperty) 
 	{ 		 
 		return m_namesourceproperty; 
	}
	SET(NameSourceProperty)
	{
		m_namesourceproperty = value;
	}
	
private:
	void PropertyChanged(CMFCPropertyGridPropertyMask* pProp);
	void SaveProperties();
	void ResetToNull();
};

