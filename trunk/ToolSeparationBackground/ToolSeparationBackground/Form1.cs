using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ToolSeparationBackground
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            
        }

        #region VARIABLES

        Bitmap _picture;
        Bitmap _result;
        MapWriter _wMap;
        String _fileMapText;
        String _folderTexture;
        int _width, _height;
        List<Bitmap> _list_texture;
        List<String> _map;

        #endregion

        #region METHODS
        /// <summary>
        /// Chuyển ảnh gốc thành ảnh 8bpp (8 bit depth)
        /// </summary>
        /// <param name="img">Ảnh gốc</param>
        /// <returns></returns>
        private Bitmap ConvertTo8bpp(Image img)
        {
            var bmp = new Bitmap(img.Width, img.Height, System.Drawing.Imaging.PixelFormat.Format16bppRgb555);
            using (var gr = Graphics.FromImage(bmp))
                gr.DrawImage(img, new Rectangle(0, 0, img.Width, img.Height));
            return bmp;
        }

        /// <summary>
        /// Tải ảnh lên màn hình
        /// </summary>
        /// <param name="fullPath">Đường dẫn đầy đủ của ảnh cần tải</param>
        private Bitmap loadPicture(string fullPath)
        {
            //Tải ảnh
            Bitmap img = new Bitmap(fullPath);
            return img;     
        }

        /// <summary>
        /// So sánh 2 ảnh 
        /// </summary>
        /// <param name="firstImage">Ảnh thứ nhất</param>
        /// <param name="secondImage">Ảnh thứ hai</param>
        /// <returns>true nếu giống nhau hoàn toàn, false nếu khác nhau</returns>
        private bool compare2Images(Bitmap firstImage, Bitmap secondImage)
        {
            //Khác kích thước chắc chắn không giống nhau
            if (firstImage.Width != secondImage.Width ||
                firstImage.Height != secondImage.Height)
            {
                return false;
            }

            //Bộ nhớ tạm
            MemoryStream ms = new MemoryStream();

            //Lưu ảnh 1 vào bộ nhớ tạm và chuyển đổi thành chuỗi
            firstImage.Save(ms, System.Drawing.Imaging.ImageFormat.Png);
            String firstString = Convert.ToBase64String(ms.ToArray());

            ms.Position = 0;
            //Lưu ảnh 2 vào nhớ tạm và chuyển đổi thành chuỗi
            secondImage.Save(ms, System.Drawing.Imaging.ImageFormat.Png);
            String secondString = Convert.ToBase64String(ms.ToArray());

            //So sánh 2 chuỗi 
            if (firstString.Equals(secondString))
            {
                return true; 
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// Tách texture từ background gốc
        /// </summary>
        /// <param name="img">background gốc</param>
        /// <param name="width">chiều rộng texture</param>
        /// <param name="height">chiều dài texture</param>
        /// <returns></returns>
        private void separateImage(Bitmap img, int width, int height)
        {
            //img = ConvertTo8bpp(img);

            //Khởi tạo danh sách ảnh chứa tất cả các texture tách ra được
            _list_texture = new List<Bitmap>();
            
            int cWidth = img.Width / width;
            int cHeight = img.Height / height;

            cWidth = img.Width % width == 0 ? cWidth : cWidth + 1;
            cHeight = img.Height % height == 0 ? cHeight : cHeight + 1;

            _wMap.writeLine(cWidth + " " + cHeight);//Ghi số dòng và số cột của map
            _map = new List<string>();

            for (int i = 0; i < cHeight; i++)
            {
                String mapLine = "";
                for (int j = 0; j < cWidth; j++)
                {
                    Bitmap texture;
                    Graphics g;
                    int width_draw = width;
                    int height_draw = height;

                    //Trường hợp rơi vào cột cuối hoặc hàng cuối mà size còn lại nhỏ hơn size cần cắt
                    if (i == cHeight - 1 || j == cWidth - 1)
                    {
                        if (i == cHeight - 1 && img.Height % height != 0)
                        {
                            height_draw = img.Height - (i * height);
                        }

                        if (j == cWidth - 1 && img.Width % width != 0)
                        {
                            width_draw = img.Width - (j * width);
                        }
                    }
                 
                    //Tách 1 texture từ img gốc
                    //Khởi tạo một texture chứa từng hình ảnh tách ra được
                    texture = new Bitmap(width_draw, height_draw);
                    g = Graphics.FromImage(texture);
                    g.DrawImageUnscaled(img, -j * width, -i * height);
                   
                    //So sánh texture vừa tách với các texture trong danh sách 
                    int type = 0;
                    if (_list_texture.Count == 0)
                    {
                        //Danh sách rỗng thì không cần so sánh
                        _list_texture.Add(texture);

                    }
                    else
                    {
                        //So sánh texture vừa tách với các texture đã lưu
                        bool flag = false;
                        for (int k = 0; k < _list_texture.Count; k++)
                        {
                            if (compare2Images(texture, _list_texture[k]))
                            {
                                type = k;
                                flag = true;
                                break;
                            }
                        }

                        //Nếu texture vừa tách không giống với các texture đã lưu
                        if (flag == false)
                        {
                            type = _list_texture.Count;
                            _list_texture.Add(texture);
                        }
                    }

                    mapLine += type + " ";
                    int percent = (i * cWidth + j) * 100 / (cHeight * cWidth);
                    pgbSeparation.Value = percent;
                }
                _map.Add(mapLine);
            }
        }

        /// <summary>
        /// Vẽ các texture tách được lên màn hình
        /// </summary>
        /// <param name="list">danh sách các texture tách được</param>
        /// <param name="width">chiều rộng texture</param>
        /// <param name="height">chiều dài texture</param>
        private void saveListTexture(int width, int height)
        {
            _result = new Bitmap(width * _list_texture.Count, height);
            Graphics g = Graphics.FromImage(_result);

            //Nếu folder chứa các texture chưa tồn tại
            //Tạo folder chứa texture của map
            if (!Directory.Exists(_folderTexture))
            {
                Directory.CreateDirectory(_folderTexture);
            }

            int x = 0; //Tọa độ vẽ;
            for (int i = 0; i < _list_texture.Count ; i ++)
            {
                g.DrawImageUnscaled(_list_texture[i], new Point(x, 0));
                x += _list_texture[i].Width;

                //Lưu texture nếu chưa tồn tại file đã lưu
                string fileName = _folderTexture + "\\" + i + ".png";
                if (File.Exists(fileName))
                {
                    File.Delete(fileName);
                }

                _list_texture[i].Save(fileName, System.Drawing.Imaging.ImageFormat.Png);
            }

            //Lưu map
            _wMap.writeLine(_list_texture.Count.ToString()); //Lưu số texture
            for (int i = 0; i < _map.Count; i++)
            {
                _wMap.writeLine(_map[i]);
            }
            
            //Xem size của folder
            long b = 0;
            string[] files = Directory.GetFiles(_folderTexture, "*.*");
            for (int i = 0; i < files.Length; i++)
            {
                FileInfo info = new FileInfo(files[i]);
                if (info.Name != "Thumbs.db")
                    b += info.Length;
            }

            lbTextureSize.Text = (b / 1024).ToString("n0") + " kb";
            lbTotalTexture.Text = _list_texture.Count.ToString();
            pbTexture.Image = _result;
            pbTexture.Show();
            btnReset.Enabled = true;
            trbZoom.Enabled = true;
            pgbSeparation.Value = 100;
        
        }

        #endregion

        #region EVENTS

        private void btnPicturePath_Click(object sender, EventArgs e)
        {
            //Thiết lập cửa sổ chọn ảnh
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Image Files |*.BMP;*.DIB;*.RLE;*.JPG;*.JPEG;*.JPE;*.JFIF;*.GIF;*.TIF;*.TIFF;*.PNG";
            ofd.Title = "Choose Picture";
            ofd.FilterIndex = 1;
            ofd.Multiselect = false;

            //Khi đã chọn đường dẫn của ảnh
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                //Ghi đường dẫn ảnh vào textbox
                string fullPath = ofd.FileName;
                string fileName = ofd.SafeFileName;
                string path = Path.GetDirectoryName(fullPath);
                _fileMapText = path + "\\map_" + fileName.Split(new char[] { '.' })[0] + ".txt"; //Tên file map lưu
                _folderTexture = path + "\\texture_" + fileName.Split(new char[] { '.' })[0]; //Tên folder lưu texture
                _wMap = new MapWriter(_fileMapText); 

                txtPicturePath.Text = fullPath;

                //Tải ảnh lên màn hình
                _picture = loadPicture(fullPath);
                pbPicture.Image = _picture;
                pbPicture.Show();

                //Lấy thông tin ảnh đã tải
                lbWHPicture.Text = _picture.Size.ToString();
                lbPictureSize.Text = (new FileInfo(fullPath).Length / 1024).ToString("n0") + " kb";

                btnSeparation.Enabled = true;
                trbZoom.Enabled = true;
            }
        }

        private void btnSeparation_Click(object sender, EventArgs e)
        {
            //Đang xử lý ảnh, khóa tất cả các thao tác
            btnPicturePath.Enabled = false;
            btnSeparation.Enabled = false;
            cmbHeight.Enabled = false;
            cmbWidth.Enabled = false;
            btnReset.Enabled = false;
            trbZoom.Enabled = false;

            //Tách texture 
            _width = int.Parse(cmbWidth.Text);
            _height = int.Parse(cmbHeight.Text);
            separateImage(_picture, _width, _height);
            saveListTexture(_width, _height);
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            //Làm mới toàn bộ chương trình
            txtPicturePath.Clear();
            pgbSeparation.Value = 0;
            cmbHeight.SelectedIndex = 2;
            cmbWidth.SelectedIndex = 2;
            btnSeparation.Enabled = false;
            pbPicture.Hide();
            pbTexture.Hide();
            trbZoom.Enabled = false;
            btnPicturePath.Enabled = true;
            cmbHeight.Enabled = true;
            cmbWidth.Enabled = true;
            lbPictureSize.Text = "0 kb";
            lbWHPicture.Text = "0 x 0";
            lbTextureSize.Text = "0 kb";
            lbTotalTexture.Text = "0";
        }

        private void trbZoom_ValueChanged(object sender, EventArgs e)
        {
            //Hiển thị giá trị zoome
            int value = trbZoom.Value;
            lbPercent.Text = value * 10 + "%";
            
            //Thay đổi kích thước ảnh gốc
            Size size = new Size((int)_picture.Width * value * 10 / 100, (int)_picture.Height * value * 10 / 100);
            Bitmap bmp = new Bitmap(_picture, size);

            pbPicture.Image = bmp;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            cmbWidth.SelectedIndex = 2;
            cmbHeight.SelectedIndex = 2;
        }

      
        #endregion
    }
}

