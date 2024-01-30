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

// SHLStudioView.cpp : implementation of the CSHLStudioView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "SHLStudio.h"
#endif

#include "SHLStudioDoc.h"
#include "SHLStudioView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSHLStudioView

IMPLEMENT_DYNCREATE(CSHLStudioView, CView)

BEGIN_MESSAGE_MAP(CSHLStudioView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSHLStudioView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSHLStudioView construction/destruction

CSHLStudioView::CSHLStudioView()
{
	// TODO: add construction code here

}

CSHLStudioView::~CSHLStudioView()
{
}

BOOL CSHLStudioView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSHLStudioView drawing

void CSHLStudioView::OnDraw(CDC* /*pDC*/)
{
	CSHLStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CSHLStudioView printing


void CSHLStudioView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSHLStudioView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSHLStudioView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSHLStudioView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSHLStudioView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSHLStudioView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSHLStudioView diagnostics

#ifdef _DEBUG
void CSHLStudioView::AssertValid() const
{
	CView::AssertValid();
}

void CSHLStudioView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSHLStudioDoc* CSHLStudioView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSHLStudioDoc)));
	return (CSHLStudioDoc*)m_pDocument;
}
#endif //_DEBUG


// CSHLStudioView message handlers
