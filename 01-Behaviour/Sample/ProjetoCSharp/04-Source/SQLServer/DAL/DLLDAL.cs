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
	public sealed partial class DLLDAL : BaseDAL<DLL>
	{
		/// <summary>
		/// Seleciona um Registro por ID da Tabela #TABELADAL#
		/// </summary>
		override public DLL Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idDLL", pId);

			return base.ReturnUnique("DLL_Select", parameters);
		}


		/// <summary>
		/// Select and return all records from table DLL
		/// </summary>
		override public List<DLL> SelectList()
		{
			return base.ReturnList("DLL_Select");
		}

		/// <summary>
		/// Select a record with a filter
		/// </summary>
		override public DLL Select(DLL entity)
		{
			return base.ReturnUnique("DLL_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records with a filter
		/// </summary>
		override public List<DLL> SelectList(DLL entity)
		{
			return base.ReturnList("DLL_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table DLL
		/// </summary>
		override public Int32 Insert(DLL entity)
		{
			SqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table DLL with transction
		/// </summary>
		override public Int32 Insert(DLL entity, SqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("DLL_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table DLL
		/// </summary>
		override public void Update(DLL entity)
		{
			SqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table DLL with transaction
		/// </summary>
		override public void Update(DLL entity, SqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("DLL_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table DLL
		/// </summary>
		override public void Delete(Int32 pId)
		{
			SqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table DLL with transaction
		/// </summary>
		override public void Delete(Int32 pId, SqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idDLL", pId); 

			SQLHelper.ExecuteNonQuery("DLL_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(DLL entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "@idDLL", entity.idDLL); 
			}

			SQLHelper.AddParameter(ref parameters, "@idRotina", entity.idRotina);
			SQLHelper.AddParameter(ref parameters, "@Ordem", entity.Ordem);
			SQLHelper.AddParameter(ref parameters, "@Nome", entity.Nome);
			SQLHelper.AddParameter(ref parameters, "@Assembly", entity.Assembly);
			SQLHelper.AddParameter(ref parameters, "@Dependencia", entity.Dependencia);

			return parameters;
		}
	}// Close out the class and namespace
}

