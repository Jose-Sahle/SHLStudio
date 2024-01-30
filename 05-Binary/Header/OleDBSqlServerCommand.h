/*****************************************************************************
 * Arquivo: OleDBSqlServerCommand                                            *
 *                                                                           *
 * Classe para comandos do banco de dados SQL Server encapsulando OLE DB.    *
 *                                                                           *
 * Data:05/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbcommand.h"
#include "SHLOleDBReader.h"

class COleDBSqlServerCommand : public ISHLOleDBCommand
{
public:
	COleDBSqlServerCommand(void);
	~COleDBSqlServerCommand();

	virtual CString Version() { return _T("1.0.0.0"); }
};

