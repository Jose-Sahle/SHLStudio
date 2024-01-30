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
			Nullable<Int32> _idRotina;
			String _Nome;
			String _Decricao;
			Nullable<DateTime> _DataCriacao;
			String _Usuario;
			String _Funcional;
			Nullable<Boolean> _Ativo;
			String _Apelido;
			String _assembly;
			Nullable<Int32> _TestField;
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
			public String assembly
			{
				get { return _assembly; }
				set { _assembly = value; }
			}		
			public Nullable<Int32> TestField
			{
				get { return _TestField; }
				set { _TestField = value; }
			}		
		#endregion

	}
}

