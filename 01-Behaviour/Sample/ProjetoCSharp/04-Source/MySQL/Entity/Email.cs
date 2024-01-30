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
			Nullable<Int32> _idEMAIL;
			Nullable<Int32> _idRotina;
			String _FROM;
			String _TO;
			String _SUBJECT;
			String _TYPE;
			String _BODY;
			Nullable<Int32> _Classificacao;
			String _Anexo;
			Nullable<Boolean> _Ativo;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idEMAIL
			{
				get { return _idEMAIL; }
				set { _idEMAIL = value; }
			}		
			public Nullable<Int32> idRotina
			{
				get { return _idRotina; }
				set { _idRotina = value; }
			}		
			public String FROM
			{
				get { return _FROM; }
				set { _FROM = value; }
			}		
			public String TO
			{
				get { return _TO; }
				set { _TO = value; }
			}		
			public String SUBJECT
			{
				get { return _SUBJECT; }
				set { _SUBJECT = value; }
			}		
			public String TYPE
			{
				get { return _TYPE; }
				set { _TYPE = value; }
			}		
			public String BODY
			{
				get { return _BODY; }
				set { _BODY = value; }
			}		
			public Nullable<Int32> Classificacao
			{
				get { return _Classificacao; }
				set { _Classificacao = value; }
			}		
			public String Anexo
			{
				get { return _Anexo; }
				set { _Anexo = value; }
			}		
			public Nullable<Boolean> Ativo
			{
				get { return _Ativo; }
				set { _Ativo = value; }
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

