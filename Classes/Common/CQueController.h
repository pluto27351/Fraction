#pragma once

#include "cocos2d.h"
#include "Object/COnOffButton.h"
#include "Object/CButton.h"
#include "Object/CEqualController.h"
#include "Object/fraction.h"
#include "Object/combination.h"
#include "const.h"


USING_NS_CC;


class CQueController
{
public:
	CQueController(int iUnitNo, Node &rootNode, cocos2d::Layer &parent);
	~CQueController();

	// touch 事件
	bool touchesBegin(Point inPt,int iId, int iMode);
	bool touchesMoved(Point inPt,int iId, int iMode);
	bool touchesEnded(Point inPt,int iId, int iMode);
	bool getBoardStatus();
	bool goBackToMenu();

private:
	bool _bFracBoardOn;	// 顯示平分選單
	bool _bDivided;		// 已經被平分了
	bool _bShowImg;
	bool _bAnswer;
	bool _bBackMenu;

	int _curUnit;  //單元
	int _curQueNo; //題號
	int _curEqual; //數字

	const int(*equalData)[12];

	// 按鈕
	COnOffButton _answerBtn, _itemBtn, _equalBtn;  // 顯示答案與設定範例圖示顯示開關
	CButton _prevBtn, _nextBtn, _resetQueBtn,_menuBtn;	 // 前一題、下一題與本題重新出題的切換按鈕

	// 均分選單控制者
	CEqualController *_equalController;

	combination *try_img;
	//Node *answer;
    fraction * try_topic;

	Layer *_parentLayer;

	void setBtn(Node &rootNode, cocos2d::Layer &parent);

	void reset(int queNO , int equal);  	//queNo =  題號變化量  / equal = 數字變化 (0 = 隨機)
};
