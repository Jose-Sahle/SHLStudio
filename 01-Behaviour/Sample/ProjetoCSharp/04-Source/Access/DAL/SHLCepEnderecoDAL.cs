/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 10/09/2014 19:45:47
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Text;
using System.Data.OleDb;

using SHL.CEP.Entity;

namespace SHL.CEP.DAL
{
	public sealed partial class SHLCepEnderecoDAL : BaseAccessDAL<SHLCepEndereco>
	{
		/// <summary>
		/// Seleciona um Registro por ID da Tabela #TABELADAL#
		/// </summary>
		public SHLCepEndereco Select(Int32 pId)
		{
			StringBuilder sbSQL = new StringBuilder();
			
			sbSQL.Append("SELECT\n");
			sbSQL.Append("[idshlcependereco],\n");
			sbSQL.Append("[BAIRRO],\n");
			sbSQL.Append("[CEP],\n");
			sbSQL.Append("[CIDADE],\n");
			sbSQL.Append("[ENDERECO],\n");
			sbSQL.Append("[ESTADO]\n");
			sbSQL.Append("FROM \n");
			sbSQL.Append("[SHLCepEndereco] \n");
			sbSQL.Append("WHERE \n");
			sbSQL.Append("[idshlcependereco] = " + pId.ToString());

			return base.ReturnUnique(sbSQL.ToString());
		}


		/// <summary>
		/// Select and return all records from table SHLCepEndereco
		/// </summary>
		public List<SHLCepEndereco> SelectList()
		{
			StringBuilder sbSQL = new StringBuilder();
			
			sbSQL.Append("SELECT\n");
			sbSQL.Append("[idshlcependereco],\n");
			sbSQL.Append("[BAIRRO],\n");
			sbSQL.Append("[CEP],\n");
			sbSQL.Append("[CIDADE],\n");
			sbSQL.Append("[ENDERECO],\n");
			sbSQL.Append("[ESTADO]\n");
			sbSQL.Append("FROM \n");
			sbSQL.Append("[SHLCepEndereco] \n");
			
			return base.ReturnList(sbSQL.ToString());		
		}

		/// <summary>
		/// Select a record with a filter
		/// </summary>
		public SHLCepEndereco Select(SHLCepEndereco entity)
		{
			StringBuilder sbSQL = new StringBuilder();
			StringBuilder sbSQLCriteria  = new StringBuilder();
			
			sbSQL.Append("SELECT\n");
			sbSQL.Append("[idshlcependereco],\n");
			sbSQL.Append("[BAIRRO],\n");
			sbSQL.Append("[CEP],\n");
			sbSQL.Append("[CIDADE],\n");
			sbSQL.Append("[ENDERECO],\n");
			sbSQL.Append("[ESTADO]\n");
			sbSQL.Append("FROM \n");
			sbSQL.Append("[SHLCepEndereco] \n");
			sbSQL.Append("WHERE \n");
			
			if(entity.idshlcependereco != null)
				sbSQLCriteria.Append("[idshlcependereco] = " + entity.idshlcependereco.ToString() + "\n");
				
			if(entity.BAIRRO != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[BAIRRO] = '" + entity.BAIRRO.ToString() + "'\n");
			}
			
			if(entity.CEP != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[CEP] = '" + entity.CEP.ToString() + "'\n");
			}
			
			if(entity.CIDADE != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[CIDADE] = '" + entity.CIDADE.ToString() + "'\n");
			}
			
			if(entity.ENDERECO != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[ENDERECO] = '" + entity.ENDERECO.ToString() + "'\n");
			}
			
			if(entity.ESTADO != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[ESTADO] = '" + entity.ESTADO.ToString() + "'\n");
			}
			
				
			if(sbSQLCriteria.Length > 0)
				sbSQL.Append(sbSQLCriteria.ToString());
		
			return base.ReturnUnique(sbSQL.ToString());
		}

