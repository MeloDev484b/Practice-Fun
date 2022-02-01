#include <iostream>
#include "Army.h"

using namespace std;
Army::Army(int armySize, int archerAmount)
{
	this->armySize = armySize;
	this->archerAmount = archerAmount;
}
Army::Army(int armySize)
{
	this->armySize = armySize;
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
int Army::getSoldiersAtLocation(int arrayPosition) const
{
	return soldiersAtLocation[arrayPosition];
}
void Army::setSoldiersAtLocation(int soldiers, int arrayPosition)
{
	soldiersAtLocation[arrayPosition] = soldiers;
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
int Army::rollAd12()
{
	return rand() % 12 + 1;
}