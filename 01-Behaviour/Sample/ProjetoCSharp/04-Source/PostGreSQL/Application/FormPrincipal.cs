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
                catch (Exception ex)
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

                    Rotina.idrotina = idrotina;

                    if (idrotina != 0)
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
                    rotinaBLL.Delete((Int32)Rotina.idrotina);
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

                    SelecionarDLL((Int32)Rotina.idrotina);

                    txtIDRotina.Text = Rotina.idrotina.ToString();
                    txtNomeRotina.Text = Rotina.nome != null ? Rotina.nome : "";
                    txtDescricao.Text = Rotina.decricao != null ? Rotina.decricao : "";
                    txtUsuario.Text = Rotina.usuario != null ? Rotina.usuario : "";
                    txtFuncional.Text = Rotina.funcional != null ? Rotina.funcional : "";

                    if (Rotina.datacriacao != null)
                        dtpDataCriacao.Value = (DateTime)Rotina.datacriacao;

                    if (Rotina.ativo != null)
                    {
                        if ((Boolean)Rotina.ativo)
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

                    txtApelido.Text = Rotina.apelido != null ? Rotina.apelido : "";
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
                        Rotina.idrotina = Int32.Parse(txtIDRotina.Text);

                    if (txtNomeRotina.Text != "")
                        Rotina.nome = txtNomeRotina.Text;

                    if (txtDescricao.Text.Trim() != "")
                        Rotina.decricao = txtDescricao.Text;

                    if (txtUsuario.Text.Trim() != "")
                        Rotina.usuario = txtUsuario.Text;

                    if (txtFuncional.Text.Trim() != "")
                        Rotina.funcional = txtFuncional.Text;

                    if (chkAtivo.Checked)
                        Rotina.ativo = true;

                    if (chkInativo.Checked)
                        Rotina.ativo = false;

                    if (txtApelido.Text.Trim() != "")
                        Rotina.apelido = txtApelido.Text;

                    if (dtpDataCriacao.Checked)
                        Rotina.datacriacao = dtpDataCriacao.Value;
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

                    Dll.idrotina = idRotina;

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
