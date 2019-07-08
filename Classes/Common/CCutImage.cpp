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
            CreatePancake(scale,dividedP);
            break;
        case PAPER:
            _name = "paper";
            _mode = 2;
            CreatePaper(scale,dividedP);
            break;
        case WATER:
            _name = "water";
            _mode = 2;
            CreateWater(scale,dividedP);
            break;
        case BAMBOO:
            _name = "nut";
            _mode = 2;
            CreateNormalImg(scale,dividedP);
            break;
        case RIBBON:
            _name = "ribbon";
            _mode = 2;
            CreateNormalImg(scale,dividedP);
            break;
        case DISTANCE:
            _name = "road";
            _mode = 2;
            CreateNormalImg(scale,dividedP);
            break;
        case BANANA:
            _name = "banana";
            _mode = 2;
            CreateNormalImg(scale,dividedP);
            break;
        case GRAPE:
            _name = "grape";
            _mode = 2;
            CreateNormalImg(scale,dividedP);
            break;
        case FLOWER:
            _name = "flower";
            _mode = 2;
            CreateFlower(scale,dividedP);
            break;
        case BRANCH:
            _name = "branch";
            _mode = 2;
            CreateNormalImg(scale,dividedP);
            break;
        case NUT:
            _name = "nut";
            _mode = 2;
            CreateNormalImg(scale,dividedP);
            break;
        case TOMATO:
            _name = "tomato";
            _mode = 2;
            CreateNormalImg(scale,dividedP);
            break;
    }
    
}

void CCutImage::CreatePaper(float scale,int num){   //紙
    char picname[20];
    char pp[5];
    _dividePiece = num;
    _scale = scale;
    _divided = false;
    
    sprintf(picname, "ani/%s.csb",_name);
    sprintf(pp, "%d",_dividePiece);
    auto obj = CSLoader::createNode(picname)->getChildByName(pp);

    
    int totalPiece = obj->getTag();
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
        
        sprintf(picname, "%s_%d.png", _name,_dividePiece);
        int n=0;
        for (int i = 0; i <_dividePiece; i++) {
            int number = k*_dividePiece+i;
            _StickyData[number].createImgData(gPicec);
            while((n/gPicec == i)){
                char p[10];  sprintf(p, "1_%d",n);
                int v = n%gPicec;
                _StickyData[number]._imgPos[v] = obj->getChildByName(p)->getPosition();
                _StickyData[number]._imgAngle[v] =obj->getChildByName(p)->getRotation();
                n++;
            }
            img[number].setImgInfo(picname,gPicec,_StickyData[number]._imgPos,_StickyData[number]._imgAngle,Vec2(scale,scale));
            img[number].setCollisionInfo(_dividePiece);
            img[number].setPosition(POS + POSD*k);
            img[number].setSticky(number);
            img[number].setVisible(false);
            addChild(img[number].getNode(), BOTTOM_LEVEL+2);
            
            _StickyData[number]._NodeAngle = 0;
            _StickyData[number]._NodePos = img[number].getPosition();
            _StickyData[number].isSticky = true;
        }
    }
    
    _StickyRadius = powf(img[0].ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
    
    
}

void CCutImage::CreateFlower(float scale,int num){   //花
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
        
        int n=0;
        Point totalPos;
        
        for (int i = 0; i <_dividePiece; i++) {
            int number = k*_dividePiece+i;
            _StickyData[number].createImgData(gPicec);
            while((n/gPicec == i)){
                char p[10];  sprintf(p, "1_%d",n);
                int v = n%gPicec;
                _StickyData[number]._imgPos[v] = obj->getChildByName(p)->getPosition();
                _StickyData[number]._imgAngle[v] =obj->getChildByName(p)->getRotation();
                n++;
            }

            img[number].setImgInfo_flower(i,gPicec,_StickyData[number]._imgPos,_StickyData[number]._imgAngle,Vec2(scale,scale));
            img[number].setCollisionInfo(_dividePiece);
            img[number].setPosition(POS + POSD*k);
            img[number].setSticky(number);
            img[number].setVisible(false);
            addChild(img[number].getNode(), BOTTOM_LEVEL+2);
            
            _StickyData[number]._NodeAngle = 0;
            _StickyData[number]._NodePos = img[number].getPosition();
            _StickyData[number].isSticky = true;
        }
        
    }
    
    _StickyRadius = powf(img[0].ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
    
    
}

