using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Configuration;
using System.Diagnostics;

namespace lab1db
{
    public partial class Form1 : Form
    {
        private BindingSource bindingSourceParent;
        private BindingSource bindingSourceChild;
        private String connectionString = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
        private String currentState = "0";
        private Label[] labels;
        private TextBox[] textBoxes;
        private int numberOfColumns;
        private string[] columnNames;
        private string[] columnTypes;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            numberOfColumns = Int32.Parse(ConfigurationManager.AppSettings["ChildNumberOfColumns" + currentState]);
            columnTypes = (ConfigurationManager.AppSettings["ChildColumnTypes" + currentState].Split(','));
            columnNames = (ConfigurationManager.AppSettings["ChildLabelNames" + currentState].Split(','));
            populatePanel();
        }

        private void populatePanel()
        {
            panel1.Controls.Clear();
            int numberOfColumns = Int32.Parse(ConfigurationManager.AppSettings["ChildNumberOfColumns" + currentState]);
            labels = new Label[numberOfColumns - 1];
            textBoxes = new TextBox[numberOfColumns - 1];
            string[] columns = (ConfigurationManager.AppSettings["ChildLabelNames" + currentState].Split(','));
            for (int i = 0; i < numberOfColumns - 1; ++i)
            {
                labels[i] = new Label();
                textBoxes[i] = new TextBox();
                labels[i].Text = columns[i];
                textBoxes[i].Text = "";
            }

            for (int i = 0; i < numberOfColumns - 1; ++i)
            {
                panel1.Controls.Add(labels[i]);
                panel1.Controls.Add(textBoxes[i]);
            }
        }

        private void getParentData()
        {
            /*SqlConnection databaseConnection = new SqlConnection(connectionString);
            DataSet dataSet = new DataSet();

            SqlDataAdapter managersDataAdapter = new SqlDataAdapter("select * from managers", databaseConnection);
            managersDataAdapter.Fill(dataSet, "managers");

            bindingSourceManagers = new BindingSource(dataSet, "managers");
            dgvManagers.DataSource = bindingSourceManagers;*/
            SqlConnection databaseConnection = new SqlConnection(connectionString);
            DataSet dataSet = new DataSet();

            string query = ConfigurationManager.AppSettings["SelectParent" + currentState];
            string parent = ConfigurationManager.AppSettings["ParentTableName" + currentState];
            SqlDataAdapter dataAdapter = new SqlDataAdapter(query, databaseConnection);
            dataAdapter.Fill(dataSet, parent);

            bindingSourceParent = new BindingSource(dataSet, parent);
            dgvManagers.DataSource = bindingSourceParent;
        }

        private void displayManagersButton_Click(object sender, EventArgs e)
        {
            getParentData();
        }

