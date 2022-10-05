#pragma once
#include"Circle.h"
#define STARTING_GAME_SCORE 1
#define SCORE_PER_SUCCESS 0.5
class Gaming
{
public:
	//Fuc

	Gaming();
	virtual ~Gaming();
	void InsertIntoCircleArray(Circle &, bool = true);
	void RemoveFromCircleArray(int);
	void ResetGame();

	//variables

	Circle *CirclesArray[10] = {NULL};
	int nCircleCount = 0;
	double nRampUpNum = STARTING_GAME_SCORE;
	int nScore = 0;

};

