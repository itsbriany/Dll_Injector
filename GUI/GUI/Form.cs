using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;
using GUI.Properties;

namespace GUI
{
    public partial class Form : System.Windows.Forms.Form
    {

        private readonly List<Target> _processes = new List<Target>();
        private string _dllPath;
        private uint _selectedProcess;

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
                SelectDllLabel.Text = openFileDialog.SafeFileName;

                if (SelectDllLabel.Text == null) return;

                _dllPath = openFileDialog.FileName;

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
                var targetProcess = new Target(currentProcess.ProcessName, currentProcess.Id);
                ProcessListBox.Items.Add(targetProcess.Name);
                PidListBox.Items.Add(targetProcess.Pid);
                _processes.Add(targetProcess);
            }
        }

        private void RemoveProcesses()
        {
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
                _selectedProcess= (uint) _processes[selectedIndex].Pid;
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
                _selectedProcess = (uint) _processes[selectedIndex].Pid;
            }
            catch (Exception)
            {
                // ignored
            }
        }

        private void InjectButton_Click(object sender, EventArgs e)
        {
            InjectionStatusLabel.ForeColor = Color.Red;

            if (_selectedProcess == 0)
            {
                InjectionStatusLabel.Text = Resources.resx_selectProcessPrompt;
                return;
            }

            if (_dllPath == null)
            {
                InjectionStatusLabel.Text = Resources.resx_dllSelectionPrompt;
                return;
            }

            if (Injector.InjectDll(true, _selectedProcess, _dllPath))
            {
                InjectionStatusLabel.Text = Resources.resx_injectionSuccess;
                InjectionStatusLabel.ForeColor = Color.DarkGreen;
                InjectionStatusLabel.Font = new Font(InjectionStatusLabel.Font, FontStyle.Bold);
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
