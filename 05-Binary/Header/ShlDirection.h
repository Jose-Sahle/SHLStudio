/*****************************************************************************
 * Arquivo: SHLDBDirectoin                                                   *
 *                                                                           *
 * Estrutura para configurar a direção dos parâmetros enviados e retornado   *
 * de procedures e funções                                                   *
 *                                                                           *
 * Data:04/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
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
