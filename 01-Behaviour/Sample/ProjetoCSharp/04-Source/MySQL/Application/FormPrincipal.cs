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
            List<rotina> rotinas;
            List<dll> dlls;
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
                rotinaBLL rotinaBLL = new rotinaBLL();
                rotina Rotina = null;

                try
                {
                    Rotina = GetParametros();

                    rotinas = rotinaBLL.SelectList(Rotina);

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
                rotinaBLL rotinaBLL = new rotinaBLL();
                rotina Rotina = null;

                try
                {
                    rotinas = new List<rotina>();

                    Rotina = GetParametros();
                    Rotina = rotinaBLL.Select(Rotina);

                    if (Rotina != null)
                        rotinas.Add(Rotina);

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
                rotinaBLL rotinaBLL = new rotinaBLL();
                rotina Rotina = null;
                Int32 idrotina;

                try
                {
                    Rotina = GetParametros();
                    idrotina = rotinaBLL.Insert(Rotina);

                    Rotina.idRotina = idrotina;

                    if (idrotina !=  0)
                        rotinas.Add(Rotina);

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
                rotinaBLL rotinaBLL = new rotinaBLL();
                rotina Rotina = null;

                try
                {
                    Rotina = GetParametros();

                    rotinaBLL.Update(Rotina);

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
                rotinaBLL rotinaBLL = new rotinaBLL();
                rotina Rotina = null;

                try
                {
                    Rotina = GetParametros();
                    rotinaBLL.Delete((Int32)Rotina.idRotina);
                    rotinas.Remove(Rotina);
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
                rotina Rotina = null;

                try
                {
                    Rotina = (rotina)gridRotina.Rows[rowIndex].DataBoundItem;

                    SelecionarDLL((Int32)Rotina.idRotina);

                    txtIDRotina.Text = Rotina.idRotina.ToString();
                    txtNomeRotina.Text = Rotina.Nome != null ? Rotina.Nome : "";
                    txtDescricao.Text = Rotina.Decricao != null ? Rotina.Decricao : "";
                    txtUsuario.Text = Rotina.Usuario != null ? Rotina.Usuario : "";
                    txtFuncional.Text = Rotina.Funcional != null ? Rotina.Funcional : "";

                    if (Rotina.DataCriacao != null)
                        dtpDataCriacao.Value = (DateTime)Rotina.DataCriacao;

                    if (Rotina.Ativo != null)
                    {
                        if ((Boolean)Rotina.Ativo)
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

                    txtApelido.Text = Rotina.Apelido != null ? Rotina.Apelido : "";
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private rotina GetParametros()
            {
                rotina Rotina = new rotina();

                try
                {
                    if (txtIDRotina.Text.Trim() != "")
                        Rotina.idRotina = Int32.Parse(txtIDRotina.Text);

                    if (txtNomeRotina.Text != "")
                        Rotina.Nome = txtNomeRotina.Text;

                    if (txtDescricao.Text.Trim() != "")
                        Rotina.Decricao = txtDescricao.Text;

                    if (txtUsuario.Text.Trim() != "")
                        Rotina.Usuario = txtUsuario.Text;

                    if (txtFuncional.Text.Trim() != "")
                        Rotina.Funcional = txtFuncional.Text;

                    if (chkAtivo.Checked)
                        Rotina.Ativo = true;

                    if (chkInativo.Checked)
                        Rotina.Ativo = false;

                    if (txtApelido.Text.Trim() != "")
                        Rotina.Apelido = txtApelido.Text;

                    if (dtpDataCriacao.Checked)
                        Rotina.DataCriacao = dtpDataCriacao.Value;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }

                return Rotina;
            }

            private void SelecionarDLL(Int32 idRotina)
            {
                dllBLL dllBLL = null;
                dll Dll = null;

                try
                {
                    dllBLL = new dllBLL();
                    Dll = new dll();

                    Dll.idRotina = idRotina;

                    dlls = dllBLL.SelectList(Dll);

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
