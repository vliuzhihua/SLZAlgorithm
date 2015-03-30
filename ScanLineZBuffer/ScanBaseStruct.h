#include <vector>

class Edge{
public:
	int x;//�϶˵��x���ꡣ
	int ymax;//����yֵ��
	int dx;//y����1��x�ı仯��
	int yCount;//��¼�ñ߿�Խ�˶�����ɨ���ߡ�
	int PolyId;//�����Ķ���ε�id��
	
	Edge *next;//ָ��߱��е���һ����
	//Edge *polyNext;//ָ����������α߻��е���һ����
	Edge():next(NULL){}
};

class Polygon{
public:
	double A, B, C, D;
	int id;
	int yCount;//��¼�ö���ο�Խ�˶�����ɨ���ߡ�

	Polygon *next;

	
	vector<Edge*> edges;
	Polygon():next(NULL){
		
	}
};

class ActivePoly{
public:

	double A, B, C, D;//����ȷ��ƽ����ĸ�ֵ��֪���ͺá�
	int yCount;//����ֱ�߿���˶��ٸ�y���С�
	int polyId;//ָ��Ķ���ε�id��

	ActivePoly* next;
	Edge* edgeLine[3000];//�ǵ��Ժ�����Ҫ�޸ĵ�
	ActivePoly(){
		for(int i = 0; i < 3000; i++){
			edgeLine[i] = NULL;
		}
		next = NULL;
	}

};

class ActiveEdge{
public:
	double xl, dxl, dyl, xr, dxr, dyr;
	double zl, dzx, dzy;
	int polyId;//ָ��Ķ���ε�id��
	ActiveEdge *next;
	ActiveEdge():next(NULL){}
};



