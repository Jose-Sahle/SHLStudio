/* ***************************************************************************
 * Arquivo: SHLQueryScintillaSqlDoc                                          *
 *                                                                           *
 * Classe que gerencia os documentos do SHLQueryScintillaView.               *
 * Este arquivo foi alterado para meu projeto, porém pego na internet.       *
 *                                                                           *
 * Data:01/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#include "stdafx.h"
#include "SHLQueryScintillaSqlDoc.h"
#include "Library.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef SCI_NAMESPACE
using namespace Scintilla;
#endif


IMPLEMENT_DYNCREATE(CSHLQueryScintillaSqlDoc, CScintillaDoc)

BEGIN_MESSAGE_MAP(CSHLQueryScintillaSqlDoc, CScintillaDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
END_MESSAGE_MAP()

CSHLQueryScintillaSqlDoc::CSHLQueryScintillaSqlDoc()
{
	m_bAutoSave = true;
}

CSHLQueryScintillaSqlDoc::~CSHLQueryScintillaSqlDoc()
{
}

#ifdef _DEBUG
void CSHLQueryScintillaSqlDoc::AssertValid() const
{
	CScintillaDoc::AssertValid();
}

void CSHLQueryScintillaSqlDoc::Dump(CDumpContext& dc) const
{
	CScintillaDoc::Dump(dc);
}
#endif //_DEBUG

#pragma region PUBLIC_EVENTS
BOOL CSHLQueryScintillaSqlDoc::OnSaveDocument(LPCTSTR lpszPathName)
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

void CSHLQueryScintillaSqlDoc::OnFileOpen()
{
	FileOpen();
}

void CSHLQueryScintillaSqlDoc::AddToRecentFileList(LPCTSTR lpszPathName)
{

}

void CSHLQueryScintillaSqlDoc::OnFileSave()
{
	m_bAutoSave = false;
	FileSave(false);
	m_bAutoSave = true;
}

void CSHLQueryScintillaSqlDoc::OnFileSaveAs()
{
	m_bAutoSave = false;
	FileSave(true);
	m_bAutoSave = true;
}
#pragma endregion PRIVATE_EVENTS

#pragma region VIRTUAL_PUBLIC_METHODS
void CSHLQueryScintillaSqlDoc::SetModifiedFlag(BOOL bModified)
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
bool CSHLQueryScintillaSqlDoc::FileOpen()
{
	bool bRet = false;

	CDocTemplate* pTemplate = NULL;

	CString strPathName;

	try
	{
		strPathName = GetPathName();

		if(strPathName.IsEmpty())
			strPathName = GetTitle();

		if(IsModified())
		{
			CString strCaption;

			strCaption.Format(_T("The file %s has been changed, want to save it?"), strPathName);

			int MB_Answer = MessageBox(NULL, strCaption, _T("Confirmation"), MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON3);

			if(MB_Answer == IDYES)
			{
				if(!FileSave(FALSE))
					return false;
			}
			else
			if(MB_Answer == IDCANCEL)
				return false;
		}

		strPathName = GetPathName();

		if (!AfxGetApp()->DoPromptFileName(strPathName,AFX_IDS_OPENFILE, OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, TRUE, pTemplate))
			return FALSE;
	
		CWaitCursor wait;

		if (!OnOpenDocument(strPathName))
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

				strMsg.Format(_T("Erro: %i\r\n%s"), err, ErrorMessage(err));
				MessageBox(NULL, strMsg, _T("0x00057"), MB_OK);
			}

			return false;
		}

		SetPathName(strPathName);

		bRet = true;
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

void CSHLQueryScintillaSqlDoc::SetTitle(LPCTSTR lpszTitle)
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

void CSHLQueryScintillaSqlDoc::SetStyleDocument(int lexer, CQueryDataConnectionEntity* dataconnection, CString database)
{
	CMDIChildWnd* pChild = NULL;

	try
	{
		SetDataConnection(dataconnection, database);

		Invalidate();

		pChild = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
		if(pChild)
			::SendMessage(pChild->GetSafeHwnd(), WM_SET_EDITOR_FOCUS, 0, 0);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);
	}
	catch(...)
	{
	}
}

#pragma endregion PUBLIC_METHODS

#pragma region PRIVATE_METHODS
bool CSHLQueryScintillaSqlDoc::FileSave(bool bSaveAs)
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

bool CSHLQueryScintillaSqlDoc::Invalidate()
{
	BOOL bRet = false;

	try
	{
		(AfxGetApp()->m_pMainWnd)->PostMessage(WM_INVALIDATE_VIEW);

		bRet = true;
	}
	catch(...)
	{
		CString strMsg;
		DWORD err = GetLastError();

		strMsg.Format(_T("Erro: %i\r\n%s"), err, ErrorMessage(err));
		MessageBox(NULL, strMsg, _T("0x00053"), MB_OK);
	}


	return bRet;
}

void CSHLQueryScintillaSqlDoc::SetDataConnection(CQueryDataConnectionEntity* dataconnection, CString database)
{
	CMDIChildWnd* pChild = NULL;

	try
	{
		pChild = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
		if(pChild)
			::SendMessage(pChild->GetSafeHwnd(), WM_SETDATACONNECTION, (WPARAM)database.GetBuffer(), (LPARAM)dataconnection);
	}
	catch(...)
	{
		CString strMsg;
		DWORD err = GetLastError();

		strMsg.Format(_T("Erro: %i\r\n%s"), err, ErrorMessage(err));
		MessageBox(NULL, strMsg, _T("0x00053"), MB_OK);
	}
}
#pragma endregion PRIVATE_METHODS
