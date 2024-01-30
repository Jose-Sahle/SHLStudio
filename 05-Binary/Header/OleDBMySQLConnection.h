/*****************************************************************************
 * Arquivo: OleDBMySQLConnection                                             *
 *                                                                           *
 * Classe para conexão com banco de dados MySQL encapsulando OLE DB.         *
 *                                                                           *
 * Data:17/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbconnection.h"
#include "OleDBMySQLCommand.h"
#include "OleDBMySQLTransaction.h"
#include "Property.h"

class COleDBMySQLConnection : public ISHLOleDBConnection
{
public:
	COleDBMySQLConnection();
	~COleDBMySQLConnection();

	virtual bool Open();
	virtual bool Close();
	virtual ISHLOleDBTransaction* BeginTransaction();
	virtual bool ChangeDatabase(CString value);
	virtual ISHLOleDBCommand* CreateCommand();

	virtual CString Version() { return _T("1.0.0.0"); }
};
