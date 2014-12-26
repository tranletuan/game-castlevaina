using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    class FileTool
    {

        // ghi file cat background
        public static void writeFileBG(SaveFileDialog saveFile, int[,] list, int row, int col)
        {
            //ghi file txt
            string path = System.IO.Path.Combine(System.IO.Path.GetDirectoryName(saveFile.FileName),
            System.IO.Path.GetFileNameWithoutExtension(saveFile.FileName)) + "_bg.txt";
            System.IO.StreamWriter sWriter = new System.IO.StreamWriter(path);
            sWriter.WriteLine(row.ToString());
            sWriter.WriteLine(col.ToString());
            for (int h = 0; h < list.GetLength(1); h++)
            {
                for (int w = 0; w < list.GetLength(0); w++)
                {
                    string str = list[w, h].ToString();
                    if (w == list.GetLength(0) - 1)
                    {
                        // sWriter.WriteLine();
                    }
                    else
                    {
                        str += " ";
                    }
                    sWriter.Write(str);
                    if (w == list.GetLength(0) - 1)
                    {
                        if (h < list.GetLongLength(1) - 1)
                        {
                            sWriter.WriteLine();
                        }

                    }
                }
            }

            sWriter.Flush();
            sWriter.Close();

        }

        // ghi file text cho object toa do in quadtree
        public static void writeFileOB(SaveFileDialog saveFile, List<ObjectTile> list, int width, int heigth)
        {
            //ghi file txt
            string path = System.IO.Path.Combine(System.IO.Path.GetDirectoryName(saveFile.FileName),
            System.IO.Path.GetFileNameWithoutExtension(saveFile.FileName)) + "_ob_qt.txt";
            System.IO.StreamWriter sWriter = new System.IO.StreamWriter(path);

            //sWriter.WriteLine(width.ToString());
            //sWriter.WriteLine(heigth.ToString());
            for (int i = 0; i < list.Count; i++)
            {
                String name = list.ElementAt(i).Name;
                String posX = list.ElementAt(i).PosX.ToString();
                String posY = list.ElementAt(i).PosY.ToString();
                String id = list.ElementAt(i).Id.ToString();
                String w = list.ElementAt(i).Width.ToString();
                String h = list.ElementAt(i).Height.ToString();

                sWriter.WriteLine(id + " " + name + " " + posX + " " + posY + " " + w + " " + h + " ");
            }

            sWriter.Flush();
            sWriter.Close();

        }

        // ghi file text cho object k nam trong quadtree
        public static void writeFileOBNoneQuadTree(SaveFileDialog saveFile, List<ObjectTile> list, int width, int heigth)
        {
            //ghi file txt
            string path = System.IO.Path.Combine(System.IO.Path.GetDirectoryName(saveFile.FileName),
            System.IO.Path.GetFileNameWithoutExtension(saveFile.FileName)) + "_ob.txt";
            System.IO.StreamWriter sWriter = new System.IO.StreamWriter(path);

            //sWriter.WriteLine(width.ToString());
            //sWriter.WriteLine(heigth.ToString());
            for (int i = 0; i < list.Count; i++)
            {
                String name = list.ElementAt(i).Name;
                String posX = list.ElementAt(i).PosX.ToString();
                String posY = list.ElementAt(i).PosY.ToString();
                String id = list.ElementAt(i).Id.ToString();
                String w = list.ElementAt(i).Width.ToString();
                String h = list.ElementAt(i).Height.ToString();
                String directon = list.ElementAt(i).Direction.ToString();

                sWriter.WriteLine(id + " " + name + " " + posX + " " + posY + " " + w + " " + h + " " + directon + " ");
            }

            sWriter.Flush();
            sWriter.Close();

        }

        // ghi file load texture
        public static void writeFileConfi(SaveFileDialog saveFile, List<ObjectTile> listtree, List<ObjectTile> listnotree)
        {
            //ghi file txt
            string path = System.IO.Path.Combine(System.IO.Path.GetDirectoryName(saveFile.FileName),
            "confi_map_" + System.IO.Path.GetFileNameWithoutExtension(saveFile.FileName)) + ".txt";
            System.IO.StreamWriter sWriter = new System.IO.StreamWriter(path);
            List<String> listString = new List<string>();

            int levelMap = Convert.ToInt32(saveFile.FileName) + 1;
            listString.Add(levelMap.ToString());
            listString.Add("RunMan");
            listString.Add("RunManFire");
            listString.Add("Item");

            for (int i = 0; i < listtree.Count; i++)
            {
                if (listnotree.ElementAt(i).Name.IndexOf("ItemStand") == 0)
                {
                    listString.Add("ItemStand");
                }
                else
                {
                     listString.Add(listtree.ElementAt(i).Name);
                }
               
                for (int j = 0; j < listString.Count - 1; j++)
                {
                    if (listString.ElementAt(j) == listString.ElementAt(listString.Count - 1))
                    {
                        listString.RemoveAt(listString.Count - 1);
                        break;
                    }
                }
            }

            for (int i = 0; i < listString.Count; i++)
            {
                String name = listString.ElementAt(i);
                sWriter.WriteLine(name);
            }

            sWriter.Flush();
            sWriter.Close();
        }


        //Resize image
        public static Bitmap ResizeImage(Image image, int rWidth, int rHeight)
        {
            var newImage = new Bitmap(rWidth, rHeight);
            Graphics.FromImage(newImage).DrawImage(image, 0, 0, rWidth, rHeight);
            Bitmap bmp = new Bitmap(newImage);

            return SetImageAlpha(bmp, 200);
        }

        // viet file quadtree 
        // ghi file text cho object toa do
        public static void writeFileTree(SaveFileDialog saveFile, QuadTree qt)
        {
            //ghi file txt
            string path = System.IO.Path.Combine(System.IO.Path.GetDirectoryName(saveFile.FileName),
            System.IO.Path.GetFileNameWithoutExtension(saveFile.FileName)) + "_quadtree.txt";
            System.IO.StreamWriter sWriter = new System.IO.StreamWriter(path);

            for (int i = 0; i < qt.ListAllNode.Count; i++)
            {

                String posX = qt.ListAllNode.ElementAt(i).PosX.ToString();
                String posY = qt.ListAllNode.ElementAt(i).PosY.ToString();
                String w = qt.ListAllNode.ElementAt(i).Width.ToString();
                String h = qt.ListAllNode.ElementAt(i).Height.ToString();
                String id = qt.ListAllNode.ElementAt(i).Id.ToString();
                String listOB = "";

                if (qt.ListAllNode.ElementAt(i).ListObject != null)
                {
                    for (int j = 0; j < qt.ListAllNode.ElementAt(i).ListObject.Count; j++)
                    {
                        listOB += qt.ListAllNode.ElementAt(i).ListObject.ElementAt(j).Id.ToString() + ",";
                        if (j == qt.ListAllNode.ElementAt(i).ListObject.Count - 1)
                        {
                            listOB += " ";
                        }
                    }

                }

                sWriter.WriteLine(id + " " + posX + " " + posY + " " + w + " " + h + " " + listOB);
            }

            sWriter.Flush();
            sWriter.Close();

        }

        // chinh do mo anh
        public static Bitmap SetImageAlpha(Bitmap image, Byte apla)
        {
            Bitmap original = new Bitmap(image);
            Bitmap tranImage = new Bitmap(image.Width, image.Height);

            Color c = Color.Black;
            Color v = Color.Black;

            for (int i = 0; i < image.Width; i++)
            {
                for (int j = 0; j < image.Height; j++)
                {
                    c = original.GetPixel(i, j);
                    v = Color.FromArgb(apla, c.R, c.B, c.G);
                    tranImage.SetPixel(i, j, v);
                }
            }

            return tranImage;
        }
    }
}
