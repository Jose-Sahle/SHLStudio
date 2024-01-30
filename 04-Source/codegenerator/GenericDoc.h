/* ***************************************************************************
 * Arquivo: GenericDoc                                                       *
 *                                                                           *
 * Classe CDocument genérica para várias classes views                       *
 *                                                                           *
 * Data:21/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#pragma once

// CGenericDoc document
#include "Property.h"

class CGenericDoc : public CDocument
{
	DECLARE_DYNCREATE(CGenericDoc)

public:
	CGenericDoc();
	virtual ~CGenericDoc();
	virtual void AddToRecentFileList(LPCTSTR lpszPathName);

#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);

	DECLARE_MESSAGE_MAP()

private:
	void SetFrameAndView();

public:
	PROPERTY(CMDIChildWnd*, ChildFrame)
	GET(ChildFrame)
	{
		return m_pChild;
	}

	PROPERTY(CView*, View)
	GET(View)
	{
		return m_pView;
	}

protected:
	CMDIChildWnd* m_pChild;
	CView*		  m_pView;

};
