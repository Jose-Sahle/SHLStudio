/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Update a record in the table #TABLE#
**********************************************************/
/*Create the SQL for the stored procedure*/
DROP PROCEDURE IF EXISTS #TABLEWITHOUTPREFIXTABLE#_Update
GO
CREATE PROCEDURE #TABLEWITHOUTPREFIXTABLE#_Update
(
    var_#PRIMARYKEY# #TYPEPRIMARYKEYMYSQL#,
    <allfieldslessprimarykey>
    var_#FIELD# #TYPEDBMYSQL##COMMAAFTER#
    </allfieldslessprimarykey>
)
BEGIN
    UPDATE 
		#TABLE# 
	SET
		<allfieldslessprimarykey>
		#COMMABEFORE#`#FIELD#` = COALESCE(var_#FIELD#, `#FIELD#`)
		</allfieldslessprimarykey>
    WHERE 
		`#PRIMARYKEY#` = var_#PRIMARYKEY#;		
END
GO
