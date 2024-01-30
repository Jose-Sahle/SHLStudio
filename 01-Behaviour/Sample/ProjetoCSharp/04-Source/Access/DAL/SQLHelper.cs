/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 10/09/2014 19:45:48
**********************************************************/
using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Collections.Generic;
using System.Reflection;
using System.Threading;
using System.Data.OleDb;

namespace SHL.CEP.DAL
{
	public static class SQLHelper
	{
		private static String ConnectionString = String.Empty;
		// Time out em minutos COMMAND_TIMEOUT/60.
		private const int COMMAND_TIMEOUT = 600;

		/// <summary>
		/// Get the database transaction
		/// </summary>
		public static OleDbTransaction GetTransaction()
		{
			OleDbConnection oConnection = GetConnection();
			OleDbTransaction oTransaction;

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
			return ConnectionString;
		}

		/// <summary>		
		/// Obt??uma conex??para o banco de dados padr??o
		/// </summary>
		public static OleDbConnection GetConnection()
		{
			return new OleDbConnection(GetConnectionString());
		}

		public static void SetConnection(String connectionString)
		{
			ConnectionString = connectionString;
		}

		#region ExecuteNonQuery functions
			/// <summary>
			/// Execute a query.
			/// </summary>
			/// <param name="commandText">The query to execute.</param>
			public static void ExecuteNonQuery(string commandText)
			{
				OleDbConnection connection = GetConnection();
				ExecuteNonQuery(connection, commandText);
			}

			/// <summary>
			/// Executes the query.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The query to execute.</param>
			public static void ExecuteNonQuery(OleDbConnection connection, String commandText)
			{
				ExecuteNonQuery(connection, null, commandText);
			}

			/// <summary>
			/// Executes the query.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The query to execute.</param>
			public static void ExecuteNonQuery(OleDbConnection connection, OleDbTransaction transaction, String commandText)
			{
				if (connection.State == ConnectionState.Closed)
				{
					OpenDatabase(ref connection);
				}

				OleDbCommand command = CreateCommand(connection, transaction, commandText);
				command.ExecuteNonQuery();
			}

			public static void ExecuteNonQuery(string commandText, OleDbTransaction transaction)
			{
				OleDbConnection connection;
				
				if (transaction == null)
					connection = GetConnection();
				else
					connection = transaction.Connection;
					
				ExecuteNonQuery(connection, transaction, commandText);

			}

			public static Int64 ExecuteNonQueryIdentity(String commandText, OleDbConnection connection)
			{
				Int64 vRetorno;
				OleDbTransaction transaction = null;

				OpenDatabase(ref connection);
				
				OleDbCommand command = CreateCommand(connection, transaction, commandText);
				
				command.ExecuteNonQuery();
				
				DataTable dtIdenity = ExecuteDataTable(connection, "Select @@identity");
									
				vRetorno = Convert.ToInt32(dtIdenity.Rows[0][0]);
				
				return vRetorno;
			}

			public static Int64 ExecuteNonQueryIdentity(string commandText, OleDbTransaction transaction)
			{
				Int64 vRetorno;
				OleDbConnection connection;
				
				if (transaction == null)
				{
					connection = GetConnection();
					
					OpenDatabase(ref connection);
				}
				else
				{
					connection = transaction.Connection;
				}

				OleDbCommand command = CreateCommand(connection, transaction, commandText);

				command.ExecuteNonQuery();

				DataTable dtIdenity = ExecuteDataTable(connection, "Select @@identity");				
				
				vRetorno = Convert.ToInt32(dtIdenity.Rows[0][0]);
				
				return vRetorno;
			}
		#endregion

		#region ExecuteReader functions
			/// <summary>
			/// Executes the query.
			/// </summary>
			/// <param name="commandText">The query to execute.</param>
			/// <returns>A <see cref="OleDbDataReader"/> containing the results of the query execution.</returns>
			public static OleDbDataReader ExecuteReader(string commandText)
			{
				OleDbConnection connection = GetConnection();
				
				OpenDatabase(ref connection);
				
				return ExecuteReader(connection, commandText);
			}

			/// <summary>
			/// Executes the query.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The query to execute.</param>
			/// <returns>A <see cref="OleDbDataReader"/> containing the results of the query execution.</returns>
			public static OleDbDataReader ExecuteReader(OleDbConnection connection, String commandText)
			{
				return ExecuteReader(connection, null, commandText);
			}

			/// <summary>
			/// Executes the query.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The query to execute.</param>
			/// <returns>A <see cref="OleDbDataReader"/> containing the results of the query execution.</returns>
			public static OleDbDataReader ExecuteReader(OleDbConnection connection, OleDbTransaction transaction, String commandText)
			{
				if (connection.State == ConnectionState.Closed)
				{ 
					OpenDatabase(ref connection); 
				}
				
				OleDbCommand command = CreateCommand(connection, transaction, commandText);
				
				return command.ExecuteReader(CommandBehavior.CloseConnection);
			}
		#endregion

		#region ExecuteScalar functions
			/// <summary>
			/// Executes the query, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="commandText">The query to execute.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(string commandText)
			{
				using (OleDbConnection connection = GetConnection())
				{
					return ExecuteScalar(connection, commandText);
				}
			}

			/// <summary>
			/// Executes the query on the specified <see cref="OleDbConnection"/>, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The query to execute.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(OleDbConnection connection, string commandText)
			{
				return ExecuteScalar(connection, null, commandText);
			}

			/// <summary>
			/// Executes the query on the specified <see cref="OleDbConnection"/> within the specified <see cref="OleDbTransaction"/>, and returns the first column of the first row in the result set returned by the query. Extra columns or rows are ignored.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The query to execute.</param>
			/// <returns>The first column of the first row in the result set, or a null reference if the result set is empty.</returns>
			public static object ExecuteScalar(OleDbConnection connection, OleDbTransaction transaction, string commandText)
			{
				
				if (connection.State == ConnectionState.Closed)
				{ 
					OpenDatabase(ref connection); 
				}
				
				using (OleDbCommand command = CreateCommand(connection, transaction, commandText))
				{
					return command.ExecuteScalar();
				}
				
			}
		#endregion

		#region ExecuteDataSet functions
			/// <summary>
			/// Executes the query and returns the result as a <see cref="DataSet"/>.
			/// </summary>
			/// <param name="commandText">The query to execute.</param>
			/// <returns>A <see cref="DataSet"/> containing the results of the query execution.</returns>
			public static DataSet ExecuteDataSet(string commandText)
			{
				using (OleDbConnection connection = GetConnection())
				{
					using (OleDbCommand command = CreateCommand(connection, commandText))
					{
						return CreateDataSet(command);
					}
				}
			}

			/// <summary>
			/// Executes the query and returns the result as a <see cref="DataSet"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The query to execute.</param>
			/// <returns>A <see cref="DataSet"/> containing the results of the query execution.</returns>
			public static DataSet ExecuteDataSet(OleDbConnection connection, string commandText)
			{
				using (OleDbCommand command = CreateCommand(connection, commandText))
				{
					return CreateDataSet(command);
				}
			}


			/// <summary>
			/// Executes the query and returns the result as a <see cref="DataSet"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The query to execute.</param>
			/// <returns>A <see cref="DataSet"/> containing the results of the query execution.</returns>
			public static DataSet ExecuteDataSet(OleDbConnection connection, OleDbTransaction transaction, string commandText)
			{
				using (OleDbCommand command = CreateCommand(connection, transaction, commandText))
				{
					return CreateDataSet(command);
				}
			}
		#endregion

		#region ExecuteDataTable functions
			/// <summary>
			/// Executes the query and returns the result as a <see cref="DataTable"/>.
			/// </summary>
			/// <param name="commandText">The query to execute.</param>
			/// <returns>A <see cref="DataTable"/> containing the results of the query execution.</returns>
			public static DataTable ExecuteDataTable(string commandText)
			{
				using (OleDbConnection connection = GetConnection())
				{
					using (OleDbCommand command = CreateCommand(connection, commandText))
					{
						return CreateDataTable(command);
					}
				}
			}

