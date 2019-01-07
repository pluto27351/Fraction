#include "combination.h"
#include <cmath>

#define IMG_ANGLE 90 //圖片原角度

#define ANGLE(a) a*M_PI/180 //角度轉弧度

#define POS Vec2(400,700)

enum IMG_STATUS {NONE = 0, MOVE = 1, EXIT = 2};

combination::combination(const char *name, float scale){
    std::string num;
    num.assign(name,strlen(name)-6,2);
    n = ((int)num[0]-48)*10 + (int)num[1]-48;//圖片數量
    img = new TouchSprite[n];
	_StickyData = new StickyData[n];
    for(int i=0;i<n;i++){
		img[i].setSectorButtonInfo(name, scale);
		float angle = (360 / n)*i;
		img[i].setRotation(angle);
		angle +=  IMG_ANGLE;
		img[i].SetPosition(Point(0.5f * img[i].ImgRadius * cosf(ANGLE(angle)) + POS.x, 0.5f * img[i].ImgRadius * sinf(ANGLE(angle)) + POS.y));
		img[i].ImgAngle = 360/n;
        addChild(img[i].getImg());

		img[i].setSticky(i);
		_StickyData[i].angle = angle - IMG_ANGLE;
		_StickyData[i].pos = img[i].getPosition();
		_StickyData[i].isSticky = true;
    }

	_StickyRadius = powf(img[0].ImgRadius,2);
	touchedAmount = 0; //被點擊的數量
	rotateImg = NULL;
	rotateId = -1;

}

combination::~combination()
{
    
}


void combination::touchesBegin(cocos2d::Point inPos, int id){
	bool touch = false;
    for(int i=0;i<n && !touch;i++){
//		d[i] = inPos - img[i].getImg()->getPosition(); //紀錄點擊與圖片中心距離(搬進touchSprite)
		if (img[i].touchesBegin(inPos, id)) {
			touch = true;
			if (rotateImg == NULL) {
				rotateImg = &img[i];
				if(rotateId != -1) rotateImg->RotatedBegin(rotatePos, rotateId);  //先點到外 在點到圖上
			}
			int sticky = img[i].ResetSticky();        //重製磁鐵.釋放區域
			if (sticky != -1) _StickyData[sticky].isSticky = false;  
		}
    }
	if (touch == false) {
		if(rotateImg != NULL)rotateImg->RotatedBegin(inPos, id);
		else {
			rotateId = id;  rotatePos = inPos;  //沒有任何圖片被點到
		}
	}

}

bool combination::touchesMoved(cocos2d::Point inPos, int id) {
	for (int i = 0; i < n; i++) {                   //當一般點移動
		int status = img[i].touchesMoved(inPos, id);

		if (status == MOVE)  return true;
//        else if (status == EXIT) {
//            if (rotateImg == &img[i]) rotateImg = NULL;
//            return false;
//        }
	}
	if (rotateId == id) rotatePos = inPos;
	return false;
}

void combination::touchesEnded(cocos2d::Point inPos, int id){
	for (int i = 0; i<n; i++) {
		if (img[i].touchesEnded(inPos, id)) {
			if (rotateImg == &img[i]) rotateImg = NULL;
			Sticky(&img[i]);  //判斷是否吸上去
		}
	}
	if (rotateId == id)rotateId = -1;
}

void combination::Sticky(TouchSprite *img) {
	float x, y, d;
	x = img->getPosition().x - POS.x;
	y = img->getPosition().y - POS.y;
	d = powf(x, 2) + powf(y, 2);
	if (d < _StickyRadius) {    //位置靠近磁鐵區域
		int stickyPos=-1;
		float angle = img->getAngle();
		float preDAngle=1000, DAngle;
		for (int i = 0; i < n ; i++) {        //判斷和哪個角度最靠近 
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
		_StickyData[stickyPos].isSticky  = true;
	}
}

