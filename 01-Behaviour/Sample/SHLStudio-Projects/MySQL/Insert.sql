/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Insert a record in the table #TABLE#
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS #TABLEWITHOUTPREFIXTABLE#_Insert
GO
CREATE PROCEDURE #TABLEWITHOUTPREFIXTABLE#_Insert
(
	<allfieldslessprimarykey>
	#COMMABEFORE#var_#FIELD# #TYPEDBMYSQL#
	</allfieldslessprimarykey>
	,OUT var_IdReturn INT
) 
BEGIN
	INSERT INTO #TABLE#
	(
		<allfieldslessprimarykey>
		#COMMABEFORE#`#FIELD#`
		</allfieldslessprimarykey>
	)
	VALUES
	(
		<allfieldslessprimarykey>
		var_#FIELD##COMMAAFTER#
		</allfieldslessprimarykey>
	);

	SET var_IdReturn = LAST_INSERT_ID(); 
END
GO
