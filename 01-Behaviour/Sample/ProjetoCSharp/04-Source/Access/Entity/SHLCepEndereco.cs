/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 10/09/2014 19:45:48
**********************************************************/
using System;
using System.Data; 
using System.Reflection;

namespace SHL.CEP.Entity
{

	[Serializable]
	public sealed partial class SHLCepEndereco : BaseModel<SHLCepEndereco>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public SHLCepEndereco()
			{
			}

			public SHLCepEndereco(IDataReader reader) : base(reader)
			{
			}
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idshlcependereco
			{
				get;
				set;
			}		
			public String BAIRRO
			{
				get;
				set;
			}		
			public String CEP
			{
				get;
				set;
			}		
			public String CIDADE
			{
				get;
				set;
			}		
			public String ENDERECO
			{
				get;
				set;
			}		
			public String ESTADO
			{
				get;
				set;
			}		
		#endregion

	}
}

