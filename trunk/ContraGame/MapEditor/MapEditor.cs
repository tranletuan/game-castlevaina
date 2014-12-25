using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    enum CursorCur
    {
        ICON,
        OBJECT,
        NONE,
        ITEM
    }


    public partial class MapEditor : Form
    {
        int Xwidth,Xheight;
        Background frmBG;
        Image imageCursor = null;
        CursorCur CurrentCursor;
        private List<ObjectTile> listObject;
        private List<ObjectTile> listObNoneTree;
        bool isItemStand;

        public MapEditor()
        {
            InitializeComponent();
            // set panel background
            panel1.AutoScroll = true;
            panel1.HorizontalScroll.Enabled = true;
            panel1.HorizontalScroll.Visible = true;


            // List Object
            listViewOB.LargeImageList = imageListOB;
            listViewOB.View = View.LargeIcon;
            listViewOB.Items.Add("BlockHouse", 0);
            listViewOB.Items.Add("BradgeEagle", 1);
            listViewOB.Items.Add("Sniper", 2);
            listViewOB.Items.Add("RunMan", 3);
            listViewOB.Items.Add("Obstacle", 4);
            listViewOB.Items.Add("SniperHide", 5);
            listViewOB.Items.Add("Boss1", 6);
            listViewOB.Items.Add("BossGun", 7);
            listViewOB.Items.Add("Fire", 8);
            listViewOB.Items.Add("RockRoll", 9);
            listViewOB.Items.Add("RunManFire", 10);
            listViewOB.Items.Add("SniperBlock", 11);
            listViewOB.Items.Add("SniperWater", 12);
            listViewOB.Items.Add("Boom", 13);
            listViewOB.Items.Add("Tank", 14);
            listViewOB.Items.Add("Boss2", 15);
            listViewOB.Items.Add("Boss3", 16);

            imageListOB.TransparentColor = Color.Transparent;

            // List Icon Control
            listViewControl.LargeImageList = imageListControl;
            listViewControl.View = View.LargeIcon;
            listViewControl.Items.Add("Cancel", 0);
            listViewControl.Items.Add("Remove", 1);

            // List Item
            listViewItem.LargeImageList = imageListItem;
            listViewItem.View = View.LargeIcon;
            listViewItem.Items.Add("ItemB", 0);
            listViewItem.Items.Add("ItemF", 1);
            listViewItem.Items.Add("ItemL", 2);
            listViewItem.Items.Add("ItemM", 3);
            listViewItem.Items.Add("ItemR", 4);
            listViewItem.Items.Add("ItemS", 5);

            // List Background
            listViewBG.LargeImageList = imageListBG;
            listViewBG.View = View.LargeIcon;
            listViewBG.Items.Add("Ground", 0);
            listViewBG.Items.Add("Water", 1);
            listViewBG.Items.Add("Brigde", 2);
            listViewBG.Items.Add("WaterEffect1", 3);
            listViewBG.Items.Add("WaterEffect2", 4);
            listViewBG.Items.Add("WaterEffect3", 5);
            listViewBG.Items.Add("StarEffect", 6);
            listViewBG.Items.Add("RockFly", 7);
            listViewBG.Items.Add("GroundElectron", 8);
            listViewBG.Items.Add("WaterFall", 9);

            // other
            CurrentCursor = CursorCur.NONE;

            listObject = new List<ObjectTile>();
            if (listObject != null)
            {
                listObject.Clear();
            }

            listObNoneTree = new List<ObjectTile>();
            if (listObNoneTree != null)
            {
                listObNoneTree.Clear();
            }

            // default
            textBoxCamX.Text = "0";
            textBoxCamY.Text = "240";
            textBoxChaX.Text = "40";
            textBoxChaY.Text = "240";

            textBoxXWidth.Text = "1";
            textBoxXWidth.Enabled = false;
            textBoxXHeight.Text = "1";
            textBoxXHeight.Enabled = false;

            Xheight = Convert.ToInt32(textBoxXHeight.Text);
            Xwidth = Convert.ToInt32(textBoxXWidth.Text);
            buttonEdit.Enabled = false;
            comboBoxDir.SelectedIndex = 0;
            comboBoxNameItem.Visible = false;
            comboBoxNameItem.SelectedIndex = 0;
            isItemStand = false;
        }

        private void buttonBG_Click(object sender, EventArgs e)
        {
            frmBG = new Background();
            frmBG.ShowDialog();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog();
            // Set filter options and filter index.
            openFile.Filter = "PNG Files (*.png)|*.png|All Files (*.*)|*.*";
            openFile.FilterIndex = 1;
            openFile.Title = "Open file background";



            if (openFile.ShowDialog() == DialogResult.OK)
            {

                Image image = Image.FromFile(openFile.FileName);
                pictureBoxBG.Image = image;
                pictureBoxBG.SizeMode = PictureBoxSizeMode.AutoSize;

                textBoxBGWidth.Text = "     " + image.Size.Width.ToString() + " pixel";
                textBoxBGHeigth.Text = "     " + image.Size.Height.ToString() + " pixel";
            }
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void listViewOB_MouseClick(object sender, MouseEventArgs e)
        {

            comboBoxNameItem.Visible = false;
            textBoxNameOB.Visible = true;
            isItemStand = false;
            CurrentCursor = CursorCur.OBJECT;

            // Lay image khi click + doi cursor          
            foreach (ListViewItem itm in listViewOB.SelectedItems)
            {
                int imgIndex = itm.ImageIndex;
                if (imgIndex >= 0 && imgIndex < this.imageListOB.Images.Count)
                {

                    imageCursor = this.imageListOB.Images[imgIndex];
                    if (imgIndex == 2)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 24, 32);
                    }
                    else if (imgIndex == 0)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 32, 32);
                    }
                    else if (imgIndex == 1)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 32, 32);
                        comboBoxNameItem.Visible = true;
                        textBoxNameOB.Visible = false;
                        isItemStand = true;
                    }
                    else if (imgIndex == 3)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 18, 33);
                        CurrentCursor = CursorCur.ITEM;
                    }
                    else if (imgIndex == 4)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 32, 32);
                    }
                    else if (imgIndex == 5)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 24, 32);
                    }
                    else if (imgIndex == 6)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 112, 184);
                    }
                    else if (imgIndex == 7)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 12, 6);
                    }
                    else if (imgIndex == 8)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 16, 16);
                    }
                    else if (imgIndex == 9)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 28, 28);
                    }
                    else if (imgIndex == 10)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 26, 32);
                        CurrentCursor = CursorCur.ITEM;
                    }
                    else if (imgIndex == 11)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 32, 32);
                    }
                    else if (imgIndex == 12)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 16, 32);
                    }
                    else if (imgIndex == 13)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 16, 16);
                    }
                    else if (imgIndex == 14)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 96, 66);
                    }
                    else if (imgIndex == 15)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 256, 194);
                    }
                    else if (imgIndex == 16)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 60, 64);
                    }
                }
            }

            this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
            textBoxHeightOB.Text = imageCursor.Height.ToString();
            textBoxWidthOB.Text = imageCursor.Width.ToString();
            textBoxNameOB.Text = listViewOB.SelectedItems[0].Text;



            resetButtonEdit();
        }

        private void pictureBoxBG_MouseMove(object sender, MouseEventArgs e)
        {

            MouseEventArgs me = (MouseEventArgs)e;
            Point coordinates = me.Location;
            if (pictureBoxBG.Image != null)
            {
                if (this.imageCursor == null)
                {
                    textBoxX.Text = "???";
                    textBoxY.Text = "???";
                }
                else
                {
                    // toa do top - left
                    if (coordinates.X - imageCursor.Width / 2 >= 0 && coordinates.Y - imageCursor.Height / 2 >= 0
                        && coordinates.X + imageCursor.Width / 2 <= pictureBoxBG.Width && coordinates.Y + imageCursor.Height / 2 <= pictureBoxBG.Height)
                    {
                        textBoxX.Text = (coordinates.X - imageCursor.Width / 2).ToString();
                        textBoxY.Text = (pictureBoxBG.Image.Height - (coordinates.Y - imageCursor.Height / 2)).ToString();
                    }
                    else
                    {
                        textBoxX.Text = "?";
                        textBoxY.Text = "?";
                    }
                }


            }

        }

        private void pictureBoxBG_Click(object sender, EventArgs e)
        {


            if (CurrentCursor == CursorCur.OBJECT || CurrentCursor == CursorCur.ITEM)
            {
                if (textBoxX.Text.Trim() != "?" && textBoxY.Text.Trim() != "?")
                {
                    // them hinh anh vao pictureBox           
                    MouseEventArgs me = (MouseEventArgs)e;
                    Point coordinates = me.Location;
                    PictureBox p = new PictureBox();
                    p.Image = imageCursor;
                    p.Location = new Point(me.Location.X - imageCursor.Width / 2, me.Location.Y - imageCursor.Height / 2);
                    p.SizeMode = PictureBoxSizeMode.AutoSize;
                    p.BackColor = Color.Transparent;

                    int direction = comboBoxDir.SelectedIndex;

                    if (CurrentCursor == CursorCur.ITEM)
                    {
                        // them vao list  
                        ObjectTile ob = new ObjectTile(p, (listObNoneTree.Count + 1), textBoxNameOB.Text, Convert.ToInt32(textBoxX.Text.Trim()),
                            Convert.ToInt32(textBoxY.Text.Trim()), direction);
                        listObNoneTree.Add(ob);
                        listObNoneTree.ElementAt(listObNoneTree.Count - 1).Pic.Click += new System.EventHandler(PictureBoxes_Click);
                        listObNoneTree.ElementAt(listObNoneTree.Count - 1).Pic.MouseMove += new System.Windows.Forms.MouseEventHandler(PictureBoxes_MouseMove);
                        listObNoneTree.ElementAt(listObNoneTree.Count - 1).Pic.MouseLeave += new System.EventHandler(PictureBoxes_MouseLeave);
                        pictureBoxBG.Controls.Add(listObNoneTree.ElementAt(listObNoneTree.Count - 1).Pic);
                    }
                    else
                    {
                        // them vao list  
                        string nameOb = textBoxNameOB.Text.Trim();
                        if (isItemStand)
                        {
                            nameOb = "ItemStand" + comboBoxNameItem.Text.Trim();
                        }
                       
                      
                        ObjectTile ob = new ObjectTile(p, (listObject.Count + 1), nameOb, Convert.ToInt32(textBoxX.Text.Trim()),
                            Convert.ToInt32(textBoxY.Text.Trim()), direction);
                        if (nameOb == "RockRoll")
                        {
                            ob.Height = 240;
                        }
                        else if (nameOb == "Tank")
                        {
                            ob.Width = 304;
                        }
                      
                        listObject.Add(ob);
                        listObject.ElementAt(listObject.Count - 1).Pic.Click += new System.EventHandler(PictureBoxes_Click);
                        listObject.ElementAt(listObject.Count - 1).Pic.MouseMove += new System.Windows.Forms.MouseEventHandler(PictureBoxes_MouseMove);
                        listObject.ElementAt(listObject.Count - 1).Pic.MouseLeave += new System.EventHandler(PictureBoxes_MouseLeave);
                        pictureBoxBG.Controls.Add(listObject.ElementAt(listObject.Count - 1).Pic);
                    }

                }
                else
                {
                    MessageBox.Show("Lỗi!!!! Xem lại tọa độ X và Y chưa hợp lệ ");
                }
            }

        }

        private void buttonSave_Click(object sender, EventArgs e)
        {

            if (listObject.Count > 0)
            {
                saveFileDialog1.Filter = "Text Files (*.txt)|*.txt|All files (*.*)|*.*";
                saveFileDialog1.FilterIndex = 1;
                saveFileDialog1.ShowDialog();

            }
            else
            {
                MessageBox.Show("Chưa có đối tượng!!!");
            }
        }

        private void pictureBoxBG_MouseLeave(object sender, EventArgs e)
        {
            textBoxX.Text = "?";
            textBoxY.Text = "?";

        }

        private void listViewControl_Click(object sender, EventArgs e)
        {
            // Lay image khi click + doi cursor          
            foreach (ListViewItem itm in listViewControl.SelectedItems)
            {
                int imgIndex = itm.ImageIndex;
                if (imgIndex >= 0 && imgIndex < this.imageListControl.Images.Count)
                {
                    if (imgIndex == 0)
                    {
                        this.Cursor = Cursors.Default;
                        CurrentCursor = CursorCur.NONE;
                        imageCursor = null;
                    }
                    else
                    {

                        imageCursor = this.imageListControl.Images[imgIndex];
                        imageCursor = FileTool.ResizeImage(imageCursor, 8, 8);
                        CurrentCursor = CursorCur.ICON;
                        this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
                    }

                }
            }
            resetButtonEdit();
        }

        // click vo picbox new tren background
        private void PictureBoxes_Click(object sender, EventArgs e)
        {
            if (CurrentCursor == CursorCur.ICON)
            {
                // xoa pic tren background va list
                PictureBox p = (PictureBox)sender;

                for (int i = 0; i < listObject.Count; i++)
                {
                    if (listObject.ElementAt(i).Pic == p)
                    {
                        pictureBoxBG.Controls.Remove(listObject.ElementAt(i).Pic);
                        listObject.RemoveAt(i);
                    }
                }

            }
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

            QuadTree tree = new QuadTree(pictureBoxBG.Width, pictureBoxBG.Height);
            tree.createSubNode();
            tree.getListLeaf();
            tree.addObject(listObject);
            ObjectTile cam = new ObjectTile(0, "Camera", Convert.ToInt32(textBoxCamX.Text.Trim()), Convert.ToInt32(textBoxCamY.Text.Trim()), 256, 240, 0);
            listObject.Add(cam);
            ObjectTile character = new ObjectTile(0, "Character", Convert.ToInt32(textBoxChaX.Text.Trim()), Convert.ToInt32(textBoxChaY.Text.Trim()), 36, 46, 0);
            listObject.Add(character);
            FileTool.writeFileConfi(saveFileDialog1, listObject, listObNoneTree);
            FileTool.writeFileOB(saveFileDialog1, listObject, pictureBoxBG.Width, pictureBoxBG.Height);
            FileTool.writeFileOBNoneQuadTree(saveFileDialog1, listObNoneTree, pictureBoxBG.Width, pictureBoxBG.Height);
            FileTool.writeFileTree(saveFileDialog1, tree);
            MessageBox.Show("Lưu file thành công");
        }

        private void buttonRest_Click(object sender, EventArgs e)
        {

            imageCursor = null;
            CurrentCursor = CursorCur.NONE;
            if (listObject.Count > 0)
            {
                for (int i = 0; i < listObject.Count; i++)
                {
                    pictureBoxBG.Controls.Remove(listObject.ElementAt(i).Pic);
                }
            }
            listObject.Clear();
            pictureBoxBG.Image = null;
            textBoxXWidth.Text = "1";
            resetButtonEdit();
        }

        private void listViewBG_MouseClick(object sender, MouseEventArgs e)
        {


            resetButtonEdit();
            Xwidth = 1;
            Xheight = 1;
            if (Convert.ToInt32(textBoxXWidth.Text.Trim()) > 0)
            {
                Xwidth = Convert.ToInt32(textBoxXWidth.Text.Trim());
            }
            if (Convert.ToInt32(textBoxXHeight.Text.Trim()) > 0)
            {
                Xheight = Convert.ToInt32(textBoxXHeight.Text.Trim());
            }


            // Lay image khi click + doi cursor          
            foreach (ListViewItem itm in listViewBG.SelectedItems)
            {
                int imgIndex = itm.ImageIndex;
                if (imgIndex >= 0 && imgIndex < this.imageListBG.Images.Count)
                {
                    imageCursor = this.imageListBG.Images[imgIndex];

                    if (imgIndex == 0)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 32 * Xwidth, 16);

                    }
                    else if (imgIndex == 1)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 32 * Xwidth, 16);
                    }
                    else if (imgIndex == 2)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 128, 32);
                    }
                    else if (imgIndex == 3)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 32 * Xwidth, 16);
                    }
                    else if (imgIndex == 4)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 32 * Xwidth, 16);
                    }
                    else if (imgIndex == 5)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 32 * Xwidth, 16);
                    }
                    else if (imgIndex == 6)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 32 * Xwidth, 16);
                    }
                    else if (imgIndex == 7)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 32 * Xwidth, 32);
                    }
                    else if (imgIndex == 8)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 128 * Xwidth, 16);
                    }
                    else if (imgIndex == 9)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 32 * Xwidth, 16*Xheight);
                    }

                }
            }

            comboBoxNameItem.Visible = false;
            textBoxNameOB.Visible = true;
            isItemStand = false;

            this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
            textBoxHeightOB.Text = imageCursor.Height.ToString();
            textBoxWidthOB.Text = imageCursor.Width.ToString();
            textBoxNameOB.Text = listViewBG.SelectedItems[0].Text;
            CurrentCursor = CursorCur.OBJECT;
            buttonEdit.Enabled = true;

        }

        private void listViewItem_MouseClick(object sender, MouseEventArgs e)
        {


            comboBoxNameItem.Visible = false;
            textBoxNameOB.Visible = true;
            isItemStand = false;

            // Lay image khi click + doi cursor          
            foreach (ListViewItem itm in listViewItem.SelectedItems)
            {
                int imgIndex = itm.ImageIndex;
                if (imgIndex >= 0 && imgIndex < this.imageListItem.Images.Count)
                {
                    imageCursor = this.imageListItem.Images[imgIndex];

                    if (imgIndex == 0)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 24, 15);

                    }
                    else if (imgIndex == 1)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 24, 15);

                    }
                    else if (imgIndex == 2)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 24, 15);

                    }
                    else if (imgIndex == 3)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 24, 15);

                    }
                    else if (imgIndex == 4)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 24, 15);

                    }
                    else if (imgIndex == 5)
                    {
                        imageCursor = FileTool.ResizeImage(imageCursor, 24, 15);

                    }
                }
            }


            this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
            textBoxHeightOB.Text = imageCursor.Height.ToString();
            textBoxWidthOB.Text = imageCursor.Width.ToString();
            textBoxNameOB.Text = listViewItem.SelectedItems[0].Text;
            CurrentCursor = CursorCur.ITEM;
            resetButtonEdit();
        }

        private void buttonEdit_Click(object sender, EventArgs e)
        {
            if (buttonEdit.Text == "Edit")
            {
                buttonEdit.Text = "Back";
                textBoxXWidth.Enabled = true;
                textBoxXHeight.Enabled = true;
            }
            else if (buttonEdit.Text == "Back")
            {
                if (textBoxXWidth.Text.Trim() != "")
                {
                    int Xold = Xwidth; // gia tri Xwidth cu
                    Xwidth = 1;
                    Xheight = 1;
                    imageCursor = FileTool.ResizeImage(imageCursor, imageCursor.Width * Xwidth / Xold, imageCursor.Height);
                    this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
                }
                resetButtonEdit();
            }
        }

        private void textBoxXWidth_KeyUp(object sender, KeyEventArgs e)
        {

            if (textBoxXWidth.Text.Trim() != "" && Convert.ToInt32(textBoxXWidth.Text.Trim()) > 0)
            {
                int Xold = Xwidth; // gia tri Xwidth cu
                Xwidth = Convert.ToInt32(textBoxXWidth.Text);
                imageCursor = FileTool.ResizeImage(imageCursor, imageCursor.Width * Xwidth / Xold, imageCursor.Height);
                this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
            }
            else
            {
                int Xold = Xwidth; // gia tri Xwidth cu
                Xwidth = 1;
                imageCursor = FileTool.ResizeImage(imageCursor, imageCursor.Width * Xwidth / Xold, imageCursor.Height);
                this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
            }
        }

        private void textBoxXWidth_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsDigit(e.KeyChar) && !Char.IsControl(e.KeyChar))
            {
                e.Handled = true;
            }

        }

        public void resetButtonEdit()
        {
            buttonEdit.Enabled = false;
            buttonEdit.Text = "Edit";
            textBoxXWidth.Text = "1";
            textBoxXWidth.Enabled = false;
            textBoxXHeight.Text = "1";
            textBoxXHeight.Enabled = false;

        }
        private void PictureBoxes_MouseMove(object sender, EventArgs e)
        {           
            this.Cursor = Cursors.Hand;
        }

        private void PictureBoxes_MouseLeave(object sender, EventArgs e)
        {
            this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            pictureBoxBG.Visible = !pictureBoxBG.Visible;
        }

        private void textBoxXHeight_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsDigit(e.KeyChar) && !Char.IsControl(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        private void textBoxXHeight_KeyUp(object sender, KeyEventArgs e)
        {
            if (textBoxXHeight.Text.Trim() != "" && Convert.ToInt32(textBoxXHeight.Text.Trim()) > 0)
            {
                int Xold = Xheight; // gia tri Xwidth cu
                Xheight = Convert.ToInt32(textBoxXHeight.Text);
                imageCursor = FileTool.ResizeImage(imageCursor, imageCursor.Width, imageCursor.Height * Xheight / Xold);
                this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
            }
            else
            {
                int Xold = Xheight; // gia tri Xwidth cu
                Xheight = 1;
                imageCursor = FileTool.ResizeImage(imageCursor, imageCursor.Width, imageCursor.Height * Xheight / Xold);
                this.Cursor = new Cursor(((Bitmap)imageCursor).GetHicon());
            }
        }
    }


}
