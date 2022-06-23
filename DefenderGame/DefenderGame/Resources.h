#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>

class Resources
{
public:
	int getGold();
	void setGold(int addGold);
	//future use
	/*
	int getMetalScraps();
	void setMetalScraps(int newMetalScraps);
	int getWoodScraps();
	void setWoodScraps(int newWoodScraps);
	int getStone() const;
	void setStone(int newStone);
	int getMysteriousWard() const;
	void setMysteriousWard(int numberWards);
	*/
	int getCapturedEnemies() const;
	void setCapturedEnemies(int numberToSell);
private:
	int gold = 500;
	int capturedEnemies = 0;
	//future use
	/*
	int metalScraps = 0;
	int woodScraps = 0;
	int stone = 0;
	int mysteriousWard = 0;
	*/
};



#endif //RESOURCES_H