/*****************************************************************************
 * Arquivo: OleDBGenericTransaction                                          *
 *                                                                           *
 * Classe para transa��es do banco de dados gen�rica encapsulando OLE DB.    *
 *                                                                           *
 * Data:22/05/2013                                                           *
 * Auto: Jos� Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbtransaction.h"

class COleDBGenericTransaction : public ISHLOleDBTransaction
{
public:
	COleDBGenericTransaction();
	~COleDBGenericTransaction();

	virtual CString Version() { return _T("1.0.0.0"); }
};

