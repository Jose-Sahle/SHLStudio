/*****************************************************************************
 * Arquivo: SHLQueryDataConnection                                           *
 *                                                                           *
 * Classe que representa uma conexão a um determinado banco de dados.        *
 *                                                                           *
 * Data:29/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#ifndef __SHLQUERYDATACONNECTION

#define __SHLQUERYDATACONNECTION

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include "Property.h"
#include "ISHLOleDBConnection.h"

#include "OleDBGenericConnection.h"

typedef enum _shlquerydataconnectionstate
{
	 SHLQUERYDATACONNECTIONSTATE_NIL
	,SHLQUERYDATACONNECTIONSTATE_NEW
	,SHLQUERYDATACONNECTIONSTATE_UPDATE
	,SHLQUERYDATACONNECTIONSTATE_DELETE
} SHLQUERYDATACONNECTIONSTATE;

class CQueryDataConnectionEntity
{
public:
	CQueryDataConnectionEntity() { m_conn = NULL; Reset();}
	virtual ~CQueryDataConnectionEntity(){Reset();}

	virtual CQueryDataConnectionEntity& operator=(const CQueryDataConnectionEntity& other)
	{
		this->m_nidconexoes					= other.m_nidconexoes;
		this->m_nidbanco					= other.m_nidbanco;
		this->m_connectionname				= other.m_connectionname;
		this->m_connectionstring			= other.m_connectionstring;
		this->m_datasource					= other.m_datasource;
		this->m_defaultdatabase				= other.m_defaultdatabase;
		this->m_dbmsname					= other.m_dbmsname;
		this->m_drivename					= other.m_drivename;
		this->m_providername				= other.m_providername;
		this->m_userid						= other.m_userid;
		this->m_servername					= other.m_servername;

		this->m_selectuserdatabases			= other.m_selectuserdatabases;
		this->m_selectsysdatabases			= other.m_selectsysdatabases;
		this->m_selectusertables			= other.m_selectusertables;
		this->m_selectsystables				= other.m_selectsystables;
		this->m_selectusertablefields		= other.m_selectusertablefields;
		this->m_selectsystablefields		= other.m_selectsystablefields;
		this->m_selectuserviews				= other.m_selectuserviews;
		this->m_selectsysviews				= other.m_selectsysviews;
		this->m_selectviewcode				= other.m_selectviewcode;
		this->m_selectuserprocedures		= other.m_selectuserprocedures;
		this->m_selectsysprocedures			= other.m_selectsysprocedures;
		this->m_selectuserprocedurefields	= other.m_selectuserprocedurefields;
		this->m_selectsysprocedurefields	= other.m_selectsysprocedurefields;
		this->m_selectprocedurecode			= other.m_selectprocedurecode;
		this->m_selectuserfunctions			= other.m_selectuserfunctions;
		this->m_selectsysfunctions			= other.m_selectsysfunctions;
		this->m_selectuserfunctionfields	= other.m_selectuserfunctionfields;
		this->m_selectsysfunctionfields		= other.m_selectsysfunctionfields;
		this->m_selectfunctioncode			= other.m_selectfunctioncode;
		this->m_selectprimarykeys			= other.m_selectprimarykeys;
		this->m_selectprimarykeyfields		= other.m_selectprimarykeyfields;
		this->m_selectsysconstraints		= other.m_selectsysconstraints;
		this->m_selectsysconstraintsfields	= other.m_selectsysconstraintsfields;
		this->m_selectuserconstraints		= other.m_selectuserconstraints;
		this->m_selectuserconstraintsfields	= other.m_selectuserconstraintsfields;
		this->m_selectusersequences			= other.m_selectusersequences;
		this->m_selectsyssequences			= other.m_selectsyssequences;
		this->m_selectusersequencefields	= other.m_selectusersequencefields;
		this->m_selectsyssequencefields		= other.m_selectsyssequencefields;
		this->m_selectuserindexes			= other.m_selectuserindexes;
		this->m_selectsysindexes			= other.m_selectsysindexes;
		this->m_selectuserindexfields		= other.m_selectuserindexfields;
		this->m_selectsysindexfields		= other.m_selectsysindexfields;
		this->m_selectusertriggers			= other.m_selectusertriggers;
		this->m_selectsystriggers			= other.m_selectsystriggers;

		this->m_hitem						= other.m_hitem;
		this->m_state						= other.m_state;
		this->m_conn						= new COleDBGenericConnection();
		this->m_conn->ConnectionString		= other.m_conn->ConnectionString;
		this->m_conn->Provider				= SHLOLEDBPROVIDER::SHL_PROVIDER_CONNECTIONSTRING;
		this->m_conn->Open();

		return *this;
	}

protected:
	virtual void Reset()
	{
		m_nidconexoes			= -1;
		m_connectionname		= _T("");
		m_connectionstring		= _T("");
		m_datasource			= _T("");
		m_defaultdatabase		= _T("");
		m_dbmsname				= _T("");
		m_drivename				= _T("");
		m_providername			= _T("");
		m_userid				= _T("");
		m_servername			= _T("");
		m_hitem					= NULL;
		m_state					= SHLQUERYDATACONNECTIONSTATE_NIL;

		if(m_conn)
		{
			m_conn->Close();
			delete m_conn;
		}

		m_conn					= NULL;
	}

	// Properties
public:
	PROPERTY(ULONG, IDConnection)
	GET(IDConnection)
	{
		return m_nidconexoes;
	}
	SET(IDConnection)
	{
		m_nidconexoes = value;
	}

	PROPERTY(ULONG, IDBanco)
	GET(IDBanco)
	{
		return m_nidbanco;
	}
	SET(IDBanco)
	{
		m_nidbanco = value;
	}

	
	PROPERTY(CString, ConnectionName)
	GET(ConnectionName)
	{
		return m_connectionname;
	}
	SET(ConnectionName)
	{
		m_connectionname = value;
	}

	PROPERTY(CString, ConnectionString)
	GET(ConnectionString)
	{
		return m_connectionstring;
	}
	SET(ConnectionString)
	{
		m_connectionstring = value;
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

	PROPERTY(CString, DefaultDatabase)
	GET(DefaultDatabase)
	{
		return m_defaultdatabase;
	}
	SET(DefaultDatabase)
	{
		m_defaultdatabase = value;
	}

	PROPERTY(CString, DBMSName)
	GET(DBMSName)
	{
		return m_dbmsname;
	}
	SET(DBMSName)
	{
		m_dbmsname = value;
	}

	PROPERTY(CString, DriveName)
	GET(DriveName)
	{
		return m_drivename;
	}
	SET(DriveName)
	{
		m_drivename = value;
	}

	PROPERTY(CString, ProviderName)
	GET(ProviderName)
	{
		return m_providername;
	}
	SET(ProviderName)
	{
		m_providername = value;
	}

	PROPERTY(CString, UserID)
	GET(UserID)
	{
		return m_userid;
	}
	SET(UserID)
	{
		m_userid = value;
	}

	PROPERTY(CString, ServerName)
	GET(ServerName)
	{
		return m_servername;
	}
	SET(ServerName)
	{
		m_servername = value;
	}

	PROPERTY(HTREEITEM, TreeViewItem)
	GET(TreeViewItem)
	{
		return m_hitem;
	}
	SET(TreeViewItem)
	{
		m_hitem = value;
	}

	PROPERTY(SHLQUERYDATACONNECTIONSTATE, State)
	GET(State)
	{
		return m_state;
	}
	SET(State)
	{
		m_state = value;
	}

	PROPERTY(CString, SelectUserDatabases)
	GET(SelectUserDatabases)
	{
		return m_selectuserdatabases;
	}
	SET(SelectUserDatabases)
	{
		 m_selectuserdatabases = value;
	}

	PROPERTY(CString, SelectSysDatabases)
	GET(SelectSysDatabases)
	{
		return m_selectsysdatabases;
	}
	SET(SelectSysDatabases)
	{
		 m_selectsysdatabases = value;
	}

	PROPERTY(CString, SelectUserTables)
	GET(SelectUserTables)
	{
		return m_selectusertables;
	}
	SET(SelectUserTables)
	{
		 m_selectusertables = value;
	}

	PROPERTY(CString, SelectSysTables)
	GET(SelectSysTables)
	{
		return m_selectsystables;
	}
	SET(SelectSysTables)
	{
		 m_selectsystables = value;
	}

	PROPERTY(CString, SelectUserTableFields)
	GET(SelectUserTableFields)
	{
		return m_selectusertablefields;
	}
	SET(SelectUserTableFields)
	{
		 m_selectusertablefields = value;
	}

	PROPERTY(CString, SelectSysTablesFields)
	GET(SelectSysTablesFields)
	{
		return m_selectsystablefields;
	}
	SET(SelectSysTablesFields)
	{
		 m_selectsystablefields = value;
	}

	PROPERTY(CString, SelectUserViews)
	GET(SelectUserViews)
	{
		return m_selectuserviews;
	}
	SET(SelectUserViews)
	{
		 m_selectuserviews = value;
	}

	PROPERTY(CString, SelectSysViews)
	GET(SelectSysViews)
	{
		return m_selectsysviews;
	}
	SET(SelectSysViews)
	{
		 m_selectsysviews = value;
	}

	PROPERTY(CString, SelectViewCode)
	GET(SelectViewCode)
	{
		return m_selectviewcode;
	}
	SET(SelectViewCode)
	{
		 m_selectviewcode = value;
	}

	PROPERTY(CString, SelectUserProcedures)
	GET(SelectUserProcedures)
	{
		return m_selectuserprocedures;
	}
	SET(SelectUserProcedures)
	{
		 m_selectuserprocedures = value;
	}

	PROPERTY(CString, SelectSysProcedures)
	GET(SelectSysProcedures)
	{
		return m_selectsysprocedures;
	}
	SET(SelectSysProcedures)
	{
		 m_selectsysprocedures = value;
	}

	PROPERTY(CString, SelectUserProcedureFields)
	GET(SelectUserProcedureFields)
	{
		return m_selectuserprocedurefields;
	}
	SET(SelectUserProcedureFields)
	{
		 m_selectuserprocedurefields = value;
	}

	PROPERTY(CString, SelectSysProcedureFields)
	GET(SelectSysProcedureFields)
	{
		return m_selectsysprocedurefields;
	}
	SET(SelectSysProcedureFields)
	{
		 m_selectsysprocedurefields = value;
	}

	PROPERTY(CString, SelectProcedureCode)
	GET(SelectProcedureCode)
	{
		return m_selectprocedurecode;
	}
	SET(SelectProcedureCode)
	{
		 m_selectprocedurecode = value;
	}

	PROPERTY(CString, SelectUserFunctions)
	GET(SelectUserFunctions)
	{
		return m_selectuserfunctions;
	}
	SET(SelectUserFunctions)
	{
		 m_selectuserfunctions = value;
	}

	PROPERTY(CString, SelectSysFunctions)
	GET(SelectSysFunctions)
	{
		return m_selectsysfunctions;
	}
	SET(SelectSysFunctions)
	{
		 m_selectsysfunctions = value;
	}

	PROPERTY(CString, SelectUserFunctionFields)
	GET(SelectUserFunctionFields)
	{
		return m_selectuserfunctionfields;
	}
	SET(SelectUserFunctionFields)
	{
		 m_selectuserfunctionfields = value;
	}

	PROPERTY(CString, SelectSysFunctionFields)
	GET(SelectSysFunctionFields)
	{
		return m_selectsysfunctionfields;
	}
	SET(SelectSysFunctionFields)
	{
		 m_selectsysfunctionfields = value;
	}

	PROPERTY(CString, SelectFunctionCode)
	GET(SelectFunctionCode)
	{
		return m_selectfunctioncode;
	}
	SET(SelectFunctionCode)
	{
		 m_selectfunctioncode = value;
	}

	PROPERTY(CString, SelectPrimaryKeys)
	GET(SelectPrimaryKeys)
	{
		return m_selectprimarykeys;
	}
	SET(SelectPrimaryKeys)
	{
		 m_selectprimarykeys = value;
	}

	PROPERTY(CString, SelectPrimaryKeyFields)
	GET(SelectPrimaryKeyFields)
	{
		return m_selectprimarykeyfields;
	}
	SET(SelectPrimaryKeyFields)
	{
		 m_selectprimarykeyfields = value;
	}

	PROPERTY(CString, SelectSysConstraints)
	GET(SelectSysConstraints)
	{
		return m_selectsysconstraints;
	}
	SET(SelectSysConstraints)
	{
		 m_selectsysconstraints = value;
	}

	PROPERTY(CString, SelectSysConstraintFields)
	GET(SelectSysConstraintFields)
	{
		return m_selectsysconstraintsfields;
	}
	SET(SelectSysConstraintFields)
	{
		 m_selectsysconstraintsfields = value;
	}

	PROPERTY(CString, SelectUserConstraints)
	GET(SelectUserConstraints)
	{
		return m_selectuserconstraints;
	}
	SET(SelectUserConstraints)
	{
		 m_selectuserconstraints = value;
	}

	PROPERTY(CString, SelectUserConstraintFields)
	GET(SelectUserConstraintFields)
	{
		return m_selectuserconstraintsfields;
	}
	SET(SelectUserConstraintFields)
	{
		 m_selectuserconstraintsfields = value;
	}

	PROPERTY(CString, SelectUserSequences)
	GET(SelectUserSequences)
	{
		return m_selectusersequences;
	}
	SET(SelectUserSequences)
	{
		 m_selectusersequences = value;
	}

	PROPERTY(CString, SelectSysSequences)
	GET(SelectSysSequences)
	{
		return m_selectsyssequences;
	}
	SET(SelectSysSequences)
	{
		 m_selectsyssequences = value;
	}

	PROPERTY(CString, SelectUserSequenceFields)
	GET(SelectUserSequenceFields)
	{
		return m_selectusersequencefields;
	}
	SET(SelectUserSequenceFields)
	{
		 m_selectusersequencefields = value;
	}

	PROPERTY(CString, SelectSysSequenceFields)
	GET(SelectSysSequenceFields)
	{
		return m_selectsyssequencefields;
	}
	SET(SelectSysSequenceFields)
	{
		 m_selectsyssequencefields = value;
	}

	PROPERTY(CString, SelectUserIndexes)
	GET(SelectUserIndexes)
	{
		return m_selectuserindexes;
	}
	SET(SelectUserIndexes)
	{
		 m_selectuserindexes = value;
	}

	PROPERTY(CString, SelectSysIndexes)
	GET(SelectSysIndexes)
	{
		return m_selectsysindexes;
	}
	SET(SelectSysIndexes)
	{
		 m_selectsysindexes = value;
	}

	PROPERTY(CString, SelectUserIndexFields)
	GET(SelectUserIndexFields)
	{
		return m_selectuserindexfields;
	}
	SET(SelectUserIndexFields)
	{
		 m_selectuserindexfields = value;
	}

	PROPERTY(CString, SelectSysIndexFields)
	GET(SelectSysIndexFields)
	{
		return m_selectsysindexfields;
	}
	SET(SelectSysIndexFields)
	{
		 m_selectsysindexfields = value;
	}

	PROPERTY(CString, SelectUserTriggers)
	GET(SelectUserTriggers)
	{
		return m_selectusertriggers;
	}
	SET(SelectUserTriggers)
	{
		 m_selectusertriggers = value;
	}

	PROPERTY(CString, SelectSysTriggers)
	GET(SelectSysTriggers)
	{
		return m_selectsystriggers;
	}
	SET(SelectSysTriggers)
	{
		 m_selectsystriggers = value;
	}

	PROPERTY(ISHLOleDBConnection*, Connection)
	GET(Connection)
	{
		return m_conn;
	}
	SET(Connection)
	{
		m_conn = value;
	}

	// Private Members
private:
	ULONG							m_nidconexoes;
	ULONG							m_nidbanco;
	CString							m_connectionname;
	CString							m_connectionstring;
	CString							m_datasource;
	CString							m_defaultdatabase;
	CString							m_dbmsname;
	CString							m_drivename;
	CString							m_providername;
	CString							m_userid;
	CString							m_servername;

	CString							m_selectuserdatabases;
	CString							m_selectsysdatabases;
	CString							m_selectusertables;
	CString							m_selectsystables;
	CString							m_selectusertablefields;
	CString							m_selectsystablefields;
	CString							m_selectuserviews;
	CString							m_selectsysviews;
	CString							m_selectviewcode;
	CString							m_selectuserprocedures;
	CString							m_selectsysprocedures;
	CString							m_selectuserprocedurefields;
	CString							m_selectsysprocedurefields;
	CString							m_selectprocedurecode;
	CString							m_selectuserfunctions;
	CString							m_selectsysfunctions;
	CString							m_selectuserfunctionfields;
	CString							m_selectsysfunctionfields;
	CString							m_selectfunctioncode;
	CString							m_selectprimarykeys;
	CString							m_selectprimarykeyfields;
	CString							m_selectsysconstraints;
	CString							m_selectsysconstraintsfields;
	CString							m_selectuserconstraints;
	CString							m_selectuserconstraintsfields;
	CString							m_selectusersequences;
	CString							m_selectsyssequences;
	CString							m_selectusersequencefields;
	CString							m_selectsyssequencefields;
	CString							m_selectuserindexes;
	CString							m_selectsysindexes;
	CString							m_selectuserindexfields;
	CString							m_selectsysindexfields;
	CString							m_selectusertriggers;
	CString							m_selectsystriggers;

	HTREEITEM						m_hitem;
	SHLQUERYDATACONNECTIONSTATE		m_state;
	ISHLOleDBConnection*			m_conn;
};

#endif