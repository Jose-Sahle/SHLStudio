/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
#DESCRIPTION#
**********************************************************/
using System;
using System.Configuration;
using System.Data;

namespace #NAMESPACE#.Components
{ 
	[Serializable]
	public sealed partial class #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info : BaseModel<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info>
	{
		#region [ Constructors/Destructors ]
			public #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info()
			{
			}

			public #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info(IDataReader reader) : base(reader)
			{
			}
		#endregion
				
		#region [ Properties ]
			public #TYPEPRIMARYKEYCS_NULLABLE# #PRIMARYKEY#
			{
				get;
				set;
			}		
			<allfieldslessprimarykey>
			public #TYPECS_NULLABLE# #FIELD#
			{
				get;
				set;
			}		
			</allfieldslessprimarykey>
		#endregion		
	}
}