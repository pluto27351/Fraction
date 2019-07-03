#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Common/CButton.h"

#define MAX_UNITS 5

class CMenuScene : public cocos2d::Layer
{
	CButton *_unitBtn[MAX_UNITS];
	CButton _goBtn;
    CButton _storyBtn;
	Sprite *_story;

	int		_unitIdx;
	bool goBtnPressed = false;
    bool storyPressed = false;
    
	void ShowUnitStory();

public:
	static cocos2d::Scene* createScene();

	~CMenuScene();
    void onExit();
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
