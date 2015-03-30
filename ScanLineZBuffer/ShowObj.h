
#include "Solid.h"
#include "ScanBaseStruct.h"
#include "Scene.h"
#include "Buffer.h"


class ShowObj{
private:
	
	class AsmPoly{
	public:
		Polygon *first;
		Polygon *last;
		AsmPoly():first(NULL),last(NULL){
		
		}

	};//������ݽṹ����ʱ������α�ʹ�õ�,�����ڹ�����Ĺ����е���ӹ��̡�
	class AsmEdge{
	public:
		Edge *first;
		Edge *last;
		AsmEdge():first(NULL),last(NULL){}
	};//������ݽṹ����ʱ���߱�ʹ�õ�,�����ڹ�����Ĺ����е���ӹ��̡�


	AsmPoly polyLine[3000];//��ʾ��yֵ��Ϊ����Ķ���η���������
	

	int width, height;


	vector<Polygon> polygons;//����ģ�͵����ж����ȫ���洢�����


	int polyCounts;

public:
	ShowObj();
	ShowObj(int, int);
	void InitStruct(Scene s);
	Buffer<double> CreateZBuffer();

};