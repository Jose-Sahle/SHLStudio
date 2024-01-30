/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Insert a record in the table #TABLE#
**********************************************************/
--Create the SQL for the stored procedure
if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[#TABLEWITHOUTPREFIXTABLE#_Insert]') and OBJECTPROPERTY(id, N'IsProcedure') = 1)
	drop procedure [dbo].[#TABLEWITHOUTPREFIXTABLE#_Insert]
GO

SET QUOTED_IDENTIFIER ON
GO
SET ANSI_NULLS ON
GO

CREATE PROCEDURE [dbo].[#TABLEWITHOUTPREFIXTABLE#_Insert]
(
	<allfieldslessprimarykey>
	@#FIELD# #TYPEDBSQLSERVER# = NULL#COMMAAFTER#
	</allfieldslessprimarykey>
	,@IdReturn bigint output
) 
AS
BEGIN
	INSERT INTO #TABLE#
	(
		<allfieldslessprimarykey>
		#COMMABEFORE#[#FIELD#]
		</allfieldslessprimarykey>
	)
	VALUES
	(
		<allfieldslessprimarykey>
		#COMMABEFORE#@#FIELD#
		</allfieldslessprimarykey>
	)
	
	SET @IdReturn = SCOPE_IDENTITY()
END
GO

GRANT EXECUTE ON [dbo].[#TABLEWITHOUTPREFIXTABLE#_Insert] TO [Public]
GO

GRANT VIEW DEFINITION ON [dbo].[#TABLEWITHOUTPREFIXTABLE#_Insert] TO [Public]
GO
