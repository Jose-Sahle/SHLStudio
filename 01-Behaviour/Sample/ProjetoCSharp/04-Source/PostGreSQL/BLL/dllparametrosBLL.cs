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
    public sealed partial class dllparametrosBLL
    {
		/// <summary>
		/// Select a record by ID from table dllparametros
		/// </summary>");
		public dllparametros Select(Int32 piddllparametros)
		{		
			dllparametrosDAL odllparametrosDAL = new dllparametrosDAL();

			return odllparametrosDAL.Select(piddllparametros);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<dllparametros> SelectList()
		{		
			dllparametros entity = new dllparametros();
			dllparametrosDAL odllparametrosDAL = new dllparametrosDAL();
			
			return odllparametrosDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public dllparametros Select(dllparametros entity)
		{		
			dllparametrosDAL odllparametrosDAL = new dllparametrosDAL();
			
			return odllparametrosDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<dllparametros> SelectList(dllparametros entity)
		{		
			dllparametrosDAL odllparametrosDAL = new dllparametrosDAL();
			
			return odllparametrosDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table dllparametros
		/// </summary>");
		public Int32 Insert(dllparametros entity)
		{		
			dllparametrosDAL odllparametrosDAL = new dllparametrosDAL();
		   
			return odllparametrosDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table dllparametros inside a transaction
		/// </summary>");
		public Int32 Insert(dllparametros entity, NpgsqlTransaction oSqlTransaction)
		{		
			dllparametrosDAL odllparametrosDAL = new dllparametrosDAL();
			
			return odllparametrosDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table dllparametros
		/// </summary>");
		public void Update(dllparametros entity)
		{		
			dllparametrosDAL odllparametrosDAL = new dllparametrosDAL();
			
			odllparametrosDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table dllparametros with transaction
		/// </summary>");
		public void Update(dllparametros entity, NpgsqlTransaction oSqlTransaction)
		{		
			dllparametrosDAL odllparametrosDAL = new dllparametrosDAL();
			
			odllparametrosDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table dllparametros
		/// </summary>");
		public void Delete(Int32 id)
		{		
			dllparametrosDAL odllparametrosDAL = new dllparametrosDAL();
			
			odllparametrosDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table dllparametros with transaction
		/// </summary>");
		public void Delete(Int32 id, NpgsqlTransaction oSqlTransaction)
		{		
			dllparametrosDAL odllparametrosDAL = new dllparametrosDAL();
			
			odllparametrosDAL.Delete(id, oSqlTransaction);
		}
	}
}
