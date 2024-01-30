/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using Oracle.DataAccess.Client; // ODP.NET Oracle managed provider
using Oracle.DataAccess.Types; 

using #NAMESPACEENTITY#;

namespace #NAMESPACEDAL#
{
    public sealed partial class #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# : BaseDAL<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_#PRIMARYKEY#", pId);

			return base.ReturnUnique("#TABLEWITHOUTPREFIXTABLE#_Select", parameters);
		}

		/// <summary>
		/// Select and returns all records from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		override public List<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#> SelectList()
		{
			return base.ReturnList("#TABLEWITHOUTPREFIXTABLE#_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# Select(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			return base.ReturnUnique("#TABLEWITHOUTPREFIXTABLE#_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
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
			OracleTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table #TABLEWITHOUTPREFIXTABLE# with transction
		/// </summary>
		override public Int32 Insert(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity, OracleTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("#TABLEWITHOUTPREFIXTABLE#_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		override public void Update(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			OracleTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>
		override public void Update(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity, OracleTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("#TABLEWITHOUTPREFIXTABLE#_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		override public void Delete(Int32 pId)
		{
			OracleTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>
		override public void Delete(Int32 pId, OracleTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_#PRIMARYKEY#", pId); 

			SQLHelper.ExecuteNonQuery("#TABLEWITHOUTPREFIXTABLE#_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>
		override public void Delete(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{
			OracleTransaction transaction = null;

			Delete(entity, transaction);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>
		override public void Delete(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity, OracleTransaction oSqlTransaction)
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
				SQLHelper.AddParameter(ref parameters, "var_#PRIMARYKEY#", entity.#PRIMARYKEY#); 
			}

			<allfieldslessprimarykey>
			SQLHelper.AddParameter(ref parameters, "var_#FIELD#", entity.#FIELD#);
			</allfieldslessprimarykey>

			return parameters;
		}	
    }
}
