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
    public sealed partial class periodicidadeDAL : BaseDAL<periodicidade>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public periodicidade Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_idPeriodicidade", pId);

			return base.ReturnUnique("periodicidade_Select", parameters);
		}


		/// <summary>
		/// Select and returns all records from table periodicidade
		/// </summary>
		override public List<periodicidade> SelectList()
		{
			return base.ReturnList("periodicidade_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public periodicidade Select(periodicidade entity)
		{
			return base.ReturnUnique("periodicidade_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
		/// </summary>
		override public List<periodicidade> SelectList(periodicidade entity)
		{
			return base.ReturnList("periodicidade_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table periodicidade
		/// </summary>
		override public Int32 Insert(periodicidade entity)
		{
			MySqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table periodicidade with transction
		/// </summary>
		override public Int32 Insert(periodicidade entity, MySqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("periodicidade_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table periodicidade
		/// </summary>
		override public void Update(periodicidade entity)
		{
			MySqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table periodicidade with transaction
		/// </summary>
		override public void Update(periodicidade entity, MySqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("periodicidade_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table periodicidade
		/// </summary>
		override public void Delete(Int32 pId)
		{
			MySqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table periodicidade with transaction
		/// </summary>
		override public void Delete(Int32 pId, MySqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_idPeriodicidade", pId); 

			SQLHelper.ExecuteNonQuery("periodicidade_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(periodicidade entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "var_idPeriodicidade", entity.idPeriodicidade); 
			}

			SQLHelper.AddParameter(ref parameters, "var_idRotina", entity.idRotina);
			SQLHelper.AddParameter(ref parameters, "var_Tipo", entity.Tipo);
			SQLHelper.AddParameter(ref parameters, "var_Parametro", entity.Parametro);

			return parameters;
		}	
    }
}

