#pragma warning(disable:4996)
#include <fstream>
#include<iostream>
#include "Solid.h"

Point3d pp[250000];

vector<Point3d> vtx;

bool loadObj(char path[], Solid &s){
	ifstream in;
	in.open(path, ios::in);
	const int SZ = 1024; 
	char buf[SZ];
	char *index;

	
	int vtxCount = 0;

	while (in.getline(buf, SZ)){
		index = buf;
		Facet facet;
		int ic;
		char* tmp;

		if ((tmp = strstr(index, "v ")) != NULL){
			index = strstr(index, "v ");
			index += strlen("v ");
			double nx, ny, nz;
			sscanf(index, "%lf %lf %lf", &nx, &ny, &nz);
			vtx.push_back(Point3d(nx, ny, nz));
			//pp[vtxCount] = Point3d(nx, ny, nz);
			//vtxCount++;
		}

		if ((tmp = strstr(index, "f ")) != NULL){
			index = strstr(index, "f ");
			index += strlen("f ");
			int idx1, idx2, idx3;
			sscanf(index, "%d %d %d", &idx1, &idx2, &idx3);

			idx1 -= 1;
			idx2 -= 1;
			idx3 -= 1;

			//填充该面的顶点信息
			facet.point[0] = vtx.at(idx1);
			facet.point[1] = vtx.at(idx2);
			facet.point[2] = vtx.at(idx3);
			//facet.point[0] = pp[idx1];
			//facet.point[1] = pp[idx2];
			//facet.point[2] = pp[idx3];
			//计算该面的法向量，并填充法向量信息。
			Tuple3d v1 = vtx.at(idx1) - vtx.at(idx2);
			Tuple3d v2 = vtx.at(idx2) - vtx.at(idx3);
			//Tuple3d v1 = pp[idx1] - pp[idx2];
			//Tuple3d v2 = pp[idx2] - pp[idx3];
			Tuple3d normal = v1.cross(v2);
			facet.normal = normal.normalize();


			s.facets.push_back(facet);

		}
	}

	return true;
}
