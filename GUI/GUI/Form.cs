using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;
using GUI.Properties;

namespace GUI
{
    public partial class Form : System.Windows.Forms.Form
    {
        public Form()
        {
            InitializeComponent();
        }

        private void selectDllButton_Click(object sender, EventArgs e)
        {
            var openFileDialog = new OpenFileDialog
            {
                Filter = Resources.DLL_File_Type,
                FilterIndex = 2,
                RestoreDirectory = true
            };

            if (openFileDialog.ShowDialog() != DialogResult.OK) return;

            try
            {
                Stream myStream = openFileDialog.OpenFile();
                using (myStream)
                {
                    // Insert code to read the stream here.
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(Resources.select_Dll_Button_Click_Error__Could_not_read_file_from_disk__Original_error__ + ex.Message);
            }
        }

        private void Form_Load(object sender, EventArgs e)
        {
            GetProcesses();
        }

        private void GetProcesses()
        {
            RemoveProcesses();
            var processes = Process.GetProcesses();
            foreach (var currentProcess in processes)
            {
                ProcessListBox.Items.Add(currentProcess.ProcessName);
                PidListBox.Items.Add(currentProcess.Id);
            }
        }

        private void RemoveProcesses()
        {
            for (var n = ProcessListBox.Items.Count - 1; n >= 0; --n)
            {
                PidListBox.Items.RemoveAt(n);
                ProcessListBox.Items.RemoveAt(n);
            }
        }

        private void SearchProcessesTextField_TextChanged(object sender, EventArgs e)
        {
            var processName = searchProcessesTextBox.Text;
            RemoveProcesses();
            var processes = Process.GetProcesses();
            foreach (var currentProcess in processes)
            {
                if (currentProcess.ToString().Contains(processName))
                {
                    ProcessListBox.Items.Add(currentProcess.ProcessName);
                    PidListBox.Items.Add(currentProcess.Id);
                }
            }

        }

        private void ProcessListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            var processLabel = ProcessListBox.SelectedItem as string;
            
            var processes = Process.GetProcesses();
            for (var i = 0; i < processes.Length; i++)
            {
                if (processes[i].ToString() == processLabel)
                {
                    PidListBox.SetSelected(i, true);
                    InjectionStatusLabel.Text = PidListBox.SelectedItem as string;
                }
            }
        }

    }
}
