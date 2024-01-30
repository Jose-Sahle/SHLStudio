/* ***************************************************************************
 * Arquivo: DatabaseItemGenerateView                                         *
 *                                                                           *
 * Classe utilizada para gerar o XML do Database                             *
 *                                                                           *
 * Data:21/06/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *************************************************************************** */
#include "stdafx.h"
#include "resource.h"
#include "DatabaseItemGenerateView.h"
#include "library.h"
#include "Markup.h"

// CDatabaseItemGenerateView

IMPLEMENT_DYNCREATE(CDatabaseItemGenerateView, CFormView)

CDatabaseItemGenerateView::CDatabaseItemGenerateView()
	: CFormView(CDatabaseItemGenerateView::IDD)
{
	m_conn = NULL;
	m_noexecuteevents = FALSE;
}

CDatabaseItemGenerateView::~CDatabaseItemGenerateView()
{
}

void CDatabaseItemGenerateView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DATABASE, m_cmbDatabase);
	DDX_Control(pDX, IDC_LIST_TABLES, m_chklstTable);
	DDX_Control(pDX, IDC_RICHEDIT_DESCRIPTION, m_txtInformation);
}

BEGIN_MESSAGE_MAP(CDatabaseItemGenerateView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE_DATABASE_FILE_XML, &CDatabaseItemGenerateView::OnBnClickedButtonGenerateDatabaseFileXml)

	ON_MESSAGE(WM_SET_PROJECT_ITEM, OnSetProjectItem)
	ON_CBN_SELCHANGE(IDC_COMBO_DATABASE, &CDatabaseItemGenerateView::OnCbnSelchangeComboDatabase)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_ALL, &CDatabaseItemGenerateView::OnBnClickedButtonSelectAll)
	ON_BN_CLICKED(IDC_BUTTON_UNSELECT_ALL, &CDatabaseItemGenerateView::OnBnClickedButtonUnselectAll)
END_MESSAGE_MAP()


// CDatabaseItemGenerateView diagnostics

#ifdef _DEBUG
void CDatabaseItemGenerateView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDatabaseItemGenerateView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDatabaseItemGenerateView message handlers

#pragma region EVENTS
void CDatabaseItemGenerateView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_chklstTable.SetCheckStyle( BS_AUTOCHECKBOX );

	SetInfomartionText();
}

void CDatabaseItemGenerateView::OnBnClickedButtonGenerateDatabaseFileXml()
{
	GenerateXML();	
}

void CDatabaseItemGenerateView::OnBnClickedButtonSelectAll()
{
	SetSelectAll(TRUE);
}

void CDatabaseItemGenerateView::OnBnClickedButtonUnselectAll()
{
	SetSelectAll(FALSE);
}

LRESULT CDatabaseItemGenerateView::OnSetProjectItem(WPARAM wParam, LPARAM lParam)
{
	SetProjectItem(wParam, lParam);
	SetQueries();
	SetDatabaseCombo();

	return 0;
}

void CDatabaseItemGenerateView::OnCbnSelchangeComboDatabase()
{
	if(m_noexecuteevents)
		return;

	CString database;
	m_cmbDatabase.GetWindowText(database);
	SetTableList(database);
}
#pragma endregion EVENTS

