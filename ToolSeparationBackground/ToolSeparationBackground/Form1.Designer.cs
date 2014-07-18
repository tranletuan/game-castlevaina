namespace ToolSeparationBackground
{
    partial class Form1
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
            this.btnPicturePath = new System.Windows.Forms.Button();
            this.txtPicturePath = new System.Windows.Forms.TextBox();
            this.pgbSeparation = new System.Windows.Forms.ProgressBar();
            this.pbTexture = new System.Windows.Forms.PictureBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.pnlPicture = new System.Windows.Forms.Panel();
            this.pbPicture = new System.Windows.Forms.PictureBox();
            this.btnReset = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.pnlTexture = new System.Windows.Forms.Panel();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.cmbWidth = new System.Windows.Forms.ComboBox();
            this.cmbHeight = new System.Windows.Forms.ComboBox();
            this.btnSeparation = new System.Windows.Forms.Button();
            this.trbZoom = new System.Windows.Forms.TrackBar();
            this.label2 = new System.Windows.Forms.Label();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.lbPictureSize = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel6 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel7 = new System.Windows.Forms.ToolStripStatusLabel();
            this.lbWHPicture = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel4 = new System.Windows.Forms.ToolStripStatusLabel();
            this.lbTextureSize = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel5 = new System.Windows.Forms.ToolStripStatusLabel();
            this.lbTotalTexture = new System.Windows.Forms.ToolStripStatusLabel();
            this.lbPercent = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pbTexture)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.pnlPicture.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbPicture)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.pnlTexture.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trbZoom)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnPicturePath
            // 
            this.btnPicturePath.Location = new System.Drawing.Point(699, 19);
            this.btnPicturePath.Name = "btnPicturePath";
            this.btnPicturePath.Size = new System.Drawing.Size(75, 23);
            this.btnPicturePath.TabIndex = 0;
            this.btnPicturePath.Text = "Picture Path";
            this.btnPicturePath.UseVisualStyleBackColor = true;
            this.btnPicturePath.Click += new System.EventHandler(this.btnPicturePath_Click);
            // 
            // txtPicturePath
            // 
            this.txtPicturePath.Enabled = false;
            this.txtPicturePath.Location = new System.Drawing.Point(6, 21);
            this.txtPicturePath.Name = "txtPicturePath";
            this.txtPicturePath.Size = new System.Drawing.Size(687, 20);
            this.txtPicturePath.TabIndex = 2;
            // 
            // pgbSeparation
            // 
            this.pgbSeparation.Location = new System.Drawing.Point(6, 48);
            this.pgbSeparation.Name = "pgbSeparation";
            this.pgbSeparation.Size = new System.Drawing.Size(500, 23);
            this.pgbSeparation.TabIndex = 4;
            // 
            // pbTexture
            // 
            this.pbTexture.Location = new System.Drawing.Point(0, 0);
            this.pbTexture.Name = "pbTexture";
            this.pbTexture.Size = new System.Drawing.Size(100, 42);
            this.pbTexture.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pbTexture.TabIndex = 5;
            this.pbTexture.TabStop = false;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.pnlPicture);
            this.groupBox1.Location = new System.Drawing.Point(12, 159);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(782, 294);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Picture";
            // 
            // pnlPicture
            // 
            this.pnlPicture.AutoScroll = true;
            this.pnlPicture.AutoSize = true;
            this.pnlPicture.Controls.Add(this.pbPicture);
            this.pnlPicture.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlPicture.Location = new System.Drawing.Point(3, 16);
            this.pnlPicture.Name = "pnlPicture";
            this.pnlPicture.Size = new System.Drawing.Size(776, 275);
            this.pnlPicture.TabIndex = 1;
            // 
            // pbPicture
            // 
            this.pbPicture.Location = new System.Drawing.Point(0, 0);
            this.pbPicture.Name = "pbPicture";
            this.pbPicture.Size = new System.Drawing.Size(100, 50);
            this.pbPicture.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pbPicture.TabIndex = 0;
            this.pbPicture.TabStop = false;
            // 
            // btnReset
            // 
            this.btnReset.Location = new System.Drawing.Point(711, 116);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(75, 23);
            this.btnReset.TabIndex = 2;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = true;
            this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.pnlTexture);
            this.groupBox2.Location = new System.Drawing.Point(12, 459);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(782, 83);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Texture";
            // 
            // pnlTexture
            // 
            this.pnlTexture.AutoScroll = true;
            this.pnlTexture.AutoSize = true;
            this.pnlTexture.Controls.Add(this.pbTexture);
            this.pnlTexture.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlTexture.Location = new System.Drawing.Point(3, 16);
            this.pnlTexture.Name = "pnlTexture";
            this.pnlTexture.Size = new System.Drawing.Size(776, 64);
            this.pnlTexture.TabIndex = 6;
            // 
            // groupBox3
            // 
            this.groupBox3.AutoSize = true;
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.label1);
            this.groupBox3.Controls.Add(this.cmbWidth);
            this.groupBox3.Controls.Add(this.cmbHeight);
            this.groupBox3.Controls.Add(this.btnPicturePath);
            this.groupBox3.Controls.Add(this.btnSeparation);
            this.groupBox3.Controls.Add(this.txtPicturePath);
            this.groupBox3.Controls.Add(this.pgbSeparation);
            this.groupBox3.Location = new System.Drawing.Point(12, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(782, 91);
            this.groupBox3.TabIndex = 0;
            this.groupBox3.TabStop = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(512, 54);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(62, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Size texture";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(667, 54);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(28, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "pixel";
            // 
            // cmbWidth
            // 
            this.cmbWidth.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbWidth.FormattingEnabled = true;
            this.cmbWidth.Items.AddRange(new object[] {
            "4",
            "8",
            "16",
            "32",
            "64"});
            this.cmbWidth.Location = new System.Drawing.Point(583, 51);
            this.cmbWidth.Name = "cmbWidth";
            this.cmbWidth.Size = new System.Drawing.Size(36, 21);
            this.cmbWidth.TabIndex = 5;
            // 
            // cmbHeight
            // 
            this.cmbHeight.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbHeight.FormattingEnabled = true;
            this.cmbHeight.Items.AddRange(new object[] {
            "4",
            "8",
            "16",
            "32",
            "64"});
            this.cmbHeight.Location = new System.Drawing.Point(626, 51);
            this.cmbHeight.Name = "cmbHeight";
            this.cmbHeight.Size = new System.Drawing.Size(36, 21);
            this.cmbHeight.TabIndex = 5;
            // 
            // btnSeparation
            // 
            this.btnSeparation.Enabled = false;
            this.btnSeparation.Location = new System.Drawing.Point(699, 49);
            this.btnSeparation.Name = "btnSeparation";
            this.btnSeparation.Size = new System.Drawing.Size(75, 23);
            this.btnSeparation.TabIndex = 1;
            this.btnSeparation.Text = "Separation";
            this.btnSeparation.UseVisualStyleBackColor = true;
            this.btnSeparation.Click += new System.EventHandler(this.btnSeparation_Click);
            // 
            // trbZoom
            // 
            this.trbZoom.Enabled = false;
            this.trbZoom.Location = new System.Drawing.Point(65, 116);
            this.trbZoom.Minimum = 1;
            this.trbZoom.Name = "trbZoom";
            this.trbZoom.Size = new System.Drawing.Size(223, 45);
            this.trbZoom.TabIndex = 3;
            this.trbZoom.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trbZoom.Value = 10;
            this.trbZoom.ValueChanged += new System.EventHandler(this.trbZoom_ValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 121);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(34, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Zoom";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.lbPictureSize,
            this.toolStripStatusLabel6,
            this.toolStripStatusLabel7,
            this.lbWHPicture,
            this.toolStripStatusLabel3,
            this.toolStripStatusLabel4,
            this.lbTextureSize,
            this.toolStripStatusLabel2,
            this.toolStripStatusLabel5,
            this.lbTotalTexture});
            this.statusStrip1.Location = new System.Drawing.Point(0, 563);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(806, 22);
            this.statusStrip1.TabIndex = 0;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(72, 17);
            this.toolStripStatusLabel1.Text = "Picture size :";
            // 
            // lbPictureSize
            // 
            this.lbPictureSize.Name = "lbPictureSize";
            this.lbPictureSize.Size = new System.Drawing.Size(29, 17);
            this.lbPictureSize.Text = "0 kb";
            // 
            // toolStripStatusLabel6
            // 
            this.toolStripStatusLabel6.Name = "toolStripStatusLabel6";
            this.toolStripStatusLabel6.Size = new System.Drawing.Size(10, 17);
            this.toolStripStatusLabel6.Text = "|";
            // 
            // toolStripStatusLabel7
            // 
            this.toolStripStatusLabel7.Name = "toolStripStatusLabel7";
            this.toolStripStatusLabel7.Size = new System.Drawing.Size(76, 17);
            this.toolStripStatusLabel7.Text = "WH picture : ";
            // 
            // lbWHPicture
            // 
            this.lbWHPicture.Name = "lbWHPicture";
            this.lbWHPicture.Size = new System.Drawing.Size(30, 17);
            this.lbWHPicture.Text = "0 x 0";
            // 
            // toolStripStatusLabel3
            // 
            this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            this.toolStripStatusLabel3.Size = new System.Drawing.Size(10, 17);
            this.toolStripStatusLabel3.Text = "|";
            // 
            // toolStripStatusLabel4
            // 
            this.toolStripStatusLabel4.Name = "toolStripStatusLabel4";
            this.toolStripStatusLabel4.Size = new System.Drawing.Size(77, 17);
            this.toolStripStatusLabel4.Text = "Texture size : ";
            // 
            // lbTextureSize
            // 
            this.lbTextureSize.Name = "lbTextureSize";
            this.lbTextureSize.Size = new System.Drawing.Size(29, 17);
            this.lbTextureSize.Text = "0 kb";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(10, 17);
            this.toolStripStatusLabel2.Text = "|";
            // 
            // toolStripStatusLabel5
            // 
            this.toolStripStatusLabel5.Name = "toolStripStatusLabel5";
            this.toolStripStatusLabel5.Size = new System.Drawing.Size(85, 17);
            this.toolStripStatusLabel5.Text = "Total Texture : ";
            // 
            // lbTotalTexture
            // 
            this.lbTotalTexture.Name = "lbTotalTexture";
            this.lbTotalTexture.Size = new System.Drawing.Size(13, 17);
            this.lbTotalTexture.Text = "0";
            // 
            // lbPercent
            // 
            this.lbPercent.AutoSize = true;
            this.lbPercent.Location = new System.Drawing.Point(294, 121);
            this.lbPercent.Name = "lbPercent";
            this.lbPercent.Size = new System.Drawing.Size(33, 13);
            this.lbPercent.TabIndex = 5;
            this.lbPercent.Text = "100%";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(806, 585);
            this.Controls.Add(this.lbPercent);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.trbZoom);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Separation Form";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pbTexture)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.pnlPicture.ResumeLayout(false);
            this.pnlPicture.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbPicture)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.pnlTexture.ResumeLayout(false);
            this.pnlTexture.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trbZoom)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TrackBar trbZoom;
        private System.Windows.Forms.Button btnPicturePath;
        private System.Windows.Forms.TextBox txtPicturePath;
        private System.Windows.Forms.ProgressBar pgbSeparation;
        private System.Windows.Forms.PictureBox pbTexture;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.PictureBox pbPicture;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnSeparation;
        private System.Windows.Forms.Panel pnlPicture;
        private System.Windows.Forms.Panel pnlTexture;
        private System.Windows.Forms.ComboBox cmbHeight;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnReset;
       
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripStatusLabel lbPictureSize;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel6;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel7;
        private System.Windows.Forms.ToolStripStatusLabel lbWHPicture;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel3;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel4;
        private System.Windows.Forms.ToolStripStatusLabel lbTextureSize;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel5;
        private System.Windows.Forms.ToolStripStatusLabel lbTotalTexture;
        private System.Windows.Forms.Label lbPercent;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cmbWidth;
    }
}

