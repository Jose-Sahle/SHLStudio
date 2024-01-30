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
using System.Data.SqlClient;

namespace #NAMESPACEDAL#
{
	public static class SQLHelper
	{
		private static String ConnectionString = String.Empty;
		// Time out em minutos COMMAND_TIMEOUT/60.
		private const int COMMAND_TIMEOUT = 600;

		/// <summary>
		/// Get the database transaction
		/// </summary>
		public static SqlTransaction GetTransaction()
		{
			SqlConnection oConnection = GetConnection();
			SqlTransaction oTransaction;

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
		/// Retorna a String de Conexo
		/// </summary>
		/// <returns>A conexo configurada.</returns>
		public static String GetConnectionString()
		{
			#if(!DEBUG)
				return @"Data Source=#DATABASESERVERDEBUG#;Initial Catalog=#DATABASECATAGLOGDEBUG#;User ID=#DATABASEUSERDEBUG#;pwd=#DATABASEPWDDEBUG#";
			#else
				return @"Data Source=#DATABASESERVER#;Initial Catalog=#DATABASECATAGLOG#;User ID=#DATABASEUSER#;pwd=#DATABASEPWD#";
			#endif
		
			/*return ConnectionString;*/
		}

		/// <summary>		
		/// Obtéuma conexãpara o banco de dados padrão
		/// </summary>
		public static SqlConnection GetConnection()
		{
			return new SqlConnection(GetConnectionString());
		}

		public static void SetConnection(String connectionString)
		{
			ConnectionString = connectionString;
		}

		#region ExecuteNonQuery functions
			/// <summary>
			/// Execute a stored procedure.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			public static void ExecuteNonQuery(string commandText)
			{
				SqlConnection connection = GetConnection();
				ExecuteNonQuery(connection, commandText);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="SqlConnection"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			public static void ExecuteNonQuery(SqlConnection connection, String commandText)
			{
				ExecuteNonQuery(connection, null, commandText);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="SqlConnection"/> within the specified <see cref="SqlTransaction"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			public static void ExecuteNonQuery(SqlConnection connection, SqlTransaction transaction, String commandText)
			{
				if (connection.State == ConnectionState.Closed)
				{
					OpenDatabase(ref connection);
				}

				SqlCommand command = CreateCommand(connection, transaction, commandText);
				command.ExecuteNonQuery();
			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			public static void ExecuteNonQuery(String commandText, ArrayList parameters)
			{
				SqlConnection connection = GetConnection();
				ExecuteNonQuery(connection, commandText, parameters);

			}

			public static void ExecuteNonQuery(string commandText, SqlTransaction transaction, ArrayList parameters)
			{
				SqlConnection connection;
				
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
			public static void ExecuteNonQuery(SqlConnection connection, string commandText, ArrayList parameters)
			{
				ExecuteNonQuery(connection, null, commandText, parameters);
			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters on the specified <see cref="SqlConnection"/> within the specified <see cref="SqlTransaction"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			public static void ExecuteNonQuery(SqlConnection connection, SqlTransaction transaction, String commandText, ArrayList parameters)
			{
				if (connection.State == ConnectionState.Closed)
				{
					OpenDatabase(ref connection);
				}
				
				SqlCommand command = CreateCommand(connection, transaction, commandText, parameters);
				
				command.ExecuteNonQuery();
			}

			public static Int64 ExecuteNonQuery(String commandText, ArrayList parameters, String ReturnParameter)
			{
				SqlConnection connection = GetConnection();
				
				return ExecuteNonQuery(commandText, parameters, connection, ReturnParameter);
			}

			public static Int64 ExecuteNonQuery(String commandText, ArrayList parameters, SqlConnection connection, String ReturnParameter)
			{
				Int64 vRetorno;
				SqlTransaction transaction = null;

				OpenDatabase(ref connection);
				
				SqlCommand command = CreateCommand(connection, transaction, commandText, parameters);

				SqlParameter retVal = command.Parameters.Add("return", SqlDbType.Int);
				retVal.Direction = ParameterDirection.ReturnValue;
				
				command.ExecuteNonQuery();
				
				vRetorno = Convert.ToInt32(retVal.Value);
				
				return vRetorno;
			}

			public static Int64 ExecuteNonQuery(string commandText, SqlTransaction transaction, ArrayList parameters, String ReturnParameter)
			{
				Int64 vRetorno;
				SqlConnection connection;
				
				if (transaction == null)
				{
					connection = GetConnection();
					
					OpenDatabase(ref connection);
				}
				else
				{
					connection = transaction.Connection;
				}

				SqlCommand command = CreateCommand(connection, transaction, commandText, parameters);

				SqlParameter retVal = command.Parameters.Add("return", SqlDbType.Int);
				retVal.Direction = ParameterDirection.ReturnValue;
				
				vRetorno = command.ExecuteNonQuery();
				
				vRetorno = Convert.ToInt32(retVal.Value);
				
				return vRetorno;
			}

			public static void ExecuteNonQuery(String commandText, SqlTransaction transaction)
			{
				SqlCommand command = new SqlCommand();
				
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
			/// Executes the stored procedure and returns the result as a <see cref="SqlDataReader"/>.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>A <see cref="SqlDataReader"/> containing the results of the stored procedure execution.</returns>
			public static SqlDataReader ExecuteReader(string commandText)
			{
				SqlConnection connection = GetConnection();
				
				OpenDatabase(ref connection);
				
				return ExecuteReader(connection, commandText);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="SqlConnection"/> and returns the result as a <see cref="SqlDataReader"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>A <see cref="SqlDataReader"/> containing the results of the stored procedure execution.</returns>
			public static SqlDataReader ExecuteReader(SqlConnection connection, String commandText)
			{
				return ExecuteReader(connection, null, commandText);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="SqlConnection"/> within the specified <see cref="SqlTransaction"/> and returns the result as a <see cref="SqlDataReader"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>A <see cref="SqlDataReader"/> containing the results of the stored procedure execution.</returns>
			public static SqlDataReader ExecuteReader(SqlConnection connection, SqlTransaction transaction, String commandText)
			{
				if (connection.State == ConnectionState.Closed)
				{ 
				OpenDatabase(ref connection); 
				}
				
				SqlCommand command = CreateCommand(connection, transaction, commandText);
				
				return command.ExecuteReader(CommandBehavior.CloseConnection);
			}

			/// <summary>
			/// Executes the stored procedure with the specified parameters and returns the result as a <see cref="SqlDataReader"/>.
			/// </summary>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>A <see cref="SqlDataReader"/> containing the results of the stored procedure execution.</returns>
			public static SqlDataReader ExecuteReader(String commandText, ArrayList parameters)
			{
				SqlConnection connection = GetConnection();
				
				OpenDatabase(ref connection);
				
				return ExecuteReader(connection, commandText, parameters);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="SqlConnection"/> with the specified parameters and returns the result as a <see cref="SqlDataReader"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>A <see cref="SqlDataReader"/> containing the results of the stored procedure execution.</returns>
			public static SqlDataReader ExecuteReader(SqlConnection connection, string commandText, ArrayList parameters)
			{
				return ExecuteReader(connection, null, commandText, parameters);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="SqlConnection"/> within the specified <see cref="SqlTransaction"/> with the specified parameters and returns the result as a <see cref="SqlDataReader"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>A <see cref="SqlDataReader"/> containing the results of the stored procedure execution.</returns>
			public static SqlDataReader ExecuteReader(SqlConnection connection, SqlTransaction transaction, string commandText, ArrayList parameters)
			{
				if (connection.State == ConnectionState.Closed)
				{
					OpenDatabase(ref connection);
				}
				
				SqlCommand command = CreateCommand(connection, transaction, commandText, parameters);
				
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
				using (SqlConnection connection = GetConnection())
				{
					return ExecuteScalar(connection, commandText);
				}
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="SqlConnection"/>, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(SqlConnection connection, string commandText)
			{
				return ExecuteScalar(connection, null, commandText);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="SqlConnection"/> within the specified <see cref="SqlTransaction"/>, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(SqlConnection connection, SqlTransaction transaction, string commandText)
			{
				
				if (connection.State == ConnectionState.Closed)
				{ 
					OpenDatabase(ref connection); 
				}
				
				using (SqlCommand command = CreateCommand(connection, transaction, commandText))
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
				using (SqlConnection connection = GetConnection())
				{
					return ExecuteScalar(connection, commandText, parameters);
				}
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="SqlTransaction"/> with the specified parameters, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(SqlConnection connection, string commandText, ArrayList parameters)
			{
				return ExecuteScalar(connection, null, commandText, parameters);
			}

			/// <summary>
			/// Executes the stored procedure on the specified <see cref="SqlTransaction"/> within the specified <see cref="SqlTransaction"/> with the specified parameters, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(SqlConnection connection, SqlTransaction transaction, string commandText, ArrayList parameters)
			{
				if (connection.State == ConnectionState.Closed)
				{ 
					OpenDatabase(ref connection); 
				}
				
				using (SqlCommand command = CreateCommand(connection, transaction, commandText, parameters))
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
				using (SqlConnection connection = GetConnection())
				{
					using (SqlCommand command = CreateCommand(connection, commandText))
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
			public static DataSet ExecuteDataSet(SqlConnection connection, string commandText)
			{
				using (SqlCommand command = CreateCommand(connection, commandText))
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
			public static DataSet ExecuteDataSet(SqlConnection connection, SqlTransaction transaction, string commandText)
			{
				using (SqlCommand command = CreateCommand(connection, transaction, commandText))
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
				using (SqlConnection connection = GetConnection())
				{
					using (SqlCommand command = CreateCommand(connection, commandText, parameters))
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
			public static DataSet ExecuteDataSet(SqlConnection connection, string commandText, ArrayList parameters)
			{
				using (SqlCommand command = CreateCommand(connection, commandText, parameters))
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
			public static DataSet ExecuteDataSet(SqlConnection connection, SqlTransaction transaction, string commandText, ArrayList parameters)
			{
				using (SqlCommand command = CreateCommand(connection, transaction, commandText, parameters))
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
				using (SqlConnection connection = GetConnection())
				{
					using (SqlCommand command = CreateCommand(connection, commandText))
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
			public static DataTable ExecuteDataTable(SqlConnection connection, string commandText)
			{
				using (SqlCommand command = CreateCommand(connection, commandText))
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
			public static DataTable ExecuteDataTable(SqlConnection connection, SqlTransaction transaction, string commandText)
			{
				using (SqlCommand command = CreateCommand(connection, transaction, commandText))
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
				using (SqlConnection connection = GetConnection())
				{
					using (SqlCommand command = CreateCommand(connection, commandText, parameters))
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
			public static DataTable ExecuteDataTable(SqlConnection connection, string commandText, ArrayList parameters)
			{
				using (SqlCommand command = CreateCommand(connection, commandText, parameters))
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
			public static DataTable ExecuteDataTable(SqlConnection connection, SqlTransaction transaction, string commandText, ArrayList parameters)
			{
				using (SqlCommand command = CreateCommand(connection, transaction, commandText, parameters))
				{
					return CreateDataTable(command);
				}
			}
		#endregion

		#region Utility functions
			/// <summary>
			/// Sets the specified <see cref="SqlParameter"/>
			/// <code>Value</code> property to <code>DBNull.Value</code> if it is <code>null</code>.
			/// </summary>
			/// <param name="parameter">The <see cref="SqlParameter"/> that should be checked for nulls.</param>
			/// <returns>The <see cref="SqlParameter"/> with a potentially updated <code>Value</code> property.</returns>

			public static ArrayList AddParameter(string vParameter, object oValor)
			{
				vParameter = AddAt(vParameter);
				
				ArrayList parameters = new ArrayList();
				
				parameters.Add(new SqlParameter(vParameter, oValor));
				
				return parameters;
			}

			public static void AddParameter(ref ArrayList parameters, string vParameter, object oValor)
			{
				vParameter = AddAt(vParameter);
				
				parameters.Add(new SqlParameter(vParameter, oValor));
			}

			private static string AddAt(string vParameter)
			{
				if (vParameter.Substring(0, 1) != "@")
				{ 
					vParameter.Insert(0, "@"); 
				}
				
				return vParameter;
			}

			private static SqlParameter CheckParameter(SqlParameter parameter)
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
			/// Creates, initializes, and returns a <see cref="SqlCommand"/> instance.
			/// </summary>
			/// <param name="connection">The <see cref="SqlConnection"/> the <see cref="SqlCommand"/> should be executed on.</param>
			/// <param name="commandText">The name of the stored procedure to execute.</param>
			/// <returns>An initialized <see cref="SqlCommand"/> instance.</returns>
			private static SqlCommand CreateCommand(SqlConnection connection, string commandText)
			{
				return CreateCommand(connection, null, commandText);
			}

			/// <summary>
			/// Creates, initializes, and returns a <see cref="SqlCommand"/> instance.
			/// </summary>
			/// <param name="connection">The <see cref="SqlConnection"/> the <see cref="SqlCommand"/> should be executed on.</param>
			/// <param name="transaction">The <see cref="SqlTransaction"/> the stored procedure execution should participate in.</param>
			/// <param name="commandText">The name of the stored procedure to execute.</param>
			/// <returns>An initialized <see cref="SqlCommand"/> instance.</returns>
			private static SqlCommand CreateCommand(SqlConnection connection, SqlTransaction transaction, string commandText)
			{
				SqlCommand command = new SqlCommand();
				
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
			/// Creates, initializes, and returns a <see cref="SqlCommand"/> instance.
			/// </summary>
			/// <param name="connection">The <see cref="SqlConnection"/> the <see cref="SqlCommand"/> should be executed on.</param>
			/// <param name="commandText">The name of the stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>An initialized <see cref="SqlCommand"/> instance.</returns>
			private static SqlCommand CreateCommand(SqlConnection connection, string commandText, ArrayList parameters)
			{
				return CreateCommand(connection, null, commandText, parameters);
			}

			/// <summary>
			/// Creates, initializes, and returns a <see cref="SqlCommand"/> instance.
			/// </summary>
			/// <param name="connection">The <see cref="SqlConnection"/> the <see cref="SqlCommand"/> should be executed on.</param>
			/// <param name="transaction">The <see cref="SqlTransaction"/> the stored procedure execution should participate in.</param>
			/// <param name="commandText">The name of the stored procedure to execute.</param>
			/// <param name="parameters">The parameters of the stored procedure.</param>
			/// <returns>An initialized <see cref="SqlCommand"/> instance.</returns>
			private static SqlCommand CreateCommand(SqlConnection connection, SqlTransaction transaction, string commandText, ArrayList parameters)
			{
				SqlCommand command = new SqlCommand();
				
				command.Connection = connection;
				command.CommandText = commandText;
				command.CommandTimeout = COMMAND_TIMEOUT;
				command.CommandType = CommandType.StoredProcedure;
				command.Transaction = transaction;

				// Append each parameter to the command
				foreach (SqlParameter parameter in parameters)
				{
					command.Parameters.Add(CheckParameter(parameter));

				}

				return command;
			}
		#endregion CreateCommand

		private static DataSet CreateDataSet(SqlCommand command)
		{
			using (SqlDataAdapter dataAdapter = new SqlDataAdapter(command))
			{
				DataSet dataSet = new DataSet();
				
				dataAdapter.Fill(dataSet);
				
				return dataSet;
			}
		}

		private static DataTable CreateDataTable(SqlCommand command)
		{
			using (SqlDataAdapter dataAdapter = new SqlDataAdapter(command))
			{
				DataTable dataTable = new DataTable();
				
				dataAdapter.Fill(dataTable);
				
				return dataTable;
			}
		}

		private static void OpenDatabase(ref SqlConnection connection)
		{
			Int32 nTry = 0;
			while (true)
			{
				try
				{
					connection.Open();
					
					break;
				}
				catch (SqlException sex)
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
				SqlException sqlex = e as SqlException;
				
				if (sqlex != null && sqlex.Number == 547)
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
				SqlException sqlex = e as SqlException;
				
				if (sqlex != null && (sqlex.Number == 2627 || sqlex.Number == 2601))
				{
					return true;
				}

				return false;
			}
		#endregion
	}
}

