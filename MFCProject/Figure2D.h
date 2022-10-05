#pragma once
#include <math.h>
#include<iostream>
#include "Functions.h"
#include"pch.h"
const double Pi = 3.1415926535897931;
using namespace std;
class Figure2D :public CObject
{

private:

	double x;
	double y;
	double length;
	double height;
	char *name = NULL;//=NULL Needed for compiler of the testing engine

public:
	DECLARE_SERIAL(Figure2D);
	int red;
	int green;
	int blue;
	Figure2D(double l, double h, double x = 0, double y = 0);
	Figure2D(Figure2D &f);
	Figure2D();
	virtual ~Figure2D();
	const Figure2D &operator=(Figure2D &d);
	void setName(const char *);
	double getX()const;
	double getY()const;
	double getLength();
	double getHeight();
	const char *getName();
	virtual double Area();
	virtual double Perimeter();
	virtual void Shift(double dx, double dy);
	void MoveTo(double newX, double newY);
	virtual void Resize(double newL, double newH);
	virtual void Scale(double kx, double ky);
	virtual bool isInside(Figure2D *P);//Point(P->getX(),P->getY()) lies inside the figure
	virtual void print();
	friend std::ostream &operator<<(ostream &o, Figure2D &d);
	virtual void OnDraw(CPaintDC &);
	void Serialize(CArchive& ar);
	void SetRed(int);
	void SetGreen(int);
	void SetBlue(int);
	int GetRed();
	int GetGreen();
	int GetBlue();
	static int GetColorNumber();
	
};
