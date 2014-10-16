using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            txtBackgroundPath.Text = Global.SETTING.BackgroundPath;
            txtResourcesPath.Text = Global.SETTING.ResourcesPath;
            cbAutoLoad.Checked = Global.SETTING.AutoLoad;
        }

        private void btnOpenBackgroundPath_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Title = "Background Path";
            ofd.Filter = "Image Files |*.BMP;*.DIB;*.RLE;*.JPG;*.JPEG;*.JPE;*.JFIF;*.GIF;*.TIF;*.TIFF;*.PNG";
            ofd.FilterIndex = 1;
            ofd.Multiselect = false;

            if (ofd.ShowDialog() == DialogResult.OK)
            {
                
                txtBackgroundPath.Text = ofd.FileName;
            }
        }

        private void btnOpenResourcesPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();

            //Mở folder chứa các texture
            if (fbd.ShowDialog() == DialogResult.OK)
            {
                
                txtResourcesPath.Text = fbd.SelectedPath;
            }
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            Global.SETTING = new Setting(txtBackgroundPath.Text, txtResourcesPath.Text, cbAutoLoad.Checked);
            using (StreamWriter sw = new StreamWriter(Global.SETTING_PATH, false))
            {
                sw.WriteLine(Global.SETTING.BackgroundPath);
                sw.WriteLine(Global.SETTING.ResourcesPath);
                sw.WriteLine(Global.SETTING.AutoLoad.ToString());
            }

            this.Dispose();
        }


    }
}
