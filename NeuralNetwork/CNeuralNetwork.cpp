
#include "CNeuralNetwork.h"
#include "CMatrix.h"
#include "miscdef.h"
#include "CConfig.h"
#include "IniSettings.h"


CNeuralNetwork::CNeuralNetwork() :
				m_inputNodes(0),
				m_hiddenNodes(0),
				m_outputNodes(0),
				m_learningRate(0.0),
				m_weight_hidden_output_matrix(0),
				m_weight_input_hidden_matrix(0),
				m_inputs_matrix(0)
{
	std::cout << "NN initialized to zero." << std::endl;
}

CNeuralNetwork::CNeuralNetwork(u_int inputNodes, u_int hiddenNodes, 
	u_int outputNodes, double learningRate, u_int trainingSize) :
	m_inputNodes(inputNodes),
	m_hiddenNodes(hiddenNodes),
	m_outputNodes(outputNodes),
	m_learningRate(learningRate),
	m_trainingSize(trainingSize),
	m_weight_hidden_output_matrix(0),
	m_weight_input_hidden_matrix(0),
	m_inputs_matrix(0)
{
	std::stringstream strstr;
	strstr << "Input nodes: " << m_inputNodes << std::endl
		<< "Hidden nodes: " << m_hiddenNodes << std::endl
		<< "Output nodes: " << m_outputNodes << std::endl
		<< "Learning rate: " << m_learningRate << std::endl
		<< "Training size: " << m_trainingSize << std::endl;
	CMatrix::print(strstr.str(), CConfig::getInstance()->getValue(LogFile));

	if (m_inputNodes > m_hiddenNodes)
	{
		m_maxNode = m_inputNodes;
		if (m_outputNodes > m_inputNodes)
		{
			m_maxNode = m_outputNodes;
		}
	}
	else
	{
		m_maxNode = m_hiddenNodes;
		if (m_outputNodes > m_hiddenNodes)
		{
			m_maxNode = m_outputNodes;
		}
	}

	m_weight_input_hidden_matrix = CMatrix::allocateMatrix(m_hiddenNodes, m_inputNodes);
	CMatrix::fillRandomMatrix(m_weight_input_hidden_matrix, m_hiddenNodes, m_inputNodes);
	std::string str = "input_hidden";
	//CMatrix::printMatrix(m_weight_input_hidden_matrix, str, m_hiddenNodes, m_inputNodes, "neuralnetwork.log", true);

	m_weight_hidden_output_matrix = CMatrix::allocateMatrix(m_outputNodes, m_hiddenNodes);
	CMatrix::fillRandomMatrix(m_weight_hidden_output_matrix, m_outputNodes, m_hiddenNodes);
	str = "hidden_output";
	//CMatrix::printMatrix(m_weight_hidden_output_matrix, str, m_outputNodes, m_hiddenNodes, "neuralnetwork.log", true);

	m_inputs_matrix = CMatrix::allocateMatrix(m_inputNodes, 1);
	m_X_hidden = CMatrix::allocateMatrix(m_hiddenNodes, 1);
	m_X_output = CMatrix::allocateMatrix(m_outputNodes, 1);
	m_error_output = CMatrix::allocateMatrix(m_outputNodes, 1);
	m_error_hidden = CMatrix::allocateMatrix(m_hiddenNodes, 1);
	m_unit_matrix = CMatrix::allocateMatrix(m_maxNode, m_maxNode);
	CMatrix::fillMatrixWithValue(m_unit_matrix, m_maxNode, m_maxNode, 1);

	m_temp_matrix_output = CMatrix::allocateMatrix(m_maxNode, m_maxNode);
	m_temp1_matrix_output = CMatrix::allocateMatrix(m_maxNode, m_maxNode);
	m_temp2_matrix_output = CMatrix::allocateMatrix(m_maxNode, m_maxNode);

}

CNeuralNetwork::~CNeuralNetwork()
{
	CMatrix::freeMatrix(m_weight_input_hidden_matrix, m_hiddenNodes, m_inputNodes);
	CMatrix::freeMatrix(m_weight_hidden_output_matrix, m_outputNodes, m_hiddenNodes);
	CMatrix::freeMatrix(m_inputs_matrix, m_inputNodes, 1);
	CMatrix::freeMatrix(m_X_hidden, m_hiddenNodes, 1);
	CMatrix::freeMatrix(m_X_output, m_outputNodes, 1);
	CMatrix::freeMatrix(m_error_output, m_outputNodes, 1);
	CMatrix::freeMatrix(m_error_hidden, m_hiddenNodes, 1);
	CMatrix::freeMatrix(m_unit_matrix, m_maxNode, m_maxNode);
	CMatrix::freeMatrix(m_temp_matrix_output, m_maxNode, m_maxNode);
	CMatrix::freeMatrix(m_temp1_matrix_output, m_maxNode, m_maxNode);
	CMatrix::freeMatrix(m_temp2_matrix_output, m_maxNode, m_maxNode);
}

