
#include "CQuePanel.h"
#include "cocostudio/CocoStudio.h"

#define QUEX_POS 1024
#define QUEY_POS 1360

#define ANS_POS Vec2(1450,650)
#define QUE_POS Vec2(830,1200)

CQuePanel::CQuePanel(int iUnitNo, Node &rootNode, cocos2d::Layer &parent)
{
	_parentLayer = &parent;
	_curUnit = iUnitNo;
	_curQue = 1;  // 預設顯示第一題

	//獲取題目分母資訊
	switch (_curUnit){
		case 1:
			equalData = UNIT_1;  break;
		case 2:
			equalData = UNIT_2;  break;
		case 3:
			equalData = UNIT_3;  break;
		case 4:
			equalData = UNIT_4;  break;
		case 5:
			equalData = UNIT_5;  break;
	}

	//隨幾取分母
	int num = (rand() % equalData[_curQue - 1][0]) + 1;
	_curNum = equalData[_curQue - 1][num];

	//設定題目
	_que = new CAnsCreater();
	_que->queCreater(_curUnit, _curQue, _curNum);
	_que->setPosition(QUE_POS);
	_parentLayer->addChild(_que);

	//設定答案
	_ans = new CAnsCreater(_curUnit, _curQue, _curNum);
	_ans->setPosition(ANS_POS);
	_ans->setVisible(false);
	_parentLayer->addChild(_ans);

	//設定圖片
	//_cutImage = new CCutImage("stuff_muffin", 1.0f,_curNum);
    int pic= UNIT_OBJ[_curUnit-1][_curQue-1];
    _cutImage = new CCutImage(pic, 1.0f,_curNum);
	_parentLayer->addChild(_cutImage);

	//設定分母選單
    auto pt = rootNode.getChildByName("numPic")->getPosition();
    _numSwitcher.init("Q", "Q_okay.png", "Q_cut.png", parent, pt, SWITCHBOARD_LEVEL);
    _numSwitcher.setAsColumn();
    _numSwitcher.setEnabledBtns(equalData[_curQue-1], _curNum);
    _numSwitcher.setVisible(false);
    rootNode.removeChildByName("numPic");
    
    _blackMask = (Sprite *)Sprite::createWithSpriteFrameName("Q_backcolor.png");
    _blackMask->setPosition(Vec2(1024,768));
    _blackMask->setScale(4);
    _blackMask->setVisible(false);
    _parentLayer->addChild(_blackMask,INTERFACE_LEVEL);
    
	//按鈕設定
	setBtn(rootNode, parent);
    
	_bDivided = false;	// 預設沒有平分
	_bAnswer = false;
	_bnum = false;
    _bResetActive = false;
}

void CQuePanel::setBtn(Node &rootNode, cocos2d::Layer &parent) {
	//前一題
	auto pt = rootNode.getChildByName("prevbtn")->getPosition();
	auto scale = rootNode.getChildByName("prevbtn")->getScale();
	_prevBtn.setButtonInfo("Q_back.png", "Q_back.png", parent, pt, INTERFACE_LEVEL);
	_prevBtn.setScale(scale);
	if (_curQue == 1)_prevBtn.setEnabled(false);
	rootNode.removeChildByName("prevbtn");

	//下一題
	pt = rootNode.getChildByName("nextbtn")->getPosition();
	scale = rootNode.getChildByName("nextbtn")->getScale();
	_nextBtn.setButtonInfo("Q_next.png", "Q_next.png", parent, pt, INTERFACE_LEVEL);
	_nextBtn.setScale(scale);
	if (_curQue == QUEDATA[_curUnit - 1])_nextBtn.setEnabled(false);
	rootNode.removeChildByName("nextbtn");

	// 設定答案按鈕
    pt = rootNode.getChildByName("answerbtn")->getPosition();
	_ansBtn.setButtonInfo("Q_Answer.png", "Q_Answer_hover.png", parent, pt, INTERFACE_LEVEL);
    rootNode.removeChildByName("answerbtn");

	// 設定選擇分母按鈕
	pt = rootNode.getChildByName("numbtn")->getPosition();
	_numBtn.setButtonInfo("Q_leaf.png", "Q_leaf.png", parent, pt, INTERFACE_LEVEL);
	rootNode.removeChildByName("numbtn");

	// 設定切分按鈕
	pt = rootNode.getChildByName("cut")->getPosition();
	_cutBtn.setButtonInfo("Q_tool pic.png", "Q_tool pic_hover.png", parent, pt, SWITCHBOARD_LEVEL);
	rootNode.removeChildByName("cut");


}

void CQuePanel::reset(int que, int num)  //queNo = 題號變化量(+1.0.-1) / num = 數字變化 (0=自己)
{
	//題號有改變  改變分母
	if (que != 0) {  
		_curQue += que;
		if (_curQue < 1) _curQue = QUEDATA[_curUnit - 1];            //避免超過範圍１～最後一題
		else if (_curQue > QUEDATA[_curUnit - 1]) _curQue = 1;
        
        //隨機取分母
        do {
            num = (rand() % equalData[_curQue - 1][0]) + 1;
            num = equalData[_curQue - 1][num];
        } while (num == _curNum && equalData[_curQue - 1][0] != 1);

	}

    //分母有改變  重設答案＆重設題目&葉子數字
    if (num != 0) {
        _curNum = num;
        
        //重設答案
        _parentLayer->removeChild(_ans);  delete _ans;
        _ans = new CAnsCreater(_curUnit, _curQue, _curNum);
        _ans->setPosition(ANS_POS);
        _ans->setVisible(false);
        _parentLayer->addChild(_ans);
        
        //重設題目
        _parentLayer->removeChild(_que);  delete _que;
        _que = new CAnsCreater();
        _que->queCreater(_curUnit, _curQue, _curNum);
        _que->setPosition(QUE_POS);
        _parentLayer->addChild(_que);
        
    }
    
    //重設分母選單
    _numSwitcher.setEnabledBtns(equalData[_curQue-1], _curNum);
    _numSwitcher.setVisible(false);
    
    
    //切塊圖還原
    _parentLayer->removeChild(_cutImage);
    delete _cutImage;
    //_cutImage = new CCutImage("stuff_muffin", 1.0f,_curNum);
    int pic= UNIT_OBJ[_curUnit-1][_curQue-1];
    _cutImage = new CCutImage(pic, 1.0f,_curNum);
    //_cutImage = new CCutImage("stuff_muffin", 1.0f,_curNum);
    _parentLayer->addChild(_cutImage);
    
    //按鈕關閉隱藏
    _ansBtn.setStatus(false);
    _numBtn.setStatus(false);
    _cutBtn.setStatus(false);

    _blackMask->setVisible(false);
	_bDivided = false;
	_bAnswer = false;
	_bFracBoardOn = false;
	_bnum = false;
	
}


CQuePanel::~CQuePanel()
{
	if (_cutImage != NULL)delete _cutImage;
	if (_ans != NULL)delete _ans;
    if (_que != NULL)delete _que;
	//Director::getInstance()->getTextureCache()->removeUnusedTextures();
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
        else {
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

