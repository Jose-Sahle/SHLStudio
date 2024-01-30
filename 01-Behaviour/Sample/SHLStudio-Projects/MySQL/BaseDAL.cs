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
using System.Reflection;
using MySql.Data.MySqlClient;

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

        public abstract T Select(Int32 key);
        public abstract List<T> SelectList();
        public abstract T Select(T entity);
        public abstract List<T> SelectList(T entity);
        public abstract Int32 Insert(T entity);
        public abstract Int32 Insert(T entity, MySqlTransaction oSqlTransaction);
        public abstract void Update(T entiy);
        public abstract void Update(T entity, MySqlTransaction oSqlTransaction);
        public abstract void Delete(Int32 key);
        public abstract void Delete(Int32 key, MySqlTransaction oSqlTransaction);

        protected List<T> ReturnList(string procedure, ArrayList parameters)
        {
            List<T> returnlist = new List<T>();

            using (MySqlDataReader dataReader = SQLHelper.ExecuteReader(procedure, parameters))
            {
                if (dataReader.HasRows)
                {
                    returnlist = new List<T>();
                    
                    while (dataReader.Read())
                    {
                        T obj = default(T);
                        obj = (T)ConvertObject(dataReader);
                        returnlist.Add(obj);
                    }
                }
            }

            return returnlist;

        }

        protected List<T> ReturnList(string procedure)
        {

            List<T> returnlist = new List<T>();

            using (MySqlDataReader dataReader = SQLHelper.ExecuteReader(procedure))
            {
                if (dataReader.HasRows)
                {
                    returnlist = new List<T>();
                    while (dataReader.Read())
                    {
                        T obj;
                        obj = (T)ConvertObject(dataReader);
                        returnlist.Add(obj);
                    }
                }
            }

            return returnlist;

        }

        protected T ReturnUnique(String commandText, ArrayList parameters)
        {
            T obj = default(T);

            using (MySqlDataReader dataReader = SQLHelper.ExecuteReader(commandText, parameters))
            {
                if (dataReader.HasRows)
                {
                    dataReader.Read();
                    obj = (T)ConvertObject(dataReader);
                }
            }

            return obj;
        }

        protected T ReturnUnique(string commandText)
        {
            T obj = default(T);

            using (MySqlDataReader dataReader = SQLHelper.ExecuteReader(commandText))
            {
                if (dataReader.HasRows)
                {
                    dataReader.Read();
                    obj = (T)ConvertObject(dataReader);
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

        public T ConvertObject(MySqlDataReader dr)
        {
		DataRow row;
		DataTable dtSchema = dr.GetSchemaTable();
		DataTable dt = new DataTable();

		List<DataColumn> listCols = new List<DataColumn>();
		if (dtSchema != null)
		{
			foreach (DataRow drow in dtSchema.Rows)
			{
				string columnName = System.Convert.ToString(drow["ColumnName"]);
				DataColumn column = new DataColumn(columnName,(Type)(drow["DataType"]));
				listCols.Add(column);
				dt.Columns.Add(column);
			}
		}

		row = dt.NewRow();
		for (int i = 0; i < listCols.Count; i++)
		{
			row[((DataColumn)listCols[i])] = dr[i];
		}
		T outObject = (T)Assembly.GetAssembly(typeof(T)).CreateInstance(typeof(T).ToString());


		CopyProperties(row, outObject);
		
		return outObject;
        }

        private void CopyProperties(DataRow inObject, object outObject)
        {
		PropertyInfo[] propsOut = outObject.GetType().GetProperties();
		PropertyInfo propOut = null;

		foreach (DataColumn dc in inObject.Table.Columns)
		{
			propOut = propsOut.FirstOrDefault<PropertyInfo>(p => p.Name.ToLower() == dc.ColumnName.ToLower());
			if (propOut != null)
			{
				var value = inObject[dc.ColumnName];
				if (!(value is DBNull))
				{
					Type dataType = propOut.PropertyType;

					if (dataType.IsGenericType &&
						dataType.GetGenericTypeDefinition() == typeof(System.Nullable<>))
					{
						dataType = System.Nullable.GetUnderlyingType(dataType);
					}

					value = System.Convert.ChangeType(value, dataType);
					propOut.SetValue(outObject, value, null);
				}
			}
		}
        }

    }
}
