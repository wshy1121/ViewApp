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
	/*�������е��ӵ���ƫ����*/
	void setBulletOffset(float offset);

public:
	/*�ӵ�����*/
	cocos2d::Vector<Bullet*> bulletList;

private:

	/*������С*/
	cocos2d::Size winSize;

	/*��ǰ�����ĵ�*/
	cocos2d::Point curTouchPos;

	const int LIMIT_SPEED ;

	/*�Ƿ�㴥�ɻ�*/
	bool isTouchFly;

	/*�ӵ���������*/
	int bulletDelay;
	
};

#endif	//_PLAYER_FLY_H_


