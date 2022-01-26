#ifndef ENEMY_ARMY_H
#define ENEMY_ARMY_H

#include "Army.h"

class EnemyArmy : public Army 
{
	public:
		EnemyArmy(int armySize) : Army(armySize){};
		void rollArmySize();
		void rollDirection();
		void resetArmy();
		void whereAreTheEnemies();
	private:
		int armySize = 0;
};



#endif // !ENEMY_ARMY_H
