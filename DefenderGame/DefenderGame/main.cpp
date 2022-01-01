#include<iostream>
#include <string>
#include <array>
#include <limits>

#include "Resources.h"
#include "Army.h"
#include "Shop.h"
#include "Troops.h"
using namespace std;

bool kingAlive = true;

void attackDirection();
void preparation();
void combat();
void store();
void isTheKingAlive();
int getInput(char phase);

Army army(50, 0, "South");
Troops troops(10, 10, 10);
Army enemyArmy(20, 0, "South");
Resources resources;

int main()
{
	srand(time(0));
	cout << "Defend your castle!" << endl;
	while (kingAlive == true)
	{
		attackDirection();
		preparation();
	}

	cout << "Thank you for playing." << endl;
	return 0;
}
void attackDirection() //where are the enemies coming from, and how many?
{
	enemyArmy.rollArmySize();
	enemyArmy.rollDirection();
	cout << enemyArmy.getArmySize() << " enemies approach from the " << enemyArmy.getDirection() << "!" << endl;
}
void preparation()
{
	string enemyLocation = enemyArmy.getDirection();
	int tempArmySize = army.getArmySize();
	//determine where troops go before the attack
	for (int i = 0; i < DIRECTION_ARRAY_SIZE; i++)
	{
		if (army.getArmySize() > 0)
		{
			int stationInput;
			cout << "You have " << tempArmySize << " troops at your disposal." << endl;
			cout << "How any troops will you send to the " << army.returnArrayDirection(i) << "?" << endl;
			stationInput = getInput('p');
			cin >> stationInput;
			if (stationInput <= tempArmySize)
			{
				army.setArmySizeLocation(stationInput, i);
				tempArmySize -= stationInput;
			}
		}
	}
	combat();
}
void combat()
{
	int tempArmySize = army.getArmySize();
	int enemyDeaths = 0;
	//determine results of attack
	for (int i = 0; i < DIRECTION_ARRAY_SIZE; i++) //loop through each direction
	{
		if (enemyArmy.getDirection() == army.returnArrayDirection(i) && (enemyArmy.getArmySize() - army.getArcherAmount()) > (army.getArmySizeLocation(i) * (troops.getMelee() / 10)))
		{
			army.setArmySize(tempArmySize - (army.getArmySizeLocation(i)) * (troops.getArmour() / 10));
			enemyDeaths = (army.getArmySizeLocation(i) * (troops.getMelee() / 10));
			troops.setKills(enemyDeaths);
			cout << "After taking down " << enemyDeaths << " enemies, you suffer a loss in the " << army.returnArrayDirection(i) << "." << endl;
			cout << troops.getKills() << " enemies have fallen to your troops." << endl;

		}
		else if (enemyArmy.getDirection() == army.returnArrayDirection(i)) //only display victory message & reward with gold if fought enemy
		{
			int drops = rand() % 100 + 1;
			enemyDeaths = (army.getArmySizeLocation(i) * (troops.getMelee() / 10));
			cout << "You triumphed over " <<enemyDeaths<<" enemies in the " << army.returnArrayDirection(i) << "!" << endl;
			troops.setKills(enemyDeaths);
			cout << troops.getKills() << " enemies have fallen to your troops." << endl;
			cout << "You loot supplies worth " << drops << " gold from the battlefield." << endl;
			int currentGold = resources.getGold();
			resources.setGold(currentGold+drops);
		}
	}
	isTheKingAlive();
	store();
}
void store()
{
	int currentGold = resources.getGold();
	int currentMelee = troops.getMelee();
	int currentArmour = troops.getArmour();
	int currentArmySize = army.getArmySize();
	int currentArchers = army.getArcherAmount();
	if (kingAlive == true)
	{
		int userChoice = 0;
		cout << "As the fighting dies down, you strategize how to use your resources to improve your chances at the next wave." << endl;
		cout << "You have " << resources.getGold() << " gold." << endl;
		cout << "The shop contains the following: " << endl;
		cout << "Weapons - 300g(1), Armour - 300g(2), Reenforcements - 200g(3), Archers - 400g(4)" << endl;
		cout << "Type 1, 2, 3, or 4 to make your selection." << endl;
		userChoice = getInput('s');
		if (userChoice == 1 && resources.getGold() > 300)
		{
			cout << "You improve your army's weapons." << endl;
			troops.setMelee(currentMelee * 1.1);
			resources.setGold(currentGold - 300);
			cout << troops.getMelee() << endl;//test
		}
		else if (userChoice == 2 && resources.getGold() > 300)
		{
			cout << "You improve your army's armour." << endl;
			troops.setArmour(currentArmour * 1.1);
			resources.setGold(currentGold - 300);
			cout << troops.getArmour() << endl;//test
		}
		else if (userChoice == 3 && resources.getGold() > 200)
		{
			cout << "You hire more footsoldiers." << endl;
			army.setArmySize(currentArmySize + 10); //NOTE:make this scale
			resources.setGold(currentGold-200);
			cout << army.getArmySize() << endl;//test
		}
		else if (userChoice == 4 && resources.getGold() > 400)
		{
			cout << "You hire a party of archers to support your footsoldiers." << endl;
			army.setArcherAmount(currentArchers + 4); ///NOTE:make this scale
			resources.setGold(currentGold - 400);
			cout << army.getArcherAmount() << endl;//test
		}
		else
		{
			cout << "Do you take me for a fool? My shop is closed to old saps like you!" << endl;
		}
	}
}
void isTheKingAlive()
{
	int currentArmySize = army.getArmySize();
	if (currentArmySize < 1)
	{
		cout << "The king has fallen; you are at the enemy's mercy." << endl;
		cout << troops.getKills() << " enemy soldiers fell to your troops." << endl;
		kingAlive = false;
	}
}
int getInput(char phase) //function to ignore non-numeric & non-integer entries --needs work
{
	char currentPhase = phase;
	int userInput;
	cin >> userInput;
	if (cin>>userInput)
	{
		userInput = round(userInput);
		if (userInput >= 0)
		{
			return userInput;
		}
	}
	else
	{
		
		if (phase == 'p')
		{
			cout << "We need you to focus! How many troops will you send?" << endl;
		}
		else if (phase == 's')
		{
			cout << "The shop owner grows impatient. \"Stop wasting my time with nonsensical questions!\"" << endl;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getInput(currentPhase);
	}
}