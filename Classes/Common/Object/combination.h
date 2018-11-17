#ifndef combination_h
#define combination_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "TouchSprite.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

struct StickyData 
{
	float angle;
	Point pos;
	bool isSticky = false;
};

class combination : public cocos2d::Node
{
private:
    TouchSprite *img;
    int n;  //�Ϥ��ƶq
	int touchedAmount; //�Q�I�����ƶq
	TouchSprite *rotateImg;
	Point rotatePos;
	int rotateId;

	StickyData *_StickyData;
	float _StickyRadius;        //���K�b�|
	void Sticky(TouchSprite*);
public:
    combination(const char *name, float scale);
	~combination();
    void touchesBegin(cocos2d::Point inPos, int id);
    bool touchesMoved(cocos2d::Point inPos, int id);
    void touchesEnded(cocos2d::Point inPos, int id);
};
#endif /* combination_h */