u_int CNeuralNetwork::getInputNodes()
{
	return m_inputNodes;
}

void CNeuralNetwork::setInputNodes(u_int inputNodes)
{
	m_inputNodes = inputNodes;
}

u_int CNeuralNetwork::getHiddenNodes()
{
	return m_hiddenNodes;
}

void CNeuralNetwork::setHiddenNodes(u_int hiddenNodes)
{
	m_hiddenNodes = hiddenNodes;
}

u_int CNeuralNetwork::getOutputNodes()
{
	return m_outputNodes;
}

void CNeuralNetwork::setOutputNodes(u_int outputNodes)
{
	m_outputNodes = outputNodes;
}

double CNeuralNetwork::getLearningRate()
{
	return m_learningRate;
}

void CNeuralNetwork::setLearningRate(double lr)
{
	m_learningRate = lr;
}

void CNeuralNetwork::train()
{

}

void CNeuralNetwork::train(double** inputMatrix, double** targetMatrix)
{
	if(!valid())
	{
		std::cout << "Invalid neural network." << std::endl;
	}

	// signals from input-hidden layer
	u_int X_r, X_c;
	CMatrix::vectorProduct(m_weight_input_hidden_matrix, m_hiddenNodes, m_inputNodes,
		inputMatrix, m_inputNodes, 1,
		m_X_hidden, X_r, X_c, false);
	//CMatrix::print("m_X_hidden = input-hidden layer weight matrix x input matrix");
	//CMatrix::printMatrix(m_X_hidden, "m_X_hidden", X_r, X_c, "neuralnetwork.log", true);

	//output from hidden layer after applying sigmoid function
	activationFunction(m_X_hidden, X_r, X_c);
	//CMatrix::print("apply activation function to m_X_hidden matrix. 1/(1 + exp(-x))");
	//CMatrix::printMatrix(m_X_hidden, "m_X_hidden after activation function applied", X_r, X_c, "neuralnetwork.log", true);

	// do the same for the hidden-output layer
	CMatrix::vectorProduct(m_weight_hidden_output_matrix, m_outputNodes, m_hiddenNodes,
		m_X_hidden, m_hiddenNodes, 1,
		m_X_output, X_r, X_c, false);
	//CMatrix::print("m_X_output = hidden-output layer weight matrix x m_X_hidden");
	//CMatrix::printMatrix(m_X_output, "m_X_output", X_r, X_c, "neuralnetwork.log", true);

	//output from hidden layer after applying sigmoid function
	activationFunction(m_X_output, X_r, X_c);
	//CMatrix::print("apply activation function to m_X_output matrix. 1/(1 + exp(-x))");
	//CMatrix::printMatrix(m_X_output, "m_X_output after activation function applied", X_r, X_c, "neuralnetwork.log", true);

	// error in output layer - (target - actual)
	CMatrix::difference(targetMatrix, m_outputNodes, 1,
						m_X_output, m_outputNodes, 1,
						m_error_output, X_r, X_c, false);
	//CMatrix::print("calculating error in output layer. (targetMatrix - m_X_output)");
	//CMatrix::printMatrix(m_error_output, "printing error matrix for output layer, m_error_output ", X_r, X_c, "neuralnetwork.log", true);

	// error in hidden layer - (m_weight_hidden_output_matrix)Trans * m_error_output
	//CMatrix::print("calculating error in hidden layer. (transpose[hidden-output layer weights] x error in output layer)");
	//CMatrix::print("transposing hidden-output layer weights");
	//CMatrix::printMatrix(m_weight_hidden_output_matrix, "hidden-output layer weights matrix before transposing ", 
//		m_outputNodes, m_hiddenNodes, "neuralnetwork.log", true);

	CMatrix::transpose(m_weight_hidden_output_matrix, m_outputNodes, m_hiddenNodes,
		m_temp1_matrix_output, X_r, X_c, false);
	//CMatrix::printMatrix(m_temp1_matrix_output, "hidden-output layer weights matrix after transposing ", X_r, X_c, "neuralnetwork.log", true);
	CMatrix::vectorProduct(m_temp1_matrix_output, X_r, X_c,
							m_error_output, m_outputNodes, 1,
							m_error_hidden, X_r, X_c, false);
	//CMatrix::printMatrix(m_error_hidden, "printing error matrix for hidden layer, m_error_hidden ", X_r, X_c, "neuralnetwork.log", true);

	// update weights
	// hidden-output layer
	update_weight_hidden_output_layer();

	update_weight_input_hidden_layer(inputMatrix);
}

