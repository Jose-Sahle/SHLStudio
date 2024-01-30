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
    public sealed partial class emailDAL : BaseDAL<email>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public email Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_idEMAIL", pId);

			return base.ReturnUnique("email_Select", parameters);
		}


		/// <summary>
		/// Select and returns all records from table email
		/// </summary>
		override public List<email> SelectList()
		{
			return base.ReturnList("email_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public email Select(email entity)
		{
			return base.ReturnUnique("email_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
		/// </summary>
		override public List<email> SelectList(email entity)
		{
			return base.ReturnList("email_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table email
		/// </summary>
		override public Int32 Insert(email entity)
		{
			MySqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table email with transction
		/// </summary>
		override public Int32 Insert(email entity, MySqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("email_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table email
		/// </summary>
		override public void Update(email entity)
		{
			MySqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table email with transaction
		/// </summary>
		override public void Update(email entity, MySqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("email_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table email
		/// </summary>
		override public void Delete(Int32 pId)
		{
			MySqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table email with transaction
		/// </summary>
		override public void Delete(Int32 pId, MySqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_idEMAIL", pId); 

			SQLHelper.ExecuteNonQuery("email_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(email entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "var_idEMAIL", entity.idEMAIL); 
			}

			SQLHelper.AddParameter(ref parameters, "var_idRotina", entity.idRotina);
			SQLHelper.AddParameter(ref parameters, "var_FROM", entity.FROM);
			SQLHelper.AddParameter(ref parameters, "var_TO", entity.TO);
			SQLHelper.AddParameter(ref parameters, "var_SUBJECT", entity.SUBJECT);
			SQLHelper.AddParameter(ref parameters, "var_TYPE", entity.TYPE);
			SQLHelper.AddParameter(ref parameters, "var_BODY", entity.BODY);
			SQLHelper.AddParameter(ref parameters, "var_Classificacao", entity.Classificacao);
			SQLHelper.AddParameter(ref parameters, "var_Anexo", entity.Anexo);
			SQLHelper.AddParameter(ref parameters, "var_Ativo", entity.Ativo);

			return parameters;
		}	
    }
}