void CCutImage::CreateWater(float scale,int num){  // 水
    char picname[20];
    
    _dividePiece = num;
    _scale = scale;
    _divided = false;
    
    img = new TRectSprite[_dividePiece * _fullAmount];
    _StickyData = new StickyData[_dividePiece * _fullAmount];
    
    for(int k=0;k<_fullAmount;k++){
        
        sprintf(picname, "%s_1.png",_name);
        auto fi = (Sprite *)Sprite::createWithSpriteFrameName(picname);
        fi->setPosition(POS+POSD*k);
        fi->setScale(scale);
        addChild(fi,BOTTOM_LEVEL);
        _fullImg.push_back(fi);
        
        sprintf(picname, "%s_2.png", _name);
        
        Point pos[1] = {Point(0,0)};
        float angle[1] = {0};
        float center = (_dividePiece-1)/2;
        Vec2 PicScale = Vec2(1,1.0/_dividePiece);
        float height = 200*PicScale.y;

        for (int i = 0; i < _dividePiece; i++) {
            int number = k*_dividePiece+i;
            Point move = Point(0,(i - center)*height);
            img[number].setImgInfo(picname,1,pos,angle,PicScale);
            img[number].setCollisionInfo(_dividePiece);
            img[number].setPosition(POS + POSD*k+move);
            img[number].setSticky(number);
            //img[number].setVisible(false);
            addChild(img[number].getNode(), BOTTOM_LEVEL+1);
            
    
            
            _StickyData[number].createImgData(1);
            _StickyData[number]._NodeAngle = angle[0];
            _StickyData[number]._NodePos = img[number].getPosition();
            _StickyData[number]._imgPos[0] = Point(0,0);
            _StickyData[number]._imgAngle[0] = 0;
            _StickyData[number].isSticky = true;
            
//            auto line = Sprite::createWithSpriteFrameName("pancake_line.png");
//            line->setPosition(POS + POSD*k);
//            line->setScale(scale);
//            line->setRotation(angle[0]+a);
//            line->setVisible(false);
//            addChild(line, BOTTOM_LEVEL+2);
//            _line.push_back(line);
            
        }
        
        
    }
    
    _StickyRadius = powf(img[0].ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
}

void CCutImage::CreateNormalImg(float scale,int num){   //非連續物件
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
        for (int i = 0; i <_dividePiece; i++) {
            int number = k*_dividePiece+i;
            _StickyData[number].createImgData(gPicec);
            while((n/gPicec == i)){
                char p[10];  sprintf(p, "1_%d",n);
                int v = n%gPicec;
                _StickyData[number]._imgPos[v] = obj->getChildByName(p)->getPosition();
                _StickyData[number]._imgAngle[v] =obj->getChildByName(p)->getRotation();
                n++;
            }
            img[number].setImgInfo(picname,gPicec,_StickyData[number]._imgPos,_StickyData[number]._imgAngle,Vec2(scale,scale));
            img[number].setCollisionInfo(_dividePiece);
            img[number].setPosition(POS + POSD*k);
            img[number].setSticky(number);
            img[number].setVisible(false);
            addChild(img[number].getNode(), BOTTOM_LEVEL+2);
        
            _StickyData[number]._NodeAngle = 0;
            _StickyData[number]._NodePos = img[number].getPosition();
            _StickyData[number].isSticky = true;
        }
    }
    
    _StickyRadius = powf(img[0].ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
}

void CCutImage::CreatePancake(float scale,int num){  // 圓形
    char picname[20];
    
    _dividePiece = num;
    _scale = scale;
    _divided = false;
    
    img = new TCircleSprite[_dividePiece * _fullAmount];
    _StickyData = new StickyData[_dividePiece * _fullAmount];

    for(int k=0;k<_fullAmount;k++){
        sprintf(picname, "%s_1.png",_name);                               //底圖
        auto fi = (Sprite *)Sprite::createWithSpriteFrameName(picname);
        fi->setPosition(POS+POSD*k);
        fi->setScale(scale);
        addChild(fi,BOTTOM_LEVEL);
        _fullImg.push_back(fi);
        
        sprintf(picname, "%s_%d.png", _name, _dividePiece);              //切分圖
        float a = 180 / _dividePiece;
        for (int i = 0; i < _dividePiece; i++) {
            int number = k*_dividePiece+i;
            float angle[1] = {(360.0f / _dividePiece)*i};
            Point pos[1] = {POS + POSD*k};
            img[number].setImgInfo(picname,1,pos,angle,Vec2(scale,scale));
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
