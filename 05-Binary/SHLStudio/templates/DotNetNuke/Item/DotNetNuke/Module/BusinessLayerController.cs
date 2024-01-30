/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  #DESCRIPTION#
**********************************************************/
using System;
using System.Collections.Generic;
using System.Web;
using System.Data;
using System.Data.SqlClient;


namespace #NAMESPACE#.Components
{ 
	/// <summary>
	/// Controller Class for #PREFIXBLL##TABLEWITHOUTPREFIXTABLE##SUFFIX#
	/// </summary>
	public sealed partial class #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Controller
	{
		#region [ Contrutores ]
			public #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Controller()
			{
				
			}
		#endregion
					
		#region [ Public Methods ]
			public SqlTransaction GetTransaction()
			{
				return SqlDataProvider.Instance().GetTransaction();
			}
			
			public #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info Select#TABLEWITHOUTPREFIXTABLE#(Int32 p#PRIMARYKEY#)
			{					
				return SqlDataProvider.Instance().Select#TABLEWITHOUTPREFIXTABLE#(p#PRIMARYKEY#);
			}
			
			public #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info Select#TABLEWITHOUTPREFIXTABLE#(#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity)
			{
				return SqlDataProvider.Instance().Select#TABLEWITHOUTPREFIXTABLE#(entity);
			}

			public List<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info> SelectList#TABLEWITHOUTPREFIXTABLE#()
			{
				return SqlDataProvider.Instance().SelectList#TABLEWITHOUTPREFIXTABLE#();
			}
			
			public List<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info> SelectList#TABLEWITHOUTPREFIXTABLE#(#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity)
			{
				return SqlDataProvider.Instance().SelectList#TABLEWITHOUTPREFIXTABLE#(entity);
			}
			
			public #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info Insert#TABLEWITHOUTPREFIXTABLE#( #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity)
			{
				return SqlDataProvider.Instance().Insert#TABLEWITHOUTPREFIXTABLE#( entity );
			}

			public #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info Insert#TABLEWITHOUTPREFIXTABLE#( SqlTransaction transaction, #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity)
			{
				return SqlDataProvider.Instance().Insert#TABLEWITHOUTPREFIXTABLE#( transaction, entity );
			}
			
			public void Update#TABLEWITHOUTPREFIXTABLE#( #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity )
			{
				SqlDataProvider.Instance().Update#TABLEWITHOUTPREFIXTABLE#( entity );					
			}
			
			public void Update#TABLEWITHOUTPREFIXTABLE#( SqlTransaction transaction, #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity )
			{
				SqlDataProvider.Instance().Update#TABLEWITHOUTPREFIXTABLE#( transaction, entity );					
			}
			
			public void Delete#TABLEWITHOUTPREFIXTABLE#( Int32 p#PRIMARYKEY# )
			{
				SqlDataProvider.Instance().Delete#TABLEWITHOUTPREFIXTABLE#( p#PRIMARYKEY# );
			}
			
			public void Delete#TABLEWITHOUTPREFIXTABLE#( SqlTransaction transaction, Int32 p#PRIMARYKEY# )
			{
				SqlDataProvider.Instance().Delete#TABLEWITHOUTPREFIXTABLE#( transaction, p#PRIMARYKEY# );
			}
			
			public void Delete#TABLEWITHOUTPREFIXTABLE#( #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity )
			{
				SqlDataProvider.Instance().Delete#TABLEWITHOUTPREFIXTABLE#( entity );
			}
			
			public void Delete#TABLEWITHOUTPREFIXTABLE#( SqlTransaction transaction, #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity )
			{
				SqlDataProvider.Instance().Delete#TABLEWITHOUTPREFIXTABLE#( transaction, entity );
			}
		#endregion
	
	}
}
