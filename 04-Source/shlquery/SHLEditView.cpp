/* **********************************************************************************
 * Arquivo: SHLEditView.h												            *
 *																					*
 * Classe que receberá informações diversão (Texto).                                *
 *																					*
 * Data:08/06/2013																	*
 * Auto: José Sahle Netto															*
 ********************************************************************************** */
#include "stdafx.h"
#include "SHLEditView.h"
#include "Resource.h"
#include "Library.h"


// CSHLEditView

IMPLEMENT_DYNCREATE(CSHLEditView, CEditView)

CSHLEditView::CSHLEditView()
{

}

CSHLEditView::~CSHLEditView()
{
}

BEGIN_MESSAGE_MAP(CSHLEditView, CEditView)
	ON_COMMAND(ID_SHOW_HIDE_SPLITTER, OnShowHideSplitterCmd)
	ON_COMMAND(ID_EXECUTE_QUERY, OnExecuteQuery)
END_MESSAGE_MAP()


// CSHLEditView diagnostics

#ifdef _DEBUG
void CSHLEditView::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CSHLEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSHLEditView message handlers
#pragma region EVENTS
void CSHLEditView::OnShowHideSplitterCmd()
{
	::PostMessage(this->GetParentFrame()->GetSafeHwnd(), WM_SHOW_HIDE_SPLITTER, 0, 1);
}

void CSHLEditView::OnExecuteQuery()
{
	::PostMessage(this->GetParentFrame()->GetSafeHwnd(), WM_EXECUTE_QUERY, 0, 1);
}
#pragma endregion EVENTS