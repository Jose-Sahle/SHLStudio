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
    public sealed partial class ROTINADAL : BaseDAL<ROTINA>
    {
		/// <summary>
		/// Select a record by ID from table #TABELADAL#
		/// </summary>
		override public ROTINA Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDROTINA", pId);

			return base.ReturnUnique("ROTINA_Select", parameters);
		}

		/// <summary>
		/// Select and returns all records from table ROTINA
		/// </summary>
		override public List<ROTINA> SelectList()
		{
			return base.ReturnList("ROTINA_Select");
		}

		/// <summary>
		/// Select a record by filters
		/// </summary>
		override public ROTINA Select(ROTINA entity)
		{
			return base.ReturnUnique("ROTINA_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records by filters
		/// </summary>
		override public List<ROTINA> SelectList(ROTINA entity)
		{
			return base.ReturnList("ROTINA_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Insert a record in the table ROTINA
		/// </summary>
		override public Int32 Insert(ROTINA entity)
		{
			OracleTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table ROTINA with transction
		/// </summary>
		override public Int32 Insert(ROTINA entity, OracleTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("ROTINA_Insert", oSqlTransaction, CreateParameters(entity, false), "var_IdReturn"));
		}

		/// <summary>
		/// Update a record in the table ROTINA
		/// </summary>
		override public void Update(ROTINA entity)
		{
			OracleTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table ROTINA with transaction
		/// </summary>
		override public void Update(ROTINA entity, OracleTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("ROTINA_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table ROTINA
		/// </summary>
		override public void Delete(Int32 pId)
		{
			OracleTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table ROTINA with transaction
		/// </summary>
		override public void Delete(Int32 pId, OracleTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("var_IDROTINA", pId); 

			SQLHelper.ExecuteNonQuery("ROTINA_Delete", oSqlTransaction, parameters);
		}

		/// <summary>
		/// Carrega os Parametros com ou sem ID
		/// </summary>
		private ArrayList CreateParameters(ROTINA entity, bool pid)
		{
			ArrayList parameters = new ArrayList();

			if (pid) 
			{ 
				SQLHelper.AddParameter(ref parameters, "var_IDROTINA", entity.IDROTINA); 
			}

			SQLHelper.AddParameter(ref parameters, "var_NOME", entity.NOME);
			SQLHelper.AddParameter(ref parameters, "var_DECRICAO", entity.DECRICAO);
			SQLHelper.AddParameter(ref parameters, "var_DATACRIACAO", entity.DATACRIACAO);
			SQLHelper.AddParameter(ref parameters, "var_USUARIO", entity.USUARIO);
			SQLHelper.AddParameter(ref parameters, "var_FUNCIONAL", entity.FUNCIONAL);
			SQLHelper.AddParameter(ref parameters, "var_ATIVO", entity.ATIVO);
			SQLHelper.AddParameter(ref parameters, "var_APELIDO", entity.APELIDO);

			return parameters;
		}	
    }
}

