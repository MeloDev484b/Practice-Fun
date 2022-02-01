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
		//set difficulty level to match the chosen difficulty level
		void alignDifficultyLevel(int difficultyLevel);
	private:
		int armySize = 0;
		int difficultyModifier = 0;
};



#endif // !ENEMY_ARMY_H
