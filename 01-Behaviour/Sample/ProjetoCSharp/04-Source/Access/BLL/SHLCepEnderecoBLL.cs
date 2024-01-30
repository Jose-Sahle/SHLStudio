/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 10/09/2014 19:45:47
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Data.OleDb;

using SHL.CEP.Entity;
using SHL.CEP.DAL;

namespace SHL.CEP.BLL
{ 
	public sealed partial class SHLCepEnderecoBLL
	{
		/// <summary>
		/// Select a record by ID from table SHLCepEndereco
		/// </summary>");
		public SHLCepEndereco SelectSHLCepEndereco(Int32 pidshlcependereco)
		{		
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();

			return oSHLCepEnderecoDAL.Select(pidshlcependereco);
		}
	
		/// <summary>
		/// Select all records
		/// </summary>");
		public List<SHLCepEndereco> SelectListSHLCepEndereco()
		{		
			SHLCepEndereco entity = new SHLCepEndereco();
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();
			
			return oSHLCepEnderecoDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public SHLCepEndereco SelectSHLCepEndereco(SHLCepEndereco entity)
		{		
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();
			
			return oSHLCepEnderecoDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<SHLCepEndereco> SelectListSHLCepEndereco(SHLCepEndereco entity)
		{		
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();
			
			return oSHLCepEnderecoDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table SHLCepEndereco
		/// </summary>");
		public Int32 InsertSHLCepEndereco(SHLCepEndereco entity)
		{		
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();
		   
			return oSHLCepEnderecoDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table SHLCepEndereco inside a transaction
		/// </summary>");
		public Int32 InsertSHLCepEndereco(OleDbTransaction oOleDbTransaction,  SHLCepEndereco entity)
		{		
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();
			
			return oSHLCepEnderecoDAL.Insert(oOleDbTransaction, entity);
		}

		/// <summary>
		/// Update a record in the table SHLCepEndereco
		/// </summary>");
		public void UpdateSHLCepEndereco(SHLCepEndereco entity)
		{		
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();
			
			oSHLCepEnderecoDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table SHLCepEndereco with transaction
		/// </summary>");
		public void UpdateSHLCepEndereco(OleDbTransaction oOleDbTransaction, SHLCepEndereco entity)
		{		
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();
			
			oSHLCepEnderecoDAL.Update(oOleDbTransaction, entity);
		}

		/// <summary>
		/// Delete a record from table SHLCepEndereco
		/// </summary>");
		public void DeleteSHLCepEndereco(Int32 id)
		{		
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();
			
			oSHLCepEnderecoDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table SHLCepEndereco with transaction
		/// </summary>");
		public void DeleteSHLCepEndereco(OleDbTransaction oOleDbTransaction, Int32 id)
		{		
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();
			
			oSHLCepEnderecoDAL.Delete(oOleDbTransaction, id);
		}
		
		/// <summary>
		/// Delete a record from table SHLCepEndereco
		/// </summary>");
		public void DeleteSHLCepEndereco(SHLCepEndereco entity)
		{		
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();
			
			oSHLCepEnderecoDAL.Delete(entity);
		}

		/// <summary>
		/// Delete a record from table SHLCepEndereco with transaction
		/// </summary>");
		public void DeleteSHLCepEndereco(OleDbTransaction oOleDbTransaction, SHLCepEndereco entity)
		{		
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();
			
			oSHLCepEnderecoDAL.Delete(oOleDbTransaction, entity);
		}		
		public OleDbTransaction GetTransaction()
		{
			OleDbTransaction transaction = null;
			
			SHLCepEnderecoDAL oSHLCepEnderecoDAL = new SHLCepEnderecoDAL();

			transaction = oSHLCepEnderecoDAL.GetTransaction();

			return transaction;
		}			
	}
}
