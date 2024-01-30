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
	public sealed partial class EMAILDAL : BaseDAL<EMAIL>
	{
		/// <summary>
		/// Seleciona um Registro por ID da Tabela #TABELADAL#
		/// </summary>
		override public EMAIL Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idEMAIL", pId);

			return base.ReturnUnique("EMAIL_Select", parameters);
		}


		/// <summary>
		/// Select and return all records from table EMAIL
		/// </summary>
		override public List<EMAIL> SelectList()
		{
			return base.ReturnList("EMAIL_Select");
		}

		/// <summary>
		/// Select a record with a filter
		/// </summary>
		override public EMAIL Select(EMAIL entity)
		{
			return base.ReturnUnique("EMAIL_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records with a filter
		/// </summary>
		override public List<EMAIL> SelectList(EMAIL entity)
		{
			return base.ReturnList("EMAIL_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table EMAIL
		/// </summary>
		override public Int32 Insert(EMAIL entity)
		{
			SqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table EMAIL with transction
		/// </summary>
		override public Int32 Insert(EMAIL entity, SqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("EMAIL_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table EMAIL
		/// </summary>
		override public void Update(EMAIL entity)
		{
			SqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table EMAIL with transaction
		/// </summary>
		override public void Update(EMAIL entity, SqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("EMAIL_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table EMAIL
		/// </summary>
		override public void Delete(Int32 pId)
		{
			SqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table EMAIL with transaction
		/// </summary>
		override public void Delete(Int32 pId, SqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idEMAIL", pId); 

			SQLHelper.ExecuteNonQuery("EMAIL_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(EMAIL entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "@idEMAIL", entity.idEMAIL); 
			}

			SQLHelper.AddParameter(ref parameters, "@idRotina", entity.idRotina);
			SQLHelper.AddParameter(ref parameters, "@FROM", entity.FROM);
			SQLHelper.AddParameter(ref parameters, "@TO", entity.TO);
			SQLHelper.AddParameter(ref parameters, "@SUBJECT", entity.SUBJECT);
			SQLHelper.AddParameter(ref parameters, "@TYPE", entity.TYPE);
			SQLHelper.AddParameter(ref parameters, "@BODY", entity.BODY);
			SQLHelper.AddParameter(ref parameters, "@Classificacao", entity.Classificacao);
			SQLHelper.AddParameter(ref parameters, "@Anexo", entity.Anexo);
			SQLHelper.AddParameter(ref parameters, "@Ativo", entity.Ativo);

			return parameters;
		}
	}// Close out the class and namespace
}

