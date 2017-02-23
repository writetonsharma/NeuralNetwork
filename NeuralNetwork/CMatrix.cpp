
#include "CMatrix.h"
#include <iostream>
#include <time.h>
#include <fstream>

double** CMatrix::allocateMatrix(u_int row, u_int col)
{
	double ** matrix = new double* [row];
	//memset(matrix, 0, sizeof(double*) * row);
	for(u_int i = 0;i < row;i++)
	{
		matrix[i] = new double [col];
		memset(matrix[i], 0, sizeof(double*) * col);
	}
	return matrix;
}

void CMatrix::freeMatrix(double** matrix, u_int row, u_int col)
{
	for(u_int i = 0;i < row;i++)
	{
		delete [] matrix[i];
		matrix[i] = 0;
	}
	delete [] matrix;
	matrix = 0;
}

void CMatrix::fillRandomMatrix(double** matrix, u_int row, u_int col)
{
	srand(clock());
	for(u_int i = 0;i < row;i++)
	{
		for(u_int j = 0;j < col;j++)
		{
			matrix[i][j] = ((double) rand() / (RAND_MAX)) - 0.5;
		}
	}
}
void CMatrix::fillMatrixWithValue(double** matrix, u_int row, u_int col, u_int value)
{
	for(u_int i = 0;i < row;i++)
	{
		for(u_int j = 0;j < col;j++)
		{
			matrix[i][j] = value;
		}
	}
}


void CMatrix::printMatrix(double** matrix, std::string name, u_int row, u_int col,
							std::string fileName, bool printToFile)
{
	std::ostream* os;
	std::filebuf fb;
	if (!printToFile)
	{
		os = new std::ostream(std::cout.rdbuf());
	}
	else
	{		
		fb.open(fileName.c_str(), std::ios::out | std::ios::app);
		os = new std::ostream(&fb);
	}

	*os << std::endl << "Printing matrix \'" << name << "\'" << std::endl;
	for (u_int i = 0; i < row; i++)
	{
		for (u_int j = 0; j < col; j++)
		{
			*os << matrix[i][j] << "\t";
		}
		*os << std::endl;
	}
	fb.close();
	delete os;
}

void CMatrix::print(std::string name, std::string fileName, bool printToFile)
{
	std::ostream* os;
	std::filebuf fb;
	if (!printToFile)
	{
		os = new std::ostream(std::cout.rdbuf());
	}
	else
	{
		fb.open(fileName.c_str(), std::ios::out | std::ios::app);
		os = new std::ostream(&fb);
	}

	*os << name;

	fb.close();
	delete os;

}

void CMatrix::dotProduct(double** m1, u_int m1_r, u_int m1_c, 
				double** m2, u_int m2_r, u_int m2_c, 
				double** r, u_int& r_r, u_int& r_c, bool allocate)
{
	// validate
	if(m1_r != m2_r || m1_c != m2_c)
	{
		std::cout << "Invalid dimensions." << std::endl;
		return;
	}

	// update dimensions of the new matrix to be sent back
	r_r = m1_r;
	r_c = m1_c;
	if(allocate)
	{
		r = allocateMatrix(r_r, r_c);		// should be freed by client;
	}

	for(u_int i = 0;i < r_r;i++)
	{
		for (u_int j = 0;j < r_c;j++)
		{
			r[i][j] = m1[i][j] * m2[i][j];
		}
	}
	return;
}

void CMatrix::dotProduct(double value,
					   double** m1, u_int m1_r, u_int m1_c)
{
	for(u_int i = 0;i < m1_r;i++)
	{
		for (u_int j = 0;j < m1_c;j++)
		{
			m1[i][j] *= value;
		}
	}
	return;
}

