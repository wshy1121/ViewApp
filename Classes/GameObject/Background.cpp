#include "Background.h"


USING_NS_CC;

Background::Background(void) :	vy(0),
								height(0),
								backgroundTop(NULL),
								backgroundBottom(NULL),
								winSize(0,0)
{
}


Background::~Background(void)
{
}

bool Background::init()
{
	 Layer::init();


	 backgroundTop		=	Sprite::createWithSpriteFrameName("background_2.png");
	 this->addChild(backgroundTop);
	 backgroundTop->setAnchorPoint(Point::ZERO);
	 backgroundTop->setPosition(0,0);

	 height				=	backgroundTop->getContentSize().height;
	 vy					=	5.5f;
	 winSize			=	Director::getInstance()->getVisibleSize();

	 backgroundBottom	=	Sprite::createWithSpriteFrameName("background_2.png");
	 this->addChild(backgroundBottom);
	 backgroundBottom->setAnchorPoint(Point::ZERO);
	 backgroundBottom->setPositionY(backgroundTop->getPositionY() + height - 1);

	 return true;
}


void Background::move()
{
	float topY		=	backgroundTop->getPositionY() - vy;
	float bottomY	=	backgroundBottom->getPositionY() - vy;	
	backgroundTop->setPositionY(topY);
	backgroundBottom->setPositionY(bottomY);

	if(topY <= -height)
		backgroundTop->setPositionY(bottomY + height - 1);
	else if(bottomY <= -height)
		backgroundBottom->setPositionY(topY + height - 1);
}
