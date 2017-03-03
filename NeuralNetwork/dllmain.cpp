
#include "CNeuralNetwork.h"
#include "preprocess.h"
#include "CMatrix.h"
#include "CFile.h"
#include "miscdef.h"
#include "partition.h"
#include "CConfig.h"
#include "IniSettings.h"
#include "CLogging.h"



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

double ANN()
{
	//CNeuralNetwork* ann = new CNeuralNetwork(3, 3, 3, 0.300);
	std::vector<std::string> lineBuffer;
	try
	{
		CFile cfile(CConfig::getInstance()->getValue(TrainingFile), CF_READ);
		cfile.readFile(lineBuffer);
		cfile.close();
	}
	catch (std::exception&)
	{
		return 0;
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
		atof(CConfig::getInstance()->getValue(LearningRate).c_str()),
		atoi(CConfig::getInstance()->getValue(TrainingSize).c_str()));
	size_t size = slicedData.size();



	//CMatrix::print("\n###### Training run ######\n");

	// for all the inputs
	size_t outputLayer = atoi(CConfig::getInstance()->getValue(OutputLayerNodeCount).c_str());
	for (size_t i = 0; i < size; i++)
	{
		std::stringstream str;
		//str << "\n##### Iteration " << (i + 1) << " #####\n";
		//CMatrix::print(str.str());

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
		//CMatrix::printMatrix(inputMatrix, "inputMatrix", slicedData[0].size() - 1, 1, "neuralnetwork.log", true);

		ann->train(inputMatrix, targetMatrix);
	}


	// training done, lets test...

	try
	{
		CFile cfile(CConfig::getInstance()->getValue(TestFile), CF_READ);
		cfile.readFile(lineBuffer);
		cfile.close();
	}
	catch (std::exception&)
	{
		return 0;
	}

	slicedData.clear();
	scaleData(lineBuffer, slicedData);
	lineBuffer.clear();

	CMatrix::freeMatrix(inputMatrix, slicedData[0].size() - 1, 1);
	CMatrix::freeMatrix(targetMatrix, outputLayer, 1);
	inputMatrix = CMatrix::allocateMatrix(slicedData[0].size() - 1, 1);
	targetMatrix = CMatrix::allocateMatrix(outputLayer, 1);

	size = slicedData.size();

	//CMatrix::print("\n###### Test run ######\n");
	u_int success_count = 0;
	for (size_t i = 0; i < size; i++)
	{
		{
			std::stringstream str;
			//str << "\n##### Iteration " << (i + 1) << " #####\n";
			//CMatrix::print(str.str());
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
		//CMatrix::printMatrix(targetMatrix, "targetMatrix", 
		//	atoi(CConfig::getInstance()->getValue(OutputLayerNodeCount).c_str()), 1, "neuralnetwork.log", true);

		std::stringstream str;
		//str << "target: " << targetVal << "\n";
		//str << "predicted: " << index;


		if (index == targetVal)
		{
			//str << ". Success.";
			//CMatrix::print(str.str());
			success_count++;
		}
		else
		{
			//str << ". Fail.";
			//CMatrix::print(str.str());
		}
	}

 	std::stringstream str;
 	double success = (double)(((double)success_count / (double)size) * 100);
 	str << "Success%: " << success << "%.\n";
 	CLogger::getInstance()->print(str.str(), CConfig::getInstance()->getValue(LogFile), true, LL_Info);
 	std::cout << "Success%: " << success << "%.\n";

	CMatrix::freeMatrix(inputMatrix, slicedData[0].size() - 1, 1);
	CMatrix::freeMatrix(targetMatrix, outputLayer, 1);
	delete ann;
	ann = 0;

	return success;
}

extern "C" __declspec(dllexport) int __cdecl ProcessNeuralNetwork(char* configFile)
{

	std::string iniFile = configFile;
	CConfig::getInstance(iniFile);
	CLogger::getInstance(CConfig::getInstance()->getValue(LoggingLevel));

	// make combinations of settings and run

	//std::vector<std::vector<double> > combinations;
	std::vector<double> data;
	for (double i = 0.1; i <= 0.91; i += 0.1)
	{
		for (double j = 1; j <= 100; j += 5)
		{
			for (double k = 50; k <= 90; k += 5)
			{
				data.push_back(i);
				data.push_back(j);
				data.push_back(k);
			}
		}
	}
	// 	data.push_back(1);
	// 	data.push_back(2);
	// 	for (double i =5; i <= 10; i += 5)
	// 	{
	// 		data.push_back(i);
	// 	}
	// 	for (double i = 50; i <= 60; i += 5)
	// 	{
	// 		data.push_back(i);
	// 	}
	// 	double* temp = new double [data.size()];

	//getCombinations(combinations, data, temp, 0, data.size() - 1, 0, 3);

	//delete [] temp;
	//data.clear();
	remove(CConfig::getInstance()->getValue(LogFile).c_str());
	double max_success = 0.0;
	double curr_LR = 0.0;
	for (size_t i = 0; i < data.size();)
	{
		// 		if (curr_LR != data[i])
		// 		{
		// 			std::stringstream str;
		// 			str << "\n" << data[i] << ",";
		// 			CMatrix::print(str.str());
		// 			curr_LR = data[i];
		// 		}
		// 		else
		// 		{
		// 			std::stringstream str;
		// 			str << ",";
		// 			CMatrix::print(str.str());
		// 		}
		char arr[16];
		sprintf(arr, "%f", data[i++]);
		CConfig::getInstance()->setValue("LearningRate", arr);
		sprintf(arr, "%.0f", data[i++]);
		CConfig::getInstance()->setValue("HiddenLayerNodeCount", arr);
		sprintf(arr, "%.0f", data[i++]);
		CConfig::getInstance()->setValue("TrainingSize", arr);

		preprocess();
		partition(atoi(CConfig::getInstance()->getValue(TrainingSize).c_str()));

		double success = ANN();
		// 		std::stringstream str;
		// 		str << success;
		// 		CMatrix::print(str.str());

		if (success > max_success)
		{
			max_success = success;
		}
	}

	std::stringstream str;
	str << "Max Success Rate: " << max_success << "%.\n";
	CLogger::getInstance()->print(str.str(), CConfig::getInstance()->getValue(LogFile), true, LL_Info);
	std::cout << str.str() << std::endl;

	return true;
}

// void getCombinations(std::vector<std::vector<double> >& combinations, 
// 			std::vector<double> arr, double temp[], int start, int end, int index, int r)
// {
// 	// Current combination is ready to be printed, print it
// 	if (index == r)
// 	{
// 		std::vector<double> t;
// 		for (int j = 0; j < r; j++)
// 		{
// 			if (temp[0] >= 1.0)
// 				break;			
// 			t.push_back(temp[j]);
// 		}
// 		combinations.push_back(t);
// 		return;
// 	}
// 
// 	// replace index with all possible elements. The condition
// 	// "end-i+1 >= r-index" makes sure that including one element
// 	// at index will make a combination with remaining elements
// 	// at remaining positions
// 	for (int i = start; i <= end && end - i + 1 >= r - index; i++)
// 	{
// 		temp[index] = arr[i];
// 		getCombinations(combinations, arr, temp, i + 1, end, index + 1, r);
// 	}
// }

// int main(int argc, char** argv)
// {
// 	if (argc < 2)
// 	{
// 		std::cout << "Usage: " << argv[0] << " <ini_file_path>" << std::endl;
// 		return false;
// 	}
// 
// 	std::string iniFile = argv[1];
// 	CConfig::getInstance(iniFile);
// 
// 	// make combinations of settings and run
// 
// 	//std::vector<std::vector<double> > combinations;
// 	std::vector<double> data;
// 	for (double i = 0.1; i <= 0.91; i += 0.1)
// 	{		
// 		for (double j = 1; j <= 100; j += 5)
// 		{			
//  			for (double k = 50; k <= 90; k += 5)
//  			{
// 				data.push_back(i);
// 				data.push_back(j);
// 				data.push_back(k);
// 			}
// 		}		
// 	}
// // 	data.push_back(1);
// // 	data.push_back(2);
// // 	for (double i =5; i <= 10; i += 5)
// // 	{
// // 		data.push_back(i);
// // 	}
// // 	for (double i = 50; i <= 60; i += 5)
// // 	{
// // 		data.push_back(i);
// // 	}
// // 	double* temp = new double [data.size()];
// 
// 	//getCombinations(combinations, data, temp, 0, data.size() - 1, 0, 3);
// 
// 	//delete [] temp;
// 	//data.clear();
// 	remove(CConfig::getInstance()->getValue(LogFile).c_str());
// 	double max_success = 0.0;
// 	double curr_LR = 0.0;
// 	for (int i = 0; i < data.size();)
// 	{
// // 		if (curr_LR != data[i])
// // 		{
// // 			std::stringstream str;
// // 			str << "\n" << data[i] << ",";
// // 			CMatrix::print(str.str());
// // 			curr_LR = data[i];
// // 		}
// // 		else
// // 		{
// // 			std::stringstream str;
// // 			str << ",";
// // 			CMatrix::print(str.str());
// // 		}
// 		char arr[16];
// 		sprintf(arr, "%f", data[i++]);
// 		CConfig::getInstance()->setValue("LearningRate", arr);
// 		sprintf(arr, "%.0f", data[i++]);
// 		CConfig::getInstance()->setValue("HiddenLayerNodeCount", arr);
// 		sprintf(arr, "%.0f", data[i++]);
// 		CConfig::getInstance()->setValue("TrainingSize", arr);
// 
// 		preprocess();
// 		partition(atoi(CConfig::getInstance()->getValue(TrainingSize).c_str()));
// 
// 		double success = ANN();
// // 		std::stringstream str;
// // 		str << success;
// // 		CMatrix::print(str.str());
// 
// 		if (success > max_success)
// 		{
// 			max_success = success;
// 		}
// 	}
// 
// 	std::stringstream str;
// 	str << "Max Success Rate: " << max_success << "%.\n";
// 	CMatrix::print(str.str(), CConfig::getInstance()->getValue(LogFile));
// 	std::cout << str.str() << std::endl;
// 
// 	return true;
// }


