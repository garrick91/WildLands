#include "Structure.h"


inline int ToScreenX(Coordinates _map)
{
	int screenX = (_map.x - _map.y) * 64;
	return screenX;
}

inline int ToScreenY(Coordinates _map)
{
	int screenY = (_map.x + _map.y) * 32;
	return screenY;
}
