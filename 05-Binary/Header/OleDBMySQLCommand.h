/*****************************************************************************
 * Arquivo: OleDBMySQLCommand                                                *
 *                                                                           *
 * Classe para comandos do banco de dados MySQL encapsulando OLE DB.         *
 *                                                                           *
 * Data:17/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbcommand.h"
#include "SHLOleDBReader.h"

class COleDBMySQLCommand : public ISHLOleDBCommand
{
public:
	COleDBMySQLCommand(void);
	~COleDBMySQLCommand();

	virtual CString Version() { return _T("1.0.0.0"); }
};

