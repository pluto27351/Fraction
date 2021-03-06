#include "CCutImage.h"
#include "../Data.h"
#include <cmath>

#define IMG_ANGLE 90 //圖片原角度
#define ANGLE(a) a*M_PI/180 //角度轉弧度

#define SCENE_POS Vec2(1365.5,768)
#define POS_1 Vec2(SCENE_POS.x - 624,SCENE_POS.y + 32)
#define POS_2 Vec2(SCENE_POS.x - 624,SCENE_POS.y + 257)
#define POSD Vec2(0,-475)

enum PIC_CUTMODE{NORMAL,SAMEHEIGHT,WATERPIC,LONGPIC};  //sprite-cutMode

CCutImage::~CCutImage()
{
    if (_dividePiece != 0) {
       // removeAllChildren();
        for (int i = 0; i < _dividePiece*_fullAmount; i++) delete img[i];
        img.clear();
        _fullImg.clear();
        _line.clear();
        _StickyData->deleteImgData();
        _line.clear();

        delete [] _StickyData;
    }
}

CCutImage::CCutImage(int picNum,int NodeAmount, float scale,int dividedP,int c)
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
            _hasline = true;
            CreatePaper(scale,dividedP);
            break;
        case WATER:
            _mode = 3;
            _name = "water";
            CreateWater(scale,dividedP);
            setCutmode(WATERPIC);
            break;
        case BAMBOO:
            _name = "banboo";
            _pos = Vec2(SCENE_POS.x - 224,SCENE_POS.y+ 332);
            _dPos = Vec2(0,-200);
            _hasline = true;
            CreateNormalImg(scale,dividedP,c);
            setCutmode(LONGPIC);
            break;
        case RIBBON:
            _name = "ribbon";
            _pos = Vec2(SCENE_POS.x - 374,SCENE_POS.y+ 332);
            _dPos = Vec2(0,-200);
            _hasline = true;
            CreateNormalImg(scale,dividedP,c);
            setCutmode(LONGPIC);
            break;
        case DISTANCE:
            _name = "road";
            _pos = Vec2(SCENE_POS.x - 374,SCENE_POS.y+ 332);
            _dPos = Vec2(0,-200);
            _hasline = true;
            CreateNormalImg(scale,dividedP,c);
            setCutmode(LONGPIC);
            break;
        case BANANA:
            _name = "banana";
            CreateNormalImg(scale,dividedP,c);
            break;
        case GRAPE:
            _name = "grape";
            CreateNormalImg(scale,dividedP,c);
            break;
        case FLOWER:
            _name = "flower";
            _mode = 2;
            CreateFlower(scale,dividedP,c);
            setCutmode(SAMEHEIGHT);
            break;
        case BRANCH:
            _name = "branch";
            CreateNormalImg(scale,dividedP,c);
            break;
        case NUT:
            _name = "nut";
            CreateNormalImg(scale,dividedP,c);
            break;
        case TOMATO:
            _name = "tomato";
            CreateNormalImg(scale,dividedP,c);
            break;
        case APPLE:
            _name = "apple";
            CreateNormalImg(scale,dividedP,c);
            break;
        case SUGAR:
            _name = "sugar";
            _mode = 2;
            CreateNormalImg(scale,dividedP,c);
            break;
        case COOKIE:
            _name = "cookie";
            CreateNormalImg(scale,dividedP,c);
            break;
        case PEAR:
            _name = "pear";
            CreateNormalImg(scale,dividedP,c);
            break;
        case BIGROLE:
            _name = "role";
            _pos = Vec2(SCENE_POS.x - 374,SCENE_POS.y+ 332);
            _dPos = Vec2(0,-200);
            _hasline = true;
            _mode = 4;
            CreateNormalImg(scale,dividedP,c);
            setCutmode(LONGPIC);
            break;
    }
    
}

