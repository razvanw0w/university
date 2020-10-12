using assets_asp.Models;
using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace assets_asp.Communcation_Layer
{
    public class DataAccessLayer
    {
        public MySqlConnection getConnection()
        {
            string myConnectionString;
            myConnectionString = "server=localhost;database=test_php;uid=root;pwd=;";
            return new MySqlConnection(myConnectionString);
        }

        public int login(string user, string password)
        {
            List<int> users = new List<int>();

            try
            {
                MySqlConnection connection = getConnection();
                connection.Open();

                MySqlCommand command = new MySqlCommand();
                command.Connection = connection;
                command.CommandText = "select * from users where username='" + user + "'and password='" + password + "'";
                MySqlDataReader myreader = command.ExecuteReader();

                while (myreader.Read())
                {
                    users.Add(myreader.GetInt32("id"));
                }
                myreader.Close();
            }
            catch (MySqlException ex)
            {
                Console.Write(ex.Message);
                return -1;
            }
            
            if (users.Count == 1)
            {
                return users[0];
            }
            return -1;
        }

        public List<Asset> getAll(int userid)
        {
            List<Asset> assets = new List<Asset>();
            try
            {
                MySqlConnection connection = getConnection();
                connection.Open();

                MySqlCommand command = new MySqlCommand();
                command.Connection = connection;
                command.CommandText = "select * from assets where userid = " + userid.ToString();
                MySqlDataReader dataReader = command.ExecuteReader();

                while (dataReader.Read())
                {
                    int id = dataReader.GetInt32("id");
                    int uid = dataReader.GetInt32("userid");
                    string name = dataReader.GetString("name");
                    string description = dataReader.GetString("description");
                    int value = dataReader.GetInt32("value");
                    Asset asset = new Asset(id, uid, name, description, value);
                    assets.Add(asset);
                }
                dataReader.Close();
                connection.Close();
            }
            catch (MySqlException e)
            {
                System.Diagnostics.Debug.WriteLine(e.Message);
            }
            return assets;
        }

        public void add(int uid, string[] names, string[] descriptions, string[] values) {
            MySqlConnection connection = getConnection();
            connection.Open();

            int n = names.Length;
            for (int i = 0; i < n; ++i) {
                MySqlCommand command = new MySqlCommand();
                command.Connection = connection;

                command.CommandText = "INSERT INTO assets (userid,name,description,value) VALUES (" +
                    uid + ",\'" + names[i] + "\',\'" + descriptions[i] + "\'," + values[i] + ");";
                command.ExecuteNonQuery();
            }
            connection.Close();
        }
    }
}