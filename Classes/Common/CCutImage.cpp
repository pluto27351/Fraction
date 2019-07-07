#include "CCutImage.h"
#include "../Data.h"
#include <cmath>

#define IMG_ANGLE 90 //圖片原角度

#define ANGLE(a) a*M_PI/180 //角度轉弧度

#define POS Vec2(500,750)
#define POSD Vec2(650,0)

//enum IMG_STATUS { NONE = 0, MOVE = 1, ROT = 2, EXIT = 3 };
enum Object{PANCAKE,PAPER,WATER,BAMBOO,RIBBON,DISTANCE,BANANA,GRAPE,FLOWER,BRANCH,NUT,TOMATO};

CCutImage::~CCutImage()
{
    if (_dividePiece != 0) {
        CCLOG("delete cutimg");
       // removeAllChildren();
        //for (int i = 0; i < _dividePiece; i++) delete img[i];
        _StickyData->deleteImgData();
        _line.clear();
        delete [] img;
        delete [] _StickyData;
    }
}

CCutImage::CCutImage(int picNum,int NodeAmount, float scale,int dividedP)
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

    _fullAmount = NodeAmount;
    
    switch (picNum) {
        case PANCAKE:
            _name = "pancake";
            _mode = 0;_hasline = true;
            CreateImg(scale,dividedP);
            break;
        case PAPER:
            _name = "pancake";
            _cutDir = Vec2(50,0);
            _mode = 0;
            CreateImg(scale,dividedP);
            break;
        case WATER:
            _name = "banana";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,dividedP);
            break;
        case BAMBOO:
            _name = "nut";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,dividedP);
            break;
        case RIBBON:
            _name = "flower";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,dividedP);
            break;
        case DISTANCE:
            _name = "road";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,dividedP);
            break;
        case BANANA:
            _name = "banana";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,dividedP);
            break;
        case GRAPE:
            _name = "grape";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,dividedP);
            break;
        case FLOWER:
            _name = "flower";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,dividedP);
            break;
        case BRANCH:
            _name = "branch";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,dividedP);
            break;
        case NUT:
            _name = "nut";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,dividedP);
            break;
        case TOMATO:
            _name = "tomato";
            _cutDir = Vec2(50,0);
            _mode = 2;
            CreateImg2(scale,dividedP);
            break;
    }
    

}

