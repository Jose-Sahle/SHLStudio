/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Delete a record in the table #TABLE#
**********************************************************/
--Create the SQL for the stored procedure
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[#TABLEWITHOUTPREFIXTABLE#_Delete]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
	drop procedure [dbo].[#TABLEWITHOUTPREFIXTABLE#_Delete]
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO

CREATE PROCEDURE [dbo].[#TABLEWITHOUTPREFIXTABLE#_Delete]
(
	@#PRIMARYKEY# #TYPEPRIMARYKEYSQLSERVER#
)
AS
BEGIN
	DELETE FROM #TABLE#
	WHERE [#PRIMARYKEY#] = @#PRIMARYKEY#
END
GO


CREATE PROCEDURE dbo.[#TABLEWITHOUTPREFIXTABLE#_DeleteList]
(
	@#PRIMARYKEY# #TYPEPRIMARYKEYSQLSERVER# = NULL,
	<allfieldslessprimarykey>
	@#FIELD# #TYPEDBSQLSERVER# = NULL#COMMAAFTER#
	</allfieldslessprimarykey>
)
AS
BEGIN
	DELETE FROM dbo.[#TABLEWITHOUTPREFIXTABLE#]
	WHERE 
		([#PRIMARYKEY#] = @#PRIMARYKEY# OR @#PRIMARYKEY# IS NULL)
		<allfieldslessprimarykey>
	  AND ([#FIELD#] = @#FIELD# OR @#FIELD# IS NULL)
		</allfieldslessprimarykey>       
END
GO

-- tem um problema na procedure


GRANT EXECUTE ON [dbo].[#TABLEWITHOUTPREFIXTABLE#_Delete] TO [Public]
GO

GRANT VIEW DEFINITION ON [dbo].[#TABLEWITHOUTPREFIXTABLE#_Delete] TO [Public]
GO
