/*****************************************************************************
 * Arquivo: OleDBPostGreSQLTransaction                                       *
 *                                                                           *
 * Classe para transa��es do banco de dados PostGreSQL encapsulando OLE DB.  *
 *                                                                           *
 * Data:18/05/2013                                                           *
 * Auto: Jos� Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbtransaction.h"

class COleDBPostGreSQLTransaction : public ISHLOleDBTransaction
{
public:
	COleDBPostGreSQLTransaction();
	~COleDBPostGreSQLTransaction();

	virtual CString Version() { return _T("1.0.0.0"); }
};

