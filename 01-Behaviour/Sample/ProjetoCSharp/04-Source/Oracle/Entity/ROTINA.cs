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
	public sealed partial class ROTINA : BaseModel<ROTINA>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public ROTINA()
			{
			}

			public ROTINA(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _IDROTINA;
			String _NOME;
			String _DECRICAO;
			Nullable<DateTime> _DATACRIACAO;
			String _USUARIO;
			String _FUNCIONAL;
			Nullable<Int32> _ATIVO;
			String _APELIDO;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> IDROTINA
			{
				get { return _IDROTINA; }
				set { _IDROTINA = value; }
			}		
			public String NOME
			{
				get { return _NOME; }
				set { _NOME = value; }
			}		
			public String DECRICAO
			{
				get { return _DECRICAO; }
				set { _DECRICAO = value; }
			}		
			public Nullable<DateTime> DATACRIACAO
			{
				get { return _DATACRIACAO; }
				set { _DATACRIACAO = value; }
			}		
			public String USUARIO
			{
				get { return _USUARIO; }
				set { _USUARIO = value; }
			}		
			public String FUNCIONAL
			{
				get { return _FUNCIONAL; }
				set { _FUNCIONAL = value; }
			}		
			public Nullable<Int32> ATIVO
			{
				get { return _ATIVO; }
				set { _ATIVO = value; }
			}		
			public String APELIDO
			{
				get { return _APELIDO; }
				set { _APELIDO = value; }
			}		
		#endregion

	}
}

