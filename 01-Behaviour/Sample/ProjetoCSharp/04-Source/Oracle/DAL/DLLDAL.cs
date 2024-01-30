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
    public sealed partial class DLLDAL : BaseDAL<DLL>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public DLL Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDDLL", pId);

			return base.ReturnUnique("DLL_Select", parameters);
		}

		/// <summary>
		/// Select and returns all records from table DLL
		/// </summary>
		override public List<DLL> SelectList()
		{
			return base.ReturnList("DLL_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public DLL Select(DLL entity)
		{
			return base.ReturnUnique("DLL_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
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
			OracleTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table DLL with transction
		/// </summary>
		override public Int32 Insert(DLL entity, OracleTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("DLL_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table DLL
		/// </summary>
		override public void Update(DLL entity)
		{
			OracleTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table DLL with transaction
		/// </summary>
		override public void Update(DLL entity, OracleTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("DLL_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table DLL
		/// </summary>
		override public void Delete(Int32 pId)
		{
			OracleTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table DLL with transaction
		/// </summary>
		override public void Delete(Int32 pId, OracleTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDDLL", pId); 

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
				SQLHelper.AddParameter(ref parameters, "var_IDDLL", entity.IDDLL); 
			}

			SQLHelper.AddParameter(ref parameters, "var_IDROTINA", entity.IDROTINA);
			SQLHelper.AddParameter(ref parameters, "var_ORDEM", entity.ORDEM);
			SQLHelper.AddParameter(ref parameters, "var_NOME", entity.NOME);
			SQLHelper.AddParameter(ref parameters, "var_ASSEMBLY", entity.ASSEMBLY);
			SQLHelper.AddParameter(ref parameters, "var_DEPENDENCIA", entity.DEPENDENCIA);

			return parameters;
		}	
    }
}

