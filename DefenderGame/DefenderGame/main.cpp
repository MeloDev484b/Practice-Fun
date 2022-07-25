#include<iostream>
#include <string>
#include <array>
#include <limits>
#include <algorithm>
#include <cmath>

#include "Resources.h"
#include "Army.h"
#include "EnemyArmy.h"
#include "Shop.h"
#include "Troops.h"
#include "ScoreKeeper.h"
#include "RovingTraders.h"

bool kingAlive = true;

// Might change from constant so it can be adjusted based on how many enemies you have killed
const int DIPLOMACY_DENOMINATOR = 49;
// Number of rolls for diplomacy
const int DIPLOMACY_ARRAY_SIZE = 5;

// Phase "p" is planning phase, "s" is the shop phase
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
void openRovingTraderShop();
void diplomacy();
int rollDie(int sides);
void whichElementLeft();
int returnModifiedCombatPower(int numberOfTroops, int meleeSkill, int archers);
int returnModifiedLoss(int numberOfTroopsLost, int armourSkill, int currentArmySize);
int returnNumberOfPrisoners(int enemySoldiers);
bool battleWin(int playerSoldiers, int enemySoldiers);
int generateLoot(ScoreKeeper playerScore);
std::string pluralWord(std::string pluralCheck, int numberOfEnemies);
void setDifficultyLevel();


Army army(50, 0);
Troops troops(2, 2);
EnemyArmy enemyArmy(0);
Resources resources;
ScoreKeeper playerScore;
RovingTraders rovingTraders;

// Game loop
int main()
{
	srand(time(0));
	setDifficultyLevel();
	std::cout << "Defend your castle!\n";
	while (kingAlive == true)
	{
		attackDirection();
		preparation();
	}

	std::cout << "\nThank you for playing.\n";
	return 0;
}

