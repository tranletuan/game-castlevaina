using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    class ObjectTile
    {
        int _id;

        public int Id
        {
            get { return _id; }
            set { _id = value; }
        }


        String _name;

        public String Name
        {
            get { return _name; }
            set { _name = value; }
        }
        int _posX;

        public int PosX
        {
            get { return _posX; }
            set { _posX = value; }
        }


        int _posY;

        public int PosY
        {
            get { return _posY; }
            set { _posY = value; }
        }

        int _width;

        public int Width
        {
            get { return _width; }
            set { _width = value; }
        }

        int _height;

        public int Height
        {
            get { return _height; }
            set { _height = value; }
        }
       

        PictureBox _pic;

        public PictureBox Pic
        {
            get { return _pic; }
            set { _pic = value; }
        }

        int _direction;

        public int Direction
        {
            get { return _direction; }
            set { _direction = value; }
        }


        public ObjectTile(PictureBox pic, int id, String name, int posX, int posY, int direction)
        {
            _id = id;
            _name = name;
            _posX = posX;
            _posY = posY;
            _pic = pic;
            _width = pic.Width;
            _height = pic.Height;
            _direction = direction;
        }

        public ObjectTile(int id, String name, int posX, int posY, int width, int height, int direction)
        {
            _id = id;
            _name = name;
            _posX = posX;
            _posY = posY;
            _pic = null;
            _width = width;
            _height = height;
            _direction = direction;
        }

   }
}
