#pragma once

#include "TouchSprite.h"

class TCircleSprite:public TouchSprite{
private:
    bool Collision(Point touch);
    
    float ImgAngle;
    
public:
    ~TCircleSprite();
    void setImgInfo(const char *Img,int piece,Point pos[],float r[],Vec2 scale);
    void setCollisionInfo(float totalPiece);

};

