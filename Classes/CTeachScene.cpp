#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CTeachScene.h"
#include "CMenuScene.h"
#include "Data.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* CTeachScene::createScene(int unit)
{
	auto scene = Scene::create();

	auto layer = CTeachScene::create();
	layer->setCreate(unit);

	scene->addChild(layer);

	return scene;
}

bool CTeachScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_listener1 = EventListenerTouchAllAtOnce::create();
	_listener1->onTouchesBegan = CC_CALLBACK_2(CTeachScene::onTouchesBegan, this);
	_listener1->onTouchesMoved = CC_CALLBACK_2(CTeachScene::onTouchesMoved, this);
	_listener1->onTouchesEnded = CC_CALLBACK_2(CTeachScene::onTouchesEnded, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器
	this->schedule(CC_SCHEDULE_SELECTOR(CTeachScene::doStep));

	return true;
}

void CTeachScene::setCreate(int unit) 
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/handdrawing.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/Fraction_Btn.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/Fraction_Wood.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("img/quecontrol.plist");
	auto rootNode = CSLoader::createNode("TeachScene.csb");
	addChild(rootNode);

	_handDrawing = CDrawingPanel::create();
	_handDrawing->initDrawingPanel(*rootNode, *this);
	_handDrawing->retain();

	//menubtn
	auto pt = rootNode->getChildByName("menubtn")->getPosition();
	auto scale = rootNode->getChildByName("menubtn")->getScale();
	_menuBtn.setButtonInfo("prevque_off.png", "prevque_off.png", *this, pt, 1);
	_menuBtn.setScale(scale);
	rootNode->removeChildByName("menubtn");

	// 問題讀取控制器初始設定
	_queController = new CQuePanel(unit, *rootNode, *this);  // 設定為讀取 unit1 的題目

	_bFracBoardOn = false;
	_toolMode = _handDrawing->getMode();
}

void CTeachScene::doStep(float dt)  // OnFrameMove
{
	if (_bMeunBtnPressed) {
		this->unscheduleAllCallbacks();
		Director::getInstance()->runWithScene(CMenuScene::createScene());
	}

}


void CTeachScene::onTouchesBegan(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event) {
    _toolMode = _handDrawing->getMode();
	for (auto &item : touches) {
		auto touch = item;
		auto touchLoc = touch->getLocation();
		auto touchId = touch->getID();
		bool touchOnEmpty = true;

		touchOnEmpty *= !_queController->touchesBegin(touchLoc, touchId, _toolMode);

		if (!_bFracBoardOn) {
			touchOnEmpty *= !_menuBtn.touchesBegin(touchLoc);
			touchOnEmpty *= !_handDrawing->touchesBegin(touchLoc);

			if (touchOnEmpty && _toolMode == HAND_MODE) {
				_handDrawing->changeToBlackPen();
			}
		}
		

	}
}

void CTeachScene::onTouchesMoved(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event)
{
	for (auto &item : touches) {
		auto touch = item;
		auto touchLoc = touch->getLocation();
		auto touchId = touch->getID();
		Point preTouchLoc = touch->getPreviousLocation();

		_queController->touchesMoved(touchLoc, touchId, _toolMode);

		if (!_bFracBoardOn) {
			bool p = _menuBtn.touchesMoved(touchLoc);
			if(!p) _handDrawing->touchesMoved(touchLoc, preTouchLoc);
		}

	}
}

void  CTeachScene::onTouchesEnded(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event)
{
	for (auto &item : touches) {
		auto touch = item;
		auto touchLoc = touch->getLocation();
		auto touchId = touch->getID();
			
		if (_queController->touchesEnded(touchLoc, touchId, _toolMode)) {
			if (_queController->getBoardStatus())  _bFracBoardOn = true;
			else _bFracBoardOn = false;
            
            if(_queController->resetActive())_handDrawing->clearWhiteBoard();
		}


		if (!_bFracBoardOn) {
			if (_menuBtn.touchesEnded(touchLoc)) _bMeunBtnPressed = true;
            else if (_handDrawing->touchesEnded(touchLoc)) _queController->reset();     //只有reset鍵時回傳true
		}
	}
}

CTeachScene::~CTeachScene()
{
	_handDrawing->release();
	//delete _queController;
	this->removeAllChildren();

	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/handdrawing.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/Fraction_Btn.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/Fraction_Wood.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/quecontrol.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}
