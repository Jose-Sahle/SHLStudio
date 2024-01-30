
/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Update a record in the table #TABLE#
**********************************************************/
/*Create the SQL for the stored procedure*/
CREATE OR REPLACE PROCEDURE #TABLEWITHOUTPREFIXTABLE#_Update
(
	var_#PRIMARYKEY# IN #TYPEPRIMARYKEYORACLE#,
	<allfieldslessprimarykey>
	var_#FIELD# IN #TYPEDBORACLE##COMMAAFTER#
	</allfieldslessprimarykey>
)
IS 
BEGIN
	UPDATE 
		#TABLE# 
	SET
		<allfieldslessprimarykey>
		#COMMABEFORE##FIELD# = var_#FIELD#
		</allfieldslessprimarykey>
	WHERE 
		#PRIMARYKEY# = var_#PRIMARYKEY#;
		
END #TABLEWITHOUTPREFIXTABLE#_Update;
GO
