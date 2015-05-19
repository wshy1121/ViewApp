#include "InGameLayer.h"
#include "SimpleAudioEngine.h"
#include "../gameObject/Bullet.h"
#include "../GameData.h"

USING_NS_CC;
using namespace CocosDenshion;


InGameLayer::InGameLayer(void):	mBackground(NULL),
								mFly(NULL),
								enemyList(),
								winSize()
{
}


InGameLayer::~InGameLayer(void)
{
}

 Scene* InGameLayer::createScene()
 {
	 Scene* sc			=	Scene::create();
	 InGameLayer* ly	=	InGameLayer::create();
	 sc->addChild(ly);

	 return sc;
 }

bool InGameLayer::init()
{
	 Layer::init();

	 winSize		=	Director::getInstance()->getVisibleSize();

	 mBackground	=	Background::create();
	 this->addChild(mBackground);

	 mFly			=	PlayerFly::create();
	 this->addChild(mFly);

	 ttfScores		=	Label::create("Socre:0","WRYH",32);
	 this->addChild(ttfScores,1000);
	 ttfScores->setAnchorPoint(Point(0,0.5f));
	 ttfScores->setPosition(10,winSize.height - 30);


	 //GameData
	 return true;
}

/*游戏主循环*/
void InGameLayer::gameStep(float dt)
{
	 mBackground->move();
	 mFly->move();
	 mFly->fire();
	 mFly->moveAllBullet();
	 moveAllEnemy();
	 enemyHitBullet();
	 enemyHitFly();
}

void InGameLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/game_music.mp3",true);

	this->schedule(SEL_SCHEDULE(&InGameLayer::gameStep),0.02f);
	this->schedule(SEL_SCHEDULE(&InGameLayer::createEnemy),1.0f);
	
}

void InGameLayer::createEnemy(float dt)
{
	int enemyData[3][4]	=	{
								{1,1,4,0},	
								{2,2,7,1},
								{3,1,4,2}	
							};
	int index			=	CCRANDOM_0_1() * 3;
	EnemyFly* mEnemy	=	EnemyFly::create();
	this->addChild(mEnemy);
	mEnemy->setPosition(200,200);
	mEnemy->init(	enemyData[index][0],
		enemyData[index][1],
		enemyData[index][2],
		enemyData[index][3]);
	float x				=	 CCRANDOM_0_1() * (winSize.width  -	mEnemy->getContentSize().width) +
																mEnemy->getContentSize().width / 2;
	float y				=	winSize.height + mEnemy->getContentSize().height;
	mEnemy->setPosition(x,y);

	enemyList.pushBack(mEnemy);
	
}

void InGameLayer::moveAllEnemy()
{
	EnemyFly* mEnemy	=	NULL;
	for (int i = enemyList.size() - 1; i >= 0; i--)
	{
		 mEnemy			=	enemyList.at(i);
		 mEnemy->move();
 		 if(mEnemy->getPositionY() <= 300)
 			 enemyList.erase(i);
	}
}

void InGameLayer::enemyHitBullet()
{
	Vector<Bullet*>& mBulletList	=	mFly->bulletList;
	EnemyFly* mEnemy				=	NULL;
	Bullet* mBullet					=	NULL;
	for (int i = enemyList.size() - 1; i >= 0 ; i--)
	{
		mEnemy		=	enemyList.at(i);
		for (int k = mBulletList.size() - 1; k >= 0; k--)
		{
		   mBullet	=	mBulletList.at(k);
		   bool	res	=	mEnemy->hitTest(mBullet);
		   if(res)
		   {
			   
			   mEnemy->hurt(10.5f);
			   mBullet->removeFromParent();
			   //粒子效果
			   auto particle = ParticleSystemQuad::create("flash.plist");
			   this->addChild(particle);
			   particle->setPosition(mBullet->getPosition());

			   mBulletList.erase(k);

		
			   if(mEnemy->getIsDead())
			   {
				   enemyList.erase(i);

				   GameData::getInstance()->setScore(100);
				   char chScore[206];
				   sprintf(chScore,"Socre:%d",GameData::getInstance()->getScore());
				   ttfScores->setString(chScore);

				   updateView();
				   break;
			   }
		   }
		}
	}
}

void InGameLayer::enemyHitFly()
{
	EnemyFly* mEnenmy = NULL;
	for (int i = enemyList.size() - 1; i>=0; i--)
	{
		mEnenmy = enemyList.at(i);
		if (mFly->getBoundingBox().intersectsRect(mEnenmy->getBoundingBox()))
		{
			log("Game Over");
		}
	}
}

void InGameLayer::updateView()
{
	char chScores[32];
	sprintf(chScores,"Score:%d",GameData::getInstance()->getScore());
}

