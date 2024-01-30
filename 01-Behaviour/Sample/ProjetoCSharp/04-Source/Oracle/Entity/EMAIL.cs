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
	public sealed partial class EMAIL : BaseModel<EMAIL>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public EMAIL()
			{
			}

			public EMAIL(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _IDEMAIL;
			Nullable<Int32> _IDROTINA;
			String _FROMEMAIL;
			String _TOEMAIL;
			String _SUBJECTEMAIL;
			String _TYPEEMAIL;
			String _BODYEMAIL;
			Nullable<Int32> _CLASSIFICACAO;
			String _ANEXO;
			Nullable<Int32> _ATIVO;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> IDEMAIL
			{
				get { return _IDEMAIL; }
				set { _IDEMAIL = value; }
			}		
			public Nullable<Int32> IDROTINA
			{
				get { return _IDROTINA; }
				set { _IDROTINA = value; }
			}		
			public String FROMEMAIL
			{
				get { return _FROMEMAIL; }
				set { _FROMEMAIL = value; }
			}		
			public String TOEMAIL
			{
				get { return _TOEMAIL; }
				set { _TOEMAIL = value; }
			}		
			public String SUBJECTEMAIL
			{
				get { return _SUBJECTEMAIL; }
				set { _SUBJECTEMAIL = value; }
			}		
			public String TYPEEMAIL
			{
				get { return _TYPEEMAIL; }
				set { _TYPEEMAIL = value; }
			}		
			public String BODYEMAIL
			{
				get { return _BODYEMAIL; }
				set { _BODYEMAIL = value; }
			}		
			public Nullable<Int32> CLASSIFICACAO
			{
				get { return _CLASSIFICACAO; }
				set { _CLASSIFICACAO = value; }
			}		
			public String ANEXO
			{
				get { return _ANEXO; }
				set { _ANEXO = value; }
			}		
			public Nullable<Int32> ATIVO
			{
				get { return _ATIVO; }
				set { _ATIVO = value; }
			}		
		#endregion

		#region [ Relationship properties ]
			public ROTINA GP_ROTINA_FK
			{
				get;
				set;
			}
		#endregion
	}
}

