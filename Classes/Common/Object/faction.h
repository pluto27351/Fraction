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
	const std::string chiness[11] = { { "�G" },{ "�T" },{ "�|" },{ "��" },{ "��" },{ "�C" },{ "�K" },{ "�E" },{ "�Q" },{ "��" },{ "�L" } };
public:
	void Input_Que(cocos2d::Node &Q, int number);//���D���M���X�������Ʀr
	cocos2d::Node * Set_fraction(const char *numerator, const char *denominator); //�ͦ�����
	cocos2d::Node * FractionOperation(int n);
};