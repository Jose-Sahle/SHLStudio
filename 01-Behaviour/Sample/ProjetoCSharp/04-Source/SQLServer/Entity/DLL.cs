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
	public sealed partial class DLL : BaseModel<DLL>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public DLL()
			{
			}

			public DLL(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _idDLL;
			Nullable<Int32> _idRotina;
			Nullable<Int32> _Ordem;
			String _Nome;
			String _Assembly;
			Nullable<Int32> _Dependencia;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idDLL
			{
				get { return _idDLL; }
				set { _idDLL = value; }
			}		
			public Nullable<Int32> idRotina
			{
				get { return _idRotina; }
				set { _idRotina = value; }
			}		
			public Nullable<Int32> Ordem
			{
				get { return _Ordem; }
				set { _Ordem = value; }
			}		
			public String Nome
			{
				get { return _Nome; }
				set { _Nome = value; }
			}		
			public String Assembly
			{
				get { return _Assembly; }
				set { _Assembly = value; }
			}		
			public Nullable<Int32> Dependencia
			{
				get { return _Dependencia; }
				set { _Dependencia = value; }
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

