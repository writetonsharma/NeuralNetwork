
#include "CFile.h"
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

CFile::CFile() :
			m_fs(0),
			m_fileOpen(false)
{

}

CFile::CFile(const std::string& filepath, OpenType type) :
	m_fs(0),
	m_openType(type),
	m_fileOpen(false)
{
	if(exist(filepath))
	{
		m_filePath = filepath;
		setMode();
		try 
		{
			openFile();
		}
		catch(std::exception& ex)
		{
			std::cout << ex.what();
			throw(ex);
		}
	}
	else
	{
#ifdef _WIN32
		std::cout << "File do not exist. " << filepath << "." << std::endl;
		throw(std::exception("File do not exist.\n"));
#else
		std::cout << "File do not exist. " << filepath << "." << std::endl;
#endif	
	}
}

CFile::~CFile()
{
	if(m_fs)
	{
		delete m_fs;
	}
}

bool CFile::exist(const std::string& filePath)
{
	if (m_openType == CF_WRITE)
	{
		return true;
	}
#ifdef _WIN32
	if(!_access(filePath.c_str(), m_openType))
#else
	if (!access(filePath.c_str(), m_openType))
#endif
	{
		return true;
	}
	return false;
}

void CFile::openFile()
{
	if(m_fileOpen)
	{
		return;
	}

	setMode();
	m_fs = new std::fstream();
#ifdef _WIN32
	m_fs->open(m_filePath.c_str(), m_mode);
#else
	m_fs->open(m_filePath.c_str(), (std::_Ios_Openmode)m_mode);
#endif
	if(!m_fs->good())
	{
#ifdef _WIN32
		throw(std::exception("File open failed.\n"));
#else
		return;
#endif
	}

	m_fileOpen = true;
}

void CFile::close()
{
	if(!m_fileOpen)
	{
		return;
	}

	m_fs->close();
	m_fileOpen = false;
}

void CFile::readFile(std::vector<std::string>& lineBuffer) 
{
	if(!m_fileOpen)
	{
#ifdef _WIN32
		throw(std::exception("Open file first.\n"));
#else
		return;
#endif
	}

	while(!m_fs->eof())
	{
		std::string str;
		getline(*m_fs, str);
		if(str.length())
		{
			lineBuffer.push_back(str);
		}
		if(m_fs->eof())
		{
			break;
		}
	}

	return;
}

bool CFile::readLine(std::string& line)
{
	getline(*m_fs, line);
	if (line.length() == 0 && m_fs->eof())
	{
		return false;
	}

	return true;
}

void CFile::writeFile(std::vector<std::vector<double> >& indicators)
{
	if (!m_fileOpen)
	{
#ifdef _WIN32
		throw(std::exception("Open file first.\n"));
#else
		return;
#endif
	}

	for (size_t i = 0; i < indicators.size(); i++)
	{
		std::vector<double>& row = indicators[i];
		for (size_t j = 0; j < row.size(); j++)
		{
			char arr[16];
			sprintf(arr, "%.2f", row[j]);
			std::fixed(*m_fs);
			*m_fs << std::fixed << arr;
			if(j < row.size() - 1)
				*m_fs << ",";
		}
		m_fs->write("\n", 1);
	}
}

void CFile::writeFile(std::string& str)
{
	if (!m_fileOpen)
	{
#ifdef _WIN32
		throw(std::exception("Open file first.\n"));
#else
		return;
#endif
	}
	*m_fs << str.c_str();
	return;

}

void CFile::writeFile(std::vector<double>& row)
{
	for (size_t j = 0; j < row.size(); j++)
	{
		char arr[16];
		sprintf(arr, "%.2f", row[j]);
		std::fixed(*m_fs);
		*m_fs << std::fixed << arr;
		if (j < row.size() - 1)
			*m_fs << ",";
	}
	m_fs->write("\n", 1);
}

void CFile::setMode()
{
	if(m_openType == CF_READ)
	{
		m_mode = std::fstream::in;
	}
	else if(m_openType == CF_WRITE)
	{
		m_mode = std::fstream::out | std::fstream::app;
	}
	else if(m_openType == CF_READ_WRITE)
	{
		m_mode = std::fstream::in | std::fstream::out | std::fstream::app;
	}
	else
	{
		// invalid
	}
}

void CFile::skipRows(u_int count)
{
	if (!m_fileOpen)
	{
#ifdef _WIN32
		throw(std::exception("Open file first.\n"));
#else
		return;
#endif
	}

	u_int index = 0;
	while (!m_fs->eof())
	{
		std::string str;
		getline(*m_fs, str);
		if (index++ == (count - 1))
			break;
	}
}


