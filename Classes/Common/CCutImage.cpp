#include "CCutImage.h"
#include "../Data.h"
#include <cmath>

#define IMG_ANGLE 90 //圖片原角度

#define ANGLE(a) a*M_PI/180 //角度轉弧度

#define POS_1 Vec2(400,800)   //500,950
#define POS_2 Vec2(400,975)
#define POSD Vec2(0,-450)    //0,-450 ３大概

enum PIC_CUTMODE{NORMAL,SAMEHEIGHT,WATERPIC,LONGPIC};  //sprite-cutMode

CCutImage::~CCutImage()
{
    if (_dividePiece != 0) {
    //    CCLOG("delete cutimg");
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
    
    if(_fullAmount == 1)_pos = POS_1;
    else _pos = POS_2;
    _dPos = POSD;
    _mode = 1;
    switch (picNum) {
        case PANCAKE:
            _mode = 0;
            _name = "pancake";
            _hasline = true;
            CreatePancake(scale,dividedP);
            break;
        case PAPER:
            _name = "paper";
            CreatePaper(scale,dividedP);
            break;
        case WATER:
            _mode = 3;
            _name = "water";
            _hasline = true;
            CreateWater(scale,dividedP);
            setCutmode(WATERPIC);
            break;
        case BAMBOO:
            _name = "banboo";
            _pos = Vec2(700,950);
            _dPos = Vec2(0,-200);
            _hasline = true;
            CreateNormalImg(scale,dividedP);
            setCutmode(LONGPIC);
            break;
        case RIBBON:
            _name = "ribbon";
            _pos = Vec2(700,950);
            _dPos = Vec2(0,-200);
            _hasline = true;
            CreateNormalImg(scale,dividedP);
            setCutmode(LONGPIC);
            break;
        case DISTANCE:
            _name = "road";
            _pos = Vec2(700,950);
            _dPos = Vec2(0,-200);
            _hasline = true;
            CreateNormalImg(scale,dividedP);
            setCutmode(LONGPIC);
            break;
        case BANANA:
            _name = "banana";
            CreateNormalImg(scale,dividedP);
            break;
        case GRAPE:
            _name = "grape";
            CreateNormalImg(scale,dividedP);
            break;
        case FLOWER:
            _name = "flower";
            CreateFlower(scale,dividedP);
            setCutmode(SAMEHEIGHT);
            break;
        case BRANCH:
            _name = "branch";
            CreateNormalImg(scale,dividedP);
            break;
        case NUT:
            _name = "nut";
            CreateNormalImg(scale,dividedP);
            break;
        case TOMATO:
            _name = "tomato";
            CreateNormalImg(scale,dividedP);
            break;
        case APPLE:
            _name = "apple";
            CreateNormalImg(scale,dividedP);
            break;
        case BIGBAMBOO:
            _name = "banboo";
//            _mode = 2;
//            CreateNormalImg(scale,dividedP);
            break;
    }
    
}

void CCutImage::setCutmode(int m){
    for(int i=0;i<_dividePiece * _fullAmount;i++){
        img[i].setCutmode(m);
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
        fi->setPosition(_pos + _dPos*k);
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
            img[number].setPosition(_pos + _dPos*k);
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
    int totalPiece = obj->getChildByName("0")->getTag();
    if(num == -1)_dividePiece = totalPiece;
    else _dividePiece = num;
    _scale = scale;
    _divided = false;
    

    int gPicec = totalPiece / _dividePiece;
    img = new TRectSprite[_dividePiece * _fullAmount];
    _StickyData = new StickyData[_dividePiece * _fullAmount];
    
    for(int k=0;k<_fullAmount;k++){
        sprintf(picname, "%s_1.png",_name);
        auto fi = (Sprite *)Sprite::createWithSpriteFrameName(picname);
        fi->setPosition(_pos + _dPos*k);
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
            img[number].setPosition(_pos + _dPos*k);
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
        fi->setPosition(_pos + _dPos*k);
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
            img[number].setImgInfo_water(pos,angle,PicScale);
            img[number].setCollisionInfo(_dividePiece);
            img[number].setPosition(_pos + _dPos*k);
            img[number].setSticky(number);
            img[number].setVisible(false);
            addChild(img[number].getNode(), BOTTOM_LEVEL+1);
            
            float y= img[number].getPicHeight() * (i+0.5f);
            Point move = Point(0,-100+y);
            _StickyData[number].createImgData(1);
            _StickyData[number]._NodeAngle = angle[0];
            _StickyData[number]._NodePos = img[number].getPosition();
            _StickyData[number]._imgPos[0] = move;
            _StickyData[number]._imgAngle[0] = 0;
            _StickyData[number].isSticky = true;
            
//            auto line = Sprite::createWithSpriteFrameName("water_line.png");
//            line->setPosition(_pos + _dPos*k);
//            line->setScale(scale);
//            line->setRotation(0);
//            line->setVisible(false);
//            addChild(line, BOTTOM_LEVEL+2);
//            _line.push_back(line);
//
        }
    }
    
    if(_hasline){
        Vec2 dmove = Vec2(0,img[0].getPicHeight());
        int n_line =_dividePiece;
        float c_center = (n_line-1) /2.0f;
        
        for(int k=0;k<_fullAmount;k++){
            Vec2 centerPos =_pos + _dPos*k +Vec2(-46,(dmove.y+7)/2);
            for (int i = 0; i <n_line; i++) {
                auto line = Sprite::createWithSpriteFrameName("water_line.png");
                Vec2 m = (i- c_center) * dmove;
                line->setPosition(centerPos + m);
                line->setScale(scale);
                line->setRotation(0);
                line->setVisible(false);
                addChild(line, BOTTOM_LEVEL+2);
                _line.push_back(line);
            }
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
    int totalPiece = obj->getChildByName("0")->getTag();
    if(num == -1)_dividePiece = totalPiece;
    else _dividePiece = num;
    _scale = scale;
    _divided = false;

    int gPicec = totalPiece / _dividePiece;
    img = new TRectSprite[_dividePiece * _fullAmount];
    _StickyData = new StickyData[_dividePiece * _fullAmount];

    for(int k=0;k<_fullAmount;k++){
        sprintf(picname, "%s_1.png",_name);
        auto fi = (Sprite *)Sprite::createWithSpriteFrameName(picname);
        fi->setPosition(_pos + _dPos*k);
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
            img[number].setPosition(_pos + _dPos*k);
            img[number].setSticky(number);
            img[number].setVisible(false);
            addChild(img[number].getNode(), BOTTOM_LEVEL+2);
        
            _StickyData[number]._NodeAngle = 0;
            _StickyData[number]._NodePos = img[number].getPosition();
            _StickyData[number].isSticky = true;
            
        }
    }
    
    if(_hasline){
        Vec2 dmove = Vec2(img[0].getPicWidth(),0);
        int n_line =_dividePiece-1;
        float c_center = (n_line-1) /2.0f;
        
        for(int k=0;k<_fullAmount;k++){
            Vec2 centerPos =_pos + _dPos*k;
            for (int i = 0; i <n_line; i++) {
                char line_name[20];  sprintf(line_name, "%s_line.png",_name);
                auto line = Sprite::createWithSpriteFrameName(line_name);
                Vec2 m = (i- c_center) * dmove;
                line->setPosition(centerPos + m);
                line->setScale(scale);
                line->setRotation(0);
                line->setVisible(false);
                addChild(line, BOTTOM_LEVEL+2);
                _line.push_back(line);
            }
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
        fi->setPosition(_pos + _dPos*k);
        fi->setScale(scale);
        addChild(fi,BOTTOM_LEVEL);
        _fullImg.push_back(fi);
        
        sprintf(picname, "%s_%d.png", _name, _dividePiece);              //切分圖
        float a = 180 / _dividePiece;
        for (int i = 0; i < _dividePiece; i++) {
            int number = k*_dividePiece+i;
            float angle[1] = {(360.0f / _dividePiece)*i};
            Point pos[1] = {_pos + _dPos*k};
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
            line->setPosition(_pos + _dPos*k);
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
                     _StickyData[number].setSticky(number);
                    
                }
            }
        }
        break;
        default: //非連續用-圓形切法
        {
//            float n = 360/_dividePiece;
//            for(int k=0;k<_fullAmount;k++){
//                for (int i = 0; i < _dividePiece; i++) {
//                    int number = k*_dividePiece +i;
//                    Point move = Point(250 * cosf(ANGLE((n*i))), 250 * sinf(ANGLE((n*i))) );
//                    img[number].setPosition(move + _pos + _dPos*k);
//                    img[number].setRotation(_StickyData[number]._NodeAngle);
//                    img[number].setSticky(-1);
//                    _StickyData[number].isSticky = false;
//                    img[number].setDividedImg();
//                }
//            }
            for(int k=0; k<_fullAmount; k++){
                for(int i = 0; i < _dividePiece; i++){
                    int number = k*_dividePiece +i;
                    img[number].setImgPandR(_StickyData[number]._imgPos, _StickyData[number]._imgAngle);
                    img[number].setPosition(_StickyData[number]._NodePos);       //設定圖片位置與角度
                    img[number].setRotation(_StickyData[number]._NodeAngle);
                    img[number].setSticky(number);                          //紀錄區域
                    _StickyData[number].setSticky(number);
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
        
    }
    
    if(_hasline) {
        for(int i=0;i<_line.size();i++)_line[i]->setVisible(d);
    }
    
    _divided = d;


}

bool CCutImage::touchesBegin(cocos2d::Point inPos, int id) {
	if (!_divided)return false;
    for (int i = 0; i < _dividePiece*_fullAmount ; i++) {
        if (img[i].touchesBegin(inPos, id)) {
            img[i].setPosition(inPos);
            if (rotateImg == NULL) {
                rotateImg = &img[i];
            }
            int sticky = img[i].ResetSticky();        //重製磁鐵.釋放區域
            if (sticky != -1) {
                _StickyData[sticky].isSticky = false;
                
                if(_mode == 3){                       //水的特殊需求 移開時其他往下一層
                    int max = (sticky ) / _dividePiece + 1;
                    for(int kk = sticky+1;kk < max * _dividePiece ; kk++ ){
                        if(!_StickyData[kk].isSticky)return true;
                        CCLOG("NO.%d down  max = %d",kk,max * _dividePiece);
                        int number =_StickyData[kk]._num;
                        img[number].downOneFloor();
                        _StickyData[kk-1].setSticky(number);
                        _StickyData[kk].isSticky = false;
                    }
                }
            }
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
			Sticky(&img[i],i,inPos);  //判斷是否吸上去
		}
	}
}


void CCutImage::Sticky(TouchSprite *img,int number,Point pt) {
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
            
            img->setImgPandR(_StickyData[stickyNum]._imgPos, _StickyData[stickyNum]._imgAngle);
            img->setPosition(_StickyData[stickyNum]._NodePos);       //設定圖片位置與角度
            img->setRotation(_StickyData[stickyNum]._NodeAngle);
            img->setSticky(stickyNum);                          //紀錄區域
            _StickyData[stickyNum].setSticky(number);
        }
    }
    
}
