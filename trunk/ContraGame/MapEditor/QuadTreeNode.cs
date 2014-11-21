using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



namespace MapEditor
{
    class QuadTreeNode
    {
        public const int WIDTH_VIEWPORT = 256;
        public const int HEIGHT_VIEWPORT = 240;

        private String _id;

        public String Id
        {
            get { return _id; }
            set { _id = value; }
        }


        private int _posX;

        public int PosX
        {
            get { return _posX; }
            set { _posX = value; }
        }
        private int _posY;

        public int PosY
        {
            get { return _posY; }
            set { _posY = value; }
        }
        private int _width;

        public int Width
        {
            get { return _width; }
            set { _width = value; }
        }
        private int _height;

        public int Height
        {
            get { return _height; }
            set { _height = value; }
        }

        public QuadTreeNode(String id, int level, int posX, int posY, int width, int height)
        {
            _id = id;
            _posX = posX;
            _posY = posY;
            _width = width;
            _height = height;
            _nodelt = null;
            _nodert = null;
            _nodelb = null;
            _noderb = null;
            _level = level + 1;

            _listObject = new List<ObjectTile>();
        }

        private int _level;

        public int Level
        {
            get { return _level; }
            set { _level = value; }
        }


        private QuadTreeNode _nodelt;

        public QuadTreeNode Nodelt
        {
            get { return _nodelt; }
            set { _nodelt = value; }
        }
        private QuadTreeNode _nodert;

        public QuadTreeNode Nodert
        {
            get { return _nodert; }
            set { _nodert = value; }
        }
        private QuadTreeNode _nodelb;

        public QuadTreeNode Nodelb
        {
            get { return _nodelb; }
            set { _nodelb = value; }
        }
        private QuadTreeNode _noderb;

        public QuadTreeNode Noderb
        {
            get { return _noderb; }
            set { _noderb = value; }
        }

        List<ObjectTile> _listObject;

        internal List<ObjectTile> ListObject
        {
            get { return _listObject; }
            set { _listObject = value; }
        }


        public void SubDivide(String idParent, List<QuadTreeNode> listNode)
        {

            bool result = true;

            int x = _posX;
            int y = _posY;
            int w = _width / 2;
            int h = _height / 2;

            if (_width / 2 <= WIDTH_VIEWPORT || _height / 2 <= HEIGHT_VIEWPORT)
            {
                result = false;
            }

            if (result)
            {
                _nodelb = new QuadTreeNode(_id + "01", _level, x, y - h, w, h); // node left bottom
                _noderb = new QuadTreeNode(_id + "11", _level, x + w, y - h, w, h); // node right bottom
                _nodert = new QuadTreeNode(_id + "10", _level, x + w, y, w, h); // node right top
                _nodelt = new QuadTreeNode(_id + "00", _level, x, y, w, h); // node left top

                listNode.Add(_nodelt);
                listNode.Add(_nodert);
                listNode.Add(_nodelb);
                listNode.Add(_noderb);

            }

            if (_width / 4 <= WIDTH_VIEWPORT || _height / 4 <= HEIGHT_VIEWPORT)
            {
                result = false;
            }

            if (result)
            {
                _nodelt.SubDivide(_id, listNode);
                _nodert.SubDivide(_id, listNode);
                _nodelb.SubDivide(_id, listNode);
                _noderb.SubDivide(_id, listNode);
            }


        }






    }
}
