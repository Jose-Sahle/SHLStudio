/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Text;
using System.Data.OleDb;

using #NAMESPACEENTITY#;

namespace #NAMESPACEDAL#
{
	public sealed partial class #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# : BaseAccessDAL<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#>
	{
		/// <summary>
		/// Seleciona um Registro por ID da Tabela #TABELADAL#
		/// </summary>
		public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# Select(Int32 pId)
		{
			StringBuilder sbSQL = new StringBuilder();
			
			sbSQL.Append("SELECT\n");
			sbSQL.Append("[#PRIMARYKEY#],\n");
				<allfieldslessprimarykey>
			sbSQL.Append("[#FIELD#]#COMMAAFTER#\n");
				</allfieldslessprimarykey>
			sbSQL.Append("FROM \n");
			sbSQL.Append("[#TABLE#] \n");
			sbSQL.Append("WHERE \n");
			sbSQL.Append("[#PRIMARYKEY#] = " + pId.ToString());

			return base.ReturnUnique(sbSQL.ToString());
		}


		/// <summary>
		/// Select and return all records from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		public List<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#> SelectList()
		{
			StringBuilder sbSQL = new StringBuilder();
			
			sbSQL.Append("SELECT\n");
			sbSQL.Append("[#PRIMARYKEY#],\n");
				<allfieldslessprimarykey>
			sbSQL.Append("[#FIELD#]#COMMAAFTER#\n");
				</allfieldslessprimarykey>
			sbSQL.Append("FROM \n");
			sbSQL.Append("[#TABLE#] \n");
			
			return base.ReturnList(sbSQL.ToString());		
		}

		/// <summary>
		/// Select a record with a filter
		/// </summary>
		public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# Select(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			StringBuilder sbSQL = new StringBuilder();
			StringBuilder sbSQLCriteria  = new StringBuilder();
			
			sbSQL.Append("SELECT\n");
			sbSQL.Append("[#PRIMARYKEY#],\n");
				<allfieldslessprimarykey>
			sbSQL.Append("[#FIELD#]#COMMAAFTER#\n");
				</allfieldslessprimarykey>
			sbSQL.Append("FROM \n");
			sbSQL.Append("[#TABLE#] \n");
			sbSQL.Append("WHERE \n");
			
