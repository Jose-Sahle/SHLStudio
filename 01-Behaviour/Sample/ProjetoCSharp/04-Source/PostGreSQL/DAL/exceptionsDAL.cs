/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:39
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using Npgsql;

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
			ArrayList parameters = SQLHelper.AddParameter("@idexceptions", pId);

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
			NpgsqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table exceptions with transction
		/// </summary>
		override public Int32 Insert(exceptions entity, NpgsqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("exceptions_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table exceptions
		/// </summary>
		override public void Update(exceptions entity)
		{
			NpgsqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table exceptions with transaction
		/// </summary>
		override public void Update(exceptions entity, NpgsqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("exceptions_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table exceptions
		/// </summary>
		override public void Delete(Int32 pId)
		{
			NpgsqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table exceptions with transaction
		/// </summary>
		override public void Delete(Int32 pId, NpgsqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idexceptions", pId); 

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
				SQLHelper.AddParameter(ref parameters, "@idexceptions", entity.idexceptions); 
			}

			SQLHelper.AddParameter(ref parameters, "@idrotina", entity.idrotina);
			SQLHelper.AddParameter(ref parameters, "@tentativa", entity.tentativa);
			SQLHelper.AddParameter(ref parameters, "@intervalo", entity.intervalo);
			SQLHelper.AddParameter(ref parameters, "@enviaremail", entity.enviaremail);
			SQLHelper.AddParameter(ref parameters, "@enviarultimoemail", entity.enviarultimoemail);

			return parameters;
		}	
    }
}

