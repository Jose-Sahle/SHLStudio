/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Select records from table #TABLE# filtered by 
		  parameters passed into the procedure
**********************************************************/
--Create the SQL for the stored procedure
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[#TABLEWITHOUTPREFIXTABLE#_Select]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
	drop procedure [dbo].[#TABLEWITHOUTPREFIXTABLE#_Select]
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO

CREATE PROCEDURE [dbo].[#TABLEWITHOUTPREFIXTABLE#_Select]
(
    @#PRIMARYKEY# #TYPEPRIMARYKEYSQLSERVER# = NULL,
    <allfieldslessprimarykey>
    @#FIELD# #TYPEDBSQLSERVER# = NULL#COMMAAFTER#
    </allfieldslessprimarykey>
)
AS
BEGIN
    SELECT
		[#PRIMARYKEY#],
		<allfieldslessprimarykey>
		[#FIELD#]#COMMAAFTER#
		</allfieldslessprimarykey>
    FROM 
		[#TABLE#] WITH (NOLOCK)
    WHERE 
		([#PRIMARYKEY#] = @#PRIMARYKEY# OR @#PRIMARYKEY# IS NULL)
		<allfieldslessprimarykey>
	  AND ([#FIELD#] = @#FIELD# OR @#FIELD# IS NULL)
		</allfieldslessprimarykey>       
END
GO

GRANT EXECUTE ON [dbo].[#TABLEWITHOUTPREFIXTABLE#_Select] TO [#GRANTUSER#]
GO

GRANT VIEW DEFINITION ON [dbo].[#TABLEWITHOUTPREFIXTABLE#_Select] TO [#GRANTUSER#]
GO
