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
	public sealed partial class DLLParametrosDAL : BaseDAL<DLLParametros>
	{
		/// <summary>
		/// Seleciona um Registro por ID da Tabela #TABELADAL#
		/// </summary>
		override public DLLParametros Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idDLLParametros", pId);

			return base.ReturnUnique("DLLParametros_Select", parameters);
		}


		/// <summary>
		/// Select and return all records from table DLLParametros
		/// </summary>
		override public List<DLLParametros> SelectList()
		{
			return base.ReturnList("DLLParametros_Select");
		}

		/// <summary>
		/// Select a record with a filter
		/// </summary>
		override public DLLParametros Select(DLLParametros entity)
		{
			return base.ReturnUnique("DLLParametros_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records with a filter
		/// </summary>
		override public List<DLLParametros> SelectList(DLLParametros entity)
		{
			return base.ReturnList("DLLParametros_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table DLLParametros
		/// </summary>
		override public Int32 Insert(DLLParametros entity)
		{
			SqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table DLLParametros with transction
		/// </summary>
		override public Int32 Insert(DLLParametros entity, SqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("DLLParametros_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table DLLParametros
		/// </summary>
		override public void Update(DLLParametros entity)
		{
			SqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table DLLParametros with transaction
		/// </summary>
		override public void Update(DLLParametros entity, SqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("DLLParametros_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table DLLParametros
		/// </summary>
		override public void Delete(Int32 pId)
		{
			SqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table DLLParametros with transaction
		/// </summary>
		override public void Delete(Int32 pId, SqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idDLLParametros", pId); 

			SQLHelper.ExecuteNonQuery("DLLParametros_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(DLLParametros entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "@idDLLParametros", entity.idDLLParametros); 
			}

			SQLHelper.AddParameter(ref parameters, "@idDLL", entity.idDLL);
			SQLHelper.AddParameter(ref parameters, "@Nome", entity.Nome);
			SQLHelper.AddParameter(ref parameters, "@Valor", entity.Valor);
			SQLHelper.AddParameter(ref parameters, "@Tipo", entity.Tipo);
			SQLHelper.AddParameter(ref parameters, "@Formato", entity.Formato);

			return parameters;
		}
	}// Close out the class and namespace
}

