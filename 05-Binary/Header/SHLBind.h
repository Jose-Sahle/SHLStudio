/*****************************************************************************
 * Arquivo: SHLBind                                                          *
 *                                                                           *
 * Estrutura que represeta o Bind de campos e parâmetros do OleDB.           *
 *                                                                           *
 * Data:08/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "stdafx.h"
#include "ShlDbType.h"

typedef enum _uniontype
{
	UNIONTYPE_TCHAR,
	UNIONTYPE_VARIANT,
	UNIONTYPE_POINTER,
	UNIONTYPE_LENGTH
}UNIONTYPE;

typedef struct _shlbindparaminfo
{
	_shlbindparaminfo()
	{
		memset(this, 0, sizeof(*this));
	}

	union tagData
	{
		TCHAR		szValue[40];
		VARIANT*	pvtValue;
	} Data;

	DWORD		dwStatus;
} SHLBINDINFO;

typedef struct _shlbindvalue
{
	_shlbindvalue()
	{
		memset(this, 0, sizeof(*this));
	}

	_shlbindvalue& operator=(const _shlbindvalue& right) 
	{
		if (this != &right) 
		{
			this->dwStatus  = right.dwStatus;
			this->ulLength	= right.ulLength;
			this->data		= right.data;
		}

		return *this;
    }

	union tagData
	{
        CY			cyVal;
        INT			intVal;
        UINT		uintVal;
        DATE		date;
		DBTIMESTAMP datetime;
        TCHAR		szVal[8000];
		CHAR		szArray[8000];
        TCHAR		cVal;
        BYTE		bVal;
		BOOL		bolVal;
        LONG		lVal;
		LONGLONG	llVal;
        SHORT		iVal;
        FLOAT		fltVal;
        DOUBLE		dblVal;
        ULONGLONG	ullVal;
        USHORT		uiVal;
        ULONG		ulVal;
		DECIMAL		decVal;
	} data;

	DWORD		dwStatus;
	ULONG		ulLength;
} SHLBINDVALUE;
