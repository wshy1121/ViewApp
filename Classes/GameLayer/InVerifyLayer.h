#ifndef _IN_VERIFY_LAYER_H_
#define _IN_VERIFY_LAYER_H_

#include "cocos2d.h"
#include "cocos/editor-support/cocostudio/CocoStudio.h"
#include "cocos/ui/CocosGUI.h"
#include "../GameObject/Background.h"
#include "../GameObject/PlayerFly.h"
#include "../GameObject/EnemyFly.h"

class InVerifyLayer  : public cocos2d::Layer
{
public:
	InVerifyLayer(void);
	~InVerifyLayer(void);
public:
	virtual bool init();
	virtual void onEnterTransitionDidFinish();

	CREATE_FUNC(InVerifyLayer);
public:
	static cocos2d::Scene* createScene();
private:
	void initCocosStudio();
private:
	void buttonBackEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);	
	void buttonStartEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void getAccessRepEvent(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
	void dealBack();
	void startTrace();
	void getAccessRep();
private:	
	cocos2d::ui::Layout *m_inVerify;
};

#endif	//_IN_GAME_LAYER_H_

