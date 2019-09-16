#include "CHomeScene.h"
#include "CMenuScene.h"


Scene* CHomeScene::createScene()
{
	auto scene = Scene::create();

	auto layer = CHomeScene::create();

	scene->addChild(layer);

	return scene;
}


bool CHomeScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/teach_scene.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/teach_ui.plist");
    auto rootNode = CSLoader::createNode("homescene.csb");
    addChild(rootNode);
    
	auto _BtnLoc = rootNode->getChildByName("startBtn")->getPosition();
	_startBtn.setButtonInfo("main_start.png", "main_start_click.png", *this, _BtnLoc, 1);
	rootNode->removeChildByName("startBtn");

    _BtnLoc = rootNode->getChildByName("nut")->getPosition();
    _BooAct = CSLoader::createNode("ani/home_nut.csb");
    _BooAct->setPosition(_BtnLoc );
    _BooAct->setVisible(false);
    this->addChild(_BooAct,2);
    _BooActTime = (ActionTimeline *)CSLoader::createTimeline("ani/home_nut.csb");
    _BooAct->runAction(_BooActTime);
    rootNode->removeChildByName("nut");
    
	_listener1 = EventListenerTouchOneByOne::create();	//創建一個一對一的事件聆聽器
	_listener1->onTouchBegan = CC_CALLBACK_2(CHomeScene::onTouchBegan, this);		//加入觸碰開始事件
	_listener1->onTouchMoved = CC_CALLBACK_2(CHomeScene::onTouchMoved, this);		//加入觸碰移動事件
	_listener1->onTouchEnded = CC_CALLBACK_2(CHomeScene::onTouchEnded, this);		//加入觸碰離開事件

	_fTotalTime = 0; _bToMenuScene = false;
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器
	this->schedule(CC_SCHEDULE_SELECTOR(CHomeScene::doStep));


	return true;
}

void CHomeScene::doStep(float dt)  // OnFrameMove
{
	if (_bToMenuScene) {
		this->unscheduleAllCallbacks();
		auto scene = TransitionMoveInR::create(0.5f, CMenuScene::createScene());
        Director::getInstance()->replaceScene(scene);
	}
}

bool  CHomeScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
	if(_btouched == false)_startBtn.touchesBegin(touchLoc);
	return true;
}

void  CHomeScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();
	if(_btouched == false)_startBtn.touchesMoved(touchLoc);
}

void  CHomeScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();

    if (_startBtn.touchesEnded(touchLoc) && _btouched == false) {
        _btouched = true; 
        _BooAct->setVisible(true);
        _BooActTime->gotoFrameAndPlay(0, 55, false);
        _BooActTime->setLastFrameCallFunc([=]()
        {
            _BooAct->setVisible(false);
            _bToMenuScene = true;
        });
    }
}

CHomeScene::~CHomeScene()
{
	this->removeAllChildren();
    
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/teach_scene.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/teach_ui.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}



