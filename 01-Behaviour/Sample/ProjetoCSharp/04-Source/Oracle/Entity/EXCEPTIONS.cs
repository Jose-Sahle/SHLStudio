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
	public sealed partial class EXCEPTIONS : BaseModel<EXCEPTIONS>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public EXCEPTIONS()
			{
			}

			public EXCEPTIONS(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _IDEXCEPTIONS;
			Nullable<Int32> _IDROTINA;
			Nullable<Int32> _TENTATIVA;
			Nullable<Int32> _INTERVALO;
			Nullable<Int32> _ENVIAREMAIL;
			Nullable<Int32> _ENVIARULTIMOEMAIL;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> IDEXCEPTIONS
			{
				get { return _IDEXCEPTIONS; }
				set { _IDEXCEPTIONS = value; }
			}		
			public Nullable<Int32> IDROTINA
			{
				get { return _IDROTINA; }
				set { _IDROTINA = value; }
			}		
			public Nullable<Int32> TENTATIVA
			{
				get { return _TENTATIVA; }
				set { _TENTATIVA = value; }
			}		
			public Nullable<Int32> INTERVALO
			{
				get { return _INTERVALO; }
				set { _INTERVALO = value; }
			}		
			public Nullable<Int32> ENVIAREMAIL
			{
				get { return _ENVIAREMAIL; }
				set { _ENVIAREMAIL = value; }
			}		
			public Nullable<Int32> ENVIARULTIMOEMAIL
			{
				get { return _ENVIARULTIMOEMAIL; }
				set { _ENVIARULTIMOEMAIL = value; }
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

