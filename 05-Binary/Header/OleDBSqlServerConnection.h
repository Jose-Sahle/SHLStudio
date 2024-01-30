/*****************************************************************************
 * Arquivo: OleDBSqlServerConnection                                         *
 *                                                                           *
 * Classe para conexão com banco de dados SQL Server encapsulando OLE DB.    *
 *                                                                           *
 * Data:05/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbconnection.h"
#include "OleDBSqlServerCommand.h"
#include "OleDBSqlServerTransaction.h"
#include "Property.h"

class COleDBSqlServerConnection : public ISHLOleDBConnection
{
public:
	COleDBSqlServerConnection();
	~COleDBSqlServerConnection();

	virtual bool Open();
	virtual bool Close();
	virtual ISHLOleDBTransaction* BeginTransaction();
	virtual bool ChangeDatabase(CString database);
	virtual ISHLOleDBCommand* CreateCommand();

	virtual CString Version() { return _T("1.0.0.0"); }
};


