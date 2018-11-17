#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

class fraction : public cocos2d::Node
{
private:
	const std::string chiness[11] = { { "二" },{ "三" },{ "四" },{ "五" },{ "六" },{ "七" },{ "八" },{ "九" },{ "十" },{ "壹" },{ "貳" } };
public:
	void Input_Que(cocos2d::Node &Q, int number);//傳題型和分幾等分的數字
	cocos2d::Node * Set_fraction(const char *numerator, const char *denominator); //生成分數
	cocos2d::Node * FractionOperation(int n);
};