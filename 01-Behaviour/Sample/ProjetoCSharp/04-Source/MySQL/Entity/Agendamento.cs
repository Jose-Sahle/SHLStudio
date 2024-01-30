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
	public sealed partial class agendamento : BaseModel<agendamento>
	{
		//Create the Constructors/Destructors methods
		#region [ Constructors/Destructors ]
			public agendamento()
			{
			}

			public agendamento(IDataReader reader) : base(reader)
			{
			}
		#endregion

		// Create the class members variables
		#region [ Private Members ]
			Nullable<Int32> _idAgendamento;
			Nullable<Int32> _idRotina;
			Nullable<DateTime> _DataInicio;
			String _HoraInicio;
			Nullable<DateTime> _DataFim;
			String _HoraFim;
			Nullable<Int32> _Intervalo;
			Nullable<Int32> _Repeticao;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idAgendamento
			{
				get { return _idAgendamento; }
				set { _idAgendamento = value; }
			}		
			public Nullable<Int32> idRotina
			{
				get { return _idRotina; }
				set { _idRotina = value; }
			}		
			public Nullable<DateTime> DataInicio
			{
				get { return _DataInicio; }
				set { _DataInicio = value; }
			}		
			public String HoraInicio
			{
				get { return _HoraInicio; }
				set { _HoraInicio = value; }
			}		
			public Nullable<DateTime> DataFim
			{
				get { return _DataFim; }
				set { _DataFim = value; }
			}		
			public String HoraFim
			{
				get { return _HoraFim; }
				set { _HoraFim = value; }
			}		
			public Nullable<Int32> Intervalo
			{
				get { return _Intervalo; }
				set { _Intervalo = value; }
			}		
			public Nullable<Int32> Repeticao
			{
				get { return _Repeticao; }
				set { _Repeticao = value; }
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

