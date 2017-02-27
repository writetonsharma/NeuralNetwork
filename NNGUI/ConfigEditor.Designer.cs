namespace NNGUI
{
    partial class ConfigEditor
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ConfigEditor));
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabBasic = new System.Windows.Forms.TabPage();
            this.grpPaths = new System.Windows.Forms.GroupBox();
            this.btnLogFile = new System.Windows.Forms.Button();
            this.txtLogFile = new System.Windows.Forms.TextBox();
            this.btnTestFile = new System.Windows.Forms.Button();
            this.txtTestFile = new System.Windows.Forms.TextBox();
            this.btnTrainingFile = new System.Windows.Forms.Button();
            this.txtTrainingsFile = new System.Windows.Forms.TextBox();
            this.btnIndicatorsFile = new System.Windows.Forms.Button();
            this.txtIndicatorsFile = new System.Windows.Forms.TextBox();
            this.btnInputFile = new System.Windows.Forms.Button();
            this.txtInputFile = new System.Windows.Forms.TextBox();
            this.grpNetwork = new System.Windows.Forms.GroupBox();
            this.chkRunCombinations = new System.Windows.Forms.CheckBox();
            this.numTDS = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.numPD = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.numLR = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.numHLN = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.numOLN = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.tabIndicators = new System.Windows.Forms.TabPage();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.txtIndicatorsSelection = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.richIndicatorsType = new System.Windows.Forms.RichTextBox();
            this.btnBack = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.tabBasic.SuspendLayout();
            this.grpPaths.SuspendLayout();
            this.grpNetwork.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numTDS)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numPD)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLR)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numHLN)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numOLN)).BeginInit();
            this.tabIndicators.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabBasic);
            this.tabControl1.Controls.Add(this.tabIndicators);
            this.tabControl1.Location = new System.Drawing.Point(13, 4);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(504, 318);
            this.tabControl1.SizeMode = System.Windows.Forms.TabSizeMode.FillToRight;
            this.tabControl1.TabIndex = 0;
            // 
            // tabBasic
            // 
            this.tabBasic.Controls.Add(this.grpPaths);
            this.tabBasic.Controls.Add(this.grpNetwork);
            this.tabBasic.Location = new System.Drawing.Point(4, 22);
            this.tabBasic.Name = "tabBasic";
            this.tabBasic.Padding = new System.Windows.Forms.Padding(3);
            this.tabBasic.Size = new System.Drawing.Size(496, 292);
            this.tabBasic.TabIndex = 0;
            this.tabBasic.Text = "Basic";
            this.tabBasic.UseVisualStyleBackColor = true;
            // 
            // grpPaths
            // 
            this.grpPaths.Controls.Add(this.btnLogFile);
            this.grpPaths.Controls.Add(this.txtLogFile);
            this.grpPaths.Controls.Add(this.btnTestFile);
            this.grpPaths.Controls.Add(this.txtTestFile);
            this.grpPaths.Controls.Add(this.btnTrainingFile);
            this.grpPaths.Controls.Add(this.txtTrainingsFile);
            this.grpPaths.Controls.Add(this.btnIndicatorsFile);
            this.grpPaths.Controls.Add(this.txtIndicatorsFile);
            this.grpPaths.Controls.Add(this.btnInputFile);
            this.grpPaths.Controls.Add(this.txtInputFile);
            this.grpPaths.Location = new System.Drawing.Point(4, 124);
            this.grpPaths.Name = "grpPaths";
            this.grpPaths.Size = new System.Drawing.Size(490, 154);
            this.grpPaths.TabIndex = 3;
            this.grpPaths.TabStop = false;
            this.grpPaths.Text = "Paths";
            // 
            // btnLogFile
            // 
            this.btnLogFile.Location = new System.Drawing.Point(435, 124);
            this.btnLogFile.Name = "btnLogFile";
            this.btnLogFile.Size = new System.Drawing.Size(34, 23);
            this.btnLogFile.TabIndex = 9;
            this.btnLogFile.Text = "...";
            this.btnLogFile.UseVisualStyleBackColor = true;
            this.btnLogFile.Click += new System.EventHandler(this.btnLogFile_Click);
            // 
            // txtLogFile
            // 
            this.txtLogFile.Enabled = false;
            this.txtLogFile.Location = new System.Drawing.Point(9, 124);
            this.txtLogFile.Name = "txtLogFile";
            this.txtLogFile.Size = new System.Drawing.Size(420, 20);
            this.txtLogFile.TabIndex = 8;
            this.txtLogFile.Text = "Name of log file to be created";
            // 
            // btnTestFile
            // 
            this.btnTestFile.Location = new System.Drawing.Point(435, 98);
            this.btnTestFile.Name = "btnTestFile";
            this.btnTestFile.Size = new System.Drawing.Size(34, 23);
            this.btnTestFile.TabIndex = 7;
            this.btnTestFile.Text = "...";
            this.btnTestFile.UseVisualStyleBackColor = true;
            this.btnTestFile.Click += new System.EventHandler(this.btnTestFile_Click);
            // 
            // txtTestFile
            // 
            this.txtTestFile.Enabled = false;
            this.txtTestFile.Location = new System.Drawing.Point(9, 98);
            this.txtTestFile.Name = "txtTestFile";
            this.txtTestFile.Size = new System.Drawing.Size(420, 20);
            this.txtTestFile.TabIndex = 6;
            this.txtTestFile.Text = "Name of test file to be created";
            // 
            // btnTrainingFile
            // 
            this.btnTrainingFile.Location = new System.Drawing.Point(435, 72);
            this.btnTrainingFile.Name = "btnTrainingFile";
            this.btnTrainingFile.Size = new System.Drawing.Size(34, 23);
            this.btnTrainingFile.TabIndex = 5;
            this.btnTrainingFile.Text = "...";
            this.btnTrainingFile.UseVisualStyleBackColor = true;
            this.btnTrainingFile.Click += new System.EventHandler(this.btnTrainingFile_Click);
            // 
            // txtTrainingsFile
            // 
            this.txtTrainingsFile.Enabled = false;
            this.txtTrainingsFile.Location = new System.Drawing.Point(9, 72);
            this.txtTrainingsFile.Name = "txtTrainingsFile";
            this.txtTrainingsFile.Size = new System.Drawing.Size(420, 20);
            this.txtTrainingsFile.TabIndex = 4;
            this.txtTrainingsFile.Text = "Name of training file to be created";
            // 
            // btnIndicatorsFile
            // 
            this.btnIndicatorsFile.Location = new System.Drawing.Point(435, 46);
            this.btnIndicatorsFile.Name = "btnIndicatorsFile";
            this.btnIndicatorsFile.Size = new System.Drawing.Size(34, 23);
            this.btnIndicatorsFile.TabIndex = 3;
            this.btnIndicatorsFile.Text = "...";
            this.btnIndicatorsFile.UseVisualStyleBackColor = true;
            this.btnIndicatorsFile.Click += new System.EventHandler(this.btnIndicatorsFile_Click);
            // 
            // txtIndicatorsFile
            // 
            this.txtIndicatorsFile.Enabled = false;
            this.txtIndicatorsFile.Location = new System.Drawing.Point(9, 46);
            this.txtIndicatorsFile.Name = "txtIndicatorsFile";
            this.txtIndicatorsFile.Size = new System.Drawing.Size(420, 20);
            this.txtIndicatorsFile.TabIndex = 2;
            this.txtIndicatorsFile.Text = "Name of indicators file to be created";
            // 
            // btnInputFile
            // 
            this.btnInputFile.Location = new System.Drawing.Point(435, 20);
            this.btnInputFile.Name = "btnInputFile";
            this.btnInputFile.Size = new System.Drawing.Size(34, 23);
            this.btnInputFile.TabIndex = 1;
            this.btnInputFile.Text = "...";
            this.btnInputFile.UseVisualStyleBackColor = true;
            this.btnInputFile.Click += new System.EventHandler(this.btnInputFile_Click);
            // 
            // txtInputFile
            // 
            this.txtInputFile.Enabled = false;
            this.txtInputFile.Location = new System.Drawing.Point(9, 19);
            this.txtInputFile.Name = "txtInputFile";
            this.txtInputFile.Size = new System.Drawing.Size(420, 20);
            this.txtInputFile.TabIndex = 0;
            this.txtInputFile.Text = "Select Input File";
            // 
            // grpNetwork
            // 
            this.grpNetwork.Controls.Add(this.chkRunCombinations);
            this.grpNetwork.Controls.Add(this.numTDS);
            this.grpNetwork.Controls.Add(this.label5);
            this.grpNetwork.Controls.Add(this.numPD);
            this.grpNetwork.Controls.Add(this.label4);
            this.grpNetwork.Controls.Add(this.numLR);
            this.grpNetwork.Controls.Add(this.label3);
            this.grpNetwork.Controls.Add(this.numHLN);
            this.grpNetwork.Controls.Add(this.label2);
            this.grpNetwork.Controls.Add(this.numOLN);
            this.grpNetwork.Controls.Add(this.label1);
            this.grpNetwork.Location = new System.Drawing.Point(4, 6);
            this.grpNetwork.Name = "grpNetwork";
            this.grpNetwork.Size = new System.Drawing.Size(491, 112);
            this.grpNetwork.TabIndex = 2;
            this.grpNetwork.TabStop = false;
            this.grpNetwork.Text = "Network";
            // 
            // chkRunCombinations
            // 
            this.chkRunCombinations.AutoSize = true;
            this.chkRunCombinations.Location = new System.Drawing.Point(270, 72);
            this.chkRunCombinations.Name = "chkRunCombinations";
            this.chkRunCombinations.Size = new System.Drawing.Size(135, 17);
            this.chkRunCombinations.TabIndex = 10;
            this.chkRunCombinations.Text = "Run auto combinations";
            this.chkRunCombinations.UseVisualStyleBackColor = true;
            // 
            // numTDS
            // 
            this.numTDS.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.numTDS.Location = new System.Drawing.Point(409, 21);
            this.numTDS.Maximum = new decimal(new int[] {
            90,
            0,
            0,
            0});
            this.numTDS.Minimum = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numTDS.Name = "numTDS";
            this.numTDS.Size = new System.Drawing.Size(61, 20);
            this.numTDS.TabIndex = 9;
            this.numTDS.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(267, 23);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(110, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Training DataSet Size";
            // 
            // numPD
            // 
            this.numPD.Increment = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.numPD.Location = new System.Drawing.Point(409, 46);
            this.numPD.Maximum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.numPD.Minimum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.numPD.Name = "numPD";
            this.numPD.Size = new System.Drawing.Size(61, 20);
            this.numPD.TabIndex = 7;
            this.numPD.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(267, 48);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(75, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Previous Days";
            // 
            // numLR
            // 
            this.numLR.DecimalPlaces = 1;
            this.numLR.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numLR.Location = new System.Drawing.Point(173, 72);
            this.numLR.Maximum = new decimal(new int[] {
            9,
            0,
            0,
            65536});
            this.numLR.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numLR.Name = "numLR";
            this.numLR.Size = new System.Drawing.Size(61, 20);
            this.numLR.TabIndex = 5;
            this.numLR.Value = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(7, 74);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(74, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Learning Rate";
            // 
            // numHLN
            // 
            this.numHLN.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.numHLN.Location = new System.Drawing.Point(173, 46);
            this.numHLN.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numHLN.Name = "numHLN";
            this.numHLN.Size = new System.Drawing.Size(61, 20);
            this.numHLN.TabIndex = 3;
            this.numHLN.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(7, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(104, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Hidden Layer Nodes";
            // 
            // numOLN
            // 
            this.numOLN.Increment = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.numOLN.Location = new System.Drawing.Point(173, 18);
            this.numOLN.Maximum = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numOLN.Minimum = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numOLN.Name = "numOLN";
            this.numOLN.Size = new System.Drawing.Size(61, 20);
            this.numOLN.TabIndex = 1;
            this.numOLN.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(102, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Output Layer Nodes";
            // 
            // tabIndicators
            // 
            this.tabIndicators.Controls.Add(this.groupBox2);
            this.tabIndicators.Controls.Add(this.groupBox1);
            this.tabIndicators.Location = new System.Drawing.Point(4, 22);
            this.tabIndicators.Name = "tabIndicators";
            this.tabIndicators.Padding = new System.Windows.Forms.Padding(3);
            this.tabIndicators.Size = new System.Drawing.Size(496, 308);
            this.tabIndicators.TabIndex = 1;
            this.tabIndicators.Text = "Indicators";
            this.tabIndicators.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.txtIndicatorsSelection);
            this.groupBox2.Location = new System.Drawing.Point(7, 7);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(483, 44);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Indicators Selection";
            // 
            // txtIndicatorsSelection
            // 
            this.txtIndicatorsSelection.Location = new System.Drawing.Point(7, 20);
            this.txtIndicatorsSelection.Name = "txtIndicatorsSelection";
            this.txtIndicatorsSelection.Size = new System.Drawing.Size(470, 20);
            this.txtIndicatorsSelection.TabIndex = 0;
            this.txtIndicatorsSelection.Text = "0:64";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.richIndicatorsType);
            this.groupBox1.Location = new System.Drawing.Point(6, 57);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(484, 232);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Indicators Type";
            // 
            // richIndicatorsType
            // 
            this.richIndicatorsType.Location = new System.Drawing.Point(7, 19);
            this.richIndicatorsType.Name = "richIndicatorsType";
            this.richIndicatorsType.Size = new System.Drawing.Size(471, 207);
            this.richIndicatorsType.TabIndex = 0;
            this.richIndicatorsType.Text = resources.GetString("richIndicatorsType.Text");
            // 
            // btnBack
            // 
            this.btnBack.Location = new System.Drawing.Point(30, 324);
            this.btnBack.Name = "btnBack";
            this.btnBack.Size = new System.Drawing.Size(75, 23);
            this.btnBack.TabIndex = 1;
            this.btnBack.Text = "<< Back";
            this.btnBack.UseVisualStyleBackColor = true;
            this.btnBack.Click += new System.EventHandler(this.btnBack_Click);
            // 
            // ConfigEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(519, 359);
            this.Controls.Add(this.btnBack);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "ConfigEditor";
            this.Text = "Configuration Editor";
            this.Load += new System.EventHandler(this.ConfigEditor_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabBasic.ResumeLayout(false);
            this.grpPaths.ResumeLayout(false);
            this.grpPaths.PerformLayout();
            this.grpNetwork.ResumeLayout(false);
            this.grpNetwork.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numTDS)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numPD)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLR)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numHLN)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numOLN)).EndInit();
            this.tabIndicators.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.FormClosing += ConfigEditor_Closing;
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabBasic;
        private System.Windows.Forms.GroupBox grpPaths;
        private System.Windows.Forms.Button btnLogFile;
        private System.Windows.Forms.TextBox txtLogFile;
        private System.Windows.Forms.Button btnTestFile;
        private System.Windows.Forms.TextBox txtTestFile;
        private System.Windows.Forms.Button btnTrainingFile;
        private System.Windows.Forms.TextBox txtTrainingsFile;
        private System.Windows.Forms.Button btnIndicatorsFile;
        private System.Windows.Forms.TextBox txtIndicatorsFile;
        private System.Windows.Forms.Button btnInputFile;
        private System.Windows.Forms.TextBox txtInputFile;
        private System.Windows.Forms.GroupBox grpNetwork;
        private System.Windows.Forms.CheckBox chkRunCombinations;
        private System.Windows.Forms.NumericUpDown numTDS;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown numPD;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown numLR;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown numHLN;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numOLN;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TabPage tabIndicators;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox txtIndicatorsSelection;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RichTextBox richIndicatorsType;
        private System.Windows.Forms.Button btnBack;
    }
}