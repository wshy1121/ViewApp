#ifndef _PLAYER_FLY_H_
#define _PLAYER_FLY_H_

#include "cocos2d.h"
#include "Bullet.h"

class PlayerFly	: public cocos2d::Sprite
{
public:
	PlayerFly(void);
	~PlayerFly(void);

public:

	virtual bool init();
	virtual bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* evt);
	virtual void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* evt);
	virtual void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* evt);
	CREATE_FUNC(PlayerFly);

public:

	void destory();

	void move();

	void fire();

	void moveAllBullet();

private:

	float getDistance();
	void addEvents();
	/*设置所有的子弹的偏移量*/
	void setBulletOffset(float offset);

public:
	/*子弹数组*/
	cocos2d::Vector<Bullet*> bulletList;

private:

	/*场景大小*/
	cocos2d::Size winSize;

	/*当前触碰的点*/
	cocos2d::Point curTouchPos;

	const int LIMIT_SPEED ;

	/*是否点触飞机*/
	bool isTouchFly;

	/*子弹创建计数*/
	int bulletDelay;
	
};

#endif	//_PLAYER_FLY_H_


