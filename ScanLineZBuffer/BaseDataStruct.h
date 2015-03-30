//this file is describe some base data struct that been encapsule again in DataUtility.h
#pragma once
#include<iostream>
#include<math.h>
using namespace std;

#define TPLmntT template<int m, int n, int t, typename T>
#define TPLmnT template<int m, int n, typename T>
#define TPLnT template<int n, typename T>
#define MatmnT Matrix<m, n, T>
#define MatnmT Matrix<n, m, T>
#define MatnnT Matrix<n, n, T>
#define MatmmT Matrix<m, m, T>
#define MatmtT Matrix<m ,t, T>
#define MatntT Matrix<n ,t, T>
#define Mat1nT Matrix<1, n, T>
#define Mat1mT Matrix<1, m, T>
#define TuplenT Tuple<n, T>
#define TuplemT Tuple<m, T>

//use to describe point and vector,so i named it Tuple rather than point or vector.
template <int size, typename T = float>
class Tuple{
//notice that: class data member is not been arranged by the order of the defined, so 
//some error may happen when use glPointArray to get the vertex information.
public:
	T m_data[size];
	int m_size;
	Tuple(){
		m_size = size;
	}
	//there may be some error when the size is less than 3, but you use the m_data[2].
	//so ensure your Tuple is more than 3 in that situation
	Tuple(T x){
		m_data[0] = x;
		m_size = size;
	}
	Tuple(T x, T y){
		m_size = size;
		if(size >= 2){
			m_data[0] = x;
			m_data[1] = y;
		}else{
			printf("Tuple the array size is less than 2\n");
		}

	}
	Tuple(T x, T y, T z){
		m_size = size;
		if(size >= 3){
			m_data[0] = x;
			m_data[1] = y;
			m_data[2] = z;
		}else{
			printf("Tuple the array size is less than 3\n");
		}	
	}
	Tuple(T t[]){
		m_size = size;
		for(int i = 0; i < size; i++){
			m_data[i] = t[i];
		}
	}
	//******************************
	//implement some operation
	//cross production only use int 3 dimensions vector
	T dot(Tuple<size, T> a){
		T d = 0;
		for(int i = 0; i < size; i++){
			d += m_data[i] * a.m_data[i];
		}
		return d;
	}
	Tuple<size, T> cross(Tuple<size, T> a){
		return Tuple<size, T>(m_data[1] * a.m_data[2] - m_data[2] * a.m_data[1], 
				m_data[2] * a.m_data[0] - m_data[0] * a.m_data[2], 
				m_data[0] * a.m_data[1] - m_data[1] * a.m_data[0]);
	}

	T length(){
		return sqrt(this->dot(*this));
	}
	//normalize the tuple
	Tuple<size, T> normalize(){
		T d[size];
		T len = length();;
		for(int i = 0; i < size; i++){
			d[i] = m_data[i] / len;
		}
		return Tuple<size, T>(d);
	}
	//empty
	void empty(){
		for(int i = 0; i < size; i++){
			m_data[i] = 0;
		}
	}
	//show tuple 
	void show(){
		for(int i = 0; i < size; i++){
			printf("%lf\n", m_data[i]);
		}
	}
};

