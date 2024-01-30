/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
**********************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Data;
using System.Diagnostics;
using System.Data.OleDb;

namespace #NAMESPACEDAL#
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
		
		public OleDbTransaction GetTransaction()
		{
			OleDbTransaction transaction = null;

			transaction = SQLHelper.GetTransaction();

			return transaction;
		}		

		protected List<T> ReturnList(string procedure)
		{
			List<T> returnlist = new List<T>();

			using (OleDbDataReader dataReader = SQLHelper.ExecuteReader(procedure))
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

		protected T ReturnUnique(String commandText)
		{
			T obj = default(T);

			using (OleDbDataReader dataReader = SQLHelper.ExecuteReader(commandText))
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
