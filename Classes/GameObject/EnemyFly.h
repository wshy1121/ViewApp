#ifndef _ENEMY_FLY_H_
#define _ENEMY_FLY_H_

#include "cocos2d.h"

enum ENEMY_ACTION
{
	ENEMY_HURT	=	1,
	ENEMY_FLY,
	ENEMY_BLOWUP
	
};

class EnemyFly : public cocos2d::Sprite
{
public:
	EnemyFly(void);
	~EnemyFly(void);

	virtual bool init();
	CREATE_FUNC(EnemyFly);

public:

	void init(int type,int fly,int blowup,int hit);

	void move();

	void explode();

	void hurt(float dmg);

	void destory();

	bool hitTest(Node* hitNode);

	bool getIsDead() const;

private:

	cocos2d::Animation* createAnimation(const std::string& head,const std::string& mid,int num);
	void playActionWithType(int actionType,bool loop = false,bool del = false);

private:

	/*移动速度*/
	float vy;

	/*生命*/
	float hp;

	/**/
	int typeNum;
	/**/
	int flyNum;
	/**/
	int blowupNum;
	/**/
	int hitNum;


};

#endif	//_ENEMY_FLY_H_


