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
	public sealed partial class AGENDAMENTO : BaseModel<AGENDAMENTO>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public AGENDAMENTO()
			{
			}

			public AGENDAMENTO(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _IDAGENDAMENTO;
			Nullable<Int32> _IDROTINA;
			Nullable<DateTime> _DATAINICIO;
			String _HORAINICIO;
			Nullable<DateTime> _DATAFIM;
			String _HORAFIM;
			Nullable<Int32> _INTERVALO;
			Nullable<Int32> _REPETICAO;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> IDAGENDAMENTO
			{
				get { return _IDAGENDAMENTO; }
				set { _IDAGENDAMENTO = value; }
			}		
			public Nullable<Int32> IDROTINA
			{
				get { return _IDROTINA; }
				set { _IDROTINA = value; }
			}		
			public Nullable<DateTime> DATAINICIO
			{
				get { return _DATAINICIO; }
				set { _DATAINICIO = value; }
			}		
			public String HORAINICIO
			{
				get { return _HORAINICIO; }
				set { _HORAINICIO = value; }
			}		
			public Nullable<DateTime> DATAFIM
			{
				get { return _DATAFIM; }
				set { _DATAFIM = value; }
			}		
			public String HORAFIM
			{
				get { return _HORAFIM; }
				set { _HORAFIM = value; }
			}		
			public Nullable<Int32> INTERVALO
			{
				get { return _INTERVALO; }
				set { _INTERVALO = value; }
			}		
			public Nullable<Int32> REPETICAO
			{
				get { return _REPETICAO; }
				set { _REPETICAO = value; }
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

