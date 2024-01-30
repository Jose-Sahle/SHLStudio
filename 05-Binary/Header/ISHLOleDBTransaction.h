/*****************************************************************************
 * Arquivo: ISHLOleDBTransaction                                             *
 *                                                                           *
 * Classe abstrata para transação de dados encapsulando OLE DB.              *
 *                                                                           *
 * Data:04/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <atldbcli.h>
#include "ISHLOleDBConnection.h"
#include "Property.h"

class ISHLOleDBTransaction
{
public:
	ISHLOleDBTransaction();
	virtual ~ISHLOleDBTransaction();

	friend class ISHLOleDBConnection;

	virtual bool Begin();
	virtual bool Commit();
	virtual bool Rollback();

	virtual CString Version() = 0;

	//Properties
public:	
	PROPERTY(ISHLOleDBConnection*, Connection)
	GET(Connection)
	{
		return m_connection;
	}
	SET(Connection)
	{
		m_connection = value;
	}
	
protected:
	ISHLOleDBConnection*	m_connection;	
};