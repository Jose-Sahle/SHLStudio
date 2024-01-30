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
    public sealed partial class DLLPARAMETROSDAL : BaseDAL<DLLPARAMETROS>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public DLLPARAMETROS Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDDLLPARAMETROS", pId);

			return base.ReturnUnique("DLLPARAMETROS_Select", parameters);
		}

		/// <summary>
		/// Select and returns all records from table DLLPARAMETROS
		/// </summary>
		override public List<DLLPARAMETROS> SelectList()
		{
			return base.ReturnList("DLLPARAMETROS_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public DLLPARAMETROS Select(DLLPARAMETROS entity)
		{
			return base.ReturnUnique("DLLPARAMETROS_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
		/// </summary>
		override public List<DLLPARAMETROS> SelectList(DLLPARAMETROS entity)
		{
			return base.ReturnList("DLLPARAMETROS_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table DLLPARAMETROS
		/// </summary>
		override public Int32 Insert(DLLPARAMETROS entity)
		{
			OracleTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table DLLPARAMETROS with transction
		/// </summary>
		override public Int32 Insert(DLLPARAMETROS entity, OracleTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("DLLPARAMETROS_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table DLLPARAMETROS
		/// </summary>
		override public void Update(DLLPARAMETROS entity)
		{
			OracleTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table DLLPARAMETROS with transaction
		/// </summary>
		override public void Update(DLLPARAMETROS entity, OracleTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("DLLPARAMETROS_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table DLLPARAMETROS
		/// </summary>
		override public void Delete(Int32 pId)
		{
			OracleTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table DLLPARAMETROS with transaction
		/// </summary>
		override public void Delete(Int32 pId, OracleTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDDLLPARAMETROS", pId); 

			SQLHelper.ExecuteNonQuery("DLLPARAMETROS_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(DLLPARAMETROS entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "var_IDDLLPARAMETROS", entity.IDDLLPARAMETROS); 
			}

			SQLHelper.AddParameter(ref parameters, "var_IDDLL", entity.IDDLL);
			SQLHelper.AddParameter(ref parameters, "var_NOME", entity.NOME);
			SQLHelper.AddParameter(ref parameters, "var_VALOR", entity.VALOR);
			SQLHelper.AddParameter(ref parameters, "var_TIPO", entity.TIPO);
			SQLHelper.AddParameter(ref parameters, "var_FORMATO", entity.FORMATO);

			return parameters;
		}	
    }
}

