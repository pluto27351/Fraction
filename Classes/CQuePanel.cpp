
#include "CQuePanel.h"
#include "cocostudio/CocoStudio.h"

#define SCENE_POS Vec2(1365.5,768)
#define QUE_POS Vec2(SCENE_POS.x,SCENE_POS.y + 527)
#define ANS_POS Vec2(SCENE_POS.x + 650, SCENE_POS.y - 400)


CQuePanel::~CQuePanel()
{
    if (_cutImage != NULL)delete _cutImage;
    if (_ans != NULL)delete _ans;
    if (_que != NULL)delete _que;
}

CQuePanel::CQuePanel(int iUnitNo, Node &rootNode, cocos2d::Layer &parent)
{
	_parentLayer = &parent;
	_curUnit = iUnitNo;
	_curQue = 0;  // 預設顯示第一題
    _curNum = -1;
    _objNum = UNIT_OBJ[_curUnit - 1][_curQue - 1]; //圖片編號
    
    //設定分母選單
    auto obj = rootNode.getChildByName("numPic");
    _numSwitcher.init("n-", "white.png", parent, obj, SWITCHBOARD_LEVEL);
    rootNode.removeChildByName("numPic");

    _blackMask = (Sprite *)Sprite::createWithSpriteFrameName("backcolor.png");
    _blackMask->setPosition(SCENE_POS);
    _blackMask->setScale(5.5, 4);
    _blackMask->setVisible(false);
    _parentLayer->addChild(_blackMask,INTERFACE_LEVEL);

    //按鈕設定
    setBtn(rootNode, parent);
    
    //出題
    _ans = NULL;
    _que = NULL;
    _cutImage = NULL;
    reset(1);
    


}

void CQuePanel::reset(int que, int num)  //queNo = 題號變化量(+1.0.-1) / num = 數字 (0=自己)
{
    //按鈕關閉隱藏
    _ansBtn.setStatus(false);
    _numBtn.setStatus(false);
    _cutBtn.setStatus(false);
    _cutBtn.setEnabled(true);
    
    _blackMask->setVisible(false);
    _bDivided = false;
    _bAnswer = false;
    _bFracBoardOn = false;
    _bnum = false;
    _bResetActive = false;
    
    //題目變化
    if(num!= 0) _curNum = num;
    if (que != 0) {
        _curQue += que;
        if (_curQue < 1) _curQue = QUEDATA[_curUnit - 1];         //避免超過範圍１～最後一題
        else if (_curQue > QUEDATA[_curUnit - 1]) _curQue = 1;
        _curNum = -1;
    }
    
    //重設答案     //重設題目      //切塊圖還原
    if(_ans != NULL) {_parentLayer->removeChild(_ans);  delete _ans;}
    if(_que != NULL) {_parentLayer->removeChild(_que);  delete _que;}
    if(_cutImage != NULL) {_parentLayer->removeChild(_cutImage); delete _cutImage;}
    
    _objNum = UNIT_OBJ[_curUnit - 1][_curQue - 1]; //圖片編號
    
    int queCate = UNIT_QUE[_curUnit - 1][_curQue - 1];
    
    switchdata = UNIT[_curUnit - 1][_curQue - 1];
    switch (queCate) {
        case 1:                                 //一般題
            setQue(queCate);
            break;
        case 2:                                 //變量題 chap4-7~12
            setQue_quantity();
            break;
        case 3:                                 //比例題 chap5-3.4.6
            setQue_picline();
            break;
        case 4:                                 //倍數題 chap5-其他題
            setQue_multiple();
            break;
        case 5:                                 //線段題 chap3-6
            setQue_line();
            break;
        case 11:                                //分子題1 chap2-3.5.8.11
            setQue(queCate);
            break;
        case 12:                                //分子題2 chap3-7~12
            setQue(queCate);
            break;
    }

    
}

