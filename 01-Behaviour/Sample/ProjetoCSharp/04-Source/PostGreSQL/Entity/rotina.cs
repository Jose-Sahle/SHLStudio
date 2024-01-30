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
			Nullable<Int32> _idrotina;
			String _nome;
			String _decricao;
			Nullable<DateTime> _datacriacao;
			String _usuario;
			String _funcional;
			Nullable<Boolean> _ativo;
			String _apelido;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idrotina
			{
				get { return _idrotina; }
				set { _idrotina = value; }
			}		
			public String nome
			{
				get { return _nome; }
				set { _nome = value; }
			}		
			public String decricao
			{
				get { return _decricao; }
				set { _decricao = value; }
			}		
			public Nullable<DateTime> datacriacao
			{
				get { return _datacriacao; }
				set { _datacriacao = value; }
			}		
			public String usuario
			{
				get { return _usuario; }
				set { _usuario = value; }
			}		
			public String funcional
			{
				get { return _funcional; }
				set { _funcional = value; }
			}		
			public Nullable<Boolean> ativo
			{
				get { return _ativo; }
				set { _ativo = value; }
			}		
			public String apelido
			{
				get { return _apelido; }
				set { _apelido = value; }
			}		
		#endregion

	}
}

