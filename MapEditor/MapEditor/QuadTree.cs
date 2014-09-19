using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{
    public class QuadTree
    {
        private Node root;
        private List<GameObject> list_object;

        public QuadTree(List<GameObject> list_objects, Rectangle bounds)
        {
            this.list_object = list_objects;
            root = new Node(0, Location.Root, bounds);
            BuidTree();
        }

        private void BuidTree()
        {
            foreach (GameObject o in list_object)
            {
                root.Insert(o);
            }
        }

        public void SaveQuaddTreeTo(string file_tree, string file_object)
        {
            List<string> quadtree_info = new List<string>();
            List<string> object_info = new List<string>();
            List<int> list_id = new List<int>();

            root.Traversal(object_info, quadtree_info, list_id);

            //Ghi file cây quadtree
            using (StreamWriter sw = new StreamWriter(file_tree, false))
            {
                sw.WriteLine(root.BOUNDS.Width.ToString());

                foreach (string node_info in quadtree_info)
                {
                    sw.WriteLine(node_info);
                }

                sw.Close();
            }

            //Ghi file đối tượng
            using (StreamWriter sw = new StreamWriter(file_object, false))
            {
                sw.WriteLine(object_info.Count.ToString());

                foreach (string o_info in object_info)
                {
                    sw.WriteLine(o_info);
                }

                sw.Close();
            }
        }
    }
}
