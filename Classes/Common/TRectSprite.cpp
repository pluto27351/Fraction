#include "TRectSprite.h"

#define IMG_ANGLE 90

#define ANGLE(a) a*M_PI/180
#define RE_ANGLE(a) a*180/M_PI

bool TRectSprite::Collision(Point touch) {
//    Point _CenterLoc;
//    float td, ta;
//    float tx, ty;
//    _CenterLoc.x = _Pic->getPosition().x - ImgRadius / 2 * cosf(ANGLE((_fangle + IMG_ANGLE)));
//    _CenterLoc.y = _Pic->getPosition().y - ImgRadius / 2 * sinf(ANGLE((_fangle + IMG_ANGLE)));
//    tx = touch.x - _CenterLoc.x;
//    ty = touch.y - _CenterLoc.y;
//    td = sqrtf(powf(tx, 2) + powf(ty, 2));
//    ta = atanf(ty / tx);
//    ta = RE_ANGLE(ta) + 90;
//    if (tx > 0)ta = ta + 180;
//    //    if (ta > 360 - ImgAngle / 2)ta -= 360;
//    float f_min = _fangle - ImgAngle / 2, f_max = _fangle + ImgAngle / 2;
//    if (td <= ImgRadius) {
//        if (ta >= f_min && ta <= f_max)return true;
//        if (f_min < 0 && ta > 360 + f_min)return true;
//        if (f_max > 360 && ta < f_max - 360)return true;
//    }
//    return false;
    auto posInNode = _Pic->convertToNodeSpace(touch);
    if (Rect(0,0,_Pic->getContentSize().width,_Pic->getContentSize().height).containsPoint(posInNode))
    {
        CCLOG("IN");
        return true;
    }else{
        CCLOG("OUT");
        return false;
    }

}

void TRectSprite::setImgInfo(const char *Img, float scale,Point pos,float r)
{
    _Pic = (Sprite *)Sprite::createWithSpriteFrameName(Img);
    _Pic->setScale(scale);
    _fscale = scale;
    
    setPosition(pos);
    setRotation(r);
    
    _bTouched = false;
    _bRotated = false;
    _bVisible = _bEnabled = true;
}



void TRectSprite::setCollisionInfo(float a) {
    ImgRadius = _Pic->getContentSize().height * _fscale;
    ImgAngle = a;
    float r=_fangle+90;
   // Point pos = Point(0.5f * ImgRadius * cosf(ANGLE(r)) + _SpriteLoc.x, 0.5f * ImgRadius * sinf(ANGLE(r)) + _SpriteLoc .y);
   // setPosition(pos);

}

