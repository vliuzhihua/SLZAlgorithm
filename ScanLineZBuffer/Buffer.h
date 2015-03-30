#pragma once


template <typename T>
class Buffer{
public:
	T *data;
	int szOfRows, szOfCols;

	Buffer(int szOfRows, int szOfCols, T initValue = 0){
		data = new T[szOfRows * szOfCols];//暂时以一维数组模拟二维数组。

		int tmp = szOfRows * szOfCols;
		for(int i = 0; i < tmp ; i++){
			data[i] = initValue;
		}

	}

	T& at(int x, int y){
		return data[x * szOfRows + y];
	}



};