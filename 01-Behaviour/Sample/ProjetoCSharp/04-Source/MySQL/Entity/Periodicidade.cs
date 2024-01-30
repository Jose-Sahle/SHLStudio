/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 05/09/2014 11:22:17
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
			Nullable<Int32> _idPeriodicidade;
			Nullable<Int32> _idRotina;
			Nullable<Int32> _Tipo;
			String _Parametro;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idPeriodicidade
			{
				get { return _idPeriodicidade; }
				set { _idPeriodicidade = value; }
			}		
			public Nullable<Int32> idRotina
			{
				get { return _idRotina; }
				set { _idRotina = value; }
			}		
			public Nullable<Int32> Tipo
			{
				get { return _Tipo; }
				set { _Tipo = value; }
			}		
			public String Parametro
			{
				get { return _Parametro; }
				set { _Parametro = value; }
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

