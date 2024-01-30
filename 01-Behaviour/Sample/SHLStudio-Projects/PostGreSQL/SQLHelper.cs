/**********************************************************
AUTHOR	: #AUTHOR#
VERSION	: #VERSION#
DATE		: #DATETIME#
**********************************************************/
using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Collections.Generic;
using System.Reflection;
using System.Threading;
using Npgsql;

namespace #NAMESPACEDAL#
{
	public static class SQLHelper
	{
		// Time out in minuts COMMAND_TIMEOUT/60.
		private const int COMMAND_TIMEOUT = 600;

		/// <summary>
		/// Get the database transaction
		/// </summary>
		public static NpgsqlTransaction GetTransaction()
		{
			NpgsqlConnection oConnection = GetConnection();
			NpgsqlTransaction oTransaction;

			try 
			{
				OpenDatabase(ref oConnection);
			}
			finally 
			{ 
				oTransaction = oConnection.BeginTransaction(System.Data.IsolationLevel.ReadUncommitted); 
			}

			return oTransaction;
		}

		/// <summary>
		/// Returns the connection string
		/// </summary>
		/// <returns>Returns the connection string.</returns>
		public static String GetConnectionString()
		{
			NpgsqlConnectionStringBuilder connectionString = new NpgsqlConnectionStringBuilder();

			String[] sServerPort;
			String sServidorPorta = String.Empty;
			String sServer = String.Empty;
			Int32 nPort = -1;
			String sDataBase = String.Empty;
			String sUser = String.Empty;
			String sPassword = String.Empty;

			#if(!DEBUG)
				sServidorPorta = "#DATABASESERVERDEBUG#";
				sServerPort = sServidorPorta.Split(':');
				sServer = sServerPort[0].ToString();
				if (sServerPort.Length > 1)
					nPort = Convert.ToInt32(sServerPort[1].ToString());
				else
					nPort = 5432;
				sDataBase = "#DATABASECATAGLOGDEBUG#";
				sUser = "#DATABASEUSERDEBUG#";
				sPassword = "#DATABASEPWDDEBUG#";
			#else
				sServidorPorta = "#DATABASESERVER#";
				sServerPort = sServidorPorta.Split(':');
				sServer = sServerPort[0].ToString();
				if (sServerPort.Length > 1)
					nPort = Convert.ToInt32(sServerPort[1].ToString());
				else
					nPort = 5432;
				sDataBase = "#DATABASECATAGLOG#";
				sUser = "#DATABASEUSER#";
				sPassword = "#DATABASEPWD#";
			#endif

			connectionString.Host = sServer;
			connectionString.Port = nPort;
			connectionString.Database = sDataBase;

			connectionString.UserName = sUser;
			connectionString.Password = sPassword;

			return connectionString.ConnectionString;		
		}

		/// <summary>		
		/// Gets a connection to the default database
		/// </summary>
		public static NpgsqlConnection GetConnection()
		{
			return new NpgsqlConnection(GetConnectionString());
		}

