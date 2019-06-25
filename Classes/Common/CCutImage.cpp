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
    if (_dividePiece != 0) {
       // for (int i = 0; i < _totalPiece; i++) removeChild(img[i]);
        delete [] img;
        delete [] _StickyData;
    }
}

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
            _name = "banboo";
            _cutDir = Vec2(0,-50);
            _mode = 1;
            CreateImg2(scale,num);
            break;
        case RIBBON:
            _name = "banboo";
            _cutDir = Vec2(0,-50);
            _mode = 2;
            CreateImg2(scale,num);
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
            _name = "bnn";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,num);
            break;
        case FLOWER:
            _name = "tree";
            _cutDir = Vec2(50,0);
            _mode = 1;
            CreateImg2(scale,num);
            break;
        case BRANCH:
            _name = "tree";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,num);
            break;
        case NUT:
            _name = "nut";
            _cutDir = Vec2(50,0);
            _mode = 1;
            CreateImg2(scale,num);
            break;
        case TOMATO:
            _name = "nut";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,num);
            break;
    }

}

void CCutImage::CreateImg2(float scale,int num){   //非連續物件
    char picname[20];
    sprintf(picname, "ani/%s.csb",_name);
    auto obj = CSLoader::createNode(picname);
    
    _fullImg = obj;
    _fullImg ->setPosition(POS);
    addChild(_fullImg , BOTTOM_LEVEL);
    
    _dividePiece = num;
    _scale = scale;
    _divided = false;
    
    int totalPiece = obj->getChildByName("0")->getTag();

    int gPicec = totalPiece / _dividePiece;
    Point *pos = new Point[gPicec];
    img = new TouchSprite*[_dividePiece];
    _StickyData = new StickyData[_dividePiece];

    sprintf(picname, "%s_1.png", _name);
    int n=0;
    
    Point totalPos;
    float angle = 0;
    for (int i = 0; i <_dividePiece; i++) {
        totalPos = Point(0,0);
        while((n/gPicec == i)){
            char p[10];  sprintf(p, "1_%d",n);
            pos[n%gPicec] = obj->getChildByName(p)->getPosition();
            totalPos += pos[n%gPicec];
            n++;
        }
        totalPos = totalPos / gPicec;
        for(int k=0; k<gPicec; k++) pos[k] -= totalPos;
        img[i] = new TRectSprite;
        img[i]->setImgInfo(picname,gPicec, _scale,pos,angle);
        img[i]->setCollisionInfo(_dividePiece);
        img[i]->setPosition(POS+totalPos);
        addChild(img[i]->getNode(), BOTTOM_LEVEL);
        
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
    
    _dividePiece = num;
    _scale = scale;
    _divided = false;
    
    sprintf(picname, "%s%d.png", _name, _dividePiece);

    img = new TouchSprite*[_dividePiece];
    _StickyData = new StickyData[_dividePiece];
    for (int i = 0; i < _dividePiece; i++) {
        img[i] = new TCircleSprite;
        float angle = (360 / _dividePiece)*i;
        Point pos[1] = {POS};
        img[i]->setImgInfo(picname,1, _scale,pos,angle);
        img[i]->setCollisionInfo(_dividePiece);
        
        addChild(img[i]->getNode(), BOTTOM_LEVEL);
        
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
    float n;
    switch(_mode){
        case 0:  //圓形用
            for(int i = 0; i < _dividePiece; i++){
                img[i]->setPosition(_StickyData[i].pos);
                //img[i]->setRotation(_StickyData[i].angle);
                img[i]->setSticky(i);
                _StickyData[i].isSticky = true;
            }
            break;
        case 2:
            n = 360/_dividePiece;
            for (int i = 0; i < _dividePiece; i++) {
                Point move = Point(250 * cosf(ANGLE((n*i))), 250 * sinf(ANGLE((n*i))) );
                img[i]->setPosition(POS + move);
                img[i]->setRotation(_StickyData[i].angle);
                img[i]->setSticky(-1);
                _StickyData[i].isSticky = false;
            }
            break;
        case 1: //非連續用
            n = (_dividePiece - 1) / 2.0;
            Vec2 move;
            if(_dividePiece % 2 == 0){
                for (int i = 0; i < _dividePiece; i++) {
                    int gNum = i;
                    move = _cutDir * (gNum - n);
                    img[i]->setPosition(_StickyData[i].pos + move);
                    img[i]->setRotation(_StickyData[i].angle);
                    img[i]->setSticky(-1);
                    _StickyData[i].isSticky = false;
                }
            }else{
                for (int i = 0; i < _dividePiece; i++) {
                    int gNum = i ;
                    if(gNum < n) move = _cutDir * (gNum - n);
                    else         move = _cutDir * (gNum - n + 1);
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
    for(int i = 0; i < _dividePiece; i++){
        img[i]->setVisible(d);
    }
    
    _divided = d;


}

bool CCutImage::touchesBegin(cocos2d::Point inPos, int id) {
	if (!_divided)return false;

	for (int i = 0; i < _dividePiece ; i++) {
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

	for (int i = 0; i < _dividePiece; i++) {                   //當移動or旋轉
        if( img[i]->touchesMoved(inPos, id)) return true;
	}
	return false;

}

void CCutImage::touchesEnded(cocos2d::Point inPos, int id) {
	if (!_divided)return;

	for (int i = 0; i < _dividePiece; i++) {
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
		for (int i = 0; i < _dividePiece; i++) {        //判斷和哪個角度最靠近
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

