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
	public sealed partial class email : BaseModel<email>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public email()
			{
			}

			public email(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _idemail;
			Nullable<Int32> _idrotina;
			String _from;
			String _to;
			String _subject;
			String _type;
			String _body;
			Nullable<Int32> _classificacao;
			String _anexo;
			Nullable<Boolean> _ativo;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idemail
			{
				get { return _idemail; }
				set { _idemail = value; }
			}		
			public Nullable<Int32> idrotina
			{
				get { return _idrotina; }
				set { _idrotina = value; }
			}		
			public String from
			{
				get { return _from; }
				set { _from = value; }
			}		
			public String to
			{
				get { return _to; }
				set { _to = value; }
			}		
			public String subject
			{
				get { return _subject; }
				set { _subject = value; }
			}		
			public String type
			{
				get { return _type; }
				set { _type = value; }
			}		
			public String body
			{
				get { return _body; }
				set { _body = value; }
			}		
			public Nullable<Int32> classificacao
			{
				get { return _classificacao; }
				set { _classificacao = value; }
			}		
			public String anexo
			{
				get { return _anexo; }
				set { _anexo = value; }
			}		
			public Nullable<Boolean> ativo
			{
				get { return _ativo; }
				set { _ativo = value; }
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