CCutImage::CCutImage(int picNum,float scale,int dividedP,int a,int b)
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
    
    _fullAmount = 1;
    _pos = Vec2(SCENE_POS.x - 824,SCENE_POS.y + 157);
    _dPos = Vec2(0,-120);
    switch (picNum) {
        case BIGBAMBOO:
            _name = "banboo";
            CreatelinePic(scale,dividedP,a,b,dividedP);
            break;
        case BIGRODE:
            _name = "road";
            CreatelinePic(scale,dividedP,a,b,dividedP);
            break;
        case BIGRIBBON:
            _name = "ribbon";
            CreatelinePic(scale,dividedP,a,b,dividedP);
            break;
        case BIGROLE:
            _name = "role";
            CreatelinePic(scale,dividedP,a,b,dividedP);
            break;
        default:
            _name = "banboo";
            CreatelinePic(scale,dividedP,a,b,dividedP);
            break;
    }
    
}

void CCutImage::setCutmode(int m){
    for(int i=0;i<_dividePiece * _fullAmount;i++){
        img[i]->setCutmode(m);
    }
}

void CCutImage::CreatelinePic(float scale,int num,int a,int b,int c){   //線段＋圖片
    char picname[20];
    char line_name[20];
    _dividePiece = 1;
    _fullAmount = num;
    
    _scale = scale;
    _divided = false;
    
    _StickyData = new StickyData[_dividePiece * _fullAmount];
        
    sprintf(picname, "%s_big.png", _name);              //切分圖
    sprintf(line_name, "%s_line.png",_name);
    Vec2 dp2 = Vec2(235,0);
    Vec2 pos2 = _pos + Vec2(0,250);
    
    for (int i = 0; i < _fullAmount; i++) {
        TouchSprite *newimg = new TRectSprite;
        float angle[1] = {0};
        Point pos[1] = {_pos + _dPos*i};
        newimg->setImgInfo(picname,1,pos,angle,Vec2(scale,scale));
        newimg->setCollisionInfo(_fullAmount);
        newimg->setSticky(i);
        addChild(newimg->getNode(), BOTTOM_LEVEL+1);
        img.push_back(newimg);
        
        pos[0] = {pos2 + dp2*i};
        _StickyData[i].createImgData(1);
        _StickyData[i]._NodeAngle = angle[0];
        _StickyData[i]._NodePos = img[i]->getPosition();
        _StickyData[i]._imgPos[0] = pos[0];
        _StickyData[i]._imgAngle[0] = 0;
        if(i == 0) _StickyData[i].isSticky = true;
        else _StickyData[i].isSticky = false;
        
        auto fi = (Sprite *)Sprite::createWithSpriteFrameName(picname);
        fi->setPosition(pos[0]);
        fi->setVisible(false);
        addChild(fi,BOTTOM_LEVEL);
        _fullImg.push_back(fi);
        
    }
    
    //比例尺
    Vec2 initPos = pos2 - dp2 / 2 +Vec2(0,-90);
    Vec2 movePos = dp2 / b;
    int ruler_max = (b*c)>a?2:1;
    Vec2 length[3];
    int l = 0;
    
    for(int i=0;i<(ruler_max*a)+1;i++){
        Sprite *rulerPic;
        if(i % a == 0){
            sprintf(picname, "length_b%d.png", i/a);
            rulerPic = Sprite::createWithSpriteFrameName(picname);
            length[l] = initPos + movePos*i;
        }
        else rulerPic = Sprite::createWithSpriteFrameName("length_2.png");
        rulerPic->setPosition(initPos + movePos*i);
        rulerPic->setScale(scale);
        rulerPic->setRotation(0);
        rulerPic->setVisible(true);
        addChild(rulerPic, BOTTOM_LEVEL+2);
        _fullImg.push_back(rulerPic);
    }
    
    movePos = movePos*a;
    initPos += movePos /2;
    for(int i=0;i<ruler_max;i++){          //底圖->改線段！！！
        auto rulerPic = (Sprite *)Sprite::createWithSpriteFrameName("length_big.png");
        rulerPic->setScaleX((float)a / b);
        rulerPic->setPosition(initPos + movePos*i);
        addChild(rulerPic,BOTTOM_LEVEL);
        _fullImg.push_back(rulerPic);
    }
    
    
    _StickyRadius = powf(img[0]->ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
}

//紙
void CCutImage::CreatePaper(float scale,int num){  //紙
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
            TouchSprite *newimg = new TRectSprite;
            newimg->setImgInfo(picname,gPicec,_StickyData[number]._imgPos,_StickyData[number]._imgAngle,Vec2(scale,scale));
            newimg->setCollisionInfo(_dividePiece);
            newimg->setPosition(_pos + _dPos*k);
            newimg->setSticky(number);
            newimg->setVisible(false);
            addChild(newimg->getNode(), BOTTOM_LEVEL+1);
            img.push_back(newimg);
            
            _StickyData[number]._NodeAngle = 0;
            _StickyData[number]._NodePos = img[number]->getPosition();
            _StickyData[number].isSticky = true;
        }
        
        Vec2 move = Vec2(0,(_fullImg[0]->getContentSize().height-8));
        Vec2 cPos = _fullImg[k]->getPosition();
        if(_dividePiece == 3 ){
            move.y /= 3;
            for(int i=0;i<2;i++){
                auto line = Sprite::createWithSpriteFrameName("paper_line.png");
                line->setPosition(cPos + move*(i-0.5f));
                line->setScale(scale);
                line->setRotation(90);
                line->setVisible(false);
                addChild(line, BOTTOM_LEVEL+2);
                _line.push_back(line);
            }
        }else{
            auto line = Sprite::createWithSpriteFrameName("paper_line.png");
            line->setPosition(cPos);
            line->setScale(scale);
            line->setVisible(false);
            addChild(line, BOTTOM_LEVEL+2);
            _line.push_back(line);
            
            int nline = (_dividePiece)/2 -1 ;
            float center = (nline-1) /2.0f;
            move.y /= (nline+1);
            for(int i=0;i<nline;i++){
                auto line = Sprite::createWithSpriteFrameName("paper_line.png");
                line->setPosition(cPos + move*(i-center));
                line->setScale(scale);
                line->setRotation(90);
                line->setVisible(false);
                addChild(line, BOTTOM_LEVEL+2);
                _line.push_back(line);
            }
        }
    }
    

    _StickyRadius = powf(img[0]->ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
    
    
}

