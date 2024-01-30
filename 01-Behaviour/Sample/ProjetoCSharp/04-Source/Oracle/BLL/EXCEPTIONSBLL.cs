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
    public sealed partial class EXCEPTIONSBLL
    {
		/// <summary>
		/// Select a record by ID from table EXCEPTIONS
		/// </summary>");
		public EXCEPTIONS Select(Int32 pIDEXCEPTIONS)
		{		
			EXCEPTIONSDAL oEXCEPTIONSDAL = new EXCEPTIONSDAL();

			return oEXCEPTIONSDAL.Select(pIDEXCEPTIONS);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<EXCEPTIONS> SelectList()
		{		
			EXCEPTIONS entity = new EXCEPTIONS();
			EXCEPTIONSDAL oEXCEPTIONSDAL = new EXCEPTIONSDAL();
			
			return oEXCEPTIONSDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public EXCEPTIONS Select(EXCEPTIONS entity)
		{		
			EXCEPTIONSDAL oEXCEPTIONSDAL = new EXCEPTIONSDAL();
			
			return oEXCEPTIONSDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<EXCEPTIONS> SelectList(EXCEPTIONS entity)
		{		
			EXCEPTIONSDAL oEXCEPTIONSDAL = new EXCEPTIONSDAL();
			
			return oEXCEPTIONSDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table EXCEPTIONS
		/// </summary>");
		public Int32 Insert(EXCEPTIONS entity)
		{		
			EXCEPTIONSDAL oEXCEPTIONSDAL = new EXCEPTIONSDAL();
		   
			return oEXCEPTIONSDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table EXCEPTIONS inside a transaction
		/// </summary>");
		public Int32 Insert(EXCEPTIONS entity, OracleTransaction oSqlTransaction)
		{		
			EXCEPTIONSDAL oEXCEPTIONSDAL = new EXCEPTIONSDAL();
			
			return oEXCEPTIONSDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table EXCEPTIONS
		/// </summary>");
		public void Update(EXCEPTIONS entity)
		{		
			EXCEPTIONSDAL oEXCEPTIONSDAL = new EXCEPTIONSDAL();
			
			oEXCEPTIONSDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table EXCEPTIONS with transaction
		/// </summary>");
		public void Update(EXCEPTIONS entity, OracleTransaction oSqlTransaction)
		{		
			EXCEPTIONSDAL oEXCEPTIONSDAL = new EXCEPTIONSDAL();
			
			oEXCEPTIONSDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table EXCEPTIONS
		/// </summary>");
		public void Delete(Int32 id)
		{		
			EXCEPTIONSDAL oEXCEPTIONSDAL = new EXCEPTIONSDAL();
			
			oEXCEPTIONSDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table EXCEPTIONS with transaction
		/// </summary>");
		public void Delete(Int32 id, OracleTransaction oSqlTransaction)
		{		
			EXCEPTIONSDAL oEXCEPTIONSDAL = new EXCEPTIONSDAL();
			
			oEXCEPTIONSDAL.Delete(id, oSqlTransaction);
		}
	}
}
