/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 26/01/2024 09:10:53
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
			public ROTINA GP_ROTINA_FK
			{
				get;
				set;
			}
		#endregion
	}
}

