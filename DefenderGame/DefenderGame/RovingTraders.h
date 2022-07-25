#ifndef ROVING_TRADERS_H
#define ROVING_TRADERS_H
#include "ScoreKeeper.h"
#include "Resources.h"

class RovingTraders
{
public:
	int getGold() const;
	void setGold(int newGold);
	int buyCapturedEnemies(int enemiesSold);
	int getDaysSinceLastPurchase();
	void setDaysSinceLastPurchase(int newDays);
	int getPrices(int arrayPosition) const;
private:
	//wares
	int daysSinceLastPurchase = 0;
	int gold = 5000;
	int prices[4]{ 20, 15, 100, 200 };
};


#endif // !ROVING_TRADER_H
