/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  #DESCRIPTION#
**********************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Data;
using System.Diagnostics;
using System.Reflection;
using System.Data.SqlClient;

using Microsoft.ApplicationBlocks.Data;

using DotNetNuke;
using DotNetNuke.Data;
using DotNetNuke.Common.Utilities;
using DotNetNuke.Framework.Providers;


namespace #NAMESPACE#.Components
{ 
	public partial class SqlDataProvider : DataProvider
	{
		#region [ Private Members ]
			private const String ProviderType = "data";

			private DotNetNuke.Framework.Providers.ProviderConfiguration _providerConfiguration = DotNetNuke.Framework.Providers.ProviderConfiguration.GetProviderConfiguration(ProviderType);

			private String _connectionString;
			private String _upgradeConnectionString;
			private String _providerPath;
			private String _objectQualifier;
			private String _databaseOwner;			
		#endregion

		#region [ Constructor ]
			public SqlDataProvider()
			{
				DotNetNuke.Framework.Providers.Provider objProvider  =  (DotNetNuke.Framework.Providers.Provider)_providerConfiguration.Providers[_providerConfiguration.DefaultProvider];

				//Read the attributes for this provider
				_connectionString = Config.GetConnectionString();
				_upgradeConnectionString = _connectionString;

				_providerPath = objProvider.Attributes["providerPath"];

				_objectQualifier = objProvider.Attributes["objectQualifier"];

				if (_objectQualifier != "" && !_objectQualifier.EndsWith("_") )
					_objectQualifier += "_";

				_databaseOwner = objProvider.Attributes["databaseOwner"].ToString();
				_databaseOwner = "";

				if (_databaseOwner != "" && !_databaseOwner.EndsWith(".") )
					_databaseOwner += ".";
			}
		#endregion
	
		#region [ Properties ]
			public string ConnectionString
			{
				get { return _connectionString; }
			}
			
			public string ProviderPath
			{
				get { return _providerPath; }
			}
			
			public string ObjectQualifier
			{
				get { return _objectQualifier; }
			}
			
			public string DatabaseOwner
			{
				get { return _databaseOwner; }
			}
		#endregion	
		
		#region [ Private Methods ]
			private string GetFullyQualifiedName(string name)
			{
				return DatabaseOwner + ObjectQualifier + name;
			}
			
			private object GetNull(object field)
			{
				return DotNetNuke.Common.Utilities.Null.GetNull(field, DBNull.Value);
			}			
		#endregion		
		
		#region [ Override Methods ]
			public override SqlTransaction GetTransaction()
			{
				SqlConnection conn = new SqlConnection();
				SqlTransaction transaction = null;

				conn.ConnectionString = ConnectionString;
				conn.Open();

				transaction = conn.BeginTransaction();

				return transaction;
			}
		
