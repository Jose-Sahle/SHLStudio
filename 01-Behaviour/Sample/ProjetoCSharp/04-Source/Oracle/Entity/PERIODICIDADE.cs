/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:42
**********************************************************/
using System;
using System.Data; 
using System.Reflection;

namespace GPRotina.Entity
{
	[Serializable]
	public sealed partial class PERIODICIDADE : BaseModel<PERIODICIDADE>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public PERIODICIDADE()
			{
			}

			public PERIODICIDADE(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _IDPERIODICIDADE;
			Nullable<Int32> _IDROTINA;
			Nullable<Int32> _TIPO;
			String _PARAMETRO;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> IDPERIODICIDADE
			{
				get { return _IDPERIODICIDADE; }
				set { _IDPERIODICIDADE = value; }
			}		
			public Nullable<Int32> IDROTINA
			{
				get { return _IDROTINA; }
				set { _IDROTINA = value; }
			}		
			public Nullable<Int32> TIPO
			{
				get { return _TIPO; }
				set { _TIPO = value; }
			}		
			public String PARAMETRO
			{
				get { return _PARAMETRO; }
				set { _PARAMETRO = value; }
			}		
		#endregion

		#region [ Relationship properties ]
			public ROTINA GP_ROTINA_FK
			{
				get;
				set;
			}
		#endregion
	}
}

