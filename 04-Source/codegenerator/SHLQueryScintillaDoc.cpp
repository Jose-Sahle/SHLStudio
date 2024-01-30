/* ***************************************************************************
 * Arquivo: SHLQueryScintillaDoc                                             *
 *                                                                           *
 * Classe que gerencia os documentos do SHLQueryScintillaView.               *
 * Este arquivo foi alterado para meu projeto, porém pego na internet.       *
 *                                                                           *
 * Data:18/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#include "stdafx.h"
#include "SHLQueryScintillaDoc.h"
#include "Library.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef SCI_NAMESPACE
using namespace Scintilla;
#endif


IMPLEMENT_DYNCREATE(CSHLQueryScintillaDoc, CScintillaDoc)

BEGIN_MESSAGE_MAP(CSHLQueryScintillaDoc, CScintillaDoc)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
END_MESSAGE_MAP()

CSHLQueryScintillaDoc::CSHLQueryScintillaDoc()
{
	m_bAutoSave = true;
}

CSHLQueryScintillaDoc::~CSHLQueryScintillaDoc()
{
}

#ifdef _DEBUG
void CSHLQueryScintillaDoc::AssertValid() const
{
	CScintillaDoc::AssertValid();
}

void CSHLQueryScintillaDoc::Dump(CDumpContext& dc) const
{
	CScintillaDoc::Dump(dc);
}
#endif //_DEBUG

#pragma region PUBLIC_EVENTS
BOOL CSHLQueryScintillaDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	if(m_bAutoSave)
		return false;

	//Let the base class do its thing
	BOOL bSuccess = CDocument::OnSaveDocument(lpszPathName);
	if (bSuccess)
	{
		CScintillaView* pView = GetView();
		AFXASSUME(pView);
		
		CScintillaCtrl& rCtrl = pView->GetCtrl();

		//Tell the control that the document has now been saved
		rCtrl.SetSavePoint();
		rCtrl.SetReadOnly(FALSE);
	}

	return bSuccess;
} 

void CSHLQueryScintillaDoc::OnFileSave()
{
	m_bAutoSave = false;
	FileSave(false);
	m_bAutoSave = true;
}

void CSHLQueryScintillaDoc::AddToRecentFileList(LPCTSTR lpszPathName)
{

}

#pragma endregion PRIVATE_EVENTS

#pragma region VIRTUAL_PUBLIC_METHODS
void CSHLQueryScintillaDoc::SetModifiedFlag(BOOL bModified)
{
	CString strTitle;

	try
	{
		strTitle = GetTitle();

		if(/*!IsModified() && */ bModified)
		{
			if(strTitle.Find( _T("(*)") ) < 0)
				SetTitle(_T("(*)") + strTitle.Trim());
		}
		else
		if( /*IsModified() &&*/ !bModified )
		{
			strTitle.Replace(_T("(*)"), _T(""));
			SetTitle( strTitle.Trim() );
		}

		UpdateFrameCounts();
	}
	catch(...)
	{
		CString strMsg;
		DWORD err = GetLastError();

		strMsg.Format(_T("Erro: %i\r\n%s"), err, ErrorMessage(err));
		MessageBox(NULL, strMsg, _T("0x00054"), MB_OK);
	}

	CScintillaDoc::SetModifiedFlag( bModified );
	CDocument::SetModifiedFlag(bModified);
}

#pragma endregion VIRTUAL_PUBLIC_METHODS

#pragma region PUBLIC_METHODS
void CSHLQueryScintillaDoc::SetTitle(LPCTSTR lpszTitle)
{
	CString strTitle;

	strTitle = lpszTitle;
	
	if(strTitle.Find(_T("nameless")) > -1 )
	{
		strTitle.Replace(_T("<"), _T(""));
		strTitle.Replace(_T(">"), _T(""));

		strTitle = _T("<") + strTitle.Trim() + _T(">");
	}

	strTitle = _T(" ") + strTitle.Trim();

	CScintillaDoc::SetTitle(strTitle);
}

