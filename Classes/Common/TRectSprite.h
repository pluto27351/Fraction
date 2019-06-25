#pragma once

#include "TouchSprite.h"

class TRectSprite:public TouchSprite{
private:
    bool Collision(Point touch);
    
public:
    void setImgInfo(const char *Img,int piece, float scale,Point pos[],float r);
    void setCollisionInfo(float totalPiece);
    ~TRectSprite(){};
};