//first i want to write an general template Matrix class, but the work is too tremendous.
//and i just want to create an 2 X 2 matrix. so i suspend this work.
template <int rowSize, int colSize, typename T = float>
class Matrix{
public:
	T m_data[rowSize][colSize];
	int m_rowSize, m_colSize;
	Matrix(){
		m_rowSize = rowSize;
		m_colSize = colSize;
	}
	Matrix(Tuple<colSize, T> a){
		if(rowSize >= 1){
			for(int i = 0; i < colSize; i++){
				m_data[0][i] = a.m_data[i];
			}
		}else{
			printf("Matrix the row size is less than 1\n");
		}
		m_rowSize = rowSize;
		m_colSize = colSize;
	}
	Matrix(Tuple<colSize, T> a, Tuple<colSize, T> b){
		if(rowSize >= 2){
			for(int i =0 ; i < colSize; i++){
				m_data[0][i] = a.m_data[i];
			}
			for(int i =0 ; i < colSize; i++){
				m_data[1][i] = b.m_data[i];
			}
		}else{
			printf("Matrix the row size is less than 2\n");
		}
		m_rowSize = rowSize;
		m_colSize = colSize;
	}
	Matrix(Tuple<colSize, T> a, Tuple<colSize, T> b, Tuple<colSize, T> c){
		if(rowSize >= 2){
			for(int i =0 ; i < colSize; i++){
				m_data[0][i] = a.m_data[i];
			}
			for(int i =0 ; i < colSize; i++){
				m_data[1][i] = b.m_data[i];
			}
			for(int i =0 ; i < colSize; i++){
				m_data[2][i] = c.m_data[i];
			}
		}else{
			printf("Matrix the row size is less than 3\n");
		}
		m_rowSize = rowSize;
		m_colSize = colSize;
	}
	Matrix(T d[]){
		m_rowSize = rowSize;
		m_colSize = colSize;
		int n = rowSize * colSize;
		for(int i = 0; i < n; i++){
			*((T*)m_data + i) = d[i];
		}
	}
	Tuple<rowSize, T> col(int a){
		if(a < colSize){
			Tuple<rowSize, T> t;
			for(int i = 0 ; i < rowSize; i++){
				t.m_data[i] = m_data[i][a];
			}
			return t;
		}else{
			printf("colCount is out the range\n");
		}
	}
	Tuple<colSize, T> row(int a){
		if(a < rowSize){
			Tuple<colSize, T> t;
			for(int i = 0 ; i < colSize; i++){
				t.m_data[i] = m_data[a][i];
			}
			return t;
		}else{
			printf("rowCount is out the range\n");
		}
	}
	//empty
	void empty(){
		for(int i = 0; i < rowSize; i++){
			for(int j = 0; j < colSize; j++){
				m_data[i][j] = 0;
			}
		}
	}
	//show the Matrix
	void show(){
		for(int i = 0; i < rowSize; i++){
			for(int j = 0; j < colSize; j++){
				printf(" %lf", m_data[i][j]);
			}
			printf("\n");
		}
	}
};
//tuple * T and return tuple
TPLnT TuplenT operator * (TuplenT a, T b){
	T d[n];
	for(int i = 0; i < a.m_size; i++){
		d[i] = a.m_data[i] * b;
	}
	return TuplenT(d);
}
//T * tuple and return tuple
TPLnT TuplenT operator * (T a, TuplenT b){
	T d[n];
	for(int i = 0; i < b.m_size; i++){
		d[i] = b.m_data[i] * a;
	}
	return TuplenT(d);
}
//tuple * tuple and return T
TPLnT T operator * (TuplenT a, TuplenT b){
	T d = 0;
	for(int i = 0; i < a.m_size; i++){
		d += a.m_data[i] * b.m_data[i];
	}
	return d;
}
//tuple + tuple and return tuple
TPLnT TuplenT operator + (TuplenT a, TuplenT b){
	T d[n];
	for(int i = 0; i < a.m_size; i++){
		d[i] = a.m_data[i] + b.m_data[i];
	}
	return TuplenT(d);
}
//implement += operation
TPLnT void operator += (TuplenT &a, TuplenT &b){
	for(int i = 0; i < a.m_size; i++){
		a.m_data[i] += b.m_data[i];
	}
}
//tuple - tuple and return tuple
TPLnT TuplenT operator - (TuplenT a, TuplenT b){
	T d[n];
	for(int i = 0; i < a.m_size; i++){
		d[i] = a.m_data[i] - b.m_data[i];
	}
	return TuplenT(d);
}
//tuple * matrix and return matrix 
TPLmnT MatmnT operator * (TuplemT a, Mat1nT b){
	T d[m * n];
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			d[i * n + j] = a.m_data[i] * b.m_data[0][j];
		}
	}
	return MatmnT(d);
}
//matrix * matrix and return matrix
TPLmntT MatntT operator * (MatnmT a, MatmtT b){
	T d[n][t];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < t; j++){
			d[i][j] = 0;
			for(int k = 0; k < m; k++){
				d[i][j] += a.m_data[i][k] * b.m_data[k][j];
			}
		}
	}
	return MatntT((T*)d);
}
//matrix * tuple and return tuple
TPLmnT TuplenT operator * (MatnmT a, TuplemT b){
	T d[n];
	for(int i = 0; i < n; i++){
		d[i] = 0;
		for(int j = 0; j < m; j++){
			d[i] += a.m_data[i][j] * b.m_data[j];
		}
	}
	return TuplenT(d);
	
}
//matrix + matrix and return matrix
TPLmnT MatmnT operator + (MatmnT a, MatmnT b){
	T d[m][n];
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			d[i][j] = a.m_data[i][j] + b.m_data[i][j];
		}
	}
	return MatmnT((T*)d);
}
//matrix += matrix and return matrix, notice that it must be an reference to the MatmnT, due to 
//you need to change the attribute in the Matmnt.
TPLmnT void operator += (MatmnT &a, MatmnT b){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			a.m_data[i][j] += b.m_data[i][j];
		}
	}
}
//matrix * T and return matrix
TPLmnT MatmnT operator * (MatmnT a, T b){
	T d[m][n];
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			d[i][j] = a.m_data[i][j] * b;
		}
	}
	return MatmnT((T*)d);
}
//T * matrix and return matrix
TPLmnT MatmnT operator * (T a, MatmnT b){
	T d[m][n];
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			d[i][j] = b.m_data[i][j] * a;
		}
	}
	return MatmnT((T*)d);
}
//T * matrix and return matrix
TPLmnT MatmnT operator + (T a, MatmnT b){
	T d[m][n];
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			d[i][j] = a * b.m_data[i][j];
		}
	}
	return MatmnT((T*)d);
}

