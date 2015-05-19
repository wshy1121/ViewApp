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

	/*��Ϸ��ѭ��*/
	void gameStep(float dt);

private:

	void createEnemy(float dt);
	void moveAllEnemy();
	void enemyHitBullet();
	void enemyHitFly();

	/*�����ı���ͼ*/
	void updateView();

private:

	/*������*/
	Background* mBackground;

	/*��ҷɻ�*/
	PlayerFly* mFly;

	/*�л�����*/
	cocos2d::Vector<EnemyFly*> enemyList;

	/*����ʾ�����С*/
	cocos2d::Size winSize;

	/*�ͼƷ��ı� ��ǰ����: 1200��*/
	cocos2d::Label* ttfScores;

};

#endif	//_IN_GAME_LAYER_H_

