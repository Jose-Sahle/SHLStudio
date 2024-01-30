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
    public sealed partial class ROTINABLL
    {
		/// <summary>
		/// Select a record by ID from table ROTINA
		/// </summary>");
		public ROTINA Select(Int32 pIDROTINA)
		{		
			ROTINADAL oROTINADAL = new ROTINADAL();

			return oROTINADAL.Select(pIDROTINA);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<ROTINA> SelectList()
		{		
			ROTINA entity = new ROTINA();
			ROTINADAL oROTINADAL = new ROTINADAL();
			
			return oROTINADAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public ROTINA Select(ROTINA entity)
		{		
			ROTINADAL oROTINADAL = new ROTINADAL();
			
			return oROTINADAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<ROTINA> SelectList(ROTINA entity)
		{		
			ROTINADAL oROTINADAL = new ROTINADAL();
			
			return oROTINADAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table ROTINA
		/// </summary>");
		public Int32 Insert(ROTINA entity)
		{		
			ROTINADAL oROTINADAL = new ROTINADAL();
		   
			return oROTINADAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table ROTINA inside a transaction
		/// </summary>");
		public Int32 Insert(ROTINA entity, OracleTransaction oSqlTransaction)
		{		
			ROTINADAL oROTINADAL = new ROTINADAL();
			
			return oROTINADAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table ROTINA
		/// </summary>");
		public void Update(ROTINA entity)
		{		
			ROTINADAL oROTINADAL = new ROTINADAL();
			
			oROTINADAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table ROTINA with transaction
		/// </summary>");
		public void Update(ROTINA entity, OracleTransaction oSqlTransaction)
		{		
			ROTINADAL oROTINADAL = new ROTINADAL();
			
			oROTINADAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table ROTINA
		/// </summary>");
		public void Delete(Int32 id)
		{		
			ROTINADAL oROTINADAL = new ROTINADAL();
			
			oROTINADAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table ROTINA with transaction
		/// </summary>");
		public void Delete(Int32 id, OracleTransaction oSqlTransaction)
		{		
			ROTINADAL oROTINADAL = new ROTINADAL();
			
			oROTINADAL.Delete(id, oSqlTransaction);
		}
	}
}
