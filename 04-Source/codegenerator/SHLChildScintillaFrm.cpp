/* **********************************************************************************
 * Arquivo: SHLChildScintillaFrm 												    *
 *																					*
 * Classe de Frame do Document/View para hospedar a classe SHLQueryScnintillaView.  *
 *																					*
 * Data:18/06/2013																	*
 * Auto: José Sahle Netto															*
 ********************************************************************************** */
#include "stdafx.h"

#include "SHLChildScintillaFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSHLChildScintillaFrame

IMPLEMENT_DYNCREATE(CSHLChildScintillaFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CSHLChildScintillaFrame, CMDIChildWndEx)
	ON_COMMAND(ID_FILE_PRINT, &CSHLChildScintillaFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CSHLChildScintillaFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSHLChildScintillaFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CSHLChildScintillaFrame::OnUpdateFilePrintPreview)

	ON_MESSAGE(WM_SETFILTERS, OnSetFilters)
END_MESSAGE_MAP()

// CSHLChildScintillaFrame construction/destruction

CSHLChildScintillaFrame::CSHLChildScintillaFrame()
{
	m_hAccel = NULL;
}

CSHLChildScintillaFrame::~CSHLChildScintillaFrame()
{
	if(m_hAccel)
		DestroyAcceleratorTable(m_hAccel);
}

BOOL CSHLChildScintillaFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
	CRect rect;
	GetClientRect(&rect);
	CSize size = rect.Size();

	BOOL bRet = m_wndSplitter.Create(this,
		2, 2,			// TODO: adjust the number of rows, columns
		size,	// TODO: adjust the minimum pane size
		pContext);

	if(bRet)
		m_wndSplitter.SetScrollStyle(0);

	return bRet;
}

BOOL CSHLChildScintillaFrame::PreTranslateMessage(MSG* pMsg)
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

BOOL CSHLChildScintillaFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CSHLChildScintillaFrame diagnostics

#ifdef _DEBUG
void CSHLChildScintillaFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CSHLChildScintillaFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CSHLChildScintillaFrame message handlers
#pragma region EVENTS
void CSHLChildScintillaFrame::OnFilePrint()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CSHLChildScintillaFrame::OnFilePrintPreview()
{
	if (m_dockManager.IsPrintPreviewValid())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // force Print Preview mode closed
	}
}

void CSHLChildScintillaFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_dockManager.IsPrintPreviewValid());
}

LRESULT CSHLChildScintillaFrame::OnSetFilters(WPARAM wParam, LPARAM lParam)
{

	SetFilters(wParam, lParam);

	return 0;
}
#pragma endregion EVENTS

