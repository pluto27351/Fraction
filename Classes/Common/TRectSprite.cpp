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
        float w = _Pic[i]->getContentSize().width * _Pic[i]->getScaleX();
        float h = _Pic[i]->getContentSize().height * _Pic[i]->getScaleY();
        if (Rect(0,0,w+8,h+8).containsPoint(posInNode))
        {
            return true;
        }
    }
}

void TRectSprite::setImgInfo(const char *Img,int piece,Point pos[],float r[],Vec2 scale)
{
    _obj = new Node;
    _piece = piece;
    
    for(int i=0;i<_piece;i++){
        auto pic = (Sprite *)Sprite::createWithSpriteFrameName(Img);
        pic->setScale(scale.x,scale.y);
        pic->setPosition(pos[i]);
        pic->setRotation(r[i]);
        _obj->addChild(pic);
        _Pic.push_back(pic);
        
    }

    
    _bTouched = false;
    _bRotated = false;
    _bVisible = _bEnabled = true;
}

void TRectSprite::setImgInfo_flower(int num,int piece,Point pos[],float r[],Vec2 scale)
{
    _obj = new Node;
    _piece = piece;
    char picname[20];
    
    for(int i=0;i<_piece;i++){
        sprintf(picname, "flower_%d.png",num*piece + i +2);
        auto pic = (Sprite *)Sprite::createWithSpriteFrameName(picname);
        pic->setScale(scale.x,scale.y);
        pic->setPosition(pos[i]);
        pic->setRotation(r[i]);
        _obj->addChild(pic);
        _Pic.push_back(pic);
        
    }

    _bTouched = false;
    _bRotated = false;
    _bVisible = _bEnabled = true;
}

void TRectSprite::setImgInfo_water(Point pos[],float r[],Vec2 scale)
{
    _obj = new Node;
    _piece = 2;
    char picname[20];

    sprintf(picname, "water_2.png");
    auto pic = (Sprite *)Sprite::createWithSpriteFrameName(picname); // pic[0]=水
    pic->setScale(scale.x,scale.y);
    float y = (pic->getContentSize().height - 4)*pic->getScaleY() /2;
    pic->setPosition(pos[0]);
    pic->setRotation(r[0]);
    _obj->addChild(pic);
    _Pic.push_back(pic);

    sprintf(picname, "water_0.png");
    pic = (Sprite *)Sprite::createWithSpriteFrameName(picname); // pic[１]=水杯
    pic->setPosition(Vec2(0,0));
    pic->setRotation(r[0]);
    _obj->addChild(pic);
    _Pic.push_back(pic);

    _bTouched = false;
    _bRotated = false;
    _bVisible = _bEnabled = true;
}

void TRectSprite::setCollisionInfo(float totalPiece) {
    float a = 360/ totalPiece;
    ImgRadius = _Pic[0]->getContentSize().height * _Pic[0]->getScaleY();


}



    

