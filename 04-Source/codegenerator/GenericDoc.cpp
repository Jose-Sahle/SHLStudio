/* ***************************************************************************
 * Arquivo: GenericDoc                                                       *
 *                                                                           *
 * Classe CDocument genérica para várias classes views                       *
 *                                                                           *
 * Data:21/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#include "stdafx.h"
#include "GenericDoc.h"
#include "Library.h"

// CGenericDoc

IMPLEMENT_DYNCREATE(CGenericDoc, CDocument)

CGenericDoc::CGenericDoc()
{
}

CGenericDoc::~CGenericDoc()
{
}


BEGIN_MESSAGE_MAP(CGenericDoc, CDocument)
END_MESSAGE_MAP()


// CGenericDoc diagnostics

#ifdef _DEBUG
void CGenericDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CGenericDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CGenericDoc serialization

void CGenericDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
#endif


// CGenericDoc commands
#pragma region EVENTS
BOOL CGenericDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

void CGenericDoc::AddToRecentFileList(LPCTSTR lpszPathName)
{
	
}

BOOL CGenericDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	SetFrameAndView();	
	return TRUE;
}
#pragma endregion EVENTS

#pragma region PRIVATE_METHODS
void CGenericDoc::SetFrameAndView()
{
	try
	{
		m_pChild = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();

		m_pView = (CView*)::SendMessage(m_pChild->GetSafeHwnd(), WM_GET_VIEW, 0, 0);
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
#pragma endregion PRIVATE_METHODS