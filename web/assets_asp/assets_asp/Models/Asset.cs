using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace assets_asp.Models
{
    public class Asset
    {
        private int id;
        private int userid;
        private string name;
        private string description;
        private int value;

        public Asset(int id, int userid, string name, string description, int value)
        {
            this.id = id;
            this.userid = userid;
            this.name = name;
            this.description = description;
            this.value = value;
            this.Id = id;
            this.Userid = userid;
            this.Name = name;
            this.Description = description;
            this.Value = value;
        }

        public int Id { get => id; set => id = value; }
        public int Userid { get => userid; set => userid = value; }
        public string Name { get => name; set => name = value; }
        public string Description { get => description; set => description = value; }
        public int Value { get => value; set => this.value = value; }
    }
}