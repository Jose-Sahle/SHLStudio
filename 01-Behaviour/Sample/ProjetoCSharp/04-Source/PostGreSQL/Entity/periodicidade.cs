/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:40
**********************************************************/
using System;
using System.Data; 
using System.Reflection;

namespace GPRotina.Entity
{
	[Serializable]
	public sealed partial class periodicidade : BaseModel<periodicidade>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public periodicidade()
			{
			}

			public periodicidade(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _idperiodicidade;
			Nullable<Int32> _idrotina;
			Nullable<Int32> _tipo;
			String _parametro;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idperiodicidade
			{
				get { return _idperiodicidade; }
				set { _idperiodicidade = value; }
			}		
			public Nullable<Int32> idrotina
			{
				get { return _idrotina; }
				set { _idrotina = value; }
			}		
			public Nullable<Int32> tipo
			{
				get { return _tipo; }
				set { _tipo = value; }
			}		
			public String parametro
			{
				get { return _parametro; }
				set { _parametro = value; }
			}		
		#endregion

		#region [ Relationship properties ]
			public rotina gp_rotina_FK
			{
				get;
				set;
			}
		#endregion
	}
}

