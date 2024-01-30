/*****************************************************************************
 * Arquivo: SHLOleDBParameters                                               *
 *                                                                           *
 * Classe para gerenciar os parâmetros para uma procedure ou function        *
 * do Ole DB                                                                 *
 *                                                                           *
 * Data:04/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include "Property.h"
#include "SHLOleDBParameter.h"
#include "shlparameterlookup.h"
#include "ShlCollection.h"

class SHLOleDBParameters
{
public:
	SHLOleDBParameters();
	virtual ~SHLOleDBParameters();

	friend class ISHLOleDBCommand;

	int Add(SHLOleDBParameter* parameter);
	int Add(CString parametername, SHLDBTYPE dbtype);
	int Add(CString parametername, SHLDBTYPE dbtype, UINT size);

	SHLOleDBParameter* operator[](CString name);
	SHLOleDBParameter* operator[](const INT& index);

	int GetCount();
	int GetInputCount();
	int GetReturnValue();

public:
	PROPERTY(CSHLList<SHLOleDBParameter>&, Parameters)
	GET(Parameters)
	{
		return m_parameters;
	}
	SET(Parameters)
	{
		m_parameters = value;
	}
	
	PROPERTY(SHLPARAMETERLOOKUP, Lookup)
	GET(Lookup)
	{
		return m_parameterlookup;
	}
	SET(Lookup)
	{
		m_parameterlookup = value;
	}
protected:
	CSHLList<SHLOleDBParameter>			m_parameters;
	int									m_inputcount;
	int									m_returncount;
	SHLPARAMETERLOOKUP					m_parameterlookup;
};