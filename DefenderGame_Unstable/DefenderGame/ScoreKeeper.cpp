#include "ScoreKeeper.h"
#include <iostream>
using namespace std;

int ScoreKeeper::getScore() const
{
	return currentScore;
}
void ScoreKeeper::setScore(int score)
{
	currentScore = score;
}
int ScoreKeeper::getKingArms() const
{
	return kingArms;
}
void ScoreKeeper::setKingArms()
{
	kingArms++;
}
int ScoreKeeper::getKills() const
{
	return kills;
}
void ScoreKeeper::setKills(int killsAdded)
{
	kills += killsAdded;
}
int ScoreKeeper::getTrades() const
{
	return trades;
}
void ScoreKeeper::setTrades(int tradePoints)
{
	trades += tradePoints;
}
int ScoreKeeper::getDiplomacy() const
{
	return diplomacy;
}
void ScoreKeeper::setDiplomacy(int diplomacyPoints)
{
	diplomacy += diplomacyPoints;
}
int ScoreKeeper::getAllyDeaths() const
{
	return allyDeaths;
}
void ScoreKeeper::setAllyDeaths(int deaths)
{
	allyDeaths += deaths;
}