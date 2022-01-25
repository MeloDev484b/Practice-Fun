#include "Resources.h"

int Resources::getGold()
{
	return gold;
}
void Resources::setGold(int addGold)
{
	gold += addGold;
}
//int Resources::getMetalScraps()
//{
//	return metalScraps;
//}
//void Resources::setMetalScraps(int newMetalScraps)
//{
//	metalScraps = newMetalScraps;
//}
//int Resources::getWoodScraps()
//{
//	return woodScraps;
//}
//void Resources::setWoodScraps(int newWoodScraps)
//{
//	woodScraps = newWoodScraps;
//}
//int Resources::getStone() const
//{
//	return stone;
//}
//void Resources::setStone(int newStone)
//{
//	stone = newStone;
//}
//int Resources::getMysteriousWard() const
//{
//	return mysteriousWard;
//}
//void Resources::setMysteriousWard(int numberWards)
//{
//	mysteriousWard += numberWards;
//}
int Resources::getCapturedEnemies() const
{
	return capturedEnemies;
}
void Resources::setCapturedEnemies(int numberToSell)
{
	capturedEnemies -= numberToSell;
}