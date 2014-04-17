#pragma once

// This class is build with SuperLU 4.3, referece can be found in the following lin: 
// http://crd-legacy.lbl.gov/~xiaoye/SuperLU/

#include <iostream>
#include "SparseMatrixData.h"
#include "RC.h"

class SparseMatrix
{
	SparseMatrixData *data; 
	RC *rc; 
public:
	// SparseMatrix( int rows, int cols );
	SparseMatrix( int num_rows, int num_cols, 
		const double non_zero_value[], 
		const int col_index[], 
		const int row_pointer[], 
		int N );
	const SparseMatrix& operator=( const SparseMatrix& matrix ); 	
	SparseMatrix( const SparseMatrix& matrix );
	const SparseMatrix clone(void) const;
	~SparseMatrix(void);

	inline const int row() const { return data->row(); } 
	inline const int col() const { return data->col(); } 

	const SparseMatrix& operator*=( const double& value ); 
	const SparseMatrix& operator/=( const double& value ); 

	// Transpose a matrix
	const SparseMatrix t() const;

	friend void solve( const SparseMatrix& A, const double* B, double* X ); 
	friend const SparseMatrix multiply( const SparseMatrix& m1, const SparseMatrix& m2 ); 
	friend const SparseMatrix multiply_transpose( const SparseMatrix& m1, const SparseMatrix& m2 ); 
	friend const SparseMatrix operator/( const SparseMatrix& m1, const SparseMatrix& m2 ); 
	friend const SparseMatrix operator*( const SparseMatrix& m1, const SparseMatrix& m2 ); 
	friend const SparseMatrix operator+( const SparseMatrix& m1, const SparseMatrix& m2 ); 
	friend const SparseMatrix operator-( const SparseMatrix& m1, const SparseMatrix& m2 ); 
	friend std::ostream& operator<<( std::ostream& out, const SparseMatrix& m );
};
