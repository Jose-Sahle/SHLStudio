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
    public sealed partial class rotinaBLL
    {
		/// <summary>
		/// Select a record by ID from table rotina
		/// </summary>");
		public rotina Select(Int32 pidrotina)
		{		
			rotinaDAL orotinaDAL = new rotinaDAL();

			return orotinaDAL.Select(pidrotina);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<rotina> SelectList()
		{		
			rotina entity = new rotina();
			rotinaDAL orotinaDAL = new rotinaDAL();
			
			return orotinaDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public rotina Select(rotina entity)
		{		
			rotinaDAL orotinaDAL = new rotinaDAL();
			
			return orotinaDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<rotina> SelectList(rotina entity)
		{		
			rotinaDAL orotinaDAL = new rotinaDAL();
			
			return orotinaDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table rotina
		/// </summary>");
		public Int32 Insert(rotina entity)
		{		
			rotinaDAL orotinaDAL = new rotinaDAL();
		   
			return orotinaDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table rotina inside a transaction
		/// </summary>");
		public Int32 Insert(rotina entity, NpgsqlTransaction oSqlTransaction)
		{		
			rotinaDAL orotinaDAL = new rotinaDAL();
			
			return orotinaDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table rotina
		/// </summary>");
		public void Update(rotina entity)
		{		
			rotinaDAL orotinaDAL = new rotinaDAL();
			
			orotinaDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table rotina with transaction
		/// </summary>");
		public void Update(rotina entity, NpgsqlTransaction oSqlTransaction)
		{		
			rotinaDAL orotinaDAL = new rotinaDAL();
			
			orotinaDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table rotina
		/// </summary>");
		public void Delete(Int32 id)
		{		
			rotinaDAL orotinaDAL = new rotinaDAL();
			
			orotinaDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table rotina with transaction
		/// </summary>");
		public void Delete(Int32 id, NpgsqlTransaction oSqlTransaction)
		{		
			rotinaDAL orotinaDAL = new rotinaDAL();
			
			orotinaDAL.Delete(id, oSqlTransaction);
		}
	}
}