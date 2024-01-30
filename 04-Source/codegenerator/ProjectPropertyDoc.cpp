/* ***************************************************************************
 * Arquivo: ProjectPropertyDoc.cpp                                           *
 *                                                                           *
 * Classe da estrutura Doc/View do MFC que trata as propriedades do projeto  *
 * Gerador Classes C#.                                                       *
 *                                                                           *
 * Data:29/04/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#include "stdafx.h"
#include "ProjectPropertyDoc.h"
#include "Library.h"
#include "Markup.h"
#include "ProjectPropertyView.h"

// CProjectPropertyDoc

IMPLEMENT_DYNCREATE(CProjectPropertyDoc, CDocument)

CProjectPropertyDoc::CProjectPropertyDoc()
{
}

CProjectPropertyDoc::~CProjectPropertyDoc()
{
}


BEGIN_MESSAGE_MAP(CProjectPropertyDoc, CDocument)
END_MESSAGE_MAP()


// CProjectPropertyDoc diagnostics

#ifdef _DEBUG
void CProjectPropertyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CProjectPropertyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CProjectPropertyDoc serialization

void CProjectPropertyDoc::Serialize(CArchive& ar)
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


// CProjectPropertyDoc commands
BOOL CProjectPropertyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

void CProjectPropertyDoc::AddToRecentFileList(LPCTSTR lpszPathName)
{

}

BOOL CProjectPropertyDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	CString strFullNamePropertyFile;
	CPath path;

	path.AddPath(2, Project->Path, Project->PropertyFile);
	strFullNamePropertyFile = path.GetPath();
	SetPathName(strFullNamePropertyFile, false);
	
	if(!LoadPropertyDocument(strFullNamePropertyFile))
		return FALSE;

	if(!SetViewProperties())
		return FALSE;

	  return TRUE;
}

BOOL CProjectPropertyDoc::SetViewProperties()
{
	BOOL bRet = FALSE;
	CMDIChildWnd* pChild = NULL;
    CProjectPropertyView* pView = NULL;

	try
	{
		pChild = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();

		if ( pChild )
		{
			pView = (CProjectPropertyView *)pChild->GetActiveView();

			if ( pView )
			{
				if ( pView->IsKindOf( RUNTIME_CLASS(CProjectPropertyView) ) )
				{
					pView->FillProperties();
					bRet = TRUE;
				}
			}
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
	}

	return bRet;
}

BOOL CProjectPropertyDoc::OnSaveDocument(LPCTSTR lpszPathName)
{	
	return CDocument::OnSaveDocument(lpszPathName);
}


BOOL CProjectPropertyDoc::SaveModified()
{
	

	return CDocument::SaveModified();
}


void CProjectPropertyDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::OnCloseDocument();
}

BOOL CProjectPropertyDoc::LoadPropertyDocument(LPCTSTR lpszPathName)
{
	BOOL bRet = FALSE;
	CMarkup xml = NULL;
	CString strValue;
	CString strKey;

	try
	{
		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		if(!xml.Load(lpszPathName))
		{
			throw -1;
		}

		strKey = _T("VERSION");
		xml.FindChildElem(strKey);
		strValue = xml.GetChildData();
		Project->Properties[strKey] = strValue;

		strKey = _T("AUTHOR");
		xml.FindChildElem(strKey);
		strValue = xml.GetChildData();
		Project->Properties[strKey] = strValue;

		bRet = TRUE;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error.Format(_T("%s\n%s"), CString(szMessage), xml.GetError());
	}
	catch(...)
	{
		m_Error = xml.GetError();
	}

	return bRet;
}

BOOL CProjectPropertyDoc::SavePropertyDocument()
{
	BOOL bRet = FALSE;
	CMarkup xml = NULL;
	CString strValue;
	CString strKey;
	CString strAttribut;
	CString strFullPathFileName;
	CPath path;

	try
	{
		path.AddPath(2, Project->Path, Project->PropertyFile);
		strFullPathFileName = path.GetPath();

		xml.SetDocFlags( CMarkup::MDF_IGNORECASE  | CMarkup::MDF_UTF8PREAMBLE );

		if(!xml.Load(strFullPathFileName))
		{
			throw -1;
		}

		strKey = _T("VERSION");
		xml.FindChildElem(strKey);
		strValue = Project->Properties[strKey];
		xml.SetChildData(strValue);

		strKey = _T("AUTHOR");
		xml.FindChildElem(strKey);
		strValue = Project->Properties[strKey];
		xml.SetChildData(strValue);

		xml.Save(strFullPathFileName);

		bRet = TRUE;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_Error.Format(_T("%s\n%s"), CString(szMessage), xml.GetError());
	}
	catch(...)
	{
		m_Error = xml.GetError();
	}

	return bRet;
}
