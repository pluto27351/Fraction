#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"

using namespace cocos2d::ui;

USING_NS_CC;

class TouchSprite
{
private:
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

	void ImgRotate(Point touch);

	bool SectorCollision(Point touch);
public:
	float ImgAngle;
	float ImgRadius;

	void setSectorButtonInfo(const char *Img, float scale);
	void setRotation(float r);

	bool touchesBegin(cocos2d::Point inPos, int id);
	int touchesMoved(cocos2d::Point inPos, int id);
	bool touchesEnded(cocos2d::Point inPos, int id);

	void RotatedBegin(cocos2d::Point inPos, int id);
	void RotateMoved();
	void RotateEnded(int i);


	Sprite *getImg();

	void SetPosition(Point pos);
	Point getPosition() { return _SpriteLoc; }
	float getAngle() { return (_fangle); }
	void setSticky(int stickyNumber);
	int ResetSticky();
    void setVisible(bool b);
};