//花
void CCutImage::CreateFlower(float scale,int num,int c){   //花
    char picname[20],child[10];
    
    sprintf(picname, "ani/%s.csb",_name);
    sprintf(child, "%d",c);
    auto obj = CSLoader::createNode(picname)->getChildByName(child);
    int totalPiece = obj->getChildByName("0")->getTag();
    if(num == -1)_dividePiece = totalPiece;
    else _dividePiece = num;
    _scale = scale;
    _divided = false;
    

    int gPicec = totalPiece / _dividePiece;
   // img = new TRectSprite[_dividePiece * _fullAmount];
    _StickyData = new StickyData[_dividePiece * _fullAmount];
    
    for(int k=0;k<_fullAmount;k++){
        sprintf(picname, "%s_f%02d.png",_name,totalPiece);
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
            TouchSprite *newimg = new TRectSprite;
            newimg->setImgInfo_flower(i,gPicec,_StickyData[number]._imgPos,_StickyData[number]._imgAngle,Vec2(scale,scale));
            newimg->setCollisionInfo(_dividePiece);
            newimg->setPosition(_pos + _dPos*k);
            newimg->setSticky(number);
            newimg->setVisible(false);
            addChild(newimg->getNode(), BOTTOM_LEVEL+2);
            img.push_back(newimg);
            
            _StickyData[number]._NodeAngle = 0;
            _StickyData[number]._NodePos = img[number]->getPosition();
            _StickyData[number].isSticky = true;
        }
        
    }
    
    _StickyRadius = powf(img[0]->ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
    
    
}

