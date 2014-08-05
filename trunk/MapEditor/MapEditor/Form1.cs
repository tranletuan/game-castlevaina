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

        private ResourcesManager resources_manager;
        private List<Object> current_list_objects;
        #region METHODS

        #endregion

        private void Form1_Load(object sender, EventArgs e)
        {
            resources_manager = new ResourcesManager(@"H:\Users\Tran\Desktop\Map 1\Map 1_0");
            current_list_objects = new List<Object>();
        }

        private void cmbType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbType.SelectedIndex != -1)
            {
                lvObject.Clear();

                //Đưa các đối tượng vào list view
                ImageList img_list = resources_manager.list_resources[cmbType.SelectedIndex];
                current_list_objects = resources_manager.list_objects[cmbType.SelectedIndex];

                img_list.ImageSize = new Size(32, 32);
                lvObject.SmallImageList = img_list;
                for (int i = 0; i < current_list_objects.Count; i++)
                {
                    ListViewItem lvi = new ListViewItem(current_list_objects[i].Type, current_list_objects[i].Type);
                    lvObject.Items.Add(lvi);
                }
            }
        }

        private void loadResourcesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            resources_manager.LoadAllResources();
            cmbType.DataSource = resources_manager.list_global_type;
        }
    }
}
