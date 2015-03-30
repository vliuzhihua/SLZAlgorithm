
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

	};//这个数据结构是临时给多边形表使用的,加速在构建表的过程中的添加过程。
	class AsmEdge{
	public:
		Edge *first;
		Edge *last;
		AsmEdge():first(NULL),last(NULL){}
	};//这个数据结构是临时给边表使用的,加速在构建表的过程中的添加过程。


	AsmPoly polyLine[3000];//表示以y值作为分类的多边形分类容器。
	

	int width, height;


	vector<Polygon> polygons;//整个模型的所有多边形全部存储在这里。


	int polyCounts;

public:
	ShowObj();
	ShowObj(int, int);
	void InitStruct(Scene s);
	Buffer<double> CreateZBuffer();

};