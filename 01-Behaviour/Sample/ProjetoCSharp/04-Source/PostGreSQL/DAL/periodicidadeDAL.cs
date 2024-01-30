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
    public sealed partial class periodicidadeDAL : BaseDAL<periodicidade>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public periodicidade Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idperiodicidade", pId);

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
			NpgsqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table periodicidade with transction
		/// </summary>
		override public Int32 Insert(periodicidade entity, NpgsqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("periodicidade_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table periodicidade
		/// </summary>
		override public void Update(periodicidade entity)
		{
			NpgsqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table periodicidade with transaction
		/// </summary>
		override public void Update(periodicidade entity, NpgsqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("periodicidade_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table periodicidade
		/// </summary>
		override public void Delete(Int32 pId)
		{
			NpgsqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table periodicidade with transaction
		/// </summary>
		override public void Delete(Int32 pId, NpgsqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idperiodicidade", pId); 

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
				SQLHelper.AddParameter(ref parameters, "@idperiodicidade", entity.idperiodicidade); 
			}

			SQLHelper.AddParameter(ref parameters, "@idrotina", entity.idrotina);
			SQLHelper.AddParameter(ref parameters, "@tipo", entity.tipo);
			SQLHelper.AddParameter(ref parameters, "@parametro", entity.parametro);

			return parameters;
		}	
    }
}

