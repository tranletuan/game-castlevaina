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
        private List<GameObject> objects;
        private bool can_change; 

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

        private int GetIndexByPosition(Point pos)
        {
            int index = -1;
            Point p = new Point((int)(pos.X / Zoom), (int)(pos.Y / Zoom));

            foreach (GameObject o in objects)
            {
                if (o.BOUNDS.Contains(p))
                {
                    index = objects.IndexOf(o);
                    break;
                }
            }

            return index;
        }

        /// <summary>
        /// Vẽ tất cả đối tượng lên map
        /// </summary>
        private void DrawAllObject()
        {
            try
            {
                back_buffer = new Bitmap(background, new Size((int)(background.Width * Zoom), (int)(background.Height * Zoom)));
                pen = Graphics.FromImage(back_buffer);
                pbMap.Image = back_buffer;
            }
            catch
            { }

            foreach (GameObject o in objects)
            {
                DrawObject(o);
            }
        }

        private void DrawObject(GameObject o)
        {
            if (o != null)
            {
                float width = o.BOUNDS.Width * Zoom;
                float height = o.BOUNDS.Height * Zoom;
                //Point draw_point = new Point((int)((o.POSITION.X * Zoom - width / 2)), (int)(o.POSITION.Y * Zoom - height / 2));
                pen.DrawImage(
                    GetImage(o.TYPE),
                    o.POSITION.X * Zoom,
                    o.POSITION.Y * Zoom,
                    o.BOUNDS.Width * Zoom,
                    o.BOUNDS.Height * Zoom);

                pbMap.Image = back_buffer;
            }
        }

        private void ChangePositionObject(int index, int stepX, int stepY)
        {
            Point old_pos = objects[index].POSITION;
            objects[index].POSITION = new Point(old_pos.X + stepX, old_pos.Y + stepY);
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
                DrawAllObject();
            }
        }

        private void trbZoom_Scroll(object sender, EventArgs e)
        {
            zoom_rate = 1 + (float)trbZoom.Value * 0.5f;
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

            current_object_draw = new ObjectDraw(key, GetImage(key));
        }

        private void pbMap_MouseEnter(object sender, EventArgs e)
        {
            ChangeCursor(current_object_draw.Image);
        }

        private void pbMap_MouseMove(object sender, MouseEventArgs e)
        {
            if (current_object_draw.Object == null && e.Button == MouseButtons.Left && can_change)
            {
                current_point = new Point(e.X, e.Y);
                Point vector = new Point(current_point.X - last_point.X, current_point.Y - last_point.Y);
                int distance = (int)Math.Sqrt(vector.X * vector.X + vector.Y * vector.Y);

                if (distance >= Global.DISTANCE_MOVE)
                {
                    //Lấy chỉ số vị trí của đối tượng đã vẽ
                    int redraw_index = GetIndexByPosition(last_point);

                    if (redraw_index >= 0)
                    {
                        int signX = vector.X < 0? -1 : 1;
                        int signY = vector.Y < 0? -1 : 1;
                        int stepX = Math.Abs(vector.X) >= Math.Abs(vector.Y) ? signX * trbStep.Value : 0;
                        int stepY = stepX == 0 ? signY * trbStep.Value : 0;

                        ChangePositionObject(redraw_index, stepX, stepY);
                        DrawAllObject();
                        can_change = false;
                    }
                }
            }
        }

        private void pbMap_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                last_point = Point.Empty;
                current_point = Point.Empty;
                ChangeCursor(current_object_draw.Image);
                can_change = false;
            }
        }

        private void pbMap_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                last_point = new Point(e.X, e.Y);

                if (current_object_draw.Object != null)
                {
                    current_object_draw.Position = last_point;

                    Point real_point = new Point((int)(last_point.X / Zoom - current_object_draw.Image.Width / 2),
                        (int)(last_point.Y / Zoom - current_object_draw.Image.Height / 2));
                    GameObject go = new GameObject(current_object_draw.Object, real_point);

                    if (CheckIntersect(go))
                    {
                        DrawObject(go); //Vẽ đối tượng lên màn hình
                        InsertObject(go); //Lưu đối tượng vào danh sách
                        ChangeCursor(null);
                    }
                    else
                    {
                        //Hiển thị icon đỏ khi có va chạm với những đối tượng được vẽ trước
                        Bitmap bmp = new Bitmap(current_object_draw.Image);
                        Graphics gr = Graphics.FromImage(bmp);
                        gr.FillRectangle(new SolidBrush(Color.Red), new Rectangle(0, 0, bmp.Width, bmp.Height));
                        ChangeCursor(bmp);
                    }
                }
                else
                {
                    can_change = true;
                }
                
            }
        }
    }
}

