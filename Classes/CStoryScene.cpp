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
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/teach_scene.plist");
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
        sprintf(normalName, "character_%d.png", i + 1);
        sprintf(touchedName, "character_%d_click.png", i + 1);
        pt = spt->getPosition();
        scale = spt->getScale();
        _unitBtn[i] = new CButton();
        _unitBtn[i]->setButtonInfo(normalName, touchedName, *this, pt, 1);
        _unitBtn[i]->setScale(scale);
        _unitBtn[i]->setEnabled(true);
        rootNode->removeChildByName(spriteName);
    }

    _unitIdx = 0;    // 設定成切換的單元，1 到 5
    
    
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
}

void  CStoryScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件
{
    if(_bstory){
        _story[_storyNum]->setVisible(false);
        _storyNum+=1;
        
        if(_storyNum == _maxstory) goBtnPressed = true;
        else _story[_storyNum]->setVisible(true);
        return;
    }
    
    Point touchLoc = pTouch->getLocation();
    for (int i = 0; i < MAX_UNITS; i++)
    {
        if (_unitBtn[i]->touchesEnded(touchLoc)) {
            _unitIdx = i + 1;
            ShowUnitStory(_unitIdx);
            return;
        }
    }
}

void CStoryScene::ShowUnitStory(int i) {
    char spriteName[10];
    auto story = CSLoader::createNode("ani/story.csb");
    sprintf(spriteName, "story_%d", i);
    auto storyPics = story->getChildByName(spriteName);
    _maxstory = storyPics->getTag();
    
    for(int k=0; k<_maxstory; k++){
        sprintf(spriteName, "%d", k);
        Node *storyPic = storyPics->getChildByName(spriteName);
        storyPic->setPosition(Vec2(1024,768));
        storyPic->setVisible(false);
        this->addChild(storyPic, 2);
        _story.push_back(storyPic);
    }
    _story[0]->setVisible(true);
    _storyNum = 0;
    _bstory = true;
}

CStoryScene::~CStoryScene()
{
    CCLOG("delete StoryScene");
    this->removeAllChildren();
    for (int i = 0; i < MAX_UNITS; i++)delete _unitBtn[i];

}

