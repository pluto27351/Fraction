#pragma once
#include "cocos2d.h"
#include "COnButton.h"
#include "../const.h"


using namespace cocos2d;

#define MAX_EQUALITY 12

class CEqualController : public cocos2d::Node
{
protected:
	static CEqualController *_pEqualController;
	Point  _OnScreenLoc;	// 顯示在畫面上的位置
	COnButton _equalBtn[MAX_EQUALITY];  // 0 for ok btn,  1 for 2....
	//Sprite *_equalNo[MAX_EQUALITY];		 // 顯示等分的數字
	int   _selected;	// 所選取的均分量, 預設為 1，代表 2 等分被選取
	int   _selectedQuan[MAX_EQUALITY];	// [0] 放置目前提供的平分值數量，1 ~ 12 儲存平分值

public:
	CEqualController();
	~CEqualController();

	static CEqualController *create();		// 建立物件的實體
	static CEqualController *getInstance();	// 取得 CHandDrawing 的實體
	void   init(char *plist, char *csbname);	// 設定初始內容
	void   setScreenLoc(const Point &inPos);
	void   reset(int n);
	void   setEqualQuantity(const int(*unit)[12], int a, int n = 1);  // 傳入所能提供選擇的平分值

	bool touchesBegin(Point inPt);
	bool touchesMoved(Point inPt);
	int  touchesEnded(Point inPt);  // 傳回 0 或是 2 到 12 的值，0 代表 nothing，2 到 12 分別代表使用者所選擇的等分量

private:

};
  
