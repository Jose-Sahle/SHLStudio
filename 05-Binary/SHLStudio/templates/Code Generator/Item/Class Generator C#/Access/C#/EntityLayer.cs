/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
**********************************************************/
using System;
using System.Data; 
using System.Reflection;

namespace #NAMESPACEENTITY#
{

	[Serializable]
	public sealed partial class #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY# : BaseModel<#TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#()
			{
			}

			public #TABLEWITHOUTPREFIXTABLE##SUFFIXENTITY#(IDataReader reader) : base(reader)
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

		<ifexistforeignkey>		
		#region [ Relationship properties ]
			<allfieldsforeignkey>
			public #TABLEFOREIGNWITHOUTPREFIXTABLE##SUFFIXENTITY# #TABLEFOREIGN#_FK
			{
				get;
				set;
			}
			</allfieldsforeignkey>
		#endregion
		</ifexistforeignkey>
	}
}
