#ifndef TROOPS_H
#define TROOPS_H

#include <iostream>
using namespace std;

class Troops
{
public:
	Troops(int melee, int armour, int health);
	void generateStats();
	int getMelee() const;
	void setMelee(int newMeleeStat);
	int getArmour() const;
	void setArmour(int newArmourStat);
	int getHealth() const;
	void setHealth(int healthChange);
	int getKills() const;
	void setKills(int killAmount);
private:
	int melee = 0;
	int armour = 0;
	int health = 0;
	int kills = 0;
};



#endif //ENEMY_H