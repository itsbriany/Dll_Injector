using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;
using GUI.Properties;

namespace GUI
{
    public partial class Form : System.Windows.Forms.Form
    {

        private List<Target> _processes = new List<Target>();
        private string _dll_path;
        private int _selected_process;

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
                //Stream myStream = openFileDialog.OpenFile();
                SelectDllLabel.Text = openFileDialog.SafeFileName;

                if (SelectDllLabel.Text == null) return;

                _dll_path = openFileDialog.FileName;

            }
            catch (Exception ex)
            {
                MessageBox.Show(Resources.select_Dll_Button_Click_Error__Could_not_read_file_from_disk__Original_error__ + ex.Message);
            }
        }

        private void Form_Load(object sender, EventArgs e)
        {
            GetProcesses();
            InjectionProgressBar.Visible = true;
            InjectionProgressBar.Minimum = 0;
            InjectionProgressBar.Maximum = 2;
        }

        private void GetProcesses()
        {
            RemoveProcesses();
            var processes = Process.GetProcesses();
            foreach (var currentProcess in processes)
            {
                var targetProcess = new Target(currentProcess.ProcessName, currentProcess.Id);
                ProcessListBox.Items.Add(targetProcess.Name);
                PidListBox.Items.Add(targetProcess.Pid);
                _processes.Add(targetProcess);
            }
        }

        private void RemoveProcesses()
        {
            InjectionProgressBar.Value = 0;
            _processes.Clear();
            for (var n = ProcessListBox.Items.Count - 1; n >= 0; --n)
            {
                PidListBox.Items.RemoveAt(n);
                ProcessListBox.Items.RemoveAt(n);
            }
        }

        private void SearchProcessesTextField_TextChanged(object sender, EventArgs e)
        {
            var processSearch = SearchProcessesTextBox.Text;
            RemoveProcesses();
            var processes = Process.GetProcesses();
            foreach (var currentProcess in processes)
            {
                if (currentProcess.ToString().Contains(processSearch) || 
                    currentProcess.Id.ToString().Contains(processSearch))
                {
                    ProcessListBox.Items.Add(currentProcess.ProcessName);
                    PidListBox.Items.Add(currentProcess.Id);
                    _processes.Add(new Target(currentProcess.ProcessName, currentProcess.Id));
                }
            }

        }

        private void ProcessListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            var selectedIndex = ProcessListBox.SelectedIndex;
            PidListBox.SelectedIndex = selectedIndex;
            try
            {
                SelectProcessLabel.Text = _processes[selectedIndex].Name + ' ' + '(' + 
                    _processes[selectedIndex].Pid + ')';
                _selected_process= _processes[selectedIndex].Pid;
            }
            catch (Exception)
            {
                // ignored
            }
        }

        private void PidListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            var selectedIndex = PidListBox.SelectedIndex;
            ProcessListBox.SelectedIndex = selectedIndex;
            try
            {
                SelectProcessLabel.Text = _processes[selectedIndex].Name + ' ' + '(' +
                    _processes[selectedIndex].Pid + ')';
                _selected_process = _processes[selectedIndex].Pid;
            }
            catch (Exception)
            {
                // ignored
            }
        }

        private void InjectButton_Click(object sender, EventArgs e)
        {
            InjectionProgressBar.PerformStep();
            if (Injector.InjectDll(_selected_process))
            {
                InjectionStatusLabel.Text = Resources.resx_injectionSuccess;
                InjectionProgressBar.PerformStep();
                return;
            }
            InjectionStatusLabel.Text = Resources.resx_injectionFailed;
        }

        private void SearchProcessesTextBox_Enter(object sender, EventArgs e)
        {
            SearchProcessesTextBox.Text = "";
        }
    }
}
