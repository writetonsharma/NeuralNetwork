using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;



namespace NNGUI
{
    public partial class ProgressDialog : Form
    {

        private BackgroundWorker m_NNBackgroundWorker;      // worker
        private BackgroundWorker m_NNBackgroundProgressUpdater;     // updates the GUI with progress
        private string m_configPath;
        private uint m_dataSize;
        private uint m_progress;



        [DllImport(@"../Dll/NeuralNetwork.dll",
        CallingConvention = CallingConvention.Cdecl,
        ExactSpelling = false,
        EntryPoint = "Init")]
        public static extern void Init(string configFile);

        [DllImport(@"../Dll/NeuralNetwork.dll",
        CallingConvention = CallingConvention.Cdecl,
        ExactSpelling = false,
        EntryPoint = "ProcessNeuralNetwork")]
        public static extern int ProcessNeuralNetwork();

        [DllImport(@"../Dll/NeuralNetwork.dll",
        CallingConvention = CallingConvention.Cdecl,
        ExactSpelling = false,
        EntryPoint = "getProgress")]
        public static extern uint getProgress();

        [DllImport(@"../Dll/NeuralNetwork.dll",
        CallingConvention = CallingConvention.Cdecl,
        ExactSpelling = false,
        EntryPoint = "getDataSize")]
        public static extern uint getDataSize();

        public ProgressDialog()
        {
            InitializeComponent();

            // The hard worker guy, does the real processing
            this.m_NNBackgroundWorker = new BackgroundWorker();
            this.m_NNBackgroundWorker.WorkerSupportsCancellation = true;
            this.m_NNBackgroundWorker.DoWork += new System.ComponentModel.DoWorkEventHandler(this.NNBackgroundWorker_DoWork);
            this.m_NNBackgroundWorker.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.NNBackgroundWorker_RunWorkerCompleted);

            // gets the progress done and updates the progress bar
            this.m_NNBackgroundProgressUpdater = new BackgroundWorker();
            this.m_NNBackgroundProgressUpdater.DoWork += new System.ComponentModel.DoWorkEventHandler(this.NNBackgroundProgressUpdater_DoWork);
            this.m_NNBackgroundProgressUpdater.ProgressChanged += new ProgressChangedEventHandler(NNBackgroundProgressUpdater_ProgressChanged);
            this.m_NNBackgroundProgressUpdater.WorkerReportsProgress = true;

        }

        public void setConfigurationFilePath(string s)
        {
            m_configPath = s;
        }

        private void ProgressDialog_Load(object sender, EventArgs e)
        {
            this.Shown += new System.EventHandler(this.ProgressDialog_Shown);
            this.FormClosing += ProgressDialog_Closing;
            progressBar1.Minimum = 0;
            Init(m_configPath);
            m_dataSize = getDataSize();
            progressBar1.Maximum = (int)m_dataSize;
            progressBar1.Value = 0;
        }

        private void ProgressDialog_Shown(object sender, EventArgs e)
        {
            Init(m_configPath);
            m_dataSize = getDataSize();

            this.m_NNBackgroundWorker.RunWorkerAsync(this);
            this.m_NNBackgroundProgressUpdater.RunWorkerAsync(this);

        }

        private void ProgressDialog_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            
        }

        private void UpdateProgress(int value)
        {
            progressBar1.Value = value;
        }

        private void NNBackgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            //BackgroundWorker bw = sender as BackgroundWorker;

            ProgressDialog pd = (ProgressDialog)e.Argument;
            string configPath = pd.m_configPath;
            ProcessNeuralNetwork();
        }

        private void NNBackgroundWorker_RunWorkerCompleted(
            object sender,
            RunWorkerCompletedEventArgs e)
        {
            // Do something on completion of the task
            MessageBox.Show("Task completed. Check the log file for details.");
            this.m_NNBackgroundProgressUpdater.CancelAsync();
            Thread.Sleep(10);       // give time to cancel the progress updater worker.
            BeginInvoke(new MethodInvoker(Close));      // close the dialog
        }
        private void NNBackgroundProgressUpdater_DoWork(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                m_progress = getProgress();
                if(m_progress >= m_dataSize)
                {
                    break;
                }
                if (this.m_NNBackgroundProgressUpdater.CancellationPending)
                {
                    e.Cancel = true;
                    return;
                }
                m_NNBackgroundProgressUpdater.ReportProgress((int)m_progress);
                Thread.Sleep(500);
            }
        }

        private void NNBackgroundProgressUpdater_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            UpdateProgress(e.ProgressPercentage);
        }


    }
}
