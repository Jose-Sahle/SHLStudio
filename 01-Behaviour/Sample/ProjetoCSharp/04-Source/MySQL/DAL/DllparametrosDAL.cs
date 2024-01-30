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
    public sealed partial class dllparametrosDAL : BaseDAL<dllparametros>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public dllparametros Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_idDLLParametros", pId);

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
			MySqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table dllparametros with transction
		/// </summary>
		override public Int32 Insert(dllparametros entity, MySqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("dllparametros_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table dllparametros
		/// </summary>
		override public void Update(dllparametros entity)
		{
			MySqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table dllparametros with transaction
		/// </summary>
		override public void Update(dllparametros entity, MySqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("dllparametros_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table dllparametros
		/// </summary>
		override public void Delete(Int32 pId)
		{
			MySqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table dllparametros with transaction
		/// </summary>
		override public void Delete(Int32 pId, MySqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_idDLLParametros", pId); 

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
				SQLHelper.AddParameter(ref parameters, "var_idDLLParametros", entity.idDLLParametros); 
			}

			SQLHelper.AddParameter(ref parameters, "var_idDLL", entity.idDLL);
			SQLHelper.AddParameter(ref parameters, "var_Nome", entity.Nome);
			SQLHelper.AddParameter(ref parameters, "var_Valor", entity.Valor);
			SQLHelper.AddParameter(ref parameters, "var_Tipo", entity.Tipo);
			SQLHelper.AddParameter(ref parameters, "var_Formato", entity.Formato);

			return parameters;
		}	
    }
}

