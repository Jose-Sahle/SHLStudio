SET IDENTITY_INSERT GP_ROTINA ON
INSERT INTO GP_ROTINA ([idRotina],[Nome],[Decricao],[DataCriacao],[Usuario],[Funcional],[Ativo],[Apelido]) VALUES (2,'TJBAProjudi','Robo Projudi','20120305 00:00:00',NULL,NULL,'False',NULL) 
INSERT INTO GP_ROTINA ([idRotina],[Nome],[Decricao],[DataCriacao],[Usuario],[Funcional],[Ativo],[Apelido]) VALUES (4,'Distribuidor-PainelAutomator','Robo Importação Fila O9','20120305 00:00:00',NULL,NULL,'False',NULL) ; 
INSERT INTO GP_ROTINA ([idRotina],[Nome],[Decricao],[DataCriacao],[Usuario],[Funcional],[Ativo],[Apelido]) VALUES (6,'SaneamentoPilotoPCES','Saneamento do diretório Piloto PCES','20120305 00:00:00',NULL,NULL,'False',NULL) ; 
INSERT INTO GP_ROTINA ([idRotina],[Nome],[Decricao],[DataCriacao],[Usuario],[Funcional],[Ativo],[Apelido]) VALUES (7,'TJSudesteAutomator','TJAutomator dos estados da região Sudeste','20120305 00:00:00',NULL,NULL,'True',NULL) ; 
INSERT INTO GP_ROTINA ([idRotina],[Nome],[Decricao],[DataCriacao],[Usuario],[Funcional],[Ativo],[Apelido]) VALUES (8,'TJNorteAutomator','TJAutomator dos estados da região Norte','20120305 00:00:00',NULL,NULL,'False',NULL) ; 
INSERT INTO GP_ROTINA ([idRotina],[Nome],[Decricao],[DataCriacao],[Usuario],[Funcional],[Ativo],[Apelido]) VALUES (9,'TJNordesteAutomator','TJAutomator dos estados da região Nordeste','20120305 00:00:00',NULL,NULL,'False',NULL) ; 
INSERT INTO GP_ROTINA ([idRotina],[Nome],[Decricao],[DataCriacao],[Usuario],[Funcional],[Ativo],[Apelido]) VALUES (10,'TJCentroOesteAutomator','TJAutomator dos estados da região Centro-Oeste','20120305 00:00:00',NULL,NULL,'False',NULL) ; 
INSERT INTO GP_ROTINA ([idRotina],[Nome],[Decricao],[DataCriacao],[Usuario],[Funcional],[Ativo],[Apelido]) VALUES (11,'TJSulAutomator','TJAutomator dos estados da região Sul','20120305 00:00:00',NULL,NULL,'False',NULL) ; 
SET IDENTITY_INSERT GP_ROTINA OFF
go
SELECT * FROM GP_ROTINA
go

SET IDENTITY_INSERT GP_AGENDAMENTO ON
INSERT INTO GP_AGENDAMENTO ([idAgendamento],[idRotina],[DataInicio],[HoraInicio],[DataFim],[HoraFim],[Intervalo],[Repeticao]) VALUES (2,2,'20120305 00:00:00','8:01',NULL,'20:01',30,0) ; 
INSERT INTO GP_AGENDAMENTO ([idAgendamento],[idRotina],[DataInicio],[HoraInicio],[DataFim],[HoraFim],[Intervalo],[Repeticao]) VALUES (4,4,'20120103 00:00:00','8:01',NULL,'20:01',15,0) ; 
INSERT INTO GP_AGENDAMENTO ([idAgendamento],[idRotina],[DataInicio],[HoraInicio],[DataFim],[HoraFim],[Intervalo],[Repeticao]) VALUES (6,6,'20120103 00:00:00','8:01',NULL,'20:01',0,1) ; 
INSERT INTO GP_AGENDAMENTO ([idAgendamento],[idRotina],[DataInicio],[HoraInicio],[DataFim],[HoraFim],[Intervalo],[Repeticao]) VALUES (7,7,'20120103 00:00:00','0:00',NULL,'23:59',0,1) ; 
INSERT INTO GP_AGENDAMENTO ([idAgendamento],[idRotina],[DataInicio],[HoraInicio],[DataFim],[HoraFim],[Intervalo],[Repeticao]) VALUES (8,8,'20120103 00:00:00','0:00',NULL,'23:59',0,1) ; 
INSERT INTO GP_AGENDAMENTO ([idAgendamento],[idRotina],[DataInicio],[HoraInicio],[DataFim],[HoraFim],[Intervalo],[Repeticao]) VALUES (9,9,'20120103 00:00:00','0:00',NULL,'23:59',0,1) ; 
INSERT INTO GP_AGENDAMENTO ([idAgendamento],[idRotina],[DataInicio],[HoraInicio],[DataFim],[HoraFim],[Intervalo],[Repeticao]) VALUES (10,10,'20120103 00:00:00','0:00',NULL,'23:59',0,1) ; 
INSERT INTO GP_AGENDAMENTO ([idAgendamento],[idRotina],[DataInicio],[HoraInicio],[DataFim],[HoraFim],[Intervalo],[Repeticao]) VALUES (11,11,'20120103 00:00:00','0:00',NULL,'23:59',0,1) ; 
SET IDENTITY_INSERT GP_AGENDAMENTO OFF
go
SELECT * FROM GP_AGENDAMENTO 
go

