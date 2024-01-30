/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:39
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using Npgsql;

using GPRotina.Entity;
using GPRotina.DAL;
                
namespace GPRotina.BLL
{ 
    public sealed partial class exceptionsBLL
    {
		/// <summary>
		/// Select a record by ID from table exceptions
		/// </summary>");
		public exceptions Select(Int32 pidexceptions)
		{		
			exceptionsDAL oexceptionsDAL = new exceptionsDAL();

			return oexceptionsDAL.Select(pidexceptions);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<exceptions> SelectList()
		{		
			exceptions entity = new exceptions();
			exceptionsDAL oexceptionsDAL = new exceptionsDAL();
			
			return oexceptionsDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public exceptions Select(exceptions entity)
		{		
			exceptionsDAL oexceptionsDAL = new exceptionsDAL();
			
			return oexceptionsDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<exceptions> SelectList(exceptions entity)
		{		
			exceptionsDAL oexceptionsDAL = new exceptionsDAL();
			
			return oexceptionsDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table exceptions
		/// </summary>");
		public Int32 Insert(exceptions entity)
		{		
			exceptionsDAL oexceptionsDAL = new exceptionsDAL();
		   
			return oexceptionsDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table exceptions inside a transaction
		/// </summary>");
		public Int32 Insert(exceptions entity, NpgsqlTransaction oSqlTransaction)
		{		
			exceptionsDAL oexceptionsDAL = new exceptionsDAL();
			
			return oexceptionsDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table exceptions
		/// </summary>");
		public void Update(exceptions entity)
		{		
			exceptionsDAL oexceptionsDAL = new exceptionsDAL();
			
			oexceptionsDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table exceptions with transaction
		/// </summary>");
		public void Update(exceptions entity, NpgsqlTransaction oSqlTransaction)
		{		
			exceptionsDAL oexceptionsDAL = new exceptionsDAL();
			
			oexceptionsDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table exceptions
		/// </summary>");
		public void Delete(Int32 id)
		{		
			exceptionsDAL oexceptionsDAL = new exceptionsDAL();
			
			oexceptionsDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table exceptions with transaction
		/// </summary>");
		public void Delete(Int32 id, NpgsqlTransaction oSqlTransaction)
		{		
			exceptionsDAL oexceptionsDAL = new exceptionsDAL();
			
			oexceptionsDAL.Delete(id, oSqlTransaction);
		}
	}
}