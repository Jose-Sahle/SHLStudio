[Setup]
AppId=ShlStudio
AppName=SHL Studio
AppVersion=2.2.4
DefaultDirName={pf}\SHLInfo\SHLStudio
DefaultGroupName=SHL Studio
Compression=lzma2
SolidCompression=yes
OutputDir=Installer
OutputBaseFilename=shlstudiosetup
DisableStartupPrompt=yes
DisableWelcomePage=yes
DisableFinishedPage=yes
DisableProgramGroupPage=yes
DisableDirPage=yes
DisableReadyMemo=yes
Uninstallable=no
PrivilegesRequired=admin

[Icons]
Name: {group}\SHL Studio; Filename: {app}\SHLStudio.exe; WorkingDir: {app}

[Files]
Source: rabbitmq.4.dll; DestDir: {app}
Source: SHLStudio.dat; DestDir: {app}
Source: SHLStudio.exe; DestDir: {app}
Source: vcredist_x86.exe; DestDir: {app}; Flags: deleteafterinstall
Source: binaries\SciLexeru.dll; DestDir: {app}\binaries
Source: binaries\SHLDirU.dll; DestDir: {app}\binaries
Source: binaries\shlquery.dll; DestDir: {app}\binaries
Source: plugins\codegenerator_2000.dll; DestDir: {app}\plugins
Source: plugins\dotnetnukegenerator.dll; DestDir: {app}\plugins
Source: plugins\rabbitmq.4.dll; DestDir: {app}\plugins
Source: plugins\shlrabbitmq.dll; DestDir: {app}\plugins
Source: templates\Code Generator\Icons.xml; DestDir: {app}\templates\Code Generator
Source: templates\DotNetNuke\Icons.xml; DestDir: {app}\templates\DotNetNuke
Source: templates\Rabbit MQ Test\Icons.xml; DestDir: {app}\templates\Rabbit MQ Test
Source: templates\Code Generator\Icons\1_3E3E8C0E-96E6-45D0-A443-13E495D69385.bmp; DestDir: {app}\templates\Code Generator\Icons
Source: templates\Code Generator\Icons\1_50D23EF1-B85E-4D2C-B610-A48BEF47BAF88.bmp; DestDir: {app}\templates\Code Generator\Icons
Source: templates\Code Generator\Icons\1_A525422F-3A5F-446C-A3FC-54BB0FF4C5E7.bmp; DestDir: {app}\templates\Code Generator\Icons
Source: templates\Code Generator\Icons\1_CFD3347F-4C83-4EED-8F31-A48A511C3CAB.bmp; DestDir: {app}\templates\Code Generator\Icons
Source: templates\Code Generator\Icons\1_FC9575F8-4F93-4177-B845-85548C79EB3E.bmp; DestDir: {app}\templates\Code Generator\Icons
Source: templates\Code Generator\Icons\2_3E3E8C0E-96E6-45D0-A443-13E495D69385.bmp; DestDir: {app}\templates\Code Generator\Icons
Source: templates\Code Generator\Icons\2_50D23EF1-B85E-4D2C-B610-A48BEF47BAF88.bmp; DestDir: {app}\templates\Code Generator\Icons
Source: templates\Code Generator\Icons\2_A525422F-3A5F-446C-A3FC-54BB0FF4C5E7.bmp; DestDir: {app}\templates\Code Generator\Icons
Source: templates\Code Generator\Icons\2_CFD3347F-4C83-4EED-8F31-A48A511C3CAB.bmp; DestDir: {app}\templates\Code Generator\Icons
Source: templates\Code Generator\Icons\2_FC9575F8-4F93-4177-B845-85548C79EB3E.bmp; DestDir: {app}\templates\Code Generator\Icons
Source: templates\Code Generator\Item\Class Generator C#\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#
Source: templates\Code Generator\Item\Class Generator C#\Access\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\BaseDAL.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\BaseDAL.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\BaseModel.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\BaseModel.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\BusinessLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\BusinessLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\DataAcessLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\DataAcessLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\Database.dt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\Database.dt.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\EntityLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\EntityLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\SQLHelper.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\Access\C#\SQLHelper.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\BaseDAL.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\BaseDAL.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\BaseModel.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\BaseModel.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\BusinessLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\BusinessLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\ColumnQuery.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\DataAcessLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\DataAcessLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\Database.dt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\Database.dt.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\DatabaseQuery.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\EntityLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\EntityLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\SQLHelper.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\SQLHelper.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\C#\TableQuery.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Source: templates\Code Generator\Item\Class Generator C#\MySQL\Script\Delete.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\Script
Source: templates\Code Generator\Item\Class Generator C#\MySQL\Script\Delete.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\Script
Source: templates\Code Generator\Item\Class Generator C#\MySQL\Script\Insert.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\Script
Source: templates\Code Generator\Item\Class Generator C#\MySQL\Script\Insert.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\Script
Source: templates\Code Generator\Item\Class Generator C#\MySQL\Script\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\Script
Source: templates\Code Generator\Item\Class Generator C#\MySQL\Script\Select.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\Script
Source: templates\Code Generator\Item\Class Generator C#\MySQL\Script\Select.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\Script
Source: templates\Code Generator\Item\Class Generator C#\MySQL\Script\Update.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\Script
Source: templates\Code Generator\Item\Class Generator C#\MySQL\Script\Update.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\Script
Source: templates\Code Generator\Item\Class Generator C#\Oracle\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\BaseDAL.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\BaseDAL.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\BaseModel.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\BaseModel.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\BusinessLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\BusinessLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\ColumnQuery.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\DataAcessLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\DataAcessLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\Database.dt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\Database.dt.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\DatabaseQuery.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\EntityLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\EntityLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\SQLHelper.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\SQLHelper.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\C#\TableQuery.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Source: templates\Code Generator\Item\Class Generator C#\Oracle\Script\Delete.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\Script
Source: templates\Code Generator\Item\Class Generator C#\Oracle\Script\Delete.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\Script
Source: templates\Code Generator\Item\Class Generator C#\Oracle\Script\Insert.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\Script
Source: templates\Code Generator\Item\Class Generator C#\Oracle\Script\Insert.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\Script
Source: templates\Code Generator\Item\Class Generator C#\Oracle\Script\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\Script
Source: templates\Code Generator\Item\Class Generator C#\Oracle\Script\Select.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\Script
Source: templates\Code Generator\Item\Class Generator C#\Oracle\Script\Select.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\Script
Source: templates\Code Generator\Item\Class Generator C#\Oracle\Script\Update.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\Script
Source: templates\Code Generator\Item\Class Generator C#\Oracle\Script\Update.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\BaseDAL.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\BaseDAL.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\BaseModel.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\BaseModel.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\BusinessLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\BusinessLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\ColumnQuery.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\DataAcessLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\DataAcessLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\Database.dt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\Database.dt.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\DatabaseQuery.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\EntityLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\EntityLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\SQLHelper.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\SQLHelper.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\TableQuery.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Delete.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Delete.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Insert.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Insert.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Select.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Select.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Update.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Update.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\BaseDAL.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\BaseDAL.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\BaseModel.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\BaseModel.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\BusinessLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\BusinessLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\ColumnQuery.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\DataAcessLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\DataAcessLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\Database.dt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\Database.dt.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\DatabaseQuery.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\EntityLayer.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\EntityLayer.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\SQLHelper.cs; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\SQLHelper.cs.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\C#\TableQuery.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Delete.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Delete.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Insert.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Insert.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Item.xml; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Select.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Select.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Update.sql; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\Script
Source: templates\Code Generator\Item\Class Generator C#\PostGres\Script\Update.sql.prt; DestDir: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\Script
Source: templates\Code Generator\Project\AccessProject.jpj; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\AccessProject.prt; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\DotNetNuke Module.jpj; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\DotNetNuke Module.prt; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\EmptyProject.jpj; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\EmptyProject.prt; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\MySQLProject.jpj; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\MySQLProject.prt; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\OracleProject.jpj; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\OracleProject.prt; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\PostGreSQLProject.jpj; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\PostGreSQLProject.prt; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\Project.xml; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\SQLServerProject.jpj; DestDir: {app}\templates\Code Generator\Project
Source: templates\Code Generator\Project\SQLServerProject.prt; DestDir: {app}\templates\Code Generator\Project
Source: templates\DotNetNuke\Icons\1_0F879BF7-31F2-4209-9F5D-BC0D356B2D85.bmp; DestDir: {app}\templates\DotNetNuke\Icons
Source: templates\DotNetNuke\Icons\1_5E3A716B-C107-4397-B021-1DC8B7887B82.bmp; DestDir: {app}\templates\DotNetNuke\Icons
Source: templates\DotNetNuke\Icons\1_68D76982-126E-4399-A5C8-47E0AA333F8B.bmp; DestDir: {app}\templates\DotNetNuke\Icons
Source: templates\DotNetNuke\Icons\1_C1D7D4E8-C14D-4E86-8EE9-454C3219ECFB.bmp; DestDir: {app}\templates\DotNetNuke\Icons
Source: templates\DotNetNuke\Icons\1_F23F9B0C-2710-43B1-B201-0ADE3A085EBC.bmp; DestDir: {app}\templates\DotNetNuke\Icons
Source: templates\DotNetNuke\Icons\1_FECA2084-A4A9-427B-A054-4CFA9A6CA2D1.bmp; DestDir: {app}\templates\DotNetNuke\Icons
Source: templates\DotNetNuke\Icons\2_0F879BF7-31F2-4209-9F5D-BC0D356B2D85.bmp; DestDir: {app}\templates\DotNetNuke\Icons
Source: templates\DotNetNuke\Icons\2_5E3A716B-C107-4397-B021-1DC8B7887B82.bmp; DestDir: {app}\templates\DotNetNuke\Icons
Source: templates\DotNetNuke\Icons\2_68D76982-126E-4399-A5C8-47E0AA333F8B.bmp; DestDir: {app}\templates\DotNetNuke\Icons
Source: templates\DotNetNuke\Icons\2_C1D7D4E8-C14D-4E86-8EE9-454C3219ECFB.bmp; DestDir: {app}\templates\DotNetNuke\Icons
Source: templates\DotNetNuke\Icons\2_F23F9B0C-2710-43B1-B201-0ADE3A085EBC.bmp; DestDir: {app}\templates\DotNetNuke\Icons
Source: templates\DotNetNuke\Icons\2_FECA2084-A4A9-427B-A054-4CFA9A6CA2D1.bmp; DestDir: {app}\templates\DotNetNuke\Icons
Source: templates\DotNetNuke\Item\DotNetNuke\Item.xml; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke
Source: templates\DotNetNuke\Item\DotNetNuke\Module\BaseModel.cs; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\BaseModel.cs.prt; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\BusinessLayerController.cs; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\BusinessLayerController.cs.prt; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\ColumnQuery.sql; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\Database.dt; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\Database.dt.prt; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\DatabaseQuery.sql; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\DataProvider.cs; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\DataProvider.cs.prt; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\EntityInfoClass.cs; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\EntityInfoClass.cs.prt; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\Item.xml; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\Schema.sql; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\Schema.sql.prt; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\SqlDataProvider.cs; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\SqlDataProvider.cs.prt; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\TableQuery.sql; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\Uninstall.SqlDataProvider.sql; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\Uninstall.SqlDataProvider.sql.prt; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\XX.YY.ZZ.SqlDataProvider.sql; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Item\DotNetNuke\Module\XX.YY.ZZ.SqlDataProvider.sql.prt; DestDir: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Source: templates\DotNetNuke\Project\DotNetNuke Module.jpj; DestDir: {app}\templates\DotNetNuke\Project
Source: templates\DotNetNuke\Project\DotNetNuke Module.prt; DestDir: {app}\templates\DotNetNuke\Project
Source: templates\DotNetNuke\Project\EmptyProject.jpj; DestDir: {app}\templates\DotNetNuke\Project
Source: templates\DotNetNuke\Project\EmptyProject.prt; DestDir: {app}\templates\DotNetNuke\Project
Source: templates\DotNetNuke\Project\Project.xml; DestDir: {app}\templates\DotNetNuke\Project
Source: templates\Rabbit MQ Test\Icons\1_5E3A716B-C107-4397-B021-1DC8B7887B82.bmp; DestDir: {app}\templates\Rabbit MQ Test\Icons
Source: templates\Rabbit MQ Test\Icons\1_31CED5A6-04E8-4010-AB7A-77EC2AC603DB.bmp; DestDir: {app}\templates\Rabbit MQ Test\Icons
Source: templates\Rabbit MQ Test\Icons\1_ACA89196-4CDB-49B2-8DFF-B9AF19DFEE09.bmp; DestDir: {app}\templates\Rabbit MQ Test\Icons
Source: templates\Rabbit MQ Test\Icons\1_E2432BE2-2145-4AC2-979E-37B957FE53D3.bmp; DestDir: {app}\templates\Rabbit MQ Test\Icons
Source: templates\Rabbit MQ Test\Icons\2_5E3A716B-C107-4397-B021-1DC8B7887B82.bmp; DestDir: {app}\templates\Rabbit MQ Test\Icons
Source: templates\Rabbit MQ Test\Icons\2_31CED5A6-04E8-4010-AB7A-77EC2AC603DB.bmp; DestDir: {app}\templates\Rabbit MQ Test\Icons
Source: templates\Rabbit MQ Test\Icons\2_ACA89196-4CDB-49B2-8DFF-B9AF19DFEE09.bmp; DestDir: {app}\templates\Rabbit MQ Test\Icons
Source: templates\Rabbit MQ Test\Icons\2_E2432BE2-2145-4AC2-979E-37B957FE53D3.bmp; DestDir: {app}\templates\Rabbit MQ Test\Icons
Source: templates\Rabbit MQ Test\Project\EmptyProject.jpj; DestDir: {app}\templates\Rabbit MQ Test\Project
Source: templates\Rabbit MQ Test\Project\EmptyProject.prt; DestDir: {app}\templates\Rabbit MQ Test\Project
Source: templates\Rabbit MQ Test\Project\Project.xml; DestDir: {app}\templates\Rabbit MQ Test\Project
Source: templates\Rabbit MQ Test\Project\Rabbit-MQ-Test.jpj; DestDir: {app}\templates\Rabbit MQ Test\Project
Source: templates\Rabbit MQ Test\Project\Rabbit-MQ-Test.prt; DestDir: {app}\templates\Rabbit MQ Test\Project
Source: templates\Rabbit MQ Test\Icons.xml; DestDir: {app}\templates\Rabbit MQ Test\Item
Source: templates\Rabbit MQ Test\Item\Item.xml; DestDir: {app}\templates\Rabbit MQ Test\Item
Source: templates\Rabbit MQ Test\Item\Test\Item.xml; DestDir: {app}\templates\Rabbit MQ Test\Item\Test
Source: templates\Rabbit MQ Test\Item\Test\ReadXML.xhw; DestDir: {app}\templates\Rabbit MQ Test\Item\Test
Source: templates\Rabbit MQ Test\Item\Test\ReadXML.xhw.prt; DestDir: {app}\templates\Rabbit MQ Test\Item\Test
Source: templates\Rabbit MQ Test\Item\Test\WriteXML.xhw; DestDir: {app}\templates\Rabbit MQ Test\Item\Test
Source: templates\Rabbit MQ Test\Item\Test\WriteXML.xhw.prt; DestDir: {app}\templates\Rabbit MQ Test\Item\Test