void CNeuralNetwork::update_weight_hidden_output_layer()
{
	u_int X_r, X_c;

	//CMatrix::print("#### Backpropagating: Updating weights of hidden-output layer ###");

	//step1: output_error . final_output
	//CMatrix::print("step1: output layer error . final output");
	CMatrix::dotProduct(m_error_output, m_outputNodes, 1,
		m_X_output, m_outputNodes, 1,
		m_temp_matrix_output, X_r, X_c, false);
	//CMatrix::printMatrix(m_temp_matrix_output, "step1 matrix output ", X_r, X_c, "neuralnetwork.log", true);

	// step2: 1 - final_output
	//CMatrix::print("step2: unit matrix - final output");
	CMatrix::difference(m_unit_matrix, m_outputNodes, 1,
		m_X_output, m_outputNodes, 1,
		m_temp1_matrix_output, X_r, X_c, false);
	//CMatrix::printMatrix(m_temp1_matrix_output, "step2 matrix output ", X_r, X_c, "neuralnetwork.log", true);

	// step3: (step1 . step2) (dot product)
	//CMatrix::print("step3: step1 matrix . step2 matrix");
	CMatrix::dotProduct(m_temp_matrix_output, m_outputNodes, 1,
		m_temp1_matrix_output, m_outputNodes, 1,
		m_temp_matrix_output, X_r, X_c, false);
	//CMatrix::printMatrix(m_temp_matrix_output, "step3 matrix output ", X_r, X_c, "neuralnetwork.log", true);

	// step4: transpose of hidden layer error
	//CMatrix::print("step4: transpose[hidden layer output]");
	CMatrix::transpose(m_X_hidden, m_hiddenNodes, 1,
		m_temp1_matrix_output, X_r, X_c, false);
	//CMatrix::printMatrix(m_temp1_matrix_output, "step4 matrix output ", X_r, X_c, "neuralnetwork.log", true);

	// step5: step3 x step4
	//CMatrix::print("step5: step3 matrix x step4 matrix");
	CMatrix::vectorProduct(m_temp_matrix_output, m_outputNodes, 1,
		m_temp1_matrix_output, 1, m_hiddenNodes,
		m_temp2_matrix_output, X_r, X_c, false);
	//CMatrix::printMatrix(m_temp2_matrix_output, "step5 matrix output ", X_r, X_c, "neuralnetwork.log", true);

	// step6: lr . step5
	//CMatrix::print("step6: learning rate . step5 matrix");
	CMatrix::dotProduct(m_learningRate, m_temp2_matrix_output, X_r, X_c);
	//CMatrix::printMatrix(m_temp2_matrix_output, "step6 matrix output ", X_r, X_c, "neuralnetwork.log", true);

	// step7: update the weight
	//CMatrix::print("step7: update the previous weights of hidden-output layer. weight_new = weight_old + delta_weight (step7 matrix)");
	CMatrix::sum(m_weight_hidden_output_matrix, m_outputNodes, m_hiddenNodes,
		m_temp2_matrix_output, X_r, X_c);
	//CMatrix::printMatrix(m_weight_hidden_output_matrix, "step7 matrix, new updated weights of hidden-output layer ", 
//		m_outputNodes, m_hiddenNodes, "neuralnetwork.log", true);

	return;
}

