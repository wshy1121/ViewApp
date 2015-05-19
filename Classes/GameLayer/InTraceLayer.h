#ifndef _IN_TRACE_LAYER_H_
#define _IN_TRACE_LAYER_H_
#include "cocos2d.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"
#include "cocos-ext.h"
#include "log_opr.h"

class InTraceLayer  : public cocos2d::Layer, public cocos2d::extension::ScrollViewDelegate
{
public:
	InTraceLayer(const char *fileName);
	~InTraceLayer(void);
public:
	virtual bool init();
	virtual void onEnterTransitionDidFinish();

	static InTraceLayer* create(const char *fileName);
public:
	static cocos2d::Scene* createScene(const char *fileName);
private:
	void initCocosStudio(cocos2d::Layer *pLayer);
	void addEvents();
	void removeEvents();
	virtual void onEnter();
	virtual void onExit();
	//scrollview滚动的时候会调用
	void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
	//scrollview缩放的时候会调用
	void scrollViewDidZoom(cocos2d::extension::ScrollView* view);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);	
	void adjustScrollView(float offset);
	void buttonBackEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void updateTraceView(float dt);
private:	
	cocos2d::extension::ScrollView *m_pScrollView;
	cocos2d::Point m_touchPoint;
	const int m_pageNum;
	int m_nCurPage;
	cocos2d::ui::Layout *m_inTraceLayout;
	std::string m_fileName;
	TraceFileInf m_traceFileInf;
};


#endif

