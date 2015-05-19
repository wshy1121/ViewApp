#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "cocos2d.h"

class Background : public cocos2d::Layer
{
public:
	Background(void);
	~Background(void);

public:

	virtual bool init();
	CREATE_FUNC(Background);

public: 

	void move();

private:

	/*移动速度*/
	float vy;

	/*背景图高*/
	float height;

	/*替换背景*/
	cocos2d::Sprite* backgroundTop;
	cocos2d::Sprite* backgroundBottom;

	/*场景大小*/
	cocos2d::Size winSize;
};

#endif	//_BACKGROUND_H_


