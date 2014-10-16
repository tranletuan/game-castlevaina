using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{
    public class Global
    {
        public static int MIN_WIDTH = 200;
        public static int ID = 0;
        public static int DISTANCE_MOVE = 5;
        public static Setting SETTING;
        public static string SETTING_PATH = "setting.txt";
      
    }

    public struct Setting
    {
        public string BackgroundPath;
        public string ResourcesPath;
        public bool AutoLoad;

        public Setting(string bgPath, string rsPath, bool autoLoad)
        {
            BackgroundPath = bgPath;
            ResourcesPath = rsPath;
            AutoLoad = autoLoad;
        }

        public Setting(string SettingPath)
        {
            if (File.Exists(SettingPath))
            {
                using (StreamReader sr = new StreamReader(SettingPath))
                {
                    BackgroundPath = sr.ReadLine();
                    ResourcesPath = sr.ReadLine();
                    AutoLoad = bool.Parse(sr.ReadLine());
                }
            }
            else
            {
                BackgroundPath = "";
                ResourcesPath = "";
                AutoLoad = false;
            }
        }
    }
}
