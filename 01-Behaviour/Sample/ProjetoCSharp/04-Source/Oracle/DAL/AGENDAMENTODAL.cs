/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:41
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using Oracle.DataAccess.Client; // ODP.NET Oracle managed provider
using Oracle.DataAccess.Types; 

using GPRotina.Entity;

namespace GPRotina.DAL
{
    public sealed partial class AGENDAMENTODAL : BaseDAL<AGENDAMENTO>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public AGENDAMENTO Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDAGENDAMENTO", pId);

			return base.ReturnUnique("AGENDAMENTO_Select", parameters);
		}

		/// <summary>
		/// Select and returns all records from table AGENDAMENTO
		/// </summary>
		override public List<AGENDAMENTO> SelectList()
		{
			return base.ReturnList("AGENDAMENTO_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public AGENDAMENTO Select(AGENDAMENTO entity)
		{
			return base.ReturnUnique("AGENDAMENTO_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
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
			OracleTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table AGENDAMENTO with transction
		/// </summary>
		override public Int32 Insert(AGENDAMENTO entity, OracleTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("AGENDAMENTO_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table AGENDAMENTO
		/// </summary>
		override public void Update(AGENDAMENTO entity)
		{
			OracleTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table AGENDAMENTO with transaction
		/// </summary>
		override public void Update(AGENDAMENTO entity, OracleTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("AGENDAMENTO_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table AGENDAMENTO
		/// </summary>
		override public void Delete(Int32 pId)
		{
			OracleTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table AGENDAMENTO with transaction
		/// </summary>
		override public void Delete(Int32 pId, OracleTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDAGENDAMENTO", pId); 

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
				SQLHelper.AddParameter(ref parameters, "var_IDAGENDAMENTO", entity.IDAGENDAMENTO); 
			}

			SQLHelper.AddParameter(ref parameters, "var_IDROTINA", entity.IDROTINA);
			SQLHelper.AddParameter(ref parameters, "var_DATAINICIO", entity.DATAINICIO);
			SQLHelper.AddParameter(ref parameters, "var_HORAINICIO", entity.HORAINICIO);
			SQLHelper.AddParameter(ref parameters, "var_DATAFIM", entity.DATAFIM);
			SQLHelper.AddParameter(ref parameters, "var_HORAFIM", entity.HORAFIM);
			SQLHelper.AddParameter(ref parameters, "var_INTERVALO", entity.INTERVALO);
			SQLHelper.AddParameter(ref parameters, "var_REPETICAO", entity.REPETICAO);

			return parameters;
		}	
    }
}

