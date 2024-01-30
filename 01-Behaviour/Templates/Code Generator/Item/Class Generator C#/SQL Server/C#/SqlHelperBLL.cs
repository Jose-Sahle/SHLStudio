/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
**********************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using #NAMESPACEDAL#;

namespace #NAMESPACEBLL#
{ 
    public class SQLHelperController
    {
        public void SetConnection(String ConnectionString)
        {
            SQLHelperDAL sqlHelperDAL = new SQLHelperDAL();

            sqlHelperDAL.SetConnection(ConnectionString);
        }
    }
}