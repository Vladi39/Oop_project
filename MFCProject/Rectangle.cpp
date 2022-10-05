#include "Rectangle.h"


MyRectangle::MyRectangle() :Segment()
{}

MyRectangle::~MyRectangle()
{}

MyRectangle::MyRectangle(const char *name, Point &p1, Point &p2) :Segment(name, p1, p2)
{
	double MinX, MinY, MaxX, MaxY;
	MinX = p1.getX() <= p2.getX() ? p1.getX() : p2.getX();
	MinY = p1.getY() <= p2.getY() ? p1.getY() : p2.getY();
	MaxX = p1.getX() > p2.getX() ? p1.getX() : p2.getX();
	MaxY = p1.getY() > p2.getY() ? p1.getY() : p2.getY();
	Point Min("Min", MinX, MinY);
	Point Max("Max", MaxX, MaxY);
	this->pStart = Min;
	this->pEnd = Max;
	const double tempLength = lengthofsegement(this->pStart, this->pEnd);
	const double tempHeight = heightofsegement(this->pStart, this->pEnd);
	Figure2D::Resize(tempLength, tempHeight);
	Figure2D::MoveTo(this->pStart.getX(), this->pStart.getY());
	this->setName(name);
}


MyRectangle::MyRectangle(MyRectangle & rec)
{
	rec.pStart.setName("");
	rec.pEnd.setName("");
	this->MoveTo(rec.getX(), rec.getY());
	this->Resize(rec.getLength(), rec.getHeight());
	this->pStart = rec.pStart;
	this->pEnd = rec.pEnd;
	this->red = rec.red;
	this->green = rec.green;
	this->blue = rec.blue;

}

double MyRectangle::Area()
{
	return this->getLength()*this->getHeight();
}

double MyRectangle::Perimeter()
{
	return (this->getHeight() + this->getLength()) * 2;
}


void MyRectangle::Scale(double kx, double ky)
{
	this->Resize(this->getLength()*kx, this->getHeight()*ky);

}

void MyRectangle::Resize(double newL, double newH)
{
	this->pEnd.MoveTo((newL + this->pStart.getX()), newH + this->pStart.getY());
	Figure2D::Resize(newL, newH);
}

void MyRectangle::OnDraw(CPaintDC & dc)
{
	int red = this->GetRed();
	int green = this->GetGreen();
	int blue = this->GetBlue();
	CBrush MyBrush(RGB(red, green, blue));
	dc.SelectObject(MyBrush);
	dc.Rectangle(this->getX(), this->getY() + this->getHeight(), this->getX() + this->getLength(), this->getY());
}

void MyRectangle::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar <<this->getX()<<this->getY() <<this->pStart.getX() << this->pStart.getY() <<this->pEnd.getX()<<this->pEnd.getY() <<this->getLength() << this->getHeight()  << this->GetRed() << this->GetGreen() << this->GetBlue();

	}
	else
	{
		double x1, y1,x2,y2, length, height, figure2dx,figure2dy;
		int red, green, blue;
		ar>> figure2dx >> figure2dy >>x1 >> y1 >> x2 >> y2 >> length >> height >> red >> green >> blue;
		Point pTempStart("", x1, y1);
		Point pTempEnd("", x2, y2);
		this->pStart = pTempStart;
		this->pEnd = pTempEnd;
		Figure2D::MoveTo(figure2dx, figure2dy);
		Figure2D::Resize(length, height);
		this->SetRed(red);
		this->SetGreen(green);
		this->SetBlue(blue);
	}
}

IMPLEMENT_SERIAL(MyRectangle, CObject, 1);