void CNeuralNetwork::update_weight_input_hidden_layer(double** inputMatrix)
{
	u_int X_r, X_c;

	//CMatrix::print("### Backpropagating: Updating weights of input-hidden layer ###");

	//step1: hidden_error . hidden_output
	//CMatrix::print("step1: hidden layer error . hidden layer output");
	CMatrix::dotProduct(m_error_hidden, m_hiddenNodes, 1,
		m_X_hidden, m_hiddenNodes, 1,
		m_temp_matrix_output, X_r, X_c, false);
	//CMatrix::printMatrix(m_temp_matrix_output, "step1 matrix output ", X_r, X_c, "neuralnetwork.log", true);

	// step2: 1 - final_output
	//CMatrix::print("step2: unit matrix - hidden layer output");
	CMatrix::difference(m_unit_matrix, m_hiddenNodes, 1,
		m_X_hidden, m_hiddenNodes, 1,
		m_temp1_matrix_output, X_r, X_c, false);
	//CMatrix::printMatrix(m_temp1_matrix_output, "step2 matrix output ", X_r, X_c, "neuralnetwork.log", true);

	// step3: (step1 . step2) (dot product)
	//CMatrix::print("step3: step1 matrix . step2 matrix");
	CMatrix::dotProduct(m_temp_matrix_output, m_hiddenNodes, 1,
		m_temp1_matrix_output, m_hiddenNodes, 1,
		m_temp_matrix_output, X_r, X_c, false);
	//CMatrix::printMatrix(m_temp_matrix_output, "step3 matrix output ", X_r, X_c, "neuralnetwork.log", true);

	// step4: transpose of hidden layer error
	//CMatrix::print("step4: transpose[input matrix]");
	CMatrix::transpose(inputMatrix, m_inputNodes, 1,
		m_temp1_matrix_output, X_r, X_c, false);
	//CMatrix::printMatrix(m_temp1_matrix_output, "step4 matrix output ", X_r, X_c, "neuralnetwork.log", true);

	// step5: step3 x step4
	//CMatrix::print("step5: step3 matrix x step4 matrix");
	CMatrix::vectorProduct(m_temp_matrix_output, m_hiddenNodes, 1,
		m_temp1_matrix_output, 1, m_inputNodes,
		m_temp2_matrix_output, X_r, X_c, false);
	//CMatrix::printMatrix(m_temp2_matrix_output, "step5 matrix output ", X_r, X_c, "neuralnetwork.log", true);

	// step6: lr . step5
	//CMatrix::print("step6: learning rate . step5 matrix");
	CMatrix::dotProduct(m_learningRate, m_temp2_matrix_output, X_r, X_c);
	//CMatrix::printMatrix(m_temp2_matrix_output, "step6 matrix output ", X_r, X_c, "neuralnetwork.log", true);

	// step7: update the weight
	//CMatrix::print("step7: update the previous weights of input-hidden layer. weight_new = weight_old + delta_weight (step7 matrix)");
	CMatrix::sum(m_weight_input_hidden_matrix, m_hiddenNodes, m_inputNodes,
		m_temp2_matrix_output, X_r, X_c);
	//CMatrix::printMatrix(m_weight_input_hidden_matrix, "step7 matrix, new updated weights of input-hidden layer ", X_r, X_c, "neuralnetwork.log", true);

	return;
}


void CNeuralNetwork::query(double** inputMatrix, double** targetMatrix)
{
	if(!valid())
	{
		std::cout << "Invalid neural network." << std::endl;
	}

	// signals from input-hidden layer
	u_int X_r, X_c;
	CMatrix::vectorProduct(m_weight_input_hidden_matrix, m_hiddenNodes, m_inputNodes,
							inputMatrix, m_inputNodes, 1,
							m_X_hidden, X_r, X_c, false);
	
	//output from hidden layer after applying sigmoid function
	activationFunction(m_X_hidden, X_r, X_c);

	// do the same for the hidden-output layer
	CMatrix::vectorProduct(m_weight_hidden_output_matrix, m_outputNodes, m_hiddenNodes,
		m_X_hidden, m_hiddenNodes, 1,
		m_X_output, X_r, X_c, false);

	//output from hidden layer after applying sigmoid function
	activationFunction(m_X_output, X_r, X_c);
	std::string str = "output";
	//CMatrix::printMatrix(m_X_output, str, X_r, X_c, "neuralnetwork.log", true);

	CMatrix::copy(m_X_output, X_r, X_c, targetMatrix, false);
}

bool CNeuralNetwork::valid()
{
	if(!(m_inputNodes && m_hiddenNodes && m_outputNodes && m_learningRate))
	{
		return false;
	}
	if(!(m_weight_hidden_output_matrix 
		&& m_weight_input_hidden_matrix
		&& m_inputs_matrix))
	{
		return false;
	}
	return true;

}

void CNeuralNetwork::activationFunction(double** matrix, u_int row, u_int col)
{
	for(u_int i = 0;i < row;i++)
	{
		for(u_int j = 0;j < col;j++)
		{
			matrix[i][j] = 1 / (1 + exp(-1 * matrix[i][j]));
		}
	}
}


