/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:16
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
    public sealed partial class periodicidadeBLL
    {
		/// <summary>
		/// Select a record by ID from table periodicidade
		/// </summary>");
		public periodicidade Select(Int32 pidPeriodicidade)
		{		
			periodicidadeDAL operiodicidadeDAL = new periodicidadeDAL();

			return operiodicidadeDAL.Select(pidPeriodicidade);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<periodicidade> SelectList()
		{		
			periodicidade entity = new periodicidade();
			periodicidadeDAL operiodicidadeDAL = new periodicidadeDAL();
			
			return operiodicidadeDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public periodicidade Select(periodicidade entity)
		{		
			periodicidadeDAL operiodicidadeDAL = new periodicidadeDAL();
			
			return operiodicidadeDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<periodicidade> SelectList(periodicidade entity)
		{		
			periodicidadeDAL operiodicidadeDAL = new periodicidadeDAL();
			
			return operiodicidadeDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table periodicidade
		/// </summary>");
		public Int32 Insert(periodicidade entity)
		{		
			periodicidadeDAL operiodicidadeDAL = new periodicidadeDAL();
		   
			return operiodicidadeDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table periodicidade inside a transaction
		/// </summary>");
		public Int32 Insert(periodicidade entity, MySqlTransaction oSqlTransaction)
		{		
			periodicidadeDAL operiodicidadeDAL = new periodicidadeDAL();
			
			return operiodicidadeDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table periodicidade
		/// </summary>");
		public void Update(periodicidade entity)
		{		
			periodicidadeDAL operiodicidadeDAL = new periodicidadeDAL();
			
			operiodicidadeDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table periodicidade with transaction
		/// </summary>");
		public void Update(periodicidade entity, MySqlTransaction oSqlTransaction)
		{		
			periodicidadeDAL operiodicidadeDAL = new periodicidadeDAL();
			
			operiodicidadeDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table periodicidade
		/// </summary>");
		public void Delete(Int32 id)
		{		
			periodicidadeDAL operiodicidadeDAL = new periodicidadeDAL();
			
			operiodicidadeDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table periodicidade with transaction
		/// </summary>");
		public void Delete(Int32 id, MySqlTransaction oSqlTransaction)
		{		
			periodicidadeDAL operiodicidadeDAL = new periodicidadeDAL();
			
			operiodicidadeDAL.Delete(id, oSqlTransaction);
		}
	}
}
