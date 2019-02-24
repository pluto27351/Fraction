#include "CSwitch.h"

USING_NS_CC;

void CSwitch::setButtonInfo(const char *normalImg, const char *selectedImg, Layer &parent, const cocos2d::Point locPt, int level)
{
	_normalPic = (Sprite *)Sprite::createWithSpriteFrameName(normalImg);
	_selectedPic = (Sprite *)Sprite::createWithSpriteFrameName(selectedImg);
	_BtnLoc = locPt;
	_normalPic->setPosition(_BtnLoc); // 設定位置
	_selectedPic->setPosition(_BtnLoc); // 設定位置
	_selectedPic->setVisible(false);
	_selectedPic->setScale(1.15f);
	parent.addChild(_normalPic, level);  // 加入目前的 Layer 中 1: Z 軸的層次，越大代表在越上層
	parent.addChild(_selectedPic, level); // 加入目前的 Layer 中 1: Z 軸的層次，越大代表在越上層

	// 取得大小
	_BtnSize = _normalPic->getContentSize();
	// 設定判斷區域
	_BtnRect.size = _BtnSize;
	_BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
	_BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;

	_bTouched = false;
	_fScale = 1.0f;	_ftouchedScale = 1.15f;
	_bVisible = _bEnabled = true;
	_bStatus = false;
}


bool CSwitch::touchesBegin(cocos2d::Point inPos)
{
	if (_BtnRect.containsPoint(inPos) && _bVisible && _bEnabled)
	{
		_bTouched = true;
		_normalPic->setVisible(_bStatus);
		_selectedPic->setVisible(!_bStatus);
		return(true); // 有按在上面
	}
	return(false);
}

bool CSwitch::touchesMoved(cocos2d::Point inPos)
{
	if (_bTouched) { // 只有被按住的時候才處理
		if (!_BtnRect.containsPoint(inPos)) { // 手指頭位置離開按鈕
			_bTouched = false;
			_normalPic->setVisible(!_bStatus);
			_selectedPic->setVisible(_bStatus);
			return(false);
		}
		else return(true);
	}
	return(false); // 事後再移到按鈕上將被忽略
}

bool CSwitch::touchesEnded(cocos2d::Point inPos)
{
	if (_bTouched)
	{
		_bTouched = false;
		_bStatus = !_bStatus;
		/*_normalPic->setScale(_fScale);
		_normalPic->setVisible(true);
		_selectedPic->setVisible(false);*/

		if (_BtnRect.containsPoint(inPos)) return(true);  // 手指頭位置按鈕時，還在該按鈕上
	}
	return false;
}


void CSwitch::setVisible(bool bVisible)
{
	_bVisible = bVisible;
	if (!_bVisible) {
			_normalPic->setVisible(false);
			_selectedPic->setVisible(false);
	}
	else {
		_normalPic->setVisible(!_bStatus);
		_selectedPic->setVisible(_bStatus);
	}
	/*_normalPic->setVisible(true);
	_selectedPic->setVisible(false);

	if (!_bVisible) _normalPic->setVisible(false);
	else _normalPic->setVisible(true);*/
}

void  CSwitch::setStatus(bool status) {
	_bStatus = status;

	_normalPic->setVisible(!status);
	_selectedPic->setVisible(status);
}


void CSwitch::setEnabled(bool bEnable)
{
	_bEnabled = bEnable;

	if (_bEnabled) {
		_normalPic->setVisible(!_bStatus);
		_selectedPic->setVisible(_bStatus);
		_normalPic->setColor(Color3B(255, 255, 255));
	}
	else {
		_normalPic->setVisible(true);
		_selectedPic->setVisible(false);
		_normalPic->setColor(Color3B(50, 50, 50));
	}
	
}

void CSwitch::setTouchScale(float s) {
	_ftouchedScale = s;
	_selectedPic->setScale(_fScale*_ftouchedScale);
}

void CSwitch::setPosition(Vec2 locPt) {
	_BtnLoc = locPt;
	_normalPic->setPosition(_BtnLoc); // 設定位置
	_selectedPic->setPosition(_BtnLoc); // 設定位置
	
	_BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
	_BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;
}

void CSwitch::setScale(float fscale)
{
	_fScale = fscale;
	// 重新設定判斷區域範圍
	_BtnRect.size.width *= _fScale;
	_BtnRect.size.height *= _fScale;
	_BtnRect.origin.x = _BtnLoc.x - _BtnRect.size.width*0.5f;
	_BtnRect.origin.y = _BtnLoc.y - _BtnRect.size.height*0.5f;
	_normalPic->setScale(_fScale);
	_selectedPic->setScale(_fScale*_ftouchedScale);
}