[Run]
Filename: {app}\vcredist_x86.exe; Parameters: /q /norestart; Flags: waituntilterminated runhidden

[Code]
function GetCommandlineParam (inParam: String):String;
var
  LoopVar : Integer;
  BreakLoop : Boolean;
begin
  { Init the variable to known values }
  LoopVar :=0;
  Result := '';
  BreakLoop := False;

  { Loop through the passed in arry to find the parameter }
  while ( (LoopVar < ParamCount) and
          (not BreakLoop) ) do
  begin
    { Determine if the looked for parameter is the next value }
    if ( (ParamStr(LoopVar) = inParam) and
         ( (LoopVar+1) <= ParamCount )) then
    begin
      { Set the return result equal to the next command line parameter }
      Result := ParamStr(LoopVar+1);

      { Break the loop }
      BreakLoop := True;
    end;

    { Increment the loop variable }
    LoopVar := LoopVar + 1;
  end;
end;


function InitializeSetup(): boolean;
begin
  //Deletes any pendding file rename before installing..
  if RegValueExists(HKEY_LOCAL_MACHINE,'SYSTEM\CurrentControlSet\Control\Session Manager\','PendingFileRenameOperations') = true then
  begin
       RegDeleteValue (HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager\','PendingFileRenameOperations');
  end;

  //Continue Setup
  Result:= True;
end;

function Servidor(Value: string): string;
begin
   Result := GetCommandlineParam('/SERVER');
end;

function Usuario(Value: string): string;
begin
   Result := GetCommandlineParam('/USER');
end;

function Senha(Value: string): string;
begin
   Result := GetCommandlineParam('/PWD');
end;

[Dirs]
Name: {app}\binaries
Name: {app}\plugins
Name: {app}\templates
Name: {app}\Projects
Name: {app}\templates\Code Generator
Name: {app}\templates\DotNetNuke
Name: {app}\templates\Rabbit MQ Test
Name: {app}\templates\Code Generator\Icons
Name: {app}\templates\Code Generator\Item
Name: {app}\templates\Code Generator\Item\Class Generator C#
Name: {app}\templates\Code Generator\Item\Class Generator C#\Access
Name: {app}\templates\Code Generator\Item\Class Generator C#\Access\C#
Name: {app}\templates\Code Generator\Item\Class Generator C#\MySQL
Name: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\C#
Name: {app}\templates\Code Generator\Item\Class Generator C#\MySQL\Script
Name: {app}\templates\Code Generator\Item\Class Generator C#\Oracle
Name: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\C#
Name: {app}\templates\Code Generator\Item\Class Generator C#\Oracle\Script
Name: {app}\templates\Code Generator\Item\Class Generator C#\PostGres
Name: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\C#
Name: {app}\templates\Code Generator\Item\Class Generator C#\PostGres\Script
Name: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server
Name: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\C#
Name: {app}\templates\Code Generator\Item\Class Generator C#\SQL Server\Script
Name: {app}\templates\Code Generator\Project
Name: {app}\templates\DotNetNuke\Icons
Name: {app}\templates\DotNetNuke\Item
Name: {app}\templates\DotNetNuke\Item\DotNetNuke
Name: {app}\templates\DotNetNuke\Item\DotNetNuke\Module
Name: {app}\templates\DotNetNuke\Project
Name: {app}\templates\Rabbit MQ Test\Icons
Name: {app}\templates\Rabbit MQ Test\Project
Name: {app}\templates\Rabbit MQ Test\Item
Name: {app}\templates\Rabbit MQ Test\Item\Test
