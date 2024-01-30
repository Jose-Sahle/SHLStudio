/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  FUNCTION	: Delete a record in the table #TABLE#
**********************************************************/
CREATE OR REPLACE PROCEDURE #TABLEWITHOUTPREFIXTABLE#_Delete
(
	var_#PRIMARYKEY# IN #TYPEPRIMARYKEYORACLE#
)
IS
BEGIN
    DELETE FROM #TABLE#
    WHERE #PRIMARYKEY# = var_#PRIMARYKEY#;
END #TABLEWITHOUTPREFIXTABLE#_Delete;
GO
