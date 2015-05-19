#include "GameData.h"


GameData::GameData(void) : score(0)
{
}

GameData::~GameData(void)
{
}

GameData* GameData::instance	=	0;

GameData* GameData::getInstance()
{
	 if(0 == instance)
	 {
		instance	=	new GameData();
	 }
	 return instance;
}
void GameData::purgeInstance()
{
	 delete instance;
	 instance	=	0;
}

void GameData::setScore(const int& score)
{
	this->score	+=	score;
}

int GameData::getScore()const
{
   return score;
}
