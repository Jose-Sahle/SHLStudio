/*****************************************************************************
 * Arquivo: SHLOleDBReader                                                   *
 *                                                                           *
 * Classe que receberá os dados dos bancos - Tables/Rows/Columns             *
 *                                                                           *
 * Data:06/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <atlcoll.h>
#include <atldbcli.h>
#include "GUID.h"
#include "Property.h"
#include "ShlCollection.h"
#include "SHLOleDBTable.h"

class SHLOleDBReader
{
public:
	SHLOleDBReader();
	virtual ~SHLOleDBReader();

	friend class ISHLOleDBCommand;

	// Properties
public:
 	READONLY_PROPERTY(bool, IsClosed);
  	GET(IsClosed) 
 	{ 
 		return m_isclosed; 
	}

 	READONLY_PROPERTY(INT, RecordsAffected);
  	GET(RecordsAffected) 
 	{ 
 		return m_recordsaffected; 
	}

	READONLY_PROPERTY(CSHLList<SHLOleDBTable>&, Tables);
  	GET(Tables) 
 	{ 
 		return m_tables; 
	}

 	READONLY_PROPERTY(bool, HasTables);
  	GET(HasTables) 
 	{ 
 		return m_tables.GetCount() > 0; 
	}

 	READONLY_PROPERTY(UINT, TablesCount);
  	GET(TablesCount) 
 	{ 
 		return m_tables.GetCount(); 
	}
protected:
	bool														m_isclosed;
	INT															m_recordsaffected;
	CSHLList<SHLOleDBTable>										m_tables;
	CCommand<CManualAccessor, CRowset, CMultipleResults>*		m_cmd;

};