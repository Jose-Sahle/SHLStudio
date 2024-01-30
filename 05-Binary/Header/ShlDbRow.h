/*****************************************************************************
 * Arquivo: SHLDBRow                                                         *
 *                                                                           *
 * Representa as linhas dos dados retornados do OleDB.                       *
 *                                                                           *
 * Data:09/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

#include "stdafx.h"
#include "ShlDbType.h"
#include "ShlBind.h"

typedef struct _shldbrow
{
	_shldbrow()
	{
		value = NULL;
	}

	~_shldbrow()
	{
		if(value != NULL)
		{
			delete[] value;
			value = NULL;
		}
	}

	SHLBINDVALUE*	value;
} SHLDBROW;