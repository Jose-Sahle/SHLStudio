/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 26/01/2024 09:10:52
**********************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Data;
using System.Diagnostics;
using System.Data.SqlClient;

namespace GPRotina.DAL
{
	public abstract class BaseDAL<T>
	{
		public BaseDAL()
		{
		
		}

		private StringBuilder _sb;
		protected StringBuilder Query
		{
			get
			{
				if (_sb == null) _sb = new StringBuilder();
				return _sb;
			}
		}

		public abstract T Select(Int32 key);
		public abstract List<T> SelectList();
		public abstract T Select(T entity);
		public abstract List<T> SelectList(T entity);
		public abstract Int32 Insert(T entity);
		public abstract Int32 Insert(T entity, SqlTransaction oSqlTransaction);
		public abstract void Update(T entiy);
		public abstract void Update(T entity, SqlTransaction oSqlTransaction);
		public abstract void Delete(Int32 key);
		public abstract void Delete(Int32 key, SqlTransaction oSqlTransaction);

		protected List<T> ReturnList(string procedure, ArrayList parameters)
		{
			List<T> returnlist = new List<T>();

			using (SqlDataReader dataReader = SQLHelper.ExecuteReader(procedure, parameters))
			{
				if (dataReader.HasRows)
				{
					returnlist = new List<T>();

					while (dataReader.Read())
					{
						T obj = default(T);
						obj = (T)Activator.CreateInstance(typeof(T), dataReader);
						returnlist.Add(obj);
					}
				}
			}

			return returnlist;
		}

		protected List<T> ReturnList(string procedure)
		{

			List<T> returnlist = new List<T>();

			using (SqlDataReader dataReader = SQLHelper.ExecuteReader(procedure))
			{
				if (dataReader.HasRows)
				{
					returnlist = new List<T>();
					while (dataReader.Read())
					{
						T obj;
						obj = (T)Activator.CreateInstance(typeof(T), dataReader);
						returnlist.Add(obj);
					}
				}
			}

			return returnlist;
		}

		protected T ReturnUnique(String commandText, ArrayList parameters)
		{
			T obj = default(T);

			using (SqlDataReader dataReader = SQLHelper.ExecuteReader(commandText, parameters))
			{
				if (dataReader.HasRows)
				{
					dataReader.Read();
					obj = (T)Activator.CreateInstance(typeof(T), dataReader);
				}
			}

			return obj;
		}

		protected T ReturnUnique(string commandText)
		{
			T obj = default(T);

			using (SqlDataReader dataReader = SQLHelper.ExecuteReader(commandText))
			{
				if (dataReader.HasRows)
				{
					dataReader.Read();
					obj = (T)Activator.CreateInstance(typeof(T), dataReader);
				}
			}

			return obj;
		}

		protected void ClearQuery()
		{
			if (_sb != null)
			{
				_sb.Remove(0, _sb.Length);
			}
		}
	}
}

