#include<iostream>
#include <string>
#include <array>
#include <limits>
#include <algorithm>
#include <cmath>

#include "Resources.h"
#include "Army.h"
#include "Shop.h"
#include "Troops.h"
#include "ScoreKeeper.h"
#include"RovingTraders.h"
using namespace std;

bool kingAlive = true;

//might change from constant so it can be adjusted based on how many enemies you have killed
const int DIPLOMACY_DENOMINATOR = 49;
//number of rolls for diplomacy
const int DIPLOMACY_ARRAY_SIZE = 5;

int getInput(char phase);
int getInput(int numOptions);
void isTheKingAlive();
void attackDirection();
void preparation();
void combatScoreUpdate(int newKills, int newAllyDeaths);
void combatArrayCheck(Army playerArmy, Army enemyArmy);
void store();
void randomEvent();
int randomEventRoll();
void buyOrSell(bool buy, int input, int gold);
void openRovingTraderShop();
void diplomacy();
int rollDie(int sides);
void whichElementLeft();
int returnModifiedCombatPower(int numberOfTroops, int meleeSkill);
int returnModifiedLoss(int numberOfTroopsLost, int armourSkill, int currentArmySize);
int returnNumberOfPrisoners(int enemySoldiers);
bool battleWin(int playerSoldiers, int enemySoldiers);
int generateLoot(/*add modifier later*/);


Army army(50, 0);
Troops troops(2, 2);
Army enemyArmy(0, 0);
Resources resources;
ScoreKeeper playerScore;
RovingTraders rovingTraders;

