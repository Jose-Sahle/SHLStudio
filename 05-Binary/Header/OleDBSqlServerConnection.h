/*****************************************************************************
 * Arquivo: OleDBSqlServerConnection                                         *
 *                                                                           *
 * Classe para conex�o com banco de dados SQL Server encapsulando OLE DB.    *
 *                                                                           *
 * Data:05/05/2013                                                           *
 * Auto: Jos� Sahle Netto                                                    *
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


