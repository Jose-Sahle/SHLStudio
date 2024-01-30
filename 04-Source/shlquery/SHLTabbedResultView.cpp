/* ***************************************************************************
 * Arquivo: SHLTabbedResult                                                  *
 *                                                                           *
 * Classe para mostrar vários resultados em tab.                             *
 *                                                                           *
 * Data:02/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */

#include "stdafx.h"
#include "SHLTabbedResultView.h"
#include "Resource.h"
#include "Library.h"

// CSHLTabbedResultView

IMPLEMENT_DYNCREATE(CSHLTabbedResultView, CTabView)

CSHLTabbedResultView::CSHLTabbedResultView()
{
}

CSHLTabbedResultView::~CSHLTabbedResultView()
{
}

BEGIN_MESSAGE_MAP(CSHLTabbedResultView, CTabView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CSHLTabbedResultView diagnostics

#ifdef _DEBUG
void CSHLTabbedResultView::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CSHLTabbedResultView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSHLTabbedResultView message handlers
#pragma region EVENTS
int CSHLTabbedResultView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(!InitControls())
		return -1;

	return 0;
}

BOOL CSHLTabbedResultView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;// TODO: Add your message handler code here and/or call default

	//return CTabView::OnEraseBkgnd(pDC);
}

void CSHLTabbedResultView::OnSize(UINT nType, int cx, int cy)
{
	CTabView::OnSize(nType, cx, cy);

	::SendMessage(GetParentFrame()->GetSafeHwnd(), WM_SET_PERCENT_PANE, 0, 0);
}

#pragma endregion EVENTS

#pragma region PUBLIC_METHODS
void CSHLTabbedResultView::DeleteAllResults()
{
	for(UINT ntabindex = m_lastID-1; ntabindex >= 1; ntabindex--)
	{
		this->SetActiveView(ntabindex);
		m_wndGridView = (CSHLUltimateGridView*)this->GetActiveView();
		m_wndGridView->DestroyWindow();
		this->RemoveView(ntabindex);

	}

	m_lastID = 1;
}

void CSHLTabbedResultView::ResetContent()
{
	m_wndResultText->SetWindowText(_T(""));
}

void CSHLTabbedResultView::SetResultText(CString content)
{
	CString strText;
	m_wndResultText->GetWindowText(strText);
	strText += _T("\r\n\r\n");
	strText += content;
	m_wndResultText->SetWindowText(strText);
}

void CSHLTabbedResultView::SetCurrentTab(INT tab)
{
	SetActiveView(tab);
}

void CSHLTabbedResultView::SetNewDataGrid(SHLOleDBTable* table, TCHAR* szQuery)
{
	CString strCaption;
	UINT nRowAffected = -1;

	try
	{
		if(m_lastID > 256)
		{
			SetResultText(_T("Maximum size of result was reached."));
			return;
		}

		nRowAffected = table->RowsCount;

		strCaption.Format(_T("Record(s) (%i)"), nRowAffected); 

		AddView (RUNTIME_CLASS (CSHLUltimateGridView), strCaption, m_lastID);

		this->SetActiveView(m_lastID);

		m_wndGridView = (CSHLUltimateGridView*)this->GetActiveView();
		m_wndGridView->SetTableResult(table, szQuery);

		if(m_lastID == 1)
		{
			SetCurrentTab(1);
			::SendMessage(this->GetParentFrame()->GetSafeHwnd(), WM_SHOW_HIDE_SPLITTER, 0, 0);
			::SendMessage(this->GetParentFrame()->GetSafeHwnd(), WM_SET_EDITOR_FOCUS, 0, 0);
		}

		m_lastID++;

	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}
}
#pragma endregion PUBLIC_METHODS

#pragma region PRIVATE_METHODS
bool CSHLTabbedResultView::InitControls()
{
	bool bRet = false;

	try
	{
		AddView (RUNTIME_CLASS (CEditView), _T("Messages"), -1);
		this->SetActiveView(0);
		m_wndResultText = (CSHLEditView*)this->GetActiveView();
		CEdit& edit = m_wndResultText->GetEditCtrl();
		edit.SetReadOnly(TRUE);

		m_lastID = 1;

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}

	return bRet;
}
#pragma endregion PRIVATE_METHODS


