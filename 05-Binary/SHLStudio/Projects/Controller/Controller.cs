/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
**********************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System.Text;

using #NAMESPACEBLL#;
using #NAMESPACEENTITY#;

using System.Data.SqlClient;

namespace Controllers
{ 
	[Route("api/[controller]")]
	[ApiController]
	public class  <firstupper>#TABLE#</firstupper>Controller : ControllerBase
	{
		//SHLSTUDIO_USER_AREA_START_1
		//SHLSTUDIO_USER_AREA_END_1

		[HttpGet]
		[Route("SelectAll/")]
		public List<#TABLEWITHOUTPREFIXTABLE#> SelectAll()
		{
			#TABLEWITHOUTPREFIXTABLE##SUFFIXBLL# bl = new #TABLEWITHOUTPREFIXTABLE##SUFFIXBLL#();
			#TABLEWITHOUTPREFIXTABLE# entity = new #TABLEWITHOUTPREFIXTABLE#();

			return bl.SelectList(grupo, entity);
		}

		[HttpPost]
		[Route("Insert/")]
		public void Insert(String grupo, [FromBody] List<#TABLEWITHOUTPREFIXTABLE#> entities)
		{
			#TABLEWITHOUTPREFIXTABLE##SUFFIXBLL# bl = new #TABLEWITHOUTPREFIXTABLE##SUFFIXBLL#();
			List<RETORNO> retornos = new List<RETORNO>();

			try
			{
				foreach (#TABLEWITHOUTPREFIXTABLE# entity in entities)
					bl.Insert(grupo, entity, ref retornos);
			}
			catch (Exception)
			{
				throw;
			}

			return retornos;
		}
		
		// POST: api/ClienteVarejo
		[HttpPut]
		[Route("Update/")]
		public void Update([FromBody] List<#TABLEWITHOUTPREFIXTABLE#> entities)
		{
			#TABLEWITHOUTPREFIXTABLE##SUFFIXBLL# bl = new #TABLEWITHOUTPREFIXTABLE##SUFFIXBLL#();

			try
			{
				foreach (#TABLEWITHOUTPREFIXTABLE# entity in entities)
					bl.Update(grupo, entity, ref retornos);
			}
			catch (Exception)
			{
				throw;
			}
		}
		
		[HttpDelete]
		[Route("Delete/")]
		public void Delete([FromBody] List<#TABLEWITHOUTPREFIXTABLE#> entities)
		{
			#TABLEWITHOUTPREFIXTABLE##SUFFIXBLL# bl = new #TABLEWITHOUTPREFIXTABLE##SUFFIXBLL#();
			List<RETORNO> retornos = new List<RETORNO>();

			try
			{
				foreach (#TABLEWITHOUTPREFIXTABLE# entity in entities)
					bl.Update(grupo, entity, ref retornos);
			}
			catch (Exception)
			{
				throw ex;
			}

			return retornos;
		}
	}    
}