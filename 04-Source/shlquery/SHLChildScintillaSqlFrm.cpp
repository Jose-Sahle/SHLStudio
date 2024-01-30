/* **********************************************************************************
 * Arquivo: SHLChildScintillaSqlFrm.cpp												*
 *																					*
 * Classe de Frame do Document/View para hospedar a classe SHLQueryScnintillaView.  *
 *																					*
 * Data:01/06/2013																	*
 * Auto: José Sahle Netto															*
 ********************************************************************************** */

#include "stdafx.h"

#include "SHLChildScintillaSqlFrm.h"
#include "SHLOleDBTable.h"
#include "ShlDbColumn.h"
#include "ShlDbRow.h"
#include "ShlAcessorType.h"
#include "Library.h"

int CountSentenceSQL(int& nPosCommand, CSHLChildScintillaSqlFrame *queryFrame, CString separator, CString& sqlCommands);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define COOKIE_COMMENT			0x0001
#define COOKIE_COMMENT_LINE		0x0002
#define COOKIE_EXT_COMMENT		0x0004
#define COOKIE_STRING			0x0008
#define COOKIE_CHAR				0x0009
#define COOKIE_NORMALTEXT		0x000A
#define COOKIE_BEGINCOMMENT		0x000B
#define COOKIE_PREPROCESSOR		0x000C

extern HINSTANCE g_hDLLInstance;

// CSHLChildScintillaSqlFrame

IMPLEMENT_DYNCREATE(CSHLChildScintillaSqlFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CSHLChildScintillaSqlFrame, CMDIChildWndEx)
	ON_MESSAGE(WM_SHOW_HIDE_SPLITTER, OnShowHideSplitter)
	ON_MESSAGE(WM_EXECUTE_QUERY, OnExecuteQuery)
	ON_MESSAGE(WM_INVALIDATE_VIEW, OnInvalidateView)

	ON_MESSAGE(WM_SET_EDITOR_FOCUS, OnSetEditorFocus)
	ON_MESSAGE(WM_SET_PERCENT_PANE, OnSetPercentPane)

	ON_MESSAGE(WM_FILL_GRID, OnFillGrid)

	ON_MESSAGE(WM_SETDATACONNECTION, OnSetDataConnectoin)

	ON_MESSAGE(WM_NEW_QUERY, OnNewQuery)

	ON_COMMAND(ID_SHOW_HIDE_SPLITTER, OnShowHideSplitterCmd)
	ON_COMMAND(ID_EXECUTE_QUERY, OnExecuteQuery)

	ON_COMMAND(ID_BUTTON_DATABASE_CONNECT, OnDatabaseConnect)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DATABASE_CONNECT, OnUpdateDatabaseConnect)

	ON_COMMAND(ID_BUTTON_DATABASE_RECONNECT, OnDatabaseReconnect)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DATABASE_RECONNECT, OnUpdateDatabaseReconnect)
	
	ON_COMMAND(ID_BUTTON_DATABASE_DISCONNECT, OnDatabaseDisconnect)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DATABASE_DISCONNECT, OnUpdateDatabaseDisconnect)

	ON_COMMAND(ID_BUTTON_SQL_EXECUTE, OnExecuteQuery)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SQL_EXECUTE, OnUpdateExecuteQuery)

	ON_COMMAND(ID_BUTTON_SQL_STOP, OnStopExecutingQuery)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SQL_STOP, OnUpdateStopExecutingQuery)

	ON_COMMAND(ID_BUTTON_RESULT_GRID, OnTargetResultGrid)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_RESULT_GRID, OnUpdateTargetResultGrid)

	ON_COMMAND(ID_BUTTON_RESULT_TEXT, OnTargetResultText)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_RESULT_TEXT, OnUpdateTargetResultText)

	ON_COMMAND(ID_CHECK_KEEP_TAB_RESULT, OnKeepTabResult)
	ON_UPDATE_COMMAND_UI(ID_CHECK_KEEP_TAB_RESULT, OnUpdateKeepTabResult)

	ON_COMMAND(ID_CHECK_DDL_IN_TEXT_RESULT, OnInTextResult)
	ON_UPDATE_COMMAND_UI(ID_CHECK_DDL_IN_TEXT_RESULT, OnUpdateInTextResult)

	ON_COMMAND(ID_BUTTON_NEW_QUERY, OnNewQuery)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_NEW_QUERY, OnUpdateNewQuery)

	ON_COMMAND(ID_BUTTON_OPEN_SCRIPT_FILE, OnOpenQuery)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_OPEN_SCRIPT_FILE, OnUpdateOpenQuery)

	ON_UPDATE_COMMAND_UI(ID_COMBO_SQL_DATABASES, OnUpdateComboDatabase)
	ON_REGISTERED_MESSAGE(AFX_WM_ON_BEFORE_SHOW_RIBBON_ITEM_MENU, OnDropDownDatabase)

	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	ON_WM_CHILDACTIVATE()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

// CSHLChildScintillaSqlFrame construction/destruction

CSHLChildScintillaSqlFrame::CSHLChildScintillaSqlFrame()
{
	m_bHideSplitter = false;
	m_bFirstSplitter = true;
	m_ExecutingQuery = 0;
	m_hAccel = NULL;
	m_nTimerID = 0;
	m_bCanCancel = false;
	m_bStopQuery = false;
	m_offline = false;
	m_cy2 = 0.33;
	m_bresizesplitter = false;
	m_targetResult = SHLTARGETRESULT::SHLTARGETRESULT_GRID;
	m_keepingtabresults = false;
	m_intextresult = false;
	m_hThreadStarter = NULL;
	m_First = TRUE;
	m_DroppingList = FALSE;
}

CSHLChildScintillaSqlFrame::~CSHLChildScintillaSqlFrame()
{
	if(m_hAccel)
		DestroyAcceleratorTable(m_hAccel);

	if(m_hThreadStarter)
	{
		Sleep(1000);

		::TerminateThread(m_hThreadStarter, -1);
        CloseHandle(m_hThreadStarter);
	}
}

