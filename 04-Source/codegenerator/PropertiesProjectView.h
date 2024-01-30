/* **************************************************************************
* Arquivo: PropertiesProjectView.h                                          *
*                                                                           *
* Classe da estrutura Doc/View do MFC que trata as propriedades do projeto  *
* Gerador Classes C#.                                                       *
*                                                                           *
* Data:29/04/2013                                                           *
* Auto: José Sahle Netto                                                    *
*************************************************************************** */
#pragma once

// CPropertiesProjectView

class CPropertiesProjectView : public CPropertySheet
{
	DECLARE_DYNAMIC(CPropertiesProjectView)

public:
	CPropertiesProjectView(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPropertiesProjectView(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CPropertiesProjectView();

protected:
	DECLARE_MESSAGE_MAP()
};


