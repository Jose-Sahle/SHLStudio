/*****************************************************************************
 * Arquivo: OleDBPostGreSQLConnection                                        *
 *                                                                           *
 * Classe para conexão com banco de dados PostGreSQL encapsulando OLE DB.    *
 *                                                                           *
 * Data:18/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbconnection.h"
#include "OleDBPostGreSQLCommand.h"
#include "OleDBPostGreSQLTransaction.h"
#include "Property.h"

class COleDBPostGreSQLConnection : public ISHLOleDBConnection
{
public:
	COleDBPostGreSQLConnection();
	~COleDBPostGreSQLConnection();

	virtual bool Open();
	virtual bool Close();
	virtual ISHLOleDBTransaction* BeginTransaction();
	virtual bool ChangeDatabase(CString database);
	virtual ISHLOleDBCommand* CreateCommand();

	virtual CString Version() { return _T("1.0.0.0"); }
};
