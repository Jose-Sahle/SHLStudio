namespace GPRotinaUI
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
            this.gridRotina = new System.Windows.Forms.DataGridView();
            this.lblIDRotina = new System.Windows.Forms.Label();
            this.lblNomeRotina = new System.Windows.Forms.Label();
            this.chkAtivo = new System.Windows.Forms.CheckBox();
            this.chkInativo = new System.Windows.Forms.CheckBox();
            this.lblDescricao = new System.Windows.Forms.Label();
            this.lblDataCriacao = new System.Windows.Forms.Label();
            this.lblFuncional = new System.Windows.Forms.Label();
            this.lblUsuario = new System.Windows.Forms.Label();
            this.lblApelido = new System.Windows.Forms.Label();
            this.txtIDRotina = new System.Windows.Forms.TextBox();
            this.txtNomeRotina = new System.Windows.Forms.TextBox();
            this.txtDescricao = new System.Windows.Forms.TextBox();
            this.txtFuncional = new System.Windows.Forms.TextBox();
            this.txtUsuario = new System.Windows.Forms.TextBox();
            this.txtApelido = new System.Windows.Forms.TextBox();
            this.dtpDataCriacao = new System.Windows.Forms.DateTimePicker();
            this.cmdSelecinarLista = new System.Windows.Forms.Button();
            this.cmdSelecionarUnico = new System.Windows.Forms.Button();
            this.cmdIncluir = new System.Windows.Forms.Button();
            this.cmdAlterar = new System.Windows.Forms.Button();
            this.cmdExcluir = new System.Windows.Forms.Button();
            this.cmdLimparCampos = new System.Windows.Forms.Button();
            this.lblRegistros = new System.Windows.Forms.Label();
            this.gridDLL = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.gridRotina)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridDLL)).BeginInit();
            this.SuspendLayout();
            // 
            // gridRotina
            // 
            this.gridRotina.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.gridRotina.Location = new System.Drawing.Point(9, 13);
            this.gridRotina.Name = "gridRotina";
            this.gridRotina.Size = new System.Drawing.Size(800, 132);
            this.gridRotina.TabIndex = 0;
            this.gridRotina.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.gridRotina_CellClick);
            this.gridRotina.RowHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.gridRotina_RowHeaderMouseClick);
            // 
            // lblIDRotina
            // 
            this.lblIDRotina.AutoSize = true;
            this.lblIDRotina.Location = new System.Drawing.Point(15, 259);
            this.lblIDRotina.Name = "lblIDRotina";
            this.lblIDRotina.Size = new System.Drawing.Size(52, 13);
            this.lblIDRotina.TabIndex = 1;
            this.lblIDRotina.Text = "ID Rotina";
            // 
            // lblNomeRotina
            // 
            this.lblNomeRotina.AutoSize = true;
            this.lblNomeRotina.Location = new System.Drawing.Point(15, 287);
            this.lblNomeRotina.Name = "lblNomeRotina";
            this.lblNomeRotina.Size = new System.Drawing.Size(69, 13);
            this.lblNomeRotina.TabIndex = 2;
            this.lblNomeRotina.Text = "Nome Rotina";
            // 
            // chkAtivo
            // 
            this.chkAtivo.AutoSize = true;
            this.chkAtivo.Location = new System.Drawing.Point(18, 342);
            this.chkAtivo.Name = "chkAtivo";
            this.chkAtivo.Size = new System.Drawing.Size(50, 17);
            this.chkAtivo.TabIndex = 3;
            this.chkAtivo.Text = "Ativo";
            this.chkAtivo.UseVisualStyleBackColor = true;
            // 
            // chkInativo
            // 
            this.chkInativo.AutoSize = true;
            this.chkInativo.Location = new System.Drawing.Point(95, 342);
            this.chkInativo.Name = "chkInativo";
            this.chkInativo.Size = new System.Drawing.Size(58, 17);
            this.chkInativo.TabIndex = 4;
            this.chkInativo.Text = "Inativo";
            this.chkInativo.UseVisualStyleBackColor = true;
            // 
            // lblDescricao
            // 
            this.lblDescricao.AutoSize = true;
            this.lblDescricao.Location = new System.Drawing.Point(286, 287);
            this.lblDescricao.Name = "lblDescricao";
            this.lblDescricao.Size = new System.Drawing.Size(55, 13);
            this.lblDescricao.TabIndex = 5;
            this.lblDescricao.Text = "Descrição";
            // 
            // lblDataCriacao
            // 
            this.lblDataCriacao.AutoSize = true;
            this.lblDataCriacao.Location = new System.Drawing.Point(286, 259);
            this.lblDataCriacao.Name = "lblDataCriacao";
            this.lblDataCriacao.Size = new System.Drawing.Size(84, 13);
            this.lblDataCriacao.TabIndex = 6;
            this.lblDataCriacao.Text = "Data da Criação";
            // 
            // lblFuncional
            // 
            this.lblFuncional.AutoSize = true;
            this.lblFuncional.Location = new System.Drawing.Point(14, 313);
            this.lblFuncional.Name = "lblFuncional";
            this.lblFuncional.Size = new System.Drawing.Size(53, 13);
            this.lblFuncional.TabIndex = 8;
            this.lblFuncional.Text = "Funcional";
            // 
            // lblUsuario
            // 
            this.lblUsuario.AutoSize = true;
            this.lblUsuario.Location = new System.Drawing.Point(286, 313);
            this.lblUsuario.Name = "lblUsuario";
            this.lblUsuario.Size = new System.Drawing.Size(43, 13);
            this.lblUsuario.TabIndex = 7;
            this.lblUsuario.Text = "Usuário";
            // 
            // lblApelido
            // 
            this.lblApelido.AutoSize = true;
            this.lblApelido.Location = new System.Drawing.Point(634, 313);
            this.lblApelido.Name = "lblApelido";
            this.lblApelido.Size = new System.Drawing.Size(42, 13);
            this.lblApelido.TabIndex = 9;
            this.lblApelido.Text = "Apelido";
            // 
            // txtIDRotina
            // 
            this.txtIDRotina.Location = new System.Drawing.Point(95, 256);
            this.txtIDRotina.Name = "txtIDRotina";
            this.txtIDRotina.Size = new System.Drawing.Size(58, 20);
            this.txtIDRotina.TabIndex = 10;
            // 
            // txtNomeRotina
            // 
            this.txtNomeRotina.Location = new System.Drawing.Point(95, 284);
            this.txtNomeRotina.Name = "txtNomeRotina";
            this.txtNomeRotina.Size = new System.Drawing.Size(185, 20);
            this.txtNomeRotina.TabIndex = 11;
            // 
            // txtDescricao
            // 
            this.txtDescricao.Location = new System.Drawing.Point(377, 284);
            this.txtDescricao.Name = "txtDescricao";
            this.txtDescricao.Size = new System.Drawing.Size(251, 20);
            this.txtDescricao.TabIndex = 12;
            // 
            // txtFuncional
            // 
            this.txtFuncional.Location = new System.Drawing.Point(95, 310);
            this.txtFuncional.Name = "txtFuncional";
            this.txtFuncional.Size = new System.Drawing.Size(185, 20);
            this.txtFuncional.TabIndex = 13;
            // 
            // txtUsuario
            // 
            this.txtUsuario.Location = new System.Drawing.Point(377, 310);
            this.txtUsuario.Name = "txtUsuario";
            this.txtUsuario.Size = new System.Drawing.Size(251, 20);
            this.txtUsuario.TabIndex = 14;
            // 
            // txtApelido
            // 
            this.txtApelido.Location = new System.Drawing.Point(682, 310);
            this.txtApelido.Name = "txtApelido";
            this.txtApelido.Size = new System.Drawing.Size(125, 20);
            this.txtApelido.TabIndex = 15;
            // 
            // dtpDataCriacao
            // 
            this.dtpDataCriacao.CustomFormat = "dd/MM/yyyy HH:mm:ss";
            this.dtpDataCriacao.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.dtpDataCriacao.Location = new System.Drawing.Point(377, 256);
            this.dtpDataCriacao.Name = "dtpDataCriacao";
            this.dtpDataCriacao.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.dtpDataCriacao.RightToLeftLayout = true;
            this.dtpDataCriacao.ShowCheckBox = true;
            this.dtpDataCriacao.Size = new System.Drawing.Size(251, 20);
            this.dtpDataCriacao.TabIndex = 16;
            // 
            // cmdSelecinarLista
            // 
            this.cmdSelecinarLista.Location = new System.Drawing.Point(18, 382);
            this.cmdSelecinarLista.Name = "cmdSelecinarLista";
            this.cmdSelecinarLista.Size = new System.Drawing.Size(108, 23);
            this.cmdSelecinarLista.TabIndex = 17;
            this.cmdSelecinarLista.Text = "Selecionar Lista";
            this.cmdSelecinarLista.UseVisualStyleBackColor = true;
            this.cmdSelecinarLista.Click += new System.EventHandler(this.cmdSelecinarLista_Click);
            // 
            // cmdSelecionarUnico
            // 
            this.cmdSelecionarUnico.Location = new System.Drawing.Point(142, 382);
            this.cmdSelecionarUnico.Name = "cmdSelecionarUnico";
            this.cmdSelecionarUnico.Size = new System.Drawing.Size(108, 23);
            this.cmdSelecionarUnico.TabIndex = 18;
            this.cmdSelecionarUnico.Text = "Selecionar Único";
            this.cmdSelecionarUnico.UseVisualStyleBackColor = true;
            this.cmdSelecionarUnico.Click += new System.EventHandler(this.cmdSelecionarUnico_Click);
            // 
            // cmdIncluir
            // 
            this.cmdIncluir.Location = new System.Drawing.Point(332, 382);
            this.cmdIncluir.Name = "cmdIncluir";
            this.cmdIncluir.Size = new System.Drawing.Size(108, 23);
            this.cmdIncluir.TabIndex = 19;
            this.cmdIncluir.Text = "Incluir";
            this.cmdIncluir.UseVisualStyleBackColor = true;
            this.cmdIncluir.Click += new System.EventHandler(this.cmdIncluir_Click);
            // 
            // cmdAlterar
            // 
            this.cmdAlterar.Location = new System.Drawing.Point(446, 382);
            this.cmdAlterar.Name = "cmdAlterar";
            this.cmdAlterar.Size = new System.Drawing.Size(108, 23);
            this.cmdAlterar.TabIndex = 20;
            this.cmdAlterar.Text = "Alterar";
            this.cmdAlterar.UseVisualStyleBackColor = true;
            this.cmdAlterar.Click += new System.EventHandler(this.cmdAlterar_Click);
            // 
            // cmdExcluir
            // 
            this.cmdExcluir.Location = new System.Drawing.Point(560, 382);
            this.cmdExcluir.Name = "cmdExcluir";
            this.cmdExcluir.Size = new System.Drawing.Size(108, 23);
            this.cmdExcluir.TabIndex = 21;
            this.cmdExcluir.Text = "Excluir";
            this.cmdExcluir.UseVisualStyleBackColor = true;
            this.cmdExcluir.Click += new System.EventHandler(this.cmdExcluir_Click);
            // 
            // cmdLimparCampos
            // 
            this.cmdLimparCampos.Location = new System.Drawing.Point(17, 432);
            this.cmdLimparCampos.Name = "cmdLimparCampos";
            this.cmdLimparCampos.Size = new System.Drawing.Size(108, 23);
            this.cmdLimparCampos.TabIndex = 22;
            this.cmdLimparCampos.Text = "LimparCampos";
            this.cmdLimparCampos.UseVisualStyleBackColor = true;
            this.cmdLimparCampos.Click += new System.EventHandler(this.cmdLimparCampos_Click);
            // 
            // lblRegistros
            // 
            this.lblRegistros.AutoSize = true;
            this.lblRegistros.Location = new System.Drawing.Point(723, 249);
            this.lblRegistros.Name = "lblRegistros";
            this.lblRegistros.Size = new System.Drawing.Size(67, 13);
            this.lblRegistros.TabIndex = 23;
            this.lblRegistros.Text = "%s Registros";
            // 
            // gridDLL
            // 
            this.gridDLL.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.gridDLL.Location = new System.Drawing.Point(9, 150);
            this.gridDLL.Name = "gridDLL";
            this.gridDLL.Size = new System.Drawing.Size(800, 96);
            this.gridDLL.TabIndex = 24;
            // 
            // frmPrincipal
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(819, 467);
            this.Controls.Add(this.gridDLL);
            this.Controls.Add(this.lblRegistros);
            this.Controls.Add(this.cmdLimparCampos);
            this.Controls.Add(this.cmdExcluir);
            this.Controls.Add(this.cmdAlterar);
            this.Controls.Add(this.cmdIncluir);
            this.Controls.Add(this.cmdSelecionarUnico);
            this.Controls.Add(this.cmdSelecinarLista);
            this.Controls.Add(this.dtpDataCriacao);
            this.Controls.Add(this.txtApelido);
            this.Controls.Add(this.txtUsuario);
            this.Controls.Add(this.txtFuncional);
            this.Controls.Add(this.txtDescricao);
            this.Controls.Add(this.txtNomeRotina);
            this.Controls.Add(this.txtIDRotina);
            this.Controls.Add(this.lblApelido);
            this.Controls.Add(this.lblFuncional);
            this.Controls.Add(this.lblUsuario);
            this.Controls.Add(this.lblDataCriacao);
            this.Controls.Add(this.lblDescricao);
            this.Controls.Add(this.chkInativo);
            this.Controls.Add(this.chkAtivo);
            this.Controls.Add(this.lblNomeRotina);
            this.Controls.Add(this.lblIDRotina);
            this.Controls.Add(this.gridRotina);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "frmPrincipal";
            this.Text = "ProdigGR";
            this.Load += new System.EventHandler(this.frmPrincipal_Load);
            ((System.ComponentModel.ISupportInitialize)(this.gridRotina)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridDLL)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView gridRotina;
        private System.Windows.Forms.Label lblIDRotina;
        private System.Windows.Forms.Label lblNomeRotina;
        private System.Windows.Forms.CheckBox chkAtivo;
        private System.Windows.Forms.CheckBox chkInativo;
        private System.Windows.Forms.Label lblDescricao;
        private System.Windows.Forms.Label lblDataCriacao;
        private System.Windows.Forms.Label lblFuncional;
        private System.Windows.Forms.Label lblUsuario;
        private System.Windows.Forms.Label lblApelido;
        private System.Windows.Forms.TextBox txtIDRotina;
        private System.Windows.Forms.TextBox txtNomeRotina;
        private System.Windows.Forms.TextBox txtDescricao;
        private System.Windows.Forms.TextBox txtFuncional;
        private System.Windows.Forms.TextBox txtUsuario;
        private System.Windows.Forms.TextBox txtApelido;
        private System.Windows.Forms.DateTimePicker dtpDataCriacao;
        private System.Windows.Forms.Button cmdSelecinarLista;
        private System.Windows.Forms.Button cmdSelecionarUnico;
        private System.Windows.Forms.Button cmdIncluir;
        private System.Windows.Forms.Button cmdAlterar;
        private System.Windows.Forms.Button cmdExcluir;
        private System.Windows.Forms.Button cmdLimparCampos;
        private System.Windows.Forms.Label lblRegistros;
        private System.Windows.Forms.DataGridView gridDLL;
    }
}

