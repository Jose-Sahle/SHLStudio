/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:41
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using Oracle.DataAccess.Client; // ODP.NET Oracle managed provider
using Oracle.DataAccess.Types; 

using GPRotina.Entity;
using GPRotina.DAL;
                
namespace GPRotina.BLL
{ 
    public sealed partial class DLLBLL
    {
		/// <summary>
		/// Select a record by ID from table DLL
		/// </summary>");
		public DLL Select(Int32 pIDDLL)
		{		
			DLLDAL oDLLDAL = new DLLDAL();

			return oDLLDAL.Select(pIDDLL);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<DLL> SelectList()
		{		
			DLL entity = new DLL();
			DLLDAL oDLLDAL = new DLLDAL();
			
			return oDLLDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public DLL Select(DLL entity)
		{		
			DLLDAL oDLLDAL = new DLLDAL();
			
			return oDLLDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<DLL> SelectList(DLL entity)
		{		
			DLLDAL oDLLDAL = new DLLDAL();
			
			return oDLLDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table DLL
		/// </summary>");
		public Int32 Insert(DLL entity)
		{		
			DLLDAL oDLLDAL = new DLLDAL();
		   
			return oDLLDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table DLL inside a transaction
		/// </summary>");
		public Int32 Insert(DLL entity, OracleTransaction oSqlTransaction)
		{		
			DLLDAL oDLLDAL = new DLLDAL();
			
			return oDLLDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table DLL
		/// </summary>");
		public void Update(DLL entity)
		{		
			DLLDAL oDLLDAL = new DLLDAL();
			
			oDLLDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table DLL with transaction
		/// </summary>");
		public void Update(DLL entity, OracleTransaction oSqlTransaction)
		{		
			DLLDAL oDLLDAL = new DLLDAL();
			
			oDLLDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table DLL
		/// </summary>");
		public void Delete(Int32 id)
		{		
			DLLDAL oDLLDAL = new DLLDAL();
			
			oDLLDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table DLL with transaction
		/// </summary>");
		public void Delete(Int32 id, OracleTransaction oSqlTransaction)
		{		
			DLLDAL oDLLDAL = new DLLDAL();
			
			oDLLDAL.Delete(id, oSqlTransaction);
		}
	}
}
