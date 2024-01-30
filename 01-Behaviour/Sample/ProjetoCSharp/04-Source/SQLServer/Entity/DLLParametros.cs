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
	public sealed partial class DLLParametros : BaseModel<DLLParametros>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public DLLParametros()
			{
			}

			public DLLParametros(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _idDLLParametros;
			Nullable<Int32> _idDLL;
			String _Nome;
			String _Valor;
			Nullable<Int32> _Tipo;
			String _Formato;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idDLLParametros
			{
				get { return _idDLLParametros; }
				set { _idDLLParametros = value; }
			}		
			public Nullable<Int32> idDLL
			{
				get { return _idDLL; }
				set { _idDLL = value; }
			}		
			public String Nome
			{
				get { return _Nome; }
				set { _Nome = value; }
			}		
			public String Valor
			{
				get { return _Valor; }
				set { _Valor = value; }
			}		
			public Nullable<Int32> Tipo
			{
				get { return _Tipo; }
				set { _Tipo = value; }
			}		
			public String Formato
			{
				get { return _Formato; }
				set { _Formato = value; }
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

