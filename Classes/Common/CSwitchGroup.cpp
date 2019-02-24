#include "CSwitchGroup.h"

USING_NS_CC;

CSwitchGroup::CSwitchGroup(){

}

CSwitchGroup::~CSwitchGroup() {
	delete [] _numBtn;
	delete _okBtn;
}

void CSwitchGroup::init(const char *btn,int n, bool useOkbtn, const char *bg, cocos2d::Layer &parent, const cocos2d::Point locPt, int level) 
{
	_bg = (Sprite *)Sprite::createWithSpriteFrameName(bg);
	_bg->setPosition(locPt);
	parent.addChild(_bg, level);

	Vec2 L_half = Vec2(0, (n - 1) / 2.0f * 100);
	Vec2 L_ok = Vec2(0, 70);
	_halfLength = L_half + L_ok;
	_okPos = _halfLength;

	char pic[20];
	if (useOkbtn) {
		_okBtn = new CButton();
		_okBtn->setButtonInfo("topic1_OK.png", "topic1_OK.png", parent, locPt - _okPos, level);
		_okBtn->setScale(0.85);
	}

	_numBtn = new CSwitch[n];
	Vec2 pos = locPt + _halfLength;
	for (int i = 0; i < n; i++) {
		sprintf(pic, "%s%02d.png", btn, i+2);
		_numBtn[i].setButtonInfo(pic, pic, parent, pos, level);
		_numBtn[i].setScale(0.8);
		pos.y -= 100;
	};

	_n = n;
	_selectNumber = 0;
	setSelectBtn(_selectNumber);
}

void CSwitchGroup::setAsColumn() {
	Point locPt = _bg->getPosition();

	_halfLength = Vec2(-(_n - 1) / 2.0f * 170,75);
	_okPos = Vec2(0, -75);

	if (_okBtn!= NULL) _okBtn->setPosition(locPt + _okPos);

	Vec2 pos = locPt + _halfLength;
	for (int i = 0; i < _n; i++) {
		_numBtn[i].setPosition(pos);
		pos.x += 170;
	};


}

void CSwitchGroup::setEnabled(const int(*data)[12], int que, int num)
{
	setEnabled(false);
	int maxNum = data[que - 1][0];
	for (int i = 1; i <= maxNum; i++) {
		int n = data[que - 1][i];
		setEnabled(n - 2, true);
	}
	setSelectBtn(num - 2);
}

void CSwitchGroup::setScale(float s) {
	if (_okBtn != NULL) _okBtn->setScale(s*0.85f);
	
	for (int i = 0; i < _n; i++) 
		_numBtn[i].setScale(s*0.8);
}

void CSwitchGroup::setBgScale(float w, float h) 
{
	if (h == 0) {
		_bg->setScale(w);
	}
	else {
		_bg->setScaleX(w);
		_bg->setScaleY(h);
	}
}

void CSwitchGroup::setPosition(Vec2 locPt) 
{
	_bg->setPosition(locPt);

	if (_okBtn != NULL) _okBtn->setPosition(locPt - _okPos);
		
	Vec2 pos = locPt + _halfLength;
	for (int i = 0; i < _n; i++) {
		_numBtn[i].setPosition(pos);
		pos.y -= 100;
	};
}

void CSwitchGroup::setPosition(int number, Vec2 locPt) 
{
	Vec2 pos = locPt + _halfLength;
	pos.y -= 100 * number;
	_numBtn[number].setPosition(pos);
}

void CSwitchGroup::setVisible(bool bVis) 
{
	_bg->setVisible(bVis);
	if (_okBtn != NULL) _okBtn->setVisible(bVis);

	for (int i = 0; i < _n; i++)
		_numBtn[i].setVisible(bVis);
}

void CSwitchGroup::setVisible(int number, bool bVis) 
{
	_numBtn[number].setVisible(bVis);
}

void CSwitchGroup::setEnabled(bool bEnable) 
{
	for (int i = 0; i < _n; i++)
		_numBtn[i].setEnabled(bEnable);
}

void CSwitchGroup::setEnabled(int number, bool bEnable) 
{
	_numBtn[number].setEnabled(bEnable);
}

void CSwitchGroup::setSelectBtn(int number) //以陣列編號
{
	_numBtn[_selectNumber].setStatus(false);
	_selectNumber = number;
	_numBtn[_selectNumber].setStatus(true);
}

int CSwitchGroup::getSelectNumber() {
	return _selectNumber;
}

bool CSwitchGroup::touchesBegin(cocos2d::Point inPos)
{
	for (int i = 0; i < _n; i++) 
		if (_numBtn[i].touchesBegin(inPos))return true;

	if (_okBtn->touchesBegin(inPos))return true;

	return(false);
}

bool CSwitchGroup::touchesMoved(cocos2d::Point inPos)
{
	for (int i = 0; i < _n; i++)
		_numBtn[i].touchesMoved(inPos);

	_okBtn->touchesMoved(inPos);

	return true;
}

bool CSwitchGroup::touchesEnded(cocos2d::Point inPos)
{
	for (int i = 0; i < _n; i++)
		if (_numBtn[i].touchesEnded(inPos)) {
			setSelectBtn(i);
		}

	if (_okBtn->touchesEnded(inPos))return true;

	return(false);
}
