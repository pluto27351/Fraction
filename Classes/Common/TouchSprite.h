#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"

using namespace cocos2d::ui;

USING_NS_CC;

class TouchSprite
{
protected:
    std::vector<Sprite*> _Pic;
	cocos2d::Point _SpriteLoc;
    Node *_obj;
	float _fangle;

    int _piece;
    int _cutMode;
    
	bool _bTouched;
	bool _bRotated;
	bool _bEnabled;
	bool _bVisible;

	Point d;

	int touchID[2] = { -1,-1 };
	Point touchPos[2];

	float _PreRotate;

	int _StickyNumber = -1;

    virtual bool Collision(Point touch){};
    
public:
    float ImgRadius;

    virtual ~TouchSprite();
    
    virtual void setImgInfo(const char *Img,int piece,Point pos[],float r[],Vec2 scale){};
    virtual void setImgInfo_flower(int num,int piece,Point pos[],float r[],Vec2 scale){};
    virtual void setCollisionInfo(float totalPiece){};

	bool touchesBegin(cocos2d::Point inPos, int id);
	bool touchesMoved(cocos2d::Point inPos, int id);
	bool touchesEnded(cocos2d::Point inPos, int id);

	void RotatedBegin(cocos2d::Point inPos, int id);
	void RotateMoved();
	void RotateEnded(int i);

    Node *getNode(){return _obj;}
    

	void setPosition(Point pos);
    void setImgPandR(int n,Point pos,float r);
    void setRotation(float r);
    
    void setDividedImg();
    void normalDivide();
    void SameHeightDivide();
    
	Point getPosition() { return _SpriteLoc; }
	float getAngle() { return (_fangle); }
	void setSticky(int stickyNumber);
	int ResetSticky();
    void setVisible(bool b);
    int getPieceAmount(){return _piece;}
    int getPicWidth(){return (_Pic[0]->getContentSize().width);}
};
