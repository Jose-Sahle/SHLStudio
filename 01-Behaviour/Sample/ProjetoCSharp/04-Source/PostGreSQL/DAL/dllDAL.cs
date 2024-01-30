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
    public sealed partial class dllDAL : BaseDAL<dll>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public dll Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@iddll", pId);

			return base.ReturnUnique("dll_Select", parameters);
		}

		/// <summary>
		/// Select and returns all records from table dll
		/// </summary>
		override public List<dll> SelectList()
		{
			return base.ReturnList("dll_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public dll Select(dll entity)
		{
			return base.ReturnUnique("dll_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
		/// </summary>
		override public List<dll> SelectList(dll entity)
		{
			return base.ReturnList("dll_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table dll
		/// </summary>
		override public Int32 Insert(dll entity)
		{
			NpgsqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table dll with transction
		/// </summary>
		override public Int32 Insert(dll entity, NpgsqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("dll_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table dll
		/// </summary>
		override public void Update(dll entity)
		{
			NpgsqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table dll with transaction
		/// </summary>
		override public void Update(dll entity, NpgsqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("dll_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table dll
		/// </summary>
		override public void Delete(Int32 pId)
		{
			NpgsqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table dll with transaction
		/// </summary>
		override public void Delete(Int32 pId, NpgsqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@iddll", pId); 

			SQLHelper.ExecuteNonQuery("dll_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(dll entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "@iddll", entity.iddll); 
			}

			SQLHelper.AddParameter(ref parameters, "@idrotina", entity.idrotina);
			SQLHelper.AddParameter(ref parameters, "@ordem", entity.ordem);
			SQLHelper.AddParameter(ref parameters, "@nome", entity.nome);
			SQLHelper.AddParameter(ref parameters, "@assembly", entity.assembly);
			SQLHelper.AddParameter(ref parameters, "@dependencia", entity.dependencia);

			return parameters;
		}	
    }
}

