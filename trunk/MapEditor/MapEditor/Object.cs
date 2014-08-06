﻿using System;
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
        private Bitmap image;

        //Hàm khởi tạo cho đối tượng rỗng
        public Object()
        {
            pos = Point.Empty;
            type = "";
            bounds = Rectangle.Empty;
            global_type = "";
        }

        //Hàm khởi tạo cho đối tượng lưu vào node quadtree
        public Object(Object ob, Point pos)
        {
            this.pos = pos;
            type = ob.type;
            this.image = null;
            this.bounds = new Rectangle(pos.X, pos.Y, ob.bounds.Width, ob.bounds.Height);
            global_type = ob.global_type;
        }

        //Hàm khởi tạo cho đối tượng load vào list chọn
        public Object(string type, string global_type, Bitmap image)
        {
            this.type = type;
            this.global_type = global_type;
            this.image = image;
            this.bounds = new Rectangle(0, 0, image.Width, image.Height);
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

        public Rectangle Bounds
        {
            get { return bounds; }
            set { bounds = value; }
        }

        public Bitmap Image
        {
            get { return image; }
        }
        #endregion
    }
}
