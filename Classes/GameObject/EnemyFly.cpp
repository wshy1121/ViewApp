#include "EnemyFly.h"

USING_NS_CC;
using namespace std;

EnemyFly::EnemyFly(void) :	vy(0),
							hp(0),
							typeNum(0),
							flyNum(0),
							blowupNum(0),
							hitNum(0)
{
}


EnemyFly::~EnemyFly(void)
{
	log("delete enemy");
}

bool EnemyFly::init()
{
	Sprite::init();

	return true;
}

void EnemyFly::init(int type,int fly,int blowup,int hit)
{
	 typeNum	=	type;
	 flyNum		=	fly;
	 blowupNum	=	blowup;
	 hitNum		=	hit;

	 char chFileName[266];
	 sprintf(chFileName,"enemy%d_fly_1.png",type);
	 initWithSpriteFrameName(chFileName);

	 if(type == 2)
	 {
		vy			=	CCRANDOM_0_1() * 2 + 2;
		hp			=	30;
	 }
	 else if(type == 3)
	 {
		vy			=	CCRANDOM_0_1() * 2 + 4;
		hp			=	10;
	 }
	 else if(type == 1)
	 {
		vy			=	CCRANDOM_0_1() * 2 + 6;
		hp			=	20;
	 }

	 playActionWithType(ENEMY_FLY,true);
	 
}


Animation* EnemyFly::createAnimation(const string& head,const std::string& mid,int num)
{
	Animation* getAnimation	=	AnimationCache::getInstance()->getAnimation(head + mid);
	if(getAnimation != NULL)
		return getAnimation;

	Vector<SpriteFrame*> actionList;
	SpriteFrame* frame			=	NULL;
	char chMid[20];
	for (int i = 1; i <= num; i++)
	{
		sprintf(chMid,mid.c_str(),i);
		frame					=	SpriteFrameCache::getInstance()->getSpriteFrameByName(head + chMid);
		actionList.pushBack(frame);
	}
	Animation* mAnimation		=	NULL;
	if(num > 0)
	{
		mAnimation	=	Animation::createWithSpriteFrames(actionList,0.2f);
		AnimationCache::getInstance()->addAnimation(mAnimation,head + mid);
	}
	
	return mAnimation;
}

void EnemyFly::move()
{
	float y		=	this->getPositionY() - vy;
	this->setPositionY(y);
	if(y <= 300)
		destory();
}

void EnemyFly::explode()
{
	 playActionWithType(ENEMY_BLOWUP,false,true);
}

void EnemyFly::hurt(float dmg)
{
	hp	-=	dmg;
	playActionWithType(ENEMY_HURT);
	if (hp <= 0)
	{
		this->stopAllActions();
		explode();
	}
}

bool EnemyFly::getIsDead() const
{
	return hp <= 0;
}

void  EnemyFly::playActionWithType(int actionType,bool loop,bool del)
{
	string strType	=	"";
	int actionNum	=	0;
	if(actionType == ENEMY_HURT)
	{
		strType		=	"_hit_%d.png";
		actionNum	=	hitNum;
	}
	else if(actionType == ENEMY_FLY)
	{
		strType		=	"_fly_%d.png";
		actionNum	=	flyNum;
	}
	else if(actionType == ENEMY_BLOWUP) 
	{
		strType		=	"_blowup_%d.png";
		actionNum	=	blowupNum;
	}

	char chHead[10];
	sprintf(chHead,"enemy%d",typeNum);
	string head(chHead);

	Animation* mAnimation	=	createAnimation(head,strType,actionNum);
	if(mAnimation)
	{
		Animate* mAnimate		=	Animate::create(mAnimation);
		RemoveSelf* self		=	RemoveSelf::create();
		Sequence* seq			=	Sequence::create(mAnimate,self,NULL);
		if(loop)
			this->runAction(RepeatForever::create(mAnimate));
		else if(loop == false && del)
			this->runAction(seq);
		else 
			this->runAction(mAnimate);
	}
}

void EnemyFly::destory()
{
   this->removeFromParent();
}

bool EnemyFly::hitTest(Node* hitNode)
{
	//getBoundingBox() 返回一个区域的描述
	//this->getBoundingBox().intersectsRect(hitNode->getBoundingBox());
	return this->getBoundingBox().containsPoint(hitNode->getPosition());
}
