/* ***************************************************************************
 * Arquivo: ConfigurationManager.h                                           *
 *                                                                           *
 * Configura os projetos que serão "construído" a partir do comando BUILD    *
 * da Solution                                                               *
 *                                                                           *
 * Data:18/08/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "bpctrlanchormap.h"
#include "Property.h"
#include "SHLTreeNode.h"
#include "SolutionEntity.h"
#include "ProjectEntity.h"
#include "ItemEntity.h"
#include "UGCtrlEx.h"

// CConfigurationManager dialog

class CConfigurationManager : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigurationManager)

public:
	CConfigurationManager(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigurationManager();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONFIGURATION_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

protected:
	CUGCtrlEx m_grid;

public:
 	PROPERTY(CSolutionEntity*, Solution)
  	GET(Solution) 
 	{ 
 		return m_solution;
	}
 	SET(Solution)
 	{
 		m_solution = value;
 	} 

private:
	CSolutionEntity*	m_solution;
	
private:
	void InitControls();
	void SetTable(SHLOleDBTable& table);
	void SaveSolution();
};
