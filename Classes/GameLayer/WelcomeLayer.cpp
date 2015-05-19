#include "WelcomeLayer.h"
#include "net_server.h"
#include "net_client.h"
#include "InGameLayer.h"
#include "InVerifyLayer.h"

using namespace cocos2d;
using namespace ui;
using namespace cocostudio;

WelcomeLayer::WelcomeLayer(void) : logo(NULL)
{
}


WelcomeLayer::~WelcomeLayer(void)
{
}

Scene*	WelcomeLayer::createScene()
{
	Scene* sc			=	Scene::create();
	WelcomeLayer* ly	=	WelcomeLayer::create();
	sc->addChild(ly);

	return sc;
}

bool WelcomeLayer::init()
{
	Layer::init();
	initResource();
	initLogManager();
	initCocosStudio();
	return true;
}
void WelcomeLayer::initResource()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameArts.plist");
}
void WelcomeLayer::initLogManager()
{
	CNetServer::instance()->startServer();
	trace_worker();
	return ;
}
void WelcomeLayer::initBackground()
{
	Size winSize	=	Director::getInstance()->getVisibleSize();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameArts.plist");
	
	logo					=	Sprite::create("BurstAircraftLogo.png");
	this->addChild(logo);
	logo->setPosition(winSize.width / 2,winSize.height - 100);

	Label* ttfStartGame	=	Label::createWithSystemFont("PLAY GMAE","WRYH",32); 
	MenuItemLabel* itemStart=	MenuItemLabel::create(ttfStartGame,CC_CALLBACK_1(WelcomeLayer::menuCallBack,this));

	Menu* startMenu			=	Menu::create(itemStart,NULL);
	this->addChild(startMenu);


	logoAction();
	return ;
}

void WelcomeLayer::initCocosStudio()
{
	Widget *logView = GUIReader::getInstance()->widgetFromJsonFile("LogView/LogView.ExportJson");
	this->addChild(logView);
	m_welcomeWid = dynamic_cast<Layout*>(logView->getChildByName("WelCome"));
	m_welcomeWid->setVisible(true);
	
	auto* buttonLogIn = dynamic_cast<Button*>(m_welcomeWid->getChildByName("ButtonLogIn"));
	buttonLogIn->addTouchEventListener(CC_CALLBACK_2(WelcomeLayer::buttonLogInEvent, this));
}	


void WelcomeLayer::buttonLogInEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;
            
        case Widget::TouchEventType::ENDED:
			dealLogin();
            break;    
        case Widget::TouchEventType::CANCELED:
            break;
            
        default:
            break;
    }
}




void WelcomeLayer::dealLogin()
{
	auto* textUserName = dynamic_cast<TextField*>(m_welcomeWid->getChildByName("TextUserName"));
	char *userName = (char *)textUserName->getStringValue().c_str();

	auto* textPassWord = dynamic_cast<TextField*>(m_welcomeWid->getChildByName("TextPassWord"));
	char *passWord = (char *)textPassWord->getStringValue().c_str();

	auto* textIp = dynamic_cast<TextField*>(m_welcomeWid->getChildByName("TextIp"));
	char *ip = (char *)textIp->getStringValue().c_str();
	
	bool bRet = CNetClient::instance()->connect(ip);
	if (bRet)
	{
		bRet = CNetClient::instance()->login(userName, passWord);
	}
	
	if (!bRet)
	{		
		Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5f,InGameLayer::createScene(),true));
	}
	else
	{
		Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5f,InVerifyLayer::createScene(),true));
	}
	return ;
}

void WelcomeLayer::logoAction()
{
	MoveBy* mMoveBy		=	MoveBy::create(1.0f,Point(0,-200));
	FadeIn* mFadeIn		=	FadeIn::create(2.0f);
	RotateTo* mRotateTo	=	RotateTo::create(3.0,180,36);
	logo->setOpacity(0);

	Spawn* mSpawn		=	Spawn::create(mFadeIn,mMoveBy,mRotateTo,NULL);//同时动画
	Sequence* seq		=	Sequence::create(mFadeIn,mMoveBy,mRotateTo,NULL);//连续动画
	logo->runAction(seq);
}

void WelcomeLayer::menuCallBack(cocos2d::Ref* sender)
{
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5f,InGameLayer::createScene(),true));
}

