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
    public sealed partial class agendamentoDAL : BaseDAL<agendamento>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public agendamento Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_idAgendamento", pId);

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
			MySqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table agendamento with transction
		/// </summary>
		override public Int32 Insert(agendamento entity, MySqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("agendamento_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table agendamento
		/// </summary>
		override public void Update(agendamento entity)
		{
			MySqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table agendamento with transaction
		/// </summary>
		override public void Update(agendamento entity, MySqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("agendamento_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table agendamento
		/// </summary>
		override public void Delete(Int32 pId)
		{
			MySqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table agendamento with transaction
		/// </summary>
		override public void Delete(Int32 pId, MySqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_idAgendamento", pId); 

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
				SQLHelper.AddParameter(ref parameters, "var_idAgendamento", entity.idAgendamento); 
			}

			SQLHelper.AddParameter(ref parameters, "var_idRotina", entity.idRotina);
			SQLHelper.AddParameter(ref parameters, "var_DataInicio", entity.DataInicio);
			SQLHelper.AddParameter(ref parameters, "var_HoraInicio", entity.HoraInicio);
			SQLHelper.AddParameter(ref parameters, "var_DataFim", entity.DataFim);
			SQLHelper.AddParameter(ref parameters, "var_HoraFim", entity.HoraFim);
			SQLHelper.AddParameter(ref parameters, "var_Intervalo", entity.Intervalo);
			SQLHelper.AddParameter(ref parameters, "var_Repeticao", entity.Repeticao);

			return parameters;
		}	
    }
}

