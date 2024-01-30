/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 26/01/2024 09:10:53
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;

using GPRotina.Entity;

namespace GPRotina.DAL
{
	public sealed partial class AGENDAMENTODAL : BaseDAL<AGENDAMENTO>
	{
		/// <summary>
		/// Seleciona um Registro por ID da Tabela #TABELADAL#
		/// </summary>
		override public AGENDAMENTO Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idAgendamento", pId);

			return base.ReturnUnique("AGENDAMENTO_Select", parameters);
		}


		/// <summary>
		/// Select and return all records from table AGENDAMENTO
		/// </summary>
		override public List<AGENDAMENTO> SelectList()
		{
			return base.ReturnList("AGENDAMENTO_Select");
		}

		/// <summary>
		/// Select a record with a filter
		/// </summary>
		override public AGENDAMENTO Select(AGENDAMENTO entity)
		{
			return base.ReturnUnique("AGENDAMENTO_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records with a filter
		/// </summary>
		override public List<AGENDAMENTO> SelectList(AGENDAMENTO entity)
		{
			return base.ReturnList("AGENDAMENTO_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table AGENDAMENTO
		/// </summary>
		override public Int32 Insert(AGENDAMENTO entity)
		{
			SqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table AGENDAMENTO with transction
		/// </summary>
		override public Int32 Insert(AGENDAMENTO entity, SqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("AGENDAMENTO_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table AGENDAMENTO
		/// </summary>
		override public void Update(AGENDAMENTO entity)
		{
			SqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table AGENDAMENTO with transaction
		/// </summary>
		override public void Update(AGENDAMENTO entity, SqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("AGENDAMENTO_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table AGENDAMENTO
		/// </summary>
		override public void Delete(Int32 pId)
		{
			SqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table AGENDAMENTO with transaction
		/// </summary>
		override public void Delete(Int32 pId, SqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idAgendamento", pId); 

			SQLHelper.ExecuteNonQuery("AGENDAMENTO_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(AGENDAMENTO entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "@idAgendamento", entity.idAgendamento); 
			}

			SQLHelper.AddParameter(ref parameters, "@idRotina", entity.idRotina);
			SQLHelper.AddParameter(ref parameters, "@DataInicio", entity.DataInicio);
			SQLHelper.AddParameter(ref parameters, "@HoraInicio", entity.HoraInicio);
			SQLHelper.AddParameter(ref parameters, "@DataFim", entity.DataFim);
			SQLHelper.AddParameter(ref parameters, "@HoraFim", entity.HoraFim);
			SQLHelper.AddParameter(ref parameters, "@Intervalo", entity.Intervalo);
			SQLHelper.AddParameter(ref parameters, "@Repeticao", entity.Repeticao);
			SQLHelper.AddParameter(ref parameters, "@assembly", entity.assembly);

			return parameters;
		}
	}// Close out the class and namespace
}

