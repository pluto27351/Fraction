#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

class CAnsCreater : public cocos2d::Node
{
private:
	//char chiness[11][8] = { {"A"},{"B"},{"C"},{"D"},{"E"},{"F"},{"G"},{"H"},{"I"},{"J"},{"K"} };
	char chiness[12][8] = {{"二"},{"三"},{"四"},{"五"},{"六"},{"七"},{"八"},{"九"},{"十"},{"十一"},{"十二"},{"十三"}};
    Color3B _textColor3B = Color3B(255,0,0);
    Color4B _textColor4B = Color4B(255,0,0,255);
    int outNumber[3]; //帶分／分母／分子
    
public:
    ~CAnsCreater();
    //答案生成
	CAnsCreater(int uni, int queNo, int number);
    CAnsCreater(int uni, int queNo, int number,int c,int b=-1);  //第4章變量題．第5章全
    CAnsCreater(int number,int q[3]);               //第3張線段題
	void Input_ans(cocos2d::Node &Q, int number);
//    void Input_ans2(cocos2d::Node &Q, int number);  //第二章3.5.8.11暫時用(x)
    
    //題目生成
    CAnsCreater() {};
    void queCreater(int uni, int queNo, int number);
    void queCreater(int uni, int queNo, int number,int c,int b=-1); //第4章變量題．第5章全
    void queLineCreater(int number,int q[3]);  //第3張線段題
	void Input_que(cocos2d::Node &Q, int number);
    

	char *Numerator(const char *c, const char *number);
    cocos2d::Node * Set_CAnsCreater(const char *numerator, const char *denominator, const char *front,Color3B wcolor = Color3B::RED); //生成分數
	cocos2d::Node * CAnsCreaterOperation(int n);

    int getA(){return outNumber[1];}
};
