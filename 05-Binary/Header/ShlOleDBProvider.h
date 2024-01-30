/*****************************************************************************
 * Arquivo: SHLOleDBProvider                                                 *
 *                                                                           *
 * Estrutura que encapsula os vários tipos de Provider de conexão que serão  *
 * usados nas classes ...Connection                                          *
 *                                                                           *
 * Data:19/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

typedef enum _shloledbprovider
{
	SHL_PROVIDER_GENERIC,
	SHL_PROVIDER_CONNECTIONSTRING,

	SHL_MSODBC_PROVIDER_MSDASQL,
	SHL_MSODBC_PROVIDER_MSDASQL_1,

	SHL_SQLSERVER_PROVIDER_SQLNCLI10,
	SHL_SQLSERVER_PROVIDER_SQLOLEDB_1,
	SHL_SQLSERVER_PROVIDER_SQLOLEDB,

	SHL_MYSQL_PROVIDER_MYSQLPROV,

	SHL_ORACLE_PROVIDER_MSDAORA_EXPRESS,
	SHL_ORACLE_PROVIDER_MSDAORA,
	SHL_ORACLE_PROVIDER_ORAOLEDB_EXPRESS,
	SHL_ORACLE_PROVIDER_ORAOLEDB_ORACLE,

	SHL_POSTGRESQL_PROVIDER_PGNP,

	SHLOLEDBPROVIDER_LENGTH
} SHLOLEDBPROVIDER;
