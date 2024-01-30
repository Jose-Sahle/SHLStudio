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
    public sealed partial class DLLPARAMETROSBLL
    {
		/// <summary>
		/// Select a record by ID from table DLLPARAMETROS
		/// </summary>");
		public DLLPARAMETROS Select(Int32 pIDDLLPARAMETROS)
		{		
			DLLPARAMETROSDAL oDLLPARAMETROSDAL = new DLLPARAMETROSDAL();

			return oDLLPARAMETROSDAL.Select(pIDDLLPARAMETROS);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<DLLPARAMETROS> SelectList()
		{		
			DLLPARAMETROS entity = new DLLPARAMETROS();
			DLLPARAMETROSDAL oDLLPARAMETROSDAL = new DLLPARAMETROSDAL();
			
			return oDLLPARAMETROSDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public DLLPARAMETROS Select(DLLPARAMETROS entity)
		{		
			DLLPARAMETROSDAL oDLLPARAMETROSDAL = new DLLPARAMETROSDAL();
			
			return oDLLPARAMETROSDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<DLLPARAMETROS> SelectList(DLLPARAMETROS entity)
		{		
			DLLPARAMETROSDAL oDLLPARAMETROSDAL = new DLLPARAMETROSDAL();
			
			return oDLLPARAMETROSDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table DLLPARAMETROS
		/// </summary>");
		public Int32 Insert(DLLPARAMETROS entity)
		{		
			DLLPARAMETROSDAL oDLLPARAMETROSDAL = new DLLPARAMETROSDAL();
		   
			return oDLLPARAMETROSDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table DLLPARAMETROS inside a transaction
		/// </summary>");
		public Int32 Insert(DLLPARAMETROS entity, OracleTransaction oSqlTransaction)
		{		
			DLLPARAMETROSDAL oDLLPARAMETROSDAL = new DLLPARAMETROSDAL();
			
			return oDLLPARAMETROSDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table DLLPARAMETROS
		/// </summary>");
		public void Update(DLLPARAMETROS entity)
		{		
			DLLPARAMETROSDAL oDLLPARAMETROSDAL = new DLLPARAMETROSDAL();
			
			oDLLPARAMETROSDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table DLLPARAMETROS with transaction
		/// </summary>");
		public void Update(DLLPARAMETROS entity, OracleTransaction oSqlTransaction)
		{		
			DLLPARAMETROSDAL oDLLPARAMETROSDAL = new DLLPARAMETROSDAL();
			
			oDLLPARAMETROSDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table DLLPARAMETROS
		/// </summary>");
		public void Delete(Int32 id)
		{		
			DLLPARAMETROSDAL oDLLPARAMETROSDAL = new DLLPARAMETROSDAL();
			
			oDLLPARAMETROSDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table DLLPARAMETROS with transaction
		/// </summary>");
		public void Delete(Int32 id, OracleTransaction oSqlTransaction)
		{		
			DLLPARAMETROSDAL oDLLPARAMETROSDAL = new DLLPARAMETROSDAL();
			
			oDLLPARAMETROSDAL.Delete(id, oSqlTransaction);
		}
	}
}
