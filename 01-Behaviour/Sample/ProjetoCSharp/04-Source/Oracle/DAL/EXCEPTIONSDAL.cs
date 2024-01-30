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
    public sealed partial class EXCEPTIONSDAL : BaseDAL<EXCEPTIONS>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public EXCEPTIONS Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDEXCEPTIONS", pId);

			return base.ReturnUnique("EXCEPTIONS_Select", parameters);
		}

		/// <summary>
		/// Select and returns all records from table EXCEPTIONS
		/// </summary>
		override public List<EXCEPTIONS> SelectList()
		{
			return base.ReturnList("EXCEPTIONS_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public EXCEPTIONS Select(EXCEPTIONS entity)
		{
			return base.ReturnUnique("EXCEPTIONS_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
		/// </summary>
		override public List<EXCEPTIONS> SelectList(EXCEPTIONS entity)
		{
			return base.ReturnList("EXCEPTIONS_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table EXCEPTIONS
		/// </summary>
		override public Int32 Insert(EXCEPTIONS entity)
		{
			OracleTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table EXCEPTIONS with transction
		/// </summary>
		override public Int32 Insert(EXCEPTIONS entity, OracleTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("EXCEPTIONS_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table EXCEPTIONS
		/// </summary>
		override public void Update(EXCEPTIONS entity)
		{
			OracleTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table EXCEPTIONS with transaction
		/// </summary>
		override public void Update(EXCEPTIONS entity, OracleTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("EXCEPTIONS_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table EXCEPTIONS
		/// </summary>
		override public void Delete(Int32 pId)
		{
			OracleTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table EXCEPTIONS with transaction
		/// </summary>
		override public void Delete(Int32 pId, OracleTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDEXCEPTIONS", pId); 

			SQLHelper.ExecuteNonQuery("EXCEPTIONS_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(EXCEPTIONS entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "var_IDEXCEPTIONS", entity.IDEXCEPTIONS); 
			}

			SQLHelper.AddParameter(ref parameters, "var_IDROTINA", entity.IDROTINA);
			SQLHelper.AddParameter(ref parameters, "var_TENTATIVA", entity.TENTATIVA);
			SQLHelper.AddParameter(ref parameters, "var_INTERVALO", entity.INTERVALO);
			SQLHelper.AddParameter(ref parameters, "var_ENVIAREMAIL", entity.ENVIAREMAIL);
			SQLHelper.AddParameter(ref parameters, "var_ENVIARULTIMOEMAIL", entity.ENVIARULTIMOEMAIL);

			return parameters;
		}	
    }
}

