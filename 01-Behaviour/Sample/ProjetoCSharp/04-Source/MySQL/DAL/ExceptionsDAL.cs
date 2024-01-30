/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:16
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using MySql.Data.MySqlClient;

using GPRotina.Entity;

namespace GPRotina.DAL
{
    public sealed partial class exceptionsDAL : BaseDAL<exceptions>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public exceptions Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_idExceptions", pId);

			return base.ReturnUnique("exceptions_Select", parameters);
		}


		/// <summary>
		/// Select and returns all records from table exceptions
		/// </summary>
		override public List<exceptions> SelectList()
		{
			return base.ReturnList("exceptions_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public exceptions Select(exceptions entity)
		{
			return base.ReturnUnique("exceptions_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
		/// </summary>
		override public List<exceptions> SelectList(exceptions entity)
		{
			return base.ReturnList("exceptions_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table exceptions
		/// </summary>
		override public Int32 Insert(exceptions entity)
		{
			MySqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table exceptions with transction
		/// </summary>
		override public Int32 Insert(exceptions entity, MySqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("exceptions_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table exceptions
		/// </summary>
		override public void Update(exceptions entity)
		{
			MySqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table exceptions with transaction
		/// </summary>
		override public void Update(exceptions entity, MySqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("exceptions_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table exceptions
		/// </summary>
		override public void Delete(Int32 pId)
		{
			MySqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table exceptions with transaction
		/// </summary>
		override public void Delete(Int32 pId, MySqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_idExceptions", pId); 

			SQLHelper.ExecuteNonQuery("exceptions_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(exceptions entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "var_idExceptions", entity.idExceptions); 
			}

			SQLHelper.AddParameter(ref parameters, "var_idRotina", entity.idRotina);
			SQLHelper.AddParameter(ref parameters, "var_Tentativa", entity.Tentativa);
			SQLHelper.AddParameter(ref parameters, "var_Intervalo", entity.Intervalo);
			SQLHelper.AddParameter(ref parameters, "var_EnviarEmail", entity.EnviarEmail);
			SQLHelper.AddParameter(ref parameters, "var_EnviarUltimoEmail", entity.EnviarUltimoEmail);

			return parameters;
		}	
    }
}

