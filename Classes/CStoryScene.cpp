#include "CStoryScene.h"
#include "CTeachScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* CStoryScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CStoryScene::create();
    scene->addChild(layer);
    return scene;
}

bool CStoryScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size size;
    
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/Fraction_Btn.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/scene101.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/teach_ui.plist");
    auto rootNode = CSLoader::createNode("storyscene.csb");
    addChild(rootNode);
    
    Point pt;
    float scale;
    // 設定按鈕
    char spriteName[30], normalName[30], touchedName[30];
    for (int i = 0; i < MAX_UNITS; i++)
    {
        sprintf(spriteName, "levelbtn_%d", i + 1);
        auto spt = (Sprite*)rootNode->getChildByName(spriteName);
        sprintf(normalName, "Ch_%02d.png", i + 1);
        sprintf(touchedName, "Ch_%02d-click.png", i + 1);
        pt = spt->getPosition();
        scale = spt->getScale();
        _unitBtn[i] = new CButton();
        _unitBtn[i]->setButtonInfo(normalName, touchedName, *this, pt, 1);
        _unitBtn[i]->setScale(scale);
        _unitBtn[i]->setEnabled(false);
        rootNode->removeChildByName(spriteName);
    }
    _unitBtn[0]->setEnabled(true);
    _unitBtn[1]->setEnabled(true);
    _unitBtn[2]->setEnabled(true);
    _unitIdx = 0;    // 設定成切換的單元，1 到 5
    
    pt = rootNode->getChildByName("gobtn")->getPosition();
    scale = rootNode->getChildByName("gobtn")->getScale();
    _goBtn.setButtonInfo("next_R.png", "next_R_click.png", *this, pt, 3);
    _goBtn.setScale(scale);
    _goBtn.setVisible(false);
    rootNode->removeChildByName("gobtn");
    
    _listener1 = EventListenerTouchOneByOne::create();    //創建一個一對一的事件聆聽器
    _listener1->onTouchBegan = CC_CALLBACK_2(CStoryScene::onTouchBegan, this);        //加入觸碰開始事件
    _listener1->onTouchMoved = CC_CALLBACK_2(CStoryScene::onTouchMoved, this);        //加入觸碰移動事件
    _listener1->onTouchEnded = CC_CALLBACK_2(CStoryScene::onTouchEnded, this);        //加入觸碰離開事件
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);    //加入剛創建的事件聆聽器
    this->schedule(CC_SCHEDULE_SELECTOR(CStoryScene::doStep));
    
    return true;
}

void CStoryScene::doStep(float dt)  // OnFrameMove
{
    if (goBtnPressed) {
        this->unscheduleAllCallbacks();
        Director::getInstance()->runWithScene(CTeachScene::createScene(_unitIdx));
    }
    
}

bool  CStoryScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
    Point touchLoc = pTouch->getLocation();
    for (int i = 0; i < MAX_UNITS; i++)
    {
        _unitBtn[i]->touchesBegin(touchLoc);
    }
    _goBtn.touchesBegin(touchLoc);
    return true;
}

void  CStoryScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
    Point touchLoc = pTouch->getLocation();
    for (int i = 0; i < MAX_UNITS; i++)
    {
        _unitBtn[i]->touchesMoved(touchLoc);
    }
    _goBtn.touchesMoved(touchLoc);
}

void  CStoryScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件
{
    Point touchLoc = pTouch->getLocation();
    for (int i = 0; i < MAX_UNITS; i++)
    {
        if (_unitBtn[i]->touchesEnded(touchLoc)) {
            _unitIdx = i + 1;
            ShowUnitStory();
            _goBtn.setVisible(true);
            return;
        }
    }
    if (_goBtn.touchesEnded(touchLoc)) goBtnPressed = true;
}

void CStoryScene::ShowUnitStory() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    char spriteName[30];
    sprintf(spriteName, "story_%d.jpg", _unitIdx);
    _story = Sprite::create("img/story_1.jpg");
    _story->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 2)); // 設定位置
    _story->setScale(2.2f);
    this->addChild(_story, 2);  // 加入目前的 Layer 中 1: Z 軸的層次，越大代表在越上層
}

CStoryScene::~CStoryScene()
{
    this->removeAllChildren();
    for (int i = 0; i < MAX_UNITS; i++)delete _unitBtn[i];
    
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/scene101.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/teach_ui.plist");
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

