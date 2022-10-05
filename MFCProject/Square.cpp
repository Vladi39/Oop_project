#include "Square.h"

Square::Square()
{
}

Square::~Square()
{
}

Square::Square(Square & s1)
{
	this->SquareSide = s1.SquareSide;
	Figure2D::Resize(s1.getLength(), s1.getHeight());
	this->pStart = s1.pStart;
	this->pEnd = s1.pEnd;
	Figure2D::MoveTo(this->pStart.getX(), this->pStart.getY());
	this->setName(s1.getName());

}

Square & Square::operator=(Square & s1)
{
	this->SquareSide = s1.SquareSide;
	Figure2D::Resize(s1.getLength(), s1.getHeight());
	this->pStart = s1.pStart;
	this->pEnd = s1.pEnd;
	this->setName(s1.getName());
	Figure2D::MoveTo(this->pStart.getX(), this->pStart.getY());
	return *this;
}

Square::Square(const char *name, Point &p1, double side)
{
	this->pStart = p1;
	Point newEnd("End", p1.getX() + side, p1.getY() + side);
	this->pEnd = newEnd;
	this->setName(name);
	this->SquareSide = side;
	Figure2D::Resize(side, side);
	Figure2D::MoveTo(this->pStart.getX(), this->pStart.getY());
}
Square::Square(const char *name, Point &p1, Point &p2) :MyRectangle(name, p1, p2)
{
	SquareSide = this->getLength() < this->getHeight() ? this->getLength() : this->getHeight();
	this->pStart.MoveTo(
		0.5*(this->getLength() - SquareSide),
		0.5*(this->getHeight() - SquareSide)
	);
	this->pEnd.MoveTo(
		0.5*(this->getLength() + SquareSide),
		0.5*(this->getHeight() + SquareSide)
	);
}

void Square::Resize(double newL, double newH)
{
	Figure2D::Resize(newL, newH);
	SquareSide = this->getLength() < this->getHeight() ? this->getLength() : this->getHeight();
	this->pStart.MoveTo(
		0.5*(this->getLength() - SquareSide),
		0.5*(this->getHeight() - SquareSide)
	);
	this->pEnd.MoveTo(
		0.5*(this->getLength() + SquareSide),
		0.5*(this->getHeight() + SquareSide)
	);
}

double Square::Perimeter()
{
	return this->SquareSide * 4;
}

double Square::Area()
{
	return this->SquareSide*this->SquareSide;
}

void Square::print()
{
	Point Center = this->SquareCenter();

	cout << "Square " << this->getName() << " with center (" << Center.getX() << ", " << Center.getY() << ") and side = " << this->SquareSide << endl;
}

Point Square::SquareCenter()
{
	Point Center("Center", (0.5*this->getLength()) + this->getX(), (0.5*this->getHeight()) + this->getY());
	return Center;
}

double Square::GetSide()
{
	return SquareSide;
}

ostream & operator<<(ostream & o, Square & d)
{
	Point Center = d.SquareCenter();

	o << "Square " << d.getName() << " with center (" << Center.getX() << ", " << Center.getY() << ") and side = " << d.GetSide() << endl;
	return o;

}