#pragma once

#include "cocos2d.h"
#include "Common/Object/CButton.h"

#define MAX_UNITS 5

class CMenuScene : public cocos2d::Layer
{
	CButton *_unitBtn[MAX_UNITS];
	int		_unitIdx;

public:
	static cocos2d::Scene* createScene();

	~CMenuScene();

    virtual bool init();
	void doStep(float dt);

	//觸碰
	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件 

    // implement the "static create()" method manually
    CREATE_FUNC(CMenuScene);
};
