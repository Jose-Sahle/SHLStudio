/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Insert a record in the table #TABLE#
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE #TABLEWITHOUTPREFIXTABLE#_Insert
(
	<allfieldslessprimarykey>
	var_#FIELD# IN #TYPEDBORACLE##COMMAAFTER#
	</allfieldslessprimarykey>
	,var_IdReturn OUT INTEGER
)
IS
BEGIN
	INSERT INTO #TABLE#
	(
		<allfieldslessprimarykey>
		#COMMABEFORE##FIELD#
		</allfieldslessprimarykey>
	)
	VALUES
	(
		<allfieldslessprimarykey>
		#COMMABEFORE#var_#FIELD#
		</allfieldslessprimarykey>
	)
	RETURNING #PRIMARYKEY# INTO var_IdReturn;	
END #TABLEWITHOUTPREFIXTABLE#_Insert;
GO
