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
		override public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@#PRIMARYKEY#", pId);

			return base.ReturnUnique("#TABLEWITHOUTPREFIXTABLE#_Select", parameters);
		}


		/// <summary>
		/// Select and return all records from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		override public List<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#> SelectList()
		{
			return base.ReturnList("#TABLEWITHOUTPREFIXTABLE#_Select");
		}

		/// <summary>
		/// Select a record with a filter
		/// </summary>
		override public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# Select(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			return base.ReturnUnique("#TABLEWITHOUTPREFIXTABLE#_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records with a filter
		/// </summary>
		override public List<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#> SelectList(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			return base.ReturnList("#TABLEWITHOUTPREFIXTABLE#_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		override public Int32 Insert(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			SqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table #TABLEWITHOUTPREFIXTABLE# with transction
		/// </summary>
		override public Int32 Insert(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity, SqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("#TABLEWITHOUTPREFIXTABLE#_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		override public void Update(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			SqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>
		override public void Update(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity, SqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("#TABLEWITHOUTPREFIXTABLE#_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		override public void Delete(Int32 pId)
		{
			SqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>
		override public void Delete(Int32 pId, SqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@#PRIMARYKEY#", pId); 

			SQLHelper.ExecuteNonQuery("#TABLEWITHOUTPREFIXTABLE#_Delete", oSqlTransaction, parameters);
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
