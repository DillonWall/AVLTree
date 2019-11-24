/*************************************************************
* Author: Dillon Wall
* Filename: Random.cpp
* Date Created: 1/19/2019
* Modifications:
**************************************************************/


#include "Random.h"



void Random::Init()
{
	srand(time(0));
}

int Random::GetRand()
{
	return rand();
}

int Random::GetRand(int high, int low)
{
	return (rand() % (high+1-low) + low);
}
