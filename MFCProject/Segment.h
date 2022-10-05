#pragma once
#include"Figure2D.h"
#include"Point.h"
#include <math.h>
class Segment :public Figure2D
{

public:

	Segment();
	~Segment();
	Segment(const char *, Point&, Point&);
	void Scale(double kx, double ky);
	bool isInside(Figure2D *P);//Point(P->getX(),P->getY()) lies inside the figure
	void Resize(double newL, double newH);
	virtual double lengthofsegement(Point &, Point &);
	virtual double heightofsegement(Point &, Point &);
	void Shift(double dx, double dy);
	double Perimeter();
	void print();

protected:

	Point pStart;
	Point pEnd;

};

