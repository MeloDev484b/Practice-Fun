#include "Resources.h"

int Resources::getGold()
{
	return gold;
}
void Resources::setGold(int addGold)
{
	gold += addGold;
}
int Resources::getCapturedEnemies() const
{
	return capturedEnemies;
}
void Resources::setCapturedEnemies(int numberToSell)
{
	capturedEnemies -= numberToSell;
}