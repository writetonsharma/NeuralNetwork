using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NNGUI
{
    class ConfigReader : ConfigBase
    {
        // Data ---
        private System.IO.StreamReader      m_StreamReader;

        // Methods ---
        public ConfigReader(string configFile) : base(configFile)
        {

        }

        public override void process()
        {
            try
            {
                    m_StreamReader = new System.IO.StreamReader(m_ConfigFile);
            }
            catch (Exception ex)
            {
                throw (ex);
            }

            string line;
            while((line = m_StreamReader.ReadLine()) != null)
            {
                if (line.Length == 0 || line[0] == '#')
                    continue;

                processLine(line);
            }
            m_StreamReader.Close();
            return;
        }

        private void processLine(string line)
        {
            string config = "";
            string value = "";
            getConfigValue(line, ref config, ref value);
            saveToMember(config, value);

        }

        private void getConfigValue(string line, ref string config, ref string value)
        {
            Int32 index = line.IndexOf('=');
            if (index == -1)
                return;

            config = line.Substring(0, index);
            value = line.Substring(index + 1);
        }

        private void saveToMember(string config, string value)
        {
            if(config == Constants.OutputLayerNodeCount)
            {
                m_OutputLayerNodeCount = Convert.ToUInt32(value);
                m_valid = true;
            }
            else if(config == Constants.HiddenLayerNodeCount)
            {
                m_HiddenLayerNodeCount = Convert.ToUInt32(value);
                m_valid = true;
            }
            else if(config == Constants.LearningRate)
            {
                m_LearningRate = Convert.ToDouble(value);
                m_valid = true;
            }
            else if(config == Constants.PreviousDays)
            {
                m_PreviousDays = Convert.ToUInt32(value);
                m_valid = true;
            }
            else if(config == Constants.InputFile)
            {
                m_InputFilePath = value;
                m_valid = true;
            }
            else if(config == Constants.IndicatorsFile)
            {
                m_IndicatorsFilePath = value;
                m_valid = true;
            }
            else if(config == Constants.TrainingFile)
            {
                m_TrainingFilePath = value;
                m_valid = true;
            }
            else if(config == Constants.TestFile)
            {
                m_TestFilePath = value;
                m_valid = true;
            }
            else if(config == Constants.LogFile)
            {
                m_LogFilePath = value;
                m_valid = true;
            }
            else if(config == Constants.TrainingSize)
            {
                m_TrainingSize = Convert.ToUInt32(value);
                m_valid = true;
            }
            else if(config == Constants.RunCombinations)
            {
                if(value == "true")
                {
                    m_RunCombinations = true;
                }
                else
                {
                    m_RunCombinations = false;
                }
                m_valid = true;
            }
            else if(config == Constants.IndicatorsOut)
            {
                m_Indicatorsout = value;
                m_valid = true;
            }
            else if(config == Constants.LoggingLevel)
            {
                m_LoggingLevelString = value.ToLower();
                if (value.ToLower() == "errors")
                {
                    m_LoggingLevel = ConfigBase.EnumLoggingLevel.Errors;
                }
                else if(value.ToLower() == "warning")
                {
                    m_LoggingLevel = ConfigBase.EnumLoggingLevel.Warning;
                }
                else if(value.ToLower() == "info")
                {
                    m_LoggingLevel = ConfigBase.EnumLoggingLevel.Info;
                }
                else if(value.ToLower() == "debug")
                {
                    m_LoggingLevel = ConfigBase.EnumLoggingLevel.Debug;
                }
            }
        }
    }
}
