namespace MapEditor
{
    partial class Form2
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.txtBackgroundPath = new System.Windows.Forms.TextBox();
            this.txtResourcesPath = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnOpenResourcesPath = new System.Windows.Forms.Button();
            this.btnOpenBackgroundPath = new System.Windows.Forms.Button();
            this.cbAutoLoad = new System.Windows.Forms.CheckBox();
            this.btnSave = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(7, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(124, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "Background Path :";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(6, 72);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(116, 15);
            this.label2.TabIndex = 0;
            this.label2.Text = "Resources Path :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(6, 116);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 15);
            this.label3.TabIndex = 0;
            this.label3.Text = "Load :";
            // 
            // txtBackgroundPath
            // 
            this.txtBackgroundPath.Location = new System.Drawing.Point(134, 29);
            this.txtBackgroundPath.Name = "txtBackgroundPath";
            this.txtBackgroundPath.Size = new System.Drawing.Size(253, 20);
            this.txtBackgroundPath.TabIndex = 1;
            // 
            // txtResourcesPath
            // 
            this.txtResourcesPath.Location = new System.Drawing.Point(134, 71);
            this.txtResourcesPath.Name = "txtResourcesPath";
            this.txtResourcesPath.Size = new System.Drawing.Size(253, 20);
            this.txtResourcesPath.TabIndex = 1;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnOpenResourcesPath);
            this.groupBox1.Controls.Add(this.btnOpenBackgroundPath);
            this.groupBox1.Controls.Add(this.cbAutoLoad);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.txtResourcesPath);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txtBackgroundPath);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(445, 158);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "groupBox1";
            // 
            // btnOpenResourcesPath
            // 
            this.btnOpenResourcesPath.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnOpenResourcesPath.Location = new System.Drawing.Point(393, 69);
            this.btnOpenResourcesPath.Name = "btnOpenResourcesPath";
            this.btnOpenResourcesPath.Size = new System.Drawing.Size(45, 23);
            this.btnOpenResourcesPath.TabIndex = 3;
            this.btnOpenResourcesPath.Text = "Open";
            this.btnOpenResourcesPath.UseVisualStyleBackColor = true;
            this.btnOpenResourcesPath.Click += new System.EventHandler(this.btnOpenResourcesPath_Click);
            // 
            // btnOpenBackgroundPath
            // 
            this.btnOpenBackgroundPath.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnOpenBackgroundPath.Location = new System.Drawing.Point(393, 27);
            this.btnOpenBackgroundPath.Name = "btnOpenBackgroundPath";
            this.btnOpenBackgroundPath.Size = new System.Drawing.Size(45, 23);
            this.btnOpenBackgroundPath.TabIndex = 3;
            this.btnOpenBackgroundPath.Text = "Open";
            this.btnOpenBackgroundPath.UseVisualStyleBackColor = true;
            this.btnOpenBackgroundPath.Click += new System.EventHandler(this.btnOpenBackgroundPath_Click);
            // 
            // cbAutoLoad
            // 
            this.cbAutoLoad.AutoSize = true;
            this.cbAutoLoad.Location = new System.Drawing.Point(134, 117);
            this.cbAutoLoad.Name = "cbAutoLoad";
            this.cbAutoLoad.Size = new System.Drawing.Size(75, 17);
            this.cbAutoLoad.TabIndex = 2;
            this.cbAutoLoad.Text = "Auto Load";
            this.cbAutoLoad.UseVisualStyleBackColor = true;
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(286, 176);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(75, 23);
            this.btnSave.TabIndex = 3;
            this.btnSave.Text = "Save";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(382, 176);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 3;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            // 
            // Form2
            // 
            this.AcceptButton = this.btnSave;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnCancel;
            this.ClientSize = new System.Drawing.Size(469, 211);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.KeyPreview = true;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form2";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Setting";
            this.Load += new System.EventHandler(this.Form2_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtBackgroundPath;
        private System.Windows.Forms.TextBox txtResourcesPath;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnOpenResourcesPath;
        private System.Windows.Forms.Button btnOpenBackgroundPath;
        private System.Windows.Forms.CheckBox cbAutoLoad;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Button btnCancel;
    }
}