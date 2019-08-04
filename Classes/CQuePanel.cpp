
#include "CQuePanel.h"
#include "cocostudio/CocoStudio.h"

//#define QUEX_POS 1024
//#define QUEY_POS 1360

#define QUE_POS Vec2(1024,1295)
#define ANS_POS Vec2(1600,500)

CQuePanel::~CQuePanel()
{
    CCLOG("delete quePanel");
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
    _blackMask->setPosition(Vec2(1024,768));
    _blackMask->setScale(4);
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
    int cate = queCate%100;
    int cate_data = queCate/100-1;
    switch (cate) {
        case 1:                                 //一般題
            switchdata = PIECE[_objNum];
            setQue(cate);
            break;
        case 2:                                 //變量題 chap4-7~12
            switchdata = PIECE_U4[cate_data];
            setQue(cate);
            break;
        case 3:                                 //比例題 chap5-3.4.6
            switchdata = PIECE_U5[_curQue-1];
            setQue_picline();
            break;
        case 4:                                 //倍數題 chap5-其他題
            switchdata = PIECE_U5[_curQue-1];
            setQue_multiple();
        case 5:                                 //線段題 chap3-6
            switchdata = PIECE[_curNum];
            setQue_line();
            break;
        case 11:                                //分子題1 chap2-3.5.8.11
            switchdata = PIECE_U2[cate_data];
            setQue(cate);
            break;
        case 12:                                //分子題2 chap3-7~12
            switchdata = PIECE_U3[cate_data];
            setQue(cate);
            break;
    }
    
    
    //按鈕關閉隱藏
    _ansBtn.setStatus(false);
    _numBtn.setStatus(false);
    _cutBtn.setStatus(false);
    
    _blackMask->setVisible(false);
    _bDivided = false;
    _bAnswer = false;
    _bFracBoardOn = false;
    _bnum = false;
    _bResetActive = false;
    
}

void CQuePanel::setQue(int k) {
    // 獲取題目分母資訊  隨幾取分母
    if(_curNum == -1){
        srand(time(NULL));
        int num = (rand() % switchdata[0]) + 1;
        _curNum = switchdata[num];
    }

    //設定題目
    if (k == 4) {   //????
        _que = new CAnsCreater();
        _que->queCreater(_curUnit, _curQue, _curNum);
        _que->setPosition(QUE_POS);
        _parentLayer->addChild(_que);
    }
    else {
        _que = new CAnsCreater();
        _que->queCreater(_curUnit, _curQue, _curNum);
        _que->setPosition(QUE_POS);
        _parentLayer->addChild(_que);
    }
    
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

    if(k == 11 ||k == 12){
        int a= _ans->getA();
        _cutImage = new CCutImage(_objNum,_curPicAmount, 1.0f,a);
    }else{
        _cutImage = new CCutImage(_objNum,_curPicAmount, 1.0f,_curNum);
    }
    _parentLayer->addChild(_cutImage);
    
}


void CQuePanel::setQue_picline() {  //chap5-3.4.6
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
//    _curPicAmount = 1;
//    if (_curNum < _c * _b) _curPicAmount = 2;
    _cutImage = new CCutImage(_objNum, 1.0f,_c,_curNum,_b);
    _parentLayer->addChild(_cutImage);
}

void CQuePanel::setQue_multiple() {  //chap5其餘題
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
    else _curPicAmount = 2;
    
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


void CQuePanel::setQue_line(){
    // 獲取題目分母資訊  隨幾取分母
    if(_curNum == -1){
        srand(time(NULL));
        int num = (rand() % switchdata[0]) + 1;
        _curNum = switchdata[num];
    }
}


void CQuePanel::setBtn(Node &rootNode, cocos2d::Layer &parent) {
	//前一題
	auto pt = rootNode.getChildByName("prevbtn")->getPosition();
	auto scale = rootNode.getChildByName("prevbtn")->getScale();
	_prevBtn.setButtonInfo("next_L.png", "next_L_click.png", parent, pt, INTERFACE_LEVEL);
	_prevBtn.setScale(scale);
	if (_curQue == 1)_prevBtn.setEnabled(false);
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
	_cutBtn.setButtonInfo("tool_cut.png", "tool_cut_click.png", parent, pt, SWITCHBOARD_LEVEL);
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

