
#include <iostream>

extern "C" int  __cdecl ProcessNeuralNetwork(char* configFile);

void main()
{
	ProcessNeuralNetwork("D:\\personal\\Code\\NeuralNetwork\\Config\\_nnConfig.ini");

	return;
}