#pragma region PRIVATE_METHODS
void CSHLChildScintillaFrame::SetFilters(WPARAM wParam, LPARAM lParam)
{
	INT nParam   = (INT)wParam;
	INT nType    = (INT)lParam;

	try
	{	 
		switch(nType)
		{
			case SCLEX_MSSQL:
				SetEditorFiltersSQL(nParam);
				break;

			case SCLEX_CPP:
				SetEditorFiltersCPP();
				break;

			case SCLEX_XML:
				SetEditorFiltersXML();
				break;
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

void CSHLChildScintillaFrame::SetEditorFiltersCPP()
{
	CStringArray arWordList1;
	CStringArray arWordList2;
	CStringArray arWordList3;
	CStringArray arWordNull;

	CSHLQueryScintillaView* pView = NULL;

	try
	{	 
		pView = (CSHLQueryScintillaView*)GetActiveView();

		arWordList1.Add(_T("and and_eq asm auto bitand bitor bool break case catch char class "));
		arWordList1.Add(_T("compl const const_cast continue default delete do double "));
		arWordList1.Add(_T("dynamic_cast else enum explicit export extern false float "));
		arWordList1.Add(_T("for friend goto if inline int long mutable namespace new not "));
		arWordList1.Add(_T("not_eq operator or or_eq private protected public register "));
		arWordList1.Add(_T("reinterpret_cast return short signed sizeof static static_cast "));
		arWordList1.Add(_T("struct switch template this throw true try typedef typeid "));
		arWordList1.Add(_T("typename union unsigned using virtual void volatile wchar_t while "));
		arWordList1.Add(_T("xor xor_eq abstract get set finally sealed partial "));

		arWordList2.Add(_T("a addindex addtogroup anchor arg attention author b brief bug c "));
		arWordList2.Add(_T("code date def defgroup deprecated dontinclude e em endcode "));
		arWordList2.Add(_T("endhtmlonly endif endlatexonly endlink endverbatim enum example "));
		arWordList2.Add(_T("exception f$ f[ f] file fn hideinitializer htmlinclude htmlonly "));
		arWordList2.Add(_T("if image include ingroup internal invariant interface latexonly "));
		arWordList2.Add(_T("li line link mainpage name nosubgrouping note overload "));
		arWordList2.Add(_T("p page par param post pre ref relates remarks return retval sa "));
		arWordList2.Add(_T("section see showinitializer since skip skipline struct subsection "));
		arWordList2.Add(_T("test throw todo typedef union until var verbatim verbinclude "));
		arWordList2.Add(_T("version warning weakgroup System Linq Text Collections Generic Data Odbc Diagnostics Reflection Serializable "));

		arWordList2.Add(_T("#DATABASECATAGLOG# #DATABASECATAGLOGDEBUG# #DATABASEPWD# #DATABASEPWDDEBUG# #DATABASESERVER# "));
		arWordList2.Add(_T("#DATABASESERVERDEBUG# #DATABASEUSER# #DATABASEUSERDEBUG# #DATETIME# "));
		arWordList2.Add(_T("#NAMESPACEDAL# #NAMESPACEENTITY# #NAMESPACEBLL# #NAMESPACECONTROLLER# #PREFIXDAL# #PREFIXBLL# #PREFIXENTITY# #PREFIXCONTROLLER#"));
		arWordList2.Add(_T("#SUFFIXDAL# #SUFFIXBLL# #SUFFIXENTITY# #SUFFIXCONTROLLER# #GRANTUSER# #GRANTUSERDEBUG# #VERSION# "));
		arWordList2.Add(_T("#ANDAFTER# #ANDBEFORE# #COMMAAFTER# #COMMABEFORE# #FIELD# #PRIMARYKEY# #TAB# #TABLE# #TABLEFISTUPPER# #TABLEFISTLOWER# #TABLEWITHOUTPREFIXTABLE# #TABLEFOREIGN# "));
		arWordList2.Add(_T("#TABLEFOREIGNWITHOUTPREFIXTABLE# #TYPECS# #TYPECS_NULLABLE# #TYPEDBSQLSERVER# #TYPEDBORACLE# #TYPEDBPOSTGRESQL# "));
		arWordList2.Add(_T("#TYPEDBMYSQL# #TYPEPRIMARYKEYCS# #TYPEPRIMARYKEYCS_NULLABLE# #TYPEPRIMARYKEYSQLSERVER# #TYPEPRIMARYKEYORACLE# #DBSIZE# #DBSIZEPRIMARYKEY# "));
		arWordList2.Add(_T("#TYPEPRIMARYKEYPOSTGRESQL# #TYPEPRIMARYKEYMYSQL# allfieldsforeignkey allfieldslessprimarykey ifexistforeignkey #COUNT# "));

		arWordList3.Add(_T("file  $ @ \\ & < > # { }"));

		pView->SetStyleDocument(SCLEX_CPP, arWordList1, arWordList2, arWordList3, arWordNull, arWordNull, arWordNull);
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

void CSHLChildScintillaFrame::SetEditorFiltersXML()
{
	CStringArray arStyleCommands;
	CStringArray arStyleFunctions;
	CStringArray arStyleSpecialFunctions;
	CStringArray arStyleDataType;
	CStringArray arStyleDatabaseElements;
	CStringArray arStyleOperators;

	CSHLQueryScintillaView* pView = NULL;

	try
	{	 
		pView = (CSHLQueryScintillaView*)GetActiveView();

		pView->SetStyleDocument(SCLEX_XML, arStyleCommands, arStyleFunctions, arStyleSpecialFunctions, arStyleDataType, arStyleDatabaseElements, arStyleOperators);
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

void CSHLChildScintillaFrame::SetEditorFiltersSQL(INT IDBanco)
{
	CStringArray arStyleCommands;
	CStringArray arStyleFunctions;
	CStringArray arStyleSpecialFunctions;
	CStringArray arStyleDataType;
	CStringArray arStyleDatabaseElements;
	CStringArray arStyleOperators;

	CSHLQueryScintillaView* pView = NULL;

	try
	{	 
		pView = (CSHLQueryScintillaView*)GetActiveView();

		LoadStatements(arStyleCommands, SHLEDITORSTATEMENTTYPE_COMMANDS, IDBanco);

		arStyleCommands.Add(_T("#DATABASECATAGLOG# #DATABASECATAGLOGDEBUG# #DATABASEPWD# #DATABASEPWDDEBUG# #DATABASESERVER# "));
		arStyleCommands.Add(_T("#DATABASESERVERDEBUG# #DATABASEUSER# #DATABASEUSERDEBUG# #DATETIME# "));
		arStyleCommands.Add(_T("#NAMESPACEDAL# #NAMESPACEENTITY# #NAMESPACEBLL# #NAMESPACECONTROLLER# #PREFIXCONTROLLER# #PREFIXDAL# #PREFIXBLL# #PREFIXENTITY# "));
		arStyleCommands.Add(_T("#SUFFIXDAL# #SUFFIXCONTROLLER# #SUFFIXBLL# #SUFFIXENTITY# #GRANTUSER# #GRANTUSERDEBUG# #VERSION# "));
		arStyleCommands.Add(_T("#ANDAFTER# #ANDBEFORE# #COMMAAFTER# #COMMABEFORE# #FIELD# #PRIMARYKEY# #TAB# #TABLE# #TABLEFISTUPPER# #TABLEFISTLOWER# #TABLEWITHOUTPREFIXTABLE# #TABLEFOREIGN# "));
		arStyleCommands.Add(_T("#TABLEFOREIGNWITHOUTPREFIXTABLE# #TYPECS# #TYPECS_NULLABLE# #TYPEDBSQLSERVER# #TYPEDBORACLE# #TYPEDBPOSTGRESQL# "));
		arStyleCommands.Add(_T("#TYPEDBMYSQL# #TYPEPRIMARYKEYCS# #TYPEPRIMARYKEYCS_NULLABLE# #TYPEPRIMARYKEYSQLSERVER# #TYPEPRIMARYKEYORACLE# #DBSIZE# #DBSIZEPRIMARYKEY# "));
		arStyleCommands.Add(_T("#TYPEPRIMARYKEYPOSTGRESQL# #TYPEPRIMARYKEYMYSQL# allfieldsforeignkey allfieldslessprimarykey ifexistforeignkey #COUNT# "));

		LoadStatements(arStyleFunctions, SHLEDITORSTATEMENTTYPE_FUNCTIONS, IDBanco);
		LoadStatements(arStyleSpecialFunctions, SHLEDITORSTATEMENTTYPE_SPECIAL_FUNCTIONS, IDBanco);
		LoadStatements(arStyleDataType, SHLEDITORSTATEMENTTYPE_DATA_TYPE, IDBanco);
		LoadStatements(arStyleDatabaseElements, SHLEDITORSTATEMENTTYPE_DATABASE_ELEMENTS, IDBanco);
		LoadStatements(arStyleOperators, SHLEDITORSTATEMENTTYPE_OPERATORS, IDBanco);

		pView->SetStyleDocument(SCLEX_MSSQL, arStyleCommands, arStyleFunctions, arStyleSpecialFunctions, arStyleDataType, arStyleDatabaseElements, arStyleOperators);

		ShowScrollBar(SB_VERT);
		ShowScrollBar(SB_VERT, FALSE);
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

void CSHLChildScintillaFrame::LoadStatements(CStringArray& arStatments, SHLEDITORSTATEMENTTYPE statementType, INT IDBanco)
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

CString CSHLChildScintillaFrame::GetConnectionStringSHLStudio()
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
#pragma endregion PRIVATE_METHODS