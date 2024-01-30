using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using GPRotina.BLL;
using GPRotina.Entity;

namespace GPRotinaUI
{
    public partial class frmPrincipal : Form
    {
        #region [ Contrutores / Destrutores ]
            public frmPrincipal()
            {
                InitializeComponent();
            }
        #endregion

        #region [ Membros Privados ]
            List<ROTINA> rotinas;
            List<DLL> dlls;
        #endregion

        #region [ Eventos ]
            private void frmPrincipal_Load(object sender, EventArgs e)
            {
                PreencherRotina();
            }

            private void cmdSelecinarLista_Click(object sender, EventArgs e)
            {
                SelecionarLista();
            }

            private void cmdSelecionarUnico_Click(object sender, EventArgs e)
            {
                SelecionarUnico();
            }

            private void cmdIncluir_Click(object sender, EventArgs e)
            {
                Incluir();
            }

            private void cmdAlterar_Click(object sender, EventArgs e)
            {
                Alterar();
            }

            private void cmdExcluir_Click(object sender, EventArgs e)
            {
                Excluir();
            }

            private void gridRotina_RowHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
            {
                SelecionarRegistro(e.RowIndex);
            }

            private void gridRotina_CellClick(object sender, DataGridViewCellEventArgs e)
            {
                SelecionarRegistro(e.RowIndex);
            }

            private void cmdLimparCampos_Click(object sender, EventArgs e)
            {
                LimparCampos();
            }
        #endregion

        #region [ Métodos Privados ]
            private void PreencherRotina()
            {
                try
                {
                    LimparCampos();
                    SelecionarLista();
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private void SelecionarLista()
            {
                ROTINABLL rotinaBLL = new ROTINABLL();
                ROTINA rotina = null;

                try
                {
                    rotina = GetParametros();

                    rotinas = rotinaBLL.SelectList(rotina);

                    gridRotina.DataSource = rotinas;

                    MostrarQuantidadeSelecionada();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private void SelecionarUnico()
            {
                ROTINABLL rotinaBLL = new ROTINABLL();
                ROTINA rotina = null;

                try
                {
                    rotinas = new List<ROTINA>();

                    rotina = GetParametros();
                    rotina = rotinaBLL.Select(rotina);

                    if(rotina != null)
                        rotinas.Add(rotina);

                    gridRotina.DataSource = rotinas;

                    MostrarQuantidadeSelecionada();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private void Incluir()
            {
                ROTINABLL rotinaBLL = new ROTINABLL();
                ROTINA rotina = null;
                Int32 idrotina;

                try
                {
                    rotina = GetParametros();
                    idrotina = rotinaBLL.Insert(rotina);

                    rotina.IDROTINA = idrotina;

                    if (idrotina !=  0)
                        rotinas.Add(rotina);

                    gridRotina.DataSource = rotinas;

                    LimparCampos();

                    MostrarQuantidadeSelecionada();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private void Alterar()
            {
                ROTINABLL rotinaBLL = new ROTINABLL();
                ROTINA rotina = null;

                try
                {
                    rotina = GetParametros();
                    
                    rotinaBLL.Update(rotina);

                    LimparCampos();

                    MostrarQuantidadeSelecionada();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private void Excluir()
            {
                ROTINABLL rotinaBLL = new ROTINABLL();
                ROTINA rotina = null;

                try
                {
                    rotina = GetParametros();
                    rotinaBLL.Delete((Int32)rotina.IDROTINA);
                    rotinas.Remove(rotina);
                    LimparCampos();

                    MostrarQuantidadeSelecionada();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private void MostrarQuantidadeSelecionada()
            {
                try
                {
                    lblRegistros.Text = rotinas.Count.ToString() + " registro(s)";
                }
                catch (Exception ex)
                {
                }
            }

            private void LimparCampos()
            {
                try
                {
                    txtIDRotina.Text = "";
                    txtNomeRotina.Text = "";
                    txtDescricao.Text = "";
                    txtUsuario.Text = "";
                    txtFuncional.Text = "";

                    dtpDataCriacao.Value = DateTime.Now;
                    dtpDataCriacao.Checked = false;

                    chkAtivo.Checked = false;
                    chkInativo.Checked = false;

                    txtApelido.Text = "";
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private void SelecionarRegistro(Int32 rowIndex)
            {
                ROTINA rotina = null;

                try
                {
                    rotina =  (ROTINA)gridRotina.Rows[rowIndex].DataBoundItem;

                    SelecionarDLL((Int32)rotina.IDROTINA);

                    txtIDRotina.Text = rotina.IDROTINA.ToString();
                    txtNomeRotina.Text = rotina.NOME!=null?rotina.NOME:"";
                    txtDescricao.Text = rotina.DECRICAO!=null?rotina.DECRICAO:"";
                    txtUsuario.Text = rotina.USUARIO!=null?rotina.USUARIO:"";
                    txtFuncional.Text = rotina.FUNCIONAL!=null?rotina.FUNCIONAL:"";

                    if(rotina.DATACRIACAO != null)
                        dtpDataCriacao.Value = (DateTime)rotina.DATACRIACAO;

                    if (rotina.ATIVO != null)
                    {
                        if ((Int32)rotina.ATIVO == 1)
                        {
                            chkAtivo.Checked = true;
                            chkInativo.Checked = false;
                        }
                        else
                        {
                            chkAtivo.Checked = false;
                            chkInativo.Checked = true;
                        }
                    }
                    else
                    {
                        chkAtivo.Checked = false;
                        chkInativo.Checked = false;
                    }

                    txtApelido.Text = rotina.APELIDO!=null?rotina.APELIDO:"";
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private ROTINA GetParametros()
            {
                ROTINA rotina = new ROTINA();

                try
                {
                    if (txtIDRotina.Text.Trim() != "")
                        rotina.IDROTINA = Int32.Parse(txtIDRotina.Text);

                    if (txtNomeRotina.Text != "")
                        rotina.NOME = txtNomeRotina.Text;

                    if (txtDescricao.Text.Trim() != "")
                        rotina.DECRICAO = txtDescricao.Text;

                    if (txtUsuario.Text.Trim() != "")
                        rotina.USUARIO = txtUsuario.Text;

                    if (txtFuncional.Text.Trim() != "")
                        rotina.FUNCIONAL = txtFuncional.Text;

                    if (chkAtivo.Checked)
                        rotina.ATIVO = 1;

                    if (chkInativo.Checked)
                        rotina.ATIVO = 0;

                    if (txtApelido.Text.Trim() != "")
                        rotina.APELIDO = txtApelido.Text;

                    if (dtpDataCriacao.Checked)
                        rotina.DATACRIACAO = dtpDataCriacao.Value;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }

                return rotina;
            }

            private void SelecionarDLL(Int32 idRotina)
            {
                DLLBLL dllBLL = null;
                DLL dll = null;

                try
                {
                    dllBLL = new DLLBLL();
                    dll = new DLL();

                    dll.IDROTINA = idRotina;

                    dlls = dllBLL.SelectList(dll);

                    gridDLL.DataSource = dlls;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        #endregion
    }
}
