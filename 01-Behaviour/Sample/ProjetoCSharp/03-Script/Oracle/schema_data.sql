INSERT INTO GP_ROTINA (idRotina,Nome,Decricao,DataCriacao,Usuario,Funcional,Ativo,Apelido) VALUES (2,'TJBAProjudi','Robo Projudi',TO_DATE('20120305', 'yyyymmdd'),NULL,NULL,0,NULL) 
go
INSERT INTO GP_ROTINA (idRotina,Nome,Decricao,DataCriacao,Usuario,Funcional,Ativo,Apelido) VALUES (4,'Distribuidor-PainelAutomator','Robo Importação Fila O9',TO_DATE('20120305', 'yyyymmdd'),NULL,NULL,0,NULL) ;
go
INSERT INTO GP_ROTINA (idRotina,Nome,Decricao,DataCriacao,Usuario,Funcional,Ativo,Apelido) VALUES (6,'SaneamentoPilotoPCES','Saneamento do diretório Piloto PCES',TO_DATE('20120305', 'yyyymmdd'),NULL,NULL,0,NULL) ;
go
INSERT INTO GP_ROTINA (idRotina,Nome,Decricao,DataCriacao,Usuario,Funcional,Ativo,Apelido) VALUES (7,'TJSudesteAutomator','TJAutomator dos estados da região Sudeste',TO_DATE('20120305', 'yyyymmdd'),NULL,NULL,1,NULL) ; 
go
INSERT INTO GP_ROTINA (idRotina,Nome,Decricao,DataCriacao,Usuario,Funcional,Ativo,Apelido) VALUES (8,'TJNorteAutomator','TJAutomator dos estados da região Norte',TO_DATE('20120305', 'yyyymmdd'),NULL,NULL,0,NULL) ; 
go
INSERT INTO GP_ROTINA (idRotina,Nome,Decricao,DataCriacao,Usuario,Funcional,Ativo,Apelido) VALUES (9,'TJNordesteAutomator','TJAutomator dos estados da região Nordeste',TO_DATE('20120305', 'yyyymmdd'),NULL,NULL,0,NULL) ; 
go
INSERT INTO GP_ROTINA (idRotina,Nome,Decricao,DataCriacao,Usuario,Funcional,Ativo,Apelido) VALUES (10,'TJCentroOesteAutomator','TJAutomator dos estados da região Centro-Oeste',TO_DATE('20120305', 'yyyymmdd'),NULL,NULL,0,NULL) ; 
go
INSERT INTO GP_ROTINA (idRotina,Nome,Decricao,DataCriacao,Usuario,Funcional,Ativo,Apelido) VALUES (11,'TJSulAutomator','TJAutomator dos estados da região Sul',TO_DATE('20120305', 'yyyymmdd'),NULL,NULL,0,NULL) ; 
GO
SELECT * FROM GP_ROTINA
GO

INSERT INTO GP_AGENDAMENTO (idAgendamento,idRotina,DataInicio,HoraInicio,DataFim,HoraFim,Intervalo,Repeticao) VALUES (2,2,TO_DATE('20120305', 'yyyymmdd'),'8:01',NULL,'20:01',30,0) ; 
go
INSERT INTO GP_AGENDAMENTO (idAgendamento,idRotina,DataInicio,HoraInicio,DataFim,HoraFim,Intervalo,Repeticao) VALUES (4,4,TO_DATE('20120305', 'yyyymmdd'),'8:01',NULL,'20:01',15,0) ; 
go
INSERT INTO GP_AGENDAMENTO (idAgendamento,idRotina,DataInicio,HoraInicio,DataFim,HoraFim,Intervalo,Repeticao) VALUES (6,6,TO_DATE('20120305', 'yyyymmdd'),'8:01',NULL,'20:01',0,1) ; 
go
INSERT INTO GP_AGENDAMENTO (idAgendamento,idRotina,DataInicio,HoraInicio,DataFim,HoraFim,Intervalo,Repeticao) VALUES (7,7,TO_DATE('20120305', 'yyyymmdd'),'0:00',NULL,'23:59',0,1) ; 
go
INSERT INTO GP_AGENDAMENTO (idAgendamento,idRotina,DataInicio,HoraInicio,DataFim,HoraFim,Intervalo,Repeticao) VALUES (8,8,TO_DATE('20120305', 'yyyymmdd'),'0:00',NULL,'23:59',0,1) ; 
go
INSERT INTO GP_AGENDAMENTO (idAgendamento,idRotina,DataInicio,HoraInicio,DataFim,HoraFim,Intervalo,Repeticao) VALUES (9,9,TO_DATE('20120305', 'yyyymmdd'),'0:00',NULL,'23:59',0,1) ; 
go
INSERT INTO GP_AGENDAMENTO (idAgendamento,idRotina,DataInicio,HoraInicio,DataFim,HoraFim,Intervalo,Repeticao) VALUES (10,10,TO_DATE('20120305', 'yyyymmdd'),'0:00',NULL,'23:59',0,1) ; 
go
INSERT INTO GP_AGENDAMENTO (idAgendamento,idRotina,DataInicio,HoraInicio,DataFim,HoraFim,Intervalo,Repeticao) VALUES (11,11,TO_DATE('20120305', 'yyyymmdd'),'0:00',NULL,'23:59',0,1) ; 
GO
SELECT * FROM GP_AGENDAMENTO 
GO

INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (2,2,1,'TJBAProjudi.Automator.TJBAProjudiAutomator','TJBAProjudi.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (6,6,1,'ItauUnibanco.BMF.BMFAutomator','BMF.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (7,7,6,'TJAutomator.TJSaoPauloCapital','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (8,7,5,'TJAutomator.TJSaoPauloProjudi','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (9,7,4,'TJAutomator.TJEspiritoSanto','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (10,7,3,'TJAutomator.TJMinasGerais','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (11,7,2,'TJAutomator.TJMinasGeraisProjudi','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (12,7,1,'TJAutomator.TJRioDeJaneiro','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (13,4,1,'PainelOficiosAutomator.PainelOficiosAutomator','PainelOficiosAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (14,4,2,'Distribuidor.Automator.DistribuidorAutomator','AutomatorDistribuidor.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (15,8,2,'TJAutomator.TJRondoniaProjudi','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (16,8,2,'TJAutomator.TJAcre','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (17,8,2,'TJAutomator.TJRoraima','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (18,8,2,'TJAutomator.TJPara','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (19,8,2,'TJAutomator.TJTocantins','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (20,8,1,'TJAutomator.TJAmapa','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (21,8,2,'TJAutomator.TJParaProjudi','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (22,9,1,'TJAutomator.TJMaranhaoProjudi','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (23,9,2,'TJAutomator.TJBahiaProjudi','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (24,9,3,'TJAutomator.TJRioGrandeDoNorte','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (25,9,4,'TJAutomator.TJParaiba','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (26,9,5,'TJAutomator.TJParaibaProjudi','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (27,9,6,'TJAutomator.TJPernambucoProjudi','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (28,9,7,'TJAutomator.TJAlagoas','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (29,9,8,'TJAutomator.TJSergipe','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (30,10,1,'TJAutomator.TJMatoGrossoDoSul','TJAutomator.dll',0) ; 
go
INSERT INTO GP_DLL (idDLL,idRotina,Ordem,Nome,Assembly,Dependencia) VALUES (32,11,1,'TJAutomator.TJSantaCatarina','TJAutomator.dll',0) ; 
GO
SELECT * FROM GP_DLL
GO

INSERT INTO GP_PERIODICIDADE (idPeriodicidade,idRotina,Tipo,Parametro) VALUES (2,2,1,'0|1|2|3|4|5|6') ; 
go
INSERT INTO GP_PERIODICIDADE (idPeriodicidade,idRotina,Tipo,Parametro) VALUES (5,4,1,'0|1|2|3|4|5|6') ; 
go
INSERT INTO GP_PERIODICIDADE (idPeriodicidade,idRotina,Tipo,Parametro) VALUES (7,6,1,'3') ; 
go
INSERT INTO GP_PERIODICIDADE (idPeriodicidade,idRotina,Tipo,Parametro) VALUES (8,7,1,'0|1|2|3|4|5|6') ; 
go
INSERT INTO GP_PERIODICIDADE (idPeriodicidade,idRotina,Tipo,Parametro) VALUES (9,8,1,'0|1|2|3|4|5|6') ; 
go
INSERT INTO GP_PERIODICIDADE (idPeriodicidade,idRotina,Tipo,Parametro) VALUES (10,9,1,'0|1|2|3|4|5|6') ; 
go
INSERT INTO GP_PERIODICIDADE (idPeriodicidade,idRotina,Tipo,Parametro) VALUES (11,10,1,'0|1|2|3|4|5|6') ; 
go
INSERT INTO GP_PERIODICIDADE (idPeriodicidade,idRotina,Tipo,Parametro) VALUES (12,11,1,'0|1|2|3|4|5|6') ; 
GO
SELECT * FROM GP_PERIODICIDADE
GO
