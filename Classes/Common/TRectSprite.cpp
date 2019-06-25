#include "TRectSprite.h"

#define IMG_ANGLE 90

#define ANGLE(a) a*M_PI/180
#define RE_ANGLE(a) a*180/M_PI

bool TRectSprite::Collision(Point touch) {
    for(int i=0;i<_piece;i++){
        auto posInNode = _Pic[i]->convertToNodeSpace(touch);
        if (Rect(0,0,_Pic[i]->getContentSize().width,_Pic[i]->getContentSize().height).containsPoint(posInNode))
        {
            CCLOG("IN");
            return true;
        }else{
            CCLOG("OUT");
            //return false;
        }
    }
}

void TRectSprite::setImgInfo(const char *Img,int piece, float scale,Point pos[],float r)
{
    _obj = new Node;
    
    _piece = piece;
    _Pic = new Sprite *[_piece];
    for(int i=0;i<_piece;i++){
        _Pic[i] = (Sprite *)Sprite::createWithSpriteFrameName(Img);
        _Pic[i]->setScale(scale);
        Point pp =pos[i];
        _Pic[i]->setPosition(pp);
       
        _obj->addChild(_Pic[i]);
    }
    _fscale = scale;
    
   // setPosition(pos);
    setRotation(r);
    
    _bTouched = false;
    _bRotated = false;
    _bVisible = _bEnabled = true;
}



void TRectSprite::setCollisionInfo(float totalPiece) {
    float a = 360/ totalPiece;
    ImgRadius = _Pic[0]->getContentSize().height * _fscale;


}

