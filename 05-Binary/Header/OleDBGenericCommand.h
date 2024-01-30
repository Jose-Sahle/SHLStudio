/*****************************************************************************
 * Arquivo: OleDBGenericCommand                                              *
 *                                                                           *
 * Classe para comandos do banco de dados genérica encapsulando OLE DB.      *
 *                                                                           *
 * Data:22/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbcommand.h"
#include "SHLOleDBReader.h"

class COleDBGenericCommand : public ISHLOleDBCommand
{
public:
	COleDBGenericCommand(void);
	~COleDBGenericCommand();

	virtual CString Version() { return _T("1.0.0.0"); }
};

