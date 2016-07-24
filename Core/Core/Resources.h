#ifndef RESOURCES_H
#define RESOURCES_H

#include "Types.h"


struct Resource {
	int currentCount;
	ResourceType type;
	Resource() {};
	Resource(int _currentCount,  ResourceType _type) : currentCount(_currentCount), type(_type) {}
	~Resource() {};
};

#endif // !RESOURCES_H