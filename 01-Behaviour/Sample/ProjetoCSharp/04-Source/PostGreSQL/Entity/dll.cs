/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:39
**********************************************************/
using System;
using System.Data; 
using System.Reflection;

namespace GPRotina.Entity
{
	[Serializable]
	public sealed partial class dll : BaseModel<dll>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public dll()
			{
			}

			public dll(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _iddll;
			Nullable<Int32> _idrotina;
			Nullable<Int32> _ordem;
			String _nome;
			String _assembly;
			Nullable<Int32> _dependencia;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> iddll
			{
				get { return _iddll; }
				set { _iddll = value; }
			}		
			public Nullable<Int32> idrotina
			{
				get { return _idrotina; }
				set { _idrotina = value; }
			}		
			public Nullable<Int32> ordem
			{
				get { return _ordem; }
				set { _ordem = value; }
			}		
			public String nome
			{
				get { return _nome; }
				set { _nome = value; }
			}		
			public String assembly
			{
				get { return _assembly; }
				set { _assembly = value; }
			}		
			public Nullable<Int32> dependencia
			{
				get { return _dependencia; }
				set { _dependencia = value; }
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

