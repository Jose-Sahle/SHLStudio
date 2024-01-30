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
    public sealed partial class AGENDAMENTOBLL
    {
		/// <summary>
		/// Select a record by ID from table AGENDAMENTO
		/// </summary>");
		public AGENDAMENTO Select(Int32 pIDAGENDAMENTO)
		{		
			AGENDAMENTODAL oAGENDAMENTODAL = new AGENDAMENTODAL();

			return oAGENDAMENTODAL.Select(pIDAGENDAMENTO);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<AGENDAMENTO> SelectList()
		{		
			AGENDAMENTO entity = new AGENDAMENTO();
			AGENDAMENTODAL oAGENDAMENTODAL = new AGENDAMENTODAL();
			
			return oAGENDAMENTODAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public AGENDAMENTO Select(AGENDAMENTO entity)
		{		
			AGENDAMENTODAL oAGENDAMENTODAL = new AGENDAMENTODAL();
			
			return oAGENDAMENTODAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<AGENDAMENTO> SelectList(AGENDAMENTO entity)
		{		
			AGENDAMENTODAL oAGENDAMENTODAL = new AGENDAMENTODAL();
			
			return oAGENDAMENTODAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table AGENDAMENTO
		/// </summary>");
		public Int32 Insert(AGENDAMENTO entity)
		{		
			AGENDAMENTODAL oAGENDAMENTODAL = new AGENDAMENTODAL();
		   
			return oAGENDAMENTODAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table AGENDAMENTO inside a transaction
		/// </summary>");
		public Int32 Insert(AGENDAMENTO entity, OracleTransaction oSqlTransaction)
		{		
			AGENDAMENTODAL oAGENDAMENTODAL = new AGENDAMENTODAL();
			
			return oAGENDAMENTODAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table AGENDAMENTO
		/// </summary>");
		public void Update(AGENDAMENTO entity)
		{		
			AGENDAMENTODAL oAGENDAMENTODAL = new AGENDAMENTODAL();
			
			oAGENDAMENTODAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table AGENDAMENTO with transaction
		/// </summary>");
		public void Update(AGENDAMENTO entity, OracleTransaction oSqlTransaction)
		{		
			AGENDAMENTODAL oAGENDAMENTODAL = new AGENDAMENTODAL();
			
			oAGENDAMENTODAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table AGENDAMENTO
		/// </summary>");
		public void Delete(Int32 id)
		{		
			AGENDAMENTODAL oAGENDAMENTODAL = new AGENDAMENTODAL();
			
			oAGENDAMENTODAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table AGENDAMENTO with transaction
		/// </summary>");
		public void Delete(Int32 id, OracleTransaction oSqlTransaction)
		{		
			AGENDAMENTODAL oAGENDAMENTODAL = new AGENDAMENTODAL();
			
			oAGENDAMENTODAL.Delete(id, oSqlTransaction);
		}
	}
}
