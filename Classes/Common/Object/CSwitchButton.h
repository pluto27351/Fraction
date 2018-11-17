//
//	提供五種不同顏色切換顯示的按鈕
//
//
//

#pragma once

#include "cocos2d.h"
#include "COnButton.h"

USING_NS_CC;
using namespace cocos2d;

#define NUM_COLOR 5

class CSwitchButton : public Ref
{
private:
	Color3B _defaultColor[NUM_COLOR];
	COnButton _colorBtn[NUM_COLOR]; // 五個顏色的按鈕
	int		_colorIdx;

public:
	CSwitchButton();
	~CSwitchButton();
	void setButtonInfo(Node &rootNode, cocos2d::Layer &parent, int level);
	Color3B getColor(); // 取得目前使用者所選取的顏色
	bool touchesBegin(cocos2d::Point inPt);
	bool touchesMoved(cocos2d::Point inPt);
	bool touchesEnded(cocos2d::Point inPt);
};