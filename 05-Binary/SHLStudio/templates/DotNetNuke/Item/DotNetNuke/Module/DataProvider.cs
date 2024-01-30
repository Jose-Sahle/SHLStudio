/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  #DESCRIPTION#
**********************************************************/
using System;
using System.Data;
using System.Collections.Generic;
using System.Data.SqlClient;

using DotNetNuke;
using DotNetNuke.Framework;

namespace #NAMESPACE#.Components
{ 
	abstract public partial class DataProvider
	{
		#region [ Private Members ]
			private static DataProvider objProvider  = null;
		#endregion
		
		#region [ Constructors ]
			static DataProvider()
			{
				CreateProvider();
			}
		#endregion
		
		#region [ Private Methods ]
			private static void CreateProvider()
			{
				objProvider = ( DataProvider )DotNetNuke.Framework.Reflection.CreateObject( "data", "#NAMESPACE#.Components", "" );
			}
		#endregion
		
		#region [ Public Methods ]
			public static new DataProvider Instance()
			{
				return objProvider;
			}
		#endregion
		
		#region [ Abstract Methods ]
			abstract public SqlTransaction GetTransaction();
			
		<alltables>
			#region [ #TABLE# ]
				abstract public #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info Select#TABLEWITHOUTPREFIXTABLE#(Int32 p#PRIMARYKEY#);
				abstract public #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info Select#TABLEWITHOUTPREFIXTABLE#(#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity);
				abstract public List<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info> SelectList#TABLEWITHOUTPREFIXTABLE#();
				abstract public List<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info> SelectList#TABLEWITHOUTPREFIXTABLE#(#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity);
				
				abstract public #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info Insert#TABLEWITHOUTPREFIXTABLE#( #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity);
				abstract public #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info Insert#TABLEWITHOUTPREFIXTABLE#( SqlTransaction transaction, #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity);
				
				abstract public void Update#TABLEWITHOUTPREFIXTABLE#( #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity );
				abstract public void Update#TABLEWITHOUTPREFIXTABLE#( SqlTransaction transaction, #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity );
				
				abstract public void Delete#TABLEWITHOUTPREFIXTABLE#( Int32 p#PRIMARYKEY# );				
				abstract public void Delete#TABLEWITHOUTPREFIXTABLE#( SqlTransaction transaction, Int32 p#PRIMARYKEY# );
				
				abstract public void Delete#TABLEWITHOUTPREFIXTABLE#( #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity );				
				abstract public void Delete#TABLEWITHOUTPREFIXTABLE#( SqlTransaction transaction, #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity );
			#endregion
			
		</alltables>
		#endregion
	}
}
