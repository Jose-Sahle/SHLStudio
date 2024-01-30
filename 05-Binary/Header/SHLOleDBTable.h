/*****************************************************************************
 * Arquivo: SHLOleDBTable                                                    *
 *                                                                           *
 * Classe que representa as Tables contendo Columns e Rows de um banco de    *
 * dados.                                                                    *
 *                                                                           *
 * Data:16/05/2013                                                           *
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
#include "ShlDbColumn.h"
#include "ShlDbRow.h"

class SHLOleDBTable
{
public:
	SHLOleDBTable();
	virtual ~SHLOleDBTable();

	friend class ISHLOleDBCommand;
	friend class SHLOleDBReader;

public:
	//Values
	virtual void			GetValue(int row, int column, bool* value);
	virtual void			GetValue(int row, int column, BYTE* value);
	virtual void			GetValue(int row, int column, TCHAR* value);
	virtual void			GetValue(int row, int column, CURRENCY* value);
	virtual void			GetValue(int row, int column, CTime* value);
	virtual void			GetValue(int row, int column, DOUBLE* value);
	virtual void			GetValue(int row, int column, FLOAT* value);
	virtual void			GetValue(int row, int column, DECIMAL* value);
	virtual void			GetValue(int row, int column, LONG* value);
	virtual void			GetValue(int row, int column, INT* value);
	virtual void			GetValue(int row, int column, CString* value);

	virtual bool			IsNull(int row, int column);
	virtual bool			GetBoolean(int row, int column);
	virtual BYTE			GetByte(int row, int column);
	virtual TCHAR			GetChar(int row, int column);
	virtual CURRENCY		GetCurrency(int row, int column);
	virtual CTime			GetDate(int row, int column);
	virtual CTime			GetTime(int row, int column);
	virtual CTime			GetDateTime(int row, int column);
	virtual CTime			GetDateTime2(int row, int column);
	virtual DOUBLE			GetDouble(int row, int column);
	virtual FLOAT			GetFloat(int row, int column);
	virtual DECIMAL			GetDecimal(int row, int column);
	virtual CGUID			GetGuid(int row, int column);
	virtual LONG			GetLong(int row, int column);
	virtual INT				GetInt(int row, int column);
	virtual CString			GetString(int row, int column);
	virtual CString			GetStringAnsi(int row, int column);
	virtual CString			GetXml(int row, int column);
	virtual CString			GetXml();
	virtual	VARIANT			GetValue(int row, int column);
	virtual CString			GetValueToString(int row, int column, CString nullvaluestring);

	//Columns
	virtual CString			GetColumnName(int column);
	virtual UINT			GetColumnOrdinal(CString name);
	virtual SHLDBTYPE 		GetColumnType(int column);
	virtual CString 		GetColumnTypeName(int column);
	virtual UINT 			GetColumnSize(int column);
	virtual UINT 			GetColumnPrecision(int column);
	virtual BYTE 			GetColumnScale(int column);
	virtual BOOL 			IsColumnNullable(int column);

	virtual void			AddColumn(SHLDBCOLUMN* column);
	virtual void			AddColumn(UINT nOrdinal, CString ColumnName, SHLDBTYPE DBType, UINT nSize, bool IsNullable);

	virtual BOOL MoveFirst();
	virtual BOOL MoveNext();

public:
 	READONLY_PROPERTY(INT, ColumnCount);
  	GET(ColumnCount) 
 	{ 
 		return m_columns.GetCount(); 
	}

 	READONLY_PROPERTY(bool, HasRows);
  	GET(HasRows) 
 	{ 
 		return m_rows.GetCount() > 0; 
	}

	READONLY_PROPERTY(CSHLList<SHLDBCOLUMN>&, Columns);
  	GET(Columns) 
 	{ 
 		return m_columns; 
	}

 	READONLY_PROPERTY(INT, RowsCount);
  	GET(RowsCount) 
 	{ 
		if (m_rowscount != 0)
			return m_rowscount;

 		return m_rows.GetCount(); 
	}

	READONLY_PROPERTY(CSHLList<SHLDBROW>&, Rows);
  	GET(Rows) 
 	{ 
		if (m_rowsvirtual.GetCount() > 0)
			return m_rowsvirtual;

 		return m_rows; 
	}

 	PROPERTY(CString, TableName);
  	GET(TableName) 
 	{ 
 		return m_tablename; 
	}
  	SET(TableName) 
 	{ 
 		m_tablename = value; 
	}

	PROPERTY(CString, Type);
	GET(Type)
	{
		return m_type;
	}
	SET(Type)
	{
		m_type = value;
	}

	PROPERTY(CString, Catalog);
	GET(Catalog)
	{
		return m_catalog;
	}
	SET(Catalog)
	{
		m_catalog = value;
	}

	PROPERTY(CString, Schema);
	GET(Schema)
	{
		return m_schema;
	}
	SET(Schema)
	{
		m_schema = value;
	}

	PROPERTY(CString, Description);
	GET(Description)
	{
		return m_description;
	}
	SET(Description)
	{
		m_description = value;
	}

protected:
	CString								m_tablename;
	CString								m_type;
	CString								m_catalog;
	CString								m_schema;
	CString								m_description;
	CSHLList<SHLDBCOLUMN>				m_columns;
	CSHLList<SHLDBROW>					m_rows;
	CSHLList<SHLDBROW>					m_rowsvirtual;
	CRowset<CManualAccessor>			m_rowset;
	SHLBINDVALUE*						m_bindcolumns;
	ULONG								m_rowscount;
	SHLOleDBReader*						m_parent;
	BOOL								m_directtable;
	ULONG								m_virtualindex;
	virtual void RecountRows();
	virtual void AddEntry(CCommand<CManualAccessor>* cmd, SHLBINDVALUE* pColumns, SHLDBCOLUMN*& dbColumn, INT nIndexColumn);

};
