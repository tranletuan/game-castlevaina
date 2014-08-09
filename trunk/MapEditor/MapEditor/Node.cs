using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{
    public enum Location { Root, TopLeft, TopRight, BottomLeft, BottomRight };

    public class Node
    {
        private int id;
        private Rectangle bounds;
        private Node tl, tr, bl, br;
        private List<Object> list_objects;

        public Node(int parentID, Location location, Rectangle bounds)
        {
            this.id = NodeID(parentID, location);
            this.bounds = bounds;
            this.list_objects = new List<Object>();
            tl = tr = bl = br = null;
        }

        private int NodeID(int parentID, Location location)
        {
            return parentID * Global.BIT_ID + (int)location;
        }

        public bool Add(Object ob)
        {
            //Kiểm tra khung bao node với khung bao của đối tượng
            Rectangle intersect_result = Rectangle.Intersect(ob.Bounds, bounds);

            //Nếu đối tượng và node giao nhau quá ít
            if (intersect_result.Width < 3 || intersect_result.Height < 3)
            {
                return false;
            }

            //Kiểm tra node mẹ còn có thể chia node con
            if (bounds.Width <= Global.MIN_WIDTH * 2)
            {
                list_objects.Add(ob);
                return true;
            }

            //Nếu chưa chia node con thì chia
            if (tl == null)
            {
                int x = bounds.X, y = bounds.Y, width = bounds.Width / 2;
                tl = new Node(id, Location.TopLeft, new Rectangle(x, y, width, width));
                tr = new Node(id, Location.TopRight, new Rectangle(x + width, y, width, width));
                bl = new Node(id, Location.BottomLeft, new Rectangle(x, y + width, width, width));
                br = new Node(id, Location.BottomRight, new Rectangle(x + width, y + width, width, width));
            }

            tl.Add(ob);
            tr.Add(ob);
            bl.Add(ob);
            br.Add(ob);

            return true;
        }

        public void Traversal(List<string> object_info, List<string> quadtree_info, List<Int32> list_id)
        {
            String parent_info = String.Format("{0} {1} {2} {3}", id, bounds.X, bounds.Y, bounds.Width);

            //Nếu node có các node con gọi đệ quy duyệt các node con
            if (tl != null)
            {
                quadtree_info.Add(parent_info);
                tl.Traversal(object_info, quadtree_info, list_id);
                tr.Traversal(object_info, quadtree_info, list_id);
                bl.Traversal(object_info, quadtree_info, list_id);
                br.Traversal(object_info, quadtree_info, list_id);
            }
            else
            {
                parent_info += " ";

                foreach (Object o in list_objects)
                {
                    //Kiểm tra id có bị lưu trùng hay không
                    //list_object để in ra map đối tượng
                    bool is_exist = false;

                    foreach (int i in list_id)
                    {
                        if (i == o.ID)
                        {
                            is_exist = true;
                            break;
                        }
                    }

                    if (!is_exist)
                    {
                        list_id.Add(o.ID);
                        object_info.Add(o.ToString());
                    }

                    parent_info += o.ID + " ";
                }

                quadtree_info.Add(parent_info);
            }

            
        }

        public Rectangle Bounds
        {
            get { return bounds; }
        }

        public List<Object> ListObjects
        {
            get { return list_objects; }
        }


    }
}
