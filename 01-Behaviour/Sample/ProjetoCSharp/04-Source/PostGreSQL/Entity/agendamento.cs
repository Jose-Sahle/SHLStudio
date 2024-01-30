/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 08/04/2014 09:03:39
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
			Nullable<Int32> _idagendamento;
			Nullable<Int32> _idrotina;
			Nullable<DateTime> _datainicio;
			Nullable<DateTime> _horainicio;
			Nullable<DateTime> _datafim;
			Nullable<DateTime> _horafim;
			Nullable<Int32> _intervalo;
			Nullable<Int32> _repeticao;
		#endregion

		#region [ Properties ]
			public Nullable<Int32> idagendamento
			{
				get { return _idagendamento; }
				set { _idagendamento = value; }
			}		
			public Nullable<Int32> idrotina
			{
				get { return _idrotina; }
				set { _idrotina = value; }
			}		
			public Nullable<DateTime> datainicio
			{
				get { return _datainicio; }
				set { _datainicio = value; }
			}		
			public Nullable<DateTime> horainicio
			{
				get { return _horainicio; }
				set { _horainicio = value; }
			}		
			public Nullable<DateTime> datafim
			{
				get { return _datafim; }
				set { _datafim = value; }
			}		
			public Nullable<DateTime> horafim
			{
				get { return _horafim; }
				set { _horafim = value; }
			}		
			public Nullable<Int32> intervalo
			{
				get { return _intervalo; }
				set { _intervalo = value; }
			}		
			public Nullable<Int32> repeticao
			{
				get { return _repeticao; }
				set { _repeticao = value; }
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

