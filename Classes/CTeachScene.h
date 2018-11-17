#pragma once
#include "cocos2d.h"
#include "Common/CHandDrawing.h"
#include "Common/CQueController.h"


class CTeachScene : public cocos2d::Layer
{
public:
	~CTeachScene();
	// 引入的類別變數
	CHandDrawing	 *_handDrawing;
	CQueController   *_queController;  // 問題讀取與顯示的控制器

	int _curMode;		// 紀錄目前操作的模式是畫圖、移動物體或其他
	bool _bFracBoardOn;	// 目前有顯示平分選項

	//  類別內的函式
	static cocos2d::Scene* createScene(int unit);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void doStep(float dt);
	void setCreate(int unit);

	CButton _menuBtn;

	//觸碰
	cocos2d::EventListenerTouchAllAtOnce *_listener1;
	void onTouchesBegan(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);
	void OnTouchesCancelled(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);

																	   // implement the "static create()" method manually
	CREATE_FUNC(CTeachScene);
};