			/// <summary>
			/// Executes the query and returns the result as a <see cref="DataTable"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="commandText">The query to execute.</param>
			/// <returns>A <see cref="DataTable"/> containing the results of the query execution.</returns>
			public static DataTable ExecuteDataTable(OleDbConnection connection, string commandText)
			{
				using (OleDbCommand command = CreateCommand(connection, commandText))
				{
					return CreateDataTable(command);
				}
			}


			/// <summary>
			/// Executes the query and returns the result as a <see cref="DataTable"/>.
			/// </summary>
			/// <param name="connection">The database connection to be used.</param>
			/// <param name="transaction">The transaction to participate in.</param>
			/// <param name="commandText">The query to execute.</param>
			/// <returns>A <see cref="DataTable"/> containing the results of the query execution.</returns>
			public static DataTable ExecuteDataTable(OleDbConnection connection, OleDbTransaction transaction, string commandText)
			{
				using (OleDbCommand command = CreateCommand(connection, transaction, commandText))
				{
					return CreateDataTable(command);
				}
			}
		#endregion

		#region Utility functions
		#region CreateCommand
			/// <summary>
			/// Creates, initializes, and returns a <see cref="OleDbCommand"/> instance.
			/// </summary>
			/// <param name="connection">The <see cref="OleDbConnection"/> the <see cref="OleDbCommand"/> should be executed on.</param>
			/// <param name="commandText">The name of the query to execute.</param>
			/// <returns>An initialized <see cref="OleDbCommand"/> instance.</returns>
			private static OleDbCommand CreateCommand(OleDbConnection connection, string commandText)
			{
				return CreateCommand(connection, null, commandText);
			}

			/// <summary>
			/// Creates, initializes, and returns a <see cref="OleDbCommand"/> instance.
			/// </summary>
			/// <param name="connection">The <see cref="OleDbConnection"/> the <see cref="OleDbCommand"/> should be executed on.</param>
			/// <param name="transaction">The <see cref="OleDbTransaction"/> the query execution should participate in.</param>
			/// <param name="commandText">The name of the query to execute.</param>
			/// <returns>An initialized <see cref="OleDbCommand"/> instance.</returns>
			private static OleDbCommand CreateCommand(OleDbConnection connection, OleDbTransaction transaction, string commandText)
			{
				OleDbCommand command = new OleDbCommand();
				
				command.Connection = connection;
				command.CommandText = commandText;
				command.CommandTimeout = COMMAND_TIMEOUT;
				
				command.CommandType = CommandType.Text;
					
				command.Transaction = transaction;
				
				return command;
			}
		#endregion CreateCommand

		private static DataSet CreateDataSet(OleDbCommand command)
		{
			using (OleDbDataAdapter dataAdapter = new OleDbDataAdapter(command))
			{
				DataSet dataSet = new DataSet();
				
				dataAdapter.Fill(dataSet);
				
				return dataSet;
			}
		}

		private static DataTable CreateDataTable(OleDbCommand command)
		{
			using (OleDbDataAdapter dataAdapter = new OleDbDataAdapter(command))
			{
				DataTable dataTable = new DataTable();
				
				dataAdapter.Fill(dataTable);
				
				return dataTable;
			}
		}

		private static void OpenDatabase(ref OleDbConnection connection)
		{
			Int32 nTry = 0;
			while (true)
			{
				try
				{
					connection.Open();
					
					break;
				}
				catch (OleDbException sex)
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
				OleDbException sqlex = e as OleDbException;
				
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
				OleDbException sqlex = e as OleDbException;
				
				if (sqlex != null && (sqlex.ErrorCode == 2627 || sqlex.ErrorCode == 2601))
				{
					return true;
				}

				return false;
			}
		#endregion
	}
}


