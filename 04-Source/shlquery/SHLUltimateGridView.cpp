/* ***************************************************************************
 * Arquivo: SHLUltimateGridView                                              *
 *                                                                           *
 * Encapsula o control Ultimate Grid Control                                 *
 *                                                                           *
 * Data:02/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */

#include "stdafx.h"
#include "SHLUltimateGridView.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE g_hDLLInstance;

IMPLEMENT_DYNCREATE(CSHLUltimateGridView, CView)

CSHLUltimateGridView::CSHLUltimateGridView() 
{
	m_hAccel = NULL;
}

CSHLUltimateGridView::~CSHLUltimateGridView()
{
	if(m_hAccel)
		DestroyAcceleratorTable(m_hAccel);

	m_grid.DestroyWindow();
}

BEGIN_MESSAGE_MAP(CSHLUltimateGridView, CView)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()

	ON_COMMAND(ID_EDIT_COPY, CopySelected)
	ON_COMMAND(ID_EDIT_SELECT_ALL, SelectAll)

	ON_COMMAND(ID_SHOW_HIDE_SPLITTER, OnShowHideSplitterCmd)
	ON_COMMAND(ID_EXECUTE_QUERY, OnExecuteQuery)
END_MESSAGE_MAP()

#pragma region EVENTS
void CSHLUltimateGridView::OnDraw(CDC* /*pDC*/)
{
}

int CSHLUltimateGridView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(!m_grid.CreateGrid (WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, ID_DATAGRIDVIEW))
	{
		AfxMessageBox(_T("Unsuccessfull!"));
		return -1;
	}

	ASSERT(m_hAccel == NULL);
	m_hAccel = ::LoadAccelerators(g_hDLLInstance, MAKEINTRESOURCE(IDR_ACCELERATOR_SHLQUERY));
	ASSERT(m_hAccel != NULL);

	return 0;
}

BOOL CSHLUltimateGridView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return FALSE;
}

void CSHLUltimateGridView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	AdjustLayout(cx, cy);
}

void CSHLUltimateGridView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	//m_grid.SetFocus();
}

void CSHLUltimateGridView::OnShowHideSplitterCmd()
{
	::PostMessage(this->GetParentFrame()->GetSafeHwnd(), WM_SHOW_HIDE_SPLITTER, 0, 1);
}

void CSHLUltimateGridView::OnExecuteQuery()
{
	::PostMessage(this->GetParentFrame()->GetSafeHwnd(), WM_EXECUTE_QUERY, 0, 1);
}

BOOL CSHLUltimateGridView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if (m_hAccel != NULL)
		{
			if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
				return TRUE;
		}
	}

	return CView::PreTranslateMessage(pMsg);
}
#pragma endregion EVENTS

#pragma region PUBLIC_METHODS
#pragma endregion PUBLIC_METHODS

#pragma region PRIVATE_METHODS
void CSHLUltimateGridView::AdjustLayout(int cx, int cy)
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	m_grid.MoveWindow(0, 0, cx, cy);
}

void CSHLUltimateGridView::SetTableResult(SHLOleDBTable* table, TCHAR* szQuery)
{	
	try
	{
		m_grid.SetResultTable(table, szQuery);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch(...)
	{
		AfxMessageBox(ErrorMessage(::GetLastError()));
	}
}

void CSHLUltimateGridView::CopySelected()
{
	m_grid.Copy();
}

void CSHLUltimateGridView::SelectAll()
{
	m_grid.SelectAll();
}
#pragma endregion PRIVATE_METHODS
