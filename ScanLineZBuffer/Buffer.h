#pragma once


template <typename T>
class Buffer{
public:
	T *data;
	int szOfRows, szOfCols;

	Buffer(int szOfRows, int szOfCols, T initValue = 0){
		data = new T[szOfRows * szOfCols];//��ʱ��һά����ģ���ά���顣

		int tmp = szOfRows * szOfCols;
		for(int i = 0; i < tmp ; i++){
			data[i] = initValue;
		}

	}

	T& at(int x, int y){
		return data[x * szOfRows + y];
	}



};