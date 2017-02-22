#pragma once

#ifndef __CCONFIG_H__
#define __CCONFIG_H__

#include "miscdef.h"
#include "CFile.h"

class CConfig
{

private:
	CConfig(const std::string& filePath);
	CConfig(const CConfig&);
	CConfig& operator=(const CConfig&);

	void readConfig();
	bool comment(const std::string& line);
	bool empty(const std::string& line);

	bool getSettingValue(const std::string& line, std::string& setting, std::string& value);


	static CConfig*		m_instance;

	std::string			m_filePath;
	CFile*		m_cfile;

	std::map<std::string, std::string>	m_settingsPair;


public:

	static CConfig* getInstance(const std::string& filePath);
	static CConfig* getInstance();
	std::string getValue(const std::string& setting);
};
#endif		/*	__CCONFIG_H__	*/

