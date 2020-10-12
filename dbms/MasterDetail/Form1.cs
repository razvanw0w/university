using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MasterDetail
{
    public partial class Form1 : Form
    {
        private BindingSource bsGroups, bsStudents;
        private SqlDataAdapter daGroups, daStudents;
        private DataSet ds = new DataSet();
        private SqlCommandBuilder commandBuilder;
        public Form1()
        {
            InitializeComponent();
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            commandBuilder = new SqlCommandBuilder(daStudents);
            // call the respective insert/update/delete statements for each updated/inserted/deleted row in the dataset ds from table Students (child)
            daStudents.Update(ds, "Students");
            MessageBox.Show("Changes done were stored in the database! Thank you!");
        }

        private void GetData()
        {
            String connectionString = "Data Source=DESKTOP-5KGUQL0\\SQLEXPRESS;Initial Catalog=StudentLabAssignments5;Integrated Security=True";
            SqlConnection conn = new SqlConnection(connectionString);

            // get all groups
            daGroups = new SqlDataAdapter("SELECT * from Groups", conn);
            // fill the dataset with table 'Groups' from the freshly updated data adapter (with select query)
            daGroups.Fill(ds, "Groups");
            // update the binding source from which the DGVs will fetch the content
            bsGroups = new BindingSource(ds, "Groups");

            // very similar to above
            daStudents = new SqlDataAdapter("SELECT * FROM Students", conn);
            daStudents.Fill(ds, "Students");
            // define the parent-child relation
            DataRelation dr = new DataRelation("GroupsStudents",
                ds.Tables["Groups"].Columns["id"],
                ds.Tables["Students"].Columns["group_id"]);
            ds.Relations.Add(dr);
            // set the binding source to show only students from some group (students respecting the relation with the currently selected group record)
            bsStudents = new BindingSource(bsGroups, "GroupsStudents");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            GetData();
            // set binding sources as data sources to the DGVs
            dgvGroups.DataSource = bsGroups;
            dgvStudents.DataSource = bsStudents;
        }
    }
}
