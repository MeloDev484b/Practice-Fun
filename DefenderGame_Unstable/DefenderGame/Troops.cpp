#include <iostream>
#include "Troops.h"

using namespace std;

Troops::Troops(int melee, int armour)
{
	this->melee = melee;
	this->armour = armour;
}
void Troops::generateStats() //currently unused
{
	setMelee(rand() % 10 + 1);
	setArmour(rand() % 10 + 1);
	cout << melee << " " << armour << endl;
}
int Troops::getMelee() const
{
	return melee;
}
void Troops::setMelee(int newMeleeStat)
{
	melee = newMeleeStat;
}
int Troops::getArmour() const
{
	return armour;
}
void Troops::setArmour(int newArmourStat)
{
	armour = newArmourStat;
}
int Troops::getKills() const
{
	return kills;
}
void Troops::setKills(int killAmount)
{
	kills += killAmount;
}
float Troops::getDiplomacySkill() const
{
	return diplomacySkill;
}
void Troops::setDiplomacySkill(float skillProgress)
{
	diplomacySkill+= skillProgress;
}