//
//  功能 : 提供平分的選擇功能
//  使用 ： 先呼叫 init 設定相關的參數，然後呼叫 setEqualQuantity 設定本次題目所能提供的平分值
//			每次問題重設時，呼叫 reset 函式 
//   setEqualQuantity ： 傳入陣列的第一個儲存內容為這題所提供的平分值的數量
//	setScreenLoc  ： 要改變選單的位置，必須透過 setScreenLoc 函式，以反映選單的位置

#include "cocostudio/CocoStudio.h"
#include "CEqualController.h"

CEqualController * CEqualController::_pEqualController = nullptr;

CEqualController *CEqualController::create()
{ // 建立物件的實體

	if ( _pEqualController == nullptr) {
		_pEqualController = new (std::nothrow) CEqualController();
		if (_pEqualController) {
			_pEqualController->autorelease();
			return _pEqualController;
		}
		CC_SAFE_DELETE(_pEqualController);
		return nullptr;
	}
	else return _pEqualController;
}

CEqualController *CEqualController::getInstance()
{
	if (_pEqualController == nullptr) {
		_pEqualController = new (std::nothrow) CEqualController();
		if (_pEqualController) {
			_pEqualController->autorelease();
			return _pEqualController;
		}
		CC_SAFE_DELETE(_pEqualController);
		return nullptr;
	}
	return _pEqualController;
}


void CEqualController::init(char *plist, char *csbname)	// 設定初始內容
{
	char btnName[20], btnName_ml[20], btnName_on[20];
	// 讀取 csb 的內容，並加入場景中
	auto equalNode = CSLoader::createNode(csbname);
	this->addChild(equalNode);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);

	// 取得所有按鈕與顯示的資訊，並設定相關的控制參數
	Sprite *spriteBtn = (Sprite *)equalNode->getChildByName("btn_ok");
	Point pt = spriteBtn->getPosition();
	_equalBtn[0].setButtonInfo("btn_ok.png", "btn_ok.png", *equalNode, pt, EQULBTN_LEVEL);
	equalNode->removeChildByName("btn_ok");

	for (int i = 1; i < 12; i++) // 1 到 11 分別代表 2 到 12 等分的按鈕
	{
		sprintf(btnName, "btn%02d", i+1);
		sprintf(btnName_ml, "btn%02d.png", i+1);
		sprintf(btnName_on, "btn%02d_on.png", i+1);
		spriteBtn = (Sprite *)equalNode->getChildByName(btnName);
		pt = spriteBtn->getPosition();
		_equalBtn[i].setButtonInfo(btnName_ml, btnName_on, *equalNode, pt, EQULBTN_LEVEL);
		equalNode->removeChildByName(btnName);
	}

	// 取得顯示等分的數字，放在目前的 Node 上，預設不顯示
	for (int i = 0; i < 12; i++)  // 0 到 11 代表 1 到 12 ，但基本上不會用到 0
	{
		sprintf(btnName, "bb_no%02d.png", i + 1);
		_equalNo[i] = Sprite::createWithSpriteFrameName(btnName);
		_equalNo[i]->setPosition(0,0);
		_equalNo[i]->setVisible(false);
		this->addChild(_equalNo[i]);
	}
	_equalNo[1]->setVisible(true);
	_equalBtn[1].setButtonOn();
	_selected = 1;  // 預設為 2 等分被選取

	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plist);
}

bool CEqualController::touchesBegin(Point inPt)
{
	for (int i = 0; i < 12; i++) 
	{
		_equalBtn[i].touchesBegin(inPt - _OnScreenLoc);
	}
	return(true);
}

bool CEqualController::touchesMoved(Point inPt)
{
	for (int i = 0; i < 12; i++)
	{
		_equalBtn[i].touchesMoved(inPt - _OnScreenLoc);
	}
	return(true);
}

int CEqualController::touchesEnded(Point inPt)
{
	for (int i = 0; i < 12; i++)
	{
		if (_equalBtn[i].touchesEnded(inPt - _OnScreenLoc)) { // 代表該按鈕被按下了
			if (i == 0) return(_selected+1); // +1 對應於被選取的等分量
			else { // 判斷使用者目前選擇的等分量
				if (_selected != i) {
					_equalNo[_selected]->setVisible(false);  // 關閉顯示的數字與前一次按鈕的按下狀態
					_equalBtn[_selected].setButtonOff();
					_selected = i;	// 設定成這次的選擇
					_equalNo[_selected]->setVisible(true);
					_equalBtn[_selected].setButtonOn();
				}
			}
		}
	}
	return(0);  // 代表這次是選在平分數字上
}

void CEqualController::reset(int n)
{
	for (int i = 0; i < 12; i++) {
		_equalNo[i]->setVisible(false);
		_equalBtn[i].setButtonOff();
		_equalBtn[i].setEnabled(false);
	}

	_equalBtn[0].setEnabled(true);	// 確定按鈕有作用
	for (int i = 1; i <= _selectedQuan[0]; i++) {
		_equalBtn[_selectedQuan[i] - 1].setEnabled(true);
	}

	// 以 _selectedQuan 的第一個可等分的作為初始設定

	_equalNo[n-1]->setVisible(true);
	_equalBtn[n-1].setButtonOn();
	_selected = n-1;  

	// 僅設定可選擇量是有作用
}


void CEqualController::setEqualQuantity(const int (*unit)[12],int a,int n)  // 傳入所能提供選擇的平分值
{
	a = a - 1;

	int num = unit[a][0];
	_selectedQuan[0] = 0;
	for (int i = 1; i < MAX_EQUALITY; i++) {
		_equalBtn[i].setEnabled(false);
		_selectedQuan[i] = 0;  // 先全部清為 0
	}
	_selectedQuan[MAX_EQUALITY] = 0;
	for (int i = 0; i <= num; i++) _selectedQuan[i] = unit[a][i];

	reset(n);

	// 設定僅提供的平分值
	for (int i = 1; i <= num; i++) {
		_equalBtn[_selectedQuan[i] - 1].setEnabled(true);
	}
}

void CEqualController::setScreenLoc(const Point &inPos)
{
	_OnScreenLoc = inPos;
	this->setPosition(inPos);
}

CEqualController::CEqualController()
{

}

CEqualController::~CEqualController()
{
}
