/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:38
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
    public sealed partial class dllBLL
    {
		/// <summary>
		/// Select a record by ID from table dll
		/// </summary>");
		public dll Select(Int32 piddll)
		{		
			dllDAL odllDAL = new dllDAL();

			return odllDAL.Select(piddll);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<dll> SelectList()
		{		
			dll entity = new dll();
			dllDAL odllDAL = new dllDAL();
			
			return odllDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public dll Select(dll entity)
		{		
			dllDAL odllDAL = new dllDAL();
			
			return odllDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<dll> SelectList(dll entity)
		{		
			dllDAL odllDAL = new dllDAL();
			
			return odllDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table dll
		/// </summary>");
		public Int32 Insert(dll entity)
		{		
			dllDAL odllDAL = new dllDAL();
		   
			return odllDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table dll inside a transaction
		/// </summary>");
		public Int32 Insert(dll entity, NpgsqlTransaction oSqlTransaction)
		{		
			dllDAL odllDAL = new dllDAL();
			
			return odllDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table dll
		/// </summary>");
		public void Update(dll entity)
		{		
			dllDAL odllDAL = new dllDAL();
			
			odllDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table dll with transaction
		/// </summary>");
		public void Update(dll entity, NpgsqlTransaction oSqlTransaction)
		{		
			dllDAL odllDAL = new dllDAL();
			
			odllDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table dll
		/// </summary>");
		public void Delete(Int32 id)
		{		
			dllDAL odllDAL = new dllDAL();
			
			odllDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table dll with transaction
		/// </summary>");
		public void Delete(Int32 id, NpgsqlTransaction oSqlTransaction)
		{		
			dllDAL odllDAL = new dllDAL();
			
			odllDAL.Delete(id, oSqlTransaction);
		}
	}
}
