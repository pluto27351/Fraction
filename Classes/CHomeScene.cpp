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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Size size;

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/homescene.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/Fraction_Btn.plis");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/scene101.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Fraction_menu.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/teach_ui.plist");
    auto rootNode = CSLoader::createNode("homescene.csb");
    addChild(rootNode);
    
	auto _BtnLoc = rootNode->getChildByName("startBtn")->getPosition();
	_startBtn.setButtonInfo("next_R.png", "next_R_click.png", *this, _BtnLoc, 1);
	rootNode->removeChildByName("startBtn");

    _BtnLoc = rootNode->getChildByName("Boo")->getPosition();
	auto _scale = rootNode->getChildByName("Boo")->getScale();
	_Boo.setButtonInfo("bean2_01.png", "bean2_01.png", *this, _BtnLoc, 1);
	_Boo.setTouchScale(1);
	_Boo.setScale(_scale);
	rootNode->removeChildByName("Boo");

	_BooAct = CSLoader::createNode("ani/Boo.csb");
	_BooAct->setPosition(_BtnLoc);
	_BooAct->setScale(_scale);
	this->addChild(_BooAct);
	_BooAct->setVisible(false);
	_BooActTime = (ActionTimeline *)CSLoader::createTimeline("ani/Boo.csb");
	_BooAct->runAction(_BooActTime);

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
		Director::getInstance()->runWithScene(scene);
	}
}

bool  CHomeScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
	_startBtn.touchesBegin(touchLoc);
	_Boo.touchesBegin(touchLoc);
	return true;
}

void  CHomeScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();
	_startBtn.touchesMoved(touchLoc);
	_Boo.touchesMoved(touchLoc);
}

void  CHomeScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();
	if (_Boo.touchesEnded(touchLoc)) {
		_Boo.setVisible(false);  _BooAct->setVisible(true);
		_BooActTime->gotoFrameAndPlay(0, 15, false);
		_BooActTime->setLastFrameCallFunc([=]()
		{
			_Boo.setVisible(true);  _BooAct->setVisible(false);
		});
	}

	if (_startBtn.touchesEnded(touchLoc)) _bToMenuScene = true;


}

CHomeScene::~CHomeScene()
{
	this->removeAllChildren();

//    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/homescene.plist");
//    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/Fraction_Btn.plist");
//    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/scene101.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Fraction_menu.plist");
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/teach_ui.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}
