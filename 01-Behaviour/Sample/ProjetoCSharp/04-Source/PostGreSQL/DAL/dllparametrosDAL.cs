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
    public sealed partial class dllparametrosDAL : BaseDAL<dllparametros>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public dllparametros Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@iddllparametros", pId);

			return base.ReturnUnique("dllparametros_Select", parameters);
		}

		/// <summary>
		/// Select and returns all records from table dllparametros
		/// </summary>
		override public List<dllparametros> SelectList()
		{
			return base.ReturnList("dllparametros_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public dllparametros Select(dllparametros entity)
		{
			return base.ReturnUnique("dllparametros_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
		/// </summary>
		override public List<dllparametros> SelectList(dllparametros entity)
		{
			return base.ReturnList("dllparametros_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table dllparametros
		/// </summary>
		override public Int32 Insert(dllparametros entity)
		{
			NpgsqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table dllparametros with transction
		/// </summary>
		override public Int32 Insert(dllparametros entity, NpgsqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("dllparametros_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table dllparametros
		/// </summary>
		override public void Update(dllparametros entity)
		{
			NpgsqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table dllparametros with transaction
		/// </summary>
		override public void Update(dllparametros entity, NpgsqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("dllparametros_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table dllparametros
		/// </summary>
		override public void Delete(Int32 pId)
		{
			NpgsqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table dllparametros with transaction
		/// </summary>
		override public void Delete(Int32 pId, NpgsqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@iddllparametros", pId); 

			SQLHelper.ExecuteNonQuery("dllparametros_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(dllparametros entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "@iddllparametros", entity.iddllparametros); 
			}

			SQLHelper.AddParameter(ref parameters, "@iddll", entity.iddll);
			SQLHelper.AddParameter(ref parameters, "@nome", entity.nome);
			SQLHelper.AddParameter(ref parameters, "@valor", entity.valor);
			SQLHelper.AddParameter(ref parameters, "@tipo", entity.tipo);
			SQLHelper.AddParameter(ref parameters, "@formato", entity.formato);

			return parameters;
		}	
    }
}

