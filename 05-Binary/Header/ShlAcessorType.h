/*****************************************************************************
 * Arquivo: SHLAccessorType                                                  *
 *                                                                           *
 * Tipo de Accessor do Ole DB.                                               *
 *                                                                           *
 * Data:06/05/2013                                                           *
 * Auto: Jos� Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

typedef enum _shlaccessortype
{
	SHLACCESSORTYPE_DYNAMIC,
	SHLACCESSORTYPE_STRING,
	SHLACCESSORTYPE_XML,
	SHLACCESSORTYPE_DYNAMICPARAMETER,
	SHLACCESSORTYPE_DIRECTTABLE
} SHLACCESSORTYPE;