void CQuePanel::setQue(int k) {
    // 獲取題目分母資訊  隨幾取分母
    if(_curNum == -1){
        srand(time(NULL));
        int num = (rand() % switchdata[0]) + 1;
        _curNum = switchdata[num];
    }

    //設定題目
    _que = new CAnsCreater();
    _que->queCreater(_curUnit, _curQue, _curNum);
    _que->setPosition(QUE_POS);
    _parentLayer->addChild(_que);
    
    
    //設定答案
    _ans = new CAnsCreater(_curUnit, _curQue, _curNum);
    _ans->setPosition(ANS_POS);
    _ans->setVisible(false);
    _parentLayer->addChild(_ans, 1);

    _numSwitcher.setEnabledBtns(switchdata, _curNum);
    _numSwitcher.setLockNum(_curNum - 2, true);
    _numSwitcher.setVisible(false);
    
    //設定圖片
    _curPicAmount = 1;
    if (_curUnit == 4 || _curUnit == 3 ||_curUnit == 2) _curPicAmount = 2;

    if(k == 11 ||k == 12){  //分子題 獲取答案分母做切分
        int a= _ans->getA();
        _cutImage = new CCutImage(_objNum,_curPicAmount, 1.0f,a);
    }else{
        _cutImage = new CCutImage(_objNum,_curPicAmount, 1.0f,_curNum);
    }
    _parentLayer->addChild(_cutImage);
    
}

//比例題 chap5-3.4.6
void CQuePanel::setQue_picline() {  //比例題 chap5-3.4.6
    if(_curNum == -1){
        srand(time(NULL));
        int num = (rand() % switchdata[0]) + 1;
        _curNum = switchdata[num];
    }

    int k = 0;
    int _c = 0,_b = 0;
    do {
        _c = rand() % 6;
        _b = rand() % 5;
        k = UNIT5[_curNum - 2][_c][_b];  //_curNum = 2~6 , _c = 0~5  , _b = 0~4
        _c += 2; _b += 1;
    } while (k == 0);
    
    //設定題目
    _que = new CAnsCreater();
    _que->queCreater(_curUnit, _curQue, _curNum, _c, _b);
    _que->setPosition(QUE_POS);
    _parentLayer->addChild(_que);
    
    //設定答案
    _ans = new CAnsCreater(_curUnit, _curQue, _curNum, _c, _b);
    _ans->setPosition(ANS_POS);
    _ans->setVisible(false);
    _parentLayer->addChild(_ans, 1);
    
    //設定選單
    _numSwitcher.setEnabledBtns(switchdata, _curNum);
    _numSwitcher.setLockNum(_curNum - 2, true);
    _numSwitcher.setVisible(false);
    
    //設定圖片
    _cutImage = new CCutImage(_objNum, 1.0f,_c,_curNum,_b);
    _parentLayer->addChild(_cutImage);
    _bDivided = true;
   // _cutImage->divide(_bDivided); //切圖片
    _cutImage->setdivideStatus(_bDivided);
    _bCutDown = _bDivided;
    _cutBtn.setEnabled(false);
}

//倍數題 chap5-其他題
void CQuePanel::setQue_multiple() {  //倍數題 chap5-其他題
    if(_curNum == -1){
        srand(time(NULL));
        int num = (rand() % switchdata[0]) + 1;
        _curNum = switchdata[num];
    }
    int que_b = switchdata[11];
    int c = 0,ans_b = 0;
    int k = (2 * _curNum) / que_b;  //取上限 ２倍分母/分子 ＝ 倍數上限
    bool b;
    do {
        c = (rand() % k)+1; //隨機取倍數 <上限
        if(k == 2) {c = k; _c =-1;}
    } while ((c == 1 || c == _c));    //分母太小會沒有數字c出

    _c =c;
    ans_b = _c * que_b;
    
    if(ans_b > _curNum) _curPicAmount = 2;
    else _curPicAmount = 1;
    
    //設定題目
    _que = new CAnsCreater();
    _que->queCreater(_curUnit, _curQue, _curNum, _c, que_b);
    _que->setPosition(QUE_POS);
    _parentLayer->addChild(_que);
    
    //設定答案
    _ans = new CAnsCreater(_curUnit, _curQue, _curNum, _c, que_b);
    _ans->setPosition(ANS_POS);
    _ans->setVisible(false);
    _parentLayer->addChild(_ans, 1);
    
    _numSwitcher.setEnabledBtns(switchdata, _curNum);
    _numSwitcher.setLockNum(_curNum - 2, true);
    _numSwitcher.setVisible(false);
    
    //設定圖片
    _cutImage = new CCutImage(_objNum,_curPicAmount, 1.0f,_curNum);
    _parentLayer->addChild(_cutImage);
}

