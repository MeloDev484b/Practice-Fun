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

int getInput(char phase);
void isTheKingAlive();
void attackDirection();
void preparation();
void combat();
void store();
void randomEvent();


Army army(50, 0, "South");
Troops troops(10, 10, 10);
Army enemyArmy(20, 0, "South");
Resources resources;
int kingArms = 2;

int main()
{
	srand(time(0));
	cout << "Defend your castle!\n" << endl;
	while (kingAlive == true)
	{
		attackDirection();
		preparation();
	}

	cout << "Thank you for playing." << endl;
	return 0;
}

int getInput(char phase)
{
	char currentPhase = phase;
	int userInput;
	cin >> userInput;
	userInput = round(userInput);
	if (userInput < 0 || cin.fail())
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
	else
	{
		return userInput;
	}
}
void attackDirection() //where are the enemies coming from, and how many?
{
	enemyArmy.rollArmySize();
	enemyArmy.rollDirection();
	cout << enemyArmy.getArmySize() << " enemies approach from the " << enemyArmy.getDirection() << "!\n" << endl;
	randomEvent();
}
void isTheKingAlive()
{
	int currentArmySize = army.getArmySize();
	if (currentArmySize < 1)
	{
		cout << "The king has fallen; you are at the enemy's mercy." << endl;
		cout << troops.getKills() << " enemy soldiers fell to your troops." << endl;
		if (kingArms > 2)
		{
			cout << "Your kind had " << kingArms << " at the time of his passing. Oddly enough, his apothocary has left town." << endl;
		}
		kingAlive = false;
	}
}
void preparation()
{
	string enemyLocation = enemyArmy.getDirection();
	int tempArmySize = army.getArmySize();
	//determine where troops go before the attack
	for (int i = 0; i < DIRECTION_ARRAY_SIZE; i++)
	{
		if (army.getArmySize() > 0 && tempArmySize > 0)
		{
			int stationInput;
			cout <<endl<< "You have " << tempArmySize << " troops at your disposal." << endl;
			cout << "How any troops will you send to the " << army.returnArrayDirection(i) << "?" << endl;
			stationInput = getInput('p');
			if (stationInput <= tempArmySize)
			{
				army.setArmySizeLocation(stationInput, i);
				tempArmySize -= stationInput;
			}
			else if(stationInput > tempArmySize)
			{
				cout << "You can't allocate more troops than you have!" << endl;
				cout << "You send the rest of your troops to the " << army.returnArrayDirection(i) << ".\n" << endl;
				army.setArmySizeLocation(tempArmySize, i);
				tempArmySize = 0;
			}
		}
	}
	combat();
}
void combat()
{
	int tempArmySize = army.getArmySize();
	int enemyDeaths = 0;
	int allyDeaths = 0;
	//determine results of attack
	for (int i = 0; i < DIRECTION_ARRAY_SIZE; i++) //loop through each direction
	{
		if (enemyArmy.getDirection() == army.returnArrayDirection(i) && (enemyArmy.getArmySize() - army.getArcherAmount()) > (army.getArmySizeLocation(i) * (troops.getMelee() / 10)))
		{
			tempArmySize -= (army.getArmySizeLocation(i)) * (10 / troops.getArmour());
			allyDeaths = (army.getArmySizeLocation(i) * (10 / troops.getArmour()));
			army.setArmySize(tempArmySize);
			enemyDeaths = (army.getArmySizeLocation(i) * (troops.getMelee() / 10));
			troops.setKills(enemyDeaths);
			cout << "After taking down " << enemyDeaths << " enemies, you suffer a loss in the " << army.returnArrayDirection(i) << "." << endl;
			cout << troops.getKills() << " enemies have fallen to your troops." << endl;
			cout << "You lost " << allyDeaths << " of your troops in this fight." << endl;

		}
		else if (enemyArmy.getDirection() == army.returnArrayDirection(i)) //only display victory message & reward with gold if fought enemy
		{
			int drops = rand() % 100 + 1;
			enemyDeaths = (army.getArmySizeLocation(i) * (troops.getMelee() / 10));
			allyDeaths = (army.getArmySizeLocation(i) / rand() % 2 + 2);
			tempArmySize -= allyDeaths;
			army.setArmySize(tempArmySize);
			cout << "You triumphed over " <<enemyDeaths<<" enemies in the " << army.returnArrayDirection(i) << "!" << endl;
			troops.setKills(enemyDeaths);
			cout << troops.getKills() << " enemies have fallen to your troops." << endl;
			cout << "You lost " << allyDeaths << " of your troops in this fight." << endl;
			cout << "You loot supplies worth " << drops << " gold from the battlefield.\n" << endl;
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
		cout << "You have " << resources.getGold() << " gold." << endl;
		cout << "As the fighting dies down, you strategize how to use your resources to improve your chances at the next wave.\n" << endl;
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
void randomEvent()
{
	int chance = rand() % 5 + 1;
	if (chance == 1)//test nums
	{
		//stronger enemy appears
		int enemyType = rand() % 1;
		if(enemyType > 0)//test nums
		{
			cout << "The ground begins to shake. You notice a troll lurking behind the enemy army." << endl;
			cout << "You suspect it will take at least 5 extra men to take down." << endl;
			enemyArmy.setArmySize(enemyArmy.getArmySize() + 5);
			cout << enemyArmy.getArmySize();//test
		}
		else
		{
			cout << "The sky darkens. Your stomach drops as you see a dragon crush and burninate 10 troops." << endl;
			army.setArmySize(army.getArmySize() - 10);
			cout << army.getArmySize()<<endl;//test
		}
	}
	else if (chance == 2)//test nums
	{
		//troops or archers join your army from far off kingdom
		int troopType = rand() % 1;
		if (troopType > 0)
		{
			cout << "A couple Dust Bandit Bowmen have joined your cause." << endl;
			army.setArcherAmount(army.getArcherAmount() + 2);
			cout << army.getArcherAmount() << endl;//test
		}
		else
		{
			cout << "A few soldiers from the Burthorpe Imperial Guard have been sent to your aid!" << endl;
			army.setArmySize(army.getArmySize() + 5);
			cout << army.getArmySize() << endl;//test
		}
	}
	else if (chance == 3)//test nums
	{
		//troops get trained in attack or defense
		int trainer = rand() % 1;
		if (trainer > 0)
		{
			cout << "Christoph Walker stops by and shares some defensive techniques with your troops." << endl;
			troops.setArmour(troops.getArmour() + 1);
			cout << troops.getArmour() << endl;//test
		}
		else
		{
			cout << "A traveler, from a far off land called Ionia, trains your troops in the way of the blade." << endl;
			troops.setMelee(troops.getMelee() + 1);
			cout << troops.getMelee() << endl;//test
		}
	}
	else if (chance == 4)//test nums
	{
		//find gold
		int currentGold = resources.getGold();
		int foundGold = rand() % 100 + 1;
		cout << "A leprechaun appears at your door and delivers a pot of gold.\n" << endl;
		cout << "You find " << foundGold << " gold." << endl;
		resources.setGold(currentGold + foundGold);
	}
	else if (chance == 5)//test nums
	{
		//king grows another arm
		cout << "It appears the king has grown another arm. Perhaps it is the elixer of immortality he continues to drink?" << endl;
		kingArms++;
	}
}