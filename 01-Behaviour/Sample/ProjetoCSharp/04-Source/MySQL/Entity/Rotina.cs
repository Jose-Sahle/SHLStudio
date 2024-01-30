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
	public sealed partial class rotina : BaseModel<rotina>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public rotina()
			{
			}

			public rotina(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _idRotina;
			String _Nome;
			String _Decricao;
			Nullable<DateTime> _DataCriacao;
			String _Usuario;
			String _Funcional;
			Nullable<Boolean> _Ativo;
			String _Apelido;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idRotina
			{
				get { return _idRotina; }
				set { _idRotina = value; }
			}		
			public String Nome
			{
				get { return _Nome; }
				set { _Nome = value; }
			}		
			public String Decricao
			{
				get { return _Decricao; }
				set { _Decricao = value; }
			}		
			public Nullable<DateTime> DataCriacao
			{
				get { return _DataCriacao; }
				set { _DataCriacao = value; }
			}		
			public String Usuario
			{
				get { return _Usuario; }
				set { _Usuario = value; }
			}		
			public String Funcional
			{
				get { return _Funcional; }
				set { _Funcional = value; }
			}		
			public Nullable<Boolean> Ativo
			{
				get { return _Ativo; }
				set { _Ativo = value; }
			}		
			public String Apelido
			{
				get { return _Apelido; }
				set { _Apelido = value; }
			}		
		#endregion

	}
}

