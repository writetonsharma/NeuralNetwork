

#include "partition.h"
#include "CFile.h"



bool partition(double trainPercent)
{
	if (trainPercent > 100 && trainPercent < 0)
	{
		CMatrix::print("Wrong partition percentage given.\n");
		return false;
	}

	std::vector<std::string> lineBuffer;
	try
	{
		CFile cfile(STOCK_DATA_FILE_WITH_INDICATORS, OpenType::CF_READ);
		cfile.skipRows(1);
		cfile.readFile(lineBuffer);
		cfile.close();
	}
	catch (std::exception&)
	{
		return false;
	}

	size_t lineCount = (size_t)(trainPercent * (lineBuffer.size()))/100;

	remove(STOCK_DATA_FILE_TRAIN);
	remove(STOCK_DATA_FILE_TEST);

	// training data
	if (!writeData(lineBuffer, STOCK_DATA_FILE_TRAIN, 0, lineCount))
	{
		CMatrix::print("Training file creation failed.\n");
		return false;
	}

	// test data
	if (!writeData(lineBuffer, STOCK_DATA_FILE_TEST, lineCount, lineBuffer.size()))
	{
		CMatrix::print("Test file creation failed.\n");
		return false;
	}

	return true;
}

bool writeData(std::vector<std::string> lineBuffer, std::string file, size_t lineFrom, size_t lineTo)
{
	try
	{
		CFile cfile(file.c_str(), OpenType::CF_WRITE);
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

