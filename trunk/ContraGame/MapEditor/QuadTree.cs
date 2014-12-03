using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{
    class QuadTree
    {
        public const int WIDTH_VIEWPORT = 256;
        public const int HEIGHT_VIEWPORT = 240;

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

        List<QuadTreeNode> _listAllNode;

        internal List<QuadTreeNode> ListAllNode
        {
            get { return _listAllNode; }
            set { _listAllNode = value; }
        }

        List<QuadTreeNode> _listLeafNode;

        internal List<QuadTreeNode> ListLeafNode
        {
            get { return _listLeafNode; }
            set { _listLeafNode = value; }
        }



        public QuadTree(int w, int h)
        {
            _width = w;
            _height = h;
            _listAllNode = new List<QuadTreeNode>();
            _listLeafNode = new List<QuadTreeNode>();

        }
        // tao sub node tu node root
        public void createSubNode()
        {
            if (_width / 2 <= WIDTH_VIEWPORT || _height / 2 <= HEIGHT_VIEWPORT)
            {
                if (_width > _height)
                {
                    _height = _width;
                }
                else
                {
                    _width = _height;
                }
                QuadTreeNode nodeRoot = new QuadTreeNode("", 0, 0, _height, _width, _height);
                nodeRoot.SubDivide("", _listAllNode);
            }
            else
            {
                QuadTreeNode nodeRoot = new QuadTreeNode("", 0, 0, _height, _width, _height);
                // chia sub node
                nodeRoot.SubDivide("", _listAllNode);
                
            }
        }

        // chen object vo tree
        public void addObject(List<ObjectTile> listOB)
        {
            for (int i = 0; i < _listLeafNode.Count; i++)
            {
                for (int j = 0; j < listOB.Count; j++)
                {
                    if (AABBCheck(listOB.ElementAt(j),_listLeafNode.ElementAt(i)))
                    {
                        _listLeafNode.ElementAt(i).ListObject.Add(listOB.ElementAt(j));
                    }
                }
            }
        }

        // lay danh sach cac node la
        public void getListLeaf()
        {
            int levelMax = _listAllNode.ElementAt(_listAllNode.Count - 1).Id.Length / 2 + 1;
            for (int i = 0; i < _listAllNode.Count; i++)
            {
                if (levelMax == _listAllNode.ElementAt(i).Level)
                {
                    _listLeafNode.Add(_listAllNode.ElementAt(i));
                }
            }
        }

        // check ob nam trong node
        public bool AABBCheck(ObjectTile ob, QuadTreeNode node)
        {
            if (ob.Pic == null)
            {
                return false;
            }
            return !(ob.PosX + ob.Pic.Width < node.PosX || ob.PosX > node.PosX + node.Width || ob.PosY - ob.Pic.Height > node.PosY || ob.PosY < node.PosY - node.Height);
        }

       
    }
}
