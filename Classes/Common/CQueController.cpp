
#include "CQueController.h"
#include "cocostudio/CocoStudio.h"

#define QUEX_POS 1024
#define QUEY_POS 1360

#define ANSX_POS 1024
#define ANSY_POS 768


CQueController::CQueController(int iUnitNo, Node &rootNode, cocos2d::Layer &parent)
{
	_parentLayer = &parent;
	_curUnit = iUnitNo;
	_curQueNo = 5;  // 預設顯示第一題

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("quecontrol.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("items/pancake1012.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("items/pancake0203.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("items/pancake0405.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("items/pancake0608.plist");

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Fraction_Wood.plist");
    
	switch (_curUnit)
	{
		case 1:
            equalData = UNIT_demo;
			//equalData = UNIT_1;
            break;
		case 2:
            equalData = UNIT_demo;
			//equalData = UNIT_2;
            break;
		case 3:
            equalData = UNIT_demo;
			//equalData = UNIT_3;
            break;
		case 4:
            equalData = UNIT_demo;
			//equalData = UNIT_4;
            break;
		case 5:
            equalData = UNIT_demo;
            //equalData = UNIT_5;
            break;
	}
    
	int equal = (rand() % equalData[_curQueNo - 1][0]) + 1;
	_curEqual = equalData[_curQueNo - 1][equal];

	//題目-答案
    try_topic = new fraction(_curUnit,_curQueNo,_curEqual);
    try_topic->setPosition(150,0);
    _parentLayer->addChild(try_topic);
    
	//圖片
	char pic[20];
	//sprintf(pic, "pancake%d_01.png", _curEqual);
    sprintf(pic, "topic1_wood_%02d.png", _curEqual);
	try_img = new combination(pic, 1.0f);
	_parentLayer->addChild(try_img);
    
	//按鈕設定
	setBtn(rootNode,parent);

	// 等分物件的控制選單
    _equalController = CEqualController::create();
    _equalController->init("Fracrion_Btn.plist", "equalcontrolnode.csb");
    _equalController->setPosition(1830, 750);
    _equalController->setScreenLoc(Point(1830, 750));
    parent.addChild(_equalController, EQULBOARD_LEVEL);
    _equalController->setVisible(true);
    _equalController->setEqualQuantity(equalData, _curQueNo, _curEqual);  //內部自動呼叫 reset()

	_bBackMenu = false;

	_bFracBoardOn = false;
	_bDivided = false;	// 預設沒有平分
	_bAnswer = false;
	_bShowImg = true;


	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("quecontrol.plist");
	//SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("items/pancake0608.plist");
}

void CQueController::setBtn(Node &rootNode, cocos2d::Layer &parent) {
	// 設定前一題與下一題按鈕
//    Sprite *pBtn = (Sprite *)rootNode.getChildByName("prevque_btn");
//    Point pt = pBtn->getPosition();
//    _prevBtn.setButtonInfo("prevque_off.png", "prevque_on.png", parent, pt, INTERFACE_LEVEL);
//    if(_curQueNo == 1)_prevBtn.setEnabled(false);
//    rootNode.removeChildByName("prevque_btn");

//    pBtn = (Sprite *)rootNode.getChildByName("nextque_btn");
//    pt = pBtn->getPosition();
//    _nextBtn.setButtonInfo("nextque_off.png", "nextque_on.png", parent, pt, INTERFACE_LEVEL);
//    if (_curQueNo == QUEDATA[_curUnit-1])_nextBtn.setEnabled(false);
//    rootNode.removeChildByName("nextque_btn");

	// 設定重新出題按鈕
	Sprite *pBtn = (Sprite *)rootNode.getChildByName("reset_btn");
	Point pt = pBtn->getPosition();
	_resetQueBtn.setButtonInfo("reset.png", "reset.png", parent, pt, INTERFACE_LEVEL);
	rootNode.removeChildByName("reset_btn");

	// 設定圖例顯示按鈕
//    pBtn = (Sprite *)rootNode.getChildByName("example_on");
//    pt = pBtn->getPosition();
//    _itemBtn.setButtonInfo("example_off.png", "example_on.png", parent, pt, INTERFACE_LEVEL);
//    _itemBtn.setButtonOn();
//    rootNode.removeChildByName("example_on");

	// 設定顯示答案按鈕
//    pBtn = (Sprite *)rootNode.getChildByName("answer_btn");
//    pt = pBtn->getPosition();
//    _answerBtn.setButtonInfo("answer_off.png", "answer_on.png", parent, pt, INTERFACE_LEVEL);
//    rootNode.removeChildByName("answer_btn");

	// 設定顯示均分選單的按鈕
//    pBtn = (Sprite *)rootNode.getChildByName("equal_btn");
//    pt = pBtn->getPosition();
//    _equalBtn.setButtonInfo("equal_off.png", "equal_on.png", parent, pt, INTERFACE_LEVEL);
//    rootNode.removeChildByName("equal_btn");

	// 回選單
//    pBtn = (Sprite *)rootNode.getChildByName("menu_btn");
//    pt = pBtn->getPosition();
//    _menuBtn.setButtonInfo("menu_on.png", "menu_off.png", parent, pt, INTERFACE_LEVEL);
//    rootNode.removeChildByName("menu_btn");
    
    //題目數字
    char pic[20];
    Que_number = (Text *)rootNode.getChildByName("que_number");
    sprintf(pic,"%d",_curEqual);
    Que_number->setString(pic);
}

void CQueController::reset(int queNO = 0, int equal = 0)   	//queNo =  題號變化量  / equal = 數字變化 (0 = 隨機)
{	
	//題號改變 重設答案
	if (queNO != 0) {
		_curQueNo += queNO;
		if (_curQueNo < 1) _curQueNo = QUEDATA[_curUnit - 1];       //前一題
		else if (_curQueNo > QUEDATA[_curUnit - 1]) _curQueNo = 1;  //後一題
	}

	if (equal == 0)//重設數字
	{
		do {
			equal = (rand() % equalData[_curQueNo - 1][0]) + 1;
			equal = equalData[_curQueNo - 1][equal];
		} while (equal == _curEqual && equalData[_curQueNo - 1][0] != 1);
	}
    
    _curEqual = equal;
	_parentLayer->removeChild(try_topic);

    try_topic = new fraction(_curUnit, _curQueNo,_curEqual);
    try_topic->setPosition(150,0);
    _parentLayer->addChild(try_topic);
    
	_equalController->setEqualQuantity(equalData, _curQueNo, _curEqual); // 內部自動呼叫 reset()

//	answer->setVisible(false);
	//_answerBtn.setButtonOff();

	//數字改變->重製圖片
	_parentLayer->removeChild(try_img);
	delete try_img;
	char pic[20];
	//sprintf(pic, "pancake%d_01.png", _curEqual);
    sprintf(pic, "topic1_wood_%02d.png", _curEqual);
	try_img = new combination(pic, 1.0f);
	_parentLayer->addChild(try_img);

    sprintf(pic,"%d",_curEqual);
    Que_number->setString(pic);
    
	_equalController->setVisible(true);

	//按鈕重製
	//_equalBtn.setButtonOff();
	//_equalBtn.setEnabled(true);
	//_itemBtn.setButtonOn();
	_bDivided = false;
	_bAnswer = false;
    _bFracBoardOn = false;
	_bShowImg = true;
}


CQueController::~CQueController()
{
    if(try_img != NULL)delete try_img;
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

bool CQueController::getBoardStatus()
{
	return(_bFracBoardOn);
}

bool CQueController::goBackToMenu()
{
	return(_bBackMenu);
}

bool CQueController::touchesBegin(Point inPt, int iId, int iMode)
{
	if( !_bFracBoardOn ) {
		//_prevBtn.touchesBegin(inPt);
		//_nextBtn.touchesBegin(inPt);
		_resetQueBtn.touchesBegin(inPt);
		//_itemBtn.touchesBegin(inPt);
		//_answerBtn.touchesBegin(inPt);
		//_menuBtn.touchesBegin(inPt);
		if (iMode == MOVEINGOBJ_MODE && _bShowImg)try_img->touchesBegin(inPt, iId);
	}

	//if (_bFracBoardOn)
    _equalController->touchesBegin(inPt); // 平分按鈕顯示才需要呼叫
	//if (!_bDivided) _equalBtn.touchesBegin(inPt);

	return true;
}



bool CQueController::touchesMoved(Point inPt, int iId, int iMode)
{
	if (!_bFracBoardOn) {
		//_prevBtn.touchesMoved(inPt);
		//_nextBtn.touchesMoved(inPt);
		_resetQueBtn.touchesMoved(inPt);
		//_itemBtn.touchesMoved(inPt);
		//_answerBtn.touchesMoved(inPt);
		//_menuBtn.touchesMoved(inPt);
		if (iMode == MOVEINGOBJ_MODE  && _bShowImg)try_img->touchesMoved(inPt, iId);
	}
	//if (_bFracBoardOn)
	_equalController->touchesMoved(inPt);
	//if (!_bDivided) _equalBtn.touchesMoved(inPt);


	return true;
}

bool CQueController::touchesEnded(Point inPt, int iId, int iMode)
{
	//if (_bFracBoardOn) {  //平分開啟
		int t = _equalController->touchesEnded(inPt);  // 判定是否按下 確定按鈕，如果是則關閉平分按鈕的功能
		if (t >= 1) { // 傳回 0 代表目前選在平分的數字上
			reset(0,t);
			return true;
		}
	//}
	//else {
//        if (_prevBtn.touchesEnded(inPt)) { // 切換到前一題
//            reset(-1);
//            _nextBtn.setEnabled(true);
//            if (_curQueNo == 1)_prevBtn.setEnabled(false);
//            return true;
//        }
//        else if (_nextBtn.touchesEnded(inPt)) {     // 下一題按鈕被按下
//            reset(1);
//            _prevBtn.setEnabled(true);
//            if (_curQueNo == QUEDATA[_curUnit-1])_nextBtn.setEnabled(false);
//            return true;
//        }
		if (_resetQueBtn.touchesEnded(inPt)) { // 重新出題按鈕被按下， 本題重新出平分量
			reset();
			return true;
		}
//        else if (_answerBtn.touchesEnded(inPt)) { // 顯示答案按鈕被按下
//            _bAnswer = !_bAnswer;
//            try_topic->setVisible(_bAnswer);
//            return true;
//        }
//        else if (_itemBtn.touchesEnded(inPt)) { // 顯示切換物件顯示按鈕被按下
//            _bShowImg = !_bShowImg;
//            try_img->setVisible(_bShowImg);
//            return true;
//        }
//        else if (_menuBtn.touchesEnded(inPt)) { // 顯示切換物件顯示按鈕被按下
//            _bBackMenu = true;
//            return true;
//        }
		if (iMode == MOVEINGOBJ_MODE && _bShowImg) {  //圖片移動與旋轉
			try_img->touchesEnded(inPt, iId);  
			return true;
		}
	//}

//    if ( _equalBtn.touchesEnded(inPt) ) { // 平分按鈕被按下
//        if (!_bDivided) {
//            _bFracBoardOn = _equalBtn.getStatus();
//            _equalController->setVisible(_bFracBoardOn);
//
//        }
//        return true;
//    }
	return false;
}