// 水
void CCutImage::CreateWater(float scale,int num){  // 水
    char picname[20];
    
    _dividePiece = num;
    _scale = scale;
    _divided = false;

    _StickyData = new StickyData[_dividePiece * _fullAmount];
   // img = new TRectSprite[_dividePiece * _fullAmount];
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
       // float height = 200*PicScale.y;
        
        for (int i = 0; i < _dividePiece; i++) {
            TouchSprite *newimg = new TRectSprite;
            int number = k*_dividePiece+i;
            newimg->setImgInfo_water(pos,angle,PicScale);
            newimg->setCollisionInfo(_dividePiece);
            newimg->setPosition(_pos + _dPos*k);
            newimg->setSticky(number);
            newimg->setVisible(false);
            newimg->setWaterline(_dividePiece);
            addChild(newimg->getNode(), BOTTOM_LEVEL+1);
            img.push_back(newimg);
            
            float y= img[number]->getPicHeight() * (i+0.5f);
            Point move = Point(0,-135+y);
            _StickyData[number].createImgData(1);
            _StickyData[number]._NodeAngle = angle[0];
            _StickyData[number]._NodePos = img[number]->getPosition();
            _StickyData[number]._imgPos[0] = move;
            _StickyData[number]._imgAngle[0] = 0;
            _StickyData[number].isSticky = true;
            
        }
    }
    
   // if(_hasline){
        Vec2 dmove = Vec2(0,img[0]->getPicHeight());
        int n_line =_dividePiece;
        float c_center = (n_line-1) /2.0f;
        
        for(int k=0;k<_fullAmount;k++){
            Vec2 centerPos =_pos + _dPos*k +Vec2(-70,(dmove.y+20)/2);  // 水杯底厚14
            for (int i = 0; i <n_line; i++) {
                auto line = Sprite::createWithSpriteFrameName("water_line.png");
                Vec2 m = (i- c_center) * dmove;
                line->setPosition(centerPos + m);
                line->setScale(scale);
                line->setRotation(0);
             //   line->setVisible(false);
                addChild(line, BOTTOM_LEVEL+2);
                _line.push_back(line);
            }
        }
  //  }
    
    _StickyRadius = powf(img[0]->ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
}

//非連續物件
void CCutImage::CreateNormalImg(float scale,int num,int c){   //非連續物件
    char picname[20],child[10];
    
    sprintf(picname, "ani/%s.csb",_name);
    sprintf(child, "%d",c);
    auto obj = CSLoader::createNode(picname)->getChildByName(child);
    int totalPiece = obj->getChildByName("0")->getTag();
    if(num == -1)_dividePiece = totalPiece;
    else _dividePiece = num;
    _scale = scale;
    _divided = false;

    int gPicec = totalPiece / _dividePiece;
   // img = new TRectSprite[_dividePiece * _fullAmount];
    _StickyData = new StickyData[_dividePiece * _fullAmount];

    for(int k=0;k<_fullAmount;k++){
        sprintf(picname, "%s_%d.png",_name,totalPiece);
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
            TouchSprite *newimg = new TRectSprite;
            newimg->setImgInfo(picname,gPicec,_StickyData[number]._imgPos,_StickyData[number]._imgAngle,Vec2(scale,scale));
            newimg->setCollisionInfo(_dividePiece);
            newimg->setPosition(_pos + _dPos*k);
            newimg->setSticky(number);
            newimg->setVisible(false);
            addChild(newimg->getNode(), BOTTOM_LEVEL+2);
            img.push_back(newimg);
            
            _StickyData[number]._NodeAngle = 0;
            _StickyData[number]._NodePos = img[number]->getPosition();
            _StickyData[number].isSticky = true;
            
        }
    }
    
    if(_hasline){
        Vec2 dmove;
        if(_mode == 4) dmove = Vec2(220,0);
        else  dmove = Vec2(img[0]->getPicWidth(),0);

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
    
    
    _StickyRadius = powf(img[0]->ImgRadius, 2);
    touchedAmount = 0; //被點擊的數量
    rotateImg = NULL;
    rotateId = -1;
}

void CCutImage::CreatePancake(float scale,int num){  // 圓形
    char picname[20];
    
    _dividePiece = num;
    _scale = scale;
    _divided = false;
    
   // img = new TCircleSprite[_dividePiece * _fullAmount];
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
            TouchSprite *newimg = new TCircleSprite;
            int number = k*_dividePiece+i;
            float angle[1] = {(360.0f / _dividePiece)*i};
            Point pos[1] = {_pos + _dPos*k};
            newimg->setImgInfo(picname,1,pos,angle,Vec2(scale,scale));
            newimg->setCollisionInfo(_dividePiece);
            newimg->setSticky(number);
            newimg->setVisible(false);
            addChild(newimg->getNode(), BOTTOM_LEVEL+1);
            img.push_back(newimg);
            
            _StickyData[number].createImgData(1);
            _StickyData[number]._NodeAngle = angle[0];
            _StickyData[number]._NodePos = img[number]->getPosition();
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

    _StickyRadius = powf(img[0]->ImgRadius, 2);
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
                    img[number]->setPosition(_StickyData[number]._NodePos);
                    img[number]->setRotation(_StickyData[number]._NodeAngle);
                    img[number]->setSticky(number);
                     _StickyData[number].setSticky(number);
                    
                }
            }
        }
        break;
        default: //非連續用
        {
            for(int k=0; k<_fullAmount; k++){
                for(int i = 0; i < _dividePiece; i++){
                    int number = k*_dividePiece +i;
                    img[number]->setImgPandR(_StickyData[number]._imgPos, _StickyData[number]._imgAngle);
                    img[number]->setPosition(_StickyData[number]._NodePos);       //設定圖片位置與角度
                    img[number]->setRotation(_StickyData[number]._NodeAngle);
                    img[number]->setSticky(number);                          //紀錄區域
                    _StickyData[number].setSticky(number);
                }
            }
        }

        break;
    }
    
}

