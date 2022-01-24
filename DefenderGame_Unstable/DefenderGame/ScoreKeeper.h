#ifndef SCORE_KEEPER_H
#define SCORE_KEEPER_H

class ScoreKeeper
{
public:
	int getScore() const;
	void setScore(int score);
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


private:
	const double KILL_MULTIPLIER = 1.5;
	const int TRADE_MULTIPLIER = 2;
	const int DIPLOMACY_MULTIPLIER = 3;
	int currentScore;
	int kingArms = 2;
	int kills = 0;
	int allyDeaths = 0;
	int trades = 0;
	int diplomacy = 0;
};



#endif // !SCORE_KEEPER_H

