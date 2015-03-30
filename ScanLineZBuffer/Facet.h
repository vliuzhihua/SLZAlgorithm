#pragma once
#include"DataUtility.h"
#include "Transform.h"

class Facet{
public:
	Point3d point[3];
	Tuple3d normal;

	Facet doTransform(Transform t){
	
		Facet f;

		f.normal = normal;
		for(int i = 0; i < 3; i ++){
			f.point[i] = Point3d((point[i].m_data[0] + t.x) * t.scale,
								 (point[i].m_data[1] + t.y) * t.scale,
								 (point[i].m_data[2] + t.z) * t.scale);
		}
		
		return f;
		

	}
};