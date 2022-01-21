#ifndef ROVING_TRADERS_H
#define ROVING_TRADERS_H
#include "ScoreKeeper.h"
#include "Resources.h"

class RovingTraders
{
public:
	int getScrapMetal() const;
	void setScrapMetal(int metal);
	int getScrapWood() const;
	void setScrapWood(int wood);
	int getStone() const;
	void setStone(int newStone);
	int getMysteriousWard() const;
	void setMysteriousWard(ScoreKeeper playerScore);
	int getGold() const;
	void setGold(int newGold);
	int buyCapturedEnemies(int enemiesSold);
	void generateWares();
	int getDaysSinceLastPurchase();
	void setDaysSinceLastPurchase(int newDays);
	int getPrices(int arrayPosition) const;
private:
	//wares
	int daysSinceLastPurchase;
	int scrapMetal = 200;
	int scrapWood = 200;
	int stone = 200;
	int mysteriousWard = 0;
	int gold = 1000;
	int prices[4]{ 20, 15, 100, 200 };
};


#endif // !ROVING_TRADER_H
