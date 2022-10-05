#include "Gaming.h"

Gaming::Gaming()
{
}

Gaming::~Gaming()
{
}

void Gaming::InsertIntoCircleArray(Circle & circle, bool IsDeletingIfFull)
{

	if (this->CirclesArray[nCircleCount])
	{
		if (IsDeletingIfFull)
		{
			delete this->CirclesArray[nCircleCount];
			this->CirclesArray[nCircleCount] = NULL;
		}
		else
		{
			return;
		}
		
	}
	this->CirclesArray[nCircleCount] = new Circle(circle);
	nCircleCount++;
	if (nCircleCount == 10)
	{
		nCircleCount = 0;
	}
}

void Gaming::RemoveFromCircleArray(int i)
{
	delete this->CirclesArray[i];
	this->CirclesArray[i] = NULL;
	this->nCircleCount--;
}

void Gaming::ResetGame()
{
	this->nRampUpNum = STARTING_GAME_SCORE;
	this->nScore = 0;
	for (int i = 0; i < 10; i++)
	{
		if (this->CirclesArray[i])
		{
			this->RemoveFromCircleArray(i);
		}
	}
}