		/// <summary>
		/// Select some records with a filter
		/// </summary>
		public List<SHLCepEndereco> SelectList(SHLCepEndereco entity)
		{
			StringBuilder sbSQL = new StringBuilder();
			StringBuilder sbSQLCriteria  = new StringBuilder();
			
			sbSQL.Append("SELECT\n");
			sbSQL.Append("[idshlcependereco],\n");
			sbSQL.Append("[BAIRRO],\n");
			sbSQL.Append("[CEP],\n");
			sbSQL.Append("[CIDADE],\n");
			sbSQL.Append("[ENDERECO],\n");
			sbSQL.Append("[ESTADO]\n");
			sbSQL.Append("FROM \n");
			sbSQL.Append("[SHLCepEndereco] \n");
			sbSQL.Append("WHERE \n");
			
			if(entity.idshlcependereco != null)
				sbSQLCriteria.Append("[idshlcependereco] = " + entity.idshlcependereco.ToString() + "\n");
				
			if(entity.BAIRRO != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[BAIRRO] = '" + entity.BAIRRO.ToString() + "'\n");
			}
			
			if(entity.CEP != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[CEP] = '" + entity.CEP.ToString() + "'\n");
			}
			
			if(entity.CIDADE != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[CIDADE] = '" + entity.CIDADE.ToString() + "'\n");
			}
			
			if(entity.ENDERECO != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[ENDERECO] = '" + entity.ENDERECO.ToString() + "'\n");
			}
			
			if(entity.ESTADO != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[ESTADO] = '" + entity.ESTADO.ToString() + "'\n");
			}
			
				
			if(sbSQLCriteria.Length > 0)
				sbSQL.Append(sbSQLCriteria.ToString());

			return base.ReturnList(sbSQL.ToString());
		}

		/// <summary>
		/// Insert a record in the table SHLCepEndereco
		/// </summary>
		public Int32 Insert(SHLCepEndereco entity)
		{
			OleDbTransaction transaction = null;

			return Insert(transaction, entity);
		}

		/// <summary>
		/// Insert a record in the table SHLCepEndereco with transction
		/// </summary>
		public Int32 Insert(OleDbTransaction oOleDbTransaction, SHLCepEndereco entity)
		{
			StringBuilder sbSQL = new StringBuilder();

			
			sbSQL.Append("INSERT INTO SHLCepEndereco\n");
			sbSQL.Append("(\n");
			sbSQL.Append("[BAIRRO]\n");
			sbSQL.Append(",[CEP]\n");
			sbSQL.Append(",[CIDADE]\n");
			sbSQL.Append(",[ENDERECO]\n");
			sbSQL.Append(",[ESTADO]\n");
			sbSQL.Append(")\n");
			sbSQL.Append("VALUES\n");
			sbSQL.Append("(\n");
			if(entity.BAIRRO != null)
				sbSQL.Append("'" + entity.BAIRRO.ToString() + "'\n");
			else
				sbSQL.Append("NULL\n");
			if(entity.CEP != null)
				sbSQL.Append(",'" + entity.CEP.ToString() + "'\n");
			else
				sbSQL.Append(",NULL\n");
			if(entity.CIDADE != null)
				sbSQL.Append(",'" + entity.CIDADE.ToString() + "'\n");
			else
				sbSQL.Append(",NULL\n");
			if(entity.ENDERECO != null)
				sbSQL.Append(",'" + entity.ENDERECO.ToString() + "'\n");
			else
				sbSQL.Append(",NULL\n");
			if(entity.ESTADO != null)
				sbSQL.Append(",'" + entity.ESTADO.ToString() + "'\n");
			else
				sbSQL.Append(",NULL\n");
			sbSQL.Append(")\n");		
		
			return Convert.ToInt32(SQLHelperAccess.ExecuteNonQueryIdentity(sbSQL.ToString(), oOleDbTransaction));
		}

		/// <summary>
		/// Update a record in the table SHLCepEndereco
		/// </summary>
		public void Update(SHLCepEndereco entity)
		{
			OleDbTransaction transaction = null;
			
			Update(transaction, entity);
		}