		<alltables>
			#region [ #TABLE# ]
				public override #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info Select#TABLEWITHOUTPREFIXTABLE#(Int32 p#PRIMARYKEY#)
				{
					SqlDataReader dataReader = null;
					#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity = new #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info();
					#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info returnentity = null;
					
					entity.#PRIMARYKEY# = p#PRIMARYKEY#;
					ConvertObject<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info> oConvertObject = new ConvertObject<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info>();
					
					try
					{
						dataReader = SqlHelper.ExecuteReader(ConnectionString, GetFullyQualifiedName("#TABLEWITHOUTPREFIXTABLE#_Select"), 
							entity.#PRIMARYKEY#,
							<allfieldslessprimarykey>
							entity.#FIELD##COMMAAFTER#
							</allfieldslessprimarykey>					
						);
												
						if (dataReader.HasRows)
						{
							dataReader.Read();

							returnentity = (#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info)oConvertObject.Convert(dataReader);
						}
					}
					finally
					{
						if( dataReader != null)
							dataReader.Close();
					}
					
					return returnentity;
				}
								
			
				public override #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info Select#TABLEWITHOUTPREFIXTABLE#(#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity)
				{
					SqlDataReader dataReader = null;
					#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info returnentity = null;
					ConvertObject<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info> oConvertObject = new ConvertObject<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info>();
					
					try
					{
						dataReader = SqlHelper.ExecuteReader(ConnectionString, GetFullyQualifiedName("#TABLEWITHOUTPREFIXTABLE#_Select"), 
							entity.#PRIMARYKEY#,
							<allfieldslessprimarykey>
							entity.#FIELD##COMMAAFTER#
							</allfieldslessprimarykey>					
						);
												
						if (dataReader.HasRows)
						{
							dataReader.Read();

							returnentity = (#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info)oConvertObject.Convert(dataReader);
						}
					}
					finally
					{
						if( dataReader != null)
							dataReader.Close();
					}
					
					return returnentity;
				}
				
				public override List<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info> SelectList#TABLEWITHOUTPREFIXTABLE#()
				{
					SqlDataReader dataReader = null;
					#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity = new #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info();
					List<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info> returnList = null;
					ConvertObject<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info> oConvertObject = new ConvertObject<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info>();
									
					try
					{
						dataReader = SqlHelper.ExecuteReader(ConnectionString, GetFullyQualifiedName("#TABLEWITHOUTPREFIXTABLE#_Select"), 
							entity.#PRIMARYKEY#,
							<allfieldslessprimarykey>
							entity.#FIELD##COMMAAFTER#
							</allfieldslessprimarykey>					
						);
						
						returnList = new List<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info>();
						
						if (dataReader.HasRows)
						{
							while (dataReader.Read())
							{
								entity = (#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info)oConvertObject.Convert(dataReader);
								returnList.Add(entity);
							}
						}
				}
					finally
					{
						if( dataReader != null)
							dataReader.Close();
					}
					
					return returnList;
				}
				
				public override List<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info> SelectList#TABLEWITHOUTPREFIXTABLE#(#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity)
				{
					SqlDataReader dataReader = null;
					List<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info> returnList = null;
					ConvertObject<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info> oConvertObject = new ConvertObject<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info>();
					
					try
					{
						dataReader = SqlHelper.ExecuteReader(ConnectionString, GetFullyQualifiedName("#TABLEWITHOUTPREFIXTABLE#_Select"), 
							entity.#PRIMARYKEY#,
							<allfieldslessprimarykey>
							entity.#FIELD##COMMAAFTER#
							</allfieldslessprimarykey>					
						);
						
						returnList = new List<#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info>();
						
						if (dataReader.HasRows)
						{
							while (dataReader.Read())
							{
								entity = (#PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info)oConvertObject.Convert(dataReader);
								returnList.Add(entity);
							}
							
						}
					}
					finally
					{
						if( dataReader != null)
							dataReader.Close();
					}
					
					return returnList;
				}
				
				public override #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info Insert#TABLEWITHOUTPREFIXTABLE#( #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity)
				{
					object retIdentity;
					
					retIdentity = SqlHelper.ExecuteScalar(ConnectionString, GetFullyQualifiedName("#TABLEWITHOUTPREFIXTABLE#_Insert"), 
							<allfieldslessprimarykey>
							entity.#FIELD##COMMAAFTER#
							</allfieldslessprimarykey>					
						);
					
					if(retIdentity != null)
						entity.#PRIMARYKEY# = Convert.ToInt32(retIdentity.ToString());					
					
					return entity;
				}

				public override #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info Insert#TABLEWITHOUTPREFIXTABLE#(SqlTransaction transaction, #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity)
				{
					object retIdentity;
					
					retIdentity = SqlHelper.ExecuteScalar(transaction, GetFullyQualifiedName("#TABLEWITHOUTPREFIXTABLE#_Insert"), 
							<allfieldslessprimarykey>
							entity.#FIELD##COMMAAFTER#
							</allfieldslessprimarykey>					
						);
					
					if(retIdentity != null)
						entity.#PRIMARYKEY# = Convert.ToInt32(retIdentity.ToString());					
					
					return entity;
				}
				
				public override void Update#TABLEWITHOUTPREFIXTABLE#( #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity  )
				{
					SqlHelper.ExecuteNonQuery(ConnectionString, GetFullyQualifiedName("#TABLEWITHOUTPREFIXTABLE#_Update"), 
						entity.#PRIMARYKEY#,
						<allfieldslessprimarykey>
						entity.#FIELD##COMMAAFTER#
						</allfieldslessprimarykey>					
					);
				}
				
				public override void Update#TABLEWITHOUTPREFIXTABLE#(SqlTransaction transaction, #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity  )
				{
					SqlHelper.ExecuteNonQuery(transaction, GetFullyQualifiedName("#TABLEWITHOUTPREFIXTABLE#_Update"), 
						entity.#PRIMARYKEY#,
						<allfieldslessprimarykey>
						entity.#FIELD##COMMAAFTER#
						</allfieldslessprimarykey>					
					);
				}
				
				public override void Delete#TABLEWITHOUTPREFIXTABLE#( Int32 p#PRIMARYKEY# )
				{
					SqlHelper.ExecuteNonQuery( ConnectionString, GetFullyQualifiedName("#TABLEWITHOUTPREFIXTABLE#_Delete"), p#PRIMARYKEY# );
				}				
				
				public override void Delete#TABLEWITHOUTPREFIXTABLE#(SqlTransaction transaction, Int32 p#PRIMARYKEY# )
				{
					SqlHelper.ExecuteNonQuery( transaction, GetFullyQualifiedName("#TABLEWITHOUTPREFIXTABLE#_Delete"), p#PRIMARYKEY# );
				}				
				
				public override void Delete#TABLEWITHOUTPREFIXTABLE#( #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity )
				{
					SqlHelper.ExecuteNonQuery( ConnectionString, GetFullyQualifiedName("#TABLEWITHOUTPREFIXTABLE#_DeleteList"),
						entity.#PRIMARYKEY#,
						<allfieldslessprimarykey>
						entity.#FIELD##COMMAAFTER#
						</allfieldslessprimarykey>					
					);
					
				}				
				
				public override void Delete#TABLEWITHOUTPREFIXTABLE#(SqlTransaction transaction, #PREFIX##TABLEWITHOUTPREFIXTABLE##SUFFIX#Info entity )
				{
					SqlHelper.ExecuteNonQuery( transaction, GetFullyQualifiedName("#TABLEWITHOUTPREFIXTABLE#_DeleteList"), 
						entity.#PRIMARYKEY#,
						<allfieldslessprimarykey>
						entity.#FIELD##COMMAAFTER#
						</allfieldslessprimarykey>					
					);					
				}				
				
			#endregion
			
		</alltables>	
		#endregion
	}
	
	public class ConvertObject<T>
	{
		public T Convert(IDataReader dr)
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
