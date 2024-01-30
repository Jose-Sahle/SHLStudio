/*****************************************************************************
* Arquivo: SHLDBTable                                                        *
*                                                                            *
* Representa as tables de um banco de dados.                                 *
*                                                                            *
* Data:06/09/2014                                                            *
* Auto: José Sahle Netto                                                     *
******************************************************************************/
#pragma once

#include "stdafx.h"
#define MAX_SHLTABLENAME_SIZE 256

typedef struct _shldbtable
{
	_shldbcolumn()
	{
		memset(this, 0, sizeof(*this));
	}

	UINT			nOrdinal;
	TCHAR			szTableName[MAX_SHLTABLENAME_SIZE];
	SHLDBTYPE		DBType;
	UINT			nSize;
	bool			IsNullable;
	UINT			nNumericPrecision;
	BYTE			bScale;
	TCHAR			szCOLUMID[40];
} SHLDBTABLE;