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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private Bitmap background; //Chứa hình nền của map
        private Bitmap back_buffer; //Vẽ các đối tượng
        private Graphics pen;
        private float zoom_rate = 1f;
        private Dictionary<string, Image> resources;
        private ImageList current_type_list;
        private List<string> current_key_list;
        private GameObject current_object;

        #region METHOD

        public float Zoom
        {
            get { return zoom_rate >= 1 ? zoom_rate : 1; }
            set { zoom_rate = value >= 1 ? value : 1; }
        }

        private Image GetImage(string key)
        {
            return resources[type];
        }

        private void SetImageList(string big_type)
        {
            current_key_list = new List<string>();
            current_type_list = new ImageList();

            for (int i = 0; i < resources.Count; i++)
            {
                string[] texture_name = resources.ElementAt(i).Key.Split(new char[] { '_' }, StringSplitOptions.RemoveEmptyEntries);
                if (texture_name[0] == big_type)
                {
                    string key = resources.ElementAt(i).Key;
                    Image value = resources.ElementAt(i).Value;

                    current_type_list.Images.Add(key, value);
                    current_key_list.Add(key);
                }
            }
        }

        /// <summary>
        /// Vẽ tất cả đối tượng lên map
        /// </summary>
        private void RenderAllObject()
        {
 
        }

        #endregion

        private void loadMapToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Title = "Load Background";
            ofd.Filter = "Image Files |*.BMP;*.DIB;*.RLE;*.JPG;*.JPEG;*.JPE;*.JFIF;*.GIF;*.TIF;*.TIFF;*.PNG";
            ofd.FilterIndex = 1;
            ofd.Multiselect = false;

            if (ofd.ShowDialog() == DialogResult.OK)
            {
                background = new Bitmap(ofd.FileName);
                back_buffer = new Bitmap(background, new Size((int)(background.Width * Zoom), (int)(background.Height * Zoom)));
                pen = Graphics.FromImage(back_buffer);
                pbMap.Image = back_buffer;
            }
        }

        private void trbZoom_Scroll(object sender, EventArgs e)
        {
            try
            {
                zoom_rate = 1 + (float)trbZoom.Value * 0.5f;
                back_buffer = new Bitmap(background, new Size((int)(background.Width * Zoom), (int)(background.Height * Zoom)));
                pen = Graphics.FromImage(back_buffer);
                pbMap.Image = back_buffer;
                RenderAllObject();
            }
            catch { }
        }

        private void pbMap_Resize(object sender, EventArgs e)
        {
            pnlMap.AutoScrollPosition = new Point(0, 0);

            int pic_y = pnlMap.Height / 2 - back_buffer.Height / 2;
            int pic_x = pnlMap.Width / 2 - back_buffer.Width / 2;

            pic_x = pic_x >= 0 ? pic_x : 0;
            pic_y = pic_y >= 0 ? pic_y : 0;

            pbMap.Location = new Point(pic_x, pic_y);
        }

        private void loadResoucesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            resources = new Dictionary<string, Image>();
            List<string> big_types = new List<string>();
            FolderBrowserDialog fbd = new FolderBrowserDialog();

            //Mở folder chứa các texture
            if (fbd.ShowDialog() == DialogResult.OK)
            {
                string parent_path = fbd.SelectedPath;
                string[] folder_root = Directory.GetDirectories(parent_path);
               
                //Duyệt các folder con
                foreach (string node in folder_root)
                {
                    //Lấy danh sách các loại chung
                    string big_type_name = node.Substring(parent_path.Length + 1);
                    big_types.Add(big_type_name); //Danh sách các type chung trên cmb

                    string[] files = Directory.GetFiles(node);

                    //Đọc tất cả các file ảnh 
                    foreach (string file in files)
                    {
                        try
                        {
                            Image img = Image.FromFile(file);
                            string file_name = file.Substring(node.Length + 1); //Lấy tên file texture
                            string key = big_type_name + "_" + file_name.Split(new char[]{'.'},StringSplitOptions.RemoveEmptyEntries)[0];
                            resources.Add(key, img);
                        }
                        catch { }
                    }
                }

                try 
                {
                    //Đưa các danh sách type chung đọc được vào cmb
                    cmbBigType.DataSource = big_types;
                    cmbBigType.SelectedIndex = 0;
                }
                catch { }
                
            }

        }

        private void cmbBigType_SelectedValueChanged(object sender, EventArgs e)
        {
            lvType.Clear();
            SetImageList(cmbBigType.Text);    
            current_type_list.ImageSize = new Size(48, 48);
            lvType.LargeImageList = current_type_list;

            for (int i = 0; i < current_key_list.Count; i++)
            {
                string name = current_key_list[i].Split(new char[] { '_' })[1];
                ListViewItem lvi = new ListViewItem(name, current_key_list[i]);
                lvType.Items.Add(lvi);
            }


        }

        private void lvType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(lvType.SelectedItems.Count  == 0) return;

            string type = lvType.SelectedItems[0].Text;
            string key = cmbBigType.Text + "_" + type;
            
            Image current_image = GetImage(key);
            MessageBox.Show(current_image.ToString());
            //current_object = new GameObject(type)
        }

    }
}
