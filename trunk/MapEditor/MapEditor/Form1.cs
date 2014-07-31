using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private List<Image> all_image;
        private ObjectManager object_manager;

        #region METHODS

        private void ListViewLoadObject(int type)
        {
                      
        }

        #endregion

        
        private void Form1_Load(object sender, EventArgs e)
        {
            cmbType.SelectedIndex = 0;
            object_manager = new ObjectManager(@"H:\Users\Tran\Desktop\em iu");
            object_manager.LoadAllObject();
        }

        private void cmbType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbType.SelectedIndex != -1)
            {
                //Set object to list view
                ListViewLoadObject(cmbType.SelectedIndex);
            }
        }
    }
}
