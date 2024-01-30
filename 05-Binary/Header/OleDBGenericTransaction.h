/*****************************************************************************
 * Arquivo: OleDBGenericTransaction                                          *
 *                                                                           *
 * Classe para transações do banco de dados genérica encapsulando OLE DB.    *
 *                                                                           *
 * Data:22/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
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

