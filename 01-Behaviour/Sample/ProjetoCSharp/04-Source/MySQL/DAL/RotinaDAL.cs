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
    public sealed partial class rotinaDAL : BaseDAL<rotina>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public rotina Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_idRotina", pId);

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
			MySqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table rotina with transction
		/// </summary>
		override public Int32 Insert(rotina entity, MySqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("rotina_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table rotina
		/// </summary>
		override public void Update(rotina entity)
		{
			MySqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table rotina with transaction
		/// </summary>
		override public void Update(rotina entity, MySqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("rotina_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table rotina
		/// </summary>
		override public void Delete(Int32 pId)
		{
			MySqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table rotina with transaction
		/// </summary>
		override public void Delete(Int32 pId, MySqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_idRotina", pId); 

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
				SQLHelper.AddParameter(ref parameters, "var_idRotina", entity.idRotina); 
			}

			SQLHelper.AddParameter(ref parameters, "var_Nome", entity.Nome);
			SQLHelper.AddParameter(ref parameters, "var_Decricao", entity.Decricao);
			SQLHelper.AddParameter(ref parameters, "var_DataCriacao", entity.DataCriacao);
			SQLHelper.AddParameter(ref parameters, "var_Usuario", entity.Usuario);
			SQLHelper.AddParameter(ref parameters, "var_Funcional", entity.Funcional);
			SQLHelper.AddParameter(ref parameters, "var_Ativo", entity.Ativo);
			SQLHelper.AddParameter(ref parameters, "var_Apelido", entity.Apelido);

			return parameters;
		}	
    }
}

