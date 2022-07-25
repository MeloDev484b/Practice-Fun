#include "RovingTraders.h"
#include <iostream>
#include <string>

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
		std::cout << "Why are you wasting my time?\n";
		return 0;
	}
}
int RovingTraders::getDaysSinceLastPurchase()
{
	return daysSinceLastPurchase;
}
void RovingTraders::setDaysSinceLastPurchase(int newDays)
// 1 to increment, 0 to set daysSinceLastPurchase to 0
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