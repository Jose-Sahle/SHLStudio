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
	public sealed partial class EMAILBLL
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
		/// Select a record by ID from table EMAIL
		/// </summary>");
		public EMAIL Select(Int32 pidEMAIL)
		{		
			EMAILDAL oEMAILDAL = new EMAILDAL();

			return oEMAILDAL.Select(pidEMAIL);
		}
	
		/// <summary>
		/// Select all records
		/// </summary>");
		public List<EMAIL> SelectList()
		{		
			EMAIL entity = new EMAIL();
			EMAILDAL oEMAILDAL = new EMAILDAL();
			
			return oEMAILDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public EMAIL Select(EMAIL entity)
		{		
			EMAILDAL oEMAILDAL = new EMAILDAL();
			
			return oEMAILDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<EMAIL> SelectList(EMAIL entity)
		{		
			EMAILDAL oEMAILDAL = new EMAILDAL();
			
			return oEMAILDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table EMAIL
		/// </summary>");
		public Int32 Insert(EMAIL entity)
		{		
			EMAILDAL oEMAILDAL = new EMAILDAL();
		   
			return oEMAILDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table EMAIL inside a transaction
		/// </summary>");
		public Int32 Insert(EMAIL entity, SqlTransaction oSqlTransaction)
		{		
			EMAILDAL oEMAILDAL = new EMAILDAL();
			
			return oEMAILDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table EMAIL
		/// </summary>");
		public void Update(EMAIL entity)
		{		
			EMAILDAL oEMAILDAL = new EMAILDAL();
			
			oEMAILDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table EMAIL with transaction
		/// </summary>");
		public void Update(EMAIL entity, SqlTransaction oSqlTransaction)
		{		
			EMAILDAL oEMAILDAL = new EMAILDAL();
			
			oEMAILDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table EMAIL
		/// </summary>");
		public void Delete(Int32 id)
		{		
			EMAILDAL oEMAILDAL = new EMAILDAL();
			
			oEMAILDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table EMAIL with transaction
		/// </summary>");
		public void Delete(Int32 id, SqlTransaction oSqlTransaction)
		{		
			EMAILDAL oEMAILDAL = new EMAILDAL();
			
			oEMAILDAL.Delete(id, oSqlTransaction);
		}
	}
}
