#include "TouchSprite.h"
#include <cmath>

#define IMG_ANGLE 90

#define ANGLE(a) a*M_PI/180
#define RE_ANGLE(a) a*180/M_PI

TouchSprite::~TouchSprite(){
    CCLOG("delete TouchSprite");    
}

void TouchSprite::setVisible(bool b){
    for(int i=0; i<_Pic.size(); i++){
        _Pic[i]->setVisible(b);
    }
}

void TouchSprite::setRotation(float r) {
    _fangle = r;
    if (_fangle > 360)_fangle -= 360;
    else if (_fangle < 0)_fangle += 360;
    
    _obj->setRotation(-_fangle);
}

void TouchSprite::setPosition(Point pos) {
    _SpriteLoc = pos;
    _obj->setPosition(_SpriteLoc);
}

void TouchSprite::setImgPandR(int n,Point pos,float r){
    _Pic[n]->setPosition(pos);
    _Pic[n]->setRotation(r);

}
void TouchSprite::setImgPandR(Point pos[],float r[]){
    if(_cutMode == 2){
        _Pic[0]->setPosition(pos[0]); 
        _Pic[0]->setRotation(r[0]);
        _Pic[1]->setPosition(Vec2(0,0));
        _Pic[1]->setRotation(r[0]);
        
    }else{
        for(int i=0;i<_piece;i++){
            _Pic[i]->setPosition(pos[i]);
            _Pic[i]->setRotation(r[i]);
        }
    }
    
}


void TouchSprite::setDividedImg(){
    switch (_cutMode) {
        case 0:              //normal
            normalDivide();
            break;
        case 1:             //flower
           // sameHeightDivide();
            break;
        case 2:            //water
            waterDivide();
            break;
        case 3:            //long pic
            longPicDivide();
            break;
    }

}


void TouchSprite::normalDivide(){
    int g = _piece / 3;
    int tailamount = _piece % 3;
    Vec2 size =  _Pic[0]->getContentSize()/3*2;
    
    int i;
    for(i = 0; i<g; i++){                  //3個一組
        for(int j=0;j<3;j++){
            float x = size.x*(j - 1);
            _Pic[i*3+j]->setPositionX(x);
            _Pic[i*3+j]->setRotation(0);
        }
    }
    
    float d = (tailamount-1)/2.0 ;       //尾數部分
    for(int j=0;j<tailamount;j++){
        float x = size.x*(j - d);
        _Pic[i*3+j]->setPositionX(x);
        _Pic[i*3+j]->setRotation(0);
    }
    
    if(tailamount != 0) g++;
    d = (g-1) /2.0f;
    for(int i=0;i<_piece;i++){
        int j = i / 3;
        float y = -70*(j - d);
        _Pic[i]->setPositionY(y);
    }
    
}


void TouchSprite::sameHeightDivide(){
    int line = _piece / 3;
    int tailamount = _piece % 3;
    Vec2 size =  _Pic[0]->getContentSize()/3*2;
    
    std::vector<float> linetall;
    
    int i;
    for(i = 0; i<line; i++){                  //3個一組
        float tall =0;
        for(int j=0;j<3;j++){
            float x = size.x*(j - 1);
            _Pic[i*3+j]->setPositionX(x);
            _Pic[i*3+j]->setRotation(0);
            tall += _Pic[i*3+j]->getContentSize().height/2;
        }
        linetall.push_back(tall/3);
    }
    
    float d = (tailamount-1)/2.0 ;       //尾數部分
    float tall =0;
    for(int j=0;j<tailamount;j++){
        float x = size.x*(j - d);
        _Pic[i*3+j]->setPositionX(x);
        _Pic[i*3+j]->setRotation(0);
        tall += _Pic[i*3+j]->getContentSize().height/2;
    }
    linetall.push_back(tall/tailamount);
    
    if(tailamount != 0) line++;
    d = (line-1) /2.0f;
    for(int i=0;i<_piece;i++){
        int j = i / 3;
        float y = -90*(j - d);
        float dy =_Pic[i]->getContentSize().height/2;
        
        dy = 150 - dy;
        _Pic[i]->setPositionY(y + dy);
    }
    
}

void TouchSprite::waterDivide(){
    float y = _Pic[0]->getContentSize().height*_Pic[0]->getScaleY() /2;
    _Pic[0]->setPosition(Vec2(0,-135+y));
    _Pic[1]->setPosition(Vec2(0,0));
}

void TouchSprite::longPicDivide(){
    float width = _Pic[0]->getContentSize().width-10;
    float d = (_piece -1) /2.0f;
    
    for(int i = 0; i<_piece; i++){
        Point pos =Point(width*(i-d),0);
        _Pic[i]->setPosition(pos);
        _Pic[i]->setRotation(0);
    }
    
    
}

void TouchSprite::downOneFloor(){
    float y = (_Pic[0]->getContentSize().height - 8)*_Pic[0]->getScaleY();
    Vec2 pos =_Pic[0]->getPosition();
    _Pic[0]->setPosition(pos - Vec2(0,y));
    _StickyNumber-=1;
}

bool TouchSprite::touchesBegin(cocos2d::Point inPos, int id) {
	if (Collision(inPos) && _bVisible && _bEnabled)
	{
		if (_bTouched == false) {
			_bTouched = true;
			touchID[0] = id;
			touchPos[0] = inPos;
          //  d = Vec2(0,0);
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


float TouchSprite::getPicWidth(){
    float w =(_Pic[0]->getContentSize().width-7) * _piece;
    CCLOG("width = %f",w);
    return (w);
}


void TouchSprite::setWaterline(int num){
    Vec2 dmove = Vec2(0, getPicHeight());
    float c_center = (num - 1) /2.0f;
    
    Vec2 centerPos = Vec2(-70,(dmove.y+20)/2);  //水杯底厚14
    for (int i = 0; i <num; i++) {
        auto line = Sprite::createWithSpriteFrameName("water_line.png");
        Vec2 m = (i- c_center) * dmove;
        line->setPosition(centerPos + m);
        line->setRotation(0);
        _obj->addChild(line, 2);
        _Pic.push_back(line);
        }
}

void TouchSprite::setAtFinger(Point pt){
    setPosition(pt);
    d = Vec2(0,0);
}