TPLmnT MatmnT multiByPos(MatmnT a, MatmnT b){
	T d[m][n];
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			d[i][j] = a.m_data[i][j] * b.m_data[i][j];
		}
	}
	return MatmnT((T*)d);
}

//change matrix to 1 / matrix by elements
TPLmnT MatmnT changeByDivideOne(MatmnT* a){
	T d[m][n];
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n ; j++){
			d[i][j] = 1 / a->m_data[i][j]; 
		}
	}
	return MatmnT((T*)d);
}
TPLnT TuplenT changeByDivideOne(TuplenT* a){
	T d[n];
	for(int i = 0; i < n; i++){
		
		d[i] = 1 / a->m_data[i]; 
		
	}
	return TuplenT(d);
}
//change matrix to sqrt(matrix) by elements
TPLmnT MatmnT changeBysqrt(MatmnT* a){
	T d[m][n];
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n ; j++){
			d[i][j] = sqrt(a->m_data[i][j]); 
		}
	}
	return MatmnT(d);
}
TPLnT TuplenT changeBySqrt(TuplenT* a){
	T d[n];
	for(int i = 0; i < n; i++){
		
		d[i] = sqrt(a->m_data[i]); 
		
	}
	return TuplenT(d);
}

//use pointer to accelerate program below;
TPLmnT void transpose(MatmnT* a, MatnmT* b){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			b->m_data[i][j] = a->m_data[j][i];
		}
	}
}
TPLmnT MatnmT transpose(MatmnT* a){
	MatnmT re;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
		re.m_data[i][j] = a->m_data[j][i];
		}
	}
	return re;
}
TPLnT Mat1nT transpose(TuplenT* a){
	return Mat1nT(a->m_data);
}
TPLnT void getIdentity(MatnnT* a){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j){
				a->m_data[i][j] = 1;
			}else{
				a->m_data[i][j] = 0;
			}
		}
	}
}
template<typename T> T det(Matrix<2, 2, T>* a){
	return a->m_data[0][0] * a->m_data[1][1] - a->m_data[1][0] * a->m_data[0][1];
}
template<typename T> T det(Matrix<3, 3, T>* a){
	return a->row(0) * (a->row(1).cross(a->row(2)));
}	

template<typename T> void inverse(Matrix<2, 2, T>* a, Matrix<2, 2, T>* b){
	//just due to mutiplication is faster than division.
	T invDet = 1/ det(a);
	b->m_data[0][0] = a->m_data[1][1] * invDet;
	b->m_data[1][1] = a->m_data[0][0] * invDet;
	b->m_data[0][1] = -a->m_data[0][1] * invDet;
	b->m_data[1][0] = -a->m_data[1][0] * invDet;
}
//unbelievable! i just make the inverse wrong
template<typename T> Matrix<2, 2, T> inverse(Matrix<2, 2, T>* a){
	Matrix<2, 2, T> re;
	T invDet = 1/ det(a);
	re.m_data[0][0] = a->m_data[1][1] * invDet;
	re.m_data[1][1] = a->m_data[0][0] * invDet;
	re.m_data[0][1] = -a->m_data[0][1] * invDet;
	re.m_data[1][0] = -a->m_data[1][0] * invDet;
	return re;
}

template<typename T> void inverse(Matrix<3, 3, T>* a, Matrix<3, 3, T>* b){
	//just due to mutiplication is faster than division.
	int invDet = 1 / det(a);
	Tuple<3, T> t1 = (Tuple<3, T>(a->m_data[1]).cross(Tuple<3, T>(m_data[2]))) * invDet;
	Tuple<3, T> t2 = (Tuple<3, T>(a->m_data[2]).cross(Tuple<3, T>(m_data[0]))) * invDet;
	Tuple<3, T> t3 = (Tuple<3, T>(a->m_data[0]).cross(Tuple<3, T>(m_data[1]))) * invDet;
	for(int i = 0; i < 3; i++){
		b->data[i][0] = t1.m_data[i];
		b->data[i][1] = t2.m_data[i];
		b->data[i][2] = t3.m_data[i];
	}
}
template<typename T> Matrix<3, 3, T> inverse(Matrix<3, 3, T>* a){
	Matrix<3, 3, T> re;
	int invDet = 1 / det(a);
	Tuple<3, T> t1 = (Tuple<3, T>(a->m_data[1]).cross(Tuple<3, T>(m_data[2]))) * invDet;
	Tuple<3, T> t2 = (Tuple<3, T>(a->m_data[2]).cross(Tuple<3, T>(m_data[0]))) * invDet;
	Tuple<3, T> t3 = (Tuple<3, T>(a->m_data[0]).cross(Tuple<3, T>(m_data[1]))) * invDet;
	for(int i = 0; i < 3; i++){
		re.data[i][0] = t1.m_data[i];
		re.data[i][1] = t2.m_data[i];
		re.data[i][2] = t3.m_data[i];
	}
	return re;
}