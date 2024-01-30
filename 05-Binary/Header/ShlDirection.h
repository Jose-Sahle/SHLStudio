/*****************************************************************************
 * Arquivo: SHLDBDirectoin                                                   *
 *                                                                           *
 * Estrutura para configurar a dire��o dos par�metros enviados e retornado   *
 * de procedures e fun��es                                                   *
 *                                                                           *
 * Data:04/05/2013                                                           *
 * Auto: Jos� Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

typedef enum _shldirection
{
	SHLDirection_Input,
	SHLDirection_Output,
	SHLDirection_InputOutput,
	SHLDirection_ReturnValue,
	SHLDirection_LENGTH
} SHLDIRECTION;
