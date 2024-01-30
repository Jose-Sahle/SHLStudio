/*****************************************************************************
 * Arquivo: OleDBMySQLTransaction                                            *
 *                                                                           *
 * Classe para transa��o do banco de dados MySQL encapsulando OLE DB.        *
 *                                                                           *
 * Data:17/05/2013                                                           *
 * Auto: Jos� Sahle Netto                                                    *
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

