
#ifndef __C_MATRIX_H__
#define __C_MATRIX_H__

#include <string>

typedef unsigned int u_int;

class CMatrix
{
private:

public:

	CMatrix() {}
	~CMatrix() {}

	static void dotProduct(double** m1, u_int m1_r, u_int m1_c, 
							double** m2, u_int m2_r, u_int m2_c, 
							double** r, u_int& r_r, u_int& r_c, bool allocate);
	static void dotProduct(double value,
							double** m2, u_int m2_r, u_int m2_c);
	static void vectorProduct(double** m1, u_int m1_r, u_int m1_c, 
							double** m2, u_int m2_r, u_int m2_c, 
							double** r, u_int& r_r, u_int& r_c, bool allocate);

	static void difference(double** m1, u_int m1_r, u_int m1_c, 
							double** m2, u_int m2_r, u_int m2_c, 
							double** r, u_int& r_r, u_int& r_c, bool allocate);
	static void sum(double** m1, u_int m1_r, u_int m1_c, 
							double** m2, u_int m2_r, u_int m2_c, 
							double** r, u_int& r_r, u_int& r_c, bool allocate);
	static void sum(double** m1, u_int m1_r, u_int m1_c, 
							double** m2, u_int m2_r, u_int m2_c);

	static void transpose(double** m1, u_int m1_r, u_int m1_c, 
							double** r, u_int& r_r, u_int& r_c, bool allocate);
	static void copy(double** m1, u_int m1_r, u_int m1_c,
							double** r, bool allocate);

	static void fillRandomMatrix(double** matrix, u_int row, u_int col);
	static void fillMatrixWithValue(double** matrix, u_int row, u_int col, u_int value);
	static void printMatrix(double** matrix, std::string name, u_int row, u_int col,
								std::string fileName, bool printToFile = true);
	static void print(std::string name, std::string fileName = "neuralnetwork.log", bool printToFile = true);

	static double** allocateMatrix(u_int row, u_int col);
	static void freeMatrix(double** matrix, u_int row, u_int col);

};
#endif


