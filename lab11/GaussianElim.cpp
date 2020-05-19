#include <iostream>
#include <cstdio>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
using namespace std; 

class Matrix {
	public:
		int rows, columns;
		double ** matrix;
		Matrix(int r, int c)
		{
			rows = r;
			columns = c;
			matrix = new double*[rows];
			for (int i = 0; i < rows; i++)
				matrix[i] = new double[columns];
			for (int i = 0; i < rows; i++) {
				string row_data;
				printf("Enter row %d with a space in between each element: ", i+1);
				getline(cin, row_data);
				int* result = parseInput(row_data);
				for (int j = 0; j < columns; j++) {
					matrix[i][j] = result[j];
				}
			}
		}
		~Matrix()
		{
			for (int i = 0; i < rows; i++)
				delete []matrix[i];
			delete []matrix;    
		}
		void swap_row(int i, int j) 
		{ 
			//printf("Swapped rows %d and %d\n", i, j); 
			for (int k = 0; k <= rows; k++) { 
				double temp = matrix[i][k]; 
				matrix[i][k] = matrix[j][k]; 
				matrix[j][k] = temp; 
			} 
		}
		int forwardElim() 
		{ 
			for (int i = 0; i < rows; i++) 
			{ 
				int i_max = i; 
				int v_max = matrix[i_max][i]; 
				for (int j = i + 1; j < rows; j++) {
					if (abs(matrix[j][i]) > v_max) {
						v_max = matrix[j][i];
						i_max = j;
					}
				}
				if (!matrix[i][i_max]) 
					return i;
				if (i_max != i) 
					swap_row(i, i_max); 
				for (int j = i + 1; j < rows; j++) { 
					double f = matrix[j][i]/matrix[i][i]; 
					for (int k = i + 1; k <= rows; k++) 
						matrix[j][k] -= matrix[i][k]*f; 
					matrix[j][i] = 0; 
				} 
			} 
			return -1; 
		}
		void backSub() 
		{ 
			double result[rows];  // An array to store solution 
			for (int i = rows - 1; i >= 0; i--) { 
				result[i] = matrix[i][columns-1]; 
				for (int j = i + 1; j < rows; j++)
					result[i] -= matrix[i][j] * result[j]; 
				result[i] = result[i] / matrix[i][i]; 
			} 
			printf("Solution for the system:\n"); 
			for (int i = 0; i < rows; i++)
				printf("x%d = %lf\n", i+1, result[i]);
		}
		void gaussianElimination() 
		{ 
            /* Reduce matrix to row echelon form */
			int singular_flag = forwardElim(); 
			if (singular_flag != -1) { 
				printf("This matrix is singular: "); 
				if (matrix[singular_flag][rows]) 
					printf("Inconsistent System.\n"); 
				else
					printf("May have infinitely many solutions.\n"); 

				return; 
			}
            /* Reduce further to reduced row echelon form */
			backSub();
		}
		void print() 
		{
			for (int i = 0; i < rows; i++, printf("\n")) 
				for (int j = 0; j < columns; j++) 
					printf("%lf ", matrix[i][j]); 
			printf("\n"); 
		}
		int* parseInput(string arg)
		{
			string temp;
			int found = 0;
			int j = 0;
			int* result = new int[columns];
			/* fill array with 0s */
			for (int i = 0; i < columns; i++)
				result[i] = 0;
			/* separate integers from string and load them into result */
			stringstream ss;
			ss << arg;
			while (!ss.eof()) {
				ss >> temp;
				if (stringstream(temp) >> found) {
					result[j] = found; 
					j++;
				}
				temp = "";
			}
			return result;
		}
};

int main() 
{
	int rows, columns;
	printf("Enter amount of rows for the matrix: ");
	cin >> rows;
	printf("Enter amount of columns for the matrix: ");
	cin >> columns;
	cin.ignore(1,'\n');
	if (rows <= 0 || columns <= 0) {
		printf("\nMatrix cannot be formed with those parameters...\n");
		exit(1);
	}
	Matrix mat(rows, columns);
	printf("\nHere is the initial matrix:\n");
	mat.print();
	mat.gaussianElimination();
	return 0;
}
