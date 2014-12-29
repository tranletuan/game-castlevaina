namespace MapEditor
{
    partial class MapEditor
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MapEditor));
            this.buttonBG = new System.Windows.Forms.Button();
            this.buttonload = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.pictureBoxBG = new System.Windows.Forms.PictureBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.listViewControl = new System.Windows.Forms.ListView();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBoxXHeight = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.comboBoxNameItem = new System.Windows.Forms.ComboBox();
            this.label13 = new System.Windows.Forms.Label();
            this.comboBoxDir = new System.Windows.Forms.ComboBox();
            this.textBoxXWidth = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.buttonEdit = new System.Windows.Forms.Button();
            this.textBoxNameOB = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textBoxHeightOB = new System.Windows.Forms.TextBox();
            this.textBoxWidthOB = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.tabControl = new System.Windows.Forms.TabControl();
            this.tabPageBG = new System.Windows.Forms.TabPage();
            this.listViewBG = new System.Windows.Forms.ListView();
            this.tabPageOB = new System.Windows.Forms.TabPage();
            this.listViewOB = new System.Windows.Forms.ListView();
            this.tabPageItem = new System.Windows.Forms.TabPage();
            this.listViewItem = new System.Windows.Forms.ListView();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxBGWidth = new System.Windows.Forms.TextBox();
            this.textBoxBGHeigth = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.textBoxX = new System.Windows.Forms.TextBox();
            this.textBoxY = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.imageListOB = new System.Windows.Forms.ImageList(this.components);
            this.imageListBG = new System.Windows.Forms.ImageList(this.components);
            this.buttonSave = new System.Windows.Forms.Button();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.imageListControl = new System.Windows.Forms.ImageList(this.components);
            this.buttonRest = new System.Windows.Forms.Button();
            this.imageListItem = new System.Windows.Forms.ImageList(this.components);
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.textBoxChaY = new System.Windows.Forms.TextBox();
            this.textBoxChaX = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.textBoxCamY = new System.Windows.Forms.TextBox();
            this.textBoxCamX = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxBG)).BeginInit();
            this.panel2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.panel3.SuspendLayout();
            this.tabControl.SuspendLayout();
            this.tabPageBG.SuspendLayout();
            this.tabPageOB.SuspendLayout();
            this.tabPageItem.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonBG
            // 
            this.buttonBG.Location = new System.Drawing.Point(12, 12);
            this.buttonBG.Name = "buttonBG";
            this.buttonBG.Size = new System.Drawing.Size(112, 23);
            this.buttonBG.TabIndex = 0;
            this.buttonBG.Text = "Background Edit";
            this.buttonBG.UseVisualStyleBackColor = true;
            this.buttonBG.Click += new System.EventHandler(this.buttonBG_Click);
            // 
            // buttonload
            // 
            this.buttonload.Location = new System.Drawing.Point(130, 12);
            this.buttonload.Name = "buttonload";
            this.buttonload.Size = new System.Drawing.Size(113, 23);
            this.buttonload.TabIndex = 1;
            this.buttonload.Text = "Load Background";
            this.buttonload.UseVisualStyleBackColor = true;
            this.buttonload.Click += new System.EventHandler(this.button1_Click);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.pictureBoxBG);
            this.panel1.Location = new System.Drawing.Point(12, 172);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(822, 314);
            this.panel1.TabIndex = 2;
            // 
            // pictureBoxBG
            // 
            this.pictureBoxBG.Location = new System.Drawing.Point(-1, -1);
            this.pictureBoxBG.Name = "pictureBoxBG";
            this.pictureBoxBG.Size = new System.Drawing.Size(814, 308);
            this.pictureBoxBG.TabIndex = 0;
            this.pictureBoxBG.TabStop = false;
            this.pictureBoxBG.Click += new System.EventHandler(this.pictureBoxBG_Click);
            this.pictureBoxBG.MouseLeave += new System.EventHandler(this.pictureBoxBG_MouseLeave);
            this.pictureBoxBG.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBoxBG_MouseMove);
            // 
            // panel2
            // 
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel2.Controls.Add(this.listViewControl);
            this.panel2.Location = new System.Drawing.Point(310, 13);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(507, 62);
            this.panel2.TabIndex = 4;
            // 
            // listViewControl
            // 
            this.listViewControl.Location = new System.Drawing.Point(3, 3);
            this.listViewControl.Name = "listViewControl";
            this.listViewControl.Size = new System.Drawing.Size(487, 54);
            this.listViewControl.TabIndex = 0;
            this.listViewControl.UseCompatibleStateImageBehavior = false;
            this.listViewControl.Click += new System.EventHandler(this.listViewControl_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBoxXHeight);
            this.groupBox1.Controls.Add(this.label14);
            this.groupBox1.Controls.Add(this.comboBoxNameItem);
            this.groupBox1.Controls.Add(this.label13);
            this.groupBox1.Controls.Add(this.comboBoxDir);
            this.groupBox1.Controls.Add(this.textBoxXWidth);
            this.groupBox1.Controls.Add(this.label12);
            this.groupBox1.Controls.Add(this.buttonEdit);
            this.groupBox1.Controls.Add(this.textBoxNameOB);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.textBoxHeightOB);
            this.groupBox1.Controls.Add(this.textBoxWidthOB);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(9, 390);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(298, 186);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Detail : ";
            this.groupBox1.Enter += new System.EventHandler(this.groupBox1_Enter);
            // 
            // textBoxXHeight
            // 
            this.textBoxXHeight.Location = new System.Drawing.Point(189, 71);
            this.textBoxXHeight.Name = "textBoxXHeight";
            this.textBoxXHeight.Size = new System.Drawing.Size(28, 20);
            this.textBoxXHeight.TabIndex = 13;
            this.textBoxXHeight.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxXHeight_KeyPress);
            this.textBoxXHeight.KeyUp += new System.Windows.Forms.KeyEventHandler(this.textBoxXHeight_KeyUp);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(163, 71);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(20, 13);
            this.label14.TabIndex = 12;
            this.label14.Text = " X ";
            // 
            // comboBoxNameItem
            // 
            this.comboBoxNameItem.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxNameItem.FormattingEnabled = true;
            this.comboBoxNameItem.Items.AddRange(new object[] {
            "M",
            "B",
            "L",
            "S",
            "R",
            "F"});
            this.comboBoxNameItem.Location = new System.Drawing.Point(100, 103);
            this.comboBoxNameItem.Name = "comboBoxNameItem";
            this.comboBoxNameItem.Size = new System.Drawing.Size(132, 21);
            this.comboBoxNameItem.TabIndex = 11;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(16, 142);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(58, 13);
            this.label13.TabIndex = 10;
            this.label13.Text = "Direction : ";
            // 
            // comboBoxDir
            // 
            this.comboBoxDir.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxDir.FormattingEnabled = true;
            this.comboBoxDir.Items.AddRange(new object[] {
            "Left-Right",
            "Right-Left",
            "Up-Down",
            "Down-Up"});
            this.comboBoxDir.Location = new System.Drawing.Point(100, 139);
            this.comboBoxDir.Name = "comboBoxDir";
            this.comboBoxDir.Size = new System.Drawing.Size(132, 21);
            this.comboBoxDir.TabIndex = 9;
            // 
            // textBoxXWidth
            // 
            this.textBoxXWidth.Location = new System.Drawing.Point(189, 39);
            this.textBoxXWidth.Name = "textBoxXWidth";
            this.textBoxXWidth.Size = new System.Drawing.Size(28, 20);
            this.textBoxXWidth.TabIndex = 8;
            this.textBoxXWidth.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxXWidth_KeyPress);
            this.textBoxXWidth.KeyUp += new System.Windows.Forms.KeyEventHandler(this.textBoxXWidth_KeyUp);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(163, 39);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(20, 13);
            this.label12.TabIndex = 7;
            this.label12.Text = " X ";
            // 
            // buttonEdit
            // 
            this.buttonEdit.Location = new System.Drawing.Point(238, 36);
            this.buttonEdit.Name = "buttonEdit";
            this.buttonEdit.Size = new System.Drawing.Size(54, 23);
            this.buttonEdit.TabIndex = 6;
            this.buttonEdit.Text = "Edit";
            this.buttonEdit.UseVisualStyleBackColor = true;
            this.buttonEdit.Click += new System.EventHandler(this.buttonEdit_Click);
            // 
            // textBoxNameOB
            // 
            this.textBoxNameOB.Location = new System.Drawing.Point(57, 100);
            this.textBoxNameOB.Name = "textBoxNameOB";
            this.textBoxNameOB.ReadOnly = true;
            this.textBoxNameOB.Size = new System.Drawing.Size(100, 20);
            this.textBoxNameOB.TabIndex = 5;
            this.textBoxNameOB.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(16, 107);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(41, 13);
            this.label7.TabIndex = 4;
            this.label7.Text = "Name :";
            // 
            // textBoxHeightOB
            // 
            this.textBoxHeightOB.Location = new System.Drawing.Point(57, 71);
            this.textBoxHeightOB.Name = "textBoxHeightOB";
            this.textBoxHeightOB.ReadOnly = true;
            this.textBoxHeightOB.Size = new System.Drawing.Size(100, 20);
            this.textBoxHeightOB.TabIndex = 3;
            this.textBoxHeightOB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBoxWidthOB
            // 
            this.textBoxWidthOB.Location = new System.Drawing.Point(57, 36);
            this.textBoxWidthOB.Name = "textBoxWidthOB";
            this.textBoxWidthOB.ReadOnly = true;
            this.textBoxWidthOB.Size = new System.Drawing.Size(100, 20);
            this.textBoxWidthOB.TabIndex = 2;
            this.textBoxWidthOB.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(16, 71);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Height : ";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Width : ";
            // 
            // panel3
            // 
            this.panel3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel3.Controls.Add(this.tabControl);
            this.panel3.Controls.Add(this.groupBox1);
            this.panel3.Location = new System.Drawing.Point(853, 17);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(323, 587);
            this.panel3.TabIndex = 6;
            // 
            // tabControl
            // 
            this.tabControl.Controls.Add(this.tabPageBG);
            this.tabControl.Controls.Add(this.tabPageOB);
            this.tabControl.Controls.Add(this.tabPageItem);
            this.tabControl.Location = new System.Drawing.Point(3, 3);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(319, 381);
            this.tabControl.TabIndex = 3;
            // 
            // tabPageBG
            // 
            this.tabPageBG.Controls.Add(this.listViewBG);
            this.tabPageBG.Location = new System.Drawing.Point(4, 22);
            this.tabPageBG.Name = "tabPageBG";
            this.tabPageBG.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageBG.Size = new System.Drawing.Size(311, 355);
            this.tabPageBG.TabIndex = 0;
            this.tabPageBG.Text = "Background";
            this.tabPageBG.UseVisualStyleBackColor = true;
            // 
            // listViewBG
            // 
            this.listViewBG.Location = new System.Drawing.Point(3, 0);
            this.listViewBG.Name = "listViewBG";
            this.listViewBG.Size = new System.Drawing.Size(305, 352);
            this.listViewBG.TabIndex = 0;
            this.listViewBG.UseCompatibleStateImageBehavior = false;
            this.listViewBG.MouseClick += new System.Windows.Forms.MouseEventHandler(this.listViewBG_MouseClick);
            // 
            // tabPageOB
            // 
            this.tabPageOB.Controls.Add(this.listViewOB);
            this.tabPageOB.Location = new System.Drawing.Point(4, 22);
            this.tabPageOB.Name = "tabPageOB";
            this.tabPageOB.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageOB.Size = new System.Drawing.Size(311, 355);
            this.tabPageOB.TabIndex = 1;
            this.tabPageOB.Text = "Object";
            this.tabPageOB.UseVisualStyleBackColor = true;
            // 
            // listViewOB
            // 
            this.listViewOB.Location = new System.Drawing.Point(0, 3);
            this.listViewOB.Name = "listViewOB";
            this.listViewOB.Size = new System.Drawing.Size(305, 346);
            this.listViewOB.TabIndex = 0;
            this.listViewOB.UseCompatibleStateImageBehavior = false;
            this.listViewOB.MouseClick += new System.Windows.Forms.MouseEventHandler(this.listViewOB_MouseClick);
            // 
            // tabPageItem
            // 
            this.tabPageItem.Controls.Add(this.listViewItem);
            this.tabPageItem.Location = new System.Drawing.Point(4, 22);
            this.tabPageItem.Name = "tabPageItem";
            this.tabPageItem.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageItem.Size = new System.Drawing.Size(311, 355);
            this.tabPageItem.TabIndex = 2;
            this.tabPageItem.Text = "Item";
            this.tabPageItem.UseVisualStyleBackColor = true;
            // 
            // listViewItem
            // 
            this.listViewItem.Location = new System.Drawing.Point(6, 0);
            this.listViewItem.Name = "listViewItem";
            this.listViewItem.Size = new System.Drawing.Size(299, 349);
            this.listViewItem.TabIndex = 0;
            this.listViewItem.UseCompatibleStateImageBehavior = false;
            this.listViewItem.MouseClick += new System.Windows.Forms.MouseEventHandler(this.listViewItem_MouseClick);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.textBoxBGWidth);
            this.groupBox2.Controls.Add(this.textBoxBGHeigth);
            this.groupBox2.Location = new System.Drawing.Point(25, 99);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(679, 56);
            this.groupBox2.TabIndex = 10;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Background Size: ";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(338, 26);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "Height : ";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(20, 26);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 13);
            this.label3.TabIndex = 9;
            this.label3.Text = "Width :";
            // 
            // textBoxBGWidth
            // 
            this.textBoxBGWidth.Location = new System.Drawing.Point(81, 23);
            this.textBoxBGWidth.Name = "textBoxBGWidth";
            this.textBoxBGWidth.ReadOnly = true;
            this.textBoxBGWidth.Size = new System.Drawing.Size(176, 20);
            this.textBoxBGWidth.TabIndex = 7;
            this.textBoxBGWidth.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBoxBGHeigth
            // 
            this.textBoxBGHeigth.Location = new System.Drawing.Point(415, 23);
            this.textBoxBGHeigth.Name = "textBoxBGHeigth";
            this.textBoxBGHeigth.ReadOnly = true;
            this.textBoxBGHeigth.Size = new System.Drawing.Size(176, 20);
            this.textBoxBGHeigth.TabIndex = 8;
            this.textBoxBGHeigth.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.textBoxX);
            this.groupBox3.Controls.Add(this.textBoxY);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Location = new System.Drawing.Point(25, 501);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(338, 48);
            this.groupBox3.TabIndex = 11;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Position : ";
            // 
            // textBoxX
            // 
            this.textBoxX.Location = new System.Drawing.Point(64, 17);
            this.textBoxX.Name = "textBoxX";
            this.textBoxX.ReadOnly = true;
            this.textBoxX.Size = new System.Drawing.Size(100, 20);
            this.textBoxX.TabIndex = 3;
            this.textBoxX.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBoxY
            // 
            this.textBoxY.Location = new System.Drawing.Point(224, 19);
            this.textBoxY.Name = "textBoxY";
            this.textBoxY.ReadOnly = true;
            this.textBoxY.Size = new System.Drawing.Size(100, 20);
            this.textBoxY.TabIndex = 2;
            this.textBoxY.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(192, 21);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(26, 13);
            this.label6.TabIndex = 1;
            this.label6.Text = "Y = ";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(20, 18);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(26, 13);
            this.label5.TabIndex = 0;
            this.label5.Text = "X = ";
            // 
            // imageListOB
            // 
            this.imageListOB.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListOB.ImageStream")));
            this.imageListOB.TransparentColor = System.Drawing.Color.Transparent;
            this.imageListOB.Images.SetKeyName(0, "BlockHouse.png");
            this.imageListOB.Images.SetKeyName(1, "BradgeEagle.png");
            this.imageListOB.Images.SetKeyName(2, "Sniper.png");
            this.imageListOB.Images.SetKeyName(3, "RunMan.png");
            this.imageListOB.Images.SetKeyName(4, "Obstacle.png");
            this.imageListOB.Images.SetKeyName(5, "SniperHide.png");
            this.imageListOB.Images.SetKeyName(6, "Boss1.png");
            this.imageListOB.Images.SetKeyName(7, "BossGun.png");
            this.imageListOB.Images.SetKeyName(8, "Fire.png");
            this.imageListOB.Images.SetKeyName(9, "RockRoll.png");
            this.imageListOB.Images.SetKeyName(10, "RunManFire.png");
            this.imageListOB.Images.SetKeyName(11, "SniperBlock.png");
            this.imageListOB.Images.SetKeyName(12, "SniperWater.png");
            this.imageListOB.Images.SetKeyName(13, "Boom.png");
            this.imageListOB.Images.SetKeyName(14, "Tank.png");
            this.imageListOB.Images.SetKeyName(15, "Boss2.png");
            this.imageListOB.Images.SetKeyName(16, "Boss3.png");
            // 
            // imageListBG
            // 
            this.imageListBG.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListBG.ImageStream")));
            this.imageListBG.TransparentColor = System.Drawing.Color.Transparent;
            this.imageListBG.Images.SetKeyName(0, "Ground.png");
            this.imageListBG.Images.SetKeyName(1, "Water.png");
            this.imageListBG.Images.SetKeyName(2, "Bridge.png");
            this.imageListBG.Images.SetKeyName(3, "WaterEffect1.png");
            this.imageListBG.Images.SetKeyName(4, "WaterEffect2.png");
            this.imageListBG.Images.SetKeyName(5, "WaterEffect3.png");
            this.imageListBG.Images.SetKeyName(6, "Star.png");
            this.imageListBG.Images.SetKeyName(7, "rock_fly.png");
            this.imageListBG.Images.SetKeyName(8, "Ground_Electon.png");
            this.imageListBG.Images.SetKeyName(9, "WaterFall.png");
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(68, 571);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(75, 23);
            this.buttonSave.TabIndex = 12;
            this.buttonSave.Text = "Save File";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialog1_FileOk);
            // 
            // imageListControl
            // 
            this.imageListControl.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListControl.ImageStream")));
            this.imageListControl.TransparentColor = System.Drawing.Color.Transparent;
            this.imageListControl.Images.SetKeyName(0, "Cancel.png");
            this.imageListControl.Images.SetKeyName(1, "Remove.png");
            // 
            // buttonRest
            // 
            this.buttonRest.Location = new System.Drawing.Point(89, 52);
            this.buttonRest.Name = "buttonRest";
            this.buttonRest.Size = new System.Drawing.Size(75, 23);
            this.buttonRest.TabIndex = 13;
            this.buttonRest.Text = "Reset";
            this.buttonRest.UseVisualStyleBackColor = true;
            this.buttonRest.Click += new System.EventHandler(this.buttonRest_Click);
            // 
            // imageListItem
            // 
            this.imageListItem.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListItem.ImageStream")));
            this.imageListItem.TransparentColor = System.Drawing.Color.Transparent;
            this.imageListItem.Images.SetKeyName(0, "ItemB.png");
            this.imageListItem.Images.SetKeyName(1, "ItemF.png");
            this.imageListItem.Images.SetKeyName(2, "ItemL.png");
            this.imageListItem.Images.SetKeyName(3, "ItemM.png");
            this.imageListItem.Images.SetKeyName(4, "ItemR.png");
            this.imageListItem.Images.SetKeyName(5, "ItemS.png");
            this.imageListItem.Images.SetKeyName(6, "ItemX.png");
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.textBoxChaY);
            this.groupBox4.Controls.Add(this.textBoxChaX);
            this.groupBox4.Controls.Add(this.label11);
            this.groupBox4.Controls.Add(this.label10);
            this.groupBox4.Controls.Add(this.textBoxCamY);
            this.groupBox4.Controls.Add(this.textBoxCamX);
            this.groupBox4.Controls.Add(this.label9);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Location = new System.Drawing.Point(392, 501);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(434, 100);
            this.groupBox4.TabIndex = 15;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Default: ";
            // 
            // textBoxChaY
            // 
            this.textBoxChaY.Location = new System.Drawing.Point(292, 67);
            this.textBoxChaY.Name = "textBoxChaY";
            this.textBoxChaY.Size = new System.Drawing.Size(100, 20);
            this.textBoxChaY.TabIndex = 7;
            // 
            // textBoxChaX
            // 
            this.textBoxChaX.Location = new System.Drawing.Point(142, 70);
            this.textBoxChaX.Name = "textBoxChaX";
            this.textBoxChaX.Size = new System.Drawing.Size(100, 20);
            this.textBoxChaX.TabIndex = 6;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(259, 16);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(26, 13);
            this.label11.TabIndex = 5;
            this.label11.Text = "Y = ";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(104, 16);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(23, 13);
            this.label10.TabIndex = 4;
            this.label10.Text = "X =";
            // 
            // textBoxCamY
            // 
            this.textBoxCamY.Location = new System.Drawing.Point(292, 32);
            this.textBoxCamY.Name = "textBoxCamY";
            this.textBoxCamY.Size = new System.Drawing.Size(100, 20);
            this.textBoxCamY.TabIndex = 3;
            // 
            // textBoxCamX
            // 
            this.textBoxCamX.Location = new System.Drawing.Point(142, 35);
            this.textBoxCamX.Name = "textBoxCamX";
            this.textBoxCamX.Size = new System.Drawing.Size(100, 20);
            this.textBoxCamX.TabIndex = 2;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(33, 70);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(62, 13);
            this.label9.TabIndex = 1;
            this.label9.Text = "Character : ";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(43, 35);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(52, 13);
            this.label8.TabIndex = 0;
            this.label8.Text = "Camera : ";
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(721, 138);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(109, 17);
            this.checkBox1.TabIndex = 16;
            this.checkBox1.Text = "Hide Background";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // MapEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1201, 616);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.buttonRest);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.buttonload);
            this.Controls.Add(this.buttonBG);
            this.Name = "MapEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Map Editor";
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxBG)).EndInit();
            this.panel2.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.tabControl.ResumeLayout(false);
            this.tabPageBG.ResumeLayout(false);
            this.tabPageOB.ResumeLayout(false);
            this.tabPageItem.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonBG;
        private System.Windows.Forms.Button buttonload;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PictureBox pictureBoxBG;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBoxHeightOB;
        private System.Windows.Forms.TextBox textBoxWidthOB;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxBGWidth;
        private System.Windows.Forms.TextBox textBoxBGHeigth;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox textBoxX;
        private System.Windows.Forms.TextBox textBoxY;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ImageList imageListOB;
        private System.Windows.Forms.ImageList imageListBG;
        private System.Windows.Forms.TextBox textBoxNameOB;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ListView listViewControl;
        private System.Windows.Forms.ImageList imageListControl;
        private System.Windows.Forms.Button buttonRest;
        private System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.TabPage tabPageBG;
        private System.Windows.Forms.TabPage tabPageOB;
        private System.Windows.Forms.ListView listViewOB;
        private System.Windows.Forms.TabPage tabPageItem;
        private System.Windows.Forms.ImageList imageListItem;
        private System.Windows.Forms.ListView listViewItem;
        private System.Windows.Forms.ListView listViewBG;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.TextBox textBoxChaY;
        private System.Windows.Forms.TextBox textBoxChaX;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxCamY;
        private System.Windows.Forms.TextBox textBoxCamX;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBoxXWidth;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button buttonEdit;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.ComboBox comboBoxDir;
        private System.Windows.Forms.ComboBox comboBoxNameItem;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.TextBox textBoxXHeight;
        private System.Windows.Forms.Label label14;
    }
}

