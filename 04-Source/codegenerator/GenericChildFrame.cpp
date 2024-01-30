/* ***************************************************************************
 * Arquivo: GenericChildFrame                                                *
 *                                                                           *
 * Classe ChildFrame genérica                                                *
 *                                                                           *
 * Data:21/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#include "stdafx.h"
#include "GenericChildFrame.h"
#include "Library.h"


// CGenericChildFrame

IMPLEMENT_DYNCREATE(CGenericChildFrame, CMDIChildWndEx)

CGenericChildFrame::CGenericChildFrame()
{

}

CGenericChildFrame::~CGenericChildFrame()
{
}

BOOL CGenericChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	CRect rect;
	GetClientRect(&rect);
	CSize size = rect.Size();

	BOOL bRet = m_wndSplitter.Create(this,
		2, 2,			// TODO: adjust the number of rows, columns
		size,	// TODO: adjust the minimum pane size
		pContext);

	return bRet;
}

BEGIN_MESSAGE_MAP(CGenericChildFrame, CMDIChildWndEx)
	ON_MESSAGE(WM_GET_VIEW, OnGetView)
END_MESSAGE_MAP()


// CGenericChildFrame message handlers

LRESULT CGenericChildFrame::OnGetView(WPARAM wParam, LPARAM lParam)
{
	CView* pView = NULL;
	try
	{
		pView = this->GetActiveView();
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

	return (LRESULT)pView;
}