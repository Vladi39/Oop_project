#pragma once
#include"Figure2D.h"

class Point :public Figure2D
{
public:

	Point();
	~Point();
	Point(const char*, double x, double y);
	Point(const Point & other);
	const Point & operator=(Point & other);
	void Scale(double kx, double ky);
	bool isInside(Figure2D * P);
	void Resize(double newL, double newH);
	void print();
};