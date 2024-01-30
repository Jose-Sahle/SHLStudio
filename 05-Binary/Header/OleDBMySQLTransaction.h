/*****************************************************************************
 * Arquivo: OleDBMySQLTransaction                                            *
 *                                                                           *
 * Classe para transação do banco de dados MySQL encapsulando OLE DB.        *
 *                                                                           *
 * Data:17/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbtransaction.h"

class COleDBMySQLTransaction : public ISHLOleDBTransaction
{
public:
	COleDBMySQLTransaction();
	~COleDBMySQLTransaction();

	virtual CString Version() { return _T("1.0.0.0"); }
};

