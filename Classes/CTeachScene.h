#pragma once
#include "cocos2d.h"
#include "Common/CHandDrawing.h"
#include "Common/CQueController.h"


class CTeachScene : public cocos2d::Layer
{
public:
	~CTeachScene();
	// �ޤJ�����O�ܼ�
	CHandDrawing	 *_handDrawing;
	CQueController   *_queController;  // ���DŪ���P��ܪ����

	int _curMode;		// �����ثe�ާ@���Ҧ��O�e�ϡB���ʪ���Ψ�L
	bool _bFracBoardOn;	// �ثe����ܥ����ﶵ

	//  ���O�����禡
	static cocos2d::Scene* createScene(int unit);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void doStep(float dt);
	void setCreate(int unit);

	CButton _menuBtn;

	//Ĳ�I
	cocos2d::EventListenerTouchAllAtOnce *_listener1;
	void onTouchesBegan(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);
	void OnTouchesCancelled(const std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);

																	   // implement the "static create()" method manually
	CREATE_FUNC(CTeachScene);
};