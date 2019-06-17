#include "CCutImage.h"
#include "../Data.h"
#include <cmath>

#define IMG_ANGLE 90 //圖片原角度

#define ANGLE(a) a*M_PI/180 //角度轉弧度

#define POS Vec2(500,650)

//enum IMG_STATUS { NONE = 0, MOVE = 1, ROT = 2, EXIT = 3 };
enum Object{PANCAKE,PAPER,WATER,BAMBOO,RIBBON,DISTANCE,BANANA,GRAPE,FLOWER,BRANCH,NUT,TOMATO};

CCutImage::~CCutImage()
{
    if (_totalPiece != 0) {
        for (int i = 0; i < _totalPiece; i++) removeChild(img[i]->getImg());
        delete [] img;
        delete [] _StickyData;
    }
}


//CCutImage::CCutImage(const char *name, float scale,int num) {
//    char picname[20];
//    sprintf(picname, "%s.png",name);
//    _fullImg = (Sprite *)Sprite::createWithSpriteFrameName(picname);
//    _fullImg->setPosition(POS);
//    _fullImg->setScale(scale);
//    addChild(_fullImg, BOTTOM_LEVEL);
//
//    _totalPiece = _dividePiece = num;
//    _name = name;
//    _scale = scale;
//    _divided = false;
//
//    sprintf(picname, "%s%d.png", _name, _totalPiece);
//    img = new TouchSprite*[_totalPiece];
//    _StickyData = new StickyData[_totalPiece];
//    for (int i = 0; i < _totalPiece; i++) {
//        img[i] = new TCircleSprite;
//        float angle = (360 / _totalPiece)*i;
//        img[i]->setImgInfo(picname, _scale,POS,angle);
//        img[i]->setCollisionInfo(360 / _totalPiece);
//
//        addChild(img[i]->getImg(), BOTTOM_LEVEL);
//
//        img[i]->setSticky(i);
//        _StickyData[i].angle = angle;
//        _StickyData[i].pos = img[i]->getPosition();
//        _StickyData[i].isSticky = true;
//
//        img[i]->setVisible(false);
//    }
//
//    _StickyRadius = powf(img[0]->ImgRadius, 2);
//    touchedAmount = 0; //被點擊的數量
//    rotateImg = NULL;
//    rotateId = -1;
//
//}

CCutImage::CCutImage(int picNum, float scale,int num) {

    switch (picNum) {
        case PANCAKE:
            _name = "stuff_muffin";
            _mode = 0;
            CreateImg(scale,num);
            break;
        case PAPER:
            break;
        case WATER:
            break;
        case BAMBOO:
            break;
        case RIBBON:
            break;
        case DISTANCE:
            break;
        case BANANA:
            _name = "bnn";
            _cutDir = Vec2(50,0);
            _mode = 1;
            CreateImg2(scale,num);
            break;
        case GRAPE:
            break;
        case FLOWER:
            break;
        case BRANCH:
            break;
        case NUT:
            _name = "nut";
            _cutDir = Vec2(50,0);
            _mode = 1;
            CreateImg2(scale,num);
            break;
        case TOMATO:
            break;
    }

}

void CCutImage::CreateImg2(float scale,int num){   //非連續物件
    char picname[20];
    Point pos;
    sprintf(picname, "ani/%s.csb",_name);
    auto obj = CSLoader::createNode(picname);
    
    _fullImg = obj;
    _fullImg ->setPosition(POS);
    addChild(_fullImg , BOTTOM_LEVEL);
    
    _dividePiece = num;
    _totalPiece = obj->getChildByName("0")->getTag();
    _scale = scale;
    _divided = false;

    sprintf(picname, "%s_1.png", _name, _totalPiece);
    img = new TouchSprite*[_totalPiece];
    _StickyData = new StickyData[_totalPiece];
    
    for (int i = 0; i < _totalPiece; i++) {
        char p[10];  sprintf(p, "1_%d",i);
        pos = obj->getChildByName(p)->getPosition() + POS;
        float angle = obj->getChildByName(p)->getRotation();
        
        img[i] = new TRectSprite;
        img[i]->setImgInfo(picname, _scale,pos,angle);
        img[i]->setCollisionInfo(_totalPiece);
        
        addChild(img[i]->getImg(), BOTTOM_LEVEL);
        
        img[i]->setSticky(i);
        _StickyData[i].angle = angle;
        _StickyData[i].pos = img[i]->getPosition();
        _StickyData[i].isSticky = true;
        
        img[i]->setVisible(false);
    }
    
    setCutPos();
    
    _StickyRadius = powf(img[0]->ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
}

void CCutImage::CreateImg(float scale,int num){  // 圓形
    char picname[20];
    sprintf(picname, "%s.png",_name);
    _fullImg = (Sprite *)Sprite::createWithSpriteFrameName(picname);
    _fullImg->setPosition(POS);
    _fullImg->setScale(scale);
    addChild(_fullImg, BOTTOM_LEVEL);
    
    _totalPiece = _dividePiece = num;
    _scale = scale;
    _divided = false;
    
    sprintf(picname, "%s%d.png", _name, _totalPiece);

    img = new TouchSprite*[_totalPiece];
    _StickyData = new StickyData[_totalPiece];
    for (int i = 0; i < _totalPiece; i++) {
        img[i] = new TCircleSprite;
        float angle = (360 / _totalPiece)*i;
        img[i]->setImgInfo(picname, _scale,POS,angle);
        img[i]->setCollisionInfo(_totalPiece);
        
        addChild(img[i]->getImg(), BOTTOM_LEVEL);
        
        img[i]->setSticky(i);
        _StickyData[i].angle = angle;
        _StickyData[i].pos = img[i]->getPosition();
        _StickyData[i].isSticky = true;
        
        img[i]->setVisible(false);
    }
    
    _StickyRadius = powf(img[0]->ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
}



void CCutImage::setCutPos(){                  //計算切分時位置
    switch(_mode){
        case 0:  //圓形用
            for(int i = 0; i < _totalPiece; i++){
                img[i]->setPosition(_StickyData[i].pos);
                img[i]->setRotation(_StickyData[i].angle);
                img[i]->setSticky(i);
                _StickyData[i].isSticky = true;
            }
            break;
        case 1: //非連續用
            int group = _totalPiece / _dividePiece;
            float y = (_dividePiece - 1) / 2.0;
            Vec2 move;
            if(_dividePiece % 2 == 0){
                for (int i = 0; i < _totalPiece; i++) {
                    int gNum = i / group;
                    move = _cutDir * (gNum - y);
                    img[i]->setPosition(_StickyData[i].pos + move);
                    img[i]->setSticky(-1);
                    _StickyData[i].isSticky = false;
                }
            }else{
                for (int i = 0; i < _totalPiece; i++) {
                    int gNum = i / group;
                    if(gNum < y) move = _cutDir * (gNum - y);
                    else         move = _cutDir * (gNum - y + 1);
                    img[i]->setPosition(_StickyData[i].pos + move);
                    img[i]->setSticky(-1);
                    _StickyData[i].isSticky = false;
                }
            }
            break;
    }
    
}

void CCutImage::divide(bool d) {
    if(d){
        _fullImg->setOpacity(100);
    }else{
        _fullImg->setOpacity(255);
    }
    
    setCutPos();
    for(int i = 0; i < _totalPiece; i++){
        img[i]->setVisible(d);
    }
    
    _divided = d;


}

bool CCutImage::touchesBegin(cocos2d::Point inPos, int id) {
	if (!_divided)return false;

	for (int i = 0; i < _totalPiece ; i++) {
		if (img[i]->touchesBegin(inPos, id)) {
			if (rotateImg == NULL) {
				rotateImg = img[i];
			}
			int sticky = img[i]->ResetSticky();        //重製磁鐵.釋放區域
			if (sticky != -1) _StickyData[sticky].isSticky = false;

			return true;
		}
	}

	if (rotateImg != NULL) {
		rotateImg->RotatedBegin(inPos, id); 
		return true;
	}

	
	return false;

}

bool CCutImage::touchesMoved(cocos2d::Point inPos, int id) {
	if (!_divided)return false;

	for (int i = 0; i < _totalPiece; i++) {                   //當移動or旋轉
        if( img[i]->touchesMoved(inPos, id)) return true;
	}
	return false;
}

void CCutImage::touchesEnded(cocos2d::Point inPos, int id) {
	if (!_divided)return;

	for (int i = 0; i < _totalPiece; i++) {
		if (img[i]->touchesEnded(inPos, id)) {
			if (rotateImg == img[i]) rotateImg = NULL;
			Sticky(img[i]);  //判斷是否吸上去
		}
	}
	//if (rotateId == id)rotateId = -1;
}

void CCutImage::Sticky(TouchSprite *img) {
	float x, y, d;
	x = img->getPosition().x - POS.x;
	y = img->getPosition().y - POS.y;
	d = powf(x, 2) + powf(y, 2);
	if (d < _StickyRadius) {    //位置靠近磁鐵區域
		int stickyNum = -1;
		float angle = img->getAngle();
		float preDAngle = 1000, DAngle;
		for (int i = 0; i < _totalPiece; i++) {        //判斷和哪個角度最靠近
			if (_StickyData[i].isSticky == false) {
				DAngle = abs(_StickyData[i].angle - angle);   //算角度差
				if (DAngle < preDAngle) {            //如果比上次資料小  紀錄這次資料
					preDAngle = DAngle;
					stickyNum = i;
				}
			}
		}
		img->setPosition(_StickyData[stickyNum].pos);       //設定圖片位置與角度
		img->setRotation(_StickyData[stickyNum].angle);
		img->setSticky(stickyNum);                          //紀錄區域
		_StickyData[stickyNum].isSticky = true;
	}
}

