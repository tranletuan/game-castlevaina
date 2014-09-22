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
            Init();
        }


        private Bitmap background; //Chứa hình nền của map
        private Bitmap back_buffer; //Vẽ các đối tượng
        private Graphics pen;
        private float zoom_rate = 1f;
        private Dictionary<string, Image> resources;
        private ImageList current_type_list;
        private List<string> current_key_list;
        private ObjectDraw current_object_draw;
        private Point current_point;
        private Point last_point;
        private bool is_change;
        private List<GameObject> objects;


        #region METHOD

        public void Init()
        {
            objects = new List<GameObject>();
        }

        public float Zoom
        {
            get { return zoom_rate >= 1 ? zoom_rate : 1; }
            set { zoom_rate = value >= 1 ? value : 1; }
        }

        private Image GetImage(string key)
        {
            return resources[key];
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

        private void RenderObject(Point pos, Image img)
        {

        }

        private void ChangeCursor(Image img = null)
        {
            //Thay đổi con trỏ chuột
            if (current_object_draw.Object == null) return;

            if (img != null)
            {
                //Hình ảnh con trỏn chuột là hình ảnh đối tượng hiện thời
                Bitmap cur_img = new Bitmap(img, new Size((int)(img.Width * Zoom), (int)(img.Height * Zoom)));
                Cursor cur = new Cursor(cur_img.GetHicon());
                pbMap.Cursor = cur;
            }
            else
            {
                pbMap.Cursor = Cursors.Default;
            }
        }

        private bool CheckIntersect(GameObject go)
        {
            foreach (GameObject o in objects)
            {
                Rectangle rect = Rectangle.Intersect(o.BOUNDS, go.BOUNDS);

                if (rect.Width > 0 && rect.Height > 0)
                {
                    return false; //Có va chạm
                }
            }

            return true; //Không va chạm
        }

        private bool InsertObject(GameObject go)
        {
            objects.Add(go);

            return true;
        }

        /// <summary>
        /// Vẽ tất cả đối tượng lên map
        /// </summary>
        private void DrawAllObject()
        {

        }

        private void DrawCurrentObject()
        {
            if (current_object_draw.Object != null && current_object_draw.Image != null)
            {
                float width = current_object_draw.Bounds.Width * Zoom;
                float height = current_object_draw.Bounds.Height * Zoom;
                pen.DrawImage(
                    current_object_draw.Image,
                    current_object_draw.Position.X - width / 2,
                    current_object_draw.Position.Y - height / 2,
                    current_object_draw.Bounds.Width * Zoom,
                    current_object_draw.Bounds.Height * Zoom);

                pbMap.Image = back_buffer;
            }
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
                trbZoom.Enabled = true;
            }
        }

        private void trbZoom_Scroll(object sender, EventArgs e)
        {
            zoom_rate = 1 + (float)trbZoom.Value * 0.5f;
            back_buffer = new Bitmap(background, new Size((int)(background.Width * Zoom), (int)(background.Height * Zoom)));
            pen = Graphics.FromImage(back_buffer);
            pbMap.Image = back_buffer;
            DrawAllObject();
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
                            string key = big_type_name + "_" + file_name.Split(new char[] { '.' }, StringSplitOptions.RemoveEmptyEntries)[0];
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
            if (lvType.SelectedItems.Count == 0)
            {
                current_object_draw = new ObjectDraw();
                return;
            }

            string type = lvType.SelectedItems[0].Text;
            string key = cmbBigType.Text + "_" + type;

            current_object_draw = new ObjectDraw(type, GetImage(key));
        }

        private void pbMap_MouseEnter(object sender, EventArgs e)
        {
            ChangeCursor(current_object_draw.Image);
        }

        private void pbMap_MouseMove(object sender, MouseEventArgs e)
        {
            if (current_object_draw.Object != null && current_object_draw.Image != null && is_change)
            {
                current_point = new Point(e.X, e.Y);
                Point vector = new Point(current_point.X - last_point.X, current_point.Y - last_point.Y);
                int distance = (int)Math.Sqrt(vector.X * vector.X + vector.Y * vector.Y);

                if (e.Button == MouseButtons.Left && distance >= Global.DISTANCE_MOVE)
                {
                    //Vẽ lại tất cả các đối tượng trước đó
                    DrawAllObject();

                    //Gán lại last point
                    int stepX = vector.X >= vector.Y ? trbStep.Value : 0;
                    int stepY = vector.X >= vector.Y ? 0 : trbStep.Value;

                    last_point = new Point(last_point.X + stepX, last_point.Y + stepY);
                    current_point = last_point;

                    //Vẽ đối tượng tạm trên màn hình
                    RenderObject(new Point(), current_object_draw.Image);
                }
            }
        }

        private void pbMap_MouseUp(object sender, MouseEventArgs e)
        {
            if (current_object_draw.Object != null && current_object_draw.Image != null)
            {
                if (e.Button == MouseButtons.Left)
                {
                    last_point = Point.Empty;
                    current_point = Point.Empty;
                    is_change = false;
                    ChangeCursor(current_object_draw.Image);
                }
            }
        }

        private void pbMap_MouseDown(object sender, MouseEventArgs e)
        {

            if (e.Button == MouseButtons.Left)
            {
                last_point = new Point(e.X, e.Y);
                current_object_draw.Position = last_point;

                Point real_point = new Point((int)(last_point.X / Zoom), (int)(last_point.Y / Zoom));
                GameObject go = new GameObject(current_object_draw.Object, real_point);

                if (CheckIntersect(go))
                {
                    DrawCurrentObject(); //Vẽ đối tượng lên màn hình
                    InsertObject(go); //Lưu đối tượng vào danh sách
                    ChangeCursor(null); 
                }
                else
                {
                    //Hiển thị icon đỏ khi có va chạm với những đối tượng được vẽ trước
                    Bitmap bmp = new Bitmap(current_object_draw.Image);
                    Graphics gr = Graphics.FromImage(bmp);
                    gr.FillRectangle(new SolidBrush(Color.Red),new Rectangle(0,0, bmp.Width, bmp.Height));
                    ChangeCursor(bmp);
                }
            }
        }
    }
}