			if(entity.#PRIMARYKEY# != null)
				sbSQLCriteria.Append("[#PRIMARYKEY#] = " + entity.#PRIMARYKEY#.ToString() + "\n");
				
			<allfieldslessprimarykey>
			if(entity.#FIELD# != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[#FIELD#] = '" + entity.#FIELD#.ToString() + "'\n");
			}
			
			</allfieldslessprimarykey>       
				
			if(sbSQLCriteria.Length > 0)
				sbSQL.Append(sbSQLCriteria.ToString());
		
			return base.ReturnUnique(sbSQL.ToString());
		}

		/// <summary>
		/// Select some records with a filter
		/// </summary>
		public List<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#> SelectList(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			StringBuilder sbSQL = new StringBuilder();
			StringBuilder sbSQLCriteria  = new StringBuilder();
			
			sbSQL.Append("SELECT\n");
			sbSQL.Append("[#PRIMARYKEY#],\n");
				<allfieldslessprimarykey>
			sbSQL.Append("[#FIELD#]#COMMAAFTER#\n");
				</allfieldslessprimarykey>
			sbSQL.Append("FROM \n");
			sbSQL.Append("[#TABLE#] \n");
			sbSQL.Append("WHERE \n");
			
			if(entity.#PRIMARYKEY# != null)
				sbSQLCriteria.Append("[#PRIMARYKEY#] = " + entity.#PRIMARYKEY#.ToString() + "\n");
				
			<allfieldslessprimarykey>
			if(entity.#FIELD# != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[#FIELD#] = '" + entity.#FIELD#.ToString() + "'\n");
			}
			
			</allfieldslessprimarykey>       
				
			if(sbSQLCriteria.Length > 0)
				sbSQL.Append(sbSQLCriteria.ToString());

			return base.ReturnList(sbSQL.ToString());
		}

		/// <summary>
		/// Insert a record in the table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		public Int32 Insert(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			OleDbTransaction transaction = null;

			return Insert(transaction, entity);
		}

		/// <summary>
		/// Insert a record in the table #TABLEWITHOUTPREFIXTABLE# with transction
		/// </summary>
		public Int32 Insert(OleDbTransaction oOleDbTransaction, #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			StringBuilder sbSQL = new StringBuilder();

			
			sbSQL.Append("INSERT INTO #TABLE#\n");
			sbSQL.Append("(\n");
				<allfieldslessprimarykey>
			sbSQL.Append("#COMMABEFORE#[#FIELD#]\n");
				</allfieldslessprimarykey>
			sbSQL.Append(")\n");
			sbSQL.Append("VALUES\n");
			sbSQL.Append("(\n");
				<allfieldslessprimarykey>
			if(entity.#FIELD# != null)
				sbSQL.Append("#COMMABEFORE#'" + entity.#FIELD#.ToString() + "'\n");
			else
				sbSQL.Append("#COMMABEFORE#NULL\n");
				</allfieldslessprimarykey>
			sbSQL.Append(")\n");		
		
			return Convert.ToInt32(SQLHelperAccess.ExecuteNonQueryIdentity(sbSQL.ToString(), oOleDbTransaction));
		}

		/// <summary>
		/// Update a record in the table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		public void Update(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			OleDbTransaction transaction = null;
			
			Update(transaction, entity);
		}

		/// <summary>
		/// Update a record in the table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>
		public void Update(OleDbTransaction oOleDbTransaction, #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			StringBuilder sbSQL = new StringBuilder();
			
			sbSQL.Append("UPDATE \n");
			sbSQL.Append("	#TABLE# \n");
			sbSQL.Append("SET \n");
				<allfieldslessprimarykey>
				if(entity.#FIELD# != null)
					sbSQL.Append("	#COMMABEFORE#[#FIELD#] = '" + entity.#FIELD#.ToString() + "'\n");
				else
					sbSQL.Append("	#COMMABEFORE#[#FIELD#] = NULL \n");
					
				</allfieldslessprimarykey>
			sbSQL.Append("WHERE \n");
			sbSQL.Append("	[#PRIMARYKEY#] = " + entity.#PRIMARYKEY#.ToString() + " \n");

			SQLHelperAccess.ExecuteNonQuery(sbSQL.ToString(), oOleDbTransaction);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		public void Delete(Int32 pId)
		{
			OleDbTransaction transaction = null;

			Delete(transaction, pId);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>
		public void Delete(OleDbTransaction oOleDbTransaction, Int32 pId)
		{
			StringBuilder sbSQL = new StringBuilder();
			
			sbSQL.Append("DELETE FROM #TABLE# \n");
			sbSQL.Append("WHERE [#PRIMARYKEY#] = " + pId.ToString() + " \n");

			SQLHelperAccess.ExecuteNonQuery(sbSQL.ToString(), oOleDbTransaction);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		public void Delete(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			OleDbTransaction transaction = null;

			Delete(transaction, entity);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>
		public void Delete(OleDbTransaction oOleDbTransaction, #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			StringBuilder sbSQL = new StringBuilder();
			StringBuilder sbSQLCriteria = new StringBuilder();
			
			sbSQL.Append("DELETE FROM #TABLE# \n");
			sbSQL.Append("WHERE \n");
			
			if(entity.#PRIMARYKEY# != null)
				sbSQLCriteria.Append("[#PRIMARYKEY#] = " + entity.#PRIMARYKEY#.ToString() + "\n");
				
			<allfieldslessprimarykey>
			if(entity.#FIELD# != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[#FIELD#] = '" + entity.#FIELD#.ToString() + "'\n");
			}
			
			</allfieldslessprimarykey>       
				
			if(sbSQLCriteria.Length > 0)
				sbSQL.Append(sbSQLCriteria.ToString());
			
			SQLHelperAccess.ExecuteNonQuery(sbSQL.ToString(), oOleDbTransaction);
		}
	}// Close out the class and namespace
}
