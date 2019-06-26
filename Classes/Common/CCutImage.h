#ifndef CCutImage_h
#define CCutImage_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "TouchSprite.h"
#include "TCircleSprite.h"
#include "TRectSprite.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;



struct StickyData  //磁鐵資訊
{
	float _NodeAngle;
	Point _NodePos;
    float *_imgAngle;
    Point *_imgPos;
    int _num;
	bool isSticky = false;
    
    void createImgData(int num){
        _num = num;
        _imgAngle = new float [num];
        _imgPos = new Point [num];
    }
    
    void deleteImgData(){
        delete [] _imgAngle;
        delete [] _imgPos;
    }
};

class CCutImage : public cocos2d::Node
{
private:
	TouchSprite **img;        //切塊圖片們
	TouchSprite *rotateImg;  //指定被旋轉圖片
    Sprite *_fullImg[2];          //完整圖片
    
    float _scale;
    Vec2 _cutDir;
    int _mode;
    bool _divided;
    
	const char *_name;
	int _dividePiece;        //切幾組
	
	int touchedAmount;       //觸控點數量
	Point rotatePos;
	int rotateId;
    
    GLProgramState *grayGLProgrameState,*colorGLProgrameState;
    
	StickyData *_StickyData;    
	float _StickyRadius;        
	void Sticky(TouchSprite*);
    void setCutPos();
public:
	CCutImage(const char *name, float scale,int num);
    CCutImage(int picNum,float scale,int num);
    void CreateImg(float scale,int num);
    void CreateImg2(float scale,int num);
	~CCutImage();
	void divide(bool);
	bool touchesBegin(cocos2d::Point inPos, int id);
	bool touchesMoved(cocos2d::Point inPos, int id);
	void touchesEnded(cocos2d::Point inPos, int id);
};
#endif /* CCutImage_h */
