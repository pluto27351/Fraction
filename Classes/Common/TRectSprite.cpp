#include "TRectSprite.h"

#define IMG_ANGLE 90

#define ANGLE(a) a*M_PI/180
#define RE_ANGLE(a) a*180/M_PI

bool TRectSprite::Collision(Point touch) {
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



void TRectSprite::setCollisionInfo(float totalPiece) {
    float a = 360/ totalPiece;
    ImgRadius = _Pic->getContentSize().height * _fscale;
//    ImgAngle = a;
//    float r=_fangle+90;
   // Point pos = Point(0.5f * ImgRadius * cosf(ANGLE(r)) + _SpriteLoc.x, 0.5f * ImgRadius * sinf(ANGLE(r)) + _SpriteLoc .y);
   // setPosition(pos);

}

