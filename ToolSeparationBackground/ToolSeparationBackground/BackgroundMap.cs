using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ToolSeparationBackground
{
    public class BackgroundMap
    {
        private string _fileName;

        public BackgroundMap(String fileName)
        {
            _fileName = fileName;
            if (File.Exists(fileName))
            {
                File.Delete(fileName);
            }
        }

        public void writeLine(string line)
        {
            using (StreamWriter sw = new StreamWriter(_fileName, true))
            {
                sw.WriteLine(line);
            }
        }

        public string FileName
        {
            get { return _fileName; }
        }
    }
}
