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
    char chiness[10][4] = {{"一"},{"二"},{"三"},{"四"},{"五"},{"六"},{"七"},{"八"},{"九"},{"十"}};
public:
    fraction(int uni,int queNo, int number);
    
    //各單元答案
    void Input_u1(cocos2d::Node &Q, int number);
    void Input_u2_1(cocos2d::Node &Q, int number);
    void Input_u2_4(cocos2d::Node &Q, int number);
    void Input_u2_7(cocos2d::Node &Q, int number);
    void Input_u3_2(cocos2d::Node &Q, int number);
    
    char *Numerator(const char *c, const char *number);
    cocos2d::Node * Set_fraction(const char *numerator, const char *denominator, const char *front); //生成分數
    cocos2d::Node * FractionOperation(int n);
};
