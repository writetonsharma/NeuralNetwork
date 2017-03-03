#pragma once
#ifndef __C_LOGGING_H__
#define __C_LOGGING_H__

#include "miscdef.h"
#include "CFile.h"
#include <algorithm>

enum enumLoggingLevel
{
	LL_Errors,
	LL_Warning,
	LL_Info,
	LL_Debug
};

class CLogger
{
private:

	CLogger(std::string& loggingLevel)
	{
		m_loggingLevel = LL_Info;
		if (loggingLevel == "Errors")
		{
			m_loggingLevel = LL_Errors;
		}
		else if (loggingLevel == "Warning")
		{
			m_loggingLevel = LL_Warning;
		}
		else if (loggingLevel == "Info")
		{
			m_loggingLevel = LL_Info;
		}
		else if (loggingLevel == "Debug")
		{
			m_loggingLevel = LL_Debug;
		}
	}
	CLogger(const CLogger&);
	CLogger& operator= (const CLogger&);

	enumLoggingLevel		m_loggingLevel;

public:

	static CLogger*		m_instance;

	static CLogger* getInstance(std::string& loggingLevel);
	static CLogger* getInstance();

	void printMatrix(double** matrix, std::string name, u_int row, u_int col,
		std::string fileName, bool printToFile, enumLoggingLevel loggingLevel);
	void print(std::string name, std::string fileName, 
		bool printToFile, enumLoggingLevel loggingLevel);

};

#endif

