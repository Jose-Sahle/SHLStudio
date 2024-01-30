/*****************************************************************************
 * Arquivo: OleDBOracleConnection                                            *
 *                                                                           *
 * Classe para conexão com banco de dados Oracle encapsulando OLE DB.        *
 *                                                                           *
 * Data:18/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbconnection.h"
#include "OleDBOracleCommand.h"
#include "OleDBOracleTransaction.h"
#include "Property.h"

class COleDBOracleConnection : public ISHLOleDBConnection
{
public:
	COleDBOracleConnection();
	~COleDBOracleConnection();

	friend class COleDBOracleCommand;
	friend class COleDBOracleTransaction;

	virtual bool Open();
	virtual bool Close();
	virtual ISHLOleDBTransaction* BeginTransaction();
	virtual ISHLOleDBCommand* CreateCommand();
	virtual bool ChangeDatabase(CString database);

	virtual CString Version() { return _T("1.0.0.0"); }

private:
	CSession* GetSession();
};
