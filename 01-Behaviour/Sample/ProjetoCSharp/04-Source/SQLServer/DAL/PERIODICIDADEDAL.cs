/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 26/01/2024 09:10:52
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;

using GPRotina.Entity;

namespace GPRotina.DAL
{
	public sealed partial class PERIODICIDADEDAL : BaseDAL<PERIODICIDADE>
	{
		/// <summary>
		/// Seleciona um Registro por ID da Tabela #TABELADAL#
		/// </summary>
		override public PERIODICIDADE Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idPeriodicidade", pId);

			return base.ReturnUnique("PERIODICIDADE_Select", parameters);
		}


		/// <summary>
		/// Select and return all records from table PERIODICIDADE
		/// </summary>
		override public List<PERIODICIDADE> SelectList()
		{
			return base.ReturnList("PERIODICIDADE_Select");
		}

		/// <summary>
		/// Select a record with a filter
		/// </summary>
		override public PERIODICIDADE Select(PERIODICIDADE entity)
		{
			return base.ReturnUnique("PERIODICIDADE_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records with a filter
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
			SqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table PERIODICIDADE with transction
		/// </summary>
		override public Int32 Insert(PERIODICIDADE entity, SqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("PERIODICIDADE_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table PERIODICIDADE
		/// </summary>
		override public void Update(PERIODICIDADE entity)
		{
			SqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table PERIODICIDADE with transaction
		/// </summary>
		override public void Update(PERIODICIDADE entity, SqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("PERIODICIDADE_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table PERIODICIDADE
		/// </summary>
		override public void Delete(Int32 pId)
		{
			SqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table PERIODICIDADE with transaction
		/// </summary>
		override public void Delete(Int32 pId, SqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idPeriodicidade", pId); 

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
				SQLHelper.AddParameter(ref parameters, "@idPeriodicidade", entity.idPeriodicidade); 
			}

			SQLHelper.AddParameter(ref parameters, "@idRotina", entity.idRotina);
			SQLHelper.AddParameter(ref parameters, "@Tipo", entity.Tipo);
			SQLHelper.AddParameter(ref parameters, "@Parametro", entity.Parametro);

			return parameters;
		}
	}// Close out the class and namespace
}

