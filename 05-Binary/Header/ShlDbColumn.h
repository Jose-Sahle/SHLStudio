/*****************************************************************************
 * Arquivo: SHLDBColumn                                                      *
 *                                                                           *
 * Representa as colunas dos dados retornados do OleDB.                      *
 *                                                                           *
 * Data:09/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "stdafx.h"
#include "ShlDbType.h"

#define MAX_SHLCOLUMN_SIZE 256

typedef struct _shldbcolumn
{
	_shldbcolumn()
	{
		memset(this, 0, sizeof(*this));
	}

	UINT			nOrdinal;
	TCHAR			szColumName[MAX_SHLCOLUMN_SIZE];
	SHLDBTYPE		DBType;
	UINT			nSize;
	bool			IsNullable;
	bool			IsPrimaryKey;
	bool			IsIdentity;
	UINT			nNumericPrecision;	
	BYTE			bScale;
	TCHAR			szCOLUMID[40];
} SHLDBCOLUMN;