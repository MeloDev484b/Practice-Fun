#ifndef TROOPS_H
#define TROOPS_H

#include <iostream>
using namespace std;

class Troops
{
public:
	Troops(int melee, int armour);
	void generateStats();
	int getMelee() const;
	void setMelee(int newMeleeStat);
	int getArmour() const;
	void setArmour(int newArmourStat);
	int getKills() const;
	void setKills(int killAmount);
	float getDiplomacySkill() const;
	void setDiplomacySkill(float skillProgress);
private:
	int melee = 1;
	int armour = 1;
	int kills = 0;
	float diplomacySkill = 0;
};



#endif //ENEMY_H