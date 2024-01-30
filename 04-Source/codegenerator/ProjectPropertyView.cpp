/* ***************************************************************************
 * Arquivo: ProjectPropertyView.h                                            *
 *                                                                           *
 * Classe da estrutura Doc/View do MFC que trata as propriedades do projeto  *
 * Gerador Classes C#.                                                       *
 *                                                                           *
 * Data:29/04/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#include "stdafx.h"
#include "resource.h"
#include "ProjectPropertyView.h"
#include "ProjectPropertyDoc.h"

// CProjectPropertyView
BEGIN_ANCHOR_MAP(CProjectPropertyView)
    ANCHOR_MAP_ENTRY(IDC_STATIC_VERSION,    ANF_TOP | ANF_LEFT)
    ANCHOR_MAP_ENTRY(IDC_EDIT_VERSION,    ANF_TOP | ANF_LEFT)
    ANCHOR_MAP_ENTRY(IDC_STATIC_AUTHOR,    ANF_TOP | ANF_LEFT)
    ANCHOR_MAP_ENTRY(IDC_EDIT_AUTHOR,    ANF_TOP | ANF_LEFT)

    ANCHOR_MAP_ENTRY(IDC_BUTTON_APPLY,		ANF_BOTTOM | ANF_RIGHT)
END_ANCHOR_MAP()


IMPLEMENT_DYNCREATE(CProjectPropertyView, CFormView)

CProjectPropertyView::CProjectPropertyView()
	: CFormView(CProjectPropertyView::IDD)
{
	m_bFirstAtivated = true;
}

CProjectPropertyView::~CProjectPropertyView()
{
}

void CProjectPropertyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VERSION, m_txtVersion);
	DDX_Control(pDX, IDC_EDIT_AUTHOR, m_txtAuthor);
}

BEGIN_MESSAGE_MAP(CProjectPropertyView, CFormView)
	ON_EN_CHANGE(IDC_EDIT_VERSION, &CProjectPropertyView::OnEnChangeProperties)
	ON_EN_CHANGE(IDC_EDIT_AUTHOR, &CProjectPropertyView::OnEnChangeProperties)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CProjectPropertyView::OnBnClickedButtonApply)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CProjectPropertyView diagnostics

#ifdef _DEBUG
void CProjectPropertyView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CProjectPropertyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CProjectPropertyView message handlers
//////////////////////////////////////////////////////////////////////////////////////////////
// 
//  E V E N T S 
//
//////////////////////////////////////////////////////////////////////////////////////////////
#pragma region Region_Events
void CProjectPropertyView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	InitAnchors(ANIF_CALCSIZE);

	// TODO: Add your specialized code here and/or call the base class
}

void CProjectPropertyView::OnEnChangeProperties()
{
	CProjectPropertyDoc* pDoc;

	try
	{
		pDoc = (CProjectPropertyDoc*)GetDocument();
		pDoc->SetModifiedFlag(TRUE);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
	}
}

BOOL CProjectPropertyView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CFormView::OnEraseBkgnd(pDC);
	return(m_bpfxAnchorMap.EraseBackground(pDC->m_hDC));
}

void CProjectPropertyView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	CRect rcWnd;
	GetWindowRect(&rcWnd);
  
	HandleAnchors(&rcWnd);     // you can alternatively pass NULL for &rcWnd
}

void CProjectPropertyView::OnBnClickedButtonApply()
{
	SaveProperties();
}
#pragma endregion Region_Events

//////////////////////////////////////////////////////////////////////////////////////////////
// 
//  P U B L I C   M E T H O D S 
//
//////////////////////////////////////////////////////////////////////////////////////////////
#pragma region REGION_PUBLIC_METHODS
void CProjectPropertyView::FillProperties()
{
	CProjectPropertyDoc* pDoc;
	CString strValue;
	CString strKey;
	try
	{
		pDoc = (CProjectPropertyDoc*)GetDocument();

		strKey = _T("VERSION");
		if(pDoc->Project->Properties.Lookup(strKey, strValue))
		{
			m_txtVersion.SetWindowText(strValue);
			pDoc->SetModifiedFlag(FALSE);

		}		

		strKey = _T("AUTHOR");
		if(pDoc->Project->Properties.Lookup(strKey, strValue))
		{
			m_txtAuthor.SetWindowText(strValue);
			pDoc->SetModifiedFlag(FALSE);

		}		
	}
	catch(...)
	{
	}
}


void CProjectPropertyView::SaveProperties()
{
	CProjectPropertyDoc* pDoc;
	CString strValue;
	CString strKey;
	try
	{
		pDoc = (CProjectPropertyDoc*)GetDocument();

		strKey = _T("VERSION");
		m_txtVersion.GetWindowText(strValue);
		pDoc->Project->Properties[strKey] = strValue;

		strKey = _T("AUTHOR");
		m_txtAuthor.GetWindowText(strValue);
		pDoc->Project->Properties[strKey] = strValue;

		pDoc->SavePropertyDocument();

		pDoc->SetModifiedFlag(FALSE);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		MessageBox(szMessage, _T("Critical Error!"));
	}
	catch(...)
	{
	}
}
#pragma endregion REGION_PUBLIC_METHODS
