#include<iostream>
#include <string>
#include <array>
using namespace std;

//resources & goods available
int gold = 500;
int weaponsUpgrade = 300;
int armourUpgrade = 300;
int reinforcements = 200; //recruit 20 foot soldiers
int archers = 400; //increase ranged strength by 4
//army stats
double armour = 10.0;
double melee = 10.0;
double range = 0.0;
int armySize = 80;
int archerAmount = 0;
//enemy
int enemyGrowth = 10;
int totalEnemies = 30;
int enemyArmySize = 0;
int enemiesKilled = 0;
int drops;

int stationInput;
const int directionArraySize = 4;
const array <string, directionArraySize> directions{ "North","East","South","West"}; //holds names of directions
array <int, directionArraySize> armySizeLocation{ 0,0,0,0 };//position 0 is North, 1 is East...etc

string enemyDirection = directions[0];

bool kingAlive = true;

void attackDirection();
void preparation();
void combat();
void store();
void isTheKingAlive();

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
	int randomEnemyAmnt = rand() % totalEnemies; //select number of enemies between 20 & 100
	int randomDir = rand() % 4;
	if (randomEnemyAmnt < 20)
	{
		randomEnemyAmnt = 20;
	}
	enemyArmySize = randomEnemyAmnt;
	enemyDirection = directions[randomDir];
	cout << randomEnemyAmnt << " enemies approach from the " << directions[randomDir] << "!" << endl;
	totalEnemies += rand() % 20;
}
void preparation()
{
	int saveArmySize = armySize;
	string uInput;
	//determine where troops go before the attack
	for (int i = 0; i < directionArraySize; i++)
	{
		if (armySize > 0)
		{
			cout << "You have " << armySize << " troops at your disposal." << endl;
			cout << "How any troops will you send to the " << directions[i] << "?" << endl;
			cin >> stationInput;
			if (stationInput <= armySize)
			{
				armySizeLocation[i] = stationInput;
				armySize -= stationInput;
			}
		}
	}
	armySize = saveArmySize;
	combat();
}
void combat()
{
	//determine results of attack
	for (int i = 0; i < directionArraySize; i++) //loop through each direction
	{
		int enemyDeaths = 0;
		if (enemyDirection == directions[i] && (enemyArmySize - range) > (armySizeLocation[i] * (melee/10)))
		{
			armySize -= (armySizeLocation[i] * (armour/10));
			enemyDeaths = (armySizeLocation[i] * (melee / 10));
			enemiesKilled += enemyDeaths;
			cout << "After taking down "<<enemyDeaths<<" enemies, you suffer a loss in the " << directions[i] << "." << endl;
			cout << enemiesKilled << " enemies have fallen to your troops." << endl;

		}
		else if (enemyDirection == directions[i]) //only display victory message & reward with gold if fought enemy
		{
			drops = rand() % 100;
			cout << "You triumphed over " <<enemyDeaths<<" enemies in the " << directions[i] << "!" << endl;
			enemiesKilled += enemyDeaths;
			cout << enemiesKilled << " enemies have fallen to your troops." << endl;
			cout << "You loot supplies worth " << drops << " gold from the battlefield." << endl;
			gold += drops;
		}
	}
	isTheKingAlive();
	store();
}
void store()
{
	if (kingAlive == true)
	{
		int userChoice;
		cout << "As the fighting dies down, you strategize how to use your resources to improve your chances at the next wave." << endl;
		cout << "You have " << gold << " gold." << endl;
		cout << "The shop contains the following: " << endl;
		cout << "Weapons - 300g(1), Armour - 300g(2), Reenforcements - 200g(3), Archers - 400g(4)" << endl;
		cout << "Type 1, 2, 3, or 4 to make your selection." << endl;
		cin >> userChoice;
		if (userChoice == 1 && gold > 300)
		{
			cout << "You improve your army's weapons." << endl;
			melee *= 1.1;
			gold -= 300;
		}
		else if (userChoice == 2 && gold > 300)
		{
			cout << "You improve your army's armour." << endl;
			armour *= 1.1;
			gold -= 300;
		}
		else if (userChoice == 3 && gold > 200)
		{
			cout << "You hire more footsoldiers." << endl;
			armySize += (reinforcements / 10);
			gold -= 200;
		}
		else if (userChoice == 4 && gold > 400)
		{
			cout << "You hire a party of archers to support your footsoldiers." << endl;
			range += (archers / 40);
			gold -= 400;
		}
		else
		{
			cout << "Do you take me for a fool? My shop is closed to stingy saps!" << endl;
		}
	}
}
void isTheKingAlive()
{
	if (armySize < 1)
	{
		cout << "The king has fallen; you are at the enemy's mercy." << endl;
		cout << enemiesKilled << " enemy soldiers fell to your troops." << endl;
		kingAlive = false;
	}
}

//to do: implement classes, flesh out game loop, adjust spacing, balance numbers, improve shop