

#include "partition.h"
#include "CFile.h"
#include "CConfig.h"
#include "IniSettings.h"



bool partition(double trainPercent)
{
	if (trainPercent > 100 && trainPercent < 0)
	{
		CMatrix::print("Wrong partition percentage given.\n", CConfig::getInstance()->getValue(LogFile));
		return false;
	}

	std::vector<std::string> lineBuffer;
	try
	{
		CFile cfile(CConfig::getInstance()->getValue(IndicatorsFile), CF_READ);
		cfile.skipRows(1);
		cfile.readFile(lineBuffer);
		cfile.close();
	}
	catch (std::exception&)
	{
		return false;
	}

	size_t lineCount = (size_t)(trainPercent * (lineBuffer.size()))/100;

	remove(CConfig::getInstance()->getValue(TrainingFile).c_str());
	remove(CConfig::getInstance()->getValue(TestFile).c_str());

	// training data
	if (!writeData(lineBuffer, CConfig::getInstance()->getValue(TrainingFile), 0, lineCount))
	{
		CMatrix::print("Training file creation failed.\n", CConfig::getInstance()->getValue(LogFile));
		return false;
	}

	// test data
	if (!writeData(lineBuffer, CConfig::getInstance()->getValue(TestFile), lineCount, lineBuffer.size()))
	{
		CMatrix::print("Test file creation failed.\n", CConfig::getInstance()->getValue(LogFile));
		return false;
	}

	return true;
}

bool writeData(std::vector<std::string> lineBuffer, std::string file, size_t lineFrom, size_t lineTo)
{
	try
	{
		CFile cfile(file.c_str(), CF_WRITE);
		for (size_t i = lineFrom; i < lineTo; i++)
		{
			cfile.writeFile(lineBuffer[i]);
			std::string str = "\n";
			cfile.writeFile(str);
		}
		cfile.close();
	}
	catch (std::exception&)
	{
		return false;
	}
	return true;
}


