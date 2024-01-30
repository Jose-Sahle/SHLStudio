/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Data.OleDb;

namespace #NAMESPACEDAL#
{ 
    public class SQLHelperDAL
    {
        public void SetConnection(String connectionString)
        {
            SQLHelper.SetConnection(connectionString);
        }
    }
}