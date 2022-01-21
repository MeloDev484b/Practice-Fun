#include "RovingTraders.h"
#include <iostream>
#include <string>
using namespace std;

int RovingTraders::getScrapMetal() const
{
	return scrapMetal;
}
void RovingTraders::setScrapMetal(int metal)
{
	scrapMetal = metal;
}
int RovingTraders::getScrapWood() const
{
	return scrapWood;
}
void RovingTraders::setScrapWood(int wood)
{
	scrapWood = wood;
}
int RovingTraders::getStone() const
{
	return stone;
}
void RovingTraders::setStone(int newStone)
{
	stone = newStone;
}
int RovingTraders::getMysteriousWard() const
{
	return mysteriousWard;
}
void RovingTraders::setMysteriousWard(ScoreKeeper playerScore)
{
	if (playerScore.getScore() > 0)
	{
		mysteriousWard = 1;
	}
}
int RovingTraders::getGold() const
{
	return gold;
}
void RovingTraders::setGold(int newGold)
{
	gold = newGold;
}
int RovingTraders::buyCapturedEnemies(int enemiesSold)
{
	int capturedEnemeyPrice = rand() % 100 + 25;
	if (enemiesSold > 0)
	{
		return enemiesSold * capturedEnemeyPrice;
	}
	else
	{
		cout << "Why are you wasting my time?" << endl;
		return 0;
	}
}
void RovingTraders::generateWares()
{
	//make sure the trader doesn't run dry
	if (scrapMetal == 0 || scrapWood == 0 || stone == 0)
	{
		scrapMetal += (rand() % 50 + 10) * (daysSinceLastPurchase);
		scrapWood += (rand() % 50 + 1) * (daysSinceLastPurchase);
		stone += (rand() % 50 + 5) * (daysSinceLastPurchase);
	}
}
int RovingTraders::getDaysSinceLastPurchase()
{
	return daysSinceLastPurchase;
}
void RovingTraders::setDaysSinceLastPurchase(int newDays)
//1 to increment, 0 to set daysSinceLastPurchase to 0
{
	if (newDays == 1)
	{
		daysSinceLastPurchase++;
	}
	else
	{
		daysSinceLastPurchase = 0;
	}
}
int RovingTraders::getPrices(int arrayPosition) const
{
	return prices[arrayPosition];
}