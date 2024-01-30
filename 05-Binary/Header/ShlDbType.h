/*****************************************************************************
 * Arquivo: SHLDBType                                                        *
 *                                                                           *
 * Estrutura para gerenciar os tipos de dados enviados e retornados          *
 * nas classes ISHLOleDB.                                                    *
 *                                                                           *
 * Data:04/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

typedef enum _shldbtype
{
	SHLDBType_Empty,
	SHLDBType_Null,
	SHLDBType_Idispatch,
	SHLDBType_Error,
	SHLDBType_Unknown,
	SHLDBType_Variant,
	SHLDBType_AnsiString,
	SHLDBType_BAnsiString,
	SHLDBType_Binary,
	SHLDBType_Byte,
	SHLDBType_Boolean,
	SHLDBType_Currency,
	SHLDBType_Date,
	SHLDBType_Date2,
	SHLDBType_DateTime,
	SHLDBType_Decimal,
	SHLDBType_Double,
	SHLDBType_Guid,
	SHLDBType_Int16,
	SHLDBType_Int32,
	SHLDBType_Int64,
	SHLDBType_Object,
	SHLDBType_SByte,
	SHLDBType_Single,
	SHLDBType_String,
	SHLDBType_Time,
	SHLDBType_UInt16,
	SHLDBType_UInt32,
	SHLDBType_UInt64,
	SHLDBType_VarNumeric,
	SHLDBType_AnsiStringFixedLength,
	SHLDBType_StringFixedLength,
	SHLDBType_Xml,
	SHLDBType_DateTime2,
	SHLDBType_DateTimeOffset,
	SHLDBType__LENGTH
} SHLDBTYPE;
