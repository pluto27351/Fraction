#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"

using namespace cocos2d::ui;

USING_NS_CC;

class TouchSprite
{
protected:
	cocos2d::Sprite *_Pic;
	cocos2d::Point _SpriteLoc;
	float _fangle;
	float _fscale;

	bool _bTouched;
	bool _bRotated;
	bool _bEnabled;
	bool _bVisible;

	Point d;

	int touchID[2] = { -1,-1 };
	Point touchPos[2];

	float _PreRotate;

	int _StickyNumber = -1;


	//bool SectorCollision(Point touch);
    virtual bool Collision(Point touch){};
    
public:
	//float ImgAngle;
    float ImgRadius;

	//void setSectorButtonInfo(const char *Img, float scale);
	//void setRotation(float r);
    ~TouchSprite(){};
    
    virtual void setImgInfo(const char *Img, float scale,Point pos,float r){};
    virtual void setCollisionInfo(float a){};

	bool touchesBegin(cocos2d::Point inPos, int id);
	bool touchesMoved(cocos2d::Point inPos, int id);
	bool touchesEnded(cocos2d::Point inPos, int id);

	void RotatedBegin(cocos2d::Point inPos, int id);
	void RotateMoved();
	void RotateEnded(int i);


	Sprite *getImg();

	void setPosition(Point pos);
    void setRotation(float r);
    
	Point getPosition() { return _SpriteLoc; }
	float getAngle() { return (_fangle); }
	void setSticky(int stickyNumber);
	int ResetSticky();
    void setVisible(bool b);
};
