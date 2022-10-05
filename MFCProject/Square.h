#pragma once
#include "Rectangle.h"
class Square :public MyRectangle
{
public:
	Square();
	~Square();
	Square(Square&);
	Square &operator=(Square&);
	Square(const char*, Point&, Point&);
	Square(const char*, Point&, double);
	void Resize(double newL, double newH);
	double Perimeter();
	double Area();
	virtual void print() override;
	Point SquareCenter();
	friend ostream & operator<<(ostream & o, Figure2D & d);
	double GetSide();
protected:
	double SquareSide;
};

