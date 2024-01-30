/**********************************************************
  AUTHOR	: 
  VERSION	: 1.0.0.0
  DATE		: 26/01/2024 09:10:55
  FUNCTION	: Select records from table GP_DLLParametros filtered by 
		  parameters passed into the procedure
**********************************************************/
--Create the SQL for the stored procedure
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[DLLParametros_Select]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
	drop procedure [dbo].[DLLParametros_Select]
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO

CREATE PROCEDURE [dbo].[DLLParametros_Select]
(
    @idDLLParametros INT = NULL,
    @idDLL INT = NULL,
    @Nome VARCHAR(50) = NULL,
    @Valor VARCHAR(8000) = NULL,
    @Tipo INT = NULL,
    @Formato VARCHAR(2) = NULL
)
AS
BEGIN
    SELECT
		[idDLLParametros],
		[idDLL],
		[Nome],
		[Valor],
		[Tipo],
		[Formato]
    FROM 
		[GP_DLLParametros] WITH (NOLOCK)
    WHERE 
		([idDLLParametros] = @idDLLParametros OR @idDLLParametros IS NULL)
	  AND ([idDLL] = @idDLL OR @idDLL IS NULL)
	  AND ([Nome] = @Nome OR @Nome IS NULL)
	  AND ([Valor] = @Valor OR @Valor IS NULL)
	  AND ([Tipo] = @Tipo OR @Tipo IS NULL)
	  AND ([Formato] = @Formato OR @Formato IS NULL)
END
GO

GRANT EXECUTE ON [dbo].[DLLParametros_Select] TO [Public]
GO

GRANT VIEW DEFINITION ON [dbo].[DLLParametros_Select] TO [Public]
GO