void CCutImage::CreateImg2(float scale,int num){   //非連續物件
    char picname[20];
    
    sprintf(picname, "ani/%s.csb",_name);
    auto obj = CSLoader::createNode(picname);
    _dividePiece = num;
    _scale = scale;
    _divided = false;
    
    int totalPiece = obj->getChildByName("0")->getTag();
    int gPicec = totalPiece / _dividePiece;
    img = new TRectSprite[_dividePiece * _fullAmount];
    _StickyData = new StickyData[_dividePiece * _fullAmount];

    for(int k=0;k<_fullAmount;k++){
        sprintf(picname, "%s_1.png",_name);
        auto fi = (Sprite *)Sprite::createWithSpriteFrameName(picname);
        fi->setPosition(POS + POSD*k);
        fi->setScale(scale);
        addChild(fi, BOTTOM_LEVEL);
        _fullImg.push_back(fi);
        
        sprintf(picname, "%s_2.png", _name);
        int n=0;
        Point totalPos;
        
        //    _fullImg = (Sprite *)Sprite::createWithSpriteFrameName(picname);
        //    _fullImg->setPosition(POS);
        //    _fullImg->setScale(scale);
        //    addChild(_fullImg, BOTTOM_LEVEL);
        
        for (int i = 0; i <_dividePiece; i++) {
            int number = k*_dividePiece+i;
            _StickyData[number].createImgData(gPicec);
            totalPos = Point(0,0);
            while((n/gPicec == i)){
                char p[10];  sprintf(p, "1_%d",n);
                int v = n%gPicec;
                auto asdf =obj->getChildByName(p)->getPosition();
                _StickyData[number]._imgPos[v] = asdf;
                _StickyData[number]._imgAngle[v] =obj->getChildByName(p)->getRotation();
                totalPos += _StickyData[number]._imgPos[v];
               // removeChild(obj->getChildByName(p));
                n++;
            }
            totalPos = totalPos / gPicec;
            for(int v=0; v<gPicec; v++) {
                _StickyData[number]._imgPos[v] -= totalPos;
            }
            
           // img[i] = new TRectSprite;
            img[number].setImgInfo(picname,gPicec, _scale,_StickyData[number]._imgPos,_StickyData[number]._imgAngle);
            img[number].setCollisionInfo(_dividePiece);
            img[number].setPosition(POS + POSD*k + totalPos);
            img[number].setSticky(number);
            img[number].setVisible(false);
            addChild(img[number].getNode(), BOTTOM_LEVEL+2);
        
            _StickyData[number]._NodeAngle = 0;
            _StickyData[number]._NodePos = img[number].getPosition();
            _StickyData[number].isSticky = true;
        }
    
    }
    
   // setCutPos();
    
    _StickyRadius = powf(img[0].ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
    
    
}

void CCutImage::CreateImg(float scale,int num){  // 圓形
    char picname[20];
    
    _dividePiece = num;
    _scale = scale;
    _divided = false;
    
    img = new TCircleSprite[_dividePiece * _fullAmount];
    _StickyData = new StickyData[_dividePiece * _fullAmount];

    for(int k=0;k<_fullAmount;k++){

        sprintf(picname, "%s_1.png",_name);
        auto fi = (Sprite *)Sprite::createWithSpriteFrameName(picname);
        fi->setPosition(POS+POSD*k);
        fi->setScale(scale);
        addChild(fi,BOTTOM_LEVEL);
        _fullImg.push_back(fi);
        
        sprintf(picname, "%s_%d.png", _name, _dividePiece);

        float a = 180 / _dividePiece;
        for (int i = 0; i < _dividePiece; i++) {
            int number = k*_dividePiece+i;
            //img[i] = new TCircleSprite;
            float angle[1] = {(360.0f / _dividePiece)*i};
            Point pos[1] = {POS + POSD*k};
            img[number].setImgInfo(picname,1, _scale,pos,angle);
            img[number].setCollisionInfo(_dividePiece);
            img[number].setSticky(number);
            img[number].setVisible(false);
            addChild(img[number].getNode(), BOTTOM_LEVEL+1);
            
            _StickyData[number].createImgData(1);
            _StickyData[number]._NodeAngle = angle[0];
            _StickyData[number]._NodePos = img[number].getPosition();
            _StickyData[number]._imgPos[0] = Point(0,0);
            _StickyData[number]._imgAngle[0] = 0;
            _StickyData[number].isSticky = true;
            
            auto line = Sprite::createWithSpriteFrameName("pancake_line.png");
            line->setPosition(POS + POSD*k);
            line->setScale(scale);
            line->setRotation(angle[0]+a);
            line->setVisible(false);
            addChild(line, BOTTOM_LEVEL+2);
            _line.push_back(line);
            
        }

        
    }

    _StickyRadius = powf(img[0].ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
}


void CCutImage::setCutPos(){                  //計算切分時位置
    switch(_mode){
        case 0:  //圓形用
        {
            for(int k=0; k<_fullAmount; k++){
                for(int i = 0; i < _dividePiece; i++){
                    int number = k*_dividePiece +i;
                    img[number].setPosition(_StickyData[number]._NodePos);
                    img[number].setRotation(_StickyData[number]._NodeAngle);
                    img[number].setSticky(number);
                    _StickyData[number].isSticky = true;
                    
                }
            }
        }
        break;
//        case 1: //非連續用-位移切法
//        {
//            float d = (_dividePiece-1) /2.0f;
//            int n = img[0].getPieceAmount();
//            n = MIN(n, 3);
//            n *= 95;
//            for (int i = 0; i < _dividePiece; i++) {
//                Point pos = Point(n*(i - d),0);
//                img[i].setPosition(pos + POS);
//                img[i].setRotation(0);
//                img[i].setSticky(-1);
//                _StickyData[i].isSticky = false;
//                img[i].setDividedImg();
//            }
//
//        }
//        break;
        case 2: //非連續用-圓形切法
        {
            float n = 360/_dividePiece;
            for(int k=0;k<_fullAmount;k++){
                for (int i = 0; i < _dividePiece; i++) {
                    int number = k*_dividePiece +i;
                    Point move = Point(250 * cosf(ANGLE((n*i))), 250 * sinf(ANGLE((n*i))) );
                    img[number].setPosition(move + POS + POSD*k);
                    img[number].setRotation(_StickyData[number]._NodeAngle);
                    img[number].setSticky(-1);
                    _StickyData[number].isSticky = false;
                    img[number].setDividedImg();
                }
            }
        }
        break;
    }
    
}

void CCutImage::divide(bool d) {
    if(d){
        setCutPos();
        for(int i=0; i<_fullAmount; i++){
            _fullImg[i]->setGLProgramState(grayGLProgrameState);
            _fullImg[i]->setOpacity(100);
        }
    }else{
        for(int i=0; i<_fullAmount; i++){
            _fullImg[i]->setOpacity(255);
            _fullImg[i]->setGLProgramState(colorGLProgrameState);
        }
    }
    
    for(int i = 0; i < _dividePiece*_fullAmount; i++){
        img[i].setVisible(d);
        if(_hasline) _line[i]->setVisible(d);
    }
    
    
    _divided = d;


}

bool CCutImage::touchesBegin(cocos2d::Point inPos, int id) {
	if (!_divided)return false;

	for (int i = 0; i < _dividePiece*_fullAmount ; i++) {
		if (img[i].touchesBegin(inPos, id)) {
			if (rotateImg == NULL) {
				rotateImg = &img[i];
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

	for (int i = 0; i < _dividePiece*_fullAmount; i++) {                   //當移動or旋轉
        if( img[i].touchesMoved(inPos, id)) return true;
	}
	return false;

}

void CCutImage::touchesEnded(cocos2d::Point inPos, int id) {
	if (!_divided)return;

	for (int i = 0; i < _dividePiece*_fullAmount; i++) {
		if (img[i].touchesEnded(inPos, id)) {
			if (rotateImg == &img[i]) rotateImg = NULL;
			Sticky(&img[i],inPos);  //判斷是否吸上去
		}
	}
}

//void CCutImage::Sticky(TouchSprite *img) {
//    float x, y, d;
//    x = img->getPosition().x - POS.x;
//    y = img->getPosition().y - POS.y;
//    d = powf(x, 2) + powf(y, 2);
//    if (d < _StickyRadius) {    //位置靠近磁鐵區域
//        int stickyNum = -1;
//        float angle = img->getAngle();
//        float preDAngle = 1000, DAngle;
//        for (int i = 0; i < _dividePiece; i++) {        //判斷和哪個角度最靠近
//            if (_StickyData[i].isSticky == false) {
//                DAngle = abs(_StickyData[i]._NodeAngle - angle);   //算角度差
//                if (DAngle < preDAngle) {            //如果比上次資料小  紀錄這次資料
//                    preDAngle = DAngle;
//                    stickyNum = i;
//                }
//            }
//        }
//
//        if(stickyNum == -1) return;
//        for(int i=0; i<_StickyData[stickyNum]._num; i++)
//            img->setImgPandR(i, _StickyData[stickyNum]._imgPos[i], _StickyData[stickyNum]._imgAngle[i]);
//        img->setPosition(_StickyData[stickyNum]._NodePos);       //設定圖片位置與角度
//        img->setRotation(_StickyData[stickyNum]._NodeAngle);
//        img->setSticky(stickyNum);                          //紀錄區域
//        _StickyData[stickyNum].isSticky = true;
//    }
//}

void CCutImage::Sticky(TouchSprite *img,Point pt) {
    for(int k=0;k < _fullAmount; k++){
        auto posInNode = _fullImg[k]->convertToNodeSpace(pt);   //位置靠近磁鐵區域
        if (Rect(0,0,_fullImg[k]->getContentSize().width,_fullImg[k]->getContentSize().height).containsPoint(posInNode)) {
            int stickyNum = -1;
            float angle = img->getAngle();
            float preDAngle = 1000, DAngle;
            for (int i = k*_dividePiece; i < _dividePiece*(k+1); i++) {        //判斷和哪個角度最靠近
                if (_StickyData[i].isSticky == false) {
                    DAngle = abs(_StickyData[i]._NodeAngle - angle);   //算角度差
                    if (DAngle < preDAngle) {            //如果比上次資料小  紀錄這次資料
                        preDAngle = DAngle;
                        stickyNum = i;
                    }
                }
            }
            
            if(stickyNum == -1) return;
            for(int i=0; i<_StickyData[stickyNum]._num; i++){
                img->setImgPandR(i, _StickyData[stickyNum]._imgPos[i], _StickyData[stickyNum]._imgAngle[i]);
            }
            img->setPosition(_StickyData[stickyNum]._NodePos);       //設定圖片位置與角度
            img->setRotation(_StickyData[stickyNum]._NodeAngle);
            img->setSticky(stickyNum);                          //紀錄區域
            _StickyData[stickyNum].isSticky = true;
        }
    }
    
}
