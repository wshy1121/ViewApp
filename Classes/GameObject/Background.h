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

	/*�ƶ��ٶ�*/
	float vy;

	/*����ͼ��*/
	float height;

	/*�滻����*/
	cocos2d::Sprite* backgroundTop;
	cocos2d::Sprite* backgroundBottom;

	/*������С*/
	cocos2d::Size winSize;
};

#endif	//_BACKGROUND_H_


