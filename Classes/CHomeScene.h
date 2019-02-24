#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Common/CButton.h"

USING_NS_CC;

using namespace cocostudio::timeline;


class CHomeScene : public cocos2d::Layer
{
	float _fTotalTime;
	bool   _bToMenuScene;

	CButton _startBtn,_Boo;
	Node *_BooAct;
	ActionTimeline *_BooActTime;

public:
	static cocos2d::Scene* createScene();

	~CHomeScene();

	virtual bool init();
	void doStep(float dt);

	//觸碰
	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件 

	// implement the "static create()" method manually
	CREATE_FUNC(CHomeScene);
};
