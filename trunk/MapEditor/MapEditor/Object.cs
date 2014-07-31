using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{
    enum Types
    {
        SIMON 
    }

    public class Object
    {
        private Point pos;
        private string type;
        private Rectangle bounds;
        private string global_type;
        public Image image;

        public Object()
        {
            pos = Point.Empty;
            type = "";
            bounds = Rectangle.Empty;
            global_type = "";
            image = null;
        }

        public Object(Object ob)
        {
            pos = ob.pos;
            type = ob.type;
            bounds = ob.bounds;
            global_type = ob.global_type;
            image = null;
        }

        public Object(string type, string global_type, Image image)
        {
            this.pos = Point.Empty;
            this.type = type;
            this.global_type = global_type;
            this.image = image;
        }

        #region PROPERTIES

        public Point Position
        {
            get { return pos; }
            set { pos = value; }
        }

        public string Type
        {
            get { return type; }
            set { type = value; }
        }

        public string GlobalType
        {
            get { return global_type; }
            set { global_type = value; }
        }

        public Image Image
        {
            get { return image; }
            set { image = value; }
        }

        #endregion
    }
}
