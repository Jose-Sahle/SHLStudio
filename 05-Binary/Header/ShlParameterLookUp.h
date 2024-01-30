/*****************************************************************************
 * Arquivo: SHLOleDBProvider                                                 *
 *                                                                           *
 * Estrutura indicada para determinar como os parâmetros serão procurado     *
 * quando ligá-los à lista de argumentos das procedures e funçoes.           *
 * Isso é necessário devido ao PostGre não usar nomes de variávies nos       *
 * argumentos de funções.
 *                                                                           *
 * Data:19/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

typedef enum _shlparameterlookup
{
	SHLPARAMETERLOOKUP_POSITION,
	SHLPARAMETERLOOKUP_NAME,
	SHLPARAMETERLOOKUP_LENGTH
} SHLPARAMETERLOOKUP;
