/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 26/01/2024 09:10:52
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Data.SqlClient;

using GPRotina.Entity;
using GPRotina.DAL;

namespace GPRotina.BLL
{ 
	public sealed partial class DLLParametrosBLL
	{		
		// codigo alte 1	
		// dasdfseer
	
		public void GetMRS()
		{
		
		}

		public void GetGuru()
		{
		
		}
		
		//begin 
		
		//end
		
		/// <summary>
		/// Select a record by ID from table DLLParametros
		/// </summary>");
		public DLLParametros Select(Int32 pidDLLParametros)
		{		
			DLLParametrosDAL oDLLParametrosDAL = new DLLParametrosDAL();

			return oDLLParametrosDAL.Select(pidDLLParametros);
		}
	
		/// <summary>
		/// Select all records
		/// </summary>");
		public List<DLLParametros> SelectList()
		{		
			DLLParametros entity = new DLLParametros();
			DLLParametrosDAL oDLLParametrosDAL = new DLLParametrosDAL();
			
			return oDLLParametrosDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public DLLParametros Select(DLLParametros entity)
		{		
			DLLParametrosDAL oDLLParametrosDAL = new DLLParametrosDAL();
			
			return oDLLParametrosDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<DLLParametros> SelectList(DLLParametros entity)
		{		
			DLLParametrosDAL oDLLParametrosDAL = new DLLParametrosDAL();
			
			return oDLLParametrosDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table DLLParametros
		/// </summary>");
		public Int32 Insert(DLLParametros entity)
		{		
			DLLParametrosDAL oDLLParametrosDAL = new DLLParametrosDAL();
		   
			return oDLLParametrosDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table DLLParametros inside a transaction
		/// </summary>");
		public Int32 Insert(DLLParametros entity, SqlTransaction oSqlTransaction)
		{		
			DLLParametrosDAL oDLLParametrosDAL = new DLLParametrosDAL();
			
			return oDLLParametrosDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table DLLParametros
		/// </summary>");
		public void Update(DLLParametros entity)
		{		
			DLLParametrosDAL oDLLParametrosDAL = new DLLParametrosDAL();
			
			oDLLParametrosDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table DLLParametros with transaction
		/// </summary>");
		public void Update(DLLParametros entity, SqlTransaction oSqlTransaction)
		{		
			DLLParametrosDAL oDLLParametrosDAL = new DLLParametrosDAL();
			
			oDLLParametrosDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table DLLParametros
		/// </summary>");
		public void Delete(Int32 id)
		{		
			DLLParametrosDAL oDLLParametrosDAL = new DLLParametrosDAL();
			
			oDLLParametrosDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table DLLParametros with transaction
		/// </summary>");
		public void Delete(Int32 id, SqlTransaction oSqlTransaction)
		{		
			DLLParametrosDAL oDLLParametrosDAL = new DLLParametrosDAL();
			
			oDLLParametrosDAL.Delete(id, oSqlTransaction);
		}
	}
}
