#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

class GameData
{
	GameData(void);
	GameData(const GameData& other);
	static GameData* instance;
public:
	~GameData(void);

public:

	static GameData* getInstance();
	static void purgeInstance();

public:

	void setScore(const int& score);
	int getScore()const;

private:
	
	/*记录游戏中的得分*/
	int score;
};

#endif	//_GAME_DATA_H_


