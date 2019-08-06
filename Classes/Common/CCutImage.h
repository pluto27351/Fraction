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
    
    void setSticky(int num){
        _num = num;
        isSticky = true;
    }
    
    void deleteImgData(){
        delete [] _imgAngle;
        delete [] _imgPos;
    }
};

class CCutImage : public cocos2d::Node
{
private:
	TouchSprite *img;        //切塊圖片們
	TouchSprite *rotateImg;  //指定被旋轉圖片
    std::vector<Sprite*> _fullImg;          //完整圖片
    std::vector<Sprite*> _line;
    int _fullAmount;
    
    Vec2 _pos,_dPos;
    float _scale;
    int _mode;
    bool _divided;
    bool _hasline = false;
	const char *_name;
	int _dividePiece;        //切幾組
	
	int touchedAmount;       //觸控點數量
	Point rotatePos;
	int rotateId;
    
    GLProgramState *grayGLProgrameState,*colorGLProgrameState;
    
    GLProgram *shader_program;
    
	StickyData *_StickyData;    
	float _StickyRadius;        
    void Sticky(TouchSprite*,int,Point);
    void setCutPos();
public:
    ~CCutImage();

    CCutImage(int picNum,int NodeAmount, float scale,int dividedP,int c = 0);
    CCutImage(int picNum,float scale,int dividedP,int a,int b);
    
    void CreatePancake(float scale,int num);
    void CreateNormalImg(float scale,int num,int c);
    void CreateFlower(float scale,int num,int c);
    void CreatePaper(float scale,int num);
    void CreateWater(float scale,int num);
    void CreatelinePic(float scale,int num,int a,int b,int c);
    
	void divide(bool);
    void setCutmode(int);
    
	bool touchesBegin(cocos2d::Point inPos, int id);
	bool touchesMoved(cocos2d::Point inPos, int id);
	void touchesEnded(cocos2d::Point inPos, int id);
};
#endif /* CCutImage_h */
