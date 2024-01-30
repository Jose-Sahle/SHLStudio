/*****************************************************************************
 * Arquivo: OleDBSqlServerTransaction                                        *
 *                                                                           *
 * Classe para transação do banco de dados SQL Server encapsulando OLE DB.   *
 *                                                                           *
 * Data:05/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbtransaction.h"

class COleDBSqlServerTransaction : public ISHLOleDBTransaction
{
public:
	COleDBSqlServerTransaction();
	~COleDBSqlServerTransaction();

	virtual CString Version() { return _T("1.0.0.0"); }
};

