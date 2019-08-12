#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Common/CButton.h"

#define MAX_UNITS 5

class CStoryScene : public cocos2d::Layer
{
    CButton *_unitBtn[MAX_UNITS],*_charBtn[4];
    Sprite *_char[4];
    int _topPic;
    std::vector<Sprite *>_storyPic;
    
    int  _unitIdx;
    bool goBtnPressed = false;
    
    bool _bstory;
    int _storyNum,_maxstory;
    
    void ShowUnitStory(int i);
    
public:
    static cocos2d::Scene* createScene();
    
    ~CStoryScene();
    
    virtual bool init();
    void doStep(float dt);
    
    //觸碰
    cocos2d::EventListenerTouchOneByOne *_listener1;
    bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
    void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
    void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件
    
    // implement the "static create()" method manually
    CREATE_FUNC(CStoryScene);
};

