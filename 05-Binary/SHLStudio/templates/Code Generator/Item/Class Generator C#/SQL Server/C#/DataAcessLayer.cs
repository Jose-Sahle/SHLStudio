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

using #NAMESPACEENTITY#;

namespace #NAMESPACEDAL#
{
	public sealed partial class #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# : BaseDAL<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#>
	{
		/// <summary>
		/// Seleciona um Registro por ID da Tabela #TABELADAL#
		/// </summary>
		public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@#PRIMARYKEY#", pId);

			return base.ReturnUnique("#TABLEWITHOUTPREFIXTABLE#_Select", parameters);
		}

		/// <summary>
		/// Select and return all records from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		public List<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#> SelectList()
		{
			return base.ReturnList("#TABLEWITHOUTPREFIXTABLE#_Select");		
		}

		/// <summary>
		/// Select a record with a filter
		/// </summary>
		public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# Select(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			return base.ReturnUnique("#TABLEWITHOUTPREFIXTABLE#_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records with a filter
		/// </summary>
		public List<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#> SelectList(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			return base.ReturnList("#TABLEWITHOUTPREFIXTABLE#_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		public Int32 Insert(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			SqlTransaction transaction = null;

			return Insert(transaction, entity);
		}

		/// <summary>
		/// Insert a record in the table #TABLEWITHOUTPREFIXTABLE# with transction
		/// </summary>
		public Int32 Insert(SqlTransaction oSqlTransaction, #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("#TABLEWITHOUTPREFIXTABLE#_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
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
			SQLHelper.ExecuteNonQuery("#TABLEWITHOUTPREFIXTABLE#_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		public void Delete(Int32 pId)
		{
			SqlTransaction transaction = null;

			Delete(transaction, pId);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>
		public void Delete(SqlTransaction oSqlTransaction, Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@#PRIMARYKEY#", pId); 

			SQLHelper.ExecuteNonQuery("#TABLEWITHOUTPREFIXTABLE#_Delete", oSqlTransaction, parameters);
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
			SQLHelper.ExecuteNonQuery("#TABLEWITHOUTPREFIXTABLE#_DeleteList", oSqlTransaction, CreateParameters(entity, true));
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
	}// Close out the class and namespace
}
