/*****************************************************************************
 * Arquivo: SHLConnectionState                                               *
 *                                                                           *
 * Estado da conexão do ISHLOleDBConnection.                                 *
 *                                                                           *
 * Data:04/05/2013                                                           *
 * Auto: José Sahle Netto                                                    *
 *****************************************************************************/
#pragma once

typedef enum _shlcommandstate
{
	Commandstate_Closed,			//The connection is closed.
	Commandstate_Open,				//The connection is open.
	Commandstate_Connecting,		//The connection object is connecting to the data source.
	Commandstate_Executing,			//The connection object is executing a command. (This value is reserved for future versions of the product.)
	Commandstate_Fetching,			//The connection object is retrieving data. (This value is reserved for future versions of the product.)
	Commandstate_Broken,			//The connection to the data source is broken. This can occur only after the connection has been opened. A connection in this state may be closed and then re-opened. (This value is reserved for future versions of the product.)
	Commandstate_LENGTH
} SHLCONNECTIONSTATE;
