namespace lab1db
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.displayParentRecordsButton = new System.Windows.Forms.Button();
            this.addOfficeButton = new System.Windows.Forms.Button();
            this.dgvManagers = new System.Windows.Forms.DataGridView();
            this.dgvOffices = new System.Windows.Forms.DataGridView();
            this.removeOfficeButton = new System.Windows.Forms.Button();
            this.updateOfficeButton = new System.Windows.Forms.Button();
            this.switchButton = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.FlowLayoutPanel();
            ((System.ComponentModel.ISupportInitialize)(this.dgvManagers)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvOffices)).BeginInit();
            this.SuspendLayout();
            // 
            // displayParentRecordsButton
            // 
            this.displayParentRecordsButton.Location = new System.Drawing.Point(853, 12);
            this.displayParentRecordsButton.Name = "displayParentRecordsButton";
            this.displayParentRecordsButton.Size = new System.Drawing.Size(183, 23);
            this.displayParentRecordsButton.TabIndex = 2;
            this.displayParentRecordsButton.Text = "Display all parent records";
            this.displayParentRecordsButton.UseVisualStyleBackColor = true;
            this.displayParentRecordsButton.Click += new System.EventHandler(this.displayManagersButton_Click);
            // 
            // addOfficeButton
            // 
            this.addOfficeButton.Location = new System.Drawing.Point(891, 333);
            this.addOfficeButton.Name = "addOfficeButton";
            this.addOfficeButton.Size = new System.Drawing.Size(118, 23);
            this.addOfficeButton.TabIndex = 9;
            this.addOfficeButton.Text = "Add";
            this.addOfficeButton.UseVisualStyleBackColor = true;
            this.addOfficeButton.Click += new System.EventHandler(this.addOfficeButton_Click);
            // 
            // dgvManagers
            // 
            this.dgvManagers.AllowUserToAddRows = false;
            this.dgvManagers.AllowUserToDeleteRows = false;
            this.dgvManagers.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvManagers.Location = new System.Drawing.Point(12, 12);
            this.dgvManagers.Name = "dgvManagers";
            this.dgvManagers.ReadOnly = true;
            this.dgvManagers.Size = new System.Drawing.Size(381, 411);
            this.dgvManagers.TabIndex = 10;
            this.dgvManagers.Click += new System.EventHandler(this.dgvManagers_Click);
            // 
            // dgvOffices
            // 
            this.dgvOffices.AllowUserToAddRows = false;
            this.dgvOffices.AllowUserToDeleteRows = false;
            this.dgvOffices.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvOffices.Location = new System.Drawing.Point(399, 12);
            this.dgvOffices.Name = "dgvOffices";
            this.dgvOffices.ReadOnly = true;
            this.dgvOffices.Size = new System.Drawing.Size(369, 411);
            this.dgvOffices.TabIndex = 11;
            // 
            // removeOfficeButton
            // 
            this.removeOfficeButton.Location = new System.Drawing.Point(891, 362);
            this.removeOfficeButton.Name = "removeOfficeButton";
            this.removeOfficeButton.Size = new System.Drawing.Size(118, 23);
            this.removeOfficeButton.TabIndex = 12;
            this.removeOfficeButton.Text = "Remove";
            this.removeOfficeButton.UseVisualStyleBackColor = true;
            this.removeOfficeButton.Click += new System.EventHandler(this.removeOfficeButton_Click);
            // 
            // updateOfficeButton
            // 
            this.updateOfficeButton.Location = new System.Drawing.Point(891, 391);
            this.updateOfficeButton.Name = "updateOfficeButton";
            this.updateOfficeButton.Size = new System.Drawing.Size(118, 23);
            this.updateOfficeButton.TabIndex = 13;
            this.updateOfficeButton.Text = "Update";
            this.updateOfficeButton.UseVisualStyleBackColor = true;
            this.updateOfficeButton.Click += new System.EventHandler(this.updateOfficeButton_Click);
            // 
            // switchButton
            // 
            this.switchButton.Location = new System.Drawing.Point(891, 420);
            this.switchButton.Name = "switchButton";
            this.switchButton.Size = new System.Drawing.Size(118, 23);
            this.switchButton.TabIndex = 15;
            this.switchButton.Text = "Switch scenario";
            this.switchButton.UseVisualStyleBackColor = true;
            this.switchButton.Click += new System.EventHandler(this.switchButton_Click);
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(832, 55);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(221, 272);
            this.panel1.TabIndex = 16;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1104, 455);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.switchButton);
            this.Controls.Add(this.updateOfficeButton);
            this.Controls.Add(this.removeOfficeButton);
            this.Controls.Add(this.dgvOffices);
            this.Controls.Add(this.dgvManagers);
            this.Controls.Add(this.addOfficeButton);
            this.Controls.Add(this.displayParentRecordsButton);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvManagers)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvOffices)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button displayParentRecordsButton;
        private System.Windows.Forms.Button addOfficeButton;
        private System.Windows.Forms.DataGridView dgvManagers;
        private System.Windows.Forms.DataGridView dgvOffices;
        private System.Windows.Forms.Button removeOfficeButton;
        private System.Windows.Forms.Button updateOfficeButton;
        private System.Windows.Forms.Button switchButton;
        private System.Windows.Forms.FlowLayoutPanel panel1;
    }
}

