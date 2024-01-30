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
    public sealed partial class rotinaDAL : BaseDAL<rotina>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public rotina Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idrotina", pId);

			return base.ReturnUnique("rotina_Select", parameters);
		}

		/// <summary>
		/// Select and returns all records from table rotina
		/// </summary>
		override public List<rotina> SelectList()
		{
			return base.ReturnList("rotina_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public rotina Select(rotina entity)
		{
			return base.ReturnUnique("rotina_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
		/// </summary>
		override public List<rotina> SelectList(rotina entity)
		{
			return base.ReturnList("rotina_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table rotina
		/// </summary>
		override public Int32 Insert(rotina entity)
		{
			NpgsqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table rotina with transction
		/// </summary>
		override public Int32 Insert(rotina entity, NpgsqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("rotina_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table rotina
		/// </summary>
		override public void Update(rotina entity)
		{
			NpgsqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table rotina with transaction
		/// </summary>
		override public void Update(rotina entity, NpgsqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("rotina_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table rotina
		/// </summary>
		override public void Delete(Int32 pId)
		{
			NpgsqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table rotina with transaction
		/// </summary>
		override public void Delete(Int32 pId, NpgsqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idrotina", pId); 

			SQLHelper.ExecuteNonQuery("rotina_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(rotina entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "@idrotina", entity.idrotina); 
			}

			SQLHelper.AddParameter(ref parameters, "@nome", entity.nome);
			SQLHelper.AddParameter(ref parameters, "@decricao", entity.decricao);
			SQLHelper.AddParameter(ref parameters, "@datacriacao", entity.datacriacao);
			SQLHelper.AddParameter(ref parameters, "@usuario", entity.usuario);
			SQLHelper.AddParameter(ref parameters, "@funcional", entity.funcional);
			SQLHelper.AddParameter(ref parameters, "@ativo", entity.ativo);
			SQLHelper.AddParameter(ref parameters, "@apelido", entity.apelido);

			return parameters;
		}	
    }
}

