#include <iostream>
#include "Troops.h"

using namespace std;

Troops::Troops(int melee, int armour, int health)
{
	this->melee = melee;
	this->armour = armour;
	this->health = health;
}
void Troops::generateStats()
{
	setMelee(rand() % 10 + 1);
	setArmour(rand() % 10 + 1);
	setHealth(rand() % 20 + 10);
	cout << melee << " " << armour << " " << health << endl;
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
int Troops::getHealth() const
{
	return health;
}
void Troops::setHealth(int newHealth)
{
	health = newHealth;
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