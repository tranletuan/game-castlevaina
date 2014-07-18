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

namespace ToolSeparationBackground
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            
        }

        Bitmap _picture;
        BackgroundMap _map;
        String _fileMapText;
        String _fileTexture;

        List<Bitmap> listTexture;

        #region METHODS

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
            //Khởi tạo danh sách ảnh chứa tất cả các texture tách ra được
            listTexture = new List<Bitmap>();
            
            int cWidth = img.Width / width;
            int cHeight = img.Height / height;

            for (int i = 0; i < cHeight; i++)
            {
                String mapLine = "";
                for (int j = 0; j < cWidth; j++)
                {
                    //Tách 1 texture từ img gốc
                    //Khởi tạo một texture chứa từng hình ảnh tách ra được
                    Bitmap texture = new Bitmap(width, height);
                    Graphics g = Graphics.FromImage(texture);
                    g.DrawImageUnscaled(img, -j * width, -i * height);
                    int type = 0;

                    //So sánh texture vừa tách với các texture trong danh sách 
                    if (listTexture.Count == 0)
                    {
                        //Danh sách rỗng thì không cần so sánh
                        listTexture.Add(texture);
                        
                    }
                    else
                    {
                        //So sánh texture vừa tách với các texture đã lưu
                        bool flag = false;
                        for (int k = 0; k < listTexture.Count; k++)
                        {
                            if (compare2Images(texture, listTexture[k]))
                            {
                                type = k;
                                flag = true;
                                break;
                            }
                        }

                        //Nếu texture vừa tách không giống với các texture đã lưu
                        if (flag == false)
                        {
                            type = listTexture.Count;
                            listTexture.Add(texture);
                        }
                    }

                    mapLine += type + " ";
                    pgbSeparation.PerformStep();
                }

                _map.writeLine(mapLine);
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
            Bitmap bmp = new Bitmap(width * listTexture.Count, height);
            Graphics g = Graphics.FromImage(bmp);

            int x = 0; //Tọa độ vẽ;
            for (int i = 0; i < listTexture.Count ; i ++)
            {
                g.DrawImageUnscaled(listTexture[i], new Point(x, 0));
                x += width;
            }
            
            //Lưu texture
            if (File.Exists(_fileTexture))
            {
                File.Delete(_fileTexture);
            }

            bmp.Save(_fileTexture, System.Drawing.Imaging.ImageFormat.Png);
            lbTextureSize.Text = (new FileInfo(_fileTexture).Length / 1024).ToString("n0") + " kb";

            lbTotalTexture.Text = listTexture.Count.ToString();
            pbTexture.Image = bmp;
            pbTexture.Show();
            btnReset.Enabled = true;
            btnPicturePath.Enabled = true;
            cmbHeight.Enabled = true;
            cmbWidth.Enabled = true;
            trbZoom.Enabled = true;
        }

        #endregion

      
        private void btnPicturePath_Click(object sender, EventArgs e)
        {
            //Thiết lập cửa sổ chọn ảnh
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Image Files |*.jpg;*.jpeg;*.png;*.bmp;*.gif";
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
                _fileTexture = path + "\\texture_" + fileName.Split(new char[] { '.' })[0] + ".png"; //Tên file texture
                _map = new BackgroundMap(_fileMapText); 

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
            int width = int.Parse(cmbWidth.Text);
            int height = int.Parse(cmbHeight.Text);
            separateImage(_picture, width, height);
            saveListTexture(width, height);
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

        

      
    }
}
