#pragma once

#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d;

class COnOffButton
{
private:
	Sprite *_normalPic;
	Sprite *_touchedPic;

	Size  _btnSize;
	Point _btnLoc;
	Rect  _btnRect;

	float _fScale;	// 圖片縮放的大小
	bool _bTouched; // 是否被按下，用於觸控時的判斷
	bool _bEnabled; // 是否有作用
	bool _bVisible; // 是否顯示
	bool _bOn;		// 代表目前按鈕是按下的狀態

public:
	COnOffButton();
	void setButtonInfo(const char *normalImg, const char *touchedImg, cocos2d::Layer &parent, const cocos2d::Point locPt, int level);
	void setButtonInfo(const char *normalImg, const char *touchedImg, cocos2d::Node  &parent, const cocos2d::Point locPt, int level);
	bool touchesBegin(cocos2d::Point inPos);
	bool touchesMoved(cocos2d::Point inPos); 
	bool touchesEnded(cocos2d::Point inPos); 
	void setVisible(bool bVis);
	void setButtonOn();	 // 設定這個按鈕目前是選取狀態
	void setButtonOff(); // 設定這個按鈕目前是沒有被選取
	void setEnabled(bool bEnable);
	bool getStatus();	// 傳回目前開關按鈕的狀態
};