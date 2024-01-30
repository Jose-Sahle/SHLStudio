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
    public sealed partial class PERIODICIDADEDAL : BaseDAL<PERIODICIDADE>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public PERIODICIDADE Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDPERIODICIDADE", pId);

			return base.ReturnUnique("PERIODICIDADE_Select", parameters);
		}

		/// <summary>
		/// Select and returns all records from table PERIODICIDADE
		/// </summary>
		override public List<PERIODICIDADE> SelectList()
		{
			return base.ReturnList("PERIODICIDADE_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public PERIODICIDADE Select(PERIODICIDADE entity)
		{
			return base.ReturnUnique("PERIODICIDADE_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
		/// </summary>
		override public List<PERIODICIDADE> SelectList(PERIODICIDADE entity)
		{
			return base.ReturnList("PERIODICIDADE_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table PERIODICIDADE
		/// </summary>
		override public Int32 Insert(PERIODICIDADE entity)
		{
			OracleTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table PERIODICIDADE with transction
		/// </summary>
		override public Int32 Insert(PERIODICIDADE entity, OracleTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("PERIODICIDADE_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table PERIODICIDADE
		/// </summary>
		override public void Update(PERIODICIDADE entity)
		{
			OracleTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table PERIODICIDADE with transaction
		/// </summary>
		override public void Update(PERIODICIDADE entity, OracleTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("PERIODICIDADE_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table PERIODICIDADE
		/// </summary>
		override public void Delete(Int32 pId)
		{
			OracleTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table PERIODICIDADE with transaction
		/// </summary>
		override public void Delete(Int32 pId, OracleTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDPERIODICIDADE", pId); 

			SQLHelper.ExecuteNonQuery("PERIODICIDADE_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(PERIODICIDADE entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "var_IDPERIODICIDADE", entity.IDPERIODICIDADE); 
			}

			SQLHelper.AddParameter(ref parameters, "var_IDROTINA", entity.IDROTINA);
			SQLHelper.AddParameter(ref parameters, "var_TIPO", entity.TIPO);
			SQLHelper.AddParameter(ref parameters, "var_PARAMETRO", entity.PARAMETRO);

			return parameters;
		}	
    }
}

