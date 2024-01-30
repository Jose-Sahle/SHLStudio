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
    public sealed partial class agendamentoDAL : BaseDAL<agendamento>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public agendamento Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idagendamento", pId);

			return base.ReturnUnique("agendamento_Select", parameters);
		}

		/// <summary>
		/// Select and returns all records from table agendamento
		/// </summary>
		override public List<agendamento> SelectList()
		{
			return base.ReturnList("agendamento_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public agendamento Select(agendamento entity)
		{
			return base.ReturnUnique("agendamento_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
		/// </summary>
		override public List<agendamento> SelectList(agendamento entity)
		{
			return base.ReturnList("agendamento_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table agendamento
		/// </summary>
		override public Int32 Insert(agendamento entity)
		{
			NpgsqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table agendamento with transction
		/// </summary>
		override public Int32 Insert(agendamento entity, NpgsqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("agendamento_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table agendamento
		/// </summary>
		override public void Update(agendamento entity)
		{
			NpgsqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table agendamento with transaction
		/// </summary>
		override public void Update(agendamento entity, NpgsqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("agendamento_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table agendamento
		/// </summary>
		override public void Delete(Int32 pId)
		{
			NpgsqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table agendamento with transaction
		/// </summary>
		override public void Delete(Int32 pId, NpgsqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idagendamento", pId); 

			SQLHelper.ExecuteNonQuery("agendamento_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(agendamento entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "@idagendamento", entity.idagendamento); 
			}

			SQLHelper.AddParameter(ref parameters, "@idrotina", entity.idrotina);
			SQLHelper.AddParameter(ref parameters, "@datainicio", entity.datainicio);
			SQLHelper.AddParameter(ref parameters, "@horainicio", entity.horainicio);
			SQLHelper.AddParameter(ref parameters, "@datafim", entity.datafim);
			SQLHelper.AddParameter(ref parameters, "@horafim", entity.horafim);
			SQLHelper.AddParameter(ref parameters, "@intervalo", entity.intervalo);
			SQLHelper.AddParameter(ref parameters, "@repeticao", entity.repeticao);

			return parameters;
		}	
    }
}

