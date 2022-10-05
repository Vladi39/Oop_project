#pragma once
#include"Segment.h"

class MyRectangle :public Segment
{
public:
	MyRectangle();
	~MyRectangle();
	MyRectangle(const char*, Point&, Point&);
	MyRectangle(MyRectangle&);
	double Area();
	double Perimeter();
	void Scale(double kx, double ky) override;
	void Resize(double newL, double newH);
	void OnDraw(CPaintDC &);
	void Serialize(CArchive & ar);
	DECLARE_SERIAL(MyRectangle);
};

