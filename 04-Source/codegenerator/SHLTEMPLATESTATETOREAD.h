/* ****************************************************************************
 * Arquivo: SHLTEMPLATESTATETOREAD.H                                          *
 *                                                                            *
 * Define os estados da máquina de estado para leitura dos arquivos templates *
 *                                                                            *
 * Data:29/04/2013                                                            *
 * Auto: José Sahle Netto                                                     *
 **************************************************************************** */

typedef enum _shltemplatestatetoread
{
	SHLTEMPLATESTATETOREAD_IDLE,
	SHLTEMPLATESTATETOREAD_READLINE,
	SHLTEMPLATESTATETOREAD_READLINE_ALLFIELDS,
	SHLTEMPLATESTATETOREAD_READLINE_FOREIGNKEY,
	SHLTEMPLATESTATETOREAD_GETLINE,
	SHLTEMPLATESTATETOREAD_GETLINE_ALLFIELDS,
	SHLTEMPLATESTATETOREAD_GETLINE_FOREIGNKEY,
	SHLTEMPLATESTATETOREAD_TREATLINE,
	SHLTEMPLATESTATETOREAD_TREATLINE_ALLFIELDS,
	SHLTEMPLATESTATETOREAD_TREATLINE_FOREIGNKEY,
	SHLTEMPLATESTATETOREAD_WAITFORENDFOREIGNKEY,
	SHLTEMPLATESTATETOREAD_LOOPFIELDS,
	SHLTEMPLATESTATETOREAD_LENGTH
}SHLTEMPLATESTATETOREAD;