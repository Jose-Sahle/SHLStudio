/*****************************************************************************
 * Arquivo: ISHLOleDBConnection                                              *
 *                                                                           *
 * Classe abstrata para conexão com banco de dados encapsulando OLE DB.      *
 *                                                                           *
 * Data:04/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include "ISHLOleDBTransaction.h"
#include "ISHLOleDBCommand.h"
#include "ISHLOleDBConnection.h"
#include "shlconnectionstate.h"
#include "ShlOleDBProvider.h"
#include "ShlCollection.h"
#include "Property.h"

class ISHLOleDBConnection
{
public:
	ISHLOleDBConnection();
	virtual ~ISHLOleDBConnection();

	friend class ISHLOleDBCommand;
	friend class ISHLOleDBTransaction;

	virtual bool Open() = 0;
	virtual bool Close();
	virtual 
	virtual ISHLOleDBTransaction* BeginTransaction() = 0;
	virtual ISHLOleDBCommand* CreateCommand() = 0;
	virtual bool ChangeDatabase(CString database);
	virtual void RetrieveConnectionInformation();
	virtual void ResetConnectionInformation();
	virtual SHLOleDBReader* RetriveInformationSchema();
	virtual CSHLList<SHLDBCOLUMN>* RetriveInformationSchemaColumns(CString tablename);

	virtual CString Version() = 0;

protected:
	virtual bool Open(HWND handle);
	virtual bool Open(CString connectionstring);
	virtual bool Open(CString provider, CDBPropSet* rgPropertySet);
	virtual void SetError();
	virtual SHLDBTYPE GetSHLDBType(DBTYPE dbtype);

	//Properties
public:
	PROPERTY(CString, ConnectionString)
	GET(ConnectionString)
	{
		return m_connectionstring;
	}
	SET(ConnectionString)
	{
		m_connectionstring = value;
	}

	READONLY_PROPERTY(CString, ProviderName)
	GET(ProviderName)
	{
		return m_providername;
	}

	READONLY_PROPERTY(CString, DBMSName)
	GET(DBMSName)
	{
		return m_dbmsname;
	}

	PROPERTY(CString, Server)
	GET(Server)
	{
		return m_server;
	}
	SET(Server)
	{
		m_server = value;
	}

	PROPERTY(CString, DataSource)
	GET(DataSource)
	{
		return m_datasource;
	}
	SET(DataSource)
	{
		m_datasource = value;
	}

	PROPERTY(CString, Username)
	GET(Username)
	{
		return m_username;
	}
	SET(Username)
	{
		m_username = value;
	}

	PROPERTY(CString, Password)
	GET(Password)
	{
		return m_password;
	}
	SET(Password)
	{
		m_password = value;
	}

	PROPERTY(UINT, ConnectionTimeout)
	GET(ConnectionTimeout)
	{
		return m_connectiontimeout;
	}
	SET(ConnectionTimeout)
	{
		m_connectiontimeout = value;
	}

	PROPERTY(CString, Database)
	GET(Database)
	{
		return m_database;
	}
	SET(Database)
	{
		m_database = value;
	}

	READONLY_PROPERTY(CString, ServerVersion)
	GET(ServerVersion)
	{
		return m_serverversion;
	}

	READONLY_PROPERTY(SHLCONNECTIONSTATE, ConnectionState)
	GET(ConnectionState)
	{
		return m_connectionstate;
	}

	PROPERTY(SHLOLEDBPROVIDER, Provider)
	GET(Provider)
	{
		return m_provider;
	}
	SET(Provider)
	{
		m_provider = value;
	}

	READONLY_PROPERTY(CString, ErrorMessage)
	GET(ErrorMessage)
	{
		return m_errormessage;
	}

	READONLY_PROPERTY(bool, HasErrors)
	GET(HasErrors)
	{
		return m_haserror;
	}

protected:	
	CString					m_connectionstring;
	CString					m_providername;
	CString					m_dbmsname;
	CString					m_server;
	LONG					m_connectiontimeout;
	CString					m_database;
	CString					m_serverversion;
	CString					m_datasource;
	CString					m_username;
	CString					m_password;
	SHLCONNECTIONSTATE		m_connectionstate;
	CDataSource				m_connection;
	CSession*				m_session;
	SHLOLEDBPROVIDER		m_provider;
	CString					m_errormessage;
	bool					m_haserror;
};