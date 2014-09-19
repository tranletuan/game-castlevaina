using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{
    public enum Location 
    {
        Root = 0, TopLeft, TopRight, BotLeft, BotRight
    };

    public class Node
    {
        /// <summary>
        /// Các thuộc tính cơ bản của 1 node bao gồm id, khung
        /// 4 node lá và danh sách đối tượng mà nó chứa
        /// </summary>
        private Int64 id;
        private Rectangle bounds;
        private Node top_left, top_right, bot_left, bot_right;
        private List<GameObject> list_object;

        public Node(Int64 parentID, Location loc, Rectangle bounds)
        {
            this.id = parentID * 10 + (int)loc;
            this.bounds = bounds;
            this.list_object = new List<GameObject>();
            this.top_left = null;
            this.top_right = null;
            this.bot_left = null;
            this.bot_right = null;
        }

        public bool Insert(GameObject go)
        {
            //Kiểm tra nếu diện tích giao nhau giữa khung bao đối tượng
            //và khung bao của node quá nhỏ thì xem như không có
            Rectangle inter_rect = Rectangle.Intersect(go.BOUNDS, this.bounds);

            if (inter_rect.Width < 3 || inter_rect.Height < 3)
            {
                return false;
            }

            //Nếu node mẹ không thể chia node con nữa thì đưa đối tượng
            //vào node mẹ và kết thúc
            if (bounds.Width <= Global.MIN_WIDTH * 2)
            {
                list_object.Add(go);
                return true;
            }
                
            //Khởi tạo các nút lá nếu chưa có 
            if (top_left == null)
            {
                int node_width = bounds.Width / 2;

                top_left = new Node(id, Location.TopLeft, new Rectangle(bounds.X, bounds.Y, node_width, node_width));
                top_right = new Node(id, Location.TopRight, new Rectangle(bounds.X + node_width, bounds.Y, node_width, node_width));
                bot_left = new Node(id, Location.BotLeft, new Rectangle(bounds.X, bounds.Y + node_width, node_width, node_width));
                bot_right = new Node(id, Location.BotRight, new Rectangle(bounds.X + node_width, bounds.Y + node_width, node_width, node_width));
            }

            top_left.Insert(go);
            top_right.Insert(go);
            bot_left.Insert(go);
            bot_right.Insert(go);

            return true;
        }

        public void Traversal(List<string> object_info, List<string> quadtree_info, List<int> list_id)
        {
            //Lấy thông tin node mẹ
            String parent_info = String.Format("{0} {1} {2} {3}", id, bounds.X, bounds.Y, bounds.Width);

            //Kiểm tra đệ quy các node lá
            if (top_left != null)
            {
                quadtree_info.Add(parent_info);
                top_left.Traversal(object_info, quadtree_info, list_id);
                top_right.Traversal(object_info, quadtree_info, list_id);
                bot_left.Traversal(object_info, quadtree_info, list_id);
                bot_right.Traversal(object_info, quadtree_info, list_id);
            }
            else
            {
                //Nếu là node lá cuối cùng thì lấy danh sách đối tượng.
                parent_info += " ";
                foreach (GameObject go in list_object)
                {
                    //Kiểm tra đối tượng có được thêm trước đó hay chưa
                    bool is_exist = false;

                    foreach (int o_id in list_id)
                    {
                        if (o_id == go.ID)
                        {
                            is_exist = true;
                            break;
                        }
                    }

                    //Nếu chưa duyệt qua đối tượng thì thêm ID đối tượng
                    //vào object_info
                    if (!is_exist)
                    {
                        list_id.Add(go.ID);
                        object_info.Add(go.ToString());
                    }

                    parent_info += go.ID + " ";
                }

                quadtree_info.Add(parent_info);
            }

        }
        
        public Rectangle BOUNDS
        {
            get { return bounds; }
        }

        public List<GameObject> List_Object
        {
            get { return list_object; }
        }
    }
}
