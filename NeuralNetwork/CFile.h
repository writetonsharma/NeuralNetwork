
#ifndef __C_FILE_H__
#define __C_FILE_H__

#include "miscdef.h"

enum OpenType
{
	CF_READ = 04,
	CF_WRITE = 02,
	CF_READ_WRITE = 06
};


class CFile
{
private:

	std::fstream*		m_fs;
	OpenType			m_openType;
	std::string			m_filePath;
	bool				m_fileOpen;
	int					m_mode;


	CFile& operator= (const CFile&);
	CFile(const CFile&);

	bool exist(const std::string& filePath);
	void setMode();

public:

	CFile();
	CFile(const std::string& filepath, OpenType type = CF_READ);

	~CFile();

	void openFile();
	void close();

	void readFile(std::vector<std::string>& lineBuffer);
	void writeFile(std::vector<std::vector<double> >& indicators);
	void writeFile(std::string& str);
	void writeFile(std::vector<double>& row);
	void skipRows(u_int count);

	bool readLine(std::string& line);

};

#endif