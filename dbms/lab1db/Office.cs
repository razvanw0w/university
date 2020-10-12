using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1db
{
    class Office
    {
        private int id;
        private String address;
        private int managerID;

        public Office(int id, string address, int managerID)
        {
            this.Id = id;
            this.address = address;
            this.managerID = managerID;
        }

        public int Id { get => id; set => id = value; }
        public string Address { get => address; set => address = value; }
        public int ManagerID { get => managerID; set => managerID = value; }
    }
}
