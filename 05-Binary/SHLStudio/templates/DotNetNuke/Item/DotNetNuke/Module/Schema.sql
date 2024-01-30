/**********************************************************
  AUTHOR	: #AUTHOR#
  VERSION	: #VERSION#
  DATE		: #DATETIME#
  #DESCRIPTION#
**********************************************************/
IF NOT EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'{databaseOwner}[{objectQualifier}YOURTABLE]') and OBJECTPROPERTY(ID, N'IsTable') = 1)
BEGIN
	CREATE TABLE {databaseOwner}[{objectQualifier}YOURTABLE]
	(
		idYOURTABLE INT NOT NULL IDENTITY(1,1),
	)
	
	ALTER TABLE {databaseOwner}[{objectQualifier}YOURTABLE]
	ADD CONSTRAINT [PK_{objectQualifier}YOURTABLE]
	PRIMARY KEY CLUSTERED ([idYOURTABLE])
		
	CREATE NONCLUSTERED INDEX [IX_{objectQualifier}YOURTABLE]
	ON {databaseOwner}[{objectQualifier}YOURTABLE] ([ModuleID])	
	
	ALTER TABLE {databaseOwner}[{objectQualifier}YOURTABLE]
	WITH NOCHECK ADD CONSTRAINT 	[FK_{objectQualifier}YOURTABLE_{objectQualifier}Modules]
	FOREIGN KEY ([ModuleID]) 
	REFERENCES {databaseOwner}[{objectQualifier}Modules]([ModuleID]) 
	ON DELETE CASCADE NOT FOR REPLICATION	
END
GO

