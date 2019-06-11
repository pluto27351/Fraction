#include "CSwitchGroup.h"

USING_NS_CC;

CSwitchGroup::CSwitchGroup(){

}

CSwitchGroup::~CSwitchGroup() {
	delete [] _numBtn;
	delete _okBtn;
}

void CSwitchGroup::init(const char *btn ,const char *Okbtn, const char *bg, cocos2d::Layer &parent, const cocos2d::Point locPt, int level)
{
    _locPt = locPt;
	_bg = (Sprite *)Sprite::createWithSpriteFrameName(bg);
	_bg->setPosition(_locPt);
	parent.addChild(_bg, level);
    
    
	Vec2 L_half = Vec2(-130, 400);
	Vec2 L_ok = Vec2(0, 70);
	_halfLength = L_half + L_ok;

    _okPos.x = -_halfLength.x;
    _okPos.y = _halfLength.y;
    
	char pic[20];

    _okBtn = new CButton();
    _okBtn->setButtonInfo(Okbtn,Okbtn, parent, _locPt - _okPos, level);
    _okBtn->setEnabled(false);
	

	_numBtn = new CSwitch[11];
	Vec2 pos = _locPt + _halfLength;
	for (int i = 0; i < 11; i++) {
		sprintf(pic, "%s_%d.png", btn, i+2);
		_numBtn[i].setButtonInfo(pic, pic, parent, pos, level);
		pos.y -= 85;
	};

	_selectNumber = -1;
	//setSelectBtn(_selectNumber);
    _hasChoiceNum = false;
}

void CSwitchGroup::showSelectNumber(int n,cocos2d::Layer &parent, const cocos2d::Point dPt, int level) {
    char name[10];
    sprintf(name, "Q_%d.png",n);
    _selectN = (Sprite *)Sprite::createWithSpriteFrameName(name);
    _nPos = dPt;
    _selectN->setPosition(_locPt + _nPos);
    parent.addChild(_selectN,level);
    _showSelectN = true;
    
}

void CSwitchGroup::setSelectNumber(int n) {
    char name[10];
    sprintf(name, "Q_%d.png",n);
    auto num = (Sprite *)Sprite::createWithSpriteFrameName(name);
    _selectN->setDisplayFrame(num->getDisplayFrame());
    
}


void CSwitchGroup::setAsColumn() {
	_halfLength = Vec2(-475,70);
	_okPos = Vec2(0, -50);

	if (_okBtn!= NULL) _okBtn->setPosition(_locPt + _okPos);

	Vec2 pos = _locPt + _halfLength;
	for (int i = 0; i <11; i++) {
		_numBtn[i].setPosition(pos);
		pos.x += 95;
	};

}


void CSwitchGroup::setEnabledBtns(const int data[12], int num)
{
    setEnabled(false);
    int maxNum = data[0];
    for (int i = 1; i <= maxNum; i++) {  //讀取可用按鈕號碼
        int n = data[i];
        setEnabled(n - 2, true);         //按扭從２開始 -> ２號＝[0]
    }

    setSelectBtn(num - 2);
}

void CSwitchGroup::setScale(float s) {
	if (_okBtn != NULL) _okBtn->setScale(s);
	
	for (int i = 0; i < 11 ; i++)
		_numBtn[i].setScale(s);
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
    _locPt = locPt;
	_bg->setPosition(_locPt );

	if (_okBtn != NULL) _okBtn->setPosition(_locPt  - _okPos);
    if (_showSelectN) _selectN->setPosition(_locPt + _nPos);
    
	Vec2 pos = _locPt  + _halfLength;
	for (int i = 0; i < 11; i++) {
		_numBtn[i].setPosition(pos);
		pos.y -= 70;
	};
}


void CSwitchGroup::move(Vec2 dPt)
{
    _locPt += dPt;
    _bg->setPosition(_locPt);
    
    if (_okBtn != NULL) _okBtn->setPosition(_locPt - _okPos);
    if (_showSelectN) _selectN->setPosition(_locPt + _nPos);
    
    for (int i = 0; i < 11; i++) {
        auto pt = _numBtn[i].getPosition()+ dPt;
        _numBtn[i].setPosition(pt);
    };
}


void CSwitchGroup::setVisible(bool bVis) 
{
    if(!bVis){
        if(_selectNumber != -1){
            _numBtn[_selectNumber].setStatus(false);
            _selectNumber = -1;
        }
        _okBtn->setEnabled(false);
    }
    
	_bg->setVisible(bVis);
	if (_okBtn != NULL) _okBtn->setVisible(bVis);

	for (int i = 0; i < 11; i++)
		_numBtn[i].setVisible(bVis);
    
}

void CSwitchGroup::setVisible(int number, bool bVis) 
{
	_numBtn[number].setVisible(bVis);
}

void CSwitchGroup::setEnabled(bool bEnable) 
{
	for (int i = 0; i < 11; i++)
		_numBtn[i].setEnabled(bEnable);
}

void CSwitchGroup::setEnabled(int number, bool bEnable) 
{
	_numBtn[number].setEnabled(bEnable);
}

void CSwitchGroup::setSelectBtn(int number) //以陣列編號
{
	if(_selectNumber != -1)_numBtn[_selectNumber].setStatus(false);
	_selectNumber = number;
	_numBtn[_selectNumber].setStatus(true);
}

int CSwitchGroup::getSelectNumber() {
	return _selectNumber;
}

bool CSwitchGroup::touchesBegin(cocos2d::Point inPos)
{
	for (int i = 0; i < 11; i++)
		if (_numBtn[i].touchesBegin(inPos))return true;

    if(_selectNumber != -1){
        if (_okBtn->touchesBegin(inPos))return true;
    }
    
    auto posInNode = _bg->convertToNodeSpace(inPos);
    if (Rect(0,0,_bg->getContentSize().width,_bg->getContentSize().height).containsPoint(posInNode)) return true;


	return(false);
}

bool CSwitchGroup::touchesMoved(cocos2d::Point inPos)
{
	for (int i = 0; i < 11; i++)
		_numBtn[i].touchesMoved(inPos);

    if(_selectNumber != -1){_okBtn->touchesMoved(inPos);}

	return true;
}

bool CSwitchGroup::touchesEnded(cocos2d::Point inPos)
{
	for (int i = 0; i < 11; i++)
		if (_numBtn[i].touchesEnded(inPos)) {
            if(i ==_selectNumber){
                _selectNumber = -1;
                _okBtn->setEnabled(false);
            }
            else {
                setSelectBtn(i);
                _okBtn->setEnabled(true);
            }
		}

    if(_selectNumber != -1){
        if (_okBtn->touchesEnded(inPos)){
            return true;
        }
    }

	return(false);
}
