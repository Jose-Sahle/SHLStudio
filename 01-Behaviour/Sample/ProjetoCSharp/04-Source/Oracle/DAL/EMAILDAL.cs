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
    public sealed partial class EMAILDAL : BaseDAL<EMAIL>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public EMAIL Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDEMAIL", pId);

			return base.ReturnUnique("EMAIL_Select", parameters);
		}

		/// <summary>
		/// Select and returns all records from table EMAIL
		/// </summary>
		override public List<EMAIL> SelectList()
		{
			return base.ReturnList("EMAIL_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public EMAIL Select(EMAIL entity)
		{
			return base.ReturnUnique("EMAIL_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
		/// </summary>
		override public List<EMAIL> SelectList(EMAIL entity)
		{
			return base.ReturnList("EMAIL_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table EMAIL
		/// </summary>
		override public Int32 Insert(EMAIL entity)
		{
			OracleTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table EMAIL with transction
		/// </summary>
		override public Int32 Insert(EMAIL entity, OracleTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("EMAIL_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table EMAIL
		/// </summary>
		override public void Update(EMAIL entity)
		{
			OracleTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table EMAIL with transaction
		/// </summary>
		override public void Update(EMAIL entity, OracleTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("EMAIL_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table EMAIL
		/// </summary>
		override public void Delete(Int32 pId)
		{
			OracleTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table EMAIL with transaction
		/// </summary>
		override public void Delete(Int32 pId, OracleTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDEMAIL", pId); 

			SQLHelper.ExecuteNonQuery("EMAIL_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(EMAIL entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "var_IDEMAIL", entity.IDEMAIL); 
			}

			SQLHelper.AddParameter(ref parameters, "var_IDROTINA", entity.IDROTINA);
			SQLHelper.AddParameter(ref parameters, "var_FROMEMAIL", entity.FROMEMAIL);
			SQLHelper.AddParameter(ref parameters, "var_TOEMAIL", entity.TOEMAIL);
			SQLHelper.AddParameter(ref parameters, "var_SUBJECTEMAIL", entity.SUBJECTEMAIL);
			SQLHelper.AddParameter(ref parameters, "var_TYPEEMAIL", entity.TYPEEMAIL);
			SQLHelper.AddParameter(ref parameters, "var_BODYEMAIL", entity.BODYEMAIL);
			SQLHelper.AddParameter(ref parameters, "var_CLASSIFICACAO", entity.CLASSIFICACAO);
			SQLHelper.AddParameter(ref parameters, "var_ANEXO", entity.ANEXO);
			SQLHelper.AddParameter(ref parameters, "var_ATIVO", entity.ATIVO);

			return parameters;
		}	
    }
}

