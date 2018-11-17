#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CHomeScene.h"
#include "CMenuScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* CHomeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CHomeScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CHomeScene::init()
{
     
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size size;


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("homescene.plist");
    auto rootNode = CSLoader::createNode("homescene.csb");
    addChild(rootNode);
	_startTap = (Sprite *)rootNode->getChildByName("start_tap");

	auto bk_img = Sprite::create("bkimg.png", Rect(0, 0, visibleSize.width, visibleSize.height));
	Texture2D::TexParams tp = { GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT };
	bk_img->getTexture()->setTexParameters(tp);
	bk_img->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bk_img, -1);

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
	else {
		// 每秒鐘讓 _startTap 從目前的大小變大1.5倍在縮小
		float t = fabs(sinf(_fTotalTime*M_PI_4)*0.45f)+2;
		_startTap->setScale(t);
		_fTotalTime += dt;
	}
}

bool  CHomeScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
//	_handDrawing->drawing(touchLoc);
	return true;
}

void  CHomeScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();
}

void  CHomeScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();
	// switch to menu scene
	_bToMenuScene = true;

}

CHomeScene::~CHomeScene()
{
	this->removeAllChildren();
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("homescene.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}