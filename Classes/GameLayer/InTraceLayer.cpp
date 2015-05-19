#include "InTraceLayer.h"
#include "ListViewLayer.h"
#include "WelcomeLayer.h"
#include "user_manager.h"
#include "net_client.h"
#include "VisibleRect.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace extension;

InTraceLayer::InTraceLayer(const char *fileName):m_nCurPage(1), m_pageNum(1), m_fileName(fileName)
{
}


InTraceLayer::~InTraceLayer(void)
{
}

Scene* InTraceLayer::createScene(const char *fileName)
{
	Scene* sc			=	Scene::create();
	InTraceLayer* ly	=	InTraceLayer::create(fileName);
	sc->addChild(ly);

	return sc;
}

InTraceLayer* InTraceLayer::create(const char *fileName)
{
    InTraceLayer *pRet = new InTraceLayer(fileName);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool InTraceLayer::init()
{	trace_worker();
	Layer::init();
	Layer *pLayer = Layer::create();
	pLayer->setContentSize(CCSizeMake(320*3, 568));
	
	initCocosStudio(pLayer);
	
	m_pScrollView = ScrollView::create(CCSizeMake(320,568), pLayer);
	m_pScrollView->setContentOffset(CCPointZero);
	m_pScrollView->setTouchEnabled(false);
	m_pScrollView->setDelegate(this);
	m_pScrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	this->addChild(m_pScrollView);
	
	updateTraceView(0);
	return true;
}

void InTraceLayer::initCocosStudio(Layer *pLayer)
{
	
	ui::Widget *logView = GUIReader::getInstance()->widgetFromJsonFile("LogView/LogView.ExportJson");
	pLayer->addChild(logView);
	m_inTraceLayout = dynamic_cast<ui::Layout*>(logView->getChildByName("InTrace"));
	m_inTraceLayout->setVisible(true);
	m_inTraceLayout->setTouchEnabled(false);

	auto* textFile = dynamic_cast<ui::Text*>(m_inTraceLayout->getChildByName("File"));
	textFile->setString("File");

	auto* textCandy = dynamic_cast<ui::Text*>(m_inTraceLayout->getChildByName("Candy"));
	textCandy->setString("Candy");

	auto* textTrace = dynamic_cast<ui::Text*>(m_inTraceLayout->getChildByName("Trace"));
	textTrace->setString("Trace");

	auto* textLastCandy = dynamic_cast<ui::Text*>(m_inTraceLayout->getChildByName("LastCandy"));
	textLastCandy->setString("LastCandy");

	auto* textTime = dynamic_cast<ui::Text*>(m_inTraceLayout->getChildByName("Time"));
	textTime->setString("Time");

	auto* buttonBack = dynamic_cast<ui::Button*>(m_inTraceLayout->getChildByName("ButtonBack"));
	buttonBack->addTouchEventListener(CC_CALLBACK_2(InTraceLayer::buttonBackEvent, this));

	
}

void InTraceLayer::addEvents()
{
	auto touchEvt = EventListenerTouchOneByOne::create();
	touchEvt->onTouchBegan = CC_CALLBACK_2(WelcomeLayer::onTouchBegan, this);
	touchEvt->onTouchMoved = CC_CALLBACK_2(WelcomeLayer::onTouchMoved, this);
	touchEvt->onTouchEnded = CC_CALLBACK_2(WelcomeLayer::onTouchEnded, this);
	touchEvt->onTouchCancelled = CC_CALLBACK_2(WelcomeLayer::onTouchCancelled, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvt, m_inTraceLayout);
}

void InTraceLayer::removeEvents()
{
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}

void InTraceLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	this->schedule(SEL_SCHEDULE(&InTraceLayer::updateTraceView), 1.0f);	
}

void InTraceLayer::onEnter()
{	trace_worker();
	Layer::onEnter();
	addEvents();
}

void InTraceLayer::onExit()
{	trace_worker();
	removeEvents();
	Layer::onExit();
	SpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}


void InTraceLayer::scrollViewDidScroll(ScrollView *view)
{	trace_worker();
}

void InTraceLayer::scrollViewDidZoom(ScrollView *view)
{	trace_worker();
}


bool InTraceLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{	trace_worker();
	m_touchPoint = Director::sharedDirector()->convertToGL(touch->getLocationInView());
	return true;
}

void InTraceLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
}

void InTraceLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{	trace_worker();
	Point endPoint = Director::sharedDirector()->convertToGL(touch->getLocationInView());
	float distance = endPoint.x - m_touchPoint.x;
	if(fabs(distance) > 50)
	{
		adjustScrollView(distance);
	}

}
void InTraceLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{	trace_worker();
	Point endPoint = Director::sharedDirector()->convertToGL(touch->getLocationInView());
	float distance = endPoint.x - m_touchPoint.x;
	if(fabs(distance) > 50)
	{
		adjustScrollView(distance);
	}
}



void InTraceLayer::adjustScrollView(float offset)
{	trace_worker();
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	Point origin = Director::sharedDirector()->getVisibleOrigin();
	if (offset<0)
	{	trace_printf("NULL");
		m_nCurPage ++;
	}else
	{	trace_printf("NULL");
		m_nCurPage --;
	}

	if (m_nCurPage <1)
	{	trace_printf("NULL");
		m_nCurPage = 1;
		Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5f,ListViewLayer::createScene(),true));
		return ;
	}

	if(m_nCurPage > m_pageNum)
	{	trace_printf("NULL");
		m_nCurPage = m_pageNum;
	}

	trace_printf("NULL");
	Point  adjustPos = ccp(origin.x - visibleSize.width * (m_nCurPage-1), 0);
	m_pScrollView->setContentOffset(adjustPos, true);
	
}

void InTraceLayer::buttonBackEvent(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::MOVED:
            break;            
        case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5f,ListViewLayer::createScene(),true));
            break;    
        case ui::Widget::TouchEventType::CANCELED:
            break;
        default:
            break;
    }
}

void InTraceLayer::updateTraceView(float dt)
{	trace_worker();
	trace_printf("m_fileName.c_str()  %s", m_fileName.c_str());
	CNetClient::instance()->getTraceFileInf(m_fileName.c_str(), m_traceFileInf);

	char tmpchars[256];
	snprintf(tmpchars, sizeof(tmpchars), "%s  %d", m_traceFileInf.m_fileName.c_str(), m_traceFileInf.m_count);
	auto* textFileInf = dynamic_cast<ui::Text*>(m_inTraceLayout->getChildByName("FileInf"));
	textFileInf->setString(tmpchars);
	
	auto* textLastCandyInf = dynamic_cast<ui::Text*>(m_inTraceLayout->getChildByName("LastCandyInf"));
	textLastCandyInf->setString(m_traceFileInf.m_lastCandy);

	snprintf(tmpchars, sizeof(tmpchars), "%d", m_traceFileInf.m_candyCount);
	auto* textCandyInf = dynamic_cast<ui::Text*>(m_inTraceLayout->getChildByName("CandyInf"));
	textCandyInf->setString(tmpchars);

	snprintf(tmpchars, sizeof(tmpchars), "%d", m_traceFileInf.m_traceCount);
	auto* textTraceInf = dynamic_cast<ui::Text*>(m_inTraceLayout->getChildByName("TraceInf"));
	textTraceInf->setString(tmpchars);

}


