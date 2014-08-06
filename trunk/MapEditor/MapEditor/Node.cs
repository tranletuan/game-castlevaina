using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapEditor
{
    enum Location { TopLeft, TopRight, BottomLeft, BottomRight, Root };

    public class Node
    {
        private List<Object> list_objects;
        private Location location;
        private int width;

        public Node(int width, Location location)
        {
            this.location = location;
            this.width = width;
        }
    }
}