void CSHLQueryScintillaDoc::SetXMLScript()
{
	try
	{
		if(m_pChild)
			::SendMessage(m_pChild->GetSafeHwnd(), WM_SETFILTERS, 0, SCLEX_XML);
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

void CSHLQueryScintillaDoc::SetCPPScript()
{
	try
	{
		if(m_pChild)
			::SendMessage(m_pChild->GetSafeHwnd(), WM_SETFILTERS, 0, SCLEX_CPP);

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

void CSHLQueryScintillaDoc::SetAccessScript()
{
	try
	{
		if (m_pChild)
			::SendMessage(m_pChild->GetSafeHwnd(), WM_SETFILTERS, 3, SCLEX_MSSQL);

	}
	catch (CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch (...)
	{
		AfxMessageBox(ErrorMessage(::GetLastError()));
	}
}


void CSHLQueryScintillaDoc::SetSQLServerScript()
{
	try
	{
		if(m_pChild)
			::SendMessage(m_pChild->GetSafeHwnd(), WM_SETFILTERS, 3, SCLEX_MSSQL);

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

void CSHLQueryScintillaDoc::SetMySQLScript()
{
	try
	{
		if(m_pChild)
			::SendMessage(m_pChild->GetSafeHwnd(), WM_SETFILTERS, 7, SCLEX_MSSQL);

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

void CSHLQueryScintillaDoc::SetPostGresScript()
{
	try
	{
		if(m_pChild)
			::SendMessage(m_pChild->GetSafeHwnd(), WM_SETFILTERS, 8, SCLEX_MSSQL);

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

void CSHLQueryScintillaDoc::SetOracleScript()
{
	try
	{
		if(m_pChild)
			::SendMessage(m_pChild->GetSafeHwnd(), WM_SETFILTERS, 5, SCLEX_MSSQL);

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

void CSHLQueryScintillaDoc::SetChild()
{
	try
	{
		m_pChild = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
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

void CSHLQueryScintillaDoc::SetFocus()
{
	try
	{
		if(m_pChild)
		{
			m_pChild->SetFocus();
			m_pChild->BringWindowToTop();
			GetView()->BringWindowToTop();
			GetView()->SetFocus();
		}

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
#pragma endregion PUBLIC_METHODS

#pragma region PRIVATE_METHODS
bool CSHLQueryScintillaDoc::FileSave(bool bSaveAs)
{
	bool bRet = false;

	CDocTemplate* pTemplate = NULL;
	CString strPathName;
	bool bPrompt = false;
	bool bIsModified = false;

	try
	{
		bPrompt = bSaveAs;

		strPathName = GetPathName();

		bIsModified = IsModified();

		if(bIsModified)
			SetModifiedFlag(FALSE);

		if(strPathName.IsEmpty())
		{
			bPrompt = TRUE;
			strPathName = GetTitle();
			pTemplate = GetDocTemplate();

			int iBad = strPathName.FindOneOf(_T(":/\\"));
			if (iBad != -1)
				strPathName.ReleaseBuffer(iBad);

			iBad = strPathName.FindOneOf(_T("<>"));
			if (iBad != -1)
			{
				strPathName.Replace(_T("<"), _T(""));
				strPathName.Replace(_T(">"), _T(""));
			}

			strPathName.Trim();
			strPathName = strPathName + _T(".sql");
		}
	
		if (bPrompt)
		{
			if (!AfxGetApp()->DoPromptFileName(strPathName, bSaveAs? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, pTemplate))
			{
				if(bIsModified)
					SetModifiedFlag(TRUE);

				return false;
			}
		}

		CWaitCursor wait;

		if (!OnSaveDocument(strPathName))
		{
			// be sure to delete the file
			try
			{
				CFile::Remove(strPathName);
			}
			catch(...)
			{
				CString strMsg;
				DWORD err = GetLastError();

				strMsg.Format(_T("Error: %i\r\n%s"), err, ErrorMessage(err));
				MessageBox(NULL, strMsg, _T("0x00055"), MB_OK);
			}

			if(bIsModified)
				SetModifiedFlag(TRUE);

			bRet =  false;
		}
		else
			bRet = true;

		SetPathName(strPathName);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);
	}
	catch(...)
	{
	}

	return bRet;
}
#pragma endregion PRIVATE_METHODS
