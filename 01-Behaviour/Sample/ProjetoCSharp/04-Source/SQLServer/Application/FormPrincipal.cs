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
                    rotina = new ROTINA();
                    rotina.Apelido = "José";
                    rotinaBLL.Select(rotina);
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

                    rotina.idRotina = idrotina;

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
                    rotinaBLL.Delete((Int32)rotina.idRotina);
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

                    SelecionarDLL((Int32)rotina.idRotina);

                    txtIDRotina.Text = rotina.idRotina.ToString();
                    txtNomeRotina.Text = rotina.Nome!=null?rotina.Nome:"";
                    txtDescricao.Text = rotina.Decricao!=null?rotina.Decricao:"";
                    txtUsuario.Text = rotina.Usuario!=null?rotina.Usuario:"";
                    txtFuncional.Text = rotina.Funcional!=null?rotina.Funcional:"";

                    if(rotina.DataCriacao != null)
                        dtpDataCriacao.Value = (DateTime)rotina.DataCriacao;

                    if (rotina.Ativo != null)
                    {
                        if ((Boolean)rotina.Ativo)
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

                    txtApelido.Text = rotina.Apelido!=null?rotina.Apelido:"";
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
                        rotina.idRotina = Int32.Parse(txtIDRotina.Text);

                    if (txtNomeRotina.Text != "")
                        rotina.Nome = txtNomeRotina.Text;

                    if (txtDescricao.Text.Trim() != "")
                        rotina.Decricao = txtDescricao.Text;

                    if (txtUsuario.Text.Trim() != "")
                        rotina.Usuario = txtUsuario.Text;

                    if (txtFuncional.Text.Trim() != "")
                        rotina.Funcional = txtFuncional.Text;

                    if (chkAtivo.Checked)
                        rotina.Ativo = true;

                    if (chkInativo.Checked)
                        rotina.Ativo = false;

                    if (txtApelido.Text.Trim() != "")
                        rotina.Apelido = txtApelido.Text;

                    if (dtpDataCriacao.Checked)
                        rotina.DataCriacao = dtpDataCriacao.Value;
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

                    dll.idRotina = idRotina;

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