//線段題 chap3-6
void CQuePanel::setQue_line(){  //線段題 chap3-6
    // 獲取題目分母資訊  隨幾取分母
    if(_curNum == -1){
        srand(time(NULL));
        int num = (rand() % switchdata[0]) + 1;
        _curNum = switchdata[num];
    }
    
    int q[3]={-1};
    do{
        int qq[3];
        qq[0] = rand() %  (2*_curNum);
        qq[1] = rand() %  (2*_curNum);
        qq[2] = rand() %  (2*_curNum);
        q[0] = qq[0];
        if(qq[1] < q[0]){
            q[1]=q[0];q[0]=qq[1];
        }
        else {
            q[1] = qq[1];
        }
        
        if(qq[2] < q[1]){
            q[2]=q[1];
            if(qq[2] < q[0]){
                q[1]=q[0]; q[0]=qq[2];
            }
            else{
                q[1]=qq[2];
            }
        }else{
            q[2] = qq[2];
        }
    }while(q[0] == q[1] || q[0] == q[2] ||q[1] == q[2]);
    
    CCLOG("a=%d , b=%d , c=%d",q[0],q[1],q[2]);
    
    
    //設定題目
    _que = new CAnsCreater();
    _que->queCreater(_curUnit, _curQue, _curNum);
    _que->queLineCreater(_curNum,q);
    _que->setPosition(QUE_POS);
    _parentLayer->addChild(_que);
    
    //設定答案
    _ans = new CAnsCreater(_curNum,q);
    _ans->setPosition(QUE_POS);
    _ans->setVisible(false);
    _parentLayer->addChild(_ans, 1);
    
    //選單
    _numSwitcher.setEnabledBtns(switchdata, _curNum);
    _numSwitcher.setLockNum(_curNum - 2, true);
    _numSwitcher.setVisible(false);
    
    //設定圖片
    _curPicAmount = 1;
    _cutImage = NULL;
    _cutBtn.setEnabled(false);
 
}

//變量題 chap4-7~12
void CQuePanel::setQue_quantity() {  //變量題 chap4-7~12
    if(_curNum == -1){
        srand(time(NULL));
        int num = (rand() % switchdata[0]) + 1;
        _curNum = switchdata[num];
    }

    int c,r =UNIT4[_curQue-7][0];
    do{
        int k = (rand() % r) +1;
        c = UNIT4[_curQue-7][k];
    }while( c % _curNum != 0 || (_curNum <5  && c == _c) || (_curNum == 6 && (_curQue ==9 ||_curQue ==10|| _curQue == 12) && c == _c)) ;
    _c = c;
    
    
    //設定題目
    _que = new CAnsCreater();
    _que->queCreater(_curUnit, _curQue, _curNum, _c);
    _que->setPosition(QUE_POS);
    _parentLayer->addChild(_que);
    
    //設定答案
    _ans = new CAnsCreater(_curUnit, _curQue,  _curNum);
    _ans->setPosition(ANS_POS);
    _ans->setVisible(false);
    _parentLayer->addChild(_ans, 1);
    
    //設定選單
    _numSwitcher.setEnabledBtns(switchdata, _curNum);
    _numSwitcher.setLockNum(_curNum - 2, true);
    _numSwitcher.setVisible(false);
    
    //設定圖片
    _curPicAmount = 2;
    _cutImage = new CCutImage(_objNum,_curPicAmount, 1.0f,_curNum,_c);
    _parentLayer->addChild(_cutImage);
}


void CQuePanel::setBtn(Node &rootNode, cocos2d::Layer &parent) {
	//前一題
	auto pt = rootNode.getChildByName("prevbtn")->getPosition();
	auto scale = rootNode.getChildByName("prevbtn")->getScale();
	_prevBtn.setButtonInfo("next_L.png", "next_L_click.png", parent, pt, INTERFACE_LEVEL);
	_prevBtn.setScale(scale);
	if (_curQue == 0)_prevBtn.setEnabled(false);
	rootNode.removeChildByName("prevbtn");

	//下一題
	pt = rootNode.getChildByName("nextbtn")->getPosition();
	scale = rootNode.getChildByName("nextbtn")->getScale();
	_nextBtn.setButtonInfo("next_R.png", "next_R_click.png", parent, pt, INTERFACE_LEVEL);
	_nextBtn.setScale(scale);
	if (_curQue == QUEDATA[_curUnit - 1])_nextBtn.setEnabled(false);
	rootNode.removeChildByName("nextbtn");

	// 設定答案按鈕
    pt = rootNode.getChildByName("answerbtn")->getPosition();
	_ansBtn.setButtonInfo("ans.png", "ans_click.png", parent, pt, INTERFACE_LEVEL);
    rootNode.removeChildByName("answerbtn");

	// 設定選擇分母按鈕
	pt = rootNode.getChildByName("numbtn")->getPosition();
	_numBtn.setButtonInfo("tool_number.png", "tool_number_click.png", parent, pt, INTERFACE_LEVEL);
	rootNode.removeChildByName("numbtn");

	// 設定切分按鈕
	pt = rootNode.getChildByName("cut")->getPosition();
	_cutBtn.setButtonInfo("tool_cut.png", "tool_cut_click.png","tool_cut_no.png", parent, pt, SWITCHBOARD_LEVEL);
	rootNode.removeChildByName("cut");


}

