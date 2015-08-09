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
            this.searchProcessesTextBox = new System.Windows.Forms.TextBox();
            this.InjectionStatusLabel = new System.Windows.Forms.Label();
            this.ProgressBar = new System.Windows.Forms.ProgressBar();
            this.InjectButton = new System.Windows.Forms.Button();
            this.ProcessListBox = new System.Windows.Forms.ListBox();
            this.SelectDllButton = new System.Windows.Forms.Button();
            this.SelectedDllLabel = new System.Windows.Forms.Label();
            this.SelectedProcessLabel = new System.Windows.Forms.Label();
            this.ProcessesLabel = new System.Windows.Forms.Label();
            this.PIDLabel = new System.Windows.Forms.Label();
            this.PidListBox = new System.Windows.Forms.ListBox();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.searchProcessesTextBox);
            this.panel1.Controls.Add(this.InjectionStatusLabel);
            this.panel1.Controls.Add(this.ProgressBar);
            this.panel1.Controls.Add(this.InjectButton);
            this.panel1.Location = new System.Drawing.Point(217, 225);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(221, 212);
            this.panel1.TabIndex = 0;
            // 
            // searchProcessesTextBox
            // 
            this.searchProcessesTextBox.Location = new System.Drawing.Point(18, 15);
            this.searchProcessesTextBox.Name = "searchProcessesTextBox";
            this.searchProcessesTextBox.Size = new System.Drawing.Size(190, 22);
            this.searchProcessesTextBox.TabIndex = 4;
            this.searchProcessesTextBox.Text = "Search Processes...";
            this.searchProcessesTextBox.TextChanged += new System.EventHandler(this.SearchProcessesTextField_TextChanged);
            // 
            // InjectionStatusLabel
            // 
            this.InjectionStatusLabel.AutoSize = true;
            this.InjectionStatusLabel.ForeColor = System.Drawing.Color.Red;
            this.InjectionStatusLabel.Location = new System.Drawing.Point(15, 185);
            this.InjectionStatusLabel.Name = "InjectionStatusLabel";
            this.InjectionStatusLabel.Size = new System.Drawing.Size(48, 17);
            this.InjectionStatusLabel.TabIndex = 3;
            this.InjectionStatusLabel.Text = "Status";
            // 
            // ProgressBar
            // 
            this.ProgressBar.ForeColor = System.Drawing.Color.Orange;
            this.ProgressBar.Location = new System.Drawing.Point(18, 157);
            this.ProgressBar.Name = "ProgressBar";
            this.ProgressBar.Size = new System.Drawing.Size(190, 23);
            this.ProgressBar.TabIndex = 2;
            // 
            // InjectButton
            // 
            this.InjectButton.Location = new System.Drawing.Point(18, 105);
            this.InjectButton.Name = "InjectButton";
            this.InjectButton.Size = new System.Drawing.Size(190, 30);
            this.InjectButton.TabIndex = 1;
            this.InjectButton.Text = "Inject!";
            this.InjectButton.UseVisualStyleBackColor = true;
            // 
            // ProcessListBox
            // 
            this.ProcessListBox.ForeColor = System.Drawing.Color.Black;
            this.ProcessListBox.FormattingEnabled = true;
            this.ProcessListBox.ItemHeight = 16;
            this.ProcessListBox.Location = new System.Drawing.Point(16, 225);
            this.ProcessListBox.Name = "ProcessListBox";
            this.ProcessListBox.Size = new System.Drawing.Size(98, 212);
            this.ProcessListBox.TabIndex = 1;
            this.ProcessListBox.SelectedIndexChanged += new System.EventHandler(this.ProcessListBox_SelectedIndexChanged);
            // 
            // SelectDllButton
            // 
            this.SelectDllButton.Location = new System.Drawing.Point(235, 22);
            this.SelectDllButton.Name = "SelectDllButton";
            this.SelectDllButton.Size = new System.Drawing.Size(190, 28);
            this.SelectDllButton.TabIndex = 2;
            this.SelectDllButton.Text = "Select a DLL";
            this.SelectDllButton.UseVisualStyleBackColor = true;
            this.SelectDllButton.Click += new System.EventHandler(this.selectDllButton_Click);
            // 
            // SelectedDllLabel
            // 
            this.SelectedDllLabel.AutoSize = true;
            this.SelectedDllLabel.ForeColor = System.Drawing.Color.Red;
            this.SelectedDllLabel.Location = new System.Drawing.Point(13, 28);
            this.SelectedDllLabel.Name = "SelectedDllLabel";
            this.SelectedDllLabel.Size = new System.Drawing.Size(115, 17);
            this.SelectedDllLabel.TabIndex = 3;
            this.SelectedDllLabel.Text = "No DLL Selected";
            // 
            // SelectedProcessLabel
            // 
            this.SelectedProcessLabel.AutoSize = true;
            this.SelectedProcessLabel.ForeColor = System.Drawing.Color.Red;
            this.SelectedProcessLabel.Location = new System.Drawing.Point(12, 68);
            this.SelectedProcessLabel.Name = "SelectedProcessLabel";
            this.SelectedProcessLabel.Size = new System.Drawing.Size(140, 17);
            this.SelectedProcessLabel.TabIndex = 4;
            this.SelectedProcessLabel.Text = "No Process Selected";
            // 
            // ProcessesLabel
            // 
            this.ProcessesLabel.AutoSize = true;
            this.ProcessesLabel.Location = new System.Drawing.Point(13, 184);
            this.ProcessesLabel.Name = "ProcessesLabel";
            this.ProcessesLabel.Size = new System.Drawing.Size(74, 17);
            this.ProcessesLabel.TabIndex = 5;
            this.ProcessesLabel.Text = "Processes";
            // 
            // PIDLabel
            // 
            this.PIDLabel.AutoSize = true;
            this.PIDLabel.Location = new System.Drawing.Point(150, 184);
            this.PIDLabel.Name = "PIDLabel";
            this.PIDLabel.Size = new System.Drawing.Size(37, 17);
            this.PIDLabel.TabIndex = 6;
            this.PIDLabel.Text = "PIDs";
            // 
            // PidListBox
            // 
            this.PidListBox.FormattingEnabled = true;
            this.PidListBox.ItemHeight = 16;
            this.PidListBox.Location = new System.Drawing.Point(133, 225);
            this.PidListBox.Name = "PidListBox";
            this.PidListBox.Size = new System.Drawing.Size(69, 212);
            this.PidListBox.TabIndex = 7;
            // 
            // Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(450, 449);
            this.Controls.Add(this.PidListBox);
            this.Controls.Add(this.PIDLabel);
            this.Controls.Add(this.ProcessesLabel);
            this.Controls.Add(this.SelectedProcessLabel);
            this.Controls.Add(this.SelectedDllLabel);
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
        private System.Windows.Forms.ProgressBar ProgressBar;
        private System.Windows.Forms.Button InjectButton;
        private System.Windows.Forms.Button SelectDllButton;
        private System.Windows.Forms.Label SelectedDllLabel;
        private System.Windows.Forms.Label InjectionStatusLabel;
        private System.Windows.Forms.Label SelectedProcessLabel;
        private System.Windows.Forms.TextBox searchProcessesTextBox;
        private System.Windows.Forms.Label ProcessesLabel;
        private System.Windows.Forms.Label PIDLabel;
        private System.Windows.Forms.ListBox PidListBox;
    }
}

