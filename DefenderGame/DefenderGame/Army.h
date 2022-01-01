#ifndef ARMY_H
#define ARMY_H

#include <iostream>
#include <string>
#include <array>
using namespace std;

const int DIRECTION_ARRAY_SIZE = 4;
const int ENEMY_MULTIPLIER = 40;

class Army
{
public:
	Army(int armySize, int archerAmount, string direction);
	int getArmySize() const;
	void setArmySize(int newArmySize);
	int getArcherAmount() const;
	void setArcherAmount(int newArcherAmount);
	string getDirection() const;
	void setDirection(string newDirection);
	void rollDirection();
	void rollArmySize();
	int getArmySizeLocation(int direction) const;
	void setArmySizeLocation(int troopsSent, int location);
	string returnArrayDirection(int direction) const;
private:
	int armySize = 0;
	int archerAmount = 0;
	string direction;
	const array <string, DIRECTION_ARRAY_SIZE> directions{ "North","East","South","West" };
	array <int, DIRECTION_ARRAY_SIZE> armySizeLocation{ 0,0,0,0 };//array[0] = North, array[1] = East, array[2] = South, array[3] = West
};



#endif //ARMY_H
