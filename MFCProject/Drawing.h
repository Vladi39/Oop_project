#pragma once
#include "Figure2D.h"
#include "Circle.h"
class Drawing
{

public:

	//Fuc
	Drawing();
	virtual ~Drawing();

	template <class T>
	void InsertIntoFigureArray(T&);
	

	//Variables
	Figure2D *FiguresArray[10] = { NULL };
	int nFiguersCount = 0;
};


template<class T>
void Drawing::InsertIntoFigureArray(T &figure) 
{
	T &item = figure;
	if (this->FiguresArray[nFiguersCount])//checks if array is full
	{
		delete this->FiguresArray[nFiguersCount];
		this->FiguresArray[nFiguersCount] = NULL;
	}
	this->FiguresArray[nFiguersCount] = new T(figure);
	nFiguersCount++;
	if (nFiguersCount == 10)
	{
		nFiguersCount = 0;
	}
}