int getInput(char phase)
{
	char currentPhase = phase;
	int userInput;
	std::cin >> userInput;
	userInput = round(userInput);
	if (userInput < 0 || std::cin.fail())
	{
		if (phase == 'p')
		{
			std::cout << "We need you to focus! How many soldiers will you send?\n";
		}
		else if (phase == 's')
		{
			std::cout << "The shop owner grows impatient. \"Stop wasting my time with this piffle!\"\n";
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
	std::cin >> userInput;
	userInput = round(userInput);
	if (userInput <= 0 || userInput > numOptions || std::cin.fail())
	{
		std::cout << "It seems like you may have made a miscalculation.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getInput(numOptions);
	}
	else
	{
		return userInput;
	}
}
// Generate enemies and their locations
void attackDirection()
{
	// Create the enemy army
	enemyArmy.rollArmySize();
	// Place enemy troops at various locations
	enemyArmy.rollDirection();
	// Tell the player where the enemies are coming from
	enemyArmy.whereAreTheEnemies();
	// Roll for a random event to occur
	randomEvent();
}
void isTheKingAlive()
{
	int currentArmySize = army.getArmySize();
	if (currentArmySize <= 0)
	{
		int kingArms = playerScore.getKingArms();
		std::cout << "The king has fallen; you are at the enemy's mercy.\n";
		std::cout << playerScore.getKills() << " enemy soldiers fell to your army.\n";
		std::cout << "You lost " << playerScore.getAllyDeaths() << " good soldiers during your defense.\n";
		if (kingArms > 2)
		{
			std::cout << "Your kind had " << kingArms << " at the time of his passing. Oddly enough, his apothocary has left town.\n";
		}
		playerScore.setScore();
		std::cout << "\nYour final score was " << playerScore.getScore() << ".\n";
		kingAlive = false;
	}
}
void preparation()
{
	int tempArmySize = army.getArmySize();

	// Roll for diplomacy before the battle
	diplomacy();

	// Player chooses where their soldiers will go
	for (int i = 0; i < DIRECTION_ARRAY_SIZE; i++)
	{
		if (army.getArmySize() > 0 && tempArmySize > 0 && enemyArmy.getSoldiersAtLocation(i) > 0)
		{
			std::string direction = army.getDirection(i);
			int stationInput;
			std::cout << "\nYou have " << tempArmySize << " soldiers at your disposal.\n";
			std::cout << "How many soldiers will you send to the " << direction << "?\n";
			stationInput = getInput('p');
			if (stationInput <= tempArmySize)
			{
				army.setSoldiersAtLocation(stationInput, i);
				tempArmySize -= stationInput;
			}
			else if(stationInput > tempArmySize)
			{
				std::cout << "\n>>>You can't allocate more soldiers than you have!\n";
				std::cout << ">>>You send all available soldiers to the " << direction << ".\n";
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
		std::cout << "You have " << resources.getGold() << " gold.\n";
		std::cout << "You have " << army.getArmySize() << " soldiers available.\n";
		std::cout << "\nAs the fighting dies down, you strategize how to use your resources to improve your chances at the next wave.\n";
		std::cout << "The shop contains the following: \n";
		std::cout << "Weapons - 300g - (1), Armour - 300g - (2), Reenforcements - 200g - (3), Archers - 400g - (4)\n";
		std::cout << "Type 1, 2, 3, or 4 to make your selection.\n";
		userChoice = getInput('s');
		if (userChoice == 1 && resources.getGold() > 300)
		{
			std::cout << "You improve your army's weapons.\n";
			troops.setMelee(currentMelee + 1);
			resources.setGold(-300);
			std::cout << "Current weapons level: " << troops.getMelee() << ".\n";
		}
		else if (userChoice == 2 && resources.getGold() > 300)
		{
			std::cout << "You improve your army's armour.\n";
			troops.setArmour(currentArmour + 1);
			resources.setGold(-300);
			std::cout << "Current armour level: " << troops.getArmour() << ".\n";
		}
		else if (userChoice == 3 && resources.getGold() > 200)
		{
			std::cout << "You hire more soldiers.\n";
			army.setArmySize(currentArmySize + 10); // NOTE:make this scale
			resources.setGold(-200);
			std::cout << "Total soldiers enlisted: " << army.getArmySize() << ".\n";
		}
		else if (userChoice == 4 && resources.getGold() > 400)
		{
			std::cout << "You hire a party of archers to support your footsoldiers.\n";
			army.setArcherAmount(currentArchers + 4); // NOTE:make this scale
			resources.setGold(-400);
			std::cout << "Total archers enlisted: " << army.getArcherAmount() << ".\n";
		}
		else
		{
			std::cout << "Do you take me for a fool? My shop is closed to old saps like you!\n";
		}
	}
	rovingTraders.setDaysSinceLastPurchase(1);
}
void randomEvent()
{
	int chance = randomEventRoll();
	if (chance >= 53 )
	{
		// Stronger enemy appears
		int enemyType = rand() % 1;
		if(enemyType > 0)
		{
			std::cout << "\nThe ground begins to shake. You notice a troll lurking behind the enemy army.\n";
			std::cout << "You suspect it will take at least 5 extra men to take down.\n";
			enemyArmy.setArmySize(enemyArmy.getArmySize() + 5);
			std::cout << "The enemy army is now equivalent to an army of "<<enemyArmy.getArmySize()<<".\n";
		}
		else
		{
			std::cout << "\nThe sky darkens. Your stomach drops as you see a dragon crush and burninate 10 soldiers.\n";
			army.setArmySize(army.getArmySize() - 10);
		}
	}
	else if (chance == 52)
	{
		// Troops or archers join your army from far off kingdom
		int troopType = rand() % 1;
		if (troopType > 0)
		{
			std::cout << "\nA couple Dust Bandit Bowmen have joined your cause.\n";
			army.setArcherAmount(army.getArcherAmount() + 2);
			std::cout << "You have " << army.getArcherAmount() << " archers enlisted.\n";
		}
		else
		{
			std::cout << "\nA few soldiers from the Burthorpe Imperial Guard have been sent to your aid!\n";
			army.setArmySize(army.getArmySize() + 5);
			std::cout << "You have " << army.getArmySize() << " soldiers enlisted.\n";
		}
	}
	else if (chance == 51)
	{
		// Troops get trained in attack or defense
		int trainer = rand() % 1;
		if (trainer > 0)
		{
			std::cout << "\nChristoph Walker stops by and shares some defensive techniques with your soldiers.\n";
			troops.setArmour(troops.getArmour() + 1);
			std::cout << "Your soldiers' armour skill is now " << troops.getArmour() << ".\n";
		}
		else
		{
			std::cout << "\nA traveler, from a far off land called Ionia, trains your soldiers in the way of the blade.\n";
			troops.setMelee(troops.getMelee() + 1);
			std::cout << "Your soldiers' melee skill is now " << troops.getMelee() << ".\n";
		}
	}
	else if (chance >= 49 && chance != 50 && chance != 51 && chance != 52 && chance != 53)
	{
		// Find gold
		int currentGold = resources.getGold();
		int foundGold = rand() % 1000 + 1;
		std::cout << "\nA leprechaun appears at your door and delivers a pot of gold.\n";
		std::cout << "You find " << foundGold << " gold.\n";
		resources.setGold(foundGold);
	}
	else if (chance >= 50 && chance != 51 && chance != 52 && chance != 53)
	{
		// King grows another arm
		std::cout << "\nIt appears the king has grown another arm. Perhaps it is the elixer of immortality he continues to drink?\n";
		playerScore.setKingArms();
	}
	else if (chance >= 46 && chance < 50)
	{
		// Shady character looking to buy prisoners
		if (resources.getCapturedEnemies() > 0)
		{
			std::cout << "\nA shady character appears to be eyeing your prisoners.\n";
			openRovingTraderShop();
		}
		else
		{
			std::cout << "\nA shady character passes through.\nThey can't seem to find what they are looking for and whisk away before you can approach them.\n";
		}
	}
}
int randomEventRoll()
{
	int result = 0;
	std::array <int, 6> randomEventChance{ 0, 0, 0, 0, 0, 0 };
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
void openRovingTraderShop()
{
	bool buy;
	int userInput;
	int playerGold = resources.getGold();
	std::cout << "\nYou interested in sellin' any prisoners? Otherwise, stop wasting me time!\nYou have " <<resources.getCapturedEnemies() << " prisoners.\n" << "Yes - (1) / No - (2)\n";
	userInput = getInput(2);
	if (userInput == 1)
	{
		std::cout << "I'll take them off your hands for " << rovingTraders.getPrices(3) << " each?\n";

		std::cout << "How many prisoners would you like to sell?\n";
		int captivesToSell = getInput(resources.getCapturedEnemies());
		resources.setCapturedEnemies(captivesToSell);
		resources.setGold(captivesToSell * rovingTraders.getPrices(3));
		std::cout << "You sold " << captivesToSell << " prisoners. You have " << resources.getGold() << " gold.\n";
		playerScore.setTrades(2);

		rovingTraders.setDaysSinceLastPurchase(0);
	}
	else
	{
		std::cout << "\nRight, I'll be going then.\n\n";
	}
}
void diplomacy()
{
	bool useDiplomacy = false;
	std::cout << "\nWould you like to attempt to send diplomats to convince enemies to leave the fight?\nYes - (1) No - (2)\n";
	if (getInput(2) == 1) 
	{
		useDiplomacy = true;
	}
	if (useDiplomacy == true)
	{
		float highestRoll = 0;
		float diplomacyRollArray[DIPLOMACY_ARRAY_SIZE]{};
		float currentDiplomacySkill = troops.getDiplomacySkill();
		std::cout << "\nYou select several of your soldiers to serve as diplomats and send them towards the enemy's encampment.\n";
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
		std::cout << "\nDiplomacy roll: " << highestRoll << "/52\n";
		if (highestRoll < 50 && highestRoll < 52)
		{
			std::cout << "\nYour diplomats return with a nervous look in their eyes.\nAlthough their attempt was unsuccessful they have improved their diplomacy skills.\n";
			troops.setDiplomacySkill(0.25);
		}
		else if (highestRoll >= 52 && highestRoll < 80)
		{
			int currentEnemyArmySize = enemyArmy.getArmySize();
			int enemiesLeaving = int(currentDiplomacySkill);
			std::cout << "\nYour diplomats walk back with their heads held high. They convinced " << enemiesLeaving << " " << pluralWord("enemy", enemiesLeaving) << " to leave the fight!\n";
			troops.setDiplomacySkill(1.25);
			// Remove enemies from the enemy army
			enemyArmy.setArmySize(currentEnemyArmySize - enemiesLeaving);
			enemyArmy.rollDirection();
		}
		else if (highestRoll > 80 && highestRoll < 110)
		{
			int currentPlayerArmySize = army.getArmySize();
			int currentEnemyArmySize = enemyArmy.getArmySize();
			int enemiesJoining = int(currentDiplomacySkill);
			std::cout << "\nYour diplomats must be kiniving creature as they have convinced " << enemiesJoining << " " << pluralWord("enemy", enemiesJoining) << " to fight alongside your soldiers!\n";
			troops.setDiplomacySkill(3);
			// Remove enemies joining from enemy army and add to player's army
			enemyArmy.setArmySize(currentEnemyArmySize - enemiesJoining);
			army.setArmySize(currentPlayerArmySize + enemiesJoining);
			enemyArmy.rollDirection();
		}
		else if (highestRoll > 110)
		{
			std::cout << "\nYour diplomats return, bustling with excitement.\n";
			troops.setDiplomacySkill(5);
			// One element of the enemy army retreats
			whichElementLeft();
		}
	}
	enemyArmy.whereAreTheEnemies();
}
void combatArrayCheck(Army playerArmy, Army enemyArmy)
{
	int archers = army.getArcherAmount();
	int meleeModifier = troops.getMelee();
	int defenseModifier = troops.getArmour();
	int totalKills = 0;
	int totalEnemyKills = 0;
	std::cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
	for (int i = 0; i <= ARRAY_LOOP_CONST; i++)
	{
		int playerElement = army.getSoldiersAtLocation(i);
		int enemyElement = enemyArmy.getSoldiersAtLocation(i);
		std::string direction = army.getDirection(i);
		int tempPlayerKills = 0;
		int tempEnemyKills = 0;
		int tempPrisoners = 0;
		if (enemyElement > 0)
		{
			int playerArmySize = army.getArmySize();
			if (battleWin(playerElement, enemyElement))
			{
				int gold = generateLoot(playerScore);
				tempPlayerKills += std::min(rand() % returnModifiedCombatPower(playerElement, meleeModifier, archers), enemyElement);
				totalKills += tempPlayerKills;
				tempPrisoners += returnNumberOfPrisoners(enemyElement);
				resources.setCapturedEnemies(-tempPrisoners);
				std::cout << "\nYour army routes the enemy forces attacking the " << direction << "! Your soldiers killed " << tempPlayerKills << " " << pluralWord("enemy", tempPlayerKills) << ",\ntook " << tempPrisoners << " prisoner, and looted " << gold << " gold from the battlefield.\n";
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
				std::cout << "\nYour "<<direction<<" wall was breached! You lost " << tempEnemyKills << " good " << pluralWord("soldier", tempEnemyKills) << ".\n";
			}
			else
			{
				tempEnemyKills += rand() % returnModifiedLoss(playerElement, defenseModifier, playerArmySize) + 1;
				totalEnemyKills += tempEnemyKills;
				army.setArmySize(playerArmySize - tempEnemyKills);
				if (enemyElement > (playerElement * 2))
				{
					std::cout << "\nYour forces were completely overwhelmed in the "<<direction<<". " << tempEnemyKills << " perished in the defense.\n";
				}
				else
				{
					std::cout << "\nYour army was routed by the enemy. You lost " << tempEnemyKills << " good " <<pluralWord("soldier", tempEnemyKills) << ".\n";
				}
			}
		}
	}
	std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
	playerScore.setKills(totalKills);
	playerScore.setAllyDeaths(totalEnemyKills);
	std::cout << "\nAfter the battle you find that your soldiers have taken down " << totalKills << " enemies. This came at a cost of " << totalEnemyKills << " of your own soldiers.\n\n";
	isTheKingAlive();
	store();
}
void combatScoreUpdate(int newKills, int newAllyDeaths)
{
	playerScore.setKills(newKills);
	playerScore.setAllyDeaths(newAllyDeaths);
	std::cout << "\nScore updated!\n " << playerScore.getKills() << " kills, " << playerScore.getAllyDeaths() << " ally deaths!\n\n";
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
		std::cout << "The Northern enemy element of " << enemyArmy.getSoldiersAtLocation(0) << " " <<pluralWord("soldier", enemyArmy.getSoldiersAtLocation(0)) << " is deserting!\n";
		enemyArmy.setSoldiersAtLocation(0, 0);
	}
	else if (deserting == 1 && enemyArmy.getSoldiersAtLocation(1) > 0)
	{
		std::cout << "The Eastern enemy element of " << enemyArmy.getSoldiersAtLocation(1) << " " << pluralWord("soldier", enemyArmy.getSoldiersAtLocation(1)) << " is deserting!\n";
		enemyArmy.setSoldiersAtLocation(0, 1);
	}
	else if (deserting == 2 && enemyArmy.getSoldiersAtLocation(2) > 0)
	{
		std::cout << "The Southern enemy element of " << enemyArmy.getSoldiersAtLocation(2) << " " << pluralWord("soldier", enemyArmy.getSoldiersAtLocation(2)) << " is deserting!\n";
		enemyArmy.setSoldiersAtLocation(0, 2);
	}
	else if (deserting == 3 && enemyArmy.getSoldiersAtLocation(3) > 0)
	{
		std::cout << "The Western enemy element of " << enemyArmy.getSoldiersAtLocation(3) << " " << pluralWord("soldier", enemyArmy.getSoldiersAtLocation(3)) << " is deserting!\n";
		enemyArmy.setSoldiersAtLocation(0, 3);
	}
	else
	{
		whichElementLeft();
	}
}
int returnModifiedCombatPower(int numberOfTroops, int meleeSkill, int archers)
{
	return numberOfTroops + meleeSkill + archers;
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
		// Player wins
		return true;
	}
	else
	{
		// Player loses
		return false;
	}
}
int generateLoot(ScoreKeeper playerScore)
{
	int generated = rand() % 50 + 1;
	return generated + (generated * playerScore.getDifficultyModifier());
}
std::string pluralWord(std::string pluralCheck, int numberOfEnemies)
{
	if (pluralCheck == "enemy")
	{
		if (numberOfEnemies > 1)
		{
			return "enemies";
		}
		else if (numberOfEnemies == 1)
		{
			return "enemy";
		}
		else if (numberOfEnemies == 0)
		{
			return "enemies";
		}
	}
	else if(pluralCheck == "soldier")
	{
		if (numberOfEnemies > 1)
		{
			return "soldiers";
		}
		else if (numberOfEnemies == 1)
		{
			return "soldier";
		}
		else if (numberOfEnemies == 0)
		{
			return "soldiers";
		}
	}
}
void setDifficultyLevel()
{
	std::cout << "What difficulty level would you like to play on?\nYou may choose the following difficulty levels:\nEasy - (1) Medium - (2) Hard - (3)\n";
	int difficultyLevel = getInput(3);
	playerScore.setDifficultyModifier(difficultyLevel-1);
	enemyArmy.alignDifficultyLevel(difficultyLevel);
	switch (difficultyLevel)
	{
		case 1:
			std::cout << "You have selected Easy. Less enemies will attack at a time.\n\n";
			break;
		case 2:
			std::cout << "You have selected Medium. The game will play normally.\n\n";
			break;
		case 3:
			std::cout << "You have selected Hard. Good luck.\n\n";
			break;
	}
}
