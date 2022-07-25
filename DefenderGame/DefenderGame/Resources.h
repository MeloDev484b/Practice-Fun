#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>

class Resources
{
public:
	int getGold();
	void setGold(int addGold);
	int getCapturedEnemies() const;
	void setCapturedEnemies(int numberToSell);
private:
	int gold = 500;
	int capturedEnemies = 0;
};



#endif //RESOURCES_H