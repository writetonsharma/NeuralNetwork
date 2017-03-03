
#include "CLogging.h"

CLogger*		CLogger::m_instance;

CLogger* CLogger::getInstance(std::string& loggingLevel)
{
	if (m_instance == 0)
	{
		try
		{
			m_instance = new CLogger(loggingLevel);
		}
		catch (std::exception& ex)
		{
			throw(ex);
		}
	}

	return m_instance;
}

CLogger* CLogger::getInstance()
{
	return m_instance;
}
void CLogger::printMatrix(double** matrix, std::string name, u_int row, u_int col,
	std::string fileName, bool printToFile, enumLoggingLevel loggingLevel)
{
	if (m_loggingLevel < loggingLevel)
	{
		// if logging level is more than default
		return;
	}
	std::ostream* os;
	std::filebuf fb;
	if (!printToFile)
	{
		os = new std::ostream(std::cout.rdbuf());
	}
	else
	{
		fb.open(fileName.c_str(), std::ios::out | std::ios::app);
		os = new std::ostream(&fb);
	}

	*os << std::endl << "Printing matrix \'" << name << "\'" << std::endl;
	for (u_int i = 0; i < row; i++)
	{
		for (u_int j = 0; j < col; j++)
		{
			*os << matrix[i][j] << "\t";
		}
		*os << std::endl;
	}
	fb.close();
	delete os;
}

void CLogger::print(std::string name, std::string fileName, 
	bool printToFile, enumLoggingLevel loggingLevel)
{
	if (m_loggingLevel < loggingLevel)
	{
		// if logging level is more than default
		return;
	}

	std::ostream* os;
	std::filebuf fb;
	if (!printToFile)
	{
		os = new std::ostream(std::cout.rdbuf());
	}
	else
	{
		fb.open(fileName.c_str(), std::ios::out | std::ios::app);
		os = new std::ostream(&fb);
	}

	*os << name;

	fb.close();
	delete os;

}

