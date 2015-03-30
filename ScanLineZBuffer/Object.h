#include "Solid.h"
#include "Transform.h"


class Object{
public:
	Solid *solid;
	Transform *transform;

	Object *next;
};