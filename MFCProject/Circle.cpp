#include "Circle.h"
#include <string>

Circle::Circle()
{
}

Circle::~Circle()
{
}

Circle::Circle(const char *name, Point &p1, double radius) :Square("Square", p1, 2 * radius)
{
	this->CircleCenter.MoveTo(p1.getX() + radius, p1.getY() + radius);
	this->setName(name);
	this->Radius = radius;
}

Circle::Circle(Circle &c)
{
	c.CircleCenter.setName("");
	this->MoveTo(c.getX(), c.getY());
	this->Resize(c.getHeight(), c.getLength());
	this->CircleCenter = c.CircleCenter;
	this->red = c.red;
	this->green = c.green;
	this->blue = c.blue;
	this->nExpireTime = c.nExpireTime;
}

void Circle::operator=(Circle &c)
{
	c.CircleCenter.setName("");
	this->MoveTo(c.getX(), c.getY());
	this->Resize(c.getHeight(), c.getLength());
	this->CircleCenter = c.CircleCenter;
	this->red = c.red;
	this->green = c.green;
	this->blue = c.blue;
	this->nExpireTime = c.nExpireTime;
}

bool Circle::isInside(Figure2D * P)
{
	double x = (this->CircleCenter.getX() - P->getX());
	double y = (this->CircleCenter.getY() - P->getY());
	double dist = sqrt(x*x + y * y);
	if (dist > this->Radius)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Circle::Resize(double newL, double newH)
{
	Square::Resize(newL, newH);
	this->Radius = 0.5*SquareSide;
	this->CircleCenter.MoveTo(this->getX() + this->Radius, this->getY() + this->Radius);
}

double Circle::Perimeter()
{
	return 2 * this->Radius*Pi;
}

double Circle::Area()
{
	return Pi * (this->Radius*this->Radius);
}

void Circle::print()
{

	Point Center = this->SquareCenter();

	cout << "Circle " << this->getName() << " with center (" << Center.getX() << ", " << Center.getY() << ") and radius = " << this->Radius << endl;
}

void Circle::OnDraw(CPaintDC & dc)
{
	wstring sSecTimer = to_wstring(this->nExpireTime * 50);
	POINT p1, p2;
	p1.x = this->CircleCenter.getX() - 20;
	p1.y = this->CircleCenter.getY() - 10;
	p2.x = this->CircleCenter.getX() + 20;
	p2.y = this->CircleCenter.getY() + 10;
	int red = this->GetRed();
	int green = this->GetGreen();
	int blue = this->GetBlue();
	CBrush MyBrush(RGB(red,green,blue));
	dc.SelectObject(MyBrush);
	dc.Ellipse(this->getX(), this->getY() + (2 * this->Radius), this->getX() + (2 * this->Radius), this->getY());
	if (this->bIsShowingTimer)
	{
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 255, 255));
		dc.DrawText(sSecTimer.c_str(), CRect(p1, p2), DT_PATH_ELLIPSIS | DT_CENTER);
	}

}

void Circle::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << this->getX() << this->getY() << this->getLength() << this->getHeight() <<this->Radius <<this->GetRed() << this->GetGreen() << this->GetBlue() << this->nExpireTime;

	}
	else
	{
		double x, y, length, height, radius;
		int red, green, blue, expiretime;
		ar >> x >> y >> length >> height >>radius >>red >> green >> blue >> expiretime;
		this->MoveTo(x, y);
		this->Resize(length, height);
		this->Radius = radius;
		this->SetRed(red);
		this->SetGreen(green);
		this->SetBlue(blue);
		this->nExpireTime = expiretime;
	}
}


IMPLEMENT_SERIAL(Circle, CObject, 1);