/*****************************************************************************
 * Arquivo: OleDBGenericConnection                                           *
 *                                                                           *
 * Classe para conex�o com banco de dados gen�rica encapsulando OLE DB.      *
 *                                                                           *
 * Data:22/05/2013                                                           *
 * Auto: Jos� Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbconnection.h"
#include "OleDBGenericCommand.h"
#include "OleDBGenericTransaction.h"
#include "Property.h"

class COleDBGenericConnection : public ISHLOleDBConnection
{
public:
	COleDBGenericConnection();
	~COleDBGenericConnection();

	virtual bool Open();
	virtual bool Close();
	virtual ISHLOleDBTransaction* BeginTransaction();
	virtual bool ChangeDatabase(CString database);
	virtual ISHLOleDBCommand* CreateCommand();

	virtual CString Version() { return _T("1.0.0.0"); }
};
