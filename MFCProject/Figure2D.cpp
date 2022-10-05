#include "Figure2D.h"
#include "Functions.h"
#include<iostream>

using namespace std;

IMPLEMENT_SERIAL(Figure2D, CObject, 1);

Figure2D::Figure2D(double l, double h, double x, double y)
{
	this->x = x;
	this->y = y;
	this->length = l;
	this->height = h;
}

Figure2D::Figure2D(Figure2D & f)
{
}

Figure2D::Figure2D()
{
}

Figure2D::~Figure2D()
{
	delete[] this->name;
}

const Figure2D & Figure2D::operator=(Figure2D & d)
{
	this->x = d.getX();
	this->y = d.getY();
	this->name = copystring(d.getName());
	return *this;
}

void Figure2D::setName(const char *newname)
{
	char *temp;
	temp = copystring(newname);
	this->name = temp;
}

double Figure2D::getX()const
{
	return this->x;
}

double Figure2D::getY()const
{
	return this->y;
}

double Figure2D::getLength()
{
	return this->length;
}

double Figure2D::getHeight()
{
	return this->height;
}

const char * Figure2D::getName()
{
	return this->name;
}

double Figure2D::Area()
{
	return 0.0;
}

double Figure2D::Perimeter()
{
	return 0.0;
}

void Figure2D::Shift(double dx, double dy)
{
	this->x += dx;
	this->y += dy;
}

void Figure2D::MoveTo(double newX, double newY)
{
	this->x = newX;
	this->y = newY;
}

void Figure2D::Resize(double newL, double newH)
{
	this->length = newL;
	this->height = newH;
}

void Figure2D::Scale(double kx, double ky)
{
}

bool Figure2D::isInside(Figure2D * P)
{
	return false;
}

void Figure2D::print()
{
}

void Figure2D::OnDraw(CPaintDC &)
{
	return;
}

void Figure2D::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << x << y << length << height << red << green << blue;

	}
	else
	{
		ar >> x >> y >> length >> height >> red >> green >> blue;
	}
}

void Figure2D::SetRed(int red)
{
	this->red = red;
}

void Figure2D::SetGreen(int green)
{
	this->green = green;
}

void Figure2D::SetBlue(int blue)
{
	this->blue = blue;
}

int Figure2D::GetRed()
{
	return this->red;
}

int Figure2D::GetGreen()
{
	return this->green;
}

int Figure2D::GetBlue()
{
	return this->blue;
}

int Figure2D::GetColorNumber()
{
	
	return rand() % 255;
}

