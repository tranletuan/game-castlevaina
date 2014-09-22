using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{

    public class GameObject
    {
        private Rectangle bounds;
        private string type;
        private int id;

        public GameObject()
        {
 
        }

        /// <summary>
        /// Khởi tạo đối tượng trên danh sách chọn
        /// </summary>
        /// <param name="type"></param>
        /// <param name="bounds"></param>
        public GameObject(string type, Rectangle bounds)
        {
            this.type = type;
            this.bounds = bounds;
            this.id = -1;
        }

        /// <summary>
        /// Khởi tạo đối tượng được vẽ trên map
        /// </summary>
        /// <param name="go"></param>
        /// <param name="position"></param>
        public GameObject(GameObject go, Point position)
        {
            this.id = Global.ID++;
            this.type = go.type;
            this.bounds = new Rectangle(position.X, position.Y, go.bounds.Width, go.bounds.Height);
        }

        public Rectangle BOUNDS
        {
            get { return bounds; }
        }

        public int ID
        {
            get { return id; }
        }

        public string TYPE
        {
            get { return type; }
        }

        public override string ToString()
        {
            return String.Format("{0} {1} {2} {3}", id, type, bounds.X, bounds.Y);
        }
    }

    public struct ObjectDraw
    {
        public GameObject Object;
        public Image Image;
        public Rectangle Bounds;
        public Point Position;

        public ObjectDraw(string type, Image image)
        {
            Image = image;
            Bounds = new Rectangle(0, 0, Image.Width, Image.Height);
            Object = new GameObject(type, Bounds);
            Position = Point.Empty;
        }
    };
}
