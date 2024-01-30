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
	public sealed partial class DLL : BaseModel<DLL>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public DLL()
			{
			}

			public DLL(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _IDDLL;
			Nullable<Int32> _IDROTINA;
			Nullable<Int32> _ORDEM;
			String _NOME;
			String _ASSEMBLY;
			Nullable<Int32> _DEPENDENCIA;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> IDDLL
			{
				get { return _IDDLL; }
				set { _IDDLL = value; }
			}		
			public Nullable<Int32> IDROTINA
			{
				get { return _IDROTINA; }
				set { _IDROTINA = value; }
			}		
			public Nullable<Int32> ORDEM
			{
				get { return _ORDEM; }
				set { _ORDEM = value; }
			}		
			public String NOME
			{
				get { return _NOME; }
				set { _NOME = value; }
			}		
			public String ASSEMBLY
			{
				get { return _ASSEMBLY; }
				set { _ASSEMBLY = value; }
			}		
			public Nullable<Int32> DEPENDENCIA
			{
				get { return _DEPENDENCIA; }
				set { _DEPENDENCIA = value; }
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

