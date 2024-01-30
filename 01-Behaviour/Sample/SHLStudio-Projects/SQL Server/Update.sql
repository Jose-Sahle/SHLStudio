/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Update a record in the table #TABLE#
**********************************************************/
--Create the SQL for the stored procedure
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[#TABLEWITHOUTPREFIXTABLE#_Update]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
	drop procedure [dbo].[#TABLEWITHOUTPREFIXTABLE#_Update]
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO

CREATE PROCEDURE [dbo].[#TABLEWITHOUTPREFIXTABLE#_Update]
(
	 @#PRIMARYKEY# #TYPEPRIMARYKEYSQLSERVER#,
	<allfieldslessprimarykey>
	@#FIELD# #TYPEDBSQLSERVER# = NULL#COMMAAFTER#
	</allfieldslessprimarykey>
)
AS
BEGIN
	UPDATE 
		#TABLE# 
	SET
		<allfieldslessprimarykey>
		#COMMABEFORE#[#FIELD#] = @#FIELD#
		</allfieldslessprimarykey>
	WHERE 
		[#PRIMARYKEY#] = @#PRIMARYKEY#
END
GO

GRANT EXECUTE ON [dbo].[#TABLEWITHOUTPREFIXTABLE#_Update] TO [Public]
GO

GRANT VIEW DEFINITION ON [dbo].[#TABLEWITHOUTPREFIXTABLE#_Update] TO [Public]
GO
