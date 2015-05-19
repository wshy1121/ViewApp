#ifndef _WELCOME_LAYER_H_
#define _WELCOME_LAYER_H_  

#include "cocos2d.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"

class WelcomeLayer : public cocos2d::Layer
{
public:
	WelcomeLayer(void);
	~WelcomeLayer(void);

public:
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);

public:

	static cocos2d::Scene*	createScene();
private:
	void initResource();
	void initCocosStudio();
	void initLogManager();
	void initBackground();
	void logoAction();
	void menuCallBack(cocos2d::Ref* sender);
	void buttonLogInEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void dealLogin();
private:
	cocos2d::ui::Layout *m_welcomeWid;
	cocos2d::Sprite* logo;
};


#endif	//_WELCOME_LAYER_H_

