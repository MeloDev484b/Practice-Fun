#include <iostream>
#include "Army.h"

using namespace std;

Army::Army(int armySize, int archerAmount, string direction)
{
	this->armySize = armySize;
	this->archerAmount = archerAmount;
	this->direction = direction;
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
string Army::getDirection() const
{
	return direction;
}
void Army::setDirection(string newDirection)
{
	direction = newDirection;
}
void Army::rollArmySize()
{
	setArmySize(rand() % ENEMY_MULTIPLIER); //select number of enemies between 20 & 40
	if (armySize < 20)
	{
		armySize = 20;
	}
}
void Army::rollDirection()
{
	setDirection(directions[rand() % 4]);
}
int Army::getArmySizeLocation(int location) const
{
	return armySizeLocation[location];
}
void Army::setArmySizeLocation(int troopsSent, int location)
{
	armySizeLocation[location] = troopsSent;
}
string Army::returnArrayDirection(int direction) const
{
	return directions[direction];
}