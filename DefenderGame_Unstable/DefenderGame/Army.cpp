#include <iostream>
#include "Army.h"

using namespace std;
int rollAd12();

Army::Army(int armySize, int archerAmount)
{
	this->armySize = armySize;
	this->archerAmount = archerAmount;
}
int Army::getArmySize() const
{
	return armySize;
}
void Army::setArmySize(int newArmyAmount)
{
	armySize = newArmyAmount;
}
int Army::getArcherAmount() const
{
	return archerAmount;
}
void Army::setArcherAmount(int newArcherAmount)
{
	archerAmount = newArcherAmount;
}
void Army::rollArmySize() //Enemy function
{
	//set total size of army - modify based on difficulty
	armySize = rand() % 40 + 20;
}
void Army::rollDirection() //Enemy Function - pick the locations where the army is divided into [0] - [3]
{
	int tempArmySize = armySize;
	for (int i = 0; i < soldiersAtLocation.size(); i++)
	{
		if (rollAd12() > 6 && tempArmySize > 0)
		{
			int amountOfSoliers = rand() % tempArmySize + 1;
			setSoldiersAtLocation(amountOfSoliers, i);
			tempArmySize -= amountOfSoliers;
		}
	}
	
}
int Army::getSoldiersAtLocation(int arrayPosition) const
{
	return soldiersAtLocation[arrayPosition];
}
void Army::setSoldiersAtLocation(int soldiers, int arrayPosition)
{
	soldiersAtLocation[arrayPosition] = soldiers;
}
void Army::setDifficultyModifier(int newDifficulty)
{
	difficultyModifier = newDifficulty;
}
string Army::getDirection(int arrayPosition)
{
	if (arrayPosition == 0)
	{
		//North
		return directions[0];
	}
	else if(arrayPosition == 1)
	{
		//East
		return directions[1];
	}
	else if (arrayPosition == 2)
	{
		//South
		return directions[2];
	}
	else if (arrayPosition == 3)
	{
		//West
		return directions[3];
	}
	else
	{
		return "Position not found.\n";
	}
}
void Army::resetArmy() //EnemyFunction
{
	for (int i = 0; i < soldiersAtLocation.size(); i++)
	{
		setSoldiersAtLocation(0, i);
	}
}
void Army::whereAreTheEnemies() //Enemy function
{
	for (int i = 0; i < soldiersAtLocation.size(); i++)
	{
		if (getSoldiersAtLocation(i) > 0)
		{
			int enemies = getSoldiersAtLocation(i);
			string direction = getDirection(i);
			cout <<"\n"<< enemies << " enemy soldiers approach from the " << direction << "!\n\n";
		}
	}
}
int rollAd12()
{
	return rand() % 12 + 1;
}