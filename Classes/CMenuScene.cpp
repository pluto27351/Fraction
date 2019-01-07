#include "CMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Common/const.h"
//#include "CUnitOneScene.h"
#include "CTeachScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* CMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CMenuScene::init()
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

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("menuscene.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Fraction_Btn.plist");
    auto rootNode = CSLoader::createNode("menuscene.csb");
    addChild(rootNode);

//    auto bk_img = Sprite::create("bkimg.png", Rect(0, 0, visibleSize.width, visibleSize.height));
//    Texture2D::TexParams tp = { GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT };
//    bk_img->getTexture()->setTexParameters(tp);
//    bk_img->setPosition(visibleSize.width / 2, visibleSize.height / 2);
//    this->addChild(bk_img, -1);

	// 設定按鈕
	char tname[30], tpngname[30], tpngnamehover[30];
	for (int i = 0; i < MAX_UNITS; i++)
	{
		sprintf(tname, "unit%d_btn", i + 1);
		auto spt = (Sprite*)rootNode->getChildByName(tname);
        sprintf(tpngname, "bt_0%d.png", i + 1);
        sprintf(tpngnamehover, "bt_0%d_hover.png", i + 1);
		Point pt = spt->getPosition();
		_unitBtn[i] = new CButton();
		_unitBtn[i]->setButtonInfo(tpngname, tpngnamehover, *this, pt, INTERFACE_LEVEL);
		//_unitBtn[i]->setScale(2.0f);
		rootNode->removeChildByName(tname);
	}
	_unitIdx = 0;	// 設定成切換的單元，1 到 5

	_listener1 = EventListenerTouchOneByOne::create();	//創建一個一對一的事件聆聽器
	_listener1->onTouchBegan = CC_CALLBACK_2(CMenuScene::onTouchBegan, this);		//加入觸碰開始事件
	_listener1->onTouchMoved = CC_CALLBACK_2(CMenuScene::onTouchMoved, this);		//加入觸碰移動事件
	_listener1->onTouchEnded = CC_CALLBACK_2(CMenuScene::onTouchEnded, this);		//加入觸碰離開事件

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器
	this->schedule(CC_SCHEDULE_SELECTOR(CMenuScene::doStep));

    return true;
}

void CMenuScene::doStep(float dt)  // OnFrameMove
{
	if (_unitIdx != 0) {
		this->unscheduleAllCallbacks();
		Director::getInstance()->runWithScene(CTeachScene::createScene(_unitIdx));
	}
//	switch (_unitIdx)
//	{
//	case 1:
//		this->unscheduleAllCallbacks();
////		Director::getInstance()->runWithScene(CUnitOneScene::createScene());
//		Director::getInstance()->runWithScene(CTeachScene::createScene());
//		break;
//	default:
//		break;
//	}
}

bool  CMenuScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
	for (int i = 0; i < MAX_UNITS; i++)
	{
		_unitBtn[i]->touchesBegin(touchLoc);
	}
//	_handDrawing->drawing(touchLoc);
	return true;
}

void  CMenuScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();
	for (int i = 0; i < MAX_UNITS; i++)
	{
		_unitBtn[i]->touchesMoved(touchLoc);
	}
}

void  CMenuScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();
	for (int i = 0; i < MAX_UNITS; i++)
	{
		if (_unitBtn[i]->touchesEnded(touchLoc)) {
			_unitIdx = i + 1;
			return;
		}
	}
}

CMenuScene::~CMenuScene()
{
	this->removeAllChildren();
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("menuscene.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}
