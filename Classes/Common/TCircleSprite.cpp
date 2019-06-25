#include "TCircleSprite.h"

#define IMG_ANGLE 90

#define ANGLE(a) a*M_PI/180
#define RE_ANGLE(a) a*180/M_PI

bool TCircleSprite::Collision(Point touch) {
    Point _CenterLoc;
    float td, ta;
    float tx, ty;
    _CenterLoc.x = _obj->getPosition().x - ImgRadius / 2 * cosf(ANGLE((_fangle + IMG_ANGLE)));
    _CenterLoc.y = _obj->getPosition().y - ImgRadius / 2 * sinf(ANGLE((_fangle + IMG_ANGLE)));
    tx = touch.x - _CenterLoc.x;
    ty = touch.y - _CenterLoc.y;
    td = sqrtf(powf(tx, 2) + powf(ty, 2));
    ta = atanf(ty / tx);
    ta = RE_ANGLE(ta) + 90;
    if (tx > 0)ta = ta + 180;
    //    if (ta > 360 - ImgAngle / 2)ta -= 360;
    float f_min = _fangle - ImgAngle / 2, f_max = _fangle + ImgAngle / 2;
    if (td <= ImgRadius) {
        if (ta >= f_min && ta <= f_max)return true;
        if (f_min < 0 && ta > 360 + f_min)return true;
        if (f_max > 360 && ta < f_max - 360)return true;
    }
    return false;
}

void TCircleSprite::setImgInfo(const char *Img,int piece, float scale,Point pos[],float r)
{
    _obj = new Node;
    
    _piece = piece;
    _Pic = new Sprite *[_piece];
    
    for(int i=0;i<_piece;i++){
        _Pic[i] = (Sprite *)Sprite::createWithSpriteFrameName(Img);
        _Pic[i]->setScale(scale);
        
        _obj->addChild(_Pic[i]);
    }

    _fscale = scale;
    
    setPosition(pos[0]);
    setRotation(r);
    
    _bTouched = false;
    _bRotated = false;
    _bVisible = _bEnabled = true;
}



void TCircleSprite::setCollisionInfo(float totalPiece) {
    float a = 360 / totalPiece;
    ImgRadius = _Pic[0]->getContentSize().height * _fscale;
    ImgAngle = a;
    
    float r=_fangle+90;
    Point pos = Point(0.5f * ImgRadius * cosf(ANGLE(r)) + _SpriteLoc.x, 0.5f * ImgRadius * sinf(ANGLE(r)) + _SpriteLoc .y);
    setPosition(pos);
}

