// PropertiesProjectView.cpp : implementation file
//

#include "stdafx.h"
#include "PropertiesProjectView.h"


// CPropertiesProjectView

IMPLEMENT_DYNAMIC(CPropertiesProjectView, CPropertySheet)

CPropertiesProjectView::CPropertiesProjectView(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CPropertiesProjectView::CPropertiesProjectView(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CPropertiesProjectView::~CPropertiesProjectView()
{
}


BEGIN_MESSAGE_MAP(CPropertiesProjectView, CPropertySheet)
END_MESSAGE_MAP()


// CPropertiesProjectView message handlers