bool CQuePanel::getBoardStatus()
{
	return(_bnum);
}

bool CQuePanel::resetActive(){
    if(_bResetActive){
        _bResetActive= false;
        return true;
    }
    return false;
}
bool CQuePanel::cutDown(){
    if(_bCutDown){
        _bCutDown= false;
        return true;
    }
    return false;
}

bool CQuePanel::touchesBegin(Point inPt, int iId, int iMode)
{
    if (_numBtn.touchesBegin(inPt)) return true;          //分母按鈕
    
    if(_bnum){
        if ( _numSwitcher.touchesBegin(inPt) )return true; //分母選單
        else {                                             //點在選單外->關閉選單
            _bnum = false;
            _numBtn.setStatus(false);
            _numSwitcher.setVisible(_bnum);
            _blackMask->setVisible(_bnum);
        }
    }
    else{
        if (_cutBtn.touchesBegin(inPt))return true;
		if ( _prevBtn.touchesBegin(inPt) )return true;         //前一題
		if ( _nextBtn.touchesBegin(inPt) ) return true;		   //後一題
		if ( _ansBtn.touchesBegin(inPt) ) return true;		   //顯示答案
        if (iMode == HAND_MODE && _bDivided){
			if(_cutImage->touchesBegin(inPt, iId))return true; //切塊
        }
	}

	return false;
}



bool CQuePanel::touchesMoved(Point inPt, int iId, int iMode)
{
	
    _numBtn.touchesMoved(inPt);
    
    if(_bnum){
        _numSwitcher.touchesMoved(inPt);
    }
	else{
        _cutBtn.touchesMoved(inPt);
		_prevBtn.touchesMoved(inPt);
		_nextBtn.touchesMoved(inPt);
		_ansBtn.touchesMoved(inPt);

		if (iMode == HAND_MODE && _bDivided) _cutImage->touchesMoved(inPt, iId);
	}

	return true;
}

bool CQuePanel::touchesEnded(Point inPt, int iId, int iMode)
{
    if (_numBtn.touchesEnded(inPt)) {  // 分母按鈕被按下
        _bnum = !_bnum;
        _numSwitcher.setVisible(_bnum);
        _blackMask->setVisible(_bnum);
        return true;
    }
    
    if (_bnum){                       //分母選單
        if (_numSwitcher.touchesEnded(inPt)) {
            int num = _numSwitcher.getSelectNumber() + 2;
            reset(0, num);
            _bResetActive = true;
            return true;
        }
    }
    else {
        if (_cutBtn.touchesEnded(inPt)) {  // 剪刀按鈕被按下
            _bDivided = !_bDivided;

            _cutImage->divide(_bDivided); //切圖片
            _bCutDown = _bDivided;
            
            return true;
        }
		if (_prevBtn.touchesEnded(inPt)) { // 切換到前一題
            reset(-1);
            _bResetActive = true;
			_nextBtn.setEnabled(true);
			if (_curQue == 1)_prevBtn.setEnabled(false);
			return true;
		}
		if (_nextBtn.touchesEnded(inPt)) {     // 下一題按鈕被按下
			reset(1);
            _bResetActive = true;
			_prevBtn.setEnabled(true);
			if (_curQue == QUEDATA[_curUnit - 1])_nextBtn.setEnabled(false);
			return true;
		}
		if (_ansBtn.touchesEnded(inPt)) { // 答案按鈕被按下
			_bAnswer = !_bAnswer;
			_ans->setVisible(_bAnswer);
			return true;
		}
		if (iMode == HAND_MODE && _bDivided) {  //圖片移動與旋轉
			_cutImage->touchesEnded(inPt, iId);
		}

	}
	
	return false;
}

