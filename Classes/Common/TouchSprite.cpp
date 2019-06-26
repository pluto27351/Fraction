#include "TouchSprite.h"
#include <cmath>

#define IMG_ANGLE 90

#define ANGLE(a) a*M_PI/180
#define RE_ANGLE(a) a*180/M_PI

void TouchSprite::setVisible(bool b){
    for(int i=0; i<_piece; i++){
        _Pic[i]->setVisible(b);
    }
}

void TouchSprite::setRotation(float r) {
    _fangle = r;
    if (_fangle > 360)_fangle -= 360;
    else if (_fangle < 0)_fangle += 360;
    
    _obj->setRotation(-_fangle);
    //for(int i=0; i<_piece; i++)_Pic[i]->setRotation(-_fangle);
}

void TouchSprite::setPosition(Point pos) {
    _SpriteLoc = pos;
    _obj->setPosition(_SpriteLoc);
   // for(int i=0; i<_piece; i++)_Pic[i]->setPosition(_SpriteLoc);
}

void TouchSprite::setImgPandR(int n,Point pos,float r){
    _Pic[n]->setPosition(pos);
    _Pic[n]->setRotation(r);
}

void TouchSprite::setDividedImg(){
    float d = _piece /2.0f;
    for(int i=0;i<_piece;i++){
        Point pos = Point(50*(i - d),0);
        _Pic[i]->setPosition(pos);
        _Pic[i]->setRotation(0);
    }
}

bool TouchSprite::touchesBegin(cocos2d::Point inPos, int id) {
	if (Collision(inPos) && _bVisible && _bEnabled)
	{
		if (_bTouched == false) {
			_bTouched = true;
			touchID[0] = id;
			touchPos[0] = inPos;
			d = inPos - getPosition();
            setDividedImg();
			return true;

		}
		else {
			RotatedBegin(inPos, id);
			return true;
		}

	}

	return false;
}

bool TouchSprite::touchesMoved(cocos2d::Point inPos, int id) {
	if (_bRotated) {
		if (id == touchID[0]) touchPos[0] = inPos;
		if (id == touchID[1]) touchPos[1] = inPos;
		RotateMoved();
        return(true);
	}
	else if (_bTouched && touchID[0] == id) {
		setPosition(inPos - d);
		touchPos[0] = inPos;
		return(true);
	}
	return(false);

}


bool TouchSprite::touchesEnded(cocos2d::Point inPos, int id) {
	if (_bRotated) {
		if (id == touchID[0])RotateEnded(1);      //判斷剩餘的觸碰點是有在物件上
		else if (id == touchID[1])RotateEnded(0);
		
        return !_bTouched;  //若仍在物件上 回傳false 不清除上層rotatrimg變數
	}
	else if (_bTouched)
	{
		touchID[0] = -1;
		d = Point(0, 0);
		_bTouched = false;
		touchPos[0] = Point(0, 0);
		return true;
	}
	return false;
}

void TouchSprite::RotatedBegin(cocos2d::Point inPos, int id) {
	float ta;
	float tx, ty;
	_bRotated = true;
	touchID[1] = id;  touchPos[1] = inPos;

	tx = touchPos[1].x - touchPos[0].x;
	ty = touchPos[1].y - touchPos[0].y;

	ta = atanf(ty / tx);
	ta = RE_ANGLE(ta) + 90;
	if (tx > 0)ta = ta + 180;

	_PreRotate = ta;


}

void TouchSprite::RotateMoved() {
	Point _CenterLoc;
	float ta;
	float tx, ty;
	tx = touchPos[1].x - touchPos[0].x;
	ty = touchPos[1].y - touchPos[0].y;
	ta = atanf(ty / tx);
	ta = RE_ANGLE(ta) + 90;
	if (tx > 0)ta = ta + 180;
	setRotation(_fangle + ta - _PreRotate);
	_PreRotate = ta;
    

}


void TouchSprite::RotateEnded(int i) {
    if (Collision(touchPos[i])){
        touchID[0] = touchID[i];
        touchPos[0] = touchPos[i];
        d = touchPos[0] - getPosition();
        _bTouched = true;
    }else {
        touchID[0] = -1;
        touchPos[0] = Point(0, 0);
        d = Point(0, 0);
        _bTouched = false;
    }
    
    touchID[1] = -1;
    touchPos[1] = Point(0, 0);
    
	_bRotated = false;

}


void TouchSprite::setSticky(int stickyNumber) {
	_StickyNumber = stickyNumber;
}

int TouchSprite::ResetSticky() {
	int sticky = _StickyNumber;
	_StickyNumber = -1;
	return sticky;
}
