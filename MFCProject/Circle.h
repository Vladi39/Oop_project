#pragma once
#include "Square.h"
class Circle :public Square
{
public:
	Circle();
	~Circle();
	Circle(const char*, Point&, double);
	Circle(Circle &);


	// Inherited via Figure2D
	bool isInside(Figure2D * P) override;
	void Resize(double newL, double newH);
	double Perimeter();
	double Area();
	void print() override;
	void OnDraw(CPaintDC &);
	void Serialize(CArchive& ar);
	void operator=(Circle&);
	DECLARE_SERIAL(Circle);
	int nExpireTime = 4;
	bool bIsShowingTimer = false;

protected:

	Point CircleCenter;
	double Radius;

};

