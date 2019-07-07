#include "TRectSprite.h"

#define IMG_ANGLE 90

#define ANGLE(a) a*M_PI/180
#define RE_ANGLE(a) a*180/M_PI

TRectSprite::~TRectSprite(){
    CCLOG("delete TCircleSprite");
    _Pic.clear();
    
}

bool TRectSprite::Collision(Point touch) {
    for(int i=0;i<_piece;i++){
        auto posInNode = _Pic[i]->convertToNodeSpace(touch);
        if (Rect(0,0,_Pic[i]->getContentSize().width+8,_Pic[i]->getContentSize().height+8).containsPoint(posInNode))
        {
            return true;
        }
//      else{
//            //return false;
//      }
    }
}

void TRectSprite::setImgInfo(const char *Img,int piece,Point pos[],float r[])
{
    _obj = new Node;
    _piece = piece;
    
    for(int i=0;i<_piece;i++){
        auto pic = (Sprite *)Sprite::createWithSpriteFrameName(Img);
        pic->setScale(1);
        _obj->addChild(pic);
        _Pic.push_back(pic);
        
    }
    
    _fscale = 1;
    
   // setPosition(pos);
   // setRotation(r);
    
    _bTouched = false;
    _bRotated = false;
    _bVisible = _bEnabled = true;
}



void TRectSprite::setCollisionInfo(float totalPiece) {
    float a = 360/ totalPiece;
    ImgRadius = _Pic[0]->getContentSize().height * _fscale;


}

