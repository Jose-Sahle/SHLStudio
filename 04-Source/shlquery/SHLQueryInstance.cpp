/* ***************************************************************************
 * Arquivo: SHLQueryInstance                                                 *
 *                                                                           *
 * Classe que implementa ISHLQuery.                                          *
 *																		     *
 * Data:28/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#include "stdafx.h"
#include "SHLQueryInstance.h"
#include "SHLQueryScintillaSqlView.h"
#include "SHLQueryScintillaSqlDoc.h"
#include "SHLChildScintillaSqlFrm.h"          
#include "SHLDataConnection.h"
#include "Library.h"

#pragma warning(disable:4800)

#if !defined(_WIN64)
// This pragma is required only for 32-bit builds. In a 64-bit environment,
// C functions are not decorated.
#pragma comment(linker, "/export:GetSHLQueryInstance=_GetSHLQueryInstance@0")
#endif  // _WIN64

CSHLQueryInstance::CSHLQueryInstance()
{
	CString dll;
	try
	{	
		dll = _T("SciLexer32u.dll");

		m_hSciDLL = ::LoadLibraryFromApplicationDirectory(dll, _T("Binaries"));

		if (m_hSciDLL == NULL)
			throw -1;

		m_conn.ConnectionString  = _T("Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=");
		m_conn.ConnectionString += ::GetApplicationDirectory();
		m_conn.ConnectionString += _T("SHLStudio.dat;Mode=Share Deny None;Extended Properties=\"\";");
		m_conn.ConnectionString += _T("Jet OLEDB:System database=\"\";");
		m_conn.ConnectionString += _T("Jet OLEDB:Registry Path=\"\";");
		m_conn.ConnectionString += _T("Jet OLEDB:Database Password=\"shlstudio&@_1$\";");
		m_conn.ConnectionString += _T("Jet OLEDB:Engine Type=5;");
		m_conn.ConnectionString += _T("Jet OLEDB:Database Locking Mode=1;");
		m_conn.ConnectionString += _T("Jet OLEDB:Global Partial Bulk Ops=2;");
		m_conn.ConnectionString += _T("Jet OLEDB:Global Bulk Transactions=1;");
		m_conn.ConnectionString += _T("Jet OLEDB:New Database Password=\"\";");
		m_conn.ConnectionString += _T("Jet OLEDB:Create System Database=False;");
		m_conn.ConnectionString += _T("Jet OLEDB:Encrypt Database=False;");
		m_conn.ConnectionString += _T("Jet OLEDB:Don't Copy Locale on Compact=False;");
		m_conn.ConnectionString += _T("Jet OLEDB:Compact Without Replica Repair=False;");
		m_conn.ConnectionString += _T("Jet OLEDB:SFP=False");	
		m_conn.Provider = SHLOLEDBPROVIDER::SHL_PROVIDER_CONNECTIONSTRING;
	}
	catch(...)
	{
		CString errorMessage;
		errorMessage.Format(_T("Scintilla DLL is not installed\n\n%s\\Binaries\\%s not be found!\n\nThe will be terminate!"), ::GetApplicationDirectory(), dll);
		::MessageBox(NULL, errorMessage, _T("Error: Load library"), MB_OK);
		exit(-10);
	}

}

CSHLQueryInstance::~CSHLQueryInstance()
{
  if (m_hSciDLL)
    FreeLibrary(m_hSciDLL);
}

#pragma region REGION_PUBLIC_METHODS
bool CSHLQueryInstance::LoadDocumentView(CRuntimeClass*& frame, CRuntimeClass*& view, CRuntimeClass*& docment)
{
	bool bRet = false;

	try
	{
		frame = RUNTIME_CLASS(CSHLChildScintillaSqlFrame);
		view = NULL; 
		docment = RUNTIME_CLASS(CSHLQueryScintillaSqlDoc);

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLQueryInstance::SetDocument(CString documentname, CRuntimeClass*& docment)
{
	bool bRet = false;

	try
	{
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLQueryInstance::FillTreeViewConnections(CViewTree& wndServerView, CSHLTreeNode<CQueryDataConnectionEntity>& dataconnection)
{
	bool bRet = false;

	CString commandText;
	CString commandTextDatabase;

	COleDBGenericCommand command;

	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table;

	HTREEITEM hItemDataRoot;
	HTREEITEM hItemDataConnection;

	CQueryDataConnectionEntity *queryData;

	try
	{
		wndServerView.SetRedraw(FALSE);

		BuildSelectCommands(commandText, commandTextDatabase);

		hItemDataRoot = wndServerView.GetRootItem();

		if(!hItemDataRoot)
		{
			m_error = _T("There´s no items in treeview control.");
			throw -1;
		}

		if(m_conn.ConnectionState == SHLCONNECTIONSTATE::Commandstate_Closed)
		{
			if(!m_conn.Open())
			{
				m_error = m_conn.ErrorMessage;
				throw -1;
			}
		}

		command.Connection = &m_conn;
		command.CommandText = commandText;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
		reader = command.ExecuteReader();

		if(reader != NULL && reader->HasTables && reader->Tables.GetAt(0)->HasRows)
		{
			table = reader->Tables.GetAt(0);
			for(UINT nRow = 0; nRow < table->Rows.GetCount(); nRow++)
			{
				queryData = new CQueryDataConnectionEntity();

				queryData->Connection = new COleDBGenericConnection();

				hItemDataConnection = wndServerView.InsertTreeItem(table->GetValueToString(nRow, 1, _T("")), IMAGE_DATA_CONNECTION, IMAGE_DATA_CONNECTION, hItemDataRoot);
				wndServerView.SetItemData(hItemDataConnection, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
				wndServerView.SetItemState(hItemDataConnection, 0, TVIS_EXPANDPARTIAL);

				queryData->TreeViewItem = hItemDataConnection;
				queryData->IDConnection = table->GetLong(nRow, table->GetColumnOrdinal(_T("nIDConexoes")) );
				queryData->ConnectionName = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("cConnectionName")), _T("") );
				queryData->ConnectionString = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("cConnectionString")), _T("") );
				queryData->DataSource = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("cDataSource")), _T("") );
				queryData->DefaultDatabase = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("cDefaultDataBase")), _T("") );
				queryData->DBMSName = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("cDBMSName")), _T("") );
				queryData->DriveName = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("cDriveName")), _T("") );
				queryData->ProviderName = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("cProviderName")), _T("") );
				queryData->UserID = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("cUserID")), _T("") );
				queryData->ServerName = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("cServerName")), _T("") );

				dataconnection.AddItem(queryData);
			}
		}

		wndServerView.Expand(hItemDataRoot, TVE_EXPAND);
		wndServerView.SetItemState(hItemDataRoot, 0, TVIS_EXPANDPARTIAL);

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}

	if(reader)
		delete reader;

	wndServerView.SetRedraw();

	m_conn.Close();

	return bRet;
}

void CSHLQueryInstance::LoadSelectQueries(CQueryDataConnectionEntity* queryData)
{
	CString commandText;
	CString commandTextDatabase;

	COleDBGenericCommand command;
	SHLOleDBReader* readerDatabase = NULL;
	SHLOleDBTable* tableDatabase;

	bool bDidConnect = false;

	try
	{
		if(m_conn.ConnectionState == SHLCONNECTIONSTATE::Commandstate_Closed)
		{
			if(!m_conn.Open())
			{
				m_error = m_conn.ErrorMessage;
				throw -1;
			}

			bDidConnect = true;
		}

		BuildSelectCommands(commandText, commandTextDatabase);
		commandTextDatabase.Replace(_T("{DBMS}"), queryData->DBMSName);

		command.Connection = &m_conn;
		command.CommandText = commandTextDatabase;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
		readerDatabase = command.ExecuteReader();

		if(readerDatabase != NULL)
		{
			if(readerDatabase->HasTables && readerDatabase->Tables.GetAt(0)->HasRows)
			{
				tableDatabase = readerDatabase->Tables.GetAt(0);
						
				queryData->SelectUserDatabases = tableDatabase->GetValueToString(0, 0, _T("") );
				queryData->SelectSysDatabases = tableDatabase->GetValueToString(0, 1, _T("") );
				queryData->SelectUserTables = tableDatabase->GetValueToString(0, 2, _T("") );
				queryData->SelectSysTables = tableDatabase->GetValueToString(0, 3, _T("") );
				queryData->SelectUserTableFields = tableDatabase->GetValueToString(0, 4, _T("") );
				queryData->SelectSysTablesFields = tableDatabase->GetValueToString(0, 5, _T("") );
				queryData->SelectUserViews = tableDatabase->GetValueToString(0, 6, _T("") );
				queryData->SelectSysViews = tableDatabase->GetValueToString(0, 7, _T("") );
				queryData->SelectViewCode = tableDatabase->GetValueToString(0, 8, _T("") );
				queryData->SelectUserProcedures = tableDatabase->GetValueToString(0, 9, _T("") );
				queryData->SelectSysProcedures = tableDatabase->GetValueToString(0, 10, _T("") );
				queryData->SelectUserProcedureFields = tableDatabase->GetValueToString(0, 11, _T("") );
				queryData->SelectSysProcedureFields = tableDatabase->GetValueToString(0, 12, _T("") );
				queryData->SelectProcedureCode = tableDatabase->GetValueToString(0, 13, _T("") );
				queryData->SelectUserFunctions = tableDatabase->GetValueToString(0, 14, _T("") );
				queryData->SelectSysFunctions = tableDatabase->GetValueToString(0, 15, _T("") );
				queryData->SelectUserFunctionFields = tableDatabase->GetValueToString(0, 16, _T("") );
				queryData->SelectSysFunctionFields = tableDatabase->GetValueToString(0, 17, _T("") );
				queryData->SelectFunctionCode = tableDatabase->GetValueToString(0, 18, _T("") );
				queryData->SelectPrimaryKeys = tableDatabase->GetValueToString(0, 19, _T("") );
				queryData->SelectPrimaryKeyFields = tableDatabase->GetValueToString(0, 20, _T("") );
				queryData->SelectSysConstraints = tableDatabase->GetValueToString(0, 21, _T("") );
				queryData->SelectSysConstraintFields = tableDatabase->GetValueToString(0, 22, _T("") );
				queryData->SelectUserConstraints = tableDatabase->GetValueToString(0, 23, _T("") );
				queryData->SelectUserConstraintFields = tableDatabase->GetValueToString(0, 24, _T("") );
				queryData->SelectUserSequences = tableDatabase->GetValueToString(0, 25, _T("") );
				queryData->SelectSysSequences = tableDatabase->GetValueToString(0, 26, _T("") );
				queryData->SelectUserSequenceFields = tableDatabase->GetValueToString(0, 27, _T("") );
				queryData->SelectSysSequenceFields = tableDatabase->GetValueToString(0, 28, _T("") );
				queryData->SelectUserIndexes = tableDatabase->GetValueToString(0, 29, _T("") );
				queryData->SelectSysIndexes = tableDatabase->GetValueToString(0, 30, _T("") );
				queryData->SelectUserIndexFields = tableDatabase->GetValueToString(0, 31, _T("") );
				queryData->SelectSysIndexFields = tableDatabase->GetValueToString(0, 32, _T("") );
				queryData->SelectUserTriggers = tableDatabase->GetValueToString(0, 33, _T("") );
				queryData->SelectSysTriggers = tableDatabase->GetValueToString(0, 34, _T("") );
				queryData->IDBanco = tableDatabase->GetLong(0, 35 );
			}
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}

	if(readerDatabase)
		delete readerDatabase;

	if(bDidConnect)
		m_conn.Close();
}

bool CSHLQueryInstance::ConnectionDatabaseServer(CViewTree& wndServerView, CQueryDataConnectionEntity* dataconnection)
{
	bool bRet = false;

	COleDBGenericCommand command;

	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table;

	CString commandText;

	HTREEITEM	hDatabases;
	HTREEITEM	hDatabase;

	bool bItemAdded = false;

	try
	{
		wndServerView.SetRedraw(FALSE);

		if(!dataconnection->SelectSysDatabases.IsEmpty())
		{
			command.Connection = dataconnection->Connection;
			command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
			command.CommandText = dataconnection->SelectSysDatabases;
			reader = command.ExecuteReader();

			if(reader != NULL && reader->HasTables && reader->Tables.GetAt(0)->HasRows)
			{
				bItemAdded = true;

				hDatabases = wndServerView.InsertTreeItem(_T("System databases"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, dataconnection->TreeViewItem);
				wndServerView.SetItemData(hDatabases, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASES);
				wndServerView.SetItemState(hDatabases, 0, TVIS_EXPANDPARTIAL);

				table = reader->Tables.GetAt(0);
				for(INT nRow = 0; nRow < table->RowsCount; nRow++)
				{
					CString strDatabaseName = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("DATABASENAME")), _T("<null>"));

					hDatabase = wndServerView.InsertTreeItem(strDatabaseName, IMAGE_DATA_BASE, IMAGE_DATA_BASE, hDatabases);	
					wndServerView.SetItemData(hDatabase, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_DATABASE_NAME);
					wndServerView.SetItemState(hDatabase, 0, TVIS_EXPANDEDONCE | TVIS_EXPANDPARTIAL);
				}
			}

			if(reader != NULL)
			{
				delete reader;
				reader = NULL;
			}
		}

		if(!dataconnection->SelectUserDatabases.IsEmpty())
		{
			command.Connection = dataconnection->Connection;
			command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
			command.CommandText = dataconnection->SelectUserDatabases;
			reader = command.ExecuteReader();

			if(reader != NULL && reader->HasTables && reader->Tables.GetAt(0)->HasRows)
			{
				bItemAdded = true;

				hDatabases = wndServerView.InsertItem(_T("Databases"), IMAGE_DATA_FOLDER, IMAGE_DATA_FOLDER, dataconnection->TreeViewItem);
				wndServerView.SetItemData(hDatabases, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASES);
				wndServerView.SetItemState(hDatabases, 0, TVIS_EXPANDPARTIAL);

				table = reader->Tables.GetAt(0);
				for(INT nRow = 0; nRow < table->RowsCount; nRow++)
				{
					CString strDatabaseName = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("DATABASENAME")), _T("<null>"));

					hDatabase = wndServerView.InsertTreeItem(strDatabaseName, IMAGE_DATA_BASE, IMAGE_DATA_BASE, hDatabases);	
					wndServerView.SetItemData(hDatabase, SHLDATACONNECTION_ID_TREE_DATA_USER_DATABASE_NAME);
					wndServerView.SetItemState(hDatabase, 0, TVIS_EXPANDPARTIAL);
				}
			}

			if(reader != NULL)
			{
				delete reader;
				reader = NULL;
			}
		}

		if(!bItemAdded)
		{
			hDatabases = wndServerView.InsertItem(_T("<no information details>"), -1, -1, dataconnection->TreeViewItem);
			wndServerView.SetItemData(hDatabases, SHLDATACONNECTION_ID_TREE_DATA_NO_INFORMATION);
			wndServerView.SetItemState(hDatabases, 0, TVIS_EXPANDPARTIAL);
		}

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}

	if(reader)
		delete reader;

	wndServerView.SetRedraw();

	return bRet;
}

bool CSHLQueryInstance::ShowElements(CString SelectElement, CString databasename, CString tablename, CString columnName, CString columnNameFind, SHLDATACONNECTION nodeValue, INT imageIndex, CViewTree& wndServerView, HTREEITEM phItem, CQueryDataConnectionEntity* pDataConnection, bool bIfNotAdded)
{
	bool bRet = false;

	COleDBGenericCommand command;

	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table;

	CString commandText;

	bool bItemAdded = false;

	HTREEITEM hItem;
	
	try
	{
		if(!SelectElement.IsEmpty())
		{
			commandText = SelectElement;
			commandText.Replace(_T("{DATABASENAME}"), databasename);
			commandText.Replace(_T("{TABLENAME}"), tablename);
			commandText.Replace(_T("{COLUMNNAME}"), columnName);

			command.Connection = pDataConnection->Connection;
			command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
			command.CommandText = commandText;
			reader = command.ExecuteReader();

			if(reader != NULL && reader->HasTables && reader->Tables.GetAt(0)->HasRows)
			{
				bItemAdded = true;

				table = reader->Tables.GetAt(0);
				for(INT nRow = 0; nRow < table->RowsCount; nRow++)
				{
					CString strTableName = table->GetValueToString(nRow, table->GetColumnOrdinal(columnNameFind), _T("<null>"));

					hItem = wndServerView.InsertTreeItem(strTableName, imageIndex, imageIndex, phItem);	
					wndServerView.SetItemData(hItem, nodeValue);
					wndServerView.SetItemState(hItem, 0, TVIS_EXPANDPARTIAL);
				}
			}

			if(reader != NULL)
			{
				delete reader;
				reader = NULL;
			}
		}

		if(!bItemAdded && bIfNotAdded)
		{
			hItem = wndServerView.InsertItem(_T("<no information details>"), -1, -1, phItem);
			wndServerView.SetItemData(hItem, SHLDATACONNECTION_ID_TREE_DATA_NO_INFORMATION);
			wndServerView.SetItemState(hItem, 0, TVIS_EXPANDPARTIAL);
		}

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}
	
	return bRet;
}

bool CSHLQueryInstance::ShowSystemTableColumns(CViewTree& wndServerView, HTREEITEM phItemSysTable, CString strDatabasename, CString strTablename, CQueryDataConnectionEntity* pDataConnection)
{
	bool bRet = false;

	COleDBGenericCommand command;

	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table;

	CString commandText;

	bool bItemAdded = false;

	HTREEITEM hItem;

	try
	{
		// COLUMNS
		if(!pDataConnection->SelectSysTablesFields.IsEmpty())
		{
			commandText = pDataConnection->SelectSysTablesFields;
			commandText.Replace(_T("{DATABASENAME}"), strDatabasename);
			commandText.Replace(_T("{TABLENAME}"), strTablename);

			command.Connection = pDataConnection->Connection;
			command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
			command.CommandText = commandText;
			reader = command.ExecuteReader();

			if(reader != NULL && reader->HasTables && reader->Tables.GetAt(0)->HasRows)
			{
				bItemAdded = true;

				table = reader->Tables.GetAt(0);
				for(INT nRow = 0; nRow < table->RowsCount; nRow++)
				{
					CString strColumnName = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("COLUMNNAME")), _T("<null>"));
					CString strPrimaryKey = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("KEYTYPE")), _T("<null>"));

					if(strPrimaryKey == _T("P"))
						hItem = wndServerView.InsertItem(strColumnName, IMAGE_DATA_KEY, IMAGE_DATA_KEY, phItemSysTable);
					else
					if(strPrimaryKey == _T("C"))
						hItem = wndServerView.InsertItem(strColumnName, IMAGE_DATA_CONSTRAINT, IMAGE_DATA_COLUMN, phItemSysTable);
					else
						hItem = wndServerView.InsertItem(strColumnName, IMAGE_DATA_COLUMN, IMAGE_DATA_COLUMN, phItemSysTable);

					wndServerView.SetItemData(hItem, SHLDATACONNECTION_ID_TREE_DATA_SYSTEM_TABLE_COLUMNS);
					wndServerView.SetItemState(hItem, 0, TVIS_EXPANDPARTIAL);
				}
			}

			if(reader != NULL)
			{
				delete reader;
				reader = NULL;
			}

			if(!bItemAdded)
			{
				hItem = wndServerView.InsertItem(_T("<no information details>"), -1, -1, phItemSysTable);
				wndServerView.SetItemData(hItem, SHLDATACONNECTION_ID_TREE_DATA_NO_INFORMATION);
				wndServerView.SetItemState(hItem, 0, TVIS_EXPANDPARTIAL);
			}
		}

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLQueryInstance::ShowUserTableColumns(CViewTree& wndServerView, HTREEITEM phItemUserTable, CString strDatabasename, CString strTablename, CQueryDataConnectionEntity* pDataConnection)
{
	bool bRet = false;

	COleDBGenericCommand command;

	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table;

	CString commandText;

	bool bItemAdded = false;

	HTREEITEM hItem;

	try
	{
		// COLUMNS
		if(!pDataConnection->SelectUserTableFields.IsEmpty())
		{
			commandText = pDataConnection->SelectUserTableFields;
			commandText.Replace(_T("{DATABASENAME}"), strDatabasename);
			commandText.Replace(_T("{TABLENAME}"), strTablename);

			command.Connection = pDataConnection->Connection;
			command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
			command.CommandText = commandText;
			reader = command.ExecuteReader();

			if(reader != NULL && reader->HasTables && reader->Tables.GetAt(0)->HasRows)
			{
				bItemAdded = true;

				table = reader->Tables.GetAt(0);
				for(INT nRow = 0; nRow < table->RowsCount; nRow++)
				{
					CString strColumnName = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("COLUMNNAME")), _T("<null>"));
					CString strPrimaryKey = table->GetValueToString(nRow, table->GetColumnOrdinal(_T("KEYTYPE")), _T("<null>"));

					if(strPrimaryKey == _T("P"))
						hItem = wndServerView.InsertItem(strColumnName, IMAGE_DATA_KEY, IMAGE_DATA_KEY, phItemUserTable);
					else
					if(strPrimaryKey == _T("C"))
						hItem = wndServerView.InsertItem(strColumnName, IMAGE_DATA_CONSTRAINT, IMAGE_DATA_COLUMN, phItemUserTable);
					else
						hItem = wndServerView.InsertItem(strColumnName, IMAGE_DATA_COLUMN, IMAGE_DATA_COLUMN, phItemUserTable);

					wndServerView.SetItemData(hItem, SHLDATACONNECTION_ID_TREE_DATA_USER_TABLE_COLUMNS);
					wndServerView.SetItemState(hItem, 0, TVIS_EXPANDPARTIAL);
				}
			}

			if(reader != NULL)
			{
				delete reader;
				reader = NULL;
			}

			if(!bItemAdded)
			{
				hItem = wndServerView.InsertItem(_T("<no information details>"), -1, -1, phItemUserTable);
				wndServerView.SetItemData(hItem, SHLDATACONNECTION_ID_TREE_DATA_NO_INFORMATION);
				wndServerView.SetItemState(hItem, 0, TVIS_EXPANDPARTIAL);
			}
		}

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

bool CSHLQueryInstance::SetStyleDocument(UINT lexer, CDocument* docment, CStringArray& arCommands)
{
	bool bRet = false;
	CSHLQueryScintillaSqlDoc* pDoc = NULL;

	try
	{
		//pDoc = (CSHLQueryScintillaSqlDoc*)docment;
		//pDoc->SetStyleDocument(lexer, arCommands);

		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}

	return bRet;
}

CString CSHLQueryInstance::GetLastError()
{
	return m_error;
}

bool CSHLQueryInstance::AddConnection(CViewTree& wndServerView, CSHLTreeNode<CQueryDataConnectionEntity>& dataconnection, HTREEITEM& hNewItem)
{
	bool bRet = false;

	COleDBGenericConnection* conn = NULL;
	CQueryDataConnectionEntity* queryEntity = NULL;
	HTREEITEM hRoot;

	try
	{
		hRoot = wndServerView.GetRootItem();
		hNewItem = NULL;

		conn = new COleDBGenericConnection();

		conn->Provider = SHLOLEDBPROVIDER::SHL_PROVIDER_GENERIC;
		conn->Open();

		if(conn->ConnectionState == SHLCONNECTIONSTATE::Commandstate_Open)
		{
			queryEntity = new CQueryDataConnectionEntity();
			
			queryEntity->Connection = new COleDBGenericConnection();
			queryEntity->DataSource = conn->DataSource;
			queryEntity->DefaultDatabase = conn->Database;
			queryEntity->DBMSName = conn->DBMSName;
			queryEntity->DriveName = conn->ProviderName;
			queryEntity->ProviderName = conn->ProviderName;
			queryEntity->UserID = conn->Username;
			queryEntity->ConnectionString = conn->ConnectionString;
			queryEntity->ConnectionName = conn->DataSource.IsEmpty()? conn->ProviderName:conn->DataSource;
			queryEntity->State = SHLQUERYDATACONNECTIONSTATE::SHLQUERYDATACONNECTIONSTATE_NEW;
			queryEntity->IDBanco = GetIDBanco(conn->DBMSName);

			dataconnection.AddItem(queryEntity);

			CString rootText = wndServerView.GetItemText(hRoot);
			rootText.Replace(_T("*"), _T(""));
			rootText += _T("*");
			wndServerView.SetItemText(hRoot, rootText);
			wndServerView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

			CString connectionName = GetPartOf(queryEntity->ConnectionName, _A_ARQ) + _T("*");
			queryEntity->ConnectionName = connectionName;

			hNewItem = wndServerView.InsertTreeItem(connectionName, IMAGE_DATA_CONNECTION, IMAGE_DATA_CONNECTION, hRoot);
			wndServerView.SetItemData(hNewItem, SHLDATACONNECTION_ID_TREE_DATA_DATABASE_CONNECTION);
			wndServerView.SetItemState(hNewItem, 0, TVIS_EXPANDPARTIAL);

			queryEntity->TreeViewItem = hNewItem;

			bRet = true;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}

	if(conn)
	{
		conn->Close();
		delete conn;
	}
	return bRet;
}

bool CSHLQueryInstance::SaveConnections(CSHLTreeNode<CQueryDataConnectionEntity>& dataconnection)
{
	CPtrArray toDelete;
	CString connectionString;

	bool bRet = false;

	CString commandTextInsert = _T("INSERT INTO CONEXOES (cDataSource, cDefaultDataBase, cDBMSName, cDriveName, cProviderName, cUserID, cServerName, cConnectionString, cConnectionName) VALUES ('{1}', '{2}', '{3}', '{4}', '{5}', '{6}', '{7}', '{8}', '{9}')");
	CString commandTextUpdate = _T("UPDATE CONEXOES SET   cDataSource = '{1}', cDefaultDataBase = '{2}', cDBMSName = '{3}', cDriveName = '{4}', cProviderName = '{5}', cUserID = '{6}', cServerName = '{7}', cConnectionString = '{8}', cConnectionName = '{9}' WHERE nIDConexoes = {0}");
	CString commandTextDelete = _T("DELETE FROM CONEXOES WHERE nIDConexoes = {0}");
	CString commandText;

	COleDBGenericCommand command;
	COleDBGenericTransaction transaction;

	CQueryDataConnectionEntity* queryEntity;


	try
	{
		if(m_conn.ConnectionState == SHLCONNECTIONSTATE::Commandstate_Closed)
		{
			if(!m_conn.Open())
			{
				m_error = m_conn.ErrorMessage;
				throw -1;
			}
		}

		transaction.Connection = &m_conn;
		transaction.Begin();

		command.Connection = &m_conn;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;

		for(UINT nIndex = 0; nIndex < dataconnection.GetItemCount(); nIndex++)
		{
			queryEntity = dataconnection.GetItemAt(nIndex);

			switch(queryEntity->State)
			{
				case SHLQUERYDATACONNECTIONSTATE::SHLQUERYDATACONNECTIONSTATE_NIL:
					continue;
				case SHLQUERYDATACONNECTIONSTATE::SHLQUERYDATACONNECTIONSTATE_NEW:
					commandText = commandTextInsert;
					break;
				case SHLQUERYDATACONNECTIONSTATE::SHLQUERYDATACONNECTIONSTATE_UPDATE:
					commandText = commandTextUpdate;
					break;
				case SHLQUERYDATACONNECTIONSTATE::SHLQUERYDATACONNECTIONSTATE_DELETE:
					commandText = commandTextDelete;
					break;
			}

			connectionString = queryEntity->ConnectionString;
			connectionString.Replace(_T("\'"), _T("\'\'"));
			commandText.Replace(_T("{0}"), Str(queryEntity->IDConnection));
			commandText.Replace(_T("{1}"), queryEntity->DataSource);
			commandText.Replace(_T("{2}"), queryEntity->DefaultDatabase);
			commandText.Replace(_T("{3}"), queryEntity->DBMSName);
			commandText.Replace(_T("{4}"), queryEntity->DriveName);
			commandText.Replace(_T("{5}"), queryEntity->ProviderName);
			commandText.Replace(_T("{6}"), queryEntity->UserID);
			commandText.Replace(_T("{7}"), queryEntity->ServerName);
			commandText.Replace(_T("{8}"), connectionString);
			commandText.Replace(_T("{9}"), queryEntity->ConnectionName);
			commandText.Replace(_T("*"), _T(""));

			command.CommandText = commandText;
			command.ExecuteNonQuery();
			if(command.HasErrors)
			{
				m_error = command.ErrorMessage;
				throw -1;
			}

		}

		for(UINT nIndex = 0; nIndex < dataconnection.GetItemCount(); nIndex++)
		{
			queryEntity = dataconnection.GetItemAt(nIndex);

			if(queryEntity->State == SHLQUERYDATACONNECTIONSTATE::SHLQUERYDATACONNECTIONSTATE_DELETE)
			{
				toDelete.Add(queryEntity);
			}
		}

		for(INT_PTR nIndex = 0; nIndex < toDelete.GetSize(); nIndex++)
		{
			queryEntity = (CQueryDataConnectionEntity*)toDelete.GetAt(nIndex);
			dataconnection.RemoveItem(queryEntity);
		}

		transaction.Commit();


		bRet = true;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error +=  szMessage;

		transaction.Rollback();
	}
	catch(...)
	{
		m_error += ErrorMessage(::GetLastError());

		transaction.Rollback();
	}

	m_conn.Close();

	return bRet;
}

void CSHLQueryInstance::NewQuery(CQueryDataConnectionEntity* dataconnection, CDocument* pDoc, CString database)
{	
	CSHLQueryScintillaSqlDoc* pDocument = NULL;
	CString connectionstring;
	INT IDBanco = -1;
	CString dbmsName;

	try
	{
		if(dataconnection)
		{
			connectionstring = dataconnection->ConnectionString;
			IDBanco = dataconnection->IDBanco;
		}

		pDocument = (CSHLQueryScintillaSqlDoc*)pDoc;
		pDocument->SetStyleDocument(SCLEX_MSSQL, dataconnection, database);
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}
}

void CSHLQueryInstance::Release()
{
	try
	{
		delete this;
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}
}
#pragma endregion REGION_PUBLIC_METHODS

#pragma region REGION_PRIVATE_METHODS
bool CSHLQueryInstance::DeleteChildItemTreeView(CViewTree& wndServerView, HTREEITEM phItem)
{
	bool bResultado = TRUE;

	HTREEITEM hNextItem;
	HTREEITEM hChildItem;

	try
	{
		hChildItem = wndServerView.GetChildItem(phItem);
		
		while (hChildItem != NULL && bResultado)
		{
			if (wndServerView.ItemHasChildren(hChildItem))
				bResultado = DeleteChildItemTreeView(wndServerView, hChildItem);

			if (!bResultado)
				break;

			hNextItem = wndServerView.GetNextItem(hChildItem, TVGN_NEXT);
			bResultado = (bool)(wndServerView.DeleteItem(hChildItem));
			hChildItem = hNextItem;
		}
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		m_error =  szMessage;
	}
	catch(...)
	{
		m_error = ErrorMessage(::GetLastError());
	}

	return bResultado;
}

ULONG CSHLQueryInstance::GetIDBanco(CString dbmsname)
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

		conn.ConnectionString = m_conn.ConnectionString;
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

void CSHLQueryInstance::BuildSelectCommands(CString& commandSelectConnections, CString& commandSelectDatabaseQueries)
{
	commandSelectConnections = _T("SELECT nIDConexoes, cConnectionName, cConnectionString, cDataSource, cDefaultDataBase, cDBMSName, cDriveName, cProviderName, cUserID, cServerName FROM CONEXOES ORDER BY NIDCONEXOES");

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
	commandSelectDatabaseQueries += _T("FROM BANCO AS A, DBMS AS B\n ");
	commandSelectDatabaseQueries += _T("WHERE A.NIDBANCO = B.NIDBANCO\n ");
	commandSelectDatabaseQueries += _T("  AND B.CNOME = '{DBMS}'\n ");
}
#pragma endregion REGION_PRIVATE_METHODS

/***********************************************************************************
 *                                                                                 *
 * Cria um objeto GetSHLStudioProjectInstance.                                     *
 *                                                                                 *
 ***********************************************************************************/
SHLQUERY_API SHLQUERYHANDLE APIENTRY GetSHLQueryInstance()
{
	return new CSHLQueryInstance;
}
