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
			Nullable<Int32> _idexceptions;
			Nullable<Int32> _idrotina;
			Nullable<Int32> _tentativa;
			Nullable<Int32> _intervalo;
			Nullable<Boolean> _enviaremail;
			Nullable<Boolean> _enviarultimoemail;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idexceptions
			{
				get { return _idexceptions; }
				set { _idexceptions = value; }
			}		
			public Nullable<Int32> idrotina
			{
				get { return _idrotina; }
				set { _idrotina = value; }
			}		
			public Nullable<Int32> tentativa
			{
				get { return _tentativa; }
				set { _tentativa = value; }
			}		
			public Nullable<Int32> intervalo
			{
				get { return _intervalo; }
				set { _intervalo = value; }
			}		
			public Nullable<Boolean> enviaremail
			{
				get { return _enviaremail; }
				set { _enviaremail = value; }
			}		
			public Nullable<Boolean> enviarultimoemail
			{
				get { return _enviarultimoemail; }
				set { _enviarultimoemail = value; }
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