		#region ExecuteNonQuery functions
			/// <summary>
			/// Executes a stored procedure.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			public static void ExecuteNonQuery(string commandText)
			{
				NpgsqlConnection connection = GetConnection();
				ExecuteNonQuery(connection, commandText);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="NpgsqlConnection"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			public static void ExecuteNonQuery(NpgsqlConnection connection, String commandText)
			{
				ExecuteNonQuery(connection, null, commandText);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="NpgsqlConnection"/> within the specified <see cref="NpgsqlTransaction"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			public static void ExecuteNonQuery(NpgsqlConnection connection, NpgsqlTransaction transaction, String commandText)
			{
				if (connection.State == ConnectionState.Closed)
				{
					OpenDatabase(ref connection);
				}

				NpgsqlCommand command = CreateCommand(connection, transaction, commandText);
				command.ExecuteNonQuery();
			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			public static void ExecuteNonQuery(String commandText, ArrayList parameters)
			{
				NpgsqlConnection connection = GetConnection();
				ExecuteNonQuery(connection, commandText, parameters);

			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			public static void ExecuteNonQuery(string commandText, NpgsqlTransaction transaction, ArrayList parameters)
			{
				NpgsqlConnection connection;
				
				if (transaction == null)
					connection = GetConnection();
				else
					connection = transaction.Connection;
					
				ExecuteNonQuery(connection, transaction, commandText, parameters);
			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters on the specified connection.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			public static void ExecuteNonQuery(NpgsqlConnection connection, string commandText, ArrayList parameters)
			{
				ExecuteNonQuery(connection, null, commandText, parameters);
			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters on the specified <see cref="NpgsqlConnection"/> within the specified <see cref="NpgsqlTransaction"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			public static void ExecuteNonQuery(NpgsqlConnection connection, NpgsqlTransaction transaction, String commandText, ArrayList parameters)
			{
				if (connection.State == ConnectionState.Closed)
				{
					OpenDatabase(ref connection);
				}
				
				NpgsqlCommand command = CreateCommand(connection, transaction, commandText, parameters);
				
				command.ExecuteNonQuery();
			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <param name="ReturnParameter">The parameter to return.</param>
			public static Int64 ExecuteNonQuery(String commandText, ArrayList parameters, String ReturnParameter)
			{
				NpgsqlConnection connection = GetConnection();
				
				return ExecuteNonQuery(commandText, parameters, connection, ReturnParameter);
			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="ReturnParameter">The parameter to return.</param>
			public static Int64 ExecuteNonQuery(String commandText, ArrayList parameters, NpgsqlConnection connection, String ReturnParameter)
			{
				Int64 vRetorno;
				
				NpgsqlTransaction transaction = null;

				OpenDatabase(ref connection);

				parameters.Add(new NpgsqlParameter(ReturnParameter, NpgsqlTypes.NpgsqlDbType.Bigint, 8, "IdReturn", ParameterDirection.Output, false, 19, 0, DataRowVersion.Proposed, null));

				NpgsqlCommand command = CreateCommand(connection, transaction, commandText, parameters);

				command.ExecuteNonQuery();

				vRetorno = Convert.ToInt64(command.Parameters[ReturnParameter].Value);

				return vRetorno;
			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <param name="ReturnParameter">The parameter to return.</param>
			public static Int64 ExecuteNonQuery(string commandText, NpgsqlTransaction transaction, ArrayList parameters, String ReturnParameter)
			{
				Int64 vRetorno;
				NpgsqlConnection connection;
				
				if (transaction == null)
				{
					connection = GetConnection();
					
					OpenDatabase(ref connection);
				}
				else
				{
					connection = transaction.Connection;
				}

				parameters.Add(new NpgsqlParameter(ReturnParameter, NpgsqlTypes.NpgsqlDbType.Bigint, 8, "IdReturn", ParameterDirection.Output, false, 19, 0, DataRowVersion.Proposed, null));
				
				NpgsqlCommand command = CreateCommand(connection, transaction, commandText, parameters);
				
				command.ExecuteNonQuery();
				
				vRetorno = Convert.ToInt64(command.Parameters[ReturnParameter].Value);
				
				return vRetorno;
			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			public static void ExecuteNonQuery(String commandText, NpgsqlTransaction transaction)
			{
				NpgsqlCommand command = new NpgsqlCommand();
				
				command.Connection = transaction.Connection;
				command.CommandText = commandText;
				command.CommandTimeout = COMMAND_TIMEOUT;
				command.CommandType = CommandType.Text;
				command.Transaction = transaction;
				
				command.ExecuteNonQuery();
			}
		#endregion

		#region ExecuteReader functions
			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="NpgsqlDataReader"/>.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>A <see cref="NpgsqlDataReader"/> containing the results of the stored procedure execution.</returns>
			public static NpgsqlDataReader ExecuteReader(string commandText)
			{
				NpgsqlConnection connection = GetConnection();
				
				OpenDatabase(ref connection);
				
				return ExecuteReader(connection, commandText);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="NpgsqlConnection"/> and returns the result as a <see cref="NpgsqlDataReader"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>A <see cref="NpgsqlDataReader"/> containing the results of the stored procedure execution.</returns>
			public static NpgsqlDataReader ExecuteReader(NpgsqlConnection connection, String commandText)
			{
				return ExecuteReader(connection, null, commandText);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="NpgsqlConnection"/> within the specified <see cref="NpgsqlTransaction"/> and returns the result as a <see cref="NpgsqlDataReader"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>A <see cref="NpgsqlDataReader"/> containing the results of the stored procedure execution.</returns>
			public static NpgsqlDataReader ExecuteReader(NpgsqlConnection connection, NpgsqlTransaction transaction, String commandText)
			{
				if (connection.State == ConnectionState.Closed)
				{ 
					OpenDatabase(ref connection); 
				}
				
				NpgsqlCommand command = CreateCommand(connection, transaction, commandText);
				
				return command.ExecuteReader(CommandBehavior.CloseConnection);
			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters and returns the result as a <see cref="NpgsqlDataReader"/>.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>A <see cref="NpgsqlDataReader"/> containing the results of the stored procedure execution.</returns>
			public static NpgsqlDataReader ExecuteReader(String commandText, ArrayList parameters)
			{
				NpgsqlConnection connection = GetConnection();
				
				OpenDatabase(ref connection);
				
				return ExecuteReader(connection, commandText, parameters);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="NpgsqlConnection"/> with the specified parameters and returns the result as a <see cref="NpgsqlDataReader"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>A <see cref="NpgsqlDataReader"/> containing the results of the stored procedure execution.</returns>
			public static NpgsqlDataReader ExecuteReader(NpgsqlConnection connection, string commandText, ArrayList parameters)
			{
				return ExecuteReader(connection, null, commandText, parameters);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="NpgsqlConnection"/> within the specified <see cref="NpgsqlTransaction"/> with the specified parameters and returns the result as a <see cref="NpgsqlDataReader"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>A <see cref="NpgsqlDataReader"/> containing the results of the stored procedure execution.</returns>
			public static NpgsqlDataReader ExecuteReader(NpgsqlConnection connection, NpgsqlTransaction transaction, string commandText, ArrayList parameters)
			{
				if (connection.State == ConnectionState.Closed)
				{
					OpenDatabase(ref connection);
				}
				
				NpgsqlCommand command = CreateCommand(connection, transaction, commandText, parameters);
				
				return command.ExecuteReader(CommandBehavior.CloseConnection);
			}
		#endregion

		#region ExecuteScalar functions
			/// <summary>
			/// Executes the stored procedure, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(string commandText)
			{
				using (NpgsqlConnection connection = GetConnection())
				{
					return ExecuteScalar(connection, commandText);
				}
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="NpgsqlConnection"/>, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(NpgsqlConnection connection, string commandText)
			{
				return ExecuteScalar(connection, null, commandText);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="NpgsqlConnection"/> within the specified <see cref="NpgsqlTransaction"/>, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(NpgsqlConnection connection, NpgsqlTransaction transaction, string commandText)
			{
				
				if (connection.State == ConnectionState.Closed)
				{ 
					OpenDatabase(ref connection); 
				}
				
				using (NpgsqlCommand command = CreateCommand(connection, transaction, commandText))
				{
					return command.ExecuteScalar();
				}				
			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(string commandText, ArrayList parameters)
			{
				using (NpgsqlConnection connection = GetConnection())
				{
					return ExecuteScalar(connection, commandText, parameters);
				}
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="NpgsqlTransaction"/> with the specified parameters, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(NpgsqlConnection connection, string commandText, ArrayList parameters)
			{
				return ExecuteScalar(connection, null, commandText, parameters);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="NpgsqlTransaction"/> within the specified <see cref="NpgsqlTransaction"/> with the specified parameters, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(NpgsqlConnection connection, NpgsqlTransaction transaction, string commandText, ArrayList parameters)
			{
				if (connection.State == ConnectionState.Closed)
				{ 
					OpenDatabase(ref connection); 
				}
				
				using (NpgsqlCommand command = CreateCommand(connection, transaction, commandText, parameters))
				{
					return command.ExecuteScalar();
				}
			}
		#endregion

		#region ExecuteDataSet functions
			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="DataSet"/>.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>A <see cref="DataSet"/> containing the results of the stored procedure execution.</returns>
			public static DataSet ExecuteDataSet(string commandText)
			{
				using (NpgsqlConnection connection = GetConnection())
				{
					using (NpgsqlCommand command = CreateCommand(connection, commandText))
					{
						return CreateDataSet(command);
					}
				}
			}

			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="DataSet"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>A <see cref="DataSet"/> containing the results of the stored procedure execution.</returns>
			public static DataSet ExecuteDataSet(NpgsqlConnection connection, string commandText)
			{
				using (NpgsqlCommand command = CreateCommand(connection, commandText))
				{
					return CreateDataSet(command);
				}
			}

			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="DataSet"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>A <see cref="DataSet"/> containing the results of the stored procedure execution.</returns>
			public static DataSet ExecuteDataSet(NpgsqlConnection connection, NpgsqlTransaction transaction, string commandText)
			{
				using (NpgsqlCommand command = CreateCommand(connection, transaction, commandText))
				{
					return CreateDataSet(command);
				}
			}

			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="DataSet"/>.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>A <see cref="DataSet"/> containing the results of the stored procedure execution.</returns>
			public static DataSet ExecuteDataSet(string commandText, ArrayList parameters)
			{
				using (NpgsqlConnection connection = GetConnection())
				{
					using (NpgsqlCommand command = CreateCommand(connection, commandText, parameters))
					{
						return CreateDataSet(command);
					}
				}
			}

			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="DataSet"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>A <see cref="DataSet"/> containing the results of the stored procedure execution.</returns>
			public static DataSet ExecuteDataSet(NpgsqlConnection connection, string commandText, ArrayList parameters)
			{
				using (NpgsqlCommand command = CreateCommand(connection, commandText, parameters))
				{
					return CreateDataSet(command);
				}
			}

			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="DataSet"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>A <see cref="DataSet"/> containing the results of the stored procedure execution.</returns>
			public static DataSet ExecuteDataSet(NpgsqlConnection connection, NpgsqlTransaction transaction, string commandText, ArrayList parameters)
			{
				using (NpgsqlCommand command = CreateCommand(connection, transaction, commandText, parameters))
				{
					return CreateDataSet(command);
				}
			}
		#endregion

		#region ExecuteDataTable functions
			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="DataTable"/>.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>A <see cref="DataTable"/> containing the results of the stored procedure execution.</returns>
			public static DataTable ExecuteDataTable(string commandText)
			{
				using (NpgsqlConnection connection = GetConnection())
				{
					using (NpgsqlCommand command = CreateCommand(connection, commandText))
					{
						return CreateDataTable(command);
					}
				}
			}

			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="DataTable"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>A <see cref="DataTable"/> containing the results of the stored procedure execution.</returns>
			public static DataTable ExecuteDataTable(NpgsqlConnection connection, string commandText)
			{
				using (NpgsqlCommand command = CreateCommand(connection, commandText))
				{
					return CreateDataTable(command);
				}
			}

			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="DataTable"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>A <see cref="DataTable"/> containing the results of the stored procedure execution.</returns>
			public static DataTable ExecuteDataTable(NpgsqlConnection connection, NpgsqlTransaction transaction, string commandText)
			{
				using (NpgsqlCommand command = CreateCommand(connection, transaction, commandText))
				{
					return CreateDataTable(command);
				}
			}

			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="DataTable"/>.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>A <see cref="DataTable"/> containing the results of the stored procedure execution.</returns>
			public static DataTable ExecuteDataTable(string commandText, ArrayList parameters)
			{
				using (NpgsqlConnection connection = GetConnection())
				{
					using (NpgsqlCommand command = CreateCommand(connection, commandText, parameters))
					{
						return CreateDataTable(command);
					}
				}
			}

			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="DataTable"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>A <see cref="DataTable"/> containing the results of the stored procedure execution.</returns>
			public static DataTable ExecuteDataTable(NpgsqlConnection connection, string commandText, ArrayList parameters)
			{
				using (NpgsqlCommand command = CreateCommand(connection, commandText, parameters))
				{
					return CreateDataTable(command);
				}
			}

			/// <summary>
			/// Executes the stored procedure and returns the result as a <see cref="DataTable"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>A <see cref="DataTable"/> containing the results of the stored procedure execution.</returns>
			public static DataTable ExecuteDataTable(NpgsqlConnection connection, NpgsqlTransaction transaction, string commandText, ArrayList parameters)
			{
				using (NpgsqlCommand command = CreateCommand(connection, transaction, commandText, parameters))
				{
					return CreateDataTable(command);
				}
			}
		#endregion

		#region Utility functions
			/// <summary>
			/// Sets the specified <see cref="NpgsqlParameter"/>
			/// <code>Value</code> property to <code>DBNull.Value</code> if it is <code>null</code>.
			/// </summary>
			/// <param name="parameter">The <see cref="NpgsqlParameter"/> that should be checked for nulls.</param>
			/// <returns>The <see cref="NpgsqlParameter"/> with a potentially updated <code>Value</code> property.</returns>

			public static ArrayList AddParameter(string vParameter, object oValor)
			{
				vParameter = AddAt(vParameter);
				
				ArrayList parameters = new ArrayList();
				
				parameters.Add(new NpgsqlParameter(vParameter, oValor));
				
				return parameters;
			}

			public static void AddParameter(ref ArrayList parameters, string vParameter, object oValor)
			{
				vParameter = AddAt(vParameter);
				
				parameters.Add(new NpgsqlParameter(vParameter, oValor));
			}

			private static string AddAt(string vParameter)
			{
				if (vParameter.Substring(0, 1) != "@")
				{ 
					vParameter.Insert(0, "@"); 
				}
				
				return vParameter;
			}

			private static NpgsqlParameter CheckParameter(NpgsqlParameter parameter)
			{
				if (parameter.Value == null)
				{
					parameter.Value = DBNull.Value;
				}
				else if ((parameter.DbType == DbType.DateTime ||
							parameter.DbType == DbType.Date ||
							parameter.DbType == DbType.Time
						) && Convert.ToDateTime(parameter.Value) == new DateTime(1900, 1, 1))
				{
					parameter.Value = DBNull.Value;
				}

				return parameter;
			}
			
			#region CreateCommand
				/// <summary>
				/// Creates, initializes, and returns a <see cref="NpgsqlCommand"/> instance.
				/// </summary>
				/// <param name="connection">The <see cref="NpgsqlConnection"/> the <see cref="NpgsqlCommand"/> should be executed on.</param>
				/// <param name="commandText">The name of the stored procedure to execute.</param>
				/// <returns>An initialized <see cref="NpgsqlCommand"/> instance.</returns>
				private static NpgsqlCommand CreateCommand(NpgsqlConnection connection, string commandText)
				{
					return CreateCommand(connection, null, commandText);
				}

				/// <summary>
				/// Creates, initializes, and returns a <see cref="NpgsqlCommand"/> instance.
				/// </summary>
				/// <param name="connection">The <see cref="NpgsqlConnection"/> the <see cref="NpgsqlCommand"/> should be executed on.</param>
				/// <param name="transaction">The <see cref="NpgsqlTransaction"/> the stored procedure execution should participate in.</param>
				/// <param name="commandText">The name of the stored procedure to execute.</param>
				/// <returns>An initialized <see cref="NpgsqlCommand"/> instance.</returns>
				private static NpgsqlCommand CreateCommand(NpgsqlConnection connection, NpgsqlTransaction transaction, string commandText)
				{
					NpgsqlCommand command = new NpgsqlCommand();
					
					command.Connection = connection;
					command.CommandText = commandText;
					command.CommandTimeout = COMMAND_TIMEOUT;
					
					if (commandText.ToUpper().StartsWith("SELECT"))
						command.CommandType = CommandType.Text;
					else
						command.CommandType = CommandType.StoredProcedure;
						
					command.Transaction = transaction;
					
					return command;
				}

				/// <summary>
				/// Creates, initializes, and returns a <see cref="NpgsqlCommand"/> instance.
				/// </summary>
				/// <param name="connection">The <see cref="NpgsqlConnection"/> the <see cref="NpgsqlCommand"/> should be executed on.</param>
				/// <param name="commandText">The name of the stored procedure to execute.</param>
				/// <param name="parameters">The parameters of the stored procedure.</param>
				/// <returns>An initialized <see cref="NpgsqlCommand"/> instance.</returns>
				private static NpgsqlCommand CreateCommand(NpgsqlConnection connection, string commandText, ArrayList parameters)
				{
					return CreateCommand(connection, null, commandText, parameters);
				}

				/// <summary>
				/// Creates, initializes, and returns a <see cref="NpgsqlCommand"/> instance.
				/// </summary>
				/// <param name="connection">The <see cref="NpgsqlConnection"/> the <see cref="NpgsqlCommand"/> should be executed on.</param>
				/// <param name="transaction">The <see cref="NpgsqlTransaction"/> the stored procedure execution should participate in.</param>
				/// <param name="commandText">The name of the stored procedure to execute.</param>
				/// <param name="parameters">The parameters of the stored procedure.</param>
				/// <returns>An initialized <see cref="NpgsqlCommand"/> instance.</returns>
				private static NpgsqlCommand CreateCommand(NpgsqlConnection connection, NpgsqlTransaction transaction, string commandText, ArrayList parameters)
				{
					NpgsqlCommand command = new NpgsqlCommand();
					
					command.Connection = connection;
					command.CommandText = commandText;
					command.CommandTimeout = COMMAND_TIMEOUT;
					command.CommandType = CommandType.StoredProcedure;
					command.Transaction = transaction;

					// Append each parameter to the command
					foreach (NpgsqlParameter parameter in parameters)
					{
						command.Parameters.Add(CheckParameter(parameter));
					}

					return command;
				}
			#endregion CreateCommand

			private static DataSet CreateDataSet(NpgsqlCommand command)
			{
				using (NpgsqlDataAdapter dataAdapter = new NpgsqlDataAdapter(command))
				{
					DataSet dataSet = new DataSet();
					
					dataAdapter.Fill(dataSet);
					
					return dataSet;
				}
			}

			private static DataTable CreateDataTable(NpgsqlCommand command)
			{
				using (NpgsqlDataAdapter dataAdapter = new NpgsqlDataAdapter(command))
				{
					DataTable dataTable = new DataTable();
					
					dataAdapter.Fill(dataTable);
					
					return dataTable;
				}
			}

			private static void OpenDatabase(ref NpgsqlConnection connection)
			{
				Int32 nTry = 0;
				while (true)
				{
					try
					{
						connection.Open();
						
						break;
					}
					catch (NpgsqlException sex)
					{
						nTry++;

						if (nTry > 10)
							throw sex;
					}
					catch (Exception ex)
					{
						nTry++;

						if (nTry > 10)
							throw ex;
					}

					Thread.Sleep(2000);
				}
			}
		#endregion

		#region Exception functions
			/// <summary>
			/// Determines if the specified exception is the result of a foreign key violation.
			/// </summary>
			/// <param name="e">The exception to check.</param>
			/// <returns><code>true</code> if the exception is a foreign key violation, otherwise <code>false</code>.</returns>
			public static bool IsForeignKeyContraintException(Exception e)
			{
				NpgsqlException sqlex = e as NpgsqlException;
				
				if (sqlex != null && sqlex.ErrorCode == 547)
				{
					return true;
				}

				return false;
			}

			/// <summary>
			/// Determines if the specified exception is the result of a unique constraint violation.
			/// </summary>
			/// <param name="e">The exception to check.</param>
			/// <returns><code>true</code> if the exception is a unique constraint violation, otherwise <code>false</code>.</returns>
			public static bool IsUniqueConstraintException(Exception e)
			{
				NpgsqlException sqlex = e as NpgsqlException;
				
				if (sqlex != null && (sqlex.ErrorCode == 2627 || sqlex.ErrorCode == 2601))
				{
					return true;
				}

				return false;
			}
		#endregion
	}
}