#pragma region EVENTS
BOOL CSHLChildScintillaSqlFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	BOOL bRet = FALSE;
	CRect rect;

	try
	{
		GetClientRect(&rect);
		CSize size = rect.Size();

		if(!m_wndSplitter.CreateStatic(this, 2, 1))
			return FALSE;	

		m_bresizesplitter = true;

		m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CSHLQueryScintillaSqlView), size, pContext);
		m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CSHLTabbedResultView), CSize(0, 0), pContext);

		m_lpQueryView  = (CSHLQueryScintillaSqlView*)m_wndSplitter.GetPane(0, 0);
		m_lpResultView = (CSHLTabbedResultView*)m_wndSplitter.GetPane(1, 0);

		SetActiveView(m_lpResultView);
		m_lpQueryView->SetFocus();

		ASSERT(m_hAccel == NULL);
		m_hAccel = ::LoadAccelerators(g_hDLLInstance, MAKEINTRESOURCE(IDR_ACCELERATOR_SHLQUERY));
		ASSERT(m_hAccel != NULL);

		bRet = TRUE;
		m_bFirstSplitter = false;
		m_bHideSplitter = true;
		m_bresizesplitter = false;

	}
	catch(...)
	{
		CString strMsg;
		DWORD err = GetLastError();

		strMsg.Format(_T("Erro: %i\r\n%s"), err, ErrorMessage(err));
		MessageBox(strMsg, _T("0x00064"));

		return FALSE;
	}

	return bRet;
}

BOOL CSHLChildScintillaSqlFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

#ifdef _DEBUG
void CSHLChildScintillaSqlFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CSHLChildScintillaSqlFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