int main()
{
	srand(time(0));
	cout << "Defend your castle!\n";
	while (kingAlive == true)
	{
		attackDirection();
		preparation();
	}

	cout << "\nThank you for playing.\n";
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
			cout << "We need you to focus! How many soldiers will you send?\n";
		}
		else if (phase == 's')
		{
			cout << "The shop owner grows impatient. \"Stop wasting my time with this piffle!\"\n";
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
int getInput(int numOptions)
{
	int userInput;
	cin >> userInput;
	userInput = round(userInput);
	if (userInput <= 0 || userInput > numOptions || cin.fail())
	{
		cout << "It seems like you may have made a miscalculation.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getInput(numOptions);
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
	enemyArmy.whereAreTheEnemies();
	randomEvent();
}
void isTheKingAlive()
{
	int currentArmySize = army.getArmySize();
	if (currentArmySize <= 0)
	{
		int kingArms = playerScore.getKingArms();
		cout << "The king has fallen; you are at the enemy's mercy.\n";
		cout << playerScore.getKills() << " enemy soldiers fell to your army.\n";
		cout << "You lost " << playerScore.getAllyDeaths() << " good soldiers during your defense.\n";
		if (kingArms > 2)
		{
			cout << "Your kind had " << kingArms << " at the time of his passing. Oddly enough, his apothocary has left town.\n";
		}
		kingAlive = false;
	}
}
void preparation()
{
	int tempArmySize = army.getArmySize();
	//make an attempt at diplomacy first
	diplomacy();
	//determine where troops go before the attack
	for (int i = 0; i < DIRECTION_ARRAY_SIZE; i++)
	{
		if (army.getArmySize() > 0 && tempArmySize > 0 && enemyArmy.getSoldiersAtLocation(i) > 0)
		{
			string direction = army.getDirection(i);
			int stationInput;
			cout << "\nYou have " << tempArmySize << " soldiers at your disposal.\n";
			cout << "How many soldiers will you send to the " << direction << "?\n";
			stationInput = getInput('p');
			if (stationInput <= tempArmySize)
			{
				army.setSoldiersAtLocation(stationInput, i);
				tempArmySize -= stationInput;
			}
			else if(stationInput > tempArmySize)
			{
				cout << "You can't allocate more soldiers than you have!\n";
				cout << "You send all available soldiers to the " << direction << ".\n";
				army.setSoldiersAtLocation(tempArmySize, i);
				tempArmySize = 0;
			}
		}
	}
	combatArrayCheck(army, enemyArmy);
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
		cout << "You have " << resources.getGold() << " gold.\n";
		cout << "\nAs the fighting dies down, you strategize how to use your resources to improve your chances at the next wave.\n";
		cout << "The shop contains the following: \n";
		cout << "Weapons - 300g(1), Armour - 300g(2), Reenforcements - 200g(3), Archers - 400g(4)\n";
		cout << "Type 1, 2, 3, or 4 to make your selection.\n";
		userChoice = getInput('s');
		if (userChoice == 1 && resources.getGold() > 300)
		{
			cout << "You improve your army's weapons.\n";
			troops.setMelee(currentMelee + 1);
			resources.setGold(-300);
			cout << "Current weapons skill level: " << troops.getMelee() << ".\n";
		}
		else if (userChoice == 2 && resources.getGold() > 300)
		{
			cout << "You improve your army's armour.\n";
			troops.setArmour(currentArmour + 1);
			resources.setGold(-300);
			cout << "Current armour skill level: " << troops.getArmour() << ".\n";
		}
		else if (userChoice == 3 && resources.getGold() > 200)
		{
			cout << "You hire more soldiers.\n";
			army.setArmySize(currentArmySize + 10); //NOTE:make this scale
			resources.setGold(-200);
			cout << "Total soldiers enlisted: " << army.getArmySize() << ".\n";
		}
		else if (userChoice == 4 && resources.getGold() > 400)
		{
			cout << "You hire a party of archers to support your footsoldiers.\n";
			army.setArcherAmount(currentArchers + 4); ///NOTE:make this scale
			resources.setGold(-400);
			cout << "Total archers enlisted: " << army.getArcherAmount() << ".\n";
		}
		else
		{
			cout << "Do you take me for a fool? My shop is closed to old saps like you!\n";
		}
	}
	rovingTraders.setDaysSinceLastPurchase(1);
}
void randomEvent()
{
	int chance = randomEventRoll();
	if (chance >= 53 )//test nums
	{
		//stronger enemy appears
		int enemyType = rand() % 1;
		if(enemyType > 0)//test nums
		{
			cout << "The ground begins to shake. You notice a troll lurking behind the enemy army.\n";
			cout << "You suspect it will take at least 5 extra men to take down.\n";
			enemyArmy.setArmySize(enemyArmy.getArmySize() + 5);
			cout << enemyArmy.getArmySize();//test
		}
		else
		{
			cout << "The sky darkens. Your stomach drops as you see a dragon crush and burninate 10 soldiers.\n";
			army.setArmySize(army.getArmySize() - 10);
			cout << army.getArmySize()<<endl;//test
		}
	}
	else if (chance == 52)//test nums
	{
		//troops or archers join your army from far off kingdom
		int troopType = rand() % 1;
		if (troopType > 0)
		{
			cout << "A couple Dust Bandit Bowmen have joined your cause.\n";
			army.setArcherAmount(army.getArcherAmount() + 2);
			cout << army.getArcherAmount() << endl;//test
		}
		else
		{
			cout << "A few soldiers from the Burthorpe Imperial Guard have been sent to your aid!\n";
			army.setArmySize(army.getArmySize() + 5);
			cout << army.getArmySize() << endl;//test
		}
	}
	else if (chance == 51)//test nums
	{
		//troops get trained in attack or defense
		int trainer = rand() % 1;
		if (trainer > 0)
		{
			cout << "Christoph Walker stops by and shares some defensive techniques with your soldiers.\n";
			troops.setArmour(troops.getArmour() + 1);
			cout << troops.getArmour() << endl;//test
		}
		else
		{
			cout << "A traveler, from a far off land called Ionia, trains your soldiers in the way of the blade.\n";
			troops.setMelee(troops.getMelee() + 1);
			cout << troops.getMelee() << endl;//test
		}
	}
	else if (chance >= 49 && chance != 50 && chance != 51 && chance != 52 && chance != 53)//test nums - lol
	{
		//find gold
		int currentGold = resources.getGold();
		int foundGold = rand() % 1000 + 1;
		cout << "A leprechaun appears at your door and delivers a pot of gold.\n";
		cout << "You find " << foundGold << " gold.\n";
		resources.setGold(foundGold);
	}
	else if (chance >= 50 && chance != 51 && chance != 52 && chance != 53)//test nums
	{
		//king grows another arm
		cout << "It appears the king has grown another arm. Perhaps it is the elixer of immortality he continues to drink?\n";
		playerScore.setKingArms();
	}
	else if (chance >= 46 && chance < 50)//test nums
	{
		//roving trader passes through
		cout << "A band of roving traders are passing through. They are willing to buy or sell wares.\n";
		openRovingTraderShop();
	}
}
int randomEventRoll()
{
	int result = 0;
	array <int, 6> randomEventChance{ 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < randomEventChance.size(); i++)
	{
		randomEventChance[i] = rollDie(12);
		if (randomEventChance[i] > 6)
		{
			result += randomEventChance[i];
		}
	}
	return result;
}
void buyOrSell(bool buy, int input, int gold)
{
	int playerGold = gold;
	int userInput = input;
	int maxPurchase = 0;
	if (userInput == 1)
	{
		if (buy)
		{
			maxPurchase = min(rovingTraders.getScrapMetal(), (playerGold/rovingTraders.getPrices(0)));
			cout << "How many metal scraps would you like to buy?\n";
			int metalToBuy = getInput(maxPurchase);
			rovingTraders.setScrapMetal(rovingTraders.getScrapMetal() - metalToBuy);
			rovingTraders.setGold(metalToBuy * rovingTraders.getPrices(0));
			resources.setGold(-(metalToBuy * rovingTraders.getPrices(0)));
			cout << "You bought " << metalToBuy << " metal scraps. You have " << resources.getGold() << " gold.\n";
			playerScore.setTrades(1);
		}
		else
		{
			cout << "How many metal scraps would you like to sell?\n";
			int metalToSell = getInput(resources.getMetalScraps());
			resources.setMetalScraps(resources.getMetalScraps() - metalToSell);
			resources.setGold(metalToSell * rovingTraders.getPrices(0));
			cout << "You sold " << metalToSell << " metal scraps. You have " << resources.getGold() << " gold.\n";
			playerScore.setTrades(1);
		}
	}
	else if (userInput == 2)
	{
		if (buy)
		{
			maxPurchase = min(rovingTraders.getScrapWood(), (playerGold / rovingTraders.getPrices(0)));
			cout << "How many wood scraps would you like to buy?\n";
			int woodToBuy = getInput(maxPurchase);
			rovingTraders.setScrapWood(rovingTraders.getScrapWood() - woodToBuy);
			rovingTraders.setGold((woodToBuy * rovingTraders.getPrices(1)));
			resources.setGold(-(woodToBuy * rovingTraders.getPrices(1)));
			cout << "You bought "<<woodToBuy << " wood scraps. You have " << resources.getGold() << " gold.\n";
			playerScore.setTrades(1);
		}
		else
		{
			cout << "How many wood scraps would you like to sell?\n";
			int woodToSell = getInput(resources.getWoodScraps());
			resources.setWoodScraps(resources.getWoodScraps() - woodToSell);
			resources.setGold(woodToSell * rovingTraders.getPrices(1));
			cout << "You sold " << woodToSell << " wood scraps. You have " << resources.getGold() << " gold.\n";
			playerScore.setTrades(1);
		}
	}
	else if (userInput == 3)
	{
		if (buy)
		{
			maxPurchase = min(rovingTraders.getStone(), (playerGold / rovingTraders.getPrices(0)));
			cout << "How much stone would you like to buy?\n";
			int stoneToBuy = getInput(maxPurchase);
			rovingTraders.setStone(rovingTraders.getStone() - stoneToBuy);
			rovingTraders.setGold((stoneToBuy * rovingTraders.getPrices(0)));
			resources.setGold(-(stoneToBuy * rovingTraders.getPrices(0)));
			cout << "You bought " << stoneToBuy << " stone. You have " << resources.getGold() << " gold.\n";
			playerScore.setTrades(1);
		}
		else
		{
			cout << "How much stone would you like to sell?\n";
			int stoneToSell = getInput(resources.getStone());
			resources.setStone(resources.getStone() - stoneToSell);
			resources.setGold(stoneToSell * rovingTraders.getPrices(2));
			cout << "You sold " << stoneToSell << " stone. You have " << resources.getGold() << " gold.\n";
			playerScore.setTrades(1);
		}
	}
	else if (userInput == 4)
	{
		cout << "How many prisoners would you like to sell?\n";
		int captivesToSell = getInput(resources.getCapturedEnemies());
		resources.setCapturedEnemies(captivesToSell);
		resources.setGold(captivesToSell * rovingTraders.getPrices(3));
		cout << "Transaction complete" << endl; //test
		cout << "You sold " << captivesToSell << " prisoners. You have " << resources.getGold() << " gold.\n";
		playerScore.setTrades(2);
	}
}
void openRovingTraderShop()
{
	bool buy;
	int userInput;
	int playerGold = resources.getGold();
	cout << "Oi I've got wares, care to take a look? Otherwise, stop wasting me time!\nYes - (1) / No - (2)\n";
	userInput = getInput(2);
	if (userInput == 1)
	{
		cout << "Right, this is what I've got in stock. 'Urry up then.\nMetal Scrap: " << rovingTraders.getScrapMetal() << " for " << rovingTraders.getPrices(0)
			<< " each(1)\nWood Scrap: " << rovingTraders.getScrapWood() << " for " << rovingTraders.getPrices(1) << " each(2)\nStone: " << rovingTraders.getStone() << " for " << rovingTraders.getPrices(2)
			<< " each(3)\nI'm also willing to, eh, buy some prisoners if you've got any. Say, " << rovingTraders.getPrices(3) << " each?(4)\n";
		if (resources.getMysteriousWard() > 0 && playerGold > 5000)
		{
			cout << "I've also got this, uh, mysterious thing. It kinda spooks me. Not sure what it is.\n You wanna buy it for 5000 gold?\nYes - (1) / No - (2)\n";
			userInput = getInput(2);
			if (userInput == 1)
			{
				cout << "Right, here you go then.\n";
				resources.setGold(-5000);
			}
			else
			{
				cout << "Yeah, you're probably right to steer clear of it. I'll hold onto it, in case you change your mind.\n";
			}
		}
		cout << "Would you like to buy or sell?\nBuy - (1) / Sell - (2)\n";
		userInput = getInput(2);
		if (userInput == 1)
		{
			buy = true;
		}
		else
		{
			buy = false;
		}
		cout << "buy set to " << boolalpha << buy << endl;//test
		cout << "What item are you interested in?\n";
		userInput = getInput(4);
		cout << "User input " << userInput << endl; //test
		buyOrSell(buy, userInput, playerGold);


		rovingTraders.setDaysSinceLastPurchase(0);
	}
	else
	{
		cout << "\nRight, I'll be going then.\n\n";
	}

}
void diplomacy()
{
	bool useDiplomacy = false;
	cout << "\nWould you like to attempt to send diplomats to convince enemies to leave the fight?\nYes - (1) No - (2)\n";
	if (getInput(2) == 1) 
	{
		useDiplomacy = true;
	}
	if (useDiplomacy == true)
	{
		float highestRoll = 0;
		float diplomacyRollArray[DIPLOMACY_ARRAY_SIZE]{};
		float currentDiplomacySkill = troops.getDiplomacySkill();
		cout << "\nYou select several of your soldiers to serve as diplomats and send them towards the enemy's encampment.\n";
		for (int i = 0; i < DIPLOMACY_ARRAY_SIZE; i++)
		{
			diplomacyRollArray[i] = rand() % DIPLOMACY_DENOMINATOR + currentDiplomacySkill;
		}
		for (int i = 0; i < DIPLOMACY_ARRAY_SIZE; i++)
		{
			if (diplomacyRollArray[i] > highestRoll)
			{
				highestRoll = diplomacyRollArray[i];
			}
		}
		cout << "\nHighest roll: " << highestRoll << ".\n"; //test
		if (highestRoll < 50 && highestRoll < 52)
		{
			cout << "\nYour diplomats return with a nervous look in their eyes.\nAlthough their attempt was unsuccessful they have improved their diplomacy skills.\n";
			troops.setDiplomacySkill(0.25);
		}
		else if (highestRoll >= 52 && highestRoll < 80)
		{
			int currentEnemyArmySize = enemyArmy.getArmySize();
			int enemiesLeaving = int(currentDiplomacySkill);
			cout << "\nYour diplomats walk back with their heads held high. They convinced " << enemiesLeaving << " enemies to leave the fight!\n";
			troops.setDiplomacySkill(1.25);
			//remove enemies from the enemy army
			enemyArmy.setArmySize(currentEnemyArmySize - enemiesLeaving);
			enemyArmy.rollDirection();
		}
		else if (highestRoll > 80 && highestRoll < 110)
		{
			int currentPlayerArmySize = army.getArmySize();
			int currentEnemyArmySize = enemyArmy.getArmySize();
			int enemiesJoining = int(currentDiplomacySkill);
			cout << "\nYour diplomats must be kiniving creature as they have convinced " << enemiesJoining << " enemies to fight alongside your soldiers!\n";
			troops.setDiplomacySkill(3);
			//remove enemies joining from enemy army and add to player's army
			enemyArmy.setArmySize(currentEnemyArmySize - enemiesJoining);
			army.setArmySize(currentPlayerArmySize + enemiesJoining);
			enemyArmy.rollDirection();
		}
		else if (highestRoll > 110)
		{
			cout << "\nYour diplomats return, bustling with excitement.\n";
			troops.setDiplomacySkill(5);
			//one element of the enemy army retreats
			whichElementLeft();
		}
	}
	enemyArmy.whereAreTheEnemies();
}
///Combat Begins
void combatArrayCheck(Army playerArmy, Army enemyArmy)
{
	int meleeModifier = troops.getMelee();
	int defenseModifier = troops.getArmour();
	int totalKills = 0;
	int totalEnemyKills = 0;
	for (int i = 0; i <= ARRAY_LOOP_CONST; i++)
	{
		int playerElement = army.getSoldiersAtLocation(i);
		int enemyElement = enemyArmy.getSoldiersAtLocation(i);
		string direction = army.getDirection(i);
		int tempPlayerKills = 0;
		int tempEnemyKills = 0;
		int tempPrisoners = 0;
		if (enemyElement > 0)
		{
			int playerArmySize = army.getArmySize();
			if (battleWin(playerElement, enemyElement))
			{
				int gold = generateLoot();
				tempPlayerKills += min(rand() % returnModifiedCombatPower(playerElement, meleeModifier), enemyElement);
				totalKills += tempPlayerKills;
				tempPrisoners += returnNumberOfPrisoners(enemyElement);
				resources.setCapturedEnemies(-tempPrisoners);
				cout << "Your army routes the enemy forces! Your soldiers killed " << tempPlayerKills << " soldiers, took " << tempPrisoners << " prisoners, and looted " << gold << " gold from the battlefield.\n";
				resources.setGold(gold);
			}
			else if (playerElement <= 0)
			{
				tempEnemyKills += rand() % returnModifiedLoss(playerArmySize, defenseModifier, playerArmySize) + 1;
				if (tempEnemyKills > playerArmySize)
				{
					tempEnemyKills = playerArmySize;
				}
				totalEnemyKills += tempEnemyKills;
				army.setArmySize(playerArmySize - tempEnemyKills);
				cout << "Your walls were breached! You lost " << tempEnemyKills << " good soldiers.\n";
			}
			else
			{
				tempEnemyKills += rand() % returnModifiedLoss(playerElement, defenseModifier, playerArmySize) + 1;
				totalEnemyKills += tempEnemyKills;
				army.setArmySize(playerArmySize - tempEnemyKills);
				if (enemyElement > (playerElement * 2))
				{
					cout << "Even though your soldiers' numbers dwindle, they were able to repel the invading force. " << tempEnemyKills << " perished in the defense.\n";
				}
				else
				{
					cout << "Your army was routed by the enemy. You lost " << tempEnemyKills << " good soldiers.\n";
				}
			}
		}
	}
	playerScore.setKills(totalKills);
	playerScore.setAllyDeaths(totalEnemyKills);
	isTheKingAlive();
	cout << "\nAfter the battle you find that your soldiers have taken down " << totalKills << " enemies. This came at a cost of " << totalEnemyKills << " of your own soldiers.\n";
	store();
}
///End Combat
void combatScoreUpdate(int newKills, int newAllyDeaths)
{
	playerScore.setKills(newKills);
	playerScore.setAllyDeaths(newAllyDeaths);
	cout << "\nScore updated!\n " << playerScore.getKills() << " kills, " << playerScore.getAllyDeaths() << " ally deaths!\n\n";
}
int rollDie(int sides)
{
	return rand() % sides + 1;
}
void whichElementLeft()
{
	int deserting = rand() % 3;
	if (deserting == 0 && enemyArmy.getSoldiersAtLocation(0) > 0)
	{
		cout << "The Northern enemy element of " << enemyArmy.getSoldiersAtLocation(0) << " soldiers has been convinced to desert!\n";
		enemyArmy.setSoldiersAtLocation(0, 0);
	}
	else if (deserting == 1 && enemyArmy.getSoldiersAtLocation(1) > 0)
	{
		cout << "The Eastern enemy element of " << enemyArmy.getSoldiersAtLocation(1) << " soldiers has been convinced to desert!\n";
		enemyArmy.setSoldiersAtLocation(0, 1);
	}
	else if (deserting == 2 && enemyArmy.getSoldiersAtLocation(2) > 0)
	{
		cout << "The Southern enemy element of " << enemyArmy.getSoldiersAtLocation(2) << " soldiers has been convinced to desert!\n";
		enemyArmy.setSoldiersAtLocation(0, 2);
	}
	else if (deserting == 3 && enemyArmy.getSoldiersAtLocation(3) > 0)
	{
		cout << "The Western enemy element of " << enemyArmy.getSoldiersAtLocation(3) << " soldiers has been convinced to desert!\n";
		enemyArmy.setSoldiersAtLocation(0, 3);
	}
	else
	{
		whichElementLeft();
	}
}
int returnModifiedCombatPower(int numberOfTroops, int meleeSkill)
{
	return numberOfTroops + meleeSkill;
}
int returnModifiedLoss(int numberOfTroopsLost, int armourSkill, int currentArmySize)
{
	if (currentArmySize > numberOfTroopsLost)
	{
		return rand() % currentArmySize + 1;
	}
	else
	{
		if (numberOfTroopsLost - armourSkill)
		{
			return numberOfTroopsLost - armourSkill;
		}
		else
		{
			return (numberOfTroopsLost - armourSkill) + 1;
		}
	}
}
int returnNumberOfPrisoners(int enemySoldiers)
{
	return (enemySoldiers / 10);
}
bool battleWin(int playerSoldiers, int enemySoldiers)
{
	if ((playerSoldiers - enemySoldiers) >= 0)
	{
		//player wins
		return true;
	}
	else
	{
		//player loses
		return false;
	}
}
int generateLoot(/*add modifier later*/)
{
	return rand() % 90 + 1;
}