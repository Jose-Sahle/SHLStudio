/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 10/09/2014 19:45:48
**********************************************************/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Data.OleDb;

namespace SHL.CEP.DAL
{ 
    public class SQLHelperDAL
    {
        public void SetConnection(String connectionString)
        {
            SQLHelper.SetConnection(connectionString);
        }
    }
}
