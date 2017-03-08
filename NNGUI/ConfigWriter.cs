using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NNGUI
{
    class ConfigWriter : ConfigBase
    {
        // Data ---
        private System.IO.StreamWriter m_StreamWriter;


        // Methods ---
        public ConfigWriter(string configFile) : base(configFile)
        {

        }

        public override void process()
        {
            try
            {
                    m_StreamWriter = new System.IO.StreamWriter(m_ConfigFile);
            }
            catch (Exception ex)
            {
                throw (ex);
            }
            m_StreamWriter.WriteLine(Constants.OutputLayerNodeCount + "=" + Convert.ToSingle(m_OutputLayerNodeCount));
            m_StreamWriter.WriteLine(Constants.HiddenLayerNodeCount + "=" + Convert.ToSingle(m_HiddenLayerNodeCount));
            m_StreamWriter.WriteLine(Constants.LearningRate + "=" + Convert.ToSingle(m_LearningRate));
            m_StreamWriter.WriteLine(Constants.PreviousDays + "=" + Convert.ToSingle(m_PreviousDays));
            m_StreamWriter.WriteLine(Constants.InputFile + "=" + m_InputFilePath);
            m_StreamWriter.WriteLine(Constants.IndicatorsFile + "=" + m_IndicatorsFilePath);
            m_StreamWriter.WriteLine(Constants.TrainingFile + "=" + m_TrainingFilePath);
            m_StreamWriter.WriteLine(Constants.TestFile + "=" + m_TestFilePath);
            m_StreamWriter.WriteLine(Constants.LogFile + "=" + m_LogFilePath);
            m_StreamWriter.WriteLine(Constants.TrainingSize + "=" + Convert.ToSingle(m_TrainingSize));
            if (m_RunCombinations)
            {
                m_StreamWriter.WriteLine(Constants.RunCombinations + "=true");
            }
            else
            {
                m_StreamWriter.WriteLine(Constants.RunCombinations + "=false");
            }
            m_StreamWriter.WriteLine(Constants.LoggingLevel + "=" + m_LoggingLevelString);
            m_StreamWriter.WriteLine(Constants.IndicatorsOut + "=" + m_Indicatorsout);
            m_StreamWriter.WriteLine(m_IndicatorsInfo);

            m_StreamWriter.Close();
        }
    }
}
