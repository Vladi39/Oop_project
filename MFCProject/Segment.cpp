#include "Segment.h"

Segment::Segment() :Figure2D()
{

}

Segment::~Segment()
{
}

Segment::Segment(const char *name, Point &p1, Point &p2)
{

	this->pStart = p1.getX() <= p2.getX() ? p1 : p2;
	this->pEnd = p1.getX() > p2.getX() ? p1 : p2;
	const double tempLength = lengthofsegement(p1, p2);
	const double tempHeight = heightofsegement(p1, p2);
	Figure2D::Resize(tempLength, tempHeight);
	Figure2D::MoveTo(this->pStart.getX(), this->pEnd.getY());
	this->setName(name);

}

void Segment::Scale(double kx, double ky)
{
	this->Resize(this->getLength()*kx, this->getHeight()*ky);

}

bool Segment::isInside(Figure2D * P)
{
	if (P->getX() > min(this->pStart.getX(), this->pEnd.getX()) && P->getX() < max(this->pStart.getX(), this->pEnd.getX()))
	{
		if (P->getY() > min(this->pStart.getY(), this->pEnd.getY()) && P->getY() < max(this->pStart.getY(), this->pEnd.getY()))
		{
			return true;
		}
	}
	return false;
}


void Segment::Resize(double newL, double newH)
{
	Point lowY, lowX;
	lowY = pStart.getY() <= pEnd.getY() ? pStart : pEnd;
	lowX = pStart.getX() <= pEnd.getX() ? pStart : pEnd;
	this->pStart.MoveTo(this->pStart.getX(), newH + lowY.getY());
	this->pEnd.MoveTo((newL + lowX.getX()), this->pEnd.getY());
	Figure2D::Resize(newL, newH);
}

double Segment::lengthofsegement(Point & start, Point & end)
{
	double temp;
	temp = end.getX() - start.getX();
	return abs(temp);
}

double Segment::heightofsegement(Point & start, Point & end)
{
	double temp;
	temp = end.getY() - start.getY();
	return abs(temp);
}

void Segment::Shift(double dx, double dy)
{
	this->pStart.Shift(dx, dy);
	this->pEnd.Shift(dx, dy);
	Figure2D::Shift(dx, dy);
}

double Segment::Perimeter()
{
	return sqrt(this->getLength()*this->getLength() + this->getHeight()*this->getHeight());
}

void Segment::print()
{
	cout << this->getName() << ": Point(" << this->pStart.getX() << ", " << this->pStart.getY() << ")"
		<< "-" << "Point(" << this->pEnd.getX() << ", " << this->pEnd.getY() << ")" << endl;
}