#pragma region PRIVATE_METHODS
void CDatabaseItemGenerateView::SetProjectItem(WPARAM wParam, LPARAM lParam)
{
	try
	{
		m_pProject	= (CProjectEntity*)wParam;
		m_pItem		= (CItemEntity*)lParam;		

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

void CDatabaseItemGenerateView::SetTableList(CString database)
{
	CString propertyname;
	CString connectionType;
	SHLOleDBReader* reader = NULL;

	try
	{
		BeginWaitCursor();

		propertyname = _T("ConnectionType");
		connectionType = m_pItem->Properties[propertyname];

		if(connectionType == _T("MS-Sql Server"))
		{
			reader = SelectSqlServer(database, _T(""), m_tablequery);
		}
		else
		if(connectionType == _T("Access"))
		{
			reader = SelectAccess(database, _T(""), m_tablequery);
		}
		else
		if(connectionType == _T("MySQL"))
		{
			reader = SelectMySQL(database, _T(""), m_tablequery);
		}
		else
		if(connectionType == _T("PostGres"))
		{
			reader = SelectPostGreSQL(database, _T(""), m_tablequery);
		}
		else
		if(connectionType == _T("Oracle"))
		{
			reader = SelectOracle(database, _T(""), m_tablequery);
		}

		FillTable(reader);
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

	EndWaitCursor();

	if(reader)
		delete reader;
}

void CDatabaseItemGenerateView::SetSelectAll(BOOL checkTo)
{
	INT nCount = 0;

	try
	{
		for(INT nIndex = 0; nIndex < m_chklstTable.GetCount(); nIndex++)
		{
			m_chklstTable.SetCheck(nIndex, checkTo);
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

void CDatabaseItemGenerateView::SetDatabaseCombo()
{
	CString propertyname;
	CString server;
	CString database;
	CString user;
	CString password;
	CString connectionType;
	CString datasource;
	CString providertype;
	SHLOleDBReader* reader = NULL;

	try
	{
		BeginWaitCursor();

		m_noexecuteevents = TRUE;

		propertyname = _T("ConnectionServer");
		server = m_pItem->Properties[propertyname];

		propertyname = _T("ConnectionDataSource");
		datasource = m_pItem->Properties[propertyname];

		propertyname = _T("ConnectionDatabase");
		database = m_pItem->Properties[propertyname];

		propertyname = _T("ConnectionUser");
		user = m_pItem->Properties[propertyname];

		propertyname = _T("ConnectionPwd");
		password = m_pItem->Properties[propertyname];

		propertyname = _T("ConnectionType");
		connectionType = m_pItem->Properties[propertyname];

		propertyname = _T("ProviderType");
		providertype = m_pItem->Properties[propertyname];

		if(connectionType == _T("MS-Sql Server"))
		{
			reader = SelectSqlServerDatabase(server, datasource, database, user, password, providertype);
		}
		else
		if(connectionType == _T("Access"))
		{
			reader = SelectAccessDatabase(server, datasource, database, user, password, providertype);
		}
		else
		if(connectionType == _T("MySQL"))
		{
			reader = SelectMySQLDatabase(server, datasource, database, user, password, providertype);
		}
		else
		if(connectionType == _T("PostGres"))
		{
			reader = SelectPostGreSQLDatabase(server, datasource, database, user, password, providertype);
		}
		else
		if(connectionType == _T("Oracle"))
		{
			reader = SelectOracleDatabase(server, datasource, database, user, password, providertype);
		}

		if(reader  != NULL)
		{
			FillCombo(reader, database);
			SetTableList(database);
		}

		m_noexecuteevents = FALSE;
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

	EndWaitCursor();

	if(reader)
		delete reader;

}

SHLOleDBReader* CDatabaseItemGenerateView::SelectSqlServerDatabase(CString server, CString datasource, CString database, CString user, CString password, CString providertype)
{
	COleDBSqlServerCommand command;
	SHLOleDBReader* reader = NULL;
	CString msgError;

	try
	{
		m_conn = new COleDBSqlServerConnection();
		m_conn->Server = server;
		m_conn->Database = database;
		m_conn->Username = user;
		m_conn->Password = password;

		if(!datasource.IsEmpty())
		{
			m_conn->DataSource = datasource;
			m_conn->Provider = SHLOLEDBPROVIDER::SHL_MSODBC_PROVIDER_MSDASQL_1;
		}
		else
		{
			if (providertype == _T("SQLSERVER_PROVIDER_SQLNCLI10"))
				m_conn->Provider = SHLOLEDBPROVIDER::SHL_SQLSERVER_PROVIDER_SQLNCLI10;
			else 
			if (providertype == _T("SQLSERVER_PROVIDER_SQLOLEDB_1"))
				m_conn->Provider = SHLOLEDBPROVIDER::SHL_SQLSERVER_PROVIDER_SQLOLEDB_1;
			if (providertype == _T("SQLSERVER_PROVIDER_SQLOLEDB"))
				m_conn->Provider = SHLOLEDBPROVIDER::SHL_SQLSERVER_PROVIDER_SQLOLEDB;
			else
				m_conn->Provider = SHLOLEDBPROVIDER::SHL_SQLSERVER_PROVIDER_SQLOLEDB;
		}

		if(!m_conn->Open())
		{
			msgError = m_conn->ErrorMessage;
			throw -1;
		}

		command.Connection = m_conn;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
		command.CommandText = m_databasequery;

		reader = command.ExecuteReader();
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch(...)
	{
		if(msgError.IsEmpty())
			msgError = ErrorMessage(::GetLastError());

		AfxMessageBox(msgError);
	}

	return reader;
}

SHLOleDBReader* CDatabaseItemGenerateView::SelectAccessDatabase(CString server, CString datasource, CString database, CString user, CString password, CString providertype)
{
	COleDBSqlServerCommand command;
	SHLOleDBReader* reader = NULL;
	CString msgError;

	try
	{
		m_conn = new COleDBGenericConnection();
		m_conn->ConnectionString = _T("Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=");
		m_conn->ConnectionString += database;
		m_conn->ConnectionString += _T(";Mode=Share Deny None;Extended Properties=\"\";");
		m_conn->ConnectionString += _T("Jet OLEDB:System database=\"\";");
		m_conn->ConnectionString += _T("Jet OLEDB:Registry Path=\"\";");
		if (password != _T(""))
		{
			m_conn->ConnectionString += _T("Jet OLEDB:Database Password=\"");
			m_conn->ConnectionString += password;
			m_conn->ConnectionString += _T(";");
		}
		m_conn->ConnectionString += _T("Jet OLEDB:Engine Type=5;");
		m_conn->ConnectionString += _T("Jet OLEDB:Database Locking Mode=1;");
		m_conn->ConnectionString += _T("Jet OLEDB:Global Partial Bulk Ops=2;");
		m_conn->ConnectionString += _T("Jet OLEDB:Global Bulk Transactions=1;");
		m_conn->ConnectionString += _T("Jet OLEDB:New Database Password=\"\";");
		m_conn->ConnectionString += _T("Jet OLEDB:Create System Database=False;");
		m_conn->ConnectionString += _T("Jet OLEDB:Encrypt Database=False;");
		m_conn->ConnectionString += _T("Jet OLEDB:Don't Copy Locale on Compact=False;");
		m_conn->ConnectionString += _T("Jet OLEDB:Compact Without Replica Repair=False;");
		m_conn->ConnectionString += _T("Jet OLEDB:SFP=False");
		m_conn->Provider = SHLOLEDBPROVIDER::SHL_PROVIDER_CONNECTIONSTRING;

		if (!m_conn->Open())
		{
			msgError = m_conn->ErrorMessage;
			throw - 1;
		}

		command.Connection = m_conn;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
		command.CommandText = _T("SELECT 0 AS ID, 'User' AS NAME");

		reader = command.ExecuteReader();
	}
	catch (CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch (...)
	{
		if (msgError.IsEmpty())
			msgError = ErrorMessage(::GetLastError());

		AfxMessageBox(msgError);
	}

	return reader;
}

SHLOleDBReader* CDatabaseItemGenerateView::SelectMySQLDatabase(CString server, CString datasource, CString database, CString user, CString password, CString providertype)
{
	COleDBMySQLCommand command;
	SHLOleDBReader* reader = NULL;
	CString msgError;

	try
	{
		m_conn = new COleDBMySQLConnection();
		m_conn->Server = server;
		m_conn->Database = database;
		m_conn->Username = user;
		m_conn->Password = password;
		if(!datasource.IsEmpty())
		{
			m_conn->DataSource = datasource;
			m_conn->Provider = SHLOLEDBPROVIDER::SHL_MSODBC_PROVIDER_MSDASQL_1;
		}
		else
		{
			m_conn->Provider = SHLOLEDBPROVIDER::SHL_MYSQL_PROVIDER_MYSQLPROV;
		}

		if(!m_conn->Open())
		{
			msgError = m_conn->ErrorMessage;
			throw -1;
		}

		command.Connection = m_conn;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
		command.CommandText = m_databasequery;

		reader = command.ExecuteReader();
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch(...)
	{
		if(msgError.IsEmpty())
			msgError = ErrorMessage(::GetLastError());

		AfxMessageBox(msgError);
	}

	return reader;
}

SHLOleDBReader* CDatabaseItemGenerateView::SelectPostGreSQLDatabase(CString server, CString datasource, CString database, CString user, CString password, CString providertype)
{
	COleDBPostGreSQLCommand command;
	SHLOleDBReader* reader = NULL;
	CString msgError;

	try
	{
		m_conn = new COleDBPostGreSQLConnection();
		m_conn->Server = server;
		m_conn->Database = database;
		m_conn->Username = user;
		m_conn->Password = password;
		if(!datasource.IsEmpty())
		{
			m_conn->DataSource = datasource;
			m_conn->Provider = SHLOLEDBPROVIDER::SHL_MSODBC_PROVIDER_MSDASQL_1;
		}
		else
			m_conn->Provider = SHLOLEDBPROVIDER::SHL_POSTGRESQL_PROVIDER_PGNP;

		if(!m_conn->Open())
		{
			msgError = m_conn->ErrorMessage;
			throw -1;
		}

		command.Connection = m_conn;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
		command.CommandText = m_databasequery;

		reader = command.ExecuteReader();
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch(...)
	{
		if(msgError.IsEmpty())
			msgError = ErrorMessage(::GetLastError());

		AfxMessageBox(msgError);
	}

	return reader;
}

SHLOleDBReader* CDatabaseItemGenerateView::SelectOracleDatabase(CString server, CString datasource, CString database, CString user, CString password, CString providertype)
{
	COleDBOracleCommand command;
	SHLOleDBReader* reader = NULL;
	CString msgError;

	try
	{
		m_conn = new COleDBOracleConnection();
		m_conn->Server = server;
		m_conn->Database = database;
		m_conn->Username = user;
		m_conn->Password = password;
		if(!datasource.IsEmpty())
		{
			m_conn->DataSource = datasource;
			m_conn->Provider = SHLOLEDBPROVIDER::SHL_MSODBC_PROVIDER_MSDASQL_1;
		}
		else
			m_conn->Provider = SHLOLEDBPROVIDER::SHL_ORACLE_PROVIDER_MSDAORA;

		if(!m_conn->Open())
		{
			msgError = m_conn->ErrorMessage;
			throw -1;
		}

		command.Connection = m_conn;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
		command.CommandText = m_databasequery;

		reader = command.ExecuteReader();
	}
	catch(CException* ex)
	{
		TCHAR szMessage[4000];

		BOOL bCapturouMensagem = ex->GetErrorMessage(szMessage, 4000, NULL);

		AfxMessageBox(szMessage);
	}
	catch(...)
	{
		if(msgError.IsEmpty())
			msgError = ErrorMessage(::GetLastError());

		AfxMessageBox(msgError);
	}

	return reader;
}

void CDatabaseItemGenerateView::FillTable(SHLOleDBReader* reader)
{
	SHLOleDBTable* table;

	try
	{		
		if(!reader)
			return;

		m_chklstTable.ResetContent();

		table = reader->Tables.GetAt(0);

		if(table->HasRows)
		{
			for(int nRowIndex = 0; nRowIndex < table->RowsCount; nRowIndex++)
			{
				CString strValue = table->GetValueToString(nRowIndex, table->GetColumnOrdinal(_T("TABLE_NAME")), _T("<null>"));

				m_chklstTable.AddString(strValue);
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
}

void CDatabaseItemGenerateView::FillCombo(SHLOleDBReader* reader, CString database)
{
	SHLOleDBTable* table;
	INT nCurSel = 0;

	try
	{
		table = reader->Tables.GetAt(0);

		if(table->HasRows)
		{
			for(int nRowIndex = 0; nRowIndex < table->RowsCount; nRowIndex++)
			{
				CString strValue = table->GetValueToString(nRowIndex, table->GetColumnOrdinal(_T("NAME")), _T("<null>"));

				if(strValue.MakeLower() == database.MakeLower())
					nCurSel = nRowIndex;

				m_cmbDatabase.AddString(strValue);
			}

			m_cmbDatabase.SetCurSel(nCurSel);
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

SHLOleDBReader* CDatabaseItemGenerateView::SelectSqlServer(CString database, CString tablename, CString query)
{
	COleDBSqlServerCommand command;
	SHLOleDBReader* reader = NULL;
	CString commandText;

	try
	{
		commandText = query;
		commandText.Replace(_T("#DatabaseName#"), database);
		commandText.Replace(_T("#TableName#"), tablename);

		command.Connection = m_conn;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
		command.CommandText = commandText;

		reader = command.ExecuteReader();
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

	return reader;
}

SHLOleDBReader* CDatabaseItemGenerateView::SelectFieldAccess(CString database, CString tablename, CString query)
{
	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table = NULL;
	SHLDBCOLUMN* columninfo = NULL;
	CSHLList<SHLDBCOLUMN>* columnsinfo = NULL;
	SHLDBROW* row = NULL;

	try
	{
		columnsinfo = m_conn->RetriveInformationSchemaColumns(tablename);

		if (columnsinfo->GetCount() > 0)
		{
			reader = new SHLOleDBReader;

			table = new SHLOleDBTable;

			table->TableName = _T("AccessFields");
			table->AddColumn(0, _T("COLUMNNAME"), SHLDBTYPE::SHLDBType_String, 256, false);
			table->AddColumn(1, _T("IS_IDENTITY"), SHLDBTYPE::SHLDBType_Int32, 0, false);
			table->AddColumn(2, _T("IS_FOREIGNKEY"), SHLDBTYPE::SHLDBType_Int32, 0, false);
			table->AddColumn(3, _T("TABLE_FOREIGNKEY"), SHLDBTYPE::SHLDBType_String, 256, false);
			table->AddColumn(4, _T("DATA_TYPE"), SHLDBTYPE::SHLDBType_String, 15, false);
			table->AddColumn(5, _T("DATA_SIZE"), SHLDBTYPE::SHLDBType_Int32, 0, false);
			table->AddColumn(6, _T("IS_PRIMARYKEY"), SHLDBTYPE::SHLDBType_Int32, 0, false);

			reader->Tables.Add(table);

			for (int nindex = 0; nindex < columnsinfo->GetCount(); nindex++)
			{
				columninfo = columnsinfo->GetAt(nindex);

				row = new SHLDBROW;
				row->value = new SHLBINDVALUE[7];

				_tcscpy_s(row->value[0].data.szVal, columninfo->szColumName);
				row->value[1].data.iVal = columninfo->IsPrimaryKey ? 1 : 0;
				row->value[2].data.iVal = 0;
				row->value[3].data.szVal[0] = '\0';
				_tcscpy_s(row->value[4].data.szVal, GetSHLOleDBType(columninfo->DBType));
				row->value[5].data.iVal = columninfo->nSize;
				row->value[6].data.iVal = columninfo->IsPrimaryKey ? 1 : 0;

				table->Rows.Add(row);
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


	if (columninfo != NULL)
		delete columninfo;

	return reader;

}

CString CDatabaseItemGenerateView::GetSHLOleDBType(SHLDBTYPE dbtype)
{
	CString strValue;

	switch (dbtype)
	{
		case SHLDBType_Empty:
			strValue = _T("String");
			break;
		case SHLDBType_Null:
			strValue = _T("String");
			break;
		case SHLDBType_Idispatch:
			strValue = _T("String");
			break;
		case SHLDBType_Error:
			strValue = _T("String");
			break;
		case SHLDBType_Unknown:
			strValue = _T("String");
			break;
		case SHLDBType_Variant:
			strValue = _T("String");
			break;
		case SHLDBType_AnsiString:
			strValue = _T("String");
			break;
		case SHLDBType_Binary:
			strValue = _T("Byte");
			break;
		case SHLDBType_Byte:
			strValue = _T("Byte");
			break;
		case SHLDBType_Boolean:
			strValue = _T("Boolean");
			break;
		case SHLDBType_Currency:
			strValue = _T("Double");
			break;
		case SHLDBType_Time:
			strValue = _T("DateTime");
			break;
		case SHLDBType_Date:
			strValue = _T("DateTime");
			break;
		case SHLDBType_DateTime:
			strValue = _T("DateTime");
			break;
		case SHLDBType_DateTime2:
			strValue = _T("DateTime");
			break;
		case SHLDBType_DateTimeOffset:
			strValue = _T("DateTime");
			break;
		case SHLDBType_Decimal:
			strValue = _T("Double");
			break;
		case SHLDBType_Double:
			strValue = _T("Double");
			break;
		case SHLDBType_Guid:
			strValue = _T("String");
			break;
		case SHLDBType_Int16:
			strValue = _T("Int16");
			break;
		case SHLDBType_Int32:
			strValue = _T("Int32");
			break;
		case SHLDBType_Int64:
			strValue = _T("Int64");
			break;
		case SHLDBType_Object:
			strValue = _T("String");
			break;
		case SHLDBType_SByte:
			strValue = _T("Int16");
			break;
		case SHLDBType_Single:
			strValue = _T("Double");
			break;
		case SHLDBType_String:
			strValue = _T("String");
			break;
		case SHLDBType_UInt16:
			strValue = _T("Int16");
			break;
		case SHLDBType_UInt32:
			strValue = _T("Int32");
			break;
		case SHLDBType_UInt64:
			strValue = _T("Int64");
			break;
		case SHLDBType_VarNumeric:
			strValue = _T("Double");
			break;
		case SHLDBType_AnsiStringFixedLength:
			strValue = _T("String");
			break;
		case SHLDBType_StringFixedLength:
			strValue = _T("String");
			break;
		case SHLDBType_Xml:
			strValue = _T("String");
			break;
	}

	return strValue;
}

SHLOleDBReader* CDatabaseItemGenerateView::SelectAccess(CString database, CString tablename, CString query)
{
	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table = NULL;
	SHLOleDBTable* tableinfo = NULL;
	SHLOleDBReader* readerinfo = NULL;
	SHLDBROW* row = NULL;

	try
	{
		readerinfo = m_conn->RetriveInformationSchema();

		if (readerinfo->HasTables)
		{
			reader = new SHLOleDBReader;

			table = new SHLOleDBTable;

			table->TableName = _T("Access");
			table->AddColumn(0, _T("TABLEID"), SHLDBTYPE::SHLDBType_Int32, 0, false);
			table->AddColumn(1, _T("TABLE_NAME"), SHLDBTYPE::SHLDBType_String, 1, false);

			reader->Tables.Add(table);

			for (int nindex = 0; nindex < readerinfo->TablesCount; nindex++)
			{
				tableinfo = readerinfo->Tables.GetAt(nindex);
				row = new SHLDBROW;
				row->value = new SHLBINDVALUE[2];

				row->value[0].data.intVal = nindex;
				_tcscpy_s(row->value[1].data.szVal, tableinfo->TableName);

				table->Rows.Add(row);
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


	if (readerinfo != NULL)
		delete readerinfo;

	return reader;
}

SHLOleDBReader* CDatabaseItemGenerateView::SelectMySQL(CString database, CString tablename, CString query)
{
	COleDBMySQLCommand command;
	SHLOleDBReader* reader = NULL;
	CString commandText;

	try
	{
		commandText = query;
		commandText.Replace(_T("#DatabaseName#"), database);
		commandText.Replace(_T("#TableName#"), tablename);

		command.Connection = m_conn;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
		command.CommandText = commandText;

		reader = command.ExecuteReader();
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

	return reader;
}

SHLOleDBReader* CDatabaseItemGenerateView::SelectPostGreSQL(CString database, CString tablename, CString query)
{
	COleDBPostGreSQLCommand command;
	SHLOleDBReader* reader = NULL;
	CString commandText;

	try
	{
		if(!m_conn->ChangeDatabase(database))
		{
			CString msg;
			msg.Format(_T("Can't connect to %s"), database);
			AfxMessageBox(msg);
			return FALSE;
		}
		commandText = query;
		commandText.Replace(_T("#DatabaseName#"), database);
		commandText.Replace(_T("#TableName#"), tablename);

		command.Connection = m_conn;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
		command.CommandText = commandText;

		reader = command.ExecuteReader();
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

	return reader;
}

SHLOleDBReader* CDatabaseItemGenerateView::SelectOracle(CString database, CString tablename, CString query)
{
	COleDBOracleCommand command;
	SHLOleDBReader* reader = NULL;
	CString commandText;

	try
	{
		commandText = query;
		commandText.Replace(_T("#DatabaseName#"), database);
		commandText.Replace(_T("#TableName#"), tablename);

		command.Connection = m_conn;
		command.CommandType = SHLCOMMANDTYPE::Commandtype_Text;
		command.CommandText = commandText;

		reader = command.ExecuteReader();
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

	return reader;
}

SHLOleDBReader* CDatabaseItemGenerateView::SelectField(CString databasename, CString tablename)
{
	SHLOleDBReader* reader = NULL;
	CString connectionType;
	CString propertyname;

	try
	{
		propertyname = _T("ConnectionType");
		connectionType = m_pItem->Properties[propertyname];

		if(connectionType == _T("MS-Sql Server"))
		{
			reader = SelectSqlServer(databasename, tablename, m_columnquery);
		}
		else
		if(connectionType == _T("Access"))
		{
			reader = SelectFieldAccess(databasename, tablename, m_columnquery);
		}
		else
		if(connectionType == _T("MySQL"))
		{
			reader = SelectMySQL(databasename, tablename, m_columnquery);
		}
		else
		if(connectionType == _T("PostGres"))
		{
			reader = SelectPostGreSQL(databasename, tablename, m_columnquery);
		}
		else
		if(connectionType == _T("Oracle"))
		{
			reader = SelectOracle(databasename, tablename, m_columnquery);
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

	return reader;
}

void CDatabaseItemGenerateView::SetQueries()
{
	CString strFileName;
	CString strName;
	CPath path;

	try
	{
		strName = _T("ConnectionDependencySelectCatalog");
		if (m_pItem->Properties[strName] != _T(""))
		{
			path.AddPath(2, m_pItem->Path, m_pItem->Properties[strName]);
			strFileName = path.GetPath();
			m_databasequery = ReadFullFile(strFileName);
		}
		else
			m_databasequery = _T("");

		if (m_pItem->Properties[strName] != _T(""))
		{
			strName = _T("ConnectionDependencySelectTable");
			path.AddPath(2, m_pItem->Path, m_pItem->Properties[strName]);
			strFileName = path.GetPath();
			m_tablequery = ReadFullFile(strFileName);
		}
		else
			m_tablequery = _T("");

		if (m_pItem->Properties[strName] != _T(""))
		{
			strName = _T("ConnectionDependencySelectColumn");
			path.AddPath(2, m_pItem->Path, m_pItem->Properties[strName]);
			strFileName = path.GetPath();
			m_columnquery = ReadFullFile(strFileName);
		}
		else
			m_columnquery = _T("");
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

void CDatabaseItemGenerateView::GenerateXML()
{
	SHLOleDBReader* reader = NULL;
	SHLOleDBTable* table;
	CMarkup xml = NULL;
	CString tempfilename = _T("");
	CString filename = _T("");
	TCHAR szTempPath[256];
	CString tablename;
	CString databasename;
	CString value;
	CPath path;

	try
	{
		BeginWaitCursor();

		memset(szTempPath, NULL, 256 * sizeof(TCHAR));

		GetTempPath(256, szTempPath);

		path.AddPath(2, CString(szTempPath), m_pItem->FileName);
		tempfilename = path.GetPath();

		path.AddPath(2, m_pItem->Path, m_pItem->FileName);
		filename = path.GetPath();

		if(ArquivoExiste(tempfilename))
			DeleteFile(tempfilename);

		xml.AddElem(_T("Settings"));

		xml.IntoElem();

		m_cmbDatabase.GetWindowText(databasename);

		for(INT nIndexTable = 0; nIndexTable < m_chklstTable.GetCount(); nIndexTable++)
		{
			if(!m_chklstTable.GetCheck(nIndexTable))
				continue;

			m_chklstTable.GetText(nIndexTable, tablename);

			xml.AddElem(_T("Table"));
			xml.SetAttrib(_T("Name"), tablename);

			reader = SelectField(databasename, tablename);
			if(reader == NULL)
				continue;

			if (!reader->HasTables || reader->Tables.GetCount() == 0)
			{
				delete reader;
				reader = NULL;
				continue;
			}

			table = reader->Tables.GetAt(0);

			xml.IntoElem();

			for(INT row = 0; row < table->Rows.GetCount(); row++)
			{
				INT columnid;

				xml.AddElem(_T("Field"));

				columnid = table->GetColumnOrdinal(_T("COLUMNNAME"));
				if(columnid == -1)
				{
					AfxMessageBox(_T("Column 'COLUMNNAME' don't exist in Dependency Column Query File."));
					return;
				}
				value = table->GetValueToString(row, columnid, _T(""));
				xml.SetAttrib(_T("Name"), value);

				columnid = table->GetColumnOrdinal(_T("IS_PRIMARYKEY"));
				if(columnid == -1)
				{
					AfxMessageBox(_T("Column 'IS_PRIMARYKEY' don't exist in Dependency Column Query File."));
					return;
				}
				value = table->GetValueToString(row, columnid, _T(""));
				xml.SetAttrib(_T("PrimaryKey"), value);

				columnid = table->GetColumnOrdinal(_T("IS_IDENTITY"));
				if(columnid == -1)
				{
					AfxMessageBox(_T("Column 'IS_IDENTITY' don't exist in Dependency Column Query File."));
					return;
				}
				value = table->GetValueToString(row, columnid, _T(""));
				xml.SetAttrib(_T("Identity"), value);

				columnid = table->GetColumnOrdinal(_T("DATA_TYPE"));
				if(columnid == -1)
				{
					AfxMessageBox(_T("Column 'DATA_TYPE' don't exist in Dependency Column Query File ."));
					return;
				}
				value = table->GetValueToString(row, columnid, _T(""));
				xml.SetAttrib(_T("DBType"), value);

				columnid = table->GetColumnOrdinal(_T("DATA_SIZE"));
				if(columnid == -1)
				{
					AfxMessageBox(_T("Column 'DATA_SIZE' don't exist in Dependency Column Query File ."));
					return;
				}
				value = table->GetValueToString(row, columnid, _T(""));
				xml.SetAttrib(_T("DBSize"), value);

				columnid = table->GetColumnOrdinal(_T("IS_FOREIGNKEY"));
				if(columnid == -1)
				{
					AfxMessageBox(_T("Column 'IS_FOREIGNKEY' don't exist in Dependency Column Query File ."));
					return;
				}
				value = table->GetValueToString(row, columnid, _T(""));
				xml.SetAttrib(_T("ForeignKey"), value);

				columnid = table->GetColumnOrdinal(_T("TABLE_FOREIGNKEY"));
				if(columnid == -1)
				{
					AfxMessageBox(_T("Column 'TABLE_FOREIGNKEY' don't exist in Dependency Column Query File ."));
					return;
				}
				value = table->GetValueToString(row, columnid, _T(""));
				xml.SetAttrib(_T("TableForeignKey"), value);
			}

			xml.OutOfElem();

			if (reader != NULL)
			{
				delete reader;
				reader = NULL;
			}
		}

		xml.Save(tempfilename);

		if(ArquivoExiste(filename))
			DeleteFile(filename);

		MoveFile(tempfilename, filename);
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

	if (reader != NULL)
	{
		delete reader;
		reader = NULL;
	}

	EndWaitCursor();
}

CString CDatabaseItemGenerateView::ReadFullFile(CString filename)
{
	CString strContent;
	CString strFileName;

	HANDLE hFile = NULL;
	char *filebuffer = NULL;
	DWORD bytereaded;
	LARGE_INTEGER filesize;
	LONGLONG size;

	try
	{
		hFile = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,  NULL); 
		
		if(hFile == INVALID_HANDLE_VALUE)
		{
			hFile = NULL;
			throw -1;
		}

		GetFileSizeEx(hFile, &filesize);
		size = filesize.QuadPart + 1;

		filebuffer = new char[size];
		memset(filebuffer, NULL, size);

		ReadFile(hFile, filebuffer, size, &bytereaded, NULL);

		strContent = CString(filebuffer);

		delete[] filebuffer;

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

	if(hFile)
		CloseHandle(hFile);

	return strContent;
}

void CDatabaseItemGenerateView::SetInfomartionText()
{
	CString text;

	try
	{
		text  = _T("Select a database in the ComboBox.\n\n");
		InsertText(text, RGB(0, 0, 156), false, false, 10);

		text = _T("Then choose one or more tables marking the CheckBox.\n\n");
		InsertText(text, RGB(0, 0, 156), false, false, 10);

		text = _T("For each selected table will be generated");
		InsertText(text, RGB(0, 0, 156), false, false, 10);

		text = _T(" METADATA\n");
		InsertText(text, RGB(0, 0, 156), true, true, 10);

		text = _T("that can be used as a data source for PostGreSQL, MySQL,\n");
		InsertText(text, RGB(0, 0, 156), false, false, 10);

		text = _T("Oracle and SQL Server.");
		InsertText(text, RGB(0, 0, 156), false, false, 10);
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

void CDatabaseItemGenerateView::InsertText(CString text, COLORREF color, bool bold, bool italic, INT size)
{
	CHARRANGE cr;
    CHARFORMAT cf = {0};
    LONG txtLen = 0;
	LONG endLen = 0;

	try
	{
		txtLen = m_txtInformation.GetTextLength();
		
		cf.cbSize = sizeof(cf);
		cf.dwMask = CFM_BOLD  | CFM_ITALIC | CFM_COLOR | CFM_SIZE;
		cf.dwEffects = (bold ? CFE_BOLD : 0) | (italic ? CFE_ITALIC : 0);
		cf.crTextColor = color;		
		cf.yHeight = size * 18;

		cr.cpMin = txtLen;
		cr.cpMax = txtLen;

		m_txtInformation.SetSel(cr); // Set the cursor to the end of the text area and deselect everything.
		m_txtInformation.SetSelectionCharFormat(cf);
		m_txtInformation.ReplaceSel(text); // Inserts when nothing is selected.
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
#pragma endregion PRIVATE_METHODS
