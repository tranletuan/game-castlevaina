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
        private int object_id;
        private int max_width;
        private Bitmap background;
        

        #region METHODS

        private void Draw(Bitmap bmp, Point pos)
        {
            int x = (int)(pos.X * Zoom);
            int y = (int)(pos.Y * Zoom);
            int width = (int)(bmp.Width * Zoom);
            int height = (int)(bmp.Height * Zoom);
            graphics.DrawImage(bmp, new Rectangle(x, y, width, height));
            pbMap.Image = bitmap;
        }

        private void ReDraw(List<Object> map_objects, ResourcesManager rm)
        {
            foreach (Object o in map_objects)
            {
                Bitmap bm = new Bitmap(rm.GetObjectBy(o.Type, o.GlobalType).Image);
                Draw(bm, o.Position);
            }
        }

        private void Remove(ref List<Object> map_objects, Point p)
        {
            foreach (Object o in map_objects)
            {
                if (o.Bounds.Contains(p))
                {
                    map_objects.Remove(o);
                    break;
                }
            }
        }

        private bool CheckCollision(List<Object> map_objects, Object o)
        {
            foreach (Object ob in map_objects)
            {
                Rectangle rect = Rectangle.Intersect(ob.Bounds, o.Bounds);
                if (rect.Width > 1 && rect.Height > 1)
                {
                    return true;
                }
            }
            return false;
        }

        #endregion

        #region EVENTS

        private void Form1_Load(object sender, EventArgs e)
        {
            resources_manager = new ResourcesManager();
            list_view_objects = new List<Object>();
            map_objects = new List<Object>();
            resources_manager.LoadAllResources(@"H:\Users\Tran\Desktop\Map 1\Map 1_0");
            cmbType.DataSource = resources_manager.ListGlobalType;
            Zoom = 1.25f;
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

        private void newMapToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Tạo map mới sử dụng hình nền sẳn hoặc tạo map tự do
            DialogResult dr = MessageBox.Show("Bạn có muốn sử dụng image làm background?", "Thông báo", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (dr == DialogResult.No)
            {
                bitmap = new Bitmap(panel1.Width, panel1.Height);
                grbNonBackground.Visible = false;
                graphics = Graphics.FromImage(bitmap);
                graphics.Clear(Color.AliceBlue);
                grbNonBackground.Visible = true;
            }
            else
            {
                OpenFileDialog ofd = new OpenFileDialog();
                ofd.Title = "Background Image";
                ofd.Multiselect = false;
                ofd.Filter = "Image Files |*.BMP;*.DIB;*.RLE;*.JPG;*.JPEG;*.JPE;*.JFIF;*.GIF;*.TIF;*.TIFF;*.PNG";
                ofd.FilterIndex = 1;
                grbNonBackground.Visible = false;

                if (ofd.ShowDialog() == DialogResult.OK)
                {
                    background = new Bitmap(ofd.FileName);
                }

                bitmap = new Bitmap(background, new Size((int)(background.Width * Zoom), (int)(background.Height * Zoom)));
                graphics = Graphics.FromImage(bitmap);
            }

            width = bitmap.Width;
            height = bitmap.Height;
            pbMap.Image = bitmap;
            object_id = 0;
            map_objects = new List<Object>();
            max_width = height;
        }

        private void normalToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Rectangle quadtree_bounds = new Rectangle(0, 0, max_width, max_width);
            QuadTree quadtree = new QuadTree(map_objects, quadtree_bounds);
            quadtree.SaveQuaddTreeTo(@"H:\Users\Tran\Desktop\Map QuadTree\quadtree.txt", @"H:\Users\Tran\Desktop\Map QuadTree\object.txt");
        }

        private void lvObject_SelectedIndexChanged(object sender, EventArgs e)
        {
            var indeces = lvObject.SelectedIndices;
            if (indeces.Count > 0)
            {
                int index = indeces[0];
                //string key = lvObject.Items[index].ImageKey;
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
                Bitmap img = new Bitmap(current_object.Image,
                    new Size((int)(current_object.Image.Width * Zoom), (int)(current_object.Image.Height * Zoom)));
                pbMap.Cursor = new Cursor(img.GetHicon());
            }
        }

        private void pbMap_MouseMove(object sender, MouseEventArgs e)
        {
            if (current_object != null)
            {
                current_position = new Point(e.X - current_object.Image.Width / 2, e.Y - current_object.Image.Height / 2);
            }

            //Vẽ liên tục
            if (e.Button == MouseButtons.Left)
            {
                pbMap_MouseDown(sender, e);
            }
        }

        private void pbMap_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                if (current_object != null)
                {
                    //Chuyển con trỏ vào đúng tọa độ ô ma trận
                    int x = (int)(current_position.X / Zoom) / current_object.Bounds.Width * current_object.Bounds.Width;
                    int y = (int)(current_position.Y / Zoom) / current_object.Bounds.Height * current_object.Bounds.Height;

                    current_position = new Point(x, y);

                    Object o = new Object(current_object, current_position, object_id);
                    //Kiểm tra va chạm với những đối tượng đã vẽ
                    //Tránh vẽ chồng các đối tượng lên nhau
                    if (CheckCollision(map_objects, o) == false)
                    {
                        Draw(current_object.Image, current_position);
                        map_objects.Add(o);
                        object_id++;

                        max_width = max_width < o.Position.X + o.Bounds.Width ? o.Position.X + o.Bounds.Width : max_width;
                        max_width = max_width < o.Position.Y + o.Bounds.Height ? o.Position.Y + o.Bounds.Height : max_width;
                    }
                }
            }

            if (e.Button == MouseButtons.Right)
            {
                //Chuyển con trỏ vào đúng tọa độ ô ma trận
                int x = (int)(current_position.X / Zoom) / current_object.Bounds.Width * current_object.Bounds.Width;
                int y = (int)(current_position.Y / Zoom) / current_object.Bounds.Height * current_object.Bounds.Height;

                current_position = new Point(x + 1, y + 1);

                bitmap = new Bitmap(background, new Size((int)(background.Width * Zoom), (int)(background.Height * Zoom)));
                graphics = Graphics.FromImage(bitmap);
                pbMap.Image = bitmap;
                Remove(ref map_objects, current_position);
                ReDraw(map_objects, resources_manager);
            }
        }

        #endregion

        #region PROPERTIES

        public float Zoom
        {
            get { return zoom >= 1 ? zoom : 1; }
            set { zoom = value >= 1 ? value : 1; }
        }

        #endregion
    }
}
