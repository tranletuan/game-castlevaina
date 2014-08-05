using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    public class ResourcesManager
    {
        public List<ImageList> list_resources;
        public List<List<Object>> list_objects;
        public List<string> list_global_type;

        private string folder_resources_;
        private string[] define_tail = { "BMP", "DIB", "RLE", "JPG", "JPEG", "JPE", "JFIF", "GIF", "TIF", "TIFF", "PNG" };

        public ResourcesManager(string folder_resources)
        {
            this.folder_resources_ = folder_resources;
            this.list_resources = new List<ImageList>();
            this.list_objects = new List<List<Object>>();
            this.list_global_type = new List<string>();
        }

        public void LoadAllResources()
        {
            //Đọc tất cả các thư mục con trong thư mục gốc
            string[] folders = Directory.GetDirectories(folder_resources_);
            foreach (string folder in folders)
            {
                //Tên của thư mục con được cắt ra
                //Tên của thư mục con chính là loại bao quát
                string global_type = folder.Substring(folder_resources_.Length + 1);
                list_global_type.Add(global_type); //Tên loại tổng quát
                ImageList images = new ImageList(); //Danh sách texture
                List<Object> objects = new List<Object>(); //Danh sách đối tượng

                //Đọc tất cả các file trong thư mục con 
                DirectoryInfo di = new DirectoryInfo(folder);
                FileInfo[] files_info = di.GetFiles();
                var files = files_info.Select(f => f).Where(f => (f.Attributes & FileAttributes.Hidden) == 0);
                
                foreach (var file in files)
                {
                    //Tải hình ảnh lên đối tượng, tên file texture là type
                    string[] file_name = file.Name.Split(new string[] { "." }, StringSplitOptions.RemoveEmptyEntries);
                    string type = file_name[0];
                    string tail = file_name[1];

                    if (IsImage(tail))
                    {
                        //Load texture và lưu đối tượng
                        Image img = Image.FromFile(file.FullName);
                        if (img != null)
                        {
                            objects.Add(new Object(Point.Empty, type, global_type, img.Width, img.Height));
                            images.Images.Add(type, img);
                        }
                    }
                }

                //Lưu danh sách những đối tượng cùng loại vào danh sách
                list_resources.Add(images);
                list_objects.Add(objects);
            }
        }

        private bool IsImage(string tail)
        {
            bool result = false;
            foreach (string t in define_tail)
            {
                if (t.CompareTo(tail.ToUpper()) == 0)
                {
                    return true;
                }
            }
            return result;
        }
    }
}
