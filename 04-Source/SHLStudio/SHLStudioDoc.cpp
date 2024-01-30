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

// SHLStudioDoc.cpp : implementation of the CSHLStudioDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SHLStudio.h"
#endif

#include "SHLStudioDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSHLStudioDoc

IMPLEMENT_DYNCREATE(CSHLStudioDoc, CDocument)

BEGIN_MESSAGE_MAP(CSHLStudioDoc, CDocument)
END_MESSAGE_MAP()


// CSHLStudioDoc construction/destruction

CSHLStudioDoc::CSHLStudioDoc()
{
	// TODO: add one-time construction code here

}

CSHLStudioDoc::~CSHLStudioDoc()
{
}

BOOL CSHLStudioDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

void CSHLStudioDoc::AddToRecentFileList(LPCTSTR lpszPathName)
{

}

BOOL CSHLStudioDoc::AtivarJanela(CRuntimeClass* pNewViewClass)
{

	CCreateContext context;
	CFormView* pNewView = NULL;
	CFrameWnd* pMainWnd = NULL;

	try
	{
		pMainWnd = (CFrameWnd*)AfxGetMainWnd();

		context.m_pNewViewClass = pNewViewClass;
		context.m_pCurrentDoc = this;

		pNewView = STATIC_DOWNCAST(CFormView, pMainWnd->CreateView(&context));

		if (pNewView != NULL)
		{
			// the new view is there, but invisible and not active...
			pNewView->ShowWindow(SW_SHOW);
			pNewView->OnInitialUpdate();
			pMainWnd->SetActiveView(pNewView);
			pMainWnd->RecalcLayout();

			// destroy the old view...
			return TRUE;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error = CString(szMessage);
	}
	catch(...)
	{
		CString szMessage;
		szMessage = ErrorMessage(GetLastError());
		m_Error = szMessage;
	}

	return FALSE;
}

// CSHLStudioDoc serialization
void CSHLStudioDoc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSHLStudioDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSHLStudioDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSHLStudioDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSHLStudioDoc diagnostics

#ifdef _DEBUG
void CSHLStudioDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSHLStudioDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSHLStudioDoc commands
