#pragma once

#include "TouchSprite.h"

class TRectSprite:public TouchSprite{
private:
    bool Collision(Point touch);
    
public:
    ~TRectSprite();
    void setImgInfo(const char *Img,int piece,Point pos[],float r[],Vec2 scale);
    void setImgInfo_flower(int num,int piece,Point pos[],float r[],Vec2 scale);
    void setImgInfo_water(Point pos[],float r[],Vec2 scale);
    void setCollisionInfo(float totalPiece);

};

