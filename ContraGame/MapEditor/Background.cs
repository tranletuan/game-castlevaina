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
    public partial class Background : Form
    {

        const int TILE_WEIDTH = 16;
        const int TILE_HEIGTH = 16;
        const int BGSLIPT_WEIDTH = 256;

        private int bg_width; //  so tile cua bg chua cat theo width
        private int bg_height;
        private int[,] lis;
        private List<Bitmap> list; // danh sach tile chua loc cua bg
        private List<Bitmap> listtam; // danh sach tile da loc cua bg
        private Bitmap background;

        

        public Background()
        {
            InitializeComponent();
            panel1.AutoScroll = true;
            panel1.HorizontalScroll.Enabled = true;
            panel1.HorizontalScroll.Visible = true;
            panel2.AutoScroll = true;
            panel2.HorizontalScroll.Enabled = true;
            panel2.VerticalScroll.Enabled = true; 

            if (pictureBoxAfter.Image == null)
            {
                buttonSave.Enabled = false;
            }
            else
            {
                buttonSave.Enabled = true;
            }

            if (pictureBoxBG.Image == null)
            {
                buttonSlipt.Enabled = false;
            }
            else
            {
                buttonSlipt.Enabled = true;
            }

            textBox3.Text = "0";
            textBox4.Text = "0";
        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog();
            // Set filter options and filter index.
            openFile.Filter = "PNG Files (*.png)|*.png|All Files (*.*)|*.*";
            openFile.FilterIndex = 1;
            openFile.Title = "Open file background";

          

            if (  openFile.ShowDialog() == DialogResult.OK)
            {            

                Image image = Image.FromFile(openFile.FileName);
                pictureBoxBG.Image = image;
                pictureBoxBG.SizeMode = PictureBoxSizeMode.AutoSize;

                if (openFile.FileName.Trim() !="")
                {
                    textBoxBGWidth.Text = "     " + image.Size.Width.ToString() + " pixel";
                    textBoxBGHeigth.Text = "     " +  image.Size.Height.ToString() + " pixel";
                } else
                {
                    textBoxBGWidth.Text = "     ";
                    textBoxBGHeigth.Text = "     " ;
                }
                buttonSlipt.Enabled = true;
            }
        }

        //cat anh
        private Bitmap CropBitmap(Bitmap bitmap, int CropX, int CropY, int CropWidth, int CropHeigh)
        {
            Rectangle rect = new Rectangle(CropX, CropY, CropWidth, CropHeigh);
            Bitmap cropped = bitmap.Clone(rect, bitmap.PixelFormat);
            return cropped;
        }

        //so sanh 2 anh
        private bool Compare(Bitmap firstBitmap, Bitmap secondBitmap)
        {
            //bool flat = true;
            string firstPixel;
            string secondPixel;

            if (firstBitmap.Width == secondBitmap.Width && firstBitmap.Height == secondBitmap.Height)
            {
                for (int i = 0; i < firstBitmap.Width; i++)
                {
                    for (int j = 0; j < firstBitmap.Height; j++)
                    {
                        firstPixel = firstBitmap.GetPixel(i, j).ToString();
                        secondPixel = secondBitmap.GetPixel(i, j).ToString();
                        if (firstPixel != secondPixel)
                        {
                            return false;
                        }
                    }
                }
                return true;
            }
            else
            {
                return false;
            }
        }

        //gắn ảnh lại
        private Bitmap Combine(List<Bitmap> list)
        {
            List<System.Drawing.Bitmap> images = new List<System.Drawing.Bitmap>();
            System.Drawing.Bitmap finalImage = null;

            try
            {
                int width = 0;
                int height = 0;
                foreach (Bitmap image in list)
                {

                    System.Drawing.Bitmap bitmap = new System.Drawing.Bitmap(image);
                    width += bitmap.Width;
                    height = bitmap.Height > height ? bitmap.Height : height;
                    images.Add(bitmap);

                }
                            
                int final_height;
                int numTileInWidth = BGSLIPT_WEIDTH / TILE_WEIDTH;
                if (images.Count % 8 == 0)
                {
                    final_height = (images.Count / numTileInWidth) * TILE_HEIGTH;
                }
                else
                {
                    final_height = (images.Count / numTileInWidth + 1) * TILE_HEIGTH;
                }

                //create a bitmap to hold the combined image
                finalImage = new Bitmap(BGSLIPT_WEIDTH, final_height);

                //get a graphics object from the image so we can draw on it
                using (Graphics g = Graphics.FromImage(finalImage))
                {
                    //set background color
                    g.Clear(System.Drawing.Color.Black);

                    //go through each image and draw it on the final image
                    int offset_width = 0;
                    int offset_height = 0;
                    foreach (Bitmap image in images)
                    {
                        g.CompositingQuality = System.Drawing.Drawing2D.CompositingQuality.HighQuality;
                        g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
                        g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighQuality;
                        g.DrawImage(image,
                          new System.Drawing.Rectangle(offset_width, offset_height, image.Width, image.Height));
                        offset_width += image.Width;
                        if (offset_width >= BGSLIPT_WEIDTH)
                        {
                            offset_width = 0;
                            offset_height += image.Height;
                        }
                    }
                }

                return finalImage;
            }
            catch (Exception ex)
            {
                if (finalImage != null)
                    finalImage.Dispose();

                throw ex;
            }
            finally
            {
                foreach (System.Drawing.Bitmap image in images)
                {
                    image.Dispose();
                }
            }
        }

        private void buttonSlipt_Click(object sender, EventArgs e)
        {
            Cursor = Cursors.AppStarting;
            background = (Bitmap)pictureBoxBG.Image;

            bg_width = background.Width / TILE_WEIDTH;
            bg_height = background.Height / TILE_HEIGTH;
            lis = new int[bg_width, bg_height];

            list = new List<Bitmap>();
            listtam = new List<Bitmap>();
            int after = 0; //so anh sau khi cat
            int before = 0; //so anh truoc khi cat
            int size = 16;
            for (int i = 0; i < background.Height; i = i + size)
            {
                for (int j = 0; j < background.Width; j = j + size)
                {
                    Bitmap tam = CropBitmap(background, j, i, size, size);
                    listtam.Add(tam);
                    before++;
                    int dem = 0;
                    for (int k = 0; k < list.Count; k++)
                    {
                        if (Compare(tam, list[k]) == true)
                        {
                            dem++;
                            break;
                        }
                    }
                    if (dem == 0) //2 bitmap khac nhau thi add vao list
                    {
                        list.Add(tam);
                        after++;
                    }
                }
            }
            textBoxDaLoc.Text = after.ToString() + " tile ( Width : 16 tile)";
            textBoxChuaLoc.Text = before.ToString() +" tile";
            pictureBoxAfter.Image = Combine(list);
            pictureBoxAfter.SizeMode = PictureBoxSizeMode.AutoSize;
            Cursor = Cursors.Default;
            buttonSave.Enabled = true;
            textBox3.Text = " 16 pixel ";
            textBox4.Text = " 16 pixel ";
            textBoxBGWidth.Text += "  ( " + bg_width +" tile)";
            textBoxBGHeigth.Text += "  ( " + bg_height + " tile)";
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            Cursor = Cursors.AppStarting;
            int lis_x = 0;
            int lis_y = 0;           

            List<ObjectTile> listObject = new List<ObjectTile>();

            for (int i = 0; i < listtam.Count; i++)
            {
                for (int j = 0; j < list.Count; j++)
                {
                    if (Compare(listtam[i], list[j]))
                    {
                        lis[lis_x, lis_y] = j;                      
                        if (lis_x < bg_width - 1)
                        {
                            lis_x++;
                        }
                        else
                        {
                            lis_x = 0;
                            lis_y++;
                        }
                    }
                }
            }

            int row = pictureBoxBG.Image.Width / TILE_WEIDTH;
            int col = pictureBoxBG.Image.Height / TILE_HEIGTH;
            FileTool.writeFileBG(saveFileDialog1, lis, row,col);
            //ghi file png
            Combine(list).Save(saveFileDialog1.FileName.ToString());
            Cursor = Cursors.Default;
            MessageBox.Show("Đã tạo file PNG và file TXT thành công");
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            if (pictureBoxAfter.Image != null)
            {
                saveFileDialog1.Filter = "PNG Files (*.png)|*.png|All files (*.*)|*.*";
                saveFileDialog1.FilterIndex = 1;
                saveFileDialog1.ShowDialog();
            } 
        }

        private void groupBox3_Enter(object sender, EventArgs e)
        {

        }
    }
}