SET IDENTITY_INSERT GP_DLL ON
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (2,2,1,'TJBAProjudi.Automator.TJBAProjudiAutomator','TJBAProjudi.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (6,6,1,'ItauUnibanco.BMF.BMFAutomator','BMF.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (7,7,6,'TJAutomator.TJSaoPauloCapital','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (8,7,5,'TJAutomator.TJSaoPauloProjudi','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (9,7,4,'TJAutomator.TJEspiritoSanto','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (10,7,3,'TJAutomator.TJMinasGerais','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (11,7,2,'TJAutomator.TJMinasGeraisProjudi','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (12,7,1,'TJAutomator.TJRioDeJaneiro','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (13,4,1,'PainelOficiosAutomator.PainelOficiosAutomator','PainelOficiosAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (14,4,2,'Distribuidor.Automator.DistribuidorAutomator','AutomatorDistribuidor.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (15,8,2,'TJAutomator.TJRondoniaProjudi','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (16,8,2,'TJAutomator.TJAcre','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (17,8,2,'TJAutomator.TJRoraima','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (18,8,2,'TJAutomator.TJPara','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (19,8,2,'TJAutomator.TJTocantins','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (20,8,1,'TJAutomator.TJAmapa','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (21,8,2,'TJAutomator.TJParaProjudi','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (22,9,1,'TJAutomator.TJMaranhaoProjudi','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (23,9,2,'TJAutomator.TJBahiaProjudi','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (24,9,3,'TJAutomator.TJRioGrandeDoNorte','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (25,9,4,'TJAutomator.TJParaiba','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (26,9,5,'TJAutomator.TJParaibaProjudi','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (27,9,6,'TJAutomator.TJPernambucoProjudi','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (28,9,7,'TJAutomator.TJAlagoas','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (29,9,8,'TJAutomator.TJSergipe','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (30,10,1,'TJAutomator.TJMatoGrossoDoSul','TJAutomator.dll',0) ; 
INSERT INTO GP_DLL ([idDLL],[idRotina],[Ordem],[Nome],[Assembly],[Dependencia]) VALUES (32,11,1,'TJAutomator.TJSantaCatarina','TJAutomator.dll',0) ; 
SET IDENTITY_INSERT GP_DLL OFF
go
SELECT * FROM GP_DLL
go

SET IDENTITY_INSERT GP_PERIODICIDADE ON
INSERT INTO GP_PERIODICIDADE ([idPeriodicidade],[idRotina],[Tipo],[Parametro]) VALUES (2,2,1,'0|1|2|3|4|5|6') ; 
INSERT INTO GP_PERIODICIDADE ([idPeriodicidade],[idRotina],[Tipo],[Parametro]) VALUES (5,4,1,'0|1|2|3|4|5|6') ; 
INSERT INTO GP_PERIODICIDADE ([idPeriodicidade],[idRotina],[Tipo],[Parametro]) VALUES (7,6,1,'3') ; 
INSERT INTO GP_PERIODICIDADE ([idPeriodicidade],[idRotina],[Tipo],[Parametro]) VALUES (8,7,1,'0|1|2|3|4|5|6') ; 
INSERT INTO GP_PERIODICIDADE ([idPeriodicidade],[idRotina],[Tipo],[Parametro]) VALUES (9,8,1,'0|1|2|3|4|5|6') ; 
INSERT INTO GP_PERIODICIDADE ([idPeriodicidade],[idRotina],[Tipo],[Parametro]) VALUES (10,9,1,'0|1|2|3|4|5|6') ; 
INSERT INTO GP_PERIODICIDADE ([idPeriodicidade],[idRotina],[Tipo],[Parametro]) VALUES (11,10,1,'0|1|2|3|4|5|6') ; 
INSERT INTO GP_PERIODICIDADE ([idPeriodicidade],[idRotina],[Tipo],[Parametro]) VALUES (12,11,1,'0|1|2|3|4|5|6') ; 
SET IDENTITY_INSERT GP_PERIODICIDADE OFF
go
SELECT * FROM GP_PERIODICIDADE
go