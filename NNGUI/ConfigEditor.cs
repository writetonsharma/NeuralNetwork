using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NNGUI
{
    public partial class ConfigEditor : Form
    {
        public ConfigEditor()
        {
            InitializeComponent();
        }

        private void setToolTips()
        {
            ToolTip buttonToolTip = new ToolTip();
            buttonToolTip.ToolTipTitle = "Indicators Selection";
            buttonToolTip.UseFading = true;
            buttonToolTip.UseAnimation = true;
            buttonToolTip.IsBalloon = true;
            buttonToolTip.ShowAlways = true;
            buttonToolTip.AutoPopDelay = 20000;
            buttonToolTip.InitialDelay = 500;
            buttonToolTip.ReshowDelay = 500;
            buttonToolTip.SetToolTip(this.txtIndicatorsSelection, "Select features which you want to use to build the ANN.\n"
                + "Continuous selection can be separated by discrete selection using comma.\n"
                + "Eg: 0:12,21:30,50:64. If this sequence is given, this means\n"
                + "indicators from 0 to 12, from 21 to 30 and from 50 to 64 will be selected.\n"
                + "Validation of what you enter will be done during processing and\n"
                + "if wrong sequence is given, all the indicators will be selected.");
        }

        private void ConfigEditor_Load(object sender, EventArgs e)
        {
            setToolTips();
            
        }

        private string m_configPath;
        private Form m_iniFileSelectDialog;

        public void setConfigurationFilePath(string s)
        {
            m_configPath = s;
        }

        public void setIniFileSelectDialog(Form d)
        {
            m_iniFileSelectDialog = d;
        }

        private void ConfigEditor_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            m_iniFileSelectDialog.Show();
        }

        private void btnIndicatorsFile_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "Indicators file|*.csv";
            saveFileDialog1.Title = "Save indicators file";
            if (saveFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                txtIndicatorsFile.Text = saveFileDialog1.FileName;
            }
        }

        private void btnInputFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "Input file|*.csv";
            openFileDialog1.Title = "Select input file";

            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                txtInputFile.Text = openFileDialog1.FileName;
            }
        }

        private void btnTrainingFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "Training file|*.csv";
            openFileDialog1.Title = "Save training file";

            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                txtTrainingsFile.Text = openFileDialog1.FileName;
            }
        }

        private void btnTestFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "Test file|*.csv";
            openFileDialog1.Title = "Save test file";

            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                txtTestFile.Text = openFileDialog1.FileName;
            }
        }

        private void btnLogFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "Log file|*.csv";
            openFileDialog1.Title = "Save log file";

            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                txtLogFile.Text = openFileDialog1.FileName;
            }
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
