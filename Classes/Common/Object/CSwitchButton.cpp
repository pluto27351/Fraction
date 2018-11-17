#include "CSwitchButton.h"

USING_NS_CC;

void CSwitchButton::setButtonInfo(Node &rootNode, cocos2d::Layer &parent, int level)
{
	Sprite *colorBtn = (Sprite *)rootNode.getChildByName("colorb_nl");
	Point pt = colorBtn->getPosition();
	_colorBtn[0].setButtonInfo("colorb_nl.png", "colorb_on.png", parent, pt, level);
	_colorBtn[0].setButtonOn();
	rootNode.removeChildByName("colorb_nl");

	colorBtn = (Sprite *)rootNode.getChildByName("colorg_nl");
	pt = colorBtn->getPosition();
	_colorBtn[1].setButtonInfo("colorg_nl.png", "colorg_on.png", parent, pt, level);
	rootNode.removeChildByName("colorg_nl");

	colorBtn = (Sprite *)rootNode.getChildByName("colork_nl");
	pt = colorBtn->getPosition();
	_colorBtn[2].setButtonInfo("colork_nl.png", "colork_on.png", parent, pt, level);
	rootNode.removeChildByName("colork_nl");

	colorBtn = (Sprite *)rootNode.getChildByName("colory_nl");
	pt = colorBtn->getPosition();
	_colorBtn[3].setButtonInfo("colory_nl.png", "colory_on.png", parent, pt, level);
	rootNode.removeChildByName("colory_nl");

	colorBtn = (Sprite *)rootNode.getChildByName("colorr_nl");
	pt = colorBtn->getPosition();
	_colorBtn[4].setButtonInfo("colorr_nl.png", "colorr_on.png", parent, pt, level);
	rootNode.removeChildByName("colorr_nl");
}


bool CSwitchButton::touchesBegin(cocos2d::Point inPt)
{
	for (int i = 0; i < NUM_COLOR; i++) {
		if (_colorBtn[i].touchesBegin(inPt)) return true;
	}
	return false;
}

bool CSwitchButton::touchesMoved(cocos2d::Point inPt)
{
	for (int i = 0; i < NUM_COLOR; i++) {
		if (_colorBtn[i].touchesMoved(inPt)) return true;
	}
	return false;
}

bool CSwitchButton::touchesEnded(cocos2d::Point inPt)
{
	for (int i = 0; i < NUM_COLOR; i++) {
		if (_colorBtn[i].touchesEnded(inPt)) { // 代表這個按鈕被按到
			if (i != _colorIdx) { // 目前被按下的顏色跟之前的顏色不同，切換顯示
				_colorBtn[_colorIdx].setButtonOff();
				_colorIdx = i;
				return(true);	// 代表顏色被更新
			}
			else {
				return(false);	// 代表顏色沒有被更新
			}
		}
	}
	return(false);
}

Color3B CSwitchButton::getColor()  // 取得目前使用者所選取的顏色
{
	return(_defaultColor[_colorIdx]);
}

// 建構元 設定初始狀態
// 藍色為預設選項，藍色放在第一個位置
CSwitchButton::CSwitchButton()
{
	// 5種顏色的順序是 藍、綠、黑、黃、紅
	_defaultColor[0] = Color3B(0, 0, 250);
	_defaultColor[1] = Color3B(0, 255, 0);
	_defaultColor[2] = Color3B(0, 0, 0);
	_defaultColor[3] = Color3B(250, 250, 0);
	_defaultColor[4] = Color3B(250, 0, 0);
	_colorIdx = 0;
}

CSwitchButton::~CSwitchButton()
{

}