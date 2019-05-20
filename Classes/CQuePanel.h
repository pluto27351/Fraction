#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Common/CAnsCreater.h"
#include "Common/CCutImage.h"
#include "Common/CButton.h"
#include "Common/CSwitch.h"
#include "Common/CSwitchGroup.h"
#include "Data.h"


USING_NS_CC;
using namespace ui;

class CQuePanel : public Ref
{
private:
    bool _bFracBoardOn;    // 顯示平分選單
    bool _bDivided;        // 已經被平分了
    bool _bAnswer;
    bool _bnum;         //選擇分母介面是否顯示
    bool _bResetActive,_bCutDown;
    
    int _curUnit;  //單元
    int _curQue; //題號
    int _curNum; //數字
    
    CButton _prevBtn, _nextBtn;
    CSwitch _ansBtn,_numBtn,_cutBtn;
    CSwitchGroup _numSwitcher,_cutSwitcher;
    CCutImage *_cutImage;
    CAnsCreater *_ans,*_que;
    const int(*equalData)[12];
    
    Layer *_parentLayer;
public:
	CQuePanel(int iUnitNo, Node &rootNode, cocos2d::Layer &parent);
	~CQuePanel();

	// touch 事件
	bool touchesBegin(Point inPt, int iId, int iMode);
	bool touchesMoved(Point inPt, int iId, int iMode);
	bool touchesEnded(Point inPt, int iId, int iMode);
    
	bool getBoardStatus();
    bool resetActive();
    bool cutDown();
    void reset(int queNO = 0, int equal = 0);      //queNo =  題號變化量  / equal = 數字變化 (0 = 隨機)
    void setBtn(Node &rootNode, cocos2d::Layer &parent);

    

};
