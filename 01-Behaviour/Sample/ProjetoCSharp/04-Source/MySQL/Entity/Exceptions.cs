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
	public sealed partial class exceptions : BaseModel<exceptions>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public exceptions()
			{
			}

			public exceptions(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _idExceptions;
			Nullable<Int32> _idRotina;
			Nullable<Int32> _Tentativa;
			Nullable<Int32> _Intervalo;
			Nullable<Boolean> _EnviarEmail;
			Nullable<Boolean> _EnviarUltimoEmail;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idExceptions
			{
				get { return _idExceptions; }
				set { _idExceptions = value; }
			}		
			public Nullable<Int32> idRotina
			{
				get { return _idRotina; }
				set { _idRotina = value; }
			}		
			public Nullable<Int32> Tentativa
			{
				get { return _Tentativa; }
				set { _Tentativa = value; }
			}		
			public Nullable<Int32> Intervalo
			{
				get { return _Intervalo; }
				set { _Intervalo = value; }
			}		
			public Nullable<Boolean> EnviarEmail
			{
				get { return _EnviarEmail; }
				set { _EnviarEmail = value; }
			}		
			public Nullable<Boolean> EnviarUltimoEmail
			{
				get { return _EnviarUltimoEmail; }
				set { _EnviarUltimoEmail = value; }
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

