using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{
    public class ObjectManager
    {
        public List<Object> list_object;
        private string folder_object;

        public ObjectManager(string folder_object)
        {
            this.folder_object = folder_object;
            this.list_object = new List<Object>();
        }

        public void LoadAllObject()
        {
            //Đọc tất cả các thư mục con trong thư mục gốc
            string[] folders = Directory.GetDirectories(folder_object);
            foreach (string folder in folders)
            {
                //Tên của thư mục con được cắt ra
                //Tên của thư mục con chính là loại bao quát
                string global_type = folder.Substring(folder_object.Length + 1);

                //Đọc tất cả các file trong thư mục con 
                DirectoryInfo di = new DirectoryInfo(folder);
                FileInfo[] files_info = di.GetFiles();
                var files = files_info.Select(f => f).Where(f => (f.Attributes & FileAttributes.Hidden) == 0);
                foreach (var file in files)
                {
                    //Tải hình ảnh lên đối tượng
                    string type = file.Name.Split(new string[] { "." }, StringSplitOptions.RemoveEmptyEntries)[0];
                    
                }
            }
        }

        public List<Object> GetList(int big_type)
        {

            return null;
        }




    }
}
