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
	public sealed partial class EXCEPTIONSDAL : BaseDAL<EXCEPTIONS>
	{
		/// <summary>
		/// Seleciona um Registro por ID da Tabela #TABELADAL#
		/// </summary>
		override public EXCEPTIONS Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idExceptions", pId);

			return base.ReturnUnique("EXCEPTIONS_Select", parameters);
		}


		/// <summary>
		/// Select and return all records from table EXCEPTIONS
		/// </summary>
		override public List<EXCEPTIONS> SelectList()
		{
			return base.ReturnList("EXCEPTIONS_Select");
		}

		/// <summary>
		/// Select a record with a filter
		/// </summary>
		override public EXCEPTIONS Select(EXCEPTIONS entity)
		{
			return base.ReturnUnique("EXCEPTIONS_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records with a filter
		/// </summary>
		override public List<EXCEPTIONS> SelectList(EXCEPTIONS entity)
		{
			return base.ReturnList("EXCEPTIONS_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table EXCEPTIONS
		/// </summary>
		override public Int32 Insert(EXCEPTIONS entity)
		{
			SqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table EXCEPTIONS with transction
		/// </summary>
		override public Int32 Insert(EXCEPTIONS entity, SqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("EXCEPTIONS_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table EXCEPTIONS
		/// </summary>
		override public void Update(EXCEPTIONS entity)
		{
			SqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table EXCEPTIONS with transaction
		/// </summary>
		override public void Update(EXCEPTIONS entity, SqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("EXCEPTIONS_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table EXCEPTIONS
		/// </summary>
		override public void Delete(Int32 pId)
		{
			SqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table EXCEPTIONS with transaction
		/// </summary>
		override public void Delete(Int32 pId, SqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idExceptions", pId); 

			SQLHelper.ExecuteNonQuery("EXCEPTIONS_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(EXCEPTIONS entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "@idExceptions", entity.idExceptions); 
			}

			SQLHelper.AddParameter(ref parameters, "@idRotina", entity.idRotina);
			SQLHelper.AddParameter(ref parameters, "@Tentativa", entity.Tentativa);
			SQLHelper.AddParameter(ref parameters, "@Intervalo", entity.Intervalo);
			SQLHelper.AddParameter(ref parameters, "@EnviarEmail", entity.EnviarEmail);
			SQLHelper.AddParameter(ref parameters, "@EnviarUltimoEmail", entity.EnviarUltimoEmail);

			return parameters;
		}
	}// Close out the class and namespace
}

