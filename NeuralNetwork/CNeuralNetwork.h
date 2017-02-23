

#ifndef __C_NEURALNETWORK_H__
#define __C_NEURALNETWORK_H__

#include "miscdef.h"

class CNeuralNetwork
{

private:
	u_int	m_inputNodes;		// number of input layer nodes
	u_int	m_hiddenNodes;		// number of hidden layer nodes
	u_int	m_outputNodes;		// number of output layer nodes
	double	m_learningRate;		// learning rate
	u_int m_trainingSize;		// training%, test% will be 100-training%

	double**	m_weight_input_hidden_matrix;		// weight matrix of input-hidden layer, (m_hiddenNodes x m_inputNodes)
	double**	m_weight_hidden_output_matrix;		// weight matrix of hidden-output layer, (m_outputNodes x m_hiddenNodes)
	double**	m_inputs_matrix;					// inputs to the network, (m_inputNodes x 1)
	double**	m_X_hidden;			// X = (W * I) for hidden layer, (m_hiddenNodes x 1)
	//double**	m_O_hidden;			// O = sigmoid(X) for hidden layer, (m_hiddenNodes x 1)
	double**	m_X_output;			// X = (W * I) for output layer, (m_outputNodes x 1)
	//double**	m_O_output;			// O = sigmoid(X) for output layer, (m_outputNodes x 1)
	double**	m_error_output;		// error in output layer, target - m_X_output, (m_outputNodes x 1)
	double**	m_error_hidden;		// error in hidden layer, (m_hiddenNodes x 1)
	double**	m_unit_matrix;		// unit matrix, (m_outputNodes x 1)

	double**	m_temp_matrix_output;	// temporary, (m_outputNodes x m_outputNodes)
	double**	m_temp1_matrix_output;	// temporary, (m_outputNodes x m_outputNodes)
	double**	m_temp2_matrix_output;	// temporary, (m_outputNodes x m_outputNodes)

	u_int		m_maxNode;

	// methods
	void activationFunction(double**, u_int, u_int);
	void update_weight_hidden_output_layer();
	void update_weight_input_hidden_layer(double** inputMatrix);

	bool valid();
public:
	CNeuralNetwork();
	CNeuralNetwork(u_int inputNodes, u_int hiddenNodes, u_int outputNodes, double learningRate, u_int trainingSize);
	~CNeuralNetwork();

	u_int getInputNodes();
	void setInputNodes(u_int);
	
	u_int getHiddenNodes();
	void setHiddenNodes(u_int);

	u_int getOutputNodes();
	void setOutputNodes(u_int);

	double getLearningRate();
	void setLearningRate(double);

	void train();
	void train(double** inputMatrix, double** targetMatrix);		// input passed by client
	
	void query(double** inputMatrix, double** targetMatrix);		// input passed by client



};
#endif


