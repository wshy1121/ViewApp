#include "PlayerFly.h"

USING_NS_CC;


PlayerFly::PlayerFly(void) :	winSize(),
								curTouchPos(),
								LIMIT_SPEED(25)	,
								isTouchFly(false),
								bulletList(),
								bulletDelay(0)
{
}


PlayerFly::~PlayerFly(void)
{
}


bool PlayerFly::init()
{
	Sprite::init();

	winSize	=	Director::getInstance()->getVisibleSize();

	initWithSpriteFrameName("hero_fly_1.png");

	this->setPosition(winSize.width / 2, 150);

	curTouchPos	=	Point(winSize.width / 2,150);

	addEvents();

	this->setZOrder(2);
	return true;
}

void PlayerFly::addEvents()
{
	EventListenerTouchOneByOne* evtTouch	=	EventListenerTouchOneByOne::create();
	evtTouch->onTouchBegan					=	CC_CALLBACK_2(PlayerFly::onTouchBegan,this);
	evtTouch->onTouchMoved					=	CC_CALLBACK_2(PlayerFly::onTouchMoved,this);
	evtTouch->onTouchEnded					=	CC_CALLBACK_2(PlayerFly::onTouchEnded,this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(evtTouch,this);
}

bool PlayerFly::onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* evt)
{
	curTouchPos		=	touch->getLocation();
	if(getDistance() <= 50)
		isTouchFly	=	true;
	return true;
}
void PlayerFly::onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* evt)
{
	   curTouchPos	=	touch->getLocation();
}

void PlayerFly::onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* evt)
{
	  isTouchFly	=	false;
}

void PlayerFly::move()
{
	if(isTouchFly == false)
		return;

	float vx		= (curTouchPos.x - this->getPositionX()) / 3;
	float vy		= (curTouchPos.y - this->getPositionY()) / 3;

	if(vx > LIMIT_SPEED)
		vx			=	LIMIT_SPEED;
	else if(vx < -LIMIT_SPEED)
		vx			=	-LIMIT_SPEED;

	if(vy > LIMIT_SPEED)
		vy			=	LIMIT_SPEED;
	else if(vy < -LIMIT_SPEED)
		vy			=	-LIMIT_SPEED;

	this->setPositionX(this->getPositionX() + vx);
	this->setPositionY(this->getPositionY() + vy);

	setBulletOffset(vy);
}

float PlayerFly::getDistance()
{
	float dx	=	this->getPositionX() - curTouchPos.x;
	float dy	=	this->getPositionY() - curTouchPos.y;
	return sqrt(dx * dx + dy * dy);
}

void PlayerFly::destory()
{
	/*有事件注册 就有事件移除*/
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
	this->removeFromParent();
}

void PlayerFly::fire()
{
	if(bulletDelay < 3)
	{
		bulletDelay++;
		return;
	}

	bulletDelay		=	0;

	Node* parent	=	this->getParent();
	Bullet* mBullet	=	Bullet::create("bullet1.png");
	if(parent)
	{
		//获取飞机在容器中的深度
		int zOrder	=	this->getZOrder();
		parent->addChild(mBullet,zOrder - 1);
		mBullet->setPositionX(this->getPositionX() + CCRANDOM_0_1() * 2 - 1);
		mBullet->setPositionY(this->getPositionY());
		mBullet->setRotation(CCRANDOM_0_1() * 10 - 5);
		bulletList.pushBack(mBullet);
	}
	
}

void PlayerFly::moveAllBullet()
{
	 Bullet* mBullet		=	NULL;
	 for (int i = bulletList.size() - 1; i >= 0; i--)
	 {
			mBullet			=	bulletList.at(i);
			mBullet->move();
			if(mBullet->getPositionY() > winSize.height)
				bulletList.eraseObject(mBullet);
	 }
}

/*设置所有的子弹的偏移量*/
void PlayerFly::setBulletOffset(float offset)
{
	 for(Bullet* mBullet : bulletList)
	 {
		mBullet->offsetY	=	offset;
	 }
}


