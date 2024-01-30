/*****************************************************************************
 * Arquivo: OleDBPostGreSQLCommand                                           *
 *                                                                           *
 * Classe para commandos do banco de dados PostGreSQL encapsulando OLE DB.   *
 *                                                                           *
 * Data:18/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbcommand.h"
#include "SHLOleDBReader.h"

class COleDBPostGreSQLCommand : public ISHLOleDBCommand
{
public:
	COleDBPostGreSQLCommand(void);
	~COleDBPostGreSQLCommand();

	virtual CString Version() { return _T("1.0.0.0"); }
};
