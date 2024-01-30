/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 10/09/2014 19:45:48
**********************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using SHL.CEP.DAL;

namespace SHL.CEP.BLL
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