void CMatrix::vectorProduct(double** m1, u_int m1_r, u_int m1_c, 
				   double** m2, u_int m2_r, u_int m2_c, 
				   double** r, u_int& r_r, u_int& r_c, bool allocate)
{
	// validate
	if(m1_c != m2_r)
	{
		std::cout << "Invalid dimensions." << std::endl;
		return;
	}

	// update dimensions of the new matrix to be sent back
	r_r = m1_r;
	r_c = m2_c;
	if(allocate)
	{
		r = allocateMatrix(r_r, r_c);		// should be freed by client;
	}

	// reset the matrix
	for (u_int i = 0; i < r_r; i++)
	{
		for (u_int j = 0; j < r_c; j++)
		{
			r[i][j] = 0.0;
		}
	}

	for (u_int i = 0; i < r_r; i++) 
	{  
		for (u_int j = 0; j < r_c; j++) 
		{  
			for (u_int k = 0; k < m1_c; k++) 
			{  
				r[i][j] += m1[i][k] * m2[k][j];
			}  
		}  
	}  
}


void CMatrix::difference(double** m1, u_int m1_r, u_int m1_c, 
					   double** m2, u_int m2_r, u_int m2_c, 
					   double** r, u_int& r_r, u_int& r_c, bool allocate)
{
	// validate
	if(m1_r != m2_r || m1_c != m2_c)
	{
		std::cout << "Invalid dimensions." << std::endl;
		return;
	}

	// update dimensions of the new matrix to be sent back
	r_r = m1_r;
	r_c = m1_c;
	if(allocate)
	{
		r = allocateMatrix(r_r, r_c);		// should be freed by client;
	}

	for(u_int i = 0;i < r_r;i++)
	{
		for (u_int j = 0;j < r_c;j++)
		{
			r[i][j] = m1[i][j] - m2[i][j];
		}
	}
	return;
}

void CMatrix::sum(double** m1, u_int m1_r, u_int m1_c, 
						 double** m2, u_int m2_r, u_int m2_c, 
						 double** r, u_int& r_r, u_int& r_c, bool allocate)
{
	// validate
	if(m1_r != m2_r || m1_c != m2_c)
	{
		std::cout << "Invalid dimensions." << std::endl;
		return;
	}

	// update dimensions of the new matrix to be sent back
	r_r = m1_r;
	r_c = m1_c;
	if(allocate)
	{
		r = allocateMatrix(r_r, r_c);		// should be freed by client;
	}

	for(u_int i = 0;i < r_r;i++)
	{
		for (u_int j = 0;j < r_c;j++)
		{
			r[i][j] = m1[i][j] + m2[i][j];
		}
	}
	return;
}

void CMatrix::sum(double** m1, u_int m1_r, u_int m1_c, 
				  double** m2, u_int m2_r, u_int m2_c)
{
	// validate
	if(m1_r != m2_r || m1_c != m2_c)
	{
		std::cout << "Invalid dimensions." << std::endl;
		return;
	}

	for(u_int i = 0;i < m1_r;i++)
	{
		for (u_int j = 0;j < m1_c;j++)
		{
			m1[i][j] = m1[i][j] + m2[i][j];
		}
	}
	return;
}

void CMatrix::transpose(double** m1, u_int m1_r, u_int m1_c, 
					  double** r, u_int& r_r, u_int& r_c, bool allocate)
{

	r_r = m1_c;
	r_c = m1_r;
	if(allocate)
	{
		r = allocateMatrix(r_r, r_c);
	}

	for(u_int i = 0;i < m1_r;i++)
	{
		for (u_int j = 0;j < m1_c;j++)
		{
			r[j][i] = m1[i][j];
		}
	}

	return;
}

void CMatrix::copy(double** m1, u_int m1_r, u_int m1_c,
					double** r, bool allocate)
{
	if (allocate)
	{
		r = allocateMatrix(m1_r, m1_c);		// should be freed by client;
	}

	for (u_int i = 0; i < m1_r; i++)
	{
		for (u_int j = 0; j < m1_c; j++)
		{
			r[i][j] = m1[i][j];
		}
	}
	return;
}


