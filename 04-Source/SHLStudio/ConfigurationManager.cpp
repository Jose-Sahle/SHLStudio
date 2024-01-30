/* ***************************************************************************
 * Arquivo: ConfigurationManager.h                                           *
 *                                                                           *
 * Configura os projetos que serão "construído" a partir do comando BUILD    *
 * da Solution                                                               *
 *                                                                           *
 * Data:18/08/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */

#include "stdafx.h"
#include "SHLStudio.h"
#include "ConfigurationManager.h"
#include "afxdialogex.h"
#include "ProjectWrapper.h"
#include "Library.h"
#include "Resource.h"

// CConfigurationManager dialog

IMPLEMENT_DYNAMIC(CConfigurationManager, CDialogEx)

CConfigurationManager::CConfigurationManager(CWnd* pParent /*=NULL*/) : CDialogEx(CConfigurationManager::IDD, pParent)
{

}

CConfigurationManager::~CConfigurationManager()
{
}

void CConfigurationManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfigurationManager, CDialogEx)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CConfigurationManager::OnBnClickedOk)
END_MESSAGE_MAP()


// CConfigurationManager message handlers

#pragma region EVENTS
BOOL CConfigurationManager::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

int CConfigurationManager::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CConfigurationManager::OnBnClickedOk()
{
	SaveSolution();

	CDialogEx::OnOK();
}
#pragma endregion EVENTS

#pragma region PRIVATE_METHODS
void CConfigurationManager::InitControls()
{
	SHLOleDBTable table;
	CUGCell *cell;

	try
	{
		m_grid.AttachGrid(this, IDC_GRIDPLACEHOLDER); 

		m_grid.ShowRowHeader(FALSE);

		m_grid.AddColumn(_T("Project"), 250, NULL, FALSE);

		cell = new CUGCell();
		m_grid.GetGridDefault(cell);
		cell->SetAlignment(UG_ALIGNVCENTER | UG_ALIGNCENTER);
		m_grid.AddColumn(_T("Type"), 120, cell, FALSE);

		m_grid.AddColumn(_T("Plugin"), 200, NULL, FALSE);

		cell = new CUGCell();
		m_grid.GetGridDefault(cell);
		cell->SetAlignment(UG_ALIGNVCENTER | UG_ALIGNCENTER);
		m_grid.AddColumn(_T("Version"), 100, cell, FALSE);

		cell = new CUGCell();
		m_grid.GetGridDefault(cell);
		cell->SetAlignment(UG_ALIGNVCENTER | UG_ALIGNCENTER);
		cell->SetCellType(UGCT_DROPLIST);
		cell->SetLabelText(_T("True\nFalse\n"));
		cell->SetReadOnly(FALSE);
		m_grid.AddColumn(_T("Build"), 80, cell, FALSE);

		m_grid.AddColumn(_T("TreeNode"), 0, NULL, FALSE);

		SetTable(table);

		m_grid.SetResultTable(table);

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

void CConfigurationManager::SetTable(SHLOleDBTable& table)
{
	SHLDBROW *row;
	SHLDBCOLUMN *column;
	CString strValue;

	CProjectEntity* project = NULL;

	try
	{
		column = new SHLDBCOLUMN();
		column->DBType = SHLDBType_String;
		memset(column->szColumName, NULL, sizeof(TCHAR)*40);
		Copychar(_T("Project"), column->szColumName, 7);
		column->nOrdinal = 1;
		table.Columns.Add(column);

		column = new SHLDBCOLUMN();
		column->DBType = SHLDBType_String;
		memset(column->szColumName, NULL, sizeof(TCHAR)*40);
		Copychar(_T("Type"), column->szColumName, 4);
		column->nOrdinal = 2;
		table.Columns.Add(column);

		column = new SHLDBCOLUMN();
		column->DBType = SHLDBType_String;
		memset(column->szColumName, NULL, sizeof(TCHAR)*40);
		Copychar(_T("Plugin"), column->szColumName, 6);
		column->nOrdinal = 3;
		table.Columns.Add(column);

		column = new SHLDBCOLUMN();
		column->DBType = SHLDBType_String;
		memset(column->szColumName, NULL, sizeof(TCHAR)*40);
		Copychar(_T("Version"), column->szColumName, 7);
		column->nOrdinal = 4;
		table.Columns.Add(column);

		column = new SHLDBCOLUMN();
		column->DBType = SHLDBType_Boolean;
		memset(column->szColumName, NULL, sizeof(TCHAR)*40);
		Copychar(_T("Build"), column->szColumName, 5);
		column->nOrdinal = 5;
		table.Columns.Add(column);

		column = new SHLDBCOLUMN();
		column->DBType = SHLDBType_Int32;
		memset(column->szColumName, NULL, sizeof(TCHAR)*40);
		Copychar(_T("TreeNode"), column->szColumName, 8);
		column->nOrdinal = 6;
		table.Columns.Add(column);

		for(INT nIndexSolution = 0; nIndexSolution < m_solution->Projects->GetItemCount(); nIndexSolution++)
		{
			project = m_solution->Projects->GetItemAt(nIndexSolution);

			row = new SHLDBROW;
			row->value = new SHLBINDVALUE[6];

			// Project - 0
			strValue = project->Name;
			memset(row->value[0].data.szArray, NULL, sizeof(TCHAR)*8000);
			Copychar(strValue.GetBuffer(), (TCHAR*)row->value[0].data.szArray, strValue.GetLength());

			// Type - 1
			strValue = project->Type;
			memset(row->value[1].data.szArray, NULL, sizeof(TCHAR)*8000);
			Copychar(strValue.GetBuffer(), (TCHAR*)row->value[1].data.szArray, strValue.GetLength());

			// Plugin - 2
			strValue = project->ClassDll;
			memset(row->value[2].data.szArray, NULL, sizeof(TCHAR)*8000);
			Copychar(strValue.GetBuffer(), (TCHAR*)row->value[2].data.szArray, strValue.GetLength());

			// Version- 3
			strValue = project->Version;
			memset(row->value[3].data.szArray, NULL, sizeof(TCHAR)*8000);
			Copychar(strValue.GetBuffer(), (TCHAR*)row->value[3].data.szArray, strValue.GetLength());

			// Build - 4
			row->value[4].data.bolVal = (BOOL)project->CanBuild;

			// TreeNode - 5
			row->value[5].data.intVal = (INT)project->TreeNode;

			table.Rows.Add(row);
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

void CConfigurationManager::SaveSolution()
{
	HTREEITEM hTreeItem;
	long lTreeItem;
	CString strhTreeItem;

	CString strValue;

	CProjectEntity* project = NULL;
	CProjectWrapper pw;

	try
	{
		for(INT nIndexRows = 0; nIndexRows < m_grid.GetNumberRows(); nIndexRows++)
		{
			strhTreeItem	= m_grid.QuickGetText(5, nIndexRows);
			strValue		= m_grid.QuickGetText(4, nIndexRows);

			Val(strhTreeItem, lTreeItem);

			hTreeItem = (HTREEITEM) lTreeItem;

			project = pw.GetProject(m_solution, hTreeItem);

			if(strValue == _T("True"))
				project->CanBuild = true;
			else
				project->CanBuild = false;
		}

		pw.SaveSolution(m_solution, FALSE);
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
