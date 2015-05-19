#include "InVerifyLayer.h"
#include "InTraceLayer.h"
#include "WelcomeLayer.h"
#include "ListViewLayer.h"
#include "net_client.h"

using namespace cocos2d;
using namespace ui;
using namespace cocostudio;

InVerifyLayer::InVerifyLayer(void):m_inVerify(NULL)
{
}


InVerifyLayer::~InVerifyLayer(void)
{
}

 Scene* InVerifyLayer::createScene()
 {
	 Scene* sc			=	Scene::create();
	 InVerifyLayer* ly	=	InVerifyLayer::create();
	 sc->addChild(ly);

	 return sc;
 }

bool InVerifyLayer::init()
{
	Layer::init();

	initCocosStudio();
	return true;
}

void InVerifyLayer::initCocosStudio()
{
	Widget *logView = GUIReader::getInstance()->widgetFromJsonFile("LogView.ExportJson");
	this->addChild(logView);
	m_inVerify = dynamic_cast<Layout*>(logView->getChildByName("InVerify"));
	m_inVerify->setVisible(true);
	
	auto* buttonBack = dynamic_cast<Button*>(m_inVerify->getChildByName("ButtonBack"));
	buttonBack->addTouchEventListener(CC_CALLBACK_2(InVerifyLayer::buttonBackEvent, this));

	auto* buttonStart = dynamic_cast<Button*>(m_inVerify->getChildByName("ButtonStart"));
	buttonStart->addTouchEventListener(CC_CALLBACK_2(InVerifyLayer::buttonStartEvent, this));

	auto* getAccessRep = dynamic_cast<Button*>(m_inVerify->getChildByName("GetAccessRep"));
	getAccessRep->addTouchEventListener(CC_CALLBACK_2(InVerifyLayer::getAccessRepEvent, this));

	char access[32];
	int accessLen = sizeof(access);
	CNetClient::instance()->createAccess(access, accessLen);
	const std::string sTextAccess = access;
	
	auto* textAccess = dynamic_cast<Text*>(m_inVerify->getChildByName("TextAccess"));
	textAccess->setString(sTextAccess);
}


void InVerifyLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();	
}


void InVerifyLayer::buttonBackEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;            
        case Widget::TouchEventType::ENDED:
			dealBack();
            break;    
        case Widget::TouchEventType::CANCELED:
            break;
        default:
            break;
    }
}

void InVerifyLayer::buttonStartEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;            
        case Widget::TouchEventType::ENDED:
			startTrace();
            break;    
        case Widget::TouchEventType::CANCELED:
            break;
        default:
            break;
    }
}

void InVerifyLayer::getAccessRepEvent(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
        case Widget::TouchEventType::BEGAN:
            break;
        case Widget::TouchEventType::MOVED:
            break;            
        case Widget::TouchEventType::ENDED:
			getAccessRep();
            break;    
        case Widget::TouchEventType::CANCELED:
            break;
        default:
            break;
    }
}

void InVerifyLayer::dealBack()
{
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5f,WelcomeLayer::createScene(),true));
}

void InVerifyLayer::startTrace()
{
	std::string sTextAccess;
	auto* textAccess = dynamic_cast<Text*>(m_inVerify->getChildByName("TextAccess"));
	sTextAccess = textAccess->getString();

	auto* textAccessRep = dynamic_cast<TextField*>(m_inVerify->getChildByName("TextAccessRep"));
	std::string sTextAccessRep = textAccessRep->getStringValue();

	char *access = (char *)sTextAccess.c_str();
	int accessLen = sTextAccess.size();
	char *accessRep = (char *)sTextAccessRep.c_str();
	
	bool bRet = CNetClient::instance()->verifyAccess(access, accessLen, accessRep);
	if (bRet)
	{
		Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5f,ListViewLayer::createScene(),true));

	}
	return ;
}


void InVerifyLayer::getAccessRep()
{
	std::string sTextAccess;
	auto* textAccess = dynamic_cast<Text*>(m_inVerify->getChildByName("TextAccess"));
	sTextAccess = textAccess->getString();

	char *access = (char *)sTextAccess.c_str();
	int accessLen = sTextAccess.size();
	char accessRep[32];
	CNetClient::instance()->getAccessRep(access, accessLen, accessRep);

	std::string sTextAccessRep = accessRep;
	auto* textAccessRep = dynamic_cast<TextField*>(m_inVerify->getChildByName("TextAccessRep"));
	textAccessRep->setText(sTextAccessRep);
}

