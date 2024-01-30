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
    public sealed partial class PERIODICIDADEBLL
    {
		/// <summary>
		/// Select a record by ID from table PERIODICIDADE
		/// </summary>");
		public PERIODICIDADE Select(Int32 pIDPERIODICIDADE)
		{		
			PERIODICIDADEDAL oPERIODICIDADEDAL = new PERIODICIDADEDAL();

			return oPERIODICIDADEDAL.Select(pIDPERIODICIDADE);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<PERIODICIDADE> SelectList()
		{		
			PERIODICIDADE entity = new PERIODICIDADE();
			PERIODICIDADEDAL oPERIODICIDADEDAL = new PERIODICIDADEDAL();
			
			return oPERIODICIDADEDAL.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public PERIODICIDADE Select(PERIODICIDADE entity)
		{		
			PERIODICIDADEDAL oPERIODICIDADEDAL = new PERIODICIDADEDAL();
			
			return oPERIODICIDADEDAL.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<PERIODICIDADE> SelectList(PERIODICIDADE entity)
		{		
			PERIODICIDADEDAL oPERIODICIDADEDAL = new PERIODICIDADEDAL();
			
			return oPERIODICIDADEDAL.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table PERIODICIDADE
		/// </summary>");
		public Int32 Insert(PERIODICIDADE entity)
		{		
			PERIODICIDADEDAL oPERIODICIDADEDAL = new PERIODICIDADEDAL();
		   
			return oPERIODICIDADEDAL.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table PERIODICIDADE inside a transaction
		/// </summary>");
		public Int32 Insert(PERIODICIDADE entity, OracleTransaction oSqlTransaction)
		{		
			PERIODICIDADEDAL oPERIODICIDADEDAL = new PERIODICIDADEDAL();
			
			return oPERIODICIDADEDAL.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table PERIODICIDADE
		/// </summary>");
		public void Update(PERIODICIDADE entity)
		{		
			PERIODICIDADEDAL oPERIODICIDADEDAL = new PERIODICIDADEDAL();
			
			oPERIODICIDADEDAL.Update(entity);
		}

		/// <summary>
		/// Update a record in the table PERIODICIDADE with transaction
		/// </summary>");
		public void Update(PERIODICIDADE entity, OracleTransaction oSqlTransaction)
		{		
			PERIODICIDADEDAL oPERIODICIDADEDAL = new PERIODICIDADEDAL();
			
			oPERIODICIDADEDAL.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table PERIODICIDADE
		/// </summary>");
		public void Delete(Int32 id)
		{		
			PERIODICIDADEDAL oPERIODICIDADEDAL = new PERIODICIDADEDAL();
			
			oPERIODICIDADEDAL.Delete(id);
		}

		/// <summary>
		/// Delete a record from table PERIODICIDADE with transaction
		/// </summary>");
		public void Delete(Int32 id, OracleTransaction oSqlTransaction)
		{		
			PERIODICIDADEDAL oPERIODICIDADEDAL = new PERIODICIDADEDAL();
			
			oPERIODICIDADEDAL.Delete(id, oSqlTransaction);
		}
	}
}
