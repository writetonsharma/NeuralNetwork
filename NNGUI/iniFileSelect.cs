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
    public partial class iniFileSelect : Form
    {
        public iniFileSelect()
        {
            InitializeComponent();
        }


        private void btnSelectConfFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "Config Files|*.ini";
            openFileDialog1.Title = "Select configuration file";

            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                txtFilePath.Text = openFileDialog1.FileName;
            }
        }

        private void btnSelect_Click(object sender, EventArgs e)
        {
            string s = txtFilePath.Text;
            if(s.Length == 0 || s == "Select Configuration File")
            {
                MessageBox.Show("Select configuration file path first.");
                return;
            }

            ConfigEditor ce = new ConfigEditor();
            ce.setConfigurationFilePath(s);
            ce.setIniFileSelectDialog(this);
            this.Hide();
            ce.ShowDialog();
        }

        private void txtFilePath_TextChanged(object sender, EventArgs e)
        {

        }

        private void iniFileSelect_Load(object sender, EventArgs e)
        {

        }


    }
}
