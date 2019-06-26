#ifndef __CBUTTON_H__
#define __CBUTTON_H__

#include "cocos2d.h"

USING_NS_CC;

class CButton
{
private:
	cocos2d::Sprite *_normalPic;
	cocos2d::Sprite *_touchedPic;

	cocos2d::Size  _BtnSize;
	cocos2d::Point _BtnLoc;
	cocos2d::Rect  _BtnRect;

	float _fScale, _ftouchedScale;	// 圖片縮放的大小
	bool _bTouched; // 是否被按下
	bool _bEnabled; // 是否有作用
	bool _bVisible; // 是否顯示

public:
	void setButtonInfo(const char *normalImg, const char *touchedImg, cocos2d::Layer &parent, const cocos2d::Point locPt, int level);
	bool touchesBegin(cocos2d::Point inPos);
	bool touchesMoved(cocos2d::Point inPos);
	bool touchesEnded(cocos2d::Point inPos);
	void setVisible(bool bVis);
	void setTouched();	// 設定這個按鈕目前是選取狀態
	void setEnabled(bool bEnable);
	void setPosition(Vec2 locPt);
	void setScale(float fscale);
	void setTouchScale(float s);
};


#endif
