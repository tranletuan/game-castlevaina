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
        private List<ImageList> list_resources;
        private List<List<Object>> list_objects;
        private List<string> list_global_type;

        private string[] define_tail = { "BMP", "DIB", "RLE", "JPG", "JPEG", "JPE", "JFIF", "GIF", "TIF", "TIFF", "PNG" };

        public ResourcesManager()
        {
            this.list_resources = new List<ImageList>();
            this.list_objects = new List<List<Object>>();
            this.list_global_type = new List<string>();
        }

        public void LoadAllResources(string folder_resources)
        {
            list_global_type = new List<string>();
            list_resources = new List<ImageList>();
            list_objects = new List<List<Object>>();
            //Đọc tất cả các thư mục con trong thư mục gốc
            string[] folders = Directory.GetDirectories(folder_resources);
            foreach (string folder in folders)
            {
                //Tên của thư mục con được cắt ra
                //Tên của thư mục con chính là loại bao quát
                string global_type = folder.Substring(folder_resources.Length + 1);
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
                        Bitmap img = new Bitmap(file.FullName);
                        if (img != null)
                        {
                            objects.Add(new Object(type, global_type, img));
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

        public List<ImageList> ListResources
        {
            get { return list_resources; }
        }

        public List<List<Object>> ListObjects
        {
            get { return list_objects; }
        }

        public List<string> ListGlobalType
        {
            get { return list_global_type; }
        }

        public Object GetObjectBy(string type, string global_type)
        {
            Object o = new Object();
            int index = list_global_type.IndexOf(global_type);

            foreach (Object ob in list_objects[index])
            {
                if (o.Type.CompareTo(ob.Type) == 0)
                {
                    o = ob;
                    break;
                }
            }

            return o;
        }
    }
}
