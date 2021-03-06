﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NNGUI
{
    abstract class ConfigBase
    {
        public enum EnumLoggingLevel { Errors, Warning, Info, Debug};
        // Data ---
        protected string      m_ConfigFile;
        protected uint        m_OutputLayerNodeCount;
        protected uint        m_HiddenLayerNodeCount;
        protected double      m_LearningRate;
        protected uint        m_PreviousDays;
        protected string      m_InputFilePath;
        protected string      m_IndicatorsFilePath;
        protected string      m_TrainingFilePath;
        protected string      m_TestFilePath;
        protected string      m_LogFilePath;
        protected uint        m_TrainingSize;
        protected bool        m_RunCombinations;
        protected string      m_Indicatorsout;
        protected EnumLoggingLevel m_LoggingLevel;
        protected string m_LoggingLevelString;

        protected bool        m_valid;


        // Methods ---
        // Mandatory parameter constructor
        public ConfigBase(string configFile)
        {
            m_ConfigFile = configFile;
            m_valid = false;
            m_OutputLayerNodeCount = 2;
            m_HiddenLayerNodeCount = 2;
            m_LearningRate = 0.1;
            m_PreviousDays = 200;
            m_InputFilePath = "./InputFile.csv";
            m_IndicatorsFilePath = "./IndicatorsFile.csv";
            m_TrainingFilePath = "./TrainingFile.csv";
            m_TestFilePath = "./TestFile.csv";
            m_LogFilePath = "./LogFile.log";
            m_TrainingSize = 80;
            m_RunCombinations = false;
            m_Indicatorsout = "0:64";
            m_LoggingLevel = EnumLoggingLevel.Warning;
            m_LoggingLevelString = Constants.WarningLevel;
        }

        public string ConfigFile
        {
            get
            {
                return m_ConfigFile;
            }
            set
            {
                m_ConfigFile = value;
            }
        }
        public uint HiddenLayerNodeCount
        {
            get
            {
                return m_HiddenLayerNodeCount;
            }
            set
            {
                m_HiddenLayerNodeCount = value;
            }
        }
        public double LearningRate
        {
            get
            {
                return m_LearningRate;
            }
            set
            {
                m_LearningRate = value;
            }
        }

        public uint OutputLayerNodeCount
        {
            get
            {
                return m_OutputLayerNodeCount;
            }
            set
            {
                m_OutputLayerNodeCount = value;
            }
        }
        public uint PreviousDays
        {
            get
            {
                return m_PreviousDays;
            }
            set
            {
                m_PreviousDays = value;
            }
        }
        public string InputFilePath
        {
            get
            {
                return m_InputFilePath;
            }
            set
            {
                m_InputFilePath = value;
            }
        }
        public string IndicatorsFilePath
        {
            get
            {
                return m_IndicatorsFilePath;
            }
            set
            {
                m_IndicatorsFilePath = value;
            }
        }
        public string TrainingFilePath
        {
            get
            {
                return m_TrainingFilePath;
            }
            set
            {
                m_TrainingFilePath = value;
            }
        }
        public string TestFilePath
        {
            get
            {
                return m_TestFilePath;
            }
            set
            {
                m_TestFilePath = value;
            }
        }
        public string LogFilePath
        {
            get
            {
                return m_LogFilePath;
            }
            set
            {
                m_LogFilePath = value;
            }
        }
        public uint TrainingSize
        {
            get
            {
                return m_TrainingSize;
            }
            set
            {
                m_TrainingSize = value;
            }
        }
        public bool RunCombinations
        {
            get
            {
                return m_RunCombinations;
            }
            set
            {
                m_RunCombinations = value;
            }
        }
        public string IndicatorsOut
        {
            get
            {
                return m_Indicatorsout;
            }
            set
            {
                m_Indicatorsout = value;
            }
        }
        protected string m_IndicatorsInfo;
        public string IndicatorsInfo
        {
            get
            {
                return m_IndicatorsInfo;
            }
            set
            {
                m_IndicatorsInfo = value;
            }
        }
        public EnumLoggingLevel LoggingLevel
        {
            get
            {
                return m_LoggingLevel;
            }
            set
            {
                m_LoggingLevel = value;
            }
        }
        public string LoggingLevelString
        {
            get
            {
                return m_LoggingLevelString;
            }
            set
            {
                m_LoggingLevelString = value;
            }
        }
        public bool isValid()
        {
            return m_valid;
        }
        public abstract void process();

    }
}