void CCutImage::divide(bool d) {
    _divided = d;
    
    if(_divided){
        setCutPos();
        for(int i=0; i<_fullImg.size(); i++){
            _fullImg[i]->setGLProgramState(grayGLProgrameState);
            _fullImg[i]->setOpacity(100);
        }
        rotateImg == NULL;
    }else{
        for(int i=0; i<_fullAmount; i++){
            _fullImg[i]->setOpacity(255);
            _fullImg[i]->setGLProgramState(colorGLProgrameState);
        }
    }
    
    for(int i = 0; i < _dividePiece*_fullAmount; i++){
        img[i]->setVisible(d);
    }
    
    if(_hasline) {
        for(int i=0;i<_line.size();i++)_line[i]->setVisible(d);
    }
}

bool CCutImage::touchesBegin(cocos2d::Point inPos, int id) {
	if (!_divided)return false;
    for (int i = 0; i < _dividePiece*_fullAmount ; i++) {
        if (img[i]->touchesBegin(inPos, id)) {
            if (rotateImg == NULL) {
                rotateImg = img[i];
            }

            int sticky = img[i]->ResetSticky();        //重置磁鐵.釋放區域
            if (sticky != -1) {
                img[i]->setAtFinger(inPos);
                if(_mode == 2) {                 //花不用重置
                    img[i]->setSticky(sticky);
                    return true;
                }
                
                _StickyData[sticky].isSticky = false;
                if(_mode == 3){                       //水的特殊需求 移開時其他往下一層
                    int max = (sticky ) / _dividePiece + 1;
                    for(int kk = sticky+1;kk < max * _dividePiece ; kk++ ){
                        if(!_StickyData[kk].isSticky)return true;
                        CCLOG("NO.%d down  max = %d",kk,max * _dividePiece);
                        int number =_StickyData[kk]._num;
                        img[number]->downOneFloor();
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
        if( img[i]->touchesMoved(inPos, id)) return true;
	}
	return false;

}

void CCutImage::touchesEnded(cocos2d::Point inPos, int id) {
	if (!_divided)return;

	for (int i = 0; i < _dividePiece*_fullAmount; i++) {
		if (img[i]->touchesEnded(inPos, id)) {
			if (rotateImg == img[i]) rotateImg = NULL;
			Sticky(img[i],i,inPos);  //判斷是否吸上去
		}
	}
}


void CCutImage::Sticky(TouchSprite *img,int number,Point pt) {
    for(int k=0;k < _fullAmount; k++){
        auto posInNode = _fullImg[k]->convertToNodeSpace(pt);   //位置靠近磁鐵區域
        if (Rect(0,0,_fullImg[k]->getContentSize().width,_fullImg[k]->getContentSize().height).containsPoint(posInNode)) {
            int stickyNum = -1;
            if(_mode == 2){              //花會回固定位置
                stickyNum = img->getSticky();
            }else {
                float angle = img->getAngle();
                float preDAngle = 1000, DAngle;
                for (int i = k*_dividePiece; i < _dividePiece*(k+1); i++) {  //判斷和哪個角度最靠近
                    if (_StickyData[i].isSticky == false) {
                        DAngle = abs(_StickyData[i]._NodeAngle - angle);   //算角度差
                        if (DAngle < preDAngle) {            //如果比上次資料小  紀錄這次資料
                            preDAngle = DAngle;
                            stickyNum = i;
                        }
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