void CSHLChildScintillaSqlFrame::OnFilePrint()
{
	try
	{
		if (m_dockManager.IsPrintPreviewValid())
		{
			PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
		}
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

void CSHLChildScintillaSqlFrame::OnFilePrintPreview()
{
	try
	{
		if (m_dockManager.IsPrintPreviewValid())
		{
			PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // force Print Preview mode closed
		}
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

void CSHLChildScintillaSqlFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}

LRESULT CSHLChildScintillaSqlFrame::OnShowHideSplitter(WPARAM wParam, LPARAM lParam)
{
	try
	{
		if ((long)lParam == 1)
			m_bHideSplitter = !m_bHideSplitter;
		else
			m_bHideSplitter = (bool)wParam;

		m_wndSplitter.SetActivePane(0, 0);

		ResizeSplitters();
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

	return 0;
}

LRESULT CSHLChildScintillaSqlFrame::OnSetPercentPane(WPARAM wParam, LPARAM lParam)
{
	try
	{
		HWND hWnd = m_wndSplitter.GetSafeHwnd();
		if (hWnd != NULL && ::IsWindow(hWnd) && !m_bFirstSplitter && !m_bHideSplitter && !m_bresizesplitter)
		{
			int cyCur1, cyMin1;
			int cyCur2, cyMin2;

			m_wndSplitter.GetRowInfo(0, cyCur1, cyMin1);
			m_wndSplitter.GetRowInfo(1, cyCur2, cyMin2);

			m_cy2 = (DOUBLE)cyCur2 / (DOUBLE)((DOUBLE)cyCur1 + (DOUBLE)cyCur2);
		}
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

	return 0;
}

LRESULT CSHLChildScintillaSqlFrame::OnSetEditorFocus(WPARAM wParam, LPARAM lParam)
{
	try
	{
		SetFocus();
		m_wndSplitter.SetActivePane(0, 0, m_lpQueryView);
		m_lpQueryView->SetFocus();
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

	return 0;
}

LRESULT CSHLChildScintillaSqlFrame::OnFillGrid(WPARAM wParam, LPARAM lParam)
{
	SHLOleDBReader*	reader = (SHLOleDBReader*)wParam; 
	TCHAR* szQuery = (TCHAR*)lParam;

	try
	{
		if (m_targetResult == SHLTARGETRESULT::SHLTARGETRESULT_GRID)
			FillGrid(reader, szQuery);
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

	return 0;
}

LRESULT CSHLChildScintillaSqlFrame::OnInvalidateView(WPARAM wParam, LPARAM lParam)
{
	try
	{
		m_lpQueryView->GetDocument()->SetTitle(m_lpQueryView->GetDocument()->GetTitle());
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

	return 0;
}

void CSHLChildScintillaSqlFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);

	try
	{
		ResizeSplitters();
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

LRESULT CSHLChildScintillaSqlFrame::OnNewQuery(WPARAM wParam, LPARAM lParam)
{
	try
	{
		NewQuery();
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

	return 0;
}

LRESULT CSHLChildScintillaSqlFrame::OnSetDataConnectoin(WPARAM wParam, LPARAM lParam)
{
	CQueryDataConnectionEntity*	dataconnection = (CQueryDataConnectionEntity*)lParam;
	TCHAR* szDatabase = (TCHAR*)(wParam);

	try
	{
		if (dataconnection != NULL)
		{
			m_dataconnection = *dataconnection;
			m_dataconnection.DefaultDatabase = CString(szDatabase);
			m_dataconnection.Connection->ChangeDatabase(CString(szDatabase));
			SetEditorFilters(m_dataconnection.IDBanco);
		}
		else
		{
			m_dataconnection.Connection = new COleDBGenericConnection();
			m_dataconnection.Connection->ConnectionString = _T("");
			m_dataconnection.Connection->Provider = SHLOLEDBPROVIDER::SHL_PROVIDER_GENERIC;

			SetEditorFilters(1);
		}
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

	return 0;
}

LRESULT CSHLChildScintillaSqlFrame::OnExecuteQuery(WPARAM wParam, LPARAM lParam)
{
	try
	{
		if(m_ExecutingQuery > 0 || m_dataconnection.Connection->ConnectionState != SHLCONNECTIONSTATE::Commandstate_Open)
			return 0;

		m_CancelQuery = false;

		m_lpQueryView->GetSqlSentence();

		ExecuteSQLQuery();
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

	return 0;
}

void CSHLChildScintillaSqlFrame::OnShowHideSplitterCmd()
{
	::PostMessage(GetSafeHwnd(), WM_SHOW_HIDE_SPLITTER, 0, 1);
}

void CSHLChildScintillaSqlFrame::OnExecuteQuery()
{
	::PostMessage(GetSafeHwnd(), WM_EXECUTE_QUERY, 0, 1);
}

void CSHLChildScintillaSqlFrame::OnUpdateExecuteQuery(CCmdUI* pCmdUI)
{
	if(m_dataconnection.Connection == NULL)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		if((m_ExecutingQuery > 0 || m_dataconnection.Connection->ConnectionState != SHLCONNECTIONSTATE::Commandstate_Open))
			pCmdUI->Enable(FALSE);
		else
			pCmdUI->Enable(TRUE);
	}
}

void CSHLChildScintillaSqlFrame::OnStopExecutingQuery()
{
	m_bStopQuery = true;
}

void CSHLChildScintillaSqlFrame::OnUpdateStopExecutingQuery(CCmdUI* pCmdUI)
{
	if(m_dataconnection.Connection == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		if(m_ExecutingQuery > 0 && m_dataconnection.Connection->ConnectionState != SHLCONNECTIONSTATE::Commandstate_Closed)
			pCmdUI->Enable(TRUE);
		else
			pCmdUI->Enable(FALSE);
	}
}

BOOL CSHLChildScintillaSqlFrame::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if (m_hAccel != NULL)
		{
			if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
				return TRUE;
		}
	}

	return CMDIChildWndEx::PreTranslateMessage(pMsg);
}

void CSHLChildScintillaSqlFrame::OnDatabaseConnect()
{
	DatabaseConnect();
}

void CSHLChildScintillaSqlFrame::OnUpdateDatabaseConnect(CCmdUI* pCmdUI)
{
	if(m_dataconnection.Connection != NULL && m_dataconnection.Connection->ConnectionState == SHLCONNECTIONSTATE::Commandstate_Closed)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CSHLChildScintillaSqlFrame::OnDatabaseReconnect()
{
	DatabaseReconnect();
}

void CSHLChildScintillaSqlFrame::OnUpdateDatabaseReconnect(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CSHLChildScintillaSqlFrame::OnDatabaseDisconnect()
{
	DatabaseDisconnect();
}

void CSHLChildScintillaSqlFrame::OnUpdateDatabaseDisconnect(CCmdUI* pCmdUI)
{
	if(m_dataconnection.Connection == NULL)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		if(m_dataconnection.Connection->ConnectionState == SHLCONNECTIONSTATE::Commandstate_Closed)
			pCmdUI->Enable(FALSE);
		else
			pCmdUI->Enable(TRUE);
	}
}

void CSHLChildScintillaSqlFrame::OnTargetResultGrid()
{
	if (m_targetResult == SHLTARGETRESULT::SHLTARGETRESULT_GRID)
	{
		m_targetResult = SHLTARGETRESULT::SHLTARGETRESULT_NONE;
	}
	else
	{
		m_targetResult = SHLTARGETRESULT::SHLTARGETRESULT_GRID;
	}

}

void CSHLChildScintillaSqlFrame::OnUpdateTargetResultGrid(CCmdUI* pCmdUI)
{
	if(m_targetResult == SHLTARGETRESULT::SHLTARGETRESULT_GRID)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	pCmdUI->Enable(TRUE);
}

void CSHLChildScintillaSqlFrame::OnTargetResultText()
{
	if (m_targetResult == SHLTARGETRESULT::SHLTARGETRESULT_TEXT)
	{
		m_targetResult = SHLTARGETRESULT::SHLTARGETRESULT_NONE;
	}
	else
	{
		m_targetResult = SHLTARGETRESULT::SHLTARGETRESULT_TEXT;
	}	
}

void CSHLChildScintillaSqlFrame::OnUpdateTargetResultText(CCmdUI* pCmdUI)
{
	if(m_targetResult == SHLTARGETRESULT::SHLTARGETRESULT_TEXT)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);

	pCmdUI->Enable(TRUE);
}

void CSHLChildScintillaSqlFrame::OnInTextResult()
{
	m_intextresult = !m_intextresult;
}

void CSHLChildScintillaSqlFrame::OnUpdateInTextResult(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_intextresult);
	pCmdUI->Enable(TRUE);
}

void CSHLChildScintillaSqlFrame::OnKeepTabResult()
{
	m_keepingtabresults = !m_keepingtabresults;
}

void CSHLChildScintillaSqlFrame::OnUpdateKeepTabResult(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_keepingtabresults);
	pCmdUI->Enable(TRUE);
}

void CSHLChildScintillaSqlFrame::OnNewQuery()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_NEW_QUERY, (WPARAM)&m_dataconnection, 0);
}

void CSHLChildScintillaSqlFrame::OnUpdateNewQuery(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CSHLChildScintillaSqlFrame::OnOpenQuery()
{
	OpenQuery();
}

void CSHLChildScintillaSqlFrame::OnUpdateOpenQuery(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

LRESULT CSHLChildScintillaSqlFrame::OnDropDownDatabase(WPARAM wParam, LPARAM lParam)
{
	CMFCRibbonBaseElement* pElem = (CMFCRibbonBaseElement*) lParam;
	ASSERT_VALID(pElem);

	switch (pElem->GetID())
	{
		case ID_COMBO_SQL_DATABASES:
			DropDownDatabase();
			break;
	}

	return 0;
}

void CSHLChildScintillaSqlFrame::OnUpdateComboDatabase(CCmdUI* pCmdUI)
{
	if(!m_DroppingList)
		pCmdUI->Enable(UpdateComboDatabase());
	else
	{
		ChangeDatabase();
	}
}
#pragma endregion EVENTS

#pragma region PUBLIC_METHODS
TCHAR CSHLChildScintillaSqlFrame::GetSQLQuery(int pos)
{
	return m_lpQueryView->GetSentenceAt(pos);
}
#pragma endregion PUBLIC_METHODS

#pragma region PRIVATE_METHODS
void CSHLChildScintillaSqlFrame::ResizeSplitters()
{
	HWND hWnd;
	CRect rect;
	CSize size1, size2;
	int cyCur1, cyMin1;
	int cyCur2, cyMin2;

	try
	{
		hWnd = m_wndSplitter.GetSafeHwnd();

		if(hWnd == NULL || !::IsWindow(hWnd) || m_bFirstSplitter)
			return;

		m_bresizesplitter = true;
		GetClientRect(&rect);
		size1 = size2 = rect.Size();

		m_wndSplitter.GetRowInfo(0, cyCur1, cyMin1);
		m_wndSplitter.GetRowInfo(1, cyCur2, cyMin2);

		if(m_bHideSplitter)
		{
			size2.cy = 0;
		}
		else
		{
			size2.cy *= m_cy2;
			size1.cy -= size2.cy;
		}

		m_wndSplitter.SetRowInfo(0, size1.cy, cyMin1);
		m_wndSplitter.SetRowInfo(1, size2.cy, cyMin2);

		m_wndSplitter.RecalcLayout();

		m_bresizesplitter = false;
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

void CSHLChildScintillaSqlFrame::FillGrid(SHLOleDBReader* reader, TCHAR* szQuery)
{
	SHLOleDBTable* table = NULL;

	try
	{
		if(reader->HasTables)
		{
			for(UINT nIndexTables = 0; nIndexTables < reader->TablesCount; nIndexTables++)
			{
				DoEvents();

				table = reader->Tables.GetAt(nIndexTables);
				
				m_lpResultView->SetNewDataGrid(table, szQuery);
			}
		}
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

	if(reader != NULL)
		delete reader;

	if(szQuery != NULL)
		delete szQuery;

	//m_ExecutingQuery--;
}

void CSHLChildScintillaSqlFrame::ExecuteSQLQuery()
{
	try
	{
		if(!m_keepingtabresults)
			m_lpResultView->DeleteAllResults();

		m_lpResultView->SetResultText(_T(""));
		m_lpResultView->SetCurrentTab(0);

		if(m_nTimerID != 0)
		{
			m_nTimerID = 0;
		}

		if(m_hThreadStarter)
		{
			CloseHandle(m_hThreadStarter);
			m_hThreadStarter = NULL;
		}

		m_hThreadStarter = CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)ExecuteSQLThread, (CSHLChildScintillaSqlFrame *)this, CREATE_SUSPENDED, &m_dwThreadStarter);
		ResumeThread(m_hThreadStarter);
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

void CSHLChildScintillaSqlFrame::SetEditorFilters(INT IDBanco)
{
	CStringArray arStyleCommands;
	CStringArray arStyleFunctions;
	CStringArray arStyleSpecialFunctions;
	CStringArray arStyleDataType;
	CStringArray arStyleDatabaseElements;
	CStringArray arStyleOperators;

	CSHLQueryScintillaSqlDoc* pDocument = NULL;

	try
	{	 
		LoadStatements(arStyleCommands, SHLEDITORSTATEMENTTYPE_COMMANDS, IDBanco);
		LoadStatements(arStyleFunctions, SHLEDITORSTATEMENTTYPE_FUNCTIONS, IDBanco);
		LoadStatements(arStyleSpecialFunctions, SHLEDITORSTATEMENTTYPE_SPECIAL_FUNCTIONS, IDBanco);
		LoadStatements(arStyleDataType, SHLEDITORSTATEMENTTYPE_DATA_TYPE, IDBanco);
		LoadStatements(arStyleDatabaseElements, SHLEDITORSTATEMENTTYPE_DATABASE_ELEMENTS, IDBanco);
		LoadStatements(arStyleOperators, SHLEDITORSTATEMENTTYPE_OPERATORS, IDBanco);

		m_lpQueryView->SetStyleDocument(SCLEX_MSSQL, arStyleCommands, arStyleFunctions, arStyleSpecialFunctions, arStyleDataType, arStyleDatabaseElements, arStyleOperators);
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

void CSHLChildScintillaSqlFrame::LoadStatements(CStringArray& arStatments, SHLEDITORSTATEMENTTYPE statementType, INT IDBanco)
{
	COleDBGenericCommand command;

	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table;
	CString errorMessage;

	COleDBGenericConnection		conn;
	CString commandText = _T("SELECT DISTINCT L.cPalavra FROM LISTA L INNER JOIN COMANDO C ON L.nIDComando = C.nIDComando WHERE C.nIDBanco = {1}   AND C.nIDTipoComando = {2} ORDER BY L.cPalavra");

	try
	{
		arStatments.RemoveAll();

		conn.ConnectionString  = GetConnectionStringSHLStudio();
		conn.Provider = SHLOLEDBPROVIDER::SHL_PROVIDER_CONNECTIONSTRING;

		if(!conn.Open())
		{
			errorMessage = conn.ErrorMessage;
			throw -1;
		}
		
		commandText.Replace(_T("{1}"), Str(IDBanco));
		commandText.Replace(_T("{2}"), Str(statementType));

		command.Connection = &conn;
		command.CommandText = commandText;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
		reader = command.ExecuteReader();

		if(command.HasErrors)
		{
			errorMessage = command.ErrorMessage;
			throw -1;
		}

		if(reader != NULL && reader->Tables.GetCount() > 0)
		{
			table = reader->Tables.GetAt(0);

			if(table->HasRows)
			{
				for(int nRowIndex = 0; nRowIndex < table->RowsCount; nRowIndex++)
				{
					CString strValue = table->GetValueToString(nRowIndex, 0, _T(""));

					if(!strValue.IsEmpty())
					{
						strValue += _T(" ");
						arStatments.Add(strValue);
					}
				}
			}
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		errorMessage +=  szMessage;

		AfxMessageBox(errorMessage);
	}
	catch(...)
	{
		errorMessage += ErrorMessage(::GetLastError());
		AfxMessageBox(errorMessage);
	}

	conn.Close();
}

void CSHLChildScintillaSqlFrame::NewQuery()
{
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_NEW_QUERY, (WPARAM)&m_dataconnection, 0);
}

void CSHLChildScintillaSqlFrame::OpenQuery()
{
	((CSHLQueryScintillaSqlDoc*)GetActiveDocument())->FileOpen();
}

void CSHLChildScintillaSqlFrame::DatabaseConnect()
{
	try
	{	
		if(m_dataconnection.Connection->ConnectionState == SHLCONNECTIONSTATE::Commandstate_Closed)
		{
			m_dataconnection.Connection->Provider = SHL_PROVIDER_GENERIC;
			m_dataconnection.Connection->Database = _T("");
			m_dataconnection.Connection->Open();

			m_dataconnection.DataSource = m_dataconnection.Connection->DataSource;
			m_dataconnection.DefaultDatabase = m_dataconnection.Connection->Database;
			m_dataconnection.DBMSName = m_dataconnection.Connection->DBMSName;
			m_dataconnection.DriveName = m_dataconnection.Connection->ProviderName;
			m_dataconnection.ProviderName = m_dataconnection.Connection->ProviderName;
			m_dataconnection.UserID = m_dataconnection.Connection->Username;
			m_dataconnection.ConnectionString = m_dataconnection.Connection->ConnectionString;
			m_dataconnection.IDBanco = GetIDBanco(m_dataconnection.Connection->DBMSName);

			SetDatabaseProperties(m_dataconnection.IDBanco);

			SetEditorFilters(m_dataconnection.IDBanco);
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

void CSHLChildScintillaSqlFrame::DatabaseReconnect()
{
	try
	{	
		m_dataconnection.Connection->Open();
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

void CSHLChildScintillaSqlFrame::ChangeDatabase()
{
	CString databaseName;
	CMFCRibbonBar*    wndRibbonBar;
	CMFCRibbonComboBox* combo = NULL;
	
	CString databaseInCombo; 

	try
	{
		if(m_dataconnection.Connection == NULL)
			return;

		databaseName = m_dataconnection.Connection->Database;
		
		wndRibbonBar = (CMFCRibbonBar*)::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_GET_RIBBONBAR, 0, 0);

		combo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, wndRibbonBar->FindByID(ID_COMBO_SQL_DATABASES));
		
		if(combo->IsDroppedDown())
			return;

		databaseInCombo = combo->GetItem(combo->GetCurSel()); 

		if(databaseInCombo != databaseName)
			m_dataconnection.Connection->ChangeDatabase(databaseInCombo);

		m_DroppingList = FALSE;
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

void CSHLChildScintillaSqlFrame::DropDownDatabase()
{
	CMFCRibbonBar*    wndRibbonBar;
	CMFCRibbonComboBox* combo = NULL;

	CString defaultDatabaseName;
	COleDBGenericCommand command;

	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table;

	CString commandText;

	try
	{
		wndRibbonBar = (CMFCRibbonBar*)::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_GET_RIBBONBAR, 0, 0);
		combo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, wndRibbonBar->FindByID(ID_COMBO_SQL_DATABASES));

		combo->RemoveAllItems();

		BeginWaitCursor();

		if(!m_dataconnection.SelectSysDatabases.IsEmpty())
		{
			command.Connection = m_dataconnection.Connection;
			command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
			command.CommandText = m_dataconnection.SelectSysDatabases;
			reader = command.ExecuteReader();

			if(reader != NULL && reader->HasTables && reader->Tables.GetAt(0)->HasRows)
			{
				table = reader->Tables.GetAt(0);
				for(INT nRow = 0; nRow < table->RowsCount; nRow++)
				{
					CString strDatabaseName = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("DATABASENAME")), _T("<null>"));
					combo->AddItem(strDatabaseName);
				}
			}

			if(reader)
			{
				delete reader;
				reader = NULL;
			}
		}

		if(!m_dataconnection.SelectUserDatabases.IsEmpty())
		{
			command.Connection = m_dataconnection.Connection;
			command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
			command.CommandText = m_dataconnection.SelectUserDatabases;
			reader = command.ExecuteReader();

			if(reader != NULL && reader->HasTables && reader->Tables.GetAt(0)->HasRows)
			{
				table = reader->Tables.GetAt(0);
				for(INT nRow = 0; nRow < table->RowsCount; nRow++)
				{
					CString strDatabaseName = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("DATABASENAME")), _T("<null>"));
					combo->AddItem(strDatabaseName);
				}
			}

			if(reader)
			{
				delete reader;
				reader = NULL;
			}
		}

		combo->SelectItem(m_dataconnection.Connection->Database);		
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

	if(reader)
	{
		delete reader;
		reader = NULL;
	}

	EndWaitCursor();
}

void CSHLChildScintillaSqlFrame::SetDatabaseProperties(ULONG IDBanco)
{
	COleDBGenericConnection conn;
	COleDBGenericCommand command;

	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* tableDatabase;

	CString commandText;

	try
	{	
		if(IDBanco == -1)
			return;

		conn.ConnectionString = GetConnectionStringSHLStudio();
		conn.Provider = SHLOLEDBPROVIDER::SHL_PROVIDER_CONNECTIONSTRING;
		conn.Open();

		if(conn.ConnectionState == SHLCONNECTIONSTATE::Commandstate_Open)
		{
			commandText = GetDatabaseSelectQueries(IDBanco);

			command.Connection = &conn;
			command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
			command.CommandText = commandText;
			reader = command.ExecuteReader();

			if(reader != NULL && reader->HasTables && reader->Tables.GetAt(0)->HasRows)
			{
				tableDatabase = reader->Tables.GetAt(0);

				m_dataconnection.SelectUserDatabases = tableDatabase->GetValueToString(0, 0, _T("") );
				m_dataconnection.SelectSysDatabases = tableDatabase->GetValueToString(0, 1, _T("") );
				m_dataconnection.SelectUserTables = tableDatabase->GetValueToString(0, 2, _T("") );
				m_dataconnection.SelectSysTables = tableDatabase->GetValueToString(0, 3, _T("") );
				m_dataconnection.SelectUserTableFields = tableDatabase->GetValueToString(0, 4, _T("") );
				m_dataconnection.SelectSysTablesFields = tableDatabase->GetValueToString(0, 5, _T("") );
				m_dataconnection.SelectUserViews = tableDatabase->GetValueToString(0, 6, _T("") );
				m_dataconnection.SelectSysViews = tableDatabase->GetValueToString(0, 7, _T("") );
				m_dataconnection.SelectViewCode = tableDatabase->GetValueToString(0, 8, _T("") );
				m_dataconnection.SelectUserProcedures = tableDatabase->GetValueToString(0, 9, _T("") );
				m_dataconnection.SelectSysProcedures = tableDatabase->GetValueToString(0, 10, _T("") );
				m_dataconnection.SelectUserProcedureFields = tableDatabase->GetValueToString(0, 11, _T("") );
				m_dataconnection.SelectSysProcedureFields = tableDatabase->GetValueToString(0, 12, _T("") );
				m_dataconnection.SelectProcedureCode = tableDatabase->GetValueToString(0, 13, _T("") );
				m_dataconnection.SelectUserFunctions = tableDatabase->GetValueToString(0, 14, _T("") );
				m_dataconnection.SelectSysFunctions = tableDatabase->GetValueToString(0, 15, _T("") );
				m_dataconnection.SelectUserFunctionFields = tableDatabase->GetValueToString(0, 16, _T("") );
				m_dataconnection.SelectSysFunctionFields = tableDatabase->GetValueToString(0, 17, _T("") );
				m_dataconnection.SelectFunctionCode = tableDatabase->GetValueToString(0, 18, _T("") );
				m_dataconnection.SelectPrimaryKeys = tableDatabase->GetValueToString(0, 19, _T("") );
				m_dataconnection.SelectPrimaryKeyFields = tableDatabase->GetValueToString(0, 20, _T("") );
				m_dataconnection.SelectSysConstraints = tableDatabase->GetValueToString(0, 21, _T("") );
				m_dataconnection.SelectSysConstraintFields = tableDatabase->GetValueToString(0, 22, _T("") );
				m_dataconnection.SelectUserConstraints = tableDatabase->GetValueToString(0, 23, _T("") );
				m_dataconnection.SelectUserConstraintFields = tableDatabase->GetValueToString(0, 24, _T("") );
				m_dataconnection.SelectUserSequences = tableDatabase->GetValueToString(0, 25, _T("") );
				m_dataconnection.SelectSysSequences = tableDatabase->GetValueToString(0, 26, _T("") );
				m_dataconnection.SelectUserSequenceFields = tableDatabase->GetValueToString(0, 27, _T("") );
				m_dataconnection.SelectSysSequenceFields = tableDatabase->GetValueToString(0, 28, _T("") );
				m_dataconnection.SelectUserIndexes = tableDatabase->GetValueToString(0, 29, _T("") );
				m_dataconnection.SelectSysIndexes = tableDatabase->GetValueToString(0, 30, _T("") );
				m_dataconnection.SelectUserIndexFields = tableDatabase->GetValueToString(0, 31, _T("") );
				m_dataconnection.SelectSysIndexFields = tableDatabase->GetValueToString(0, 32, _T("") );
				m_dataconnection.SelectUserTriggers = tableDatabase->GetValueToString(0, 33, _T("") );
				m_dataconnection.SelectSysTriggers = tableDatabase->GetValueToString(0, 34, _T("") );
			}
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

	if(reader != NULL)
		delete reader;
}

CString CSHLChildScintillaSqlFrame::GetDatabaseSelectQueries(ULONG IDBanco)
{
	CString commandSelectDatabaseQueries;

	commandSelectDatabaseQueries  = _T("SELECT\n ");
	commandSelectDatabaseQueries += _T(" A.cSelecionarUserBancos\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarSysBancos\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarUserTable\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarSysTable\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarSysField\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarUserField\n");
	commandSelectDatabaseQueries += _T(",A.cSelecionarSysView\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarUserView\n");
	commandSelectDatabaseQueries += _T(",A.cViewCodeView\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarUserProcedure\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarSysProcedure\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarFieldUserProcedure\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarFieldSysProcedure\n ");
	commandSelectDatabaseQueries += _T(",A.cViewCodeProcedure\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarUserFunction\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarSysFunction\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarFieldUserFunction\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarFieldSysFunction\n ");
	commandSelectDatabaseQueries += _T(",A.cViewCodeFunction\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarPrimaryKeys\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarFieldPrimaryKey\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarSysConstraints\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarSysFieldConstraint\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarUserConstraints\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarUserFieldConstraint\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarUserSequence\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarSysSequence\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarFieldUserSequence\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarFieldSysSequence\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarUserIndexes\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarSysIndexes\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarFieldUserIndexes\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarFieldSysIndexes\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarUserTriggers\n ");
	commandSelectDatabaseQueries += _T(",A.cSelecionarSysTriggers\n ");
	commandSelectDatabaseQueries += _T(",A.nIDBanco\n ");
	commandSelectDatabaseQueries += _T("FROM BANCO AS A\n ");
	commandSelectDatabaseQueries += _T("WHERE A.NIDBANCO = {NIDBANCO}\n ");

	commandSelectDatabaseQueries.Replace(_T("{NIDBANCO}"), Str(IDBanco));

	return commandSelectDatabaseQueries;
}

ULONG CSHLChildScintillaSqlFrame::GetIDBanco(CString dbmsname)
{
	CString commanText;
	CString error;
	ULONG idbanco = -1;
	COleDBGenericConnection conn;
	COleDBGenericCommand command;

	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table;

	try
	{
		commanText = _T("SELECT NIDBANCO FROM DBMS WHERE UCASE(cNome) = UCASE('{DBMSNAME}')");
		commanText.Replace(_T("{DBMSNAME}"), dbmsname);

		conn.ConnectionString = GetConnectionStringSHLStudio();
		conn.Provider = SHLOLEDBPROVIDER::SHL_PROVIDER_CONNECTIONSTRING;
		conn.Open();

		if(conn.ConnectionState == SHLCONNECTIONSTATE::Commandstate_Open)
		{
			command.Connection = &conn;
			command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
			command.CommandText = commanText;
			reader = command.ExecuteReader();
			if(reader != NULL && reader->HasTables && reader->Tables.GetAt(0)->HasRows)
			{
				table = reader->Tables.GetAt(0);
				idbanco = table->GetLong(0, 0);
			}
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		error +=  szMessage;
		AfxMessageBox(error);
	}
	catch(...)
	{
		error += ErrorMessage(::GetLastError());
		AfxMessageBox(error);
	}

	if(reader != NULL)
		delete reader;

	return idbanco;
}

void CSHLChildScintillaSqlFrame::DatabaseDisconnect()
{
	try
	{	 
		if(m_dataconnection.Connection->ConnectionState != SHLCONNECTIONSTATE::Commandstate_Closed)
			m_dataconnection.Connection->Close();
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

BOOL CSHLChildScintillaSqlFrame::UpdateComboDatabase()
{
	BOOL bRet = FALSE;

	CString databaseName;
	CMFCRibbonBar*    wndRibbonBar;
	CMFCRibbonComboBox* combo = NULL;
	
	CString databaseInCombo; 

	try
	{
		if(m_dataconnection.Connection == NULL)
			return FALSE;

		databaseName = m_dataconnection.Connection->Database;
		
		wndRibbonBar = (CMFCRibbonBar*)::SendMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_GET_RIBBONBAR, 0, 0);

		combo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, wndRibbonBar->FindByID(ID_COMBO_SQL_DATABASES));
		
		databaseInCombo = combo->GetItem(combo->GetCurSel()); 

		if(databaseInCombo != databaseName)
		{
			combo->RemoveAllItems();
			combo->AddItem(m_dataconnection.Connection->Database);
			combo->SelectItem(m_dataconnection.Connection->Database);
			combo->SetDropDownHeight(200);
			combo->EnableDropDownListResize(TRUE);
		}
		
		if(combo->IsDroppedDown())
		{			
			m_DroppingList = TRUE;
		}

		bRet = TRUE;
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

	return bRet;
}

CString CSHLChildScintillaSqlFrame::GetConnectionStringSHLStudio()
{
	CString ConnectionString;

	ConnectionString  = _T("Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=");
	ConnectionString += ::GetApplicationDirectory();
	ConnectionString += _T("SHLStudio.dat;Mode=Share Deny None;Extended Properties=\"\";");
	ConnectionString += _T("Jet OLEDB:System database=\"\";");
	ConnectionString += _T("Jet OLEDB:Registry Path=\"\";");
	ConnectionString += _T("Jet OLEDB:Database Password=\"shlstudio&@_1$\";");
	ConnectionString += _T("Jet OLEDB:Engine Type=5;");
	ConnectionString += _T("Jet OLEDB:Database Locking Mode=1;");
	ConnectionString += _T("Jet OLEDB:Global Partial Bulk Ops=2;");
	ConnectionString += _T("Jet OLEDB:Global Bulk Transactions=1;");
	ConnectionString += _T("Jet OLEDB:New Database Password=\"\";");
	ConnectionString += _T("Jet OLEDB:Create System Database=False;");
	ConnectionString += _T("Jet OLEDB:Encrypt Database=False;");
	ConnectionString += _T("Jet OLEDB:Don't Copy Locale on Compact=False;");
	ConnectionString += _T("Jet OLEDB:Compact Without Replica Repair=False;");
	ConnectionString += _T("Jet OLEDB:SFP=False");	

	return ConnectionString;
}

void CSHLChildScintillaSqlFrame::ClearQuery()
{
	m_strSQL = _T("");
}
#pragma endregion PRIVATE_METHODS

#pragma region EXTERN
HRESULT ExecuteSQLThread(CSHLChildScintillaSqlFrame *queryFrame)
{
	COleDBGenericCommand		command;
	SHLOleDBReader*				reader;

	CString strSQL, strSQLAux, strSQLQuery;
	CString strDatabase;
	CString sqCommands;

	int nPos = 0;

	CString strSeparator;

	BOOL bStopThread = FALSE;
	TCHAR* szQuery;
	UINT nSqlSize = 0;

	bool bHasDataResult = false;

	try
	{
		strSeparator = _T("GO");
		
		queryFrame->m_lpResultView->ResetContent();

		queryFrame->m_ExecutingQuery = 1;		

		queryFrame->m_bStopQuery = false;

		for (nPos = 0; CountSentenceSQL(nPos, queryFrame, strSeparator, sqCommands) != 0 && !queryFrame->m_bStopQuery; nPos++)
		{
			DoEvents();
			strSQL = sqCommands;
					
			strSQLAux = strSQL.Trim();

			if (!strSQLAux.Trim().IsEmpty())
			{
				queryFrame->m_bCanCancel = true;

				command.Connection = queryFrame->m_dataconnection.Connection;
				command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
				command.CommandText = strSQL;
				command.AccessorType = SHLACCESSORTYPE::SHLACCESSORTYPE_DIRECTTABLE;
				reader = command.ExecuteReader();

				if(command.HasErrors)
				{
					SHLOleDBTable* table;
					SHLDBCOLUMN* column;
					SHLDBROW* row;
					CString errorMessage;

					if(reader)
						delete reader;

					reader = new SHLOleDBReader();
					table = new SHLOleDBTable();

					column = new SHLDBCOLUMN();
					column->DBType = SHLDBType_String;
					memset(column->szColumName, NULL, sizeof(TCHAR)*40);
					Copychar(_T("Error"), column->szColumName, 5);
					column->nOrdinal = 1;
					column->nSize = command.ErrorMessage.GetLength();
					table->Columns.Add(column);

					row = new SHLDBROW;
					row->value = new SHLBINDVALUE[1];
					
					errorMessage.Format(_T("SHLStudio Error:%s"), command.ErrorMessage);
					memset(row->value[0].data.szArray, NULL, sizeof(TCHAR)*8000);
					Copychar(errorMessage.GetBuffer(), (TCHAR*)row->value[0].data.szArray, errorMessage.GetLength());
					table->Rows.Add(row);					

					reader->Tables.Add(table);
				}
				else
				if(reader == NULL || (reader != NULL && !reader->HasTables))
				{
					if(queryFrame->m_intextresult)
					{
						CString strTexto;

						strTexto.Format(_T("Affected Rows: %i"), command.AffectedRows);
						queryFrame->m_lpResultView->SetResultText(strTexto);
					}
					else
					{
						SHLOleDBTable* table;
						SHLDBCOLUMN* column;
						SHLDBROW* row;

						reader = new SHLOleDBReader();
						table = new SHLOleDBTable();

						column = new SHLDBCOLUMN();
						column->DBType = SHLDBType_Int32;
						memset(column->szColumName, NULL, sizeof(TCHAR)*40);
						Copychar(_T("Affected Rows"), column->szColumName, 13);
						column->nOrdinal = 1;
						column->nSize = command.ErrorMessage.GetLength();
						table->Columns.Add(column);

						row = new SHLDBROW;
						row->value = new SHLBINDVALUE[1];
						row->value[0].data.intVal = command.AffectedRows;

						table->Rows.Add(row);					

						reader->Tables.Add(table);
					}
				}

				if(reader != NULL && reader->HasTables)
				{
					nSqlSize = strSQL.GetLength()+1;
					szQuery = new TCHAR[nSqlSize];
					memset(szQuery, NULL, nSqlSize);
					Copychar(strSQL.GetBuffer(), szQuery, nSqlSize);

					PostMessage(queryFrame->GetSafeHwnd(), WM_FILL_GRID, (WPARAM)reader, (LPARAM)szQuery);
					::Sleep(150);
					bHasDataResult = true;
				}
			}
		}

		queryFrame->m_dataconnection.Connection->RetrieveConnectionInformation();
	}
	catch(CException* ex)
	{
		CString strTexto;
		TCHAR szMessage[4000];

		ex->GetErrorMessage(szMessage, 4000, NULL);

		strTexto = szMessage;

		queryFrame->m_lpResultView->SetResultText(strTexto);
		queryFrame->m_ExecutingQuery = 0;
	}
	catch(...)
	{
		DWORD nLastError = GetLastError();
		CString strMsg;

		strMsg = ErrorMessage(nLastError);

		queryFrame->m_lpResultView->SetResultText(strMsg);
		queryFrame->m_ExecutingQuery = 0;
	}

	queryFrame->m_ExecutingQuery = 0;
	CloseHandle(queryFrame->m_hThreadStarter);
	queryFrame->m_hThreadStarter = NULL;
	return 0;
}

int CountSentenceSQL(int& nPosCommand, CSHLChildScintillaSqlFrame *queryFrame, CString separator, CString& sqlCommands)
{
	int nCount = 0;
	int nSeparatorSize = 0;

	CString strNoComment;
	CString strCaracter;
	CString strCaracterCompare;
	CString strMultiCaracter;
	CString strCommentBegin;

	DWORD dwCookie;

	try
	{
		separator.MakeLower();
		
		nSeparatorSize = separator.GetLength();

		dwCookie = COOKIE_NORMALTEXT;

		while (queryFrame->GetSQLQuery(nPosCommand) != '\0')
		{
			DoEvents();

			strCaracterCompare = queryFrame->GetSQLQuery(nPosCommand);

			strMultiCaracter = _T("");
			for(int nCont = 0; nCont < nSeparatorSize; nCont++)						
				strMultiCaracter += queryFrame->GetSQLQuery(nPosCommand + nCont);

			strMultiCaracter.MakeLower();

			switch (dwCookie)
			{
				case COOKIE_NORMALTEXT:
					if ((strCaracterCompare == _T("\'") || strCaracterCompare == _T("\"")))
					{
						strCommentBegin = strCaracterCompare;
						strCaracterCompare = _T("");
						dwCookie = COOKIE_STRING;
						strCaracter += strNoComment + queryFrame->GetSQLQuery(nPosCommand);
						strNoComment = _T("");
					}
					else
					if (strCommentBegin == _T("/") && strCaracterCompare == _T("*"))
					{
						strCaracterCompare = _T("");
						strCommentBegin = _T("");
						dwCookie = COOKIE_COMMENT;
						strNoComment = _T("");
					}
					else
					if (strCommentBegin == _T("-") && strCaracterCompare == _T("-"))
					{
						strCommentBegin = strCaracterCompare;
						strCaracterCompare = _T("");
						dwCookie = COOKIE_COMMENT_LINE;
						strNoComment = _T("");
					}
					else
					if ((strCaracterCompare == _T("/") || strCaracterCompare == _T("-")))
					{
						strCommentBegin = strCaracterCompare;
						strCaracterCompare = _T("");
						dwCookie = COOKIE_NORMALTEXT;
						strNoComment = queryFrame->GetSQLQuery(nPosCommand);
					}
					else
					if (strMultiCaracter == separator && nPosCommand - 1 >= 1)
					{
						TCHAR beforeCaracter = queryFrame->GetSQLQuery(nPosCommand - 1);
						TCHAR afterCaracter = queryFrame->GetSQLQuery(nPosCommand + nSeparatorSize + 1);

						if ((beforeCaracter == _T(' ') || beforeCaracter == _T('\n') || beforeCaracter == _T('\t')) && (afterCaracter == _T(' ') || afterCaracter == _T('\n') || afterCaracter == _T('\r') || afterCaracter == _T('\t')))
						{
							nPosCommand += nSeparatorSize;
							nCount++;

							sqlCommands = strNoComment + strCaracter;
							strCaracter = _T("");

							return nCount;
						}
						else
						{
							strCaracter += strNoComment + queryFrame->GetSQLQuery(nPosCommand);
							strNoComment = _T("");
						}
					}
					else
					{
						strCaracter += strNoComment + queryFrame->GetSQLQuery(nPosCommand);
						strNoComment = _T("");
					}

					break;

				case COOKIE_COMMENT:
					if (strCommentBegin == _T("*") && strCaracterCompare == _T("/"))
					{
						strCaracterCompare = _T("");
						strCommentBegin = _T("");
						dwCookie = COOKIE_NORMALTEXT;
						strNoComment = _T("");
					}
					else
						strCommentBegin = strCaracterCompare;

					break;

				case COOKIE_COMMENT_LINE:
					if (strCaracterCompare == _T("\n"))
					{
						strCaracterCompare = _T("");
						strCommentBegin = _T("");
						dwCookie = COOKIE_NORMALTEXT;
						strNoComment = _T("");
					}
					else
						strCommentBegin = strCaracterCompare;

					break;

				case COOKIE_STRING:
					if (dwCookie == COOKIE_STRING && strCaracterCompare == strCommentBegin)
					{
						strCaracterCompare = _T("");
						strCommentBegin = _T("");
						dwCookie = COOKIE_NORMALTEXT;
						strCaracter += strNoComment + queryFrame->GetSQLQuery(nPosCommand);
						strNoComment = _T("");
					}
					else
					{
						strCaracter += strNoComment + queryFrame->GetSQLQuery(nPosCommand);
						strNoComment = _T("");
					}

					break;

			}
		
			nPosCommand++;
		}

		if (!strCaracter.IsEmpty())
		{
			nCount++;
			sqlCommands = strCaracter;
		}
	}
	catch(...)
	{
		CString strMsg;
		DWORD err = GetLastError();

		strMsg.Format(_T("Erro: %i\r\n%s"), err, ErrorMessage(err));
		MessageBox(queryFrame->GetSafeHwnd(), strMsg, _T("0x00074"), MB_OK);

		nCount = -1;
	}

	return nCount;
}
#pragma endregion EXTERN
