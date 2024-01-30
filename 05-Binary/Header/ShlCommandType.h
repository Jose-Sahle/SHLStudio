/*****************************************************************************
 * Arquivo: SHLBind                                                          *
 *                                                                           *
 * Estrutura para configurar o ISHLOleDBCommand.                             *
 *                                                                           *
 * Data:04/05/2013                                                           *
 * Auto: Jos� Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

typedef enum _shlcommandtype
{
	Commandtype_Text,
	Commandtype_StoredProcedure,
	Commandtype_TableDirect,
	Commandtype_LENGTH
} SHLCOMMANDTYPE;
