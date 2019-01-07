#include "COnButton.h"

USING_NS_CC;

COnButton::COnButton()
{
	_normalPic = nullptr;
	_touchedPic = nullptr;
}


void COnButton::setButtonInfo(const char *normalImg, const char *touchedImg, Layer &parent, const cocos2d::Point locPt, int level)
{
	_normalPic = (Sprite *)Sprite::createWithSpriteFrameName(normalImg);
	_touchedPic = (Sprite *)Sprite::createWithSpriteFrameName(touchedImg);
	_btnLoc = locPt;
	_normalPic->setPosition(_btnLoc); // 設定位置
	_touchedPic->setPosition(_btnLoc); // 設定位置
	_touchedPic->setVisible(false);
	_touchedPic->setScale(1.15f);
	parent.addChild(_normalPic, level);  // 加入目前的 Layer 中 1: Z 軸的層次，越大代表在越上層
	parent.addChild(_touchedPic, level); // 加入目前的 Layer 中 1: Z 軸的層次，越大代表在越上層

	// 取得大小
	_btnSize = _normalPic->getContentSize();
	// 設定判斷區域
	_btnRect.size = _btnSize;
	_btnRect.origin.x = _btnLoc.x - _btnSize.width*0.5f;
	_btnRect.origin.y = _btnLoc.y - _btnSize.height*0.5f;
	_bTouched = false;
	_fScale = 1.0f;
	_bVisible = _bEnabled = true;
	_bOn = false;
}


void COnButton::setButtonInfo(const char *normalImg, const char *touchedImg, Node &parent, const cocos2d::Point locPt, int level)
{
	_normalPic = (Sprite *)Sprite::createWithSpriteFrameName(normalImg);
	_touchedPic = (Sprite *)Sprite::createWithSpriteFrameName(touchedImg);
	_btnLoc = locPt;
	_normalPic->setPosition(_btnLoc); // 設定位置
	_touchedPic->setPosition(_btnLoc); // 設定位置
	_touchedPic->setVisible(false);
	_touchedPic->setScale(1.15f);
	parent.addChild(_normalPic, level);  // 加入目前的 Layer 中 1: Z 軸的層次，越大代表在越上層
	parent.addChild(_touchedPic, level); // 加入目前的 Layer 中 1: Z 軸的層次，越大代表在越上層
									 
	_btnSize = _normalPic->getContentSize(); // 取得大小
	// 設定判斷區域
	_btnRect.size = _btnSize;
	_btnRect.origin.x = _btnLoc.x - _btnSize.width*0.5f;
	_btnRect.origin.y = _btnLoc.y - _btnSize.height*0.5f;
	_bTouched = false;
	_fScale = 1.0f;
	_bVisible = _bEnabled = true;
	_bOn = false;
}

bool COnButton::touchesBegin(cocos2d::Point inPos)
{
	if( _btnRect.containsPoint(inPos) && _bVisible && _bEnabled)
	{
		_bTouched = true;
		_normalPic->setVisible(false);
		_touchedPic->setVisible(true);
		return(true); // 有按在上面
	}
	return(false);
}

bool COnButton::touchesMoved(cocos2d::Point inPos)
{
	if( _bTouched ) { // 只有被按住的時候才處理
		if( !_btnRect.containsPoint(inPos) ) { // 手指觸控區域離開按鈕
			if ( !_bOn ) {
				_normalPic->setVisible(true);
				_touchedPic->setVisible(false);
			}
			_bTouched = false;
			return(false);
		}
		else return(true);
	}
	return(false); // 事後再移到按鈕上將被忽略
}

bool COnButton::touchesEnded(cocos2d::Point inPos)
{
	if( _bTouched )
	{
		_bTouched = false;
		if ( !_bOn ) { 	// 目前不是按下狀態，這次是按在上面，切換成按下的顯示
			_normalPic->setVisible(false);
			_touchedPic->setVisible(true);
			_bOn = true;
		}// 如果目前已經是按下狀態，這次還是按在上面，則 do nothing
		return(true); 
	}
	return false;
}

void COnButton::setButtonOn()
{
	_bOn = true;
	_normalPic->setVisible(false);
	_touchedPic->setVisible(true);
}

void COnButton::setButtonOff()
{
	_bOn = false;
	_normalPic->setVisible(true);
	_touchedPic->setVisible(false);
}

void COnButton::setVisible(bool bVisible)
{
	_bVisible = bVisible;
	if (!_bVisible) _normalPic->setVisible(false);
	else _normalPic->setVisible(true);
}

void COnButton::setEnabled(bool bEnable)
{
	_bEnabled = bEnable;
	if (_bEnabled) _normalPic->setColor(Color3B(255, 255, 255)); 
	else _normalPic->setColor(Color3B(50, 50, 50));
}
