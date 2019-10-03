#define SCREEN_POS Vec2(1365.5,768)

#include "CStoryScene.h"
#include "CTeachScene.h"
#include "CMenuScene.h"

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
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/teach_scene.plist");
    auto rootNode = CSLoader::createNode("storyscene.csb");
    addChild(rootNode);
    
    Point pt;
    float scale;
    // 設定按鈕
    char spriteName[20],normalName[20],enableName[20];

    
    for (int i = 0; i < MAX_UNITS; i++)
    {
        sprintf(spriteName, "story_%d", i + 1);
        sprintf(normalName, "story_%d.png", i + 1);
        sprintf(enableName, "story_n%d.png", i + 1);
        auto spt = (Sprite*)rootNode->getChildByName(spriteName);
        pt = spt->getPosition();
        scale = spt->getScale();
        _unitBtn[i] = new CButton();
        _unitBtn[i]->setButtonInfo(normalName,normalName, enableName, *this, pt, 1);
        _unitBtn[i]->setScale(scale);
        rootNode->removeChildByName(spriteName);
        
        
        sprintf(spriteName, "STORY_%d", i + 1);
        if(CCUserDefault::sharedUserDefault()->getBoolForKey(spriteName)){
            _unitBtn[i]->setEnabled(true);
        }else {
            _unitBtn[i]->setEnabled(false);
        }
    }

    _unitIdx = 0;
    
    for(int i=0;i<4;i++){
        sprintf(spriteName, "char_%d", i + 1);
        _char[i] = (Sprite*)rootNode->getChildByName(spriteName);
        this->addChild(_char[i], 5-i);
        
        sprintf(spriteName, "char_b%d", i + 1);
        sprintf(normalName, "tab_%d.png", i + 1);
        auto btn = (Sprite*)rootNode->getChildByName(spriteName);
        pt = btn->getPosition();
        _charBtn[i] = new CButton();
        _charBtn[i]->setButtonInfo(normalName,normalName, *this, pt, 5-i);
        rootNode->removeChildByName(spriteName);
    }
    
    //menubtn
    pt = rootNode->getChildByName("home")->getPosition();
    scale = rootNode->getChildByName("home")->getScale();
    _menuBtn.setButtonInfo("ch_home.png", "ch_home_h.png", *this, pt, 1);
    _menuBtn.setScale(scale);
    rootNode->removeChildByName("home");
    
    auto top = (Sprite*)rootNode->getChildByName("char_top");
    this->addChild(top, 10);
    _topPic = 0;
    
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
        this->removeAllChildren();
        
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/teach_scene.plist");
        Director::getInstance()->getTextureCache()->removeUnusedTextures();
        Director::getInstance()->replaceScene(CTeachScene::createScene(_unitIdx));
    }else if(menuPressed){
        this->unscheduleAllCallbacks();
        this->removeAllChildren();
        
        SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/teach_scene.plist");
        Director::getInstance()->getTextureCache()->removeUnusedTextures();
        Director::getInstance()->replaceScene(CMenuScene::createScene());
    }
    
}

bool  CStoryScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
    if(_bstory)return true;
    
    Point touchLoc = pTouch->getLocation();
    for (int i = 0; i < MAX_UNITS; i++)
    {
        _unitBtn[i]->touchesBegin(touchLoc);
    }
    
    for(int i=0;i<4;i++){
        _charBtn[i]->touchesBegin(touchLoc);
    }
    
    _menuBtn.touchesBegin(touchLoc);
    
    return true;
}

void  CStoryScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
    if(_bstory)return;
    
    Point touchLoc = pTouch->getLocation();
    for (int i = 0; i < MAX_UNITS; i++)
    {
        _unitBtn[i]->touchesMoved(touchLoc);
    }
    for(int i=0;i<4;i++){
        _charBtn[i]->touchesMoved(touchLoc);
    }
    _menuBtn.touchesMoved(touchLoc);
}

void  CStoryScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件
{
    if(_bstory){
        _storyPic[_storyNum]->setVisible(false);
        _storyNum+=1;
        
        if(_storyNum == _maxstory) goBtnPressed = true;
        else _storyPic[_storyNum]->setVisible(true);
        return;
    }
    
    Point touchLoc = pTouch->getLocation();
    
    if(_menuBtn.touchesEnded(touchLoc)){
        menuPressed = true;
    }
    
    for (int i = 0; i < MAX_UNITS; i++)
    {
        if (_unitBtn[i]->touchesEnded(touchLoc)) {
            _unitIdx = i + 1;
            ShowUnitStory(_unitIdx);
            return;
        }
    }
    for(int i=0;i<4;i++){
        if(_charBtn[i]->touchesEnded(touchLoc)){
            _char[_topPic]->setZOrder(4);
            _charBtn[_topPic]->setZ(4);
            _topPic = i;
            _char[i]->setZOrder(5);
            _charBtn[i]->setZ(5);
        }
    }
}

void CStoryScene::ShowUnitStory(int i) {
    char spriteName[30];
    _maxstory = STORYDATA[i-1];
    for(int k=1; k<=_maxstory; k++){
        sprintf(spriteName, "img/story/story_%d_%d.png", i,k);
        auto sPic = (Sprite *)Sprite::create(spriteName);
        sPic->setPosition(SCREEN_POS);
        sPic->setVisible(false);
        this->addChild(sPic, 100);
        _storyPic.push_back(sPic);
    }
    _storyPic[0]->setVisible(true);
    _storyNum = 0;
    _bstory = true;
}

CStoryScene::~CStoryScene()
{
    for (int i = 0; i < MAX_UNITS; i++)delete _unitBtn[i];
    for( int i=0 ; i<4 ; i++)delete _charBtn[i];
    _storyPic.clear();

}

