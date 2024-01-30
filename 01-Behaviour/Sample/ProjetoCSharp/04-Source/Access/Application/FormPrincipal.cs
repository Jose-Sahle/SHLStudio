using SHL.CEP.BLL;
using SHL.CEP.Entity;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CepEndereco
{
    public partial class frmPrincipal : Form
    {
        public frmPrincipal()
        {
            InitializeComponent();
        }

        #region [ Eventos ]
            private void frmPrincipal_Load(object sender, EventArgs e)
            {
                IniciarControles();
            }

            private void cmdLimpar_Click(object sender, EventArgs e)
            {
                LimparCampos();
            }

            private void cmdIncluir_Click(object sender, EventArgs e)
            {
                Incluir();
            }

            private void cmdExcluir_Click(object sender, EventArgs e)
            {
                Excluir();
            }

            private void cmdConsultar_Click(object sender, EventArgs e)
            {
                Consultar();
            }

            private void cmdAtualizar_Click(object sender, EventArgs e)
            {
                Atualizar();
            }
        #endregion

        #region [ Métodos Privados ]
            private void IniciarControles()
            {
                SQLHelperController controller = new SQLHelperController();
                StringBuilder connectionstring = new StringBuilder();

                try
                {
		            connectionstring.Append("Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=");
		            connectionstring.Append("C:\\3PPVende\\cep.mdb");
		            connectionstring.Append(";Mode=Share Deny None;Extended Properties=\"\";");
		            connectionstring.Append("Jet OLEDB:System database=\"\";");
		            connectionstring.Append("Jet OLEDB:Registry Path=\"\";");
		            connectionstring.Append("Jet OLEDB:Engine Type=5;");
		            connectionstring.Append("Jet OLEDB:Database Locking Mode=1;");
		            connectionstring.Append("Jet OLEDB:Global Partial Bulk Ops=2;");
		            connectionstring.Append("Jet OLEDB:Global Bulk Transactions=1;");
		            connectionstring.Append("Jet OLEDB:New Database Password=\"\";");
		            connectionstring.Append("Jet OLEDB:Create System Database=False;");
		            connectionstring.Append("Jet OLEDB:Encrypt Database=False;");
		            connectionstring.Append("Jet OLEDB:Don't Copy Locale on Compact=False;");
		            connectionstring.Append("Jet OLEDB:Compact Without Replica Repair=False;");
		            connectionstring.Append("Jet OLEDB:SFP=False");

                    controller.SetConnection(connectionstring.ToString());

                    lblMensagem.Text = "";
                    LimparCampos();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private void LimparCampos()
            {
                try
                {
                    txtCEP.Text = String.Empty;
                    txtEndereco.Text = String.Empty;
                    txtBairro.Text = String.Empty;
                    txtCidade.Text = String.Empty;
                    txtUF.Text = String.Empty;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private void Consultar()
            {
                SHLCepEnderecoBLL bllCepEndereco = new SHLCepEnderecoBLL();
                SHLCepEndereco cependereco = null;

                try
                {
                    lblMensagem.Text = "";
                    cependereco = new SHLCepEndereco();

                    if(txtCEP.Text != String.Empty)
                        cependereco.CEP = txtCEP.Text;

                    if(txtEndereco.Text != String.Empty)
                        cependereco.ENDERECO = txtEndereco.Text;

                    if(txtBairro.Text != String.Empty)
                        cependereco.BAIRRO = txtBairro.Text;

                    if(txtCidade.Text != String.Empty)
                        cependereco.CIDADE = txtCidade.Text;

                    if (txtUF.Text != String.Empty)
                        cependereco.ESTADO = txtUF.Text;

                    cependereco = bllCepEndereco.SelectSHLCepEndereco(cependereco);

                    if (cependereco == null)
                        throw new Exception("CEP não encontrado.");

                    txtCEP.Text = cependereco.CEP != null?cependereco.CEP:"";
                    txtEndereco.Text = cependereco.ENDERECO != null ? cependereco.ENDERECO : "";
                    txtBairro.Text = cependereco.BAIRRO != null ? cependereco.BAIRRO : "";
                    txtCidade.Text = cependereco.CIDADE != null ? cependereco.CIDADE : "";
                    txtUF.Text = cependereco.ESTADO != null ? cependereco.ESTADO : "";

                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private void Incluir()
            {
                SHLCepEnderecoBLL bllCepEndereco = new SHLCepEnderecoBLL();
                SHLCepEndereco cependereco = null;
                Int32 nid = 0;

                try
                {
                    lblMensagem.Text = "";
                    cependereco = new SHLCepEndereco();

                    if (txtCEP.Text != String.Empty)
                        cependereco.CEP = txtCEP.Text;

                    if (txtEndereco.Text != String.Empty)
                        cependereco.ENDERECO = txtEndereco.Text;

                    if (txtBairro.Text != String.Empty)
                        cependereco.BAIRRO = txtBairro.Text;

                    if (txtCidade.Text != String.Empty)
                        cependereco.CIDADE = txtCidade.Text;

                    if (txtUF.Text != String.Empty)
                        cependereco.ESTADO = txtUF.Text;

                    nid = bllCepEndereco.InsertSHLCepEndereco(cependereco);

                    lblMensagem.Text = "Novo id é " + nid.ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private void Atualizar()
            {
                SHLCepEnderecoBLL bllCepEndereco = new SHLCepEnderecoBLL();
                SHLCepEndereco cependereco = null;

                try
                {
                    lblMensagem.Text = "";
                    cependereco = new SHLCepEndereco();

                    if (txtCEP.Text != String.Empty)
                        cependereco.CEP = txtCEP.Text;

                    cependereco = bllCepEndereco.SelectSHLCepEndereco(cependereco);

                    if (txtEndereco.Text != String.Empty)
                        cependereco.ENDERECO = txtEndereco.Text;

                    if (txtBairro.Text != String.Empty)
                        cependereco.BAIRRO = txtBairro.Text;

                    if (txtCidade.Text != String.Empty)
                        cependereco.CIDADE = txtCidade.Text;

                    if (txtUF.Text != String.Empty)
                        cependereco.ESTADO = txtUF.Text;

                    bllCepEndereco.UpdateSHLCepEndereco(cependereco);

                    lblMensagem.Text = "Registro atualizado com sucesso!";
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }

            private void Excluir()
            {
                SHLCepEnderecoBLL bllCepEndereco = new SHLCepEnderecoBLL();
                SHLCepEndereco cependereco = null;

                try
                {
                    lblMensagem.Text = "";
                    cependereco = new SHLCepEndereco();

                    if (txtCEP.Text != String.Empty)
                        cependereco.CEP = txtCEP.Text;

                    if (txtEndereco.Text != String.Empty)
                        cependereco.ENDERECO = txtEndereco.Text;

                    if (txtBairro.Text != String.Empty)
                        cependereco.BAIRRO = txtBairro.Text;

                    if (txtCidade.Text != String.Empty)
                        cependereco.CIDADE = txtCidade.Text;

                    if (txtUF.Text != String.Empty)
                        cependereco.ESTADO = txtUF.Text;

                    bllCepEndereco.DeleteSHLCepEndereco(cependereco);

                    lblMensagem.Text = "Registro excluído com sucesso!";
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        #endregion
    }
}
