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
        private List<Object> list_view_objects;
        private List<Object> map_objects;
        private Object current_object;
        private Point current_position;
        private Bitmap bitmap;
        private Graphics graphics;
        private int width;
        private int height;
        private float zoom;

        #region METHODS

        private void Draw(Bitmap bmp, Point pos)
        {
            graphics.DrawImageUnscaled(bmp, pos);
            pbMap.Image = bitmap;
        }

        private bool CheckCollision(List<Object> map_objects, Object o)
        {
            foreach (Object ob in map_objects)
            {
                Rectangle rect = Rectangle.Intersect(ob.Bounds, o.Bounds);
                if(rect.Width > 1 && rect.Height > 1)
                {
                    return true;
                }
            }
            return false;
        }

        #endregion

        private void Form1_Load(object sender, EventArgs e)
        {
            resources_manager = new ResourcesManager();
            list_view_objects = new List<Object>();
            map_objects = new List<Object>();
            Zoom = 1;
        }

        private void cmbType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbType.SelectedIndex != -1)
            {
                lvObject.Clear();

                //Đưa các đối tượng vào list view
                ImageList img_list = resources_manager.ListResources[cmbType.SelectedIndex];
                list_view_objects = resources_manager.ListObjects[cmbType.SelectedIndex];
                img_list.ImageSize = new System.Drawing.Size(48, 48);

                lvObject.SmallImageList = img_list;
                for (int i = 0; i < list_view_objects.Count; i++)
                {
                    ListViewItem lvi = new ListViewItem(list_view_objects[i].Type, list_view_objects[i].Type);
                    lvObject.Items.Add(lvi);
                }
            }
        }

        private void loadResourcesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            fbd.Description = "Open Folder Title";
            fbd.ShowNewFolderButton = false;
            
            if (fbd.ShowDialog() == DialogResult.OK)
            {
                string folder_name = fbd.SelectedPath;
                resources_manager.LoadAllResources(folder_name);
                cmbType.DataSource = resources_manager.ListGlobalType;
            }

            newMapToolStripMenuItem_Click(sender, e);
            
        }

        private void newMapToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bitmap = new Bitmap(panel1.Width, panel1.Height);
            width = bitmap.Width;
            height = bitmap.Height;
            graphics = Graphics.FromImage(bitmap);
            graphics.Clear(Color.AliceBlue);
            pbMap.Image = bitmap;
        }

        private void normalToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void lvObject_SelectedIndexChanged(object sender, EventArgs e)
        {
            var indeces = lvObject.SelectedIndices;
            if (indeces.Count > 0)
            {
                int index = indeces[0];
                string key = lvObject.Items[index].ImageKey;
                current_object = list_view_objects[index];
            }
            else
            {
                current_object = null;
            }
        }

        private void pbMap_MouseEnter(object sender, EventArgs e)
        {
            if (current_object != null)
            {
                pbMap.Cursor = new Cursor(current_object.Image.GetHicon());
            }
        }

        private void pbMap_MouseMove(object sender, MouseEventArgs e)
        {
            if (current_object != null)
            {
                current_position = new Point(e.X - current_object.Image.Width / 2, e.Y - current_object.Image.Height / 2);
            }
        }

        private void pbMap_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left && current_object != null)
            {
                //Chuyển con trỏ vào đúng tọa độ ô ma trận
                Point matrix_pos = new Point(current_position.X / current_object.Bounds.Width * current_object.Bounds.Width,
                    current_position.Y / current_object.Bounds.Height * current_object.Bounds.Height);
                current_position = matrix_pos;
                
                Object o = new Object(current_object, current_position);
                //Kiểm tra va chạm với những đối tượng đã vẽ
                //Tránh vẽ chồng các đối tượng lên nhau
                if (CheckCollision(map_objects, o) == false)
                {
                    Draw(current_object.Image, current_position);
                    map_objects.Add(o);
                }
            }
        }

        public float Zoom
        {
            get { return zoom >= 1 ? zoom : 1; }
            set { zoom = value >= 1 ? value : 1; }
        }
    }
}
