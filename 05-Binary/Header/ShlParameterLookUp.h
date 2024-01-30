/*****************************************************************************
 * Arquivo: SHLOleDBProvider                                                 *
 *                                                                           *
 * Estrutura indicada para determinar como os par�metros ser�o procurado     *
 * quando lig�-los � lista de argumentos das procedures e fun�oes.           *
 * Isso � necess�rio devido ao PostGre n�o usar nomes de vari�vies nos       *
 * argumentos de fun��es.
 *                                                                           *
 * Data:19/05/2013                                                           *
 * Auto: Jos� Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

typedef enum _shlparameterlookup
{
	SHLPARAMETERLOOKUP_POSITION,
	SHLPARAMETERLOOKUP_NAME,
	SHLPARAMETERLOOKUP_LENGTH
} SHLPARAMETERLOOKUP;
