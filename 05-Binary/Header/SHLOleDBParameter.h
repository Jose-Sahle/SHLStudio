/*****************************************************************************
 * Arquivo: SHLOleDBParameter                                                *
 *                                                                           *
 * Classe para gerenciar um parâmetro para uma procedure ou function         *
 * do Ole DB                                                                 *
 *                                                                           *
 * Data:04/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include "ShlDBType.h"
#include "ShlDirection.h"

#include "Property.h"

class SHLOleDBParameter
{
public:
	SHLOleDBParameter();
	virtual ~SHLOleDBParameter();

public:
	friend class SHLOleDBParameters;
	friend class ISHLOleDBCommand;

	CString GetValueToString();

	//Properties
public:
	PROPERTY(SHLDBTYPE, DBType)
	GET(DBType)
	{
		return m_shldbtype;
	}
	SET(DBType)
	{
		m_shldbtype = value;
	}

	PROPERTY(SHLDIRECTION, Direction)
	GET(Direction)
	{
		return m_shldirection;
	}
	SET(Direction)
	{
		m_shldirection = value;
	}

	PROPERTY(bool, IsNullable)
	GET(IsNullable)
	{
		return m_isnullable;
	}
	SET(IsNullable)
	{
		m_isnullable = value;
	}

	PROPERTY(CString, ParameterName)
	GET(ParameterName)
	{
		return m_parametername;
	}
	SET(ParameterName)
	{
		m_parametername = value;
	}

	PROPERTY(VARIANT&, Value)
	GET(Value)
	{
		return m_value;
	}
	SET(Value)
	{
		m_value = value;
	}

	PROPERTY(UINT, Size)
	GET(Size)
	{
		return m_size;
	}
	SET(Size)
	{
		m_size = value;
	}

protected:
	bool				m_isnullable;
	UINT				m_size;
	CString				m_parametername;
	VARIANT				m_value;
	SHLDBTYPE			m_shldbtype;
	SHLDIRECTION		m_shldirection;
};
