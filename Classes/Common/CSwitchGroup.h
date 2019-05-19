#pragma once

#include "cocos2d.h"
#include "CSwitch.h"
#include "CButton.h"

USING_NS_CC;

class CSwitchGroup {
private:
	CSwitch *_numBtn;
	CButton *_okBtn;
	Sprite *_bg;

	Vec2 _halfLength,_okPos;
    bool _hasChoiceNum;
	int _n,_selectNumber;
public:
	CSwitchGroup();
	~CSwitchGroup();
	void init(const char *btn,int n,bool useOkbtn, const char *bg, cocos2d::Layer &parent, const cocos2d::Point locPt, int level);
	void setAsColumn();
	void setScale(float s);
	void setBgScale(float w,float h=0);
	void setPosition(Vec2 locPt);
	void setPosition(int number,Vec2 locPt);
	void setVisible(bool bVis);
	void setVisible(int number,bool bVis);
	void setEnabled(bool bEnable);
	void setEnabled(int number, bool bEnable);
    void setEnabledBtns(const int data[12],int num=0);
	void setSelectBtn(int number);
	int getSelectNumber();
    
	/*void setSwitch(int number, const char *normalImg, const char *selectImg, const cocos2d::Point locPt);
	void setOkBtn(const char *normalImg, const char *selectImg, const cocos2d::Point locPt);*/

	bool touchesBegin(cocos2d::Point inPos);
	bool touchesMoved(cocos2d::Point inPos);
	bool touchesEnded(cocos2d::Point inPos);
};
