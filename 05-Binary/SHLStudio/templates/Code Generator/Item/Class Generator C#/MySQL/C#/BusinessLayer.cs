/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using MySql.Data.MySqlClient;

using #NAMESPACEENTITY#;
using #NAMESPACEDAL#;
                
namespace #NAMESPACEBLL#
{ 
    public sealed partial class #TABLEWITHOUTPREFIXTABLE##SUFFIXBLL#
    {
		/// <summary>
		/// Select a record by ID from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>");
		public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# Select(Int32 p#PRIMARYKEY#)
		{		
			#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# = new #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#();

			return o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#.Select(p#PRIMARYKEY#);
		}

		/// <summary>
		/// Select all records
		/// </summary>");
		public List<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#> SelectList()
		{		
			#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity = new #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#();
			#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# = new #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#();
			
			return o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#.SelectList(entity);
		}

		/// <summary>
		/// Select a record by filter
		/// </summary>");
		public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# Select(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{		
			#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# = new #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#();
			
			return o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#.Select(entity);
		}

		/// <summary>
		/// Select some records by filter
		/// </summary>");
		public List<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#> SelectList(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{		
			#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# = new #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#();
			
			return o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#.SelectList(entity);
		}

		/// <summary>
		/// Insert a record in the table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>");
		public Int32 Insert(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{		
			#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# = new #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#();
		   
			return o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#.Insert(entity);
		}

		/// <summary>
		/// Insert a record in the table #TABLEWITHOUTPREFIXTABLE# inside a transaction
		/// </summary>");
		public Int32 Insert(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity, MySqlTransaction oSqlTransaction)
		{		
			#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# = new #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#();
			
			return o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#.Insert(entity, oSqlTransaction);
		}

		/// <summary>
		/// Update a record in the table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>");
		public void Update(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{		
			#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# = new #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#();
			
			o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#.Update(entity);
		}

		/// <summary>
		/// Update a record in the table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>");
		public void Update(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity, MySqlTransaction oSqlTransaction)
		{		
			#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# = new #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#();
			
			o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#.Update(entity, oSqlTransaction);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>");
		public void Delete(Int32 id)
		{		
			#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# = new #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#();
			
			o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#.Delete(id);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>");
		public void Delete(Int32 id, MySqlTransaction oSqlTransaction)
		{		
			#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# = new #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#();
			
			o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#.Delete(id, oSqlTransaction);
		}
		
		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE#
		/// </summary>");
		public void Delete(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity)
		{		
			#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# = new #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#();
			
			o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#.Delete(entity);
		}

		/// <summary>
		/// Delete a record from table #TABLEWITHOUTPREFIXTABLE# with transaction
		/// </summary>");
		public void Delete(#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# entity, MySqlTransaction oSqlTransaction)
		{		
			#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL# = new #TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#();
			
			o#TABLEWITHOUTPREFIXTABLE##SUFFIXDAL#.Delete(entity, oSqlTransaction);
		}
		
	}
}