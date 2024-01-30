/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:15
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using MySql.Data.MySqlClient;

using GPRotina.Entity;
using GPRotina.DAL;
                
namespace GPRotina.BLL
{ 
    public sealed partial class emailBLL
    {
		/// <summary>
		/// Select a record by ID from table email
		/// </summary>");
		public email Select(Int32 pidEMAIL)
		{		
			emailDAL oemailDAL = new emailDAL();

			return oemailDAL.Select(pidEMAIL);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<email> SelectList()
		{		
			email entity = new email();
			emailDAL oemailDAL = new emailDAL();
			
			return oemailDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public email Select(email entity)
		{		
			emailDAL oemailDAL = new emailDAL();
			
			return oemailDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<email> SelectList(email entity)
		{		
			emailDAL oemailDAL = new emailDAL();
			
			return oemailDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table email
		/// </summary>");
		public Int32 Insert(email entity)
		{		
			emailDAL oemailDAL = new emailDAL();
		   
			return oemailDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table email inside a transaction
		/// </summary>");
		public Int32 Insert(email entity, MySqlTransaction oSqlTransaction)
		{		
			emailDAL oemailDAL = new emailDAL();
			
			return oemailDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table email
		/// </summary>");
		public void Update(email entity)
		{		
			emailDAL oemailDAL = new emailDAL();
			
			oemailDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table email with transaction
		/// </summary>");
		public void Update(email entity, MySqlTransaction oSqlTransaction)
		{		
			emailDAL oemailDAL = new emailDAL();
			
			oemailDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table email
		/// </summary>");
		public void Delete(Int32 id)
		{		
			emailDAL oemailDAL = new emailDAL();
			
			oemailDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table email with transaction
		/// </summary>");
		public void Delete(Int32 id, MySqlTransaction oSqlTransaction)
		{		
			emailDAL oemailDAL = new emailDAL();
			
			oemailDAL.Delete(id, oSqlTransaction);
		}
	}
}
