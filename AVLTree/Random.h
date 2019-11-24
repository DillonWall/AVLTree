/*************************************************************
* Author: Dillon Wall
* Filename: Random.h
* Date Created: 1/19/2019
* Modifications:
*		- 1/22/2019 - Added no arg GetRand()
**************************************************************/

#pragma once

#include <random>
#include <ctime>


/************************************************************************
* Class: Random
*
* Purpose: This class is a helper class to signify a row in a 2D array
*
* Manager functions:
*
* Methods:
* static void Init()
*		Initializes the random seed. Ideally is called once at the start of the program
* static int GetRand(int high, int low = 0)
*		Returns a random number greater than or equal to 'low' and 
*		less than or equal to 'high'
*
*
*************************************************************************/
class Random
{
public:
	static void Init();
	static int GetRand();
	static int GetRand(int high, int low = 0);
};