        private void addOfficeButton_Click(object sender, EventArgs e)
        {
            try
            {
                int rows = executeChildInsertion();
                if (rows == 0)
                    MessageBox.Show("No rows were affected!");
                refreshChildTable();
            }
            catch (SqlException exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private int executeChildInsertion()
        {
            /*Office office = getUserOffice();
            SqlConnection databaseConnection = new SqlConnection(connectionString);

            SqlCommand command = new SqlCommand("insert into offices values (@address, @managerid)", databaseConnection);
            SqlParameter address = new SqlParameter();
            SqlParameter managerid = new SqlParameter();
            address.ParameterName = "@address"; address.DbType = DbType.String; address.Value = office.Address;
            managerid.ParameterName = "@managerid"; managerid.DbType = DbType.Int32; managerid.Value = office.ManagerID;
            command.Parameters.Add(address);
            command.Parameters.Add(managerid);
            databaseConnection.Open();
            int rows = command.ExecuteNonQuery();
            databaseConnection.Close();
            return rows;*/
            SqlConnection databaseConnection = new SqlConnection(connectionString);
            string query = ConfigurationManager.AppSettings["InsertQuery" + currentState];
            SqlCommand command = new SqlCommand(query, databaseConnection);

            for (int i = 1; i < numberOfColumns - 1; ++i)
            {
                SqlParameter parameter = new SqlParameter();
                parameter.ParameterName = "@" + columnNames[i];

                string text = textBoxes[i].Text;
                if (columnTypes[i] == "int")
                {
                    parameter.DbType = DbType.Int32;
                    parameter.Value = Int32.Parse(text);
                }
                else
                {
                    parameter.DbType = DbType.String;
                    parameter.Value = text;
                }
                command.Parameters.Add(parameter);
            }

            SqlParameter parentID = new SqlParameter();
            parentID.ParameterName = "@" + columnNames[numberOfColumns - 1]; // parent id
            parentID.DbType = DbType.Int32;
            parentID.Value = getSelectedParentID();
            command.Parameters.Add(parentID);

            databaseConnection.Open();
            int rows = command.ExecuteNonQuery();
            databaseConnection.Close();
            return rows;
        }

        private int getSelectedParentID()
        {
            DataGridViewRow selectedRow = dgvManagers.SelectedRows[0];
            int id = (int)selectedRow.Cells[0].Value;
            return id;
        }

        private void dgvManagers_Click(object sender, EventArgs e)
        {
            refreshChildTable();
        }

        private void refreshChildTable()
        {
            /*SqlConnection databaseConnection = new SqlConnection(connectionString);
            DataSet dataSet = new DataSet();

            int id = getSelectedManagerID();
            SqlCommand command = new SqlCommand("select * from offices where managerID = @id", databaseConnection);
            SqlParameter parameter = new SqlParameter();
            parameter.ParameterName = "@id";
            parameter.DbType = DbType.Int32;
            parameter.Value = id;
            command.Parameters.Add(parameter);

            SqlDataAdapter officesDataAdapter = new SqlDataAdapter(command);
            officesDataAdapter.Fill(dataSet, "offices");
            bindingSourceOffices = new BindingSource(dataSet, "offices");
            dgvOffices.DataSource = bindingSourceOffices;*/
            SqlConnection databaseConnection = new SqlConnection(connectionString);
            DataSet dataSet = new DataSet();

            int id = getSelectedParentID();
            string query = ConfigurationManager.AppSettings["SelectChild" + currentState];
            string child = ConfigurationManager.AppSettings["ChildTableName" + currentState];
            
            SqlCommand command = new SqlCommand(query, databaseConnection);
            SqlParameter parameter = new SqlParameter();
            parameter.ParameterName = "@" + columnNames[numberOfColumns - 1];
            parameter.DbType = DbType.Int32;
            parameter.Value = id;
            command.Parameters.Add(parameter);

            SqlDataAdapter dataAdapter = new SqlDataAdapter(command);
            dataAdapter.Fill(dataSet, child);
            bindingSourceChild = new BindingSource(dataSet, child);
            dgvOffices.DataSource = bindingSourceChild;
        }

        private void removeOfficeButton_Click(object sender, EventArgs e)
        {
            try
            {
                int rows = executeChildDeletion();
                if (rows == 0)
                    MessageBox.Show("No rows were affected! Probably, the desired record doesn't exist!");
                refreshChildTable();
            }
            catch (SqlException exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private int executeChildDeletion()
        {
            /*Office office = getUserOffice();
            SqlConnection databaseConnection = new SqlConnection(connectionString);

            SqlCommand command = new SqlCommand("delete from offices where id = @id and managerID = @managerid", databaseConnection);
            SqlParameter id = new SqlParameter();
            SqlParameter managerid = new SqlParameter();
            id.ParameterName = "@id"; id.DbType = DbType.Int32; id.Value = office.Id;
            managerid.ParameterName = "@managerid"; managerid.DbType = DbType.Int32; managerid.Value = office.ManagerID;
            command.Parameters.Add(id);
            command.Parameters.Add(managerid);
            databaseConnection.Open();
            int rows = command.ExecuteNonQuery();
            databaseConnection.Close();
            return rows;*/
            SqlConnection databaseConnection = new SqlConnection(connectionString);
            string query = ConfigurationManager.AppSettings["DeleteChild" + currentState];
            SqlCommand command = new SqlCommand(query, databaseConnection);
            SqlParameter childID = new SqlParameter();
            SqlParameter parentID = new SqlParameter();

            childID.ParameterName = "@" + columnNames[0];
            childID.DbType = columnTypes[0] == "int" ? DbType.Int32 : DbType.String;
            if (columnTypes[0] == "int")
                childID.Value = Int32.Parse(textBoxes[0].Text);
            else
                childID.Value = textBoxes[0].Text;

            parentID.ParameterName = "@" + columnNames[numberOfColumns - 1];
            parentID.DbType = columnTypes[numberOfColumns - 1] == "int" ? DbType.Int32 : DbType.String;
            parentID.Value = getSelectedParentID();

            command.Parameters.Add(childID);
            command.Parameters.Add(parentID);
            databaseConnection.Open();
            int rows = command.ExecuteNonQuery();
            databaseConnection.Close();
            return rows;
        }

        private int executeChildUpdation()
        {
            /*Office office = getUserOffice();
            SqlConnection databaseConnection = new SqlConnection(connectionString);

            SqlCommand command = new SqlCommand("update offices set officeAddress = @address where id = @id and managerID = @managerid", databaseConnection);
            SqlParameter id = new SqlParameter();
            SqlParameter address = new SqlParameter();
            SqlParameter managerid = new SqlParameter();
            id.ParameterName = "@id"; id.DbType = DbType.Int32; id.Value = office.Id;
            address.ParameterName = "@address"; address.DbType = DbType.String; address.Value = office.Address;
            managerid.ParameterName = "@managerid"; managerid.DbType = DbType.Int32; managerid.Value = office.ManagerID;
            command.Parameters.Add(id);
            command.Parameters.Add(address);
            command.Parameters.Add(managerid);
            databaseConnection.Open();
            int rows = command.ExecuteNonQuery();
            databaseConnection.Close();
            return rows;*/
            SqlConnection databaseConnection = new SqlConnection(connectionString);
            string query = ConfigurationManager.AppSettings["UpdateQuery" + currentState];
            SqlCommand command = new SqlCommand(query, databaseConnection);

            for (int i = 0; i < numberOfColumns - 1; ++i)
            {
                SqlParameter parameter = new SqlParameter();
                parameter.ParameterName = "@" + columnNames[i];

                string text = textBoxes[i].Text;
                if (columnTypes[i] == "int")
                {
                    parameter.DbType = DbType.Int32;
                    parameter.Value = Int32.Parse(text);
                }
                else
                {
                    parameter.DbType = DbType.String;
                    parameter.Value = text;
                }
                command.Parameters.Add(parameter);
            }

            SqlParameter parentID = new SqlParameter();
            parentID.ParameterName = "@" + columnNames[numberOfColumns - 1]; // parent id
            parentID.DbType = DbType.Int32;
            parentID.Value = getSelectedParentID();
            command.Parameters.Add(parentID);

            databaseConnection.Open();
            int rows = command.ExecuteNonQuery();
            databaseConnection.Close();
            return rows;
        }

        private void updateOfficeButton_Click(object sender, EventArgs e)
        {
            try
            {
                int rows = executeChildUpdation();
                if (rows == 0)
                    MessageBox.Show("No rows were affected! Probably, the desired record doesn't exist!");
                refreshChildTable();
            }
            catch (SqlException exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        private void switchButton_Click(object sender, EventArgs e)
        {
            if (currentState == "0") {
                currentState = "1";
            }
            else
            {
                currentState = "0";
            }
            numberOfColumns = Int32.Parse(ConfigurationManager.AppSettings["ChildNumberOfColumns" + currentState]);
            columnTypes = (ConfigurationManager.AppSettings["ChildColumnTypes" + currentState].Split(','));
            columnNames = (ConfigurationManager.AppSettings["ChildLabelNames" + currentState].Split(','));
            populatePanel();
            getParentData();
        }
    }
}