		/// <summary>
		/// Update a record in the table SHLCepEndereco with transaction
		/// </summary>
		public void Update(OleDbTransaction oOleDbTransaction, SHLCepEndereco entity)
		{
			StringBuilder sbSQL = new StringBuilder();
			
			sbSQL.Append("UPDATE \n");
			sbSQL.Append("	SHLCepEndereco \n");
			sbSQL.Append("SET \n");
				if(entity.BAIRRO != null)
					sbSQL.Append("	[BAIRRO] = '" + entity.BAIRRO.ToString() + "'\n");
				else
					sbSQL.Append("	[BAIRRO] = NULL \n");
					
				if(entity.CEP != null)
					sbSQL.Append("	,[CEP] = '" + entity.CEP.ToString() + "'\n");
				else
					sbSQL.Append("	,[CEP] = NULL \n");
					
				if(entity.CIDADE != null)
					sbSQL.Append("	,[CIDADE] = '" + entity.CIDADE.ToString() + "'\n");
				else
					sbSQL.Append("	,[CIDADE] = NULL \n");
					
				if(entity.ENDERECO != null)
					sbSQL.Append("	,[ENDERECO] = '" + entity.ENDERECO.ToString() + "'\n");
				else
					sbSQL.Append("	,[ENDERECO] = NULL \n");
					
				if(entity.ESTADO != null)
					sbSQL.Append("	,[ESTADO] = '" + entity.ESTADO.ToString() + "'\n");
				else
					sbSQL.Append("	,[ESTADO] = NULL \n");
					
			sbSQL.Append("WHERE \n");
			sbSQL.Append("	[idshlcependereco] = " + entity.idshlcependereco.ToString() + " \n");

			SQLHelperAccess.ExecuteNonQuery(sbSQL.ToString(), oOleDbTransaction);
		}

		/// <summary>
		/// Delete a record from table SHLCepEndereco
		/// </summary>
		public void Delete(Int32 pId)
		{
			OleDbTransaction transaction = null;

			Delete(transaction, pId);
		}

		/// <summary>
		/// Delete a record from table SHLCepEndereco with transaction
		/// </summary>
		public void Delete(OleDbTransaction oOleDbTransaction, Int32 pId)
		{
			StringBuilder sbSQL = new StringBuilder();
			
			sbSQL.Append("DELETE FROM SHLCepEndereco \n");
			sbSQL.Append("WHERE [idshlcependereco] = " + pId.ToString() + " \n");

			SQLHelperAccess.ExecuteNonQuery(sbSQL.ToString(), oOleDbTransaction);
		}

		/// <summary>
		/// Delete a record from table SHLCepEndereco
		/// </summary>
		public void Delete(SHLCepEndereco entity)
		{
			OleDbTransaction transaction = null;

			Delete(transaction, entity);
		}

		/// <summary>
		/// Delete a record from table SHLCepEndereco with transaction
		/// </summary>
		public void Delete(OleDbTransaction oOleDbTransaction, SHLCepEndereco entity)
		{
			StringBuilder sbSQL = new StringBuilder();
			StringBuilder sbSQLCriteria = new StringBuilder();
			
			sbSQL.Append("DELETE FROM SHLCepEndereco \n");
			sbSQL.Append("WHERE \n");
			
			if(entity.idshlcependereco != null)
				sbSQLCriteria.Append("[idshlcependereco] = " + entity.idshlcependereco.ToString() + "\n");
				
			if(entity.BAIRRO != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[BAIRRO] = '" + entity.BAIRRO.ToString() + "'\n");
			}
			
			if(entity.CEP != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[CEP] = '" + entity.CEP.ToString() + "'\n");
			}
			
			if(entity.CIDADE != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[CIDADE] = '" + entity.CIDADE.ToString() + "'\n");
			}
			
			if(entity.ENDERECO != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[ENDERECO] = '" + entity.ENDERECO.ToString() + "'\n");
			}
			
			if(entity.ESTADO != null)
			{
				if(sbSQLCriteria.Length > 0)
					sbSQLCriteria.Append("AND ");
					
				sbSQLCriteria.Append("[ESTADO] = '" + entity.ESTADO.ToString() + "'\n");
			}
			
				
			if(sbSQLCriteria.Length > 0)
				sbSQL.Append(sbSQLCriteria.ToString());
			
			SQLHelperAccess.ExecuteNonQuery(sbSQL.ToString(), oOleDbTransaction);
		}
	}// Close out the class and namespace
}

