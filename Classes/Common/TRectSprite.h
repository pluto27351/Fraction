#pragma once

#include "TouchSprite.h"

class TRectSprite:public TouchSprite{
private:
    bool Collision(Point touch);
    float ImgAngle;
public:
    void setImgInfo(const char *Img, float scale,Point pos,float r);
    void setCollisionInfo(float a);
    ~TRectSprite(){};
};

