#include "CTeachScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CMenuScene.h"


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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("handdrawing.plist");

	auto rootNode = CSLoader::createNode("unitscene.csb");
	addChild(rootNode);

	_handDrawing = CHandDrawing::create();
	_handDrawing->initHandDrawing(*rootNode, *this);
	_handDrawing->retain();


	// 問題讀取控制器初始設定
	_queController = new CQueController(unit, *rootNode, *this);  // 設定為讀取 unit1 的題目
	_bFracBoardOn = false;

}

void CTeachScene::doStep(float dt)  // OnFrameMove
{
	_handDrawing->doStep(dt);

}

void CTeachScene::onTouchesBegan(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event) {
	for (auto &item : touches) {
		auto touch = item;
		auto touchLoc = touch->getLocation();
		auto touchId = touch->getID();

		if (!_bFracBoardOn) _handDrawing->touchesBegin(touchLoc);
		_queController->touchesBegin(touchLoc, touchId, _curMode);
	}
}

void CTeachScene::onTouchesMoved(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event)
{
	for (auto &item : touches) {
		auto touch = item;
		auto touchLoc = touch->getLocation();
		auto touchId = touch->getID();
		Point preTouchLoc = touch->getPreviousLocation();

		if (!_bFracBoardOn) _handDrawing->touchesMoved(touchLoc, preTouchLoc);
		_queController->touchesMoved(touchLoc, touchId, _curMode);
	}
}

void  CTeachScene::onTouchesEnded(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event)
{
	for (auto &item : touches) {
		auto touch = item;
		auto touchLoc = touch->getLocation();
		auto touchId = touch->getID();

		if (!_bFracBoardOn)
			if (_handDrawing->touchesEnded(touchLoc)) {
				_curMode = _handDrawing->getMode();
			}
		if (_queController->touchesEnded(touchLoc, touchId, _curMode)) {
			// check 目前是否有開啟平分選單
			if (_queController->getBoardStatus())
				_bFracBoardOn = true;
			else _bFracBoardOn = false;

			if (_queController->goBackToMenu()) {
				this->unscheduleAllCallbacks();
				Director::getInstance()->runWithScene(CMenuScene::createScene());
			}
		}
	}
}

CTeachScene::~CTeachScene()
{
	_handDrawing->release();
	delete _queController;
	this->removeAllChildren();

	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("handdrawing.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}