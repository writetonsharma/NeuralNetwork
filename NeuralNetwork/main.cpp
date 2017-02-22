
#include "CNeuralNetwork.h"
#include "preprocess.h"
#include "CMatrix.h"
#include "CFile.h"
#include "miscdef.h"
#include "partition.h"
#include "CConfig.h"
#include "IniSettings.h"



extern std::map<int, double>	maxValMap;
extern std::map<int, double>	minValMap;

//#define INPUT_NODE_COUNT

void scaleData(const std::vector<std::string>& lineBuffer, std::vector<std::vector<double> >& slicedData)
{
	size_t len = lineBuffer.size();
	
	for (size_t i = 0; i < len; i++)
	{
		std::vector<double> temp;
		std::string str = lineBuffer[i];
		size_t ti = 0;
		std::string t_str;
		bool first_column = true;
		size_t col = 0;
		for (size_t j = 0; j < str.length(); j++)
		{
			 char c = str[j];
			 if (c == ',')
			 {
				 double val = atof(t_str.c_str());
				 // insert first column without change, its the target value
				 if (!first_column)
				 {
					 double mx = maxValMap[col];
					 double mn = minValMap[col];
					 //val = ((val / div) * 0.99) + 0.01;
					 val = (val - mn) / (mx - mn);
					 if ((val == mn) || (mx == mn))
					 {
						 val = 0.5;
					 }
					 ;
				 }
				 else
				 {
					 first_column = false;
				 }
				 temp.push_back(val);
				 col++;
				 t_str.clear();
				 continue;
			 }
			 else
			 {
				 t_str += c;
			 }

		}

		double val = atof(t_str.c_str());
		double div = maxValMap[col];
		val = ((val / div) * 0.99) + 0.01;
		temp.push_back(val);
		slicedData.push_back(temp);
		temp.clear();
	}

	//
}


void max(double** target, u_int r, u_int c, double& m, u_int& row_index)
{

	for (size_t i = 0; i < r; i++)
	{
		for (size_t j = 0; j < c; j++)
		{
			if (target[i][j] > m)
			{
				m = target[i][j];
				row_index = i;
			}
		}
	}

	return;
}

void ANN()
{
	//CNeuralNetwork* ann = new CNeuralNetwork(3, 3, 3, 0.300);
	std::vector<std::string> lineBuffer;
	try
	{
		CFile cfile(CConfig::getInstance()->getValue(TrainingFile), OpenType::CF_READ);
		cfile.readFile(lineBuffer);
		cfile.close();
	}
	catch (std::exception&)
	{
		return;
	}

	// data scaling
	std::vector<std::vector<double> >	slicedData;
	scaleData(lineBuffer, slicedData);
	lineBuffer.clear();



	double** targetMatrix = CMatrix::allocateMatrix(atoi(CConfig::getInstance()->getValue(OutputLayerNodeCount).c_str()), 1);
	double** inputMatrix = CMatrix::allocateMatrix(slicedData[0].size() - 1, 1);



	CNeuralNetwork* ann = new CNeuralNetwork(slicedData[0].size() - 1, 
		atoi(CConfig::getInstance()->getValue(HiddenLayerNodeCount).c_str()),
		atoi(CConfig::getInstance()->getValue(OutputLayerNodeCount).c_str()),
		atof(CConfig::getInstance()->getValue(LearningRate).c_str()));
	size_t size = slicedData.size();



	CMatrix::print("\n###### Training run ######\n");

	// for all the inputs
	size_t outputLayer = atoi(CConfig::getInstance()->getValue(OutputLayerNodeCount).c_str());
	for (size_t i = 0; i < size; i++)
	{
		std::stringstream str;
		str << "\n##### Iteration " << (i + 1) << " #####\n";
		CMatrix::print(str.str());

		// create target matrix
		
		for (size_t j = 0; j < outputLayer; j++)
		{
			targetMatrix[j][0] = 0.01;
		}
		int targetVal = (int)slicedData[i][0];
		targetMatrix[targetVal][0] = 0.99;		// set the correct index for target
		//CMatrix::printMatrix(targetMatrix, "targetMatrix", NODE_COUNT, 1, "neuralnetwork.log", true);

												// create input matrix, leave first column
		size_t size_inner = slicedData[i].size() - 1;
		for (size_t j = 0; j < size_inner; j++)
		{
			inputMatrix[j][0] = slicedData[i][j + 1];
		}
		CMatrix::printMatrix(inputMatrix, "inputMatrix", slicedData[0].size() - 1, 1, "neuralnetwork.log", true);

		ann->train(inputMatrix, targetMatrix);
	}


	// training done, lets test...

	try
	{
		CFile cfile(CConfig::getInstance()->getValue(TestFile), OpenType::CF_READ);
		cfile.readFile(lineBuffer);
		cfile.close();
	}
	catch (std::exception&)
	{
		return;
	}

	slicedData.clear();
	scaleData(lineBuffer, slicedData);
	lineBuffer.clear();

	CMatrix::freeMatrix(inputMatrix, slicedData[0].size() - 1, 1);
	CMatrix::freeMatrix(targetMatrix, outputLayer, 1);
	inputMatrix = CMatrix::allocateMatrix(slicedData[0].size() - 1, 1);
	targetMatrix = CMatrix::allocateMatrix(outputLayer, 1);

	size = slicedData.size();

	CMatrix::print("\n###### Test run ######\n");
	u_int success_count = 0;
	for (size_t i = 0; i < size; i++)
	{
		{
			std::stringstream str;
			str << "\n##### Iteration " << (i + 1) << " #####\n";
			CMatrix::print(str.str());
		}
		size_t size_inner = slicedData[i].size() - 1;
		for (size_t j = 0; j < size_inner; j++)
		{
			inputMatrix[j][0] = slicedData[i][j + 1];
		}

		int targetVal = (int)slicedData[i][0];

		ann->query(inputMatrix, targetMatrix);
		double val = 0;
		u_int index = 0;
		max(targetMatrix, outputLayer, 1, val, index);
		CMatrix::printMatrix(targetMatrix, "targetMatrix", 
			atoi(CConfig::getInstance()->getValue(OutputLayerNodeCount).c_str()), 1, "neuralnetwork.log", true);

		std::stringstream str;
		str << "target: " << targetVal << "\n";
		str << "predicted: " << index;


		if (index == targetVal)
		{
			str << ". Success.";
			CMatrix::print(str.str());
			success_count++;
		}
		else
		{
			str << ". Fail.";
			CMatrix::print(str.str());
		}
	}

	std::stringstream str;
	str << "Success%: " << (double)(((double)success_count / (double)size) * 100) << "%.\n";
	CMatrix::print(str.str());

	CMatrix::freeMatrix(inputMatrix, slicedData[0].size() - 1, 1);
	CMatrix::freeMatrix(targetMatrix, outputLayer, 1);
}


int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " <ini_file_path>" << std::endl;
		return false;
	}

	std::string iniFile = argv[1];
	CConfig::getInstance(iniFile);

	remove("neuralnetwork.log");

	preprocess();

	partition(80);

	ANN();


	return true;
}
