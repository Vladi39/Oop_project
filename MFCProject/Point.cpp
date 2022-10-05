#include<iostream>
#include"Point.h"
using namespace std;

Point::Point() :Figure2D()
{

}

Point::~Point()
{

}

Point::Point(const char* name, double x, double y) :Figure2D(0.0, 0.0, x, y)
{
	this->setName(name);
}

Point::Point(const Point & other) : Figure2D(0, 0, other.getX(), other.getY())
{

}

const Point &Point::operator=(Point & other)
{
	Figure2D::operator=(other);
	return *this;
}

void Point::Scale(double kx, double ky)
{
	this->MoveTo(this->getX() * kx, this->getY() * ky);

}

bool Point::isInside(Figure2D * P)
{
	if (this->getX() == P->getX() && this->getY() == P->getY())
	{
		return true;
	}
	else
	{
		return false;
	}

}

void Point::Resize(double newL, double newH)
{
	Figure2D::Resize(0.0, 0.0);
}


void Point::print()
{
	cout << this->getName() << ": (" << this->getX() << ", " << this->getY() << ")" << endl;
}
