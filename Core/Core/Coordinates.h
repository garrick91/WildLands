#ifndef COORDINATES_H
#define COORDINATES_H


struct Coordinates
{
	float x;
	float y;
	Coordinates() {}
	Coordinates(float x_, float y_) :x(x_), y(y_) {}
};

#endif // !COORDINATES_H