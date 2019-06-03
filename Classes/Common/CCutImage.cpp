#include "CCutImage.h"
#include "../Data.h"
#include <cmath>

#define IMG_ANGLE 90 //圖片原角度

#define ANGLE(a) a*M_PI/180 //角度轉弧度

#define POS Vec2(500,650)

enum IMG_STATUS { NONE = 0, MOVE = 1, EXIT = 2 };

CCutImage::CCutImage(const char *name, float scale,int num) {
	char picname[20];
	sprintf(picname, "%s.png",name);
	_fullImg = (Sprite *)Sprite::createWithSpriteFrameName(picname);
	_fullImg->setPosition(POS);
	_fullImg->setScale(scale);
	addChild(_fullImg, BOTTOM_LEVEL);

	_n = num;
	_name = name;
	_scale = scale;
	_divided = false;
    
    sprintf(picname, "%s%d.png", _name, _n);
    _n = num;
    img = new TouchSprite[_n];
    _StickyData = new StickyData[_n];
    for (int i = 0; i < _n; i++) {
        img[i].setSectorButtonInfo(picname, _scale);
        float angle = (360 / _n)*i;
        img[i].setRotation(angle);
        angle += IMG_ANGLE;
        img[i].SetPosition(Point(0.5f * img[i].ImgRadius * cosf(ANGLE(angle)) + POS.x, 0.5f * img[i].ImgRadius * sinf(ANGLE(angle)) + POS.y));
        img[i].ImgAngle = 360 / _n;
        addChild(img[i].getImg(), BOTTOM_LEVEL);
        
        img[i].setSticky(i);
        _StickyData[i].angle = angle - IMG_ANGLE;
        _StickyData[i].pos = img[i].getPosition();
        _StickyData[i].isSticky = true;
        
        img[i].setVisible(false);
    }
    
    _StickyRadius = powf(img[0].ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;

}

CCutImage::~CCutImage()
{
    if (_n != 0) {
        for (int i = 0; i < _n; i++) removeChild(img[i].getImg());
        delete [] img;
        delete [] _StickyData;
    }
}


void CCutImage::divide(bool d) {
    if(d){
        _fullImg->setOpacity(100);
    }else{
        _fullImg->setOpacity(255);
        for(int i = 0; i < _n; i++){
            img[i].SetPosition(_StickyData[i].pos);       //設定圖片位置與角度
            img[i].setRotation(_StickyData[i].angle);
            img[i].setSticky(i);                          //紀錄區域
            _StickyData[i].isSticky = true;
        }
    }
    
    for(int i = 0; i < _n; i++)img[i].setVisible(d);
    
    _divided = d;


}

bool CCutImage::touchesBegin(cocos2d::Point inPos, int id) {
	if (!_divided)return false;

	for (int i = 0; i < _n ; i++) {
		if (img[i].touchesBegin(inPos, id)) {
			if (rotateImg == NULL) {
				rotateImg = &img[i];
				if (rotateId != -1) rotateImg->RotatedBegin(rotatePos, rotateId);  //先點到外 在點到圖上
			}
			int sticky = img[i].ResetSticky();        //重製磁鐵.釋放區域
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

	for (int i = 0; i < _n; i++) {                   //當一般點移動
		int status = img[i].touchesMoved(inPos, id);

		if (status == MOVE)  return true;

	}
	if (rotateId == id) rotatePos = inPos;
	return false;
}

void CCutImage::touchesEnded(cocos2d::Point inPos, int id) {
	if (!_divided)return;

	for (int i = 0; i < _n; i++) {
		if (img[i].touchesEnded(inPos, id)) {
			if (rotateImg == &img[i]) rotateImg = NULL;
			Sticky(&img[i]);  //判斷是否吸上去
		}
	}
	if (rotateId == id)rotateId = -1;
}

void CCutImage::Sticky(TouchSprite *img) {
	float x, y, d;
	x = img->getPosition().x - POS.x;
	y = img->getPosition().y - POS.y;
	d = powf(x, 2) + powf(y, 2);
	if (d < _StickyRadius) {    //位置靠近磁鐵區域
		int stickyPos = -1;
		float angle = img->getAngle();
		float preDAngle = 1000, DAngle;
		for (int i = 0; i < _n; i++) {        //判斷和哪個角度最靠近 
			if (_StickyData[i].isSticky == false) {
				DAngle = abs(_StickyData[i].angle - angle);   //算角度差
				if (DAngle < preDAngle) {            //如果比上次資料小  紀錄這次資料
					preDAngle = DAngle;
					stickyPos = i;
				}
			}
		}
		img->SetPosition(_StickyData[stickyPos].pos);       //設定圖片位置與角度
		img->setRotation(_StickyData[stickyPos].angle);
		img->setSticky(stickyPos);                          //紀錄區域
		_StickyData[stickyPos].isSticky = true;
	}
}

