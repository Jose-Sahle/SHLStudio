/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Text;

using #NAMESPACEENTITY#;

namespace #NAMESPACEDAL#
{
	public sealed partial class #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# : BaseDAL<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#>
	{	
		private String GetSelectStringValidate(String property, String table, String value)
		{
			StringBuilder sql = new StringBuilder();

			sql.Append("SELECT COUNT(1) AS 'COUNT'");
			sql.Append(" FROM ");
			sql.Append(table.ToUpper());
			sql.Append(" WHERE ");
			sql.Append(property.ToUpper() + " = '" + value + "'");

			return sql.ToString();
		}
		
		/// <summary>
		/// Select and return all records from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		public Int32 SelectValidate(String Group, String property, String table, String value)
		{
			SQLHelper.Group = Group;

			int ret = 0;
			var reader = SQLHelper.ExecuteReader(GetSelectStringValidate(property, table, value));
			if (reader.Read()) { ret = Convert.ToInt32(reader["COUNT"]); }
			
			return ret;
		}

		/// <summary>
		/// Seleciona um Registro por ID da Tabela #TABELADAL#
		/// </summary>
		public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@#PRIMARYKEY#", pId);

			return base.ReturnUnique(GetSelectString(), parameters);
		}
		
		/// <summary>
		/// Select a record with a filter
		/// </summary>
		public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# Select(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			return base.ReturnUnique(GetSelectString(), CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records with a filter
		/// </summary>
		public List<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#> SelectList(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{			
			return base.ReturnList(GetSelectString(), CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		public Int32 Insert(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			SqlTransaction transaction = null;
			
			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table #TABLEWITHOUTPREFIXTABLE# with transction
		/// </summary>
		public Int32 Insert(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity, SqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery(GetInsertString(), oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		public void Update(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			SqlTransaction transaction = null;
			
			Update(transaction, entity);
		}

		/// <summary>
		/// Update a record in the table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>
		public void Update(SqlTransaction oSqlTransaction, #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			SQLHelper.ExecuteNonQuery(GetUpdateString(), oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		public void Delete(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			SqlTransaction transaction = null;

			Delete(transaction, entity);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>
		public void Delete(SqlTransaction oSqlTransaction, #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			SQLHelper.ExecuteNonQuery(GetDeleteString(), oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "@#PRIMARYKEY#", entity.#PRIMARYKEY#); 
			}

			<allfieldslessprimarykey>
			SQLHelper.AddParameter(ref parameters, "@#FIELD#", entity.#FIELD#);
			</allfieldslessprimarykey>

			return parameters;
		}
		
		private String GetInsertString()
		{
			String sql = String.Empty;
			
			sql = "INSERT INTO #TABLE#\n";
			sql +="(\n";
			<allfieldslessprimarykey>
			sql += "	#COMMABEFORE#[#FIELD#]\n";
			</allfieldslessprimarykey>
			sql +=")\n";
			sql += "VALUES\n";
			sql += "(\n";
				<allfieldslessprimarykey>
			sql += "	#COMMABEFORE#@#FIELD#\n";
				</allfieldslessprimarykey>
			sql += ")\n\n";

			sql += "SET @IdReturn = SCOPE_IDENTITY()\n";

			return sql;
		}
		
		private String GetUpdateString()
		{
			String sql = String.Empty;
			
			sql  = "UPDATE \n";
			sql += "	#TABLE# \n";
			sql += "SET \n";
				<allfieldslessprimarykey>
			sql += "	#COMMABEFORE#[#FIELD#] = @#FIELD#\n";
				</allfieldslessprimarykey>
			sql += "WHERE [#PRIMARYKEY#] = @#PRIMARYKEY#\n";
			
			return sql;
		}
		
		
		private String GetDeleteString()
		{
			String sql = String.Empty;
			
			sql = "DELETE FROM  \n";
			sql += "	#TABLE# \n";
			sql += "WHERE [#PRIMARYKEY#] = @#PRIMARYKEY#\n";
			
			return sql;
		}

		private String GetSelectString()
		{
			String sql = String.Empty;
			
			sql = "SELECT  \n";
			sql += "	[#PRIMARYKEY#],\n";
				<allfieldslessprimarykey>
			sql += "	[#FIELD#]#COMMAAFTER#\n";
				</allfieldslessprimarykey>
			sql += "FROM   #TABLE#  WITH (NOLOCK)\n";
			sql += "WHERE 1 = 1\n";
				<allfieldslessprimarykey>
			sql += "  AND ([#FIELD#] = @#FIELD# OR @#FIELD# IS NULL)\n";
				</allfieldslessprimarykey>       
				
			return sql;
		}
	}// Close out the class and namespace
}
