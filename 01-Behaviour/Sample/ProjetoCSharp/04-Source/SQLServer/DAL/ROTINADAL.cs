/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 26/01/2024 09:10:52
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;

using GPRotina.Entity;

namespace GPRotina.DAL
{
	public sealed partial class ROTINADAL : BaseDAL<ROTINA>
	{
		/// <summary>
		/// Seleciona um Registro por ID da Tabela #TABELADAL#
		/// </summary>
		override public ROTINA Select(Int32 pId)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idRotina", pId);

			return base.ReturnUnique("ROTINA_Select", parameters);
		}


		/// <summary>
		/// Select and return all records from table ROTINA
		/// </summary>
		override public List<ROTINA> SelectList()
		{
			return base.ReturnList("ROTINA_Select");
		}

		/// <summary>
		/// Select a record with a filter
		/// </summary>
		override public ROTINA Select(ROTINA entity)
		{
			return base.ReturnUnique("ROTINA_Select", CreateParameters(entity, true));
		}

		/// <summary>
		/// Select some records with a filter
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
			SqlTransaction transaction = null;

			return Insert(entity, transaction);
		}

		/// <summary>
		/// Insert a record in the table ROTINA with transction
		/// </summary>
		override public Int32 Insert(ROTINA entity, SqlTransaction oSqlTransaction)
		{
			return Convert.ToInt32(SQLHelper.ExecuteNonQuery("ROTINA_Insert", oSqlTransaction, CreateParameters(entity, false), "@IdReturn"));
		}

		/// <summary>
		/// Update a record in the table ROTINA
		/// </summary>
		override public void Update(ROTINA entity)
		{
			SqlTransaction transaction = null;
			
			Update(entity, transaction);
		}

		/// <summary>
		/// Update a record in the table ROTINA with transaction
		/// </summary>
		override public void Update(ROTINA entity, SqlTransaction oSqlTransaction)
		{
			SQLHelper.ExecuteNonQuery("ROTINA_Update", oSqlTransaction, CreateParameters(entity, true));
		}

		/// <summary>
		/// Delete a record from table ROTINA
		/// </summary>
		override public void Delete(Int32 pId)
		{
			SqlTransaction transaction = null;

			Delete(pId, transaction);
		}

		/// <summary>
		/// Delete a record from table ROTINA with transaction
		/// </summary>
		override public void Delete(Int32 pId, SqlTransaction oSqlTransaction)
		{
			ArrayList parameters = SQLHelper.AddParameter("@idRotina", pId); 

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
				SQLHelper.AddParameter(ref parameters, "@idRotina", entity.idRotina); 
			}

			SQLHelper.AddParameter(ref parameters, "@Nome", entity.Nome);
			SQLHelper.AddParameter(ref parameters, "@Decricao", entity.Decricao);
			SQLHelper.AddParameter(ref parameters, "@DataCriacao", entity.DataCriacao);
			SQLHelper.AddParameter(ref parameters, "@Usuario", entity.Usuario);
			SQLHelper.AddParameter(ref parameters, "@Funcional", entity.Funcional);
			SQLHelper.AddParameter(ref parameters, "@Ativo", entity.Ativo);
			SQLHelper.AddParameter(ref parameters, "@Apelido", entity.Apelido);
			SQLHelper.AddParameter(ref parameters, "@assembly", entity.assembly);
			SQLHelper.AddParameter(ref parameters, "@TestField", entity.TestField);

			return parameters;
		}
	}// Close out the class and namespace
}

