#include <vector>

class Edge{
public:
	int x;//上端点的x坐标。
	int ymax;//最大的y值。
	int dx;//y增加1后x的变化。
	int yCount;//记录该边跨越了多少行扫描线。
	int PolyId;//所属的多边形的id。
	
	Edge *next;//指向边表中的下一条。
	//Edge *polyNext;//指向所属多边形边环中的下一条。
	Edge():next(NULL){}
};

class Polygon{
public:
	double A, B, C, D;
	int id;
	int yCount;//记录该多边形跨越了多少行扫描线。

	Polygon *next;

	
	vector<Edge*> edges;
	Polygon():next(NULL){
		
	}
};

class ActivePoly{
public:

	double A, B, C, D;//用来确定平面的四个值。知道就好。
	int yCount;//这条直线跨过了多少个y的行。
	int polyId;//指向的多边形的id。

	ActivePoly* next;
	Edge* edgeLine[3000];//记得以后这里要修改的
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
	int polyId;//指向的多边形的id。
	ActiveEdge *next;
	ActiveEdge():next(NULL){}
};



