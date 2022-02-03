#ifndef SCORE_KEEPER_H
#define SCORE_KEEPER_H

class ScoreKeeper
{
public:
	int getScore() const;
	void setScore();
	int getKingArms() const;
	void setKingArms();
	int getKills() const;
	void setKills(int killsAdded);
	int getTrades() const;
	void setTrades(int tradePoints);
	int getDiplomacy() const;
	void setDiplomacy(int diplomacyPoints);
	int getAllyDeaths() const;
	void setAllyDeaths(int deaths);
	void setDifficultyModifier(int newDifficulty);
	int getDifficultyModifier();


private:
	const double KILL_MULTIPLIER = 1.5;
	const int TRADE_MULTIPLIER = 2;
	const int DIPLOMACY_MULTIPLIER = 3;
	//0 = easy, 1 = normal, 2 = hard
	int difficultyModifier = 0;
	int currentScore = 0;
	int kingArms = 2;
	int kills = 0;
	int allyDeaths = 0;
	int trades = 0;
	int diplomacy = 0;
};



#endif // !SCORE_KEEPER_H

