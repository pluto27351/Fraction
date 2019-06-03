#include "TouchSprite.h"
#include <cmath>

#define IMG_ANGLE 90

#define ANGLE(a) a*M_PI/180
#define RE_ANGLE(a) a*180/M_PI

void TouchSprite::setSectorButtonInfo(const char *Img, float scale)
{
	_Pic = (Sprite *)Sprite::createWithSpriteFrameName(Img);
	ImgRadius = _Pic->getContentSize().height * scale;
	_Pic->setScale(scale);
	_fscale = scale;
	_bTouched = false;
	_bRotated = false;
	_bVisible = _bEnabled = true;
}

void TouchSprite::setVisible(bool b){
    _Pic->setVisible(b);
}

bool TouchSprite::SectorCollision(Point touch) {
	Point _CenterLoc;
	float td, ta;
	float tx, ty;
	_CenterLoc.x = _Pic->getPosition().x - ImgRadius / 2 * cosf(ANGLE((_fangle + IMG_ANGLE)));
	_CenterLoc.y = _Pic->getPosition().y - ImgRadius / 2 * sinf(ANGLE((_fangle + IMG_ANGLE)));
	tx = touch.x - _CenterLoc.x;
	ty = touch.y - _CenterLoc.y;
	td = sqrtf(powf(tx, 2) + powf(ty, 2));
	ta = atanf(ty / tx);
	ta = RE_ANGLE(ta) + 90;
	if (tx > 0)ta = ta + 180;
	//	if (ta > 360 - ImgAngle / 2)ta -= 360;
	float f_min = _fangle - ImgAngle / 2, f_max = _fangle + ImgAngle / 2;
	if (td <= ImgRadius) {
		if (ta >= f_min && ta <= f_max)return true;
		if (f_min < 0 && ta > 360 + f_min)return true;
		if (f_max > 360 && ta < f_max - 360)return true;
	}
	return false;
}
void TouchSprite::setRotation(float r) {
	_fangle = r;
	if (_fangle > 360)_fangle -= 360;
	else if (_fangle < 0)_fangle += 360;
	_Pic->setRotation(-_fangle);
}

void TouchSprite::SetPosition(Point pos) {

	_SpriteLoc = pos;
	_Pic->setPosition(_SpriteLoc);
}

Sprite *TouchSprite::getImg() {
	return _Pic;
}

void TouchSprite::ImgRotate(Point touch) {
	Point _CenterLoc;
	float ta;
	float tx, ty;
	_CenterLoc.x = _Pic->getPosition().x - ImgRadius / 2 * cosf(ANGLE((_fangle + IMG_ANGLE)));
	_CenterLoc.y = _Pic->getPosition().y - ImgRadius / 2 * sinf(ANGLE((_fangle + IMG_ANGLE)));
	tx = touch.x - _CenterLoc.x;
	ty = touch.y - _CenterLoc.y;
	ta = atanf(ty / tx);
	ta = RE_ANGLE(ta) + 90;
	if (tx > 0)ta = ta + 180;

	setRotation(_fangle + ta);
}


bool TouchSprite::touchesBegin(cocos2d::Point inPos, int id) {
	if (SectorCollision(inPos) && _bVisible && _bEnabled)
	{
		if (_bTouched == false) {
			_bTouched = true;
			touchID[0] = id;
			touchPos[0] = inPos;
			d = inPos - getImg()->getPosition();
			return true;

		}
		else {
			RotatedBegin(inPos, id);
			return true;
		}

	}

	return false;
}

int TouchSprite::touchesMoved(cocos2d::Point inPos, int id) {
	if (_bRotated) {
		if (id == touchID[0]) touchPos[0] = inPos;
		if (id == touchID[1]) touchPos[1] = inPos;
		RotateMoved();
	}
	else if (_bTouched && touchID[0] == id) {
		SetPosition(inPos - d);
		touchPos[0] = inPos;
		return(1);
	}
	return(0);
	//    else if (_bTouched && touchID[0] == id) {
	//        if (!SectorCollision(inPos)) {
	//            _bTouched = false;
	//            touchID[0] = -1;
	//            touchPos[0] = Point(0,0);
	//            return(2);  //離開移動範圍
	//        }
	//        else {
	//            SetPosition(inPos - d);
	//            touchPos[0] = inPos;
	//            return(1);  //移動了
	//        }
	//    }
	//    return(0);   //非移動狀態
}


bool TouchSprite::touchesEnded(cocos2d::Point inPos, int id) {
	if (_bRotated) {
		if (id == touchID[0])RotateEnded(0);
		else if (id == touchID[1])RotateEnded(1);
		return false;
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
	//if(i == 0){
	//    touchID[0]  = touchID[1];
	//    touchPos[0] = touchPos[1];
	//    d = touchPos[0] - getImg()->getPosition();
	//}
	for (int k = 0; k < 2; k++) {
		touchID[k] = -1;
		touchPos[k] = Point(0, 0);
	}
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
