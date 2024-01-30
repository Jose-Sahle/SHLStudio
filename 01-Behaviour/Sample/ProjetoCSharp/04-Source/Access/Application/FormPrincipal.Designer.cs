namespace CepEndereco
{
    partial class frmPrincipal
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.grpInsert = new System.Windows.Forms.GroupBox();
            this.txtUF = new System.Windows.Forms.TextBox();
            this.lblUF = new System.Windows.Forms.Label();
            this.txtCidade = new System.Windows.Forms.TextBox();
            this.lblCidade = new System.Windows.Forms.Label();
            this.txtBairro = new System.Windows.Forms.TextBox();
            this.lblBairro = new System.Windows.Forms.Label();
            this.txtEndereco = new System.Windows.Forms.TextBox();
            this.lblEndereco = new System.Windows.Forms.Label();
            this.txtCEP = new System.Windows.Forms.TextBox();
            this.lblCEP = new System.Windows.Forms.Label();
            this.cmdLimpar = new System.Windows.Forms.Button();
            this.cmdConsultar = new System.Windows.Forms.Button();
            this.cmdIncluir = new System.Windows.Forms.Button();
            this.cmdAtualizar = new System.Windows.Forms.Button();
            this.cmdExcluir = new System.Windows.Forms.Button();
            this.lblMensagem = new System.Windows.Forms.Label();
            this.grpInsert.SuspendLayout();
            this.SuspendLayout();
            // 
            // grpInsert
            // 
            this.grpInsert.Controls.Add(this.txtUF);
            this.grpInsert.Controls.Add(this.lblUF);
            this.grpInsert.Controls.Add(this.txtCidade);
            this.grpInsert.Controls.Add(this.lblCidade);
            this.grpInsert.Controls.Add(this.txtBairro);
            this.grpInsert.Controls.Add(this.lblBairro);
            this.grpInsert.Controls.Add(this.txtEndereco);
            this.grpInsert.Controls.Add(this.lblEndereco);
            this.grpInsert.Controls.Add(this.txtCEP);
            this.grpInsert.Controls.Add(this.lblCEP);
            this.grpInsert.Location = new System.Drawing.Point(16, 7);
            this.grpInsert.Name = "grpInsert";
            this.grpInsert.Size = new System.Drawing.Size(429, 163);
            this.grpInsert.TabIndex = 0;
            this.grpInsert.TabStop = false;
            this.grpInsert.Text = "groupBox1";
            // 
            // txtUF
            // 
            this.txtUF.Location = new System.Drawing.Point(80, 131);
            this.txtUF.MaxLength = 2;
            this.txtUF.Name = "txtUF";
            this.txtUF.Size = new System.Drawing.Size(54, 20);
            this.txtUF.TabIndex = 9;
            // 
            // lblUF
            // 
            this.lblUF.AutoSize = true;
            this.lblUF.Location = new System.Drawing.Point(56, 135);
            this.lblUF.Name = "lblUF";
            this.lblUF.Size = new System.Drawing.Size(21, 13);
            this.lblUF.TabIndex = 8;
            this.lblUF.Text = "UF";
            // 
            // txtCidade
            // 
            this.txtCidade.Location = new System.Drawing.Point(80, 105);
            this.txtCidade.MaxLength = 8000;
            this.txtCidade.Name = "txtCidade";
            this.txtCidade.Size = new System.Drawing.Size(329, 20);
            this.txtCidade.TabIndex = 7;
            // 
            // lblCidade
            // 
            this.lblCidade.AutoSize = true;
            this.lblCidade.Location = new System.Drawing.Point(37, 108);
            this.lblCidade.Name = "lblCidade";
            this.lblCidade.Size = new System.Drawing.Size(40, 13);
            this.lblCidade.TabIndex = 6;
            this.lblCidade.Text = "Cidade";
            // 
            // txtBairro
            // 
            this.txtBairro.Location = new System.Drawing.Point(80, 79);
            this.txtBairro.MaxLength = 8000;
            this.txtBairro.Name = "txtBairro";
            this.txtBairro.Size = new System.Drawing.Size(329, 20);
            this.txtBairro.TabIndex = 5;
            // 
            // lblBairro
            // 
            this.lblBairro.AutoSize = true;
            this.lblBairro.Location = new System.Drawing.Point(43, 82);
            this.lblBairro.Name = "lblBairro";
            this.lblBairro.Size = new System.Drawing.Size(34, 13);
            this.lblBairro.TabIndex = 4;
            this.lblBairro.Text = "Bairro";
            // 
            // txtEndereco
            // 
            this.txtEndereco.Location = new System.Drawing.Point(80, 52);
            this.txtEndereco.MaxLength = 8000;
            this.txtEndereco.Name = "txtEndereco";
            this.txtEndereco.Size = new System.Drawing.Size(329, 20);
            this.txtEndereco.TabIndex = 3;
            // 
            // lblEndereco
            // 
            this.lblEndereco.AutoSize = true;
            this.lblEndereco.Location = new System.Drawing.Point(24, 55);
            this.lblEndereco.Name = "lblEndereco";
            this.lblEndereco.Size = new System.Drawing.Size(53, 13);
            this.lblEndereco.TabIndex = 2;
            this.lblEndereco.Text = "Endereço";
            // 
            // txtCEP
            // 
            this.txtCEP.Location = new System.Drawing.Point(80, 26);
            this.txtCEP.MaxLength = 8;
            this.txtCEP.Name = "txtCEP";
            this.txtCEP.Size = new System.Drawing.Size(100, 20);
            this.txtCEP.TabIndex = 1;
            // 
            // lblCEP
            // 
            this.lblCEP.AutoSize = true;
            this.lblCEP.Location = new System.Drawing.Point(49, 30);
            this.lblCEP.Name = "lblCEP";
            this.lblCEP.Size = new System.Drawing.Size(28, 13);
            this.lblCEP.TabIndex = 0;
            this.lblCEP.Text = "CEP";
            // 
            // cmdLimpar
            // 
            this.cmdLimpar.Location = new System.Drawing.Point(31, 176);
            this.cmdLimpar.Name = "cmdLimpar";
            this.cmdLimpar.Size = new System.Drawing.Size(75, 23);
            this.cmdLimpar.TabIndex = 1;
            this.cmdLimpar.Text = "Limpar";
            this.cmdLimpar.UseVisualStyleBackColor = true;
            this.cmdLimpar.Click += new System.EventHandler(this.cmdLimpar_Click);
            // 
            // cmdConsultar
            // 
            this.cmdConsultar.Location = new System.Drawing.Point(31, 215);
            this.cmdConsultar.Name = "cmdConsultar";
            this.cmdConsultar.Size = new System.Drawing.Size(75, 23);
            this.cmdConsultar.TabIndex = 2;
            this.cmdConsultar.Text = "Consultar";
            this.cmdConsultar.UseVisualStyleBackColor = true;
            this.cmdConsultar.Click += new System.EventHandler(this.cmdConsultar_Click);
            // 
            // cmdIncluir
            // 
            this.cmdIncluir.Location = new System.Drawing.Point(121, 176);
            this.cmdIncluir.Name = "cmdIncluir";
            this.cmdIncluir.Size = new System.Drawing.Size(75, 23);
            this.cmdIncluir.TabIndex = 3;
            this.cmdIncluir.Text = "Incluir";
            this.cmdIncluir.UseVisualStyleBackColor = true;
            this.cmdIncluir.Click += new System.EventHandler(this.cmdIncluir_Click);
            // 
            // cmdAtualizar
            // 
            this.cmdAtualizar.Location = new System.Drawing.Point(121, 215);
            this.cmdAtualizar.Name = "cmdAtualizar";
            this.cmdAtualizar.Size = new System.Drawing.Size(75, 23);
            this.cmdAtualizar.TabIndex = 4;
            this.cmdAtualizar.Text = "Atualizar";
            this.cmdAtualizar.UseVisualStyleBackColor = true;
            this.cmdAtualizar.Click += new System.EventHandler(this.cmdAtualizar_Click);
            // 
            // cmdExcluir
            // 
            this.cmdExcluir.Location = new System.Drawing.Point(202, 176);
            this.cmdExcluir.Name = "cmdExcluir";
            this.cmdExcluir.Size = new System.Drawing.Size(75, 23);
            this.cmdExcluir.TabIndex = 5;
            this.cmdExcluir.Text = "Excluir";
            this.cmdExcluir.UseVisualStyleBackColor = true;
            this.cmdExcluir.Click += new System.EventHandler(this.cmdExcluir_Click);
            // 
            // lblMensagem
            // 
            this.lblMensagem.Location = new System.Drawing.Point(28, 283);
            this.lblMensagem.Name = "lblMensagem";
            this.lblMensagem.Size = new System.Drawing.Size(399, 18);
            this.lblMensagem.TabIndex = 6;
            this.lblMensagem.Text = "*";
            this.lblMensagem.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // frmPrincipal
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(472, 326);
            this.Controls.Add(this.lblMensagem);
            this.Controls.Add(this.cmdExcluir);
            this.Controls.Add(this.cmdAtualizar);
            this.Controls.Add(this.cmdIncluir);
            this.Controls.Add(this.cmdConsultar);
            this.Controls.Add(this.cmdLimpar);
            this.Controls.Add(this.grpInsert);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "frmPrincipal";
            this.Text = "Test SHLStudio to Access";
            this.Load += new System.EventHandler(this.frmPrincipal_Load);
            this.grpInsert.ResumeLayout(false);
            this.grpInsert.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grpInsert;
        private System.Windows.Forms.TextBox txtUF;
        private System.Windows.Forms.Label lblUF;
        private System.Windows.Forms.TextBox txtCidade;
        private System.Windows.Forms.Label lblCidade;
        private System.Windows.Forms.TextBox txtBairro;
        private System.Windows.Forms.Label lblBairro;
        private System.Windows.Forms.TextBox txtEndereco;
        private System.Windows.Forms.Label lblEndereco;
        private System.Windows.Forms.TextBox txtCEP;
        private System.Windows.Forms.Label lblCEP;
        private System.Windows.Forms.Button cmdLimpar;
        private System.Windows.Forms.Button cmdConsultar;
        private System.Windows.Forms.Button cmdIncluir;
        private System.Windows.Forms.Button cmdAtualizar;
        private System.Windows.Forms.Button cmdExcluir;
        private System.Windows.Forms.Label lblMensagem;
    }
}

