/*****************************************************************************
 * Arquivo: OleDBOracleCommand                                               *
 *                                                                           *
 * Classe para comandos do banco de dados Oracle encapsulando OLE DB.        *
 *                                                                           *
 * Data:18/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "ishloledbcommand.h"
#include "SHLOleDBReader.h"

class COleDBOracleCommand : public ISHLOleDBCommand
{
public:
	COleDBOracleCommand(void);
	~COleDBOracleCommand();

	friend class COleDBOracleConnection;

	virtual CString Version() { return _T("1.0.0.0"); }

protected:
	//virtual SHLOleDBReader* ExecuteReaderCommandText();
	//virtual SHLOleDBReader* FillReader(CCommand<CManualAccessor>* cmd);
	//bool FillReaderFromRowSet(SHLOleDBTable*& table, CCommand<CManualAccessor>* rs, SHLBINDVALUE*& pBind);
};

