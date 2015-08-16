namespace GUI
{
    partial class Form
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.SearchProcessesTextBox = new System.Windows.Forms.TextBox();
            this.InjectionStatusLabel = new System.Windows.Forms.Label();
            this.InjectButton = new System.Windows.Forms.Button();
            this.ProcessListBox = new System.Windows.Forms.ListBox();
            this.SelectDllButton = new System.Windows.Forms.Button();
            this.InjectingLabel = new System.Windows.Forms.Label();
            this.IntoProcessLabel = new System.Windows.Forms.Label();
            this.ProcessesLabel = new System.Windows.Forms.Label();
            this.PIDLabel = new System.Windows.Forms.Label();
            this.PidListBox = new System.Windows.Forms.ListBox();
            this.SelectDllLabel = new System.Windows.Forms.Label();
            this.SelectProcessLabel = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.SearchProcessesTextBox);
            this.panel1.Controls.Add(this.InjectionStatusLabel);
            this.panel1.Controls.Add(this.InjectButton);
            this.panel1.Location = new System.Drawing.Point(435, 225);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(223, 212);
            this.panel1.TabIndex = 0;
            // 
            // SearchProcessesTextBox
            // 
            this.SearchProcessesTextBox.Location = new System.Drawing.Point(18, 15);
            this.SearchProcessesTextBox.Name = "SearchProcessesTextBox";
            this.SearchProcessesTextBox.Size = new System.Drawing.Size(190, 22);
            this.SearchProcessesTextBox.TabIndex = 4;
            this.SearchProcessesTextBox.Text = "Search Processes...";
            this.SearchProcessesTextBox.TextChanged += new System.EventHandler(this.SearchProcessesTextField_TextChanged);
            this.SearchProcessesTextBox.Enter += new System.EventHandler(this.SearchProcessesTextBox_Enter);
            // 
            // InjectionStatusLabel
            // 
            this.InjectionStatusLabel.AutoSize = true;
            this.InjectionStatusLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.InjectionStatusLabel.ForeColor = System.Drawing.Color.Red;
            this.InjectionStatusLabel.Location = new System.Drawing.Point(15, 185);
            this.InjectionStatusLabel.Name = "InjectionStatusLabel";
            this.InjectionStatusLabel.Size = new System.Drawing.Size(0, 20);
            this.InjectionStatusLabel.TabIndex = 3;
            // 
            // InjectButton
            // 
            this.InjectButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.InjectButton.Location = new System.Drawing.Point(12, 54);
            this.InjectButton.Name = "InjectButton";
            this.InjectButton.Size = new System.Drawing.Size(190, 30);
            this.InjectButton.TabIndex = 1;
            this.InjectButton.Text = "Inject!";
            this.InjectButton.UseVisualStyleBackColor = false;
            this.InjectButton.Click += new System.EventHandler(this.InjectButton_Click);
            // 
            // ProcessListBox
            // 
            this.ProcessListBox.ForeColor = System.Drawing.Color.Black;
            this.ProcessListBox.FormattingEnabled = true;
            this.ProcessListBox.ItemHeight = 16;
            this.ProcessListBox.Location = new System.Drawing.Point(16, 225);
            this.ProcessListBox.Name = "ProcessListBox";
            this.ProcessListBox.Size = new System.Drawing.Size(257, 212);
            this.ProcessListBox.TabIndex = 1;
            this.ProcessListBox.SelectedIndexChanged += new System.EventHandler(this.ProcessListBox_SelectedIndexChanged);
            // 
            // SelectDllButton
            // 
            this.SelectDllButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.SelectDllButton.Location = new System.Drawing.Point(447, 184);
            this.SelectDllButton.Name = "SelectDllButton";
            this.SelectDllButton.Size = new System.Drawing.Size(196, 28);
            this.SelectDllButton.TabIndex = 2;
            this.SelectDllButton.Text = "Select a DLL";
            this.SelectDllButton.UseVisualStyleBackColor = false;
            this.SelectDllButton.Click += new System.EventHandler(this.selectDllButton_Click);
            // 
            // InjectingLabel
            // 
            this.InjectingLabel.AutoSize = true;
            this.InjectingLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.InjectingLabel.ForeColor = System.Drawing.Color.DarkGreen;
            this.InjectingLabel.Location = new System.Drawing.Point(13, 28);
            this.InjectingLabel.Name = "InjectingLabel";
            this.InjectingLabel.Size = new System.Drawing.Size(80, 24);
            this.InjectingLabel.TabIndex = 3;
            this.InjectingLabel.Text = "Injecting";
            // 
            // IntoProcessLabel
            // 
            this.IntoProcessLabel.AutoSize = true;
            this.IntoProcessLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.IntoProcessLabel.ForeColor = System.Drawing.Color.DarkGreen;
            this.IntoProcessLabel.Location = new System.Drawing.Point(13, 69);
            this.IntoProcessLabel.Name = "IntoProcessLabel";
            this.IntoProcessLabel.Size = new System.Drawing.Size(103, 20);
            this.IntoProcessLabel.TabIndex = 4;
            this.IntoProcessLabel.Text = "Into Process";
            // 
            // ProcessesLabel
            // 
            this.ProcessesLabel.AutoSize = true;
            this.ProcessesLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ProcessesLabel.Location = new System.Drawing.Point(13, 184);
            this.ProcessesLabel.Name = "ProcessesLabel";
            this.ProcessesLabel.Size = new System.Drawing.Size(89, 20);
            this.ProcessesLabel.TabIndex = 5;
            this.ProcessesLabel.Text = "Processes";
            // 
            // PIDLabel
            // 
            this.PIDLabel.AutoSize = true;
            this.PIDLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PIDLabel.Location = new System.Drawing.Point(308, 184);
            this.PIDLabel.Name = "PIDLabel";
            this.PIDLabel.Size = new System.Drawing.Size(46, 20);
            this.PIDLabel.TabIndex = 6;
            this.PIDLabel.Text = "PIDs";
            // 
            // PidListBox
            // 
            this.PidListBox.FormattingEnabled = true;
            this.PidListBox.ItemHeight = 16;
            this.PidListBox.Location = new System.Drawing.Point(294, 225);
            this.PidListBox.Name = "PidListBox";
            this.PidListBox.Size = new System.Drawing.Size(135, 212);
            this.PidListBox.TabIndex = 7;
            this.PidListBox.SelectedIndexChanged += new System.EventHandler(this.PidListBox_SelectedIndexChanged);
            // 
            // SelectDllLabel
            // 
            this.SelectDllLabel.AutoSize = true;
            this.SelectDllLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SelectDllLabel.Location = new System.Drawing.Point(130, 28);
            this.SelectDllLabel.Name = "SelectDllLabel";
            this.SelectDllLabel.Size = new System.Drawing.Size(142, 20);
            this.SelectDllLabel.TabIndex = 8;
            this.SelectDllLabel.Text = "No DLL Specified";
            // 
            // SelectProcessLabel
            // 
            this.SelectProcessLabel.AutoSize = true;
            this.SelectProcessLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SelectProcessLabel.Location = new System.Drawing.Point(133, 69);
            this.SelectProcessLabel.Name = "SelectProcessLabel";
            this.SelectProcessLabel.Size = new System.Drawing.Size(167, 20);
            this.SelectProcessLabel.TabIndex = 9;
            this.SelectProcessLabel.Text = "No Process Selected";
            // 
            // Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(686, 449);
            this.Controls.Add(this.SelectProcessLabel);
            this.Controls.Add(this.SelectDllLabel);
            this.Controls.Add(this.PidListBox);
            this.Controls.Add(this.PIDLabel);
            this.Controls.Add(this.ProcessesLabel);
            this.Controls.Add(this.IntoProcessLabel);
            this.Controls.Add(this.InjectingLabel);
            this.Controls.Add(this.SelectDllButton);
            this.Controls.Add(this.ProcessListBox);
            this.Controls.Add(this.panel1);
            this.Name = "Form";
            this.Text = "DLL Injector";
            this.Load += new System.EventHandler(this.Form_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ListBox ProcessListBox;
        private System.Windows.Forms.Button InjectButton;
        private System.Windows.Forms.Button SelectDllButton;
        private System.Windows.Forms.Label InjectingLabel;
        private System.Windows.Forms.Label InjectionStatusLabel;
        private System.Windows.Forms.Label IntoProcessLabel;
        private System.Windows.Forms.TextBox SearchProcessesTextBox;
        private System.Windows.Forms.Label ProcessesLabel;
        private System.Windows.Forms.Label PIDLabel;
        private System.Windows.Forms.ListBox PidListBox;
        private System.Windows.Forms.Label SelectDllLabel;
        private System.Windows.Forms.Label SelectProcessLabel;
    }
}

