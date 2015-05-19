#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet(void):	vy(15.5f),
						offsetY(0)
{
}


Bullet::~Bullet(void)
{
	log("delete bullet..");
}

Bullet* Bullet::create()
{
	  Bullet* mBullet	=	new Bullet();
	  if(mBullet && mBullet->init())
	  {
		    //�����Զ��������ճ�
			mBullet->autorelease();
			return mBullet;
	  }
	  delete mBullet;
	  mBullet		=	NULL;
	  return NULL;
}

Bullet* Bullet::create(std::string fileName)
{
	Bullet* mBullet	=	new Bullet();
	if(mBullet && mBullet->initWithSpriteFrameName(fileName))
	{
		mBullet->autorelease();
		return mBullet;
	}

	delete mBullet;
	mBullet		=	NULL;

	return NULL;
}

Bullet* Bullet::create(BULLET_TYPE type)
{
	Bullet* mBullet	 =	new Bullet();
	
	char chFileName[266];
	sprintf(chFileName,"bullet%d.png",type);

	if(mBullet&& mBullet->initWithSpriteFrameName(chFileName))
	{
		 mBullet->autorelease();
		 return mBullet;
	}
	delete mBullet;
	mBullet	=	NULL;
	return NULL;
}

bool Bullet::init()
{
	Sprite::init();

	initWithSpriteFrameName("bullet1.png");

	return true;
}

void Bullet::move()
{
	Size winSize	=	 Director::getInstance()->getVisibleSize();

	//���ƫ�����Ǹ��� �ͺ���
	offsetY	=	offsetY >= 0 ? offsetY : 0;
	float y	=	this->getPositionY() + vy;
	this->setPositionY(y + offsetY);
	if(y + offsetY > winSize.height)
	{
		if(this->getParent())
			this->removeFromParent();
	}
	
}
