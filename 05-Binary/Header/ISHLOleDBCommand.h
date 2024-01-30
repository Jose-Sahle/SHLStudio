/*****************************************************************************
 * Arquivo: ISHLOleDBCommand                                                 *
 *                                                                           *
 * Classe abstrata para comandos de dados encapsulando OLE DB.               *
 *                                                                           *
 * Data:04/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <atldbcli.h>
#include "SHLOleDBReader.h"
#include "SHLCommandType.h"
#include "SHLOleDBParameters.h"
#include "ISHLOleDBConnection.h"
#include "SHLBind.h"
#include "Property.h"
#include "ShlAcessorType.h"

class ISHLOleDBCommand
{
public:
	ISHLOleDBCommand();
	virtual ~ISHLOleDBCommand();

	friend class ISHLOleDBConnection;

public:
	virtual bool Close();

	virtual DBROWCOUNT ExecuteNonQuery(); 
	virtual SHLOleDBReader* ExecuteReader();

	virtual bool Cancel();
	virtual DBROWCOUNT ExecuteNonQueryAsync();

	virtual CString Version() = 0;

protected:
	virtual DBROWCOUNT ExecuteNonQueryCommandText();
	virtual DBROWCOUNT ExecuteNonQueryStoredProcedure();

	virtual SHLOleDBReader* ExecuteReaderCommandText();
	virtual SHLOleDBReader* ExecuteReaderStoredProcedure();

	virtual SHLOleDBReader* FillReader(CCommand<CManualAccessor, CRowset, CMultipleResults>* cmd);
	virtual bool FillReaderFromRowSet(SHLOleDBTable*& table, CRowset<CManualAccessor>* rs, SHLBINDVALUE*& pBind);

	virtual SHLDBTYPE GetSHLDBType(DBTYPE dbtype);
	virtual CString GetCallProc(CPtrArray& arrColInfo, CWordArray& arrType, ULONG& ulParams);
	virtual bool	SetParameters(CCommand<CManualAccessor>* cmd, CPtrArray& arrColInfo, CWordArray& arrType, ULONG& ulParams, SHLBINDINFO*& pParams);
	virtual void AddEntry(CCommand<CManualAccessor>* cmd, SHLBINDVALUE* pColumns, SHLDBCOLUMN*& dbColumn, INT nIndexColumn);
	virtual BSTR GetParamDataSourceType(SHLDBTYPE type);

	virtual void SetError();

	// Properties
public:	
	PROPERTY(CString, CommandText)
	GET(CommandText)
	{
		return m_commandtext;
	}
	SET(CommandText)
	{
		m_commandtext = value;
	}

	PROPERTY(INT, CommandTimeout)
	GET(CommandTimeout)
	{
		return m_commandtimeout;
	}
	SET(CommandTimeout)
	{
		m_commandtimeout = value;
	}

	PROPERTY(SHLCOMMANDTYPE, CommandType)
	GET(CommandType)
	{
		return m_commandtype;
	}
	SET(CommandType)
	{
		m_commandtype = value;
	}
	
	PROPERTY(ISHLOleDBConnection*, Connection)
	GET(Connection)
	{
		return m_connection;
	}
	SET(Connection)
	{
		m_connection = value;
	}
	
	PROPERTY(SHLOleDBParameters*, Parameters)
	GET(Parameters)
	{
		return m_parameters;
	}
	SET(Parameters)
	{
		m_parameters = value;
	}

	PROPERTY(SHLACCESSORTYPE, AccessorType)
	GET(AccessorType)
	{
		return m_acessortype;
	}
	SET(AccessorType)
	{
		m_acessortype = value;
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

	READONLY_PROPERTY(DBROWCOUNT, AffectedRows)
	GET(AffectedRows)
	{
		return m_affectedrows;
	}

protected:
	CString					m_callproc;
	CString					m_startquote;
	CString					m_endquote;
	CString					m_commandtext;
	INT						m_commandtimeout;
	SHLCOMMANDTYPE			m_commandtype;
	ISHLOleDBConnection*	m_connection;
	SHLOleDBParameters*		m_parameters;
	CString					m_errormessage;
	bool					m_haserror;
	DBROWCOUNT				m_affectedrows;
	SHLACCESSORTYPE			m_acessortype;
};
