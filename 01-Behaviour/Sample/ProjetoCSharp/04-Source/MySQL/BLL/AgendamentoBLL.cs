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
    public sealed partial class agendamentoBLL
    {
		/// <summary>
		/// Select a record by ID from table agendamento
		/// </summary>");
		public agendamento Select(Int32 pidAgendamento)
		{		
			agendamentoDAL oagendamentoDAL = new agendamentoDAL();

			return oagendamentoDAL.Select(pidAgendamento);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<agendamento> SelectList()
		{		
			agendamento entity = new agendamento();
			agendamentoDAL oagendamentoDAL = new agendamentoDAL();
			
			return oagendamentoDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public agendamento Select(agendamento entity)
		{		
			agendamentoDAL oagendamentoDAL = new agendamentoDAL();
			
			return oagendamentoDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<agendamento> SelectList(agendamento entity)
		{		
			agendamentoDAL oagendamentoDAL = new agendamentoDAL();
			
			return oagendamentoDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table agendamento
		/// </summary>");
		public Int32 Insert(agendamento entity)
		{		
			agendamentoDAL oagendamentoDAL = new agendamentoDAL();
		   
			return oagendamentoDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table agendamento inside a transaction
		/// </summary>");
		public Int32 Insert(agendamento entity, MySqlTransaction oSqlTransaction)
		{		
			agendamentoDAL oagendamentoDAL = new agendamentoDAL();
			
			return oagendamentoDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table agendamento
		/// </summary>");
		public void Update(agendamento entity)
		{		
			agendamentoDAL oagendamentoDAL = new agendamentoDAL();
			
			oagendamentoDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table agendamento with transaction
		/// </summary>");
		public void Update(agendamento entity, MySqlTransaction oSqlTransaction)
		{		
			agendamentoDAL oagendamentoDAL = new agendamentoDAL();
			
			oagendamentoDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table agendamento
		/// </summary>");
		public void Delete(Int32 id)
		{		
			agendamentoDAL oagendamentoDAL = new agendamentoDAL();
			
			oagendamentoDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table agendamento with transaction
		/// </summary>");
		public void Delete(Int32 id, MySqlTransaction oSqlTransaction)
		{		
			agendamentoDAL oagendamentoDAL = new agendamentoDAL();
			
			oagendamentoDAL.Delete(id, oSqlTransaction);
		}
	}
}
