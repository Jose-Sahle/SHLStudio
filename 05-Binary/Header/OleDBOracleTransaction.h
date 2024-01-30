/*****************************************************************************
 * Arquivo: OleDBOracleTransaction                                           *
 *                                                                           *
 * Classe para transa��es do banco de dados Oracle encapsulando OLE DB.        *
 *                                                                           *
 * Data:18/05/2013                                                           *
 * Auto: Jos� Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbtransaction.h"

class COleDBOracleTransaction : public ISHLOleDBTransaction	  
{
public:
	COleDBOracleTransaction();
	~COleDBOracleTransaction();

	friend class COleDBOracleConnection;

	virtual CString Version() { return _T("1.0.0.0"); }
};
