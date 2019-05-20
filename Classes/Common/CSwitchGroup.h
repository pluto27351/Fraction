#pragma once

#include "cocos2d.h"
#include "CSwitch.h"
#include "CButton.h"

USING_NS_CC;

class CSwitchGroup {
private:
	CSwitch *_numBtn;
	CButton *_okBtn;
	Sprite *_bg,*_selectN;
    Point _locPt;
	Vec2 _halfLength,_okPos,_nPos;
    bool _hasChoiceNum;
	int _n,_selectNumber;
    bool _showSelectN = false;
public:
	CSwitchGroup();
	~CSwitchGroup();
	void init(const char *btn,int n,bool useOkbtn, const char *bg, cocos2d::Layer &parent, const cocos2d::Point locPt, int level);
	void setAsColumn();
	void setScale(float s);
	void setBgScale(float w,float h=0);
	void setPosition(Vec2 locPt);
	//void setPosition(int number,Vec2 locPt);
	void setVisible(bool bVis);
	void setVisible(int number,bool bVis);
	void setEnabled(bool bEnable);
	void setEnabled(int number, bool bEnable);
    void setEnabledBtns(const int data[12],int num=0);
	void setSelectBtn(int number);
    void showSelectNumber(int n,cocos2d::Layer &parent, const cocos2d::Point locPt, int level);
    void setSelectNumber(int);
	int getSelectNumber();
    void move(Vec2);

	bool touchesBegin(cocos2d::Point inPos);
	bool touchesMoved(cocos2d::Point inPos);
	bool touchesEnded(cocos2d::Point inPos);
};
