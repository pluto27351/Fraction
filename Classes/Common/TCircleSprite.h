#pragma once

#include "TouchSprite.h"

class TCircleSprite:public TouchSprite{
private:
    bool Collision(Point touch);
    
    float ImgAngle;
    
public:
    void setImgInfo(const char *Img,int piece, float scale,Point pos[],float r[]);
    void setCollisionInfo(float totalPiece);
    ~TCircleSprite(){};
};

