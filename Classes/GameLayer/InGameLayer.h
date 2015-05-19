#ifndef _IN_GAME_LAYER_H_
#define _IN_GAME_LAYER_H_

#include "cocos2d.h"
#include "../GameObject/Background.h"
#include "../GameObject/PlayerFly.h"
#include "../GameObject/EnemyFly.h"

class InGameLayer  : public cocos2d::Layer
{
public:
	InGameLayer(void);
	~InGameLayer(void);

public:

	virtual bool init();

	virtual void onEnterTransitionDidFinish();


	CREATE_FUNC(InGameLayer);

public:

	static cocos2d::Scene* createScene();


private:

	/*游戏主循环*/
	void gameStep(float dt);

private:

	void createEnemy(float dt);
	void moveAllEnemy();
	void enemyHitBullet();
	void enemyHitFly();

	/*更新文本视图*/
	void updateView();

private:

	/*背景层*/
	Background* mBackground;

	/*玩家飞机*/
	PlayerFly* mFly;

	/*敌机数组*/
	cocos2d::Vector<EnemyFly*> enemyList;

	/*可显示区域大小*/
	cocos2d::Size winSize;

	/*就计分文本 当前分数: 1200分*/
	cocos2d::Label* ttfScores;

};

#endif	//_IN_GAME_LAYER_H_

