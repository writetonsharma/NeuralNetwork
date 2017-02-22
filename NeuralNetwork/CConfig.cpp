
#include "CConfig.h"

CConfig* CConfig::m_instance;

 CConfig* CConfig::getInstance(const std::string& filePath)
{
	if (m_instance == 0)
	{
		try
		{
			m_instance = new CConfig(filePath);
		}
		catch (std::exception& ex)
		{
			throw(ex);
		}
	}

	return m_instance;
}

CConfig* CConfig::getInstance()
{
	return m_instance;
}

CConfig::CConfig(const std::string& filePath)
{
	m_filePath = filePath;
	m_cfile = new CFile(filePath, OpenType::CF_READ);

	readConfig();
}

void CConfig::readConfig()
{
	std::string line;
	while (m_cfile->readLine(line))
	{
		if (comment(line) || empty(line))
		{
			continue;
		}

		std::string setting;
		std::string value;
		getSettingValue(line, setting, value);
		m_settingsPair.insert(std::pair<std::string, std::string>(setting, value));
	}

}

bool CConfig::comment(const std::string& line)
{
	if (line[0] == '#')
	{
		// skip comments
		return true;
	}
	return false;
}

bool CConfig::empty(const std::string& line)
{
	if (!line.length())
	{
		return true;
	}
	return false;
}

bool CConfig::getSettingValue(const std::string& line, std::string& setting, std::string& value)
{
	size_t pos = line.find('=');
	if (pos == line.npos)
	{
		false;
	}
	setting = line.substr(0, pos);
	value = line.substr(pos+1);

	return true;
}

std::string CConfig::getValue(const std::string& setting)
{
	return m_settingsPair[setting];
}