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
	public sealed partial class dllparametros : BaseModel<dllparametros>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public dllparametros()
			{
			}

			public dllparametros(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _iddllparametros;
			Nullable<Int32> _iddll;
			String _nome;
			String _valor;
			Nullable<Int32> _tipo;
			String _formato;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> iddllparametros
			{
				get { return _iddllparametros; }
				set { _iddllparametros = value; }
			}		
			public Nullable<Int32> iddll
			{
				get { return _iddll; }
				set { _iddll = value; }
			}		
			public String nome
			{
				get { return _nome; }
				set { _nome = value; }
			}		
			public String valor
			{
				get { return _valor; }
				set { _valor = value; }
			}		
			public Nullable<Int32> tipo
			{
				get { return _tipo; }
				set { _tipo = value; }
			}		
			public String formato
			{
				get { return _formato; }
				set { _formato = value; }
			}		
		#endregion

		#region [ Relationship properties ]
			public dll gp_dll_FK
			{
				get;
				set;
			}
		#endregion
	}
}

