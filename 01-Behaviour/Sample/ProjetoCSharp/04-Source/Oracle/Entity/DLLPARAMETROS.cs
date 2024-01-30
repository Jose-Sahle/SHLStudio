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
	public sealed partial class DLLPARAMETROS : BaseModel<DLLPARAMETROS>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public DLLPARAMETROS()
			{
			}

			public DLLPARAMETROS(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _IDDLLPARAMETROS;
			Nullable<Int32> _IDDLL;
			String _NOME;
			String _VALOR;
			Nullable<Int32> _TIPO;
			String _FORMATO;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> IDDLLPARAMETROS
			{
				get { return _IDDLLPARAMETROS; }
				set { _IDDLLPARAMETROS = value; }
			}		
			public Nullable<Int32> IDDLL
			{
				get { return _IDDLL; }
				set { _IDDLL = value; }
			}		
			public String NOME
			{
				get { return _NOME; }
				set { _NOME = value; }
			}		
			public String VALOR
			{
				get { return _VALOR; }
				set { _VALOR = value; }
			}		
			public Nullable<Int32> TIPO
			{
				get { return _TIPO; }
				set { _TIPO = value; }
			}		
			public String FORMATO
			{
				get { return _FORMATO; }
				set { _FORMATO = value; }
			}		
		#endregion

		#region [ Relationship properties ]
			public DLL GP_DLL_FK
			{
				get;
				set;
			}
		#endregion
	}
}

