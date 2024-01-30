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
    public sealed partial class emailDAL : BaseDAL<email>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public email Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idemail", pId);

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
			NpgsqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table email with transction
		/// </summary>
		override public Int32 Insert(email entity, NpgsqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("email_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table email
		/// </summary>
		override public void Update(email entity)
		{
			NpgsqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table email with transaction
		/// </summary>
		override public void Update(email entity, NpgsqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("email_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table email
		/// </summary>
		override public void Delete(Int32 pId)
		{
			NpgsqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table email with transaction
		/// </summary>
		override public void Delete(Int32 pId, NpgsqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idemail", pId); 

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
				SQLHelper.AddParameter(ref parameters, "@idemail", entity.idemail); 
			}

			SQLHelper.AddParameter(ref parameters, "@idrotina", entity.idrotina);
			SQLHelper.AddParameter(ref parameters, "@from", entity.from);
			SQLHelper.AddParameter(ref parameters, "@to", entity.to);
			SQLHelper.AddParameter(ref parameters, "@subject", entity.subject);
			SQLHelper.AddParameter(ref parameters, "@type", entity.type);
			SQLHelper.AddParameter(ref parameters, "@body", entity.body);
			SQLHelper.AddParameter(ref parameters, "@classificacao", entity.classificacao);
			SQLHelper.AddParameter(ref parameters, "@anexo", entity.anexo);
			SQLHelper.AddParameter(ref parameters, "@ativo", entity.ativo);

			return parameters;
		}	
    }
}

