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
        _StickyData->deleteImgData();
        delete [] _StickyData;
    }
}

CCutImage::CCutImage(int picNum, float scale,int num)
{
    auto fileUtiles = FileUtils::getInstance();
    auto fragmentGrayFullPath = fileUtiles->fullPathForFilename("shader/gray.fsh");
    auto fragSource = fileUtiles->getStringFromFile(fragmentGrayFullPath);
    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    grayGLProgrameState = GLProgramState::getOrCreateWithGLProgram(glprogram);
    grayGLProgrameState->retain();
    
    fileUtiles = FileUtils::getInstance();
    fragmentGrayFullPath = fileUtiles->fullPathForFilename("shader/color.fsh");
    fragSource = fileUtiles->getStringFromFile(fragmentGrayFullPath);
    glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
    colorGLProgrameState = GLProgramState::getOrCreateWithGLProgram(glprogram);
    colorGLProgrameState->retain();

    
    switch (picNum) {
        case PANCAKE:
            _name = "stuff_muffin";
            _mode = 0;
            CreateImg(scale,num);
            break;
        case PAPER:
            _name = "bnn";
            _cutDir = Vec2(50,0);
            _mode = 3;
            CreateImg2(scale,num);
            break;
        case WATER:
            _name = "nut";
            _cutDir = Vec2(50,0);
            _mode = 3;
            CreateImg2(scale,num);
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
            _name = "tree";
            _cutDir = Vec2(50,0);
            _mode = 3;
            CreateImg2(scale,num);
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

    img = new TouchSprite*[_dividePiece];
    _StickyData = new StickyData[_dividePiece];

    sprintf(picname, "%s_1.png", _name);
    int n=0;
    Point totalPos;
    
    for (int i = 0; i <_dividePiece; i++) {
        _StickyData[i].createImgData(gPicec);
        totalPos = Point(0,0);
        while((n/gPicec == i)){
            char p[10];  sprintf(p, "1_%d",n);
            int k = n%gPicec;
            _StickyData[i]._imgPos[k] = obj->getChildByName(p)->getPosition();
            _StickyData[i]._imgAngle[k] =obj->getChildByName(p)->getRotation();
            totalPos += _StickyData[i]._imgPos[k];
            n++;
        }
        totalPos = totalPos / gPicec;
        for(int k=0; k<gPicec; k++) _StickyData[i]._imgPos[k] -= totalPos;
        
        img[i] = new TRectSprite;
        img[i]->setImgInfo(picname,gPicec, _scale,_StickyData[i]._imgPos,_StickyData[i]._imgAngle);
        img[i]->setCollisionInfo(_dividePiece);
        img[i]->setPosition(POS+totalPos);
        img[i]->setSticky(i);
        img[i]->setVisible(false);
        addChild(img[i]->getNode(), BOTTOM_LEVEL);
    
        _StickyData[i]._NodeAngle = 0;
        _StickyData[i]._NodePos = img[i]->getPosition();
        _StickyData[i].isSticky = true;
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
        float angle[1] = {(360.0f / _dividePiece)*i};
        Point pos[1] = {POS};
        img[i]->setImgInfo(picname,1, _scale,pos,angle);
        img[i]->setCollisionInfo(_dividePiece);
        img[i]->setSticky(i);
        img[i]->setVisible(false);
        addChild(img[i]->getNode(), BOTTOM_LEVEL);

        _StickyData[i].createImgData(1);
        _StickyData[i]._NodeAngle = angle[0];
        _StickyData[i]._NodePos = img[i]->getPosition();
        _StickyData[i]._imgPos[0] = Point(0,0);
        _StickyData[i]._imgAngle[0] = 0;
        _StickyData[i].isSticky = true;
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
                img[i]->setPosition(_StickyData[i]._NodePos);
                img[i]->setRotation(_StickyData[i]._NodeAngle);
                img[i]->setSticky(i);
                _StickyData[i].isSticky = true;
            }
            break;
        case 2:
            n = 360/_dividePiece;
            for (int i = 0; i < _dividePiece; i++) {
                Point move = Point(250 * cosf(ANGLE((n*i))), 250 * sinf(ANGLE((n*i))) );
                img[i]->setPosition(POS + move);
                img[i]->setRotation(_StickyData[i]._NodeAngle);
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
                    img[i]->setPosition(_StickyData[i]._NodePos + move);
                    img[i]->setRotation(_StickyData[i]._NodeAngle);
                    img[i]->setSticky(-1);
                    _StickyData[i].isSticky = false;
                }
            }else{
                for (int i = 0; i < _dividePiece; i++) {
                    int gNum = i ;
                    if(gNum < n) move = _cutDir * (gNum - n);
                    else         move = _cutDir * (gNum - n + 1);
                    img[i]->setPosition(_StickyData[i]._NodePos + move);
                    img[i]->setSticky(-1);
                    _StickyData[i].isSticky = false;
                }
            }
            break;
    }
    
}

void CCutImage::divide(bool d) {
    if(d){
        //_fullImg->setOpacity(100);

        _fullImg->setGLProgramState(grayGLProgrameState);
    }else{
        //_fullImg->setOpacity(255);
        _fullImg->setGLProgramState(colorGLProgrameState);
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
				DAngle = abs(_StickyData[i]._NodeAngle - angle);   //算角度差
				if (DAngle < preDAngle) {            //如果比上次資料小  紀錄這次資料
					preDAngle = DAngle;
					stickyNum = i;
				}
			}
		}
        
        if(stickyNum == -1) return;
        for(int i=0; i<_StickyData[stickyNum]._num; i++)
            img->setImgPandR(i, _StickyData[stickyNum]._imgPos[i], _StickyData[stickyNum]._imgAngle[i]);
		img->setPosition(_StickyData[stickyNum]._NodePos);       //設定圖片位置與角度
		img->setRotation(_StickyData[stickyNum]._NodeAngle);
		img->setSticky(stickyNum);                          //紀錄區域
		_StickyData[stickyNum].isSticky = true;
	}
}

