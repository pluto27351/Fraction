#include "CDrawingPanel.h"
#include "Data.h"

#define BRUSH_SIZE 0.35f
#define color_red Color3B(197,95,80)
#define color_blue Color3B(52,116,233)
#define color_black Color3B(84,84,84)

CDrawingPanel* CDrawingPanel::_pHandDrawing = nullptr;

CDrawingPanel::~CDrawingPanel(){
    _penBrushList.clear();
    _eraserBrushList.clear();
    _pHandDrawing = nullptr;
}

CDrawingPanel *CDrawingPanel::create()
{ // 建立物件的實體

	if (_pHandDrawing == nullptr) {
		_pHandDrawing = new (std::nothrow) CDrawingPanel();
		if (_pHandDrawing) {
			_pHandDrawing->autorelease();
			return _pHandDrawing;
		}
		CC_SAFE_DELETE(_pHandDrawing);
		return nullptr;
	}
	else return _pHandDrawing;
}

CDrawingPanel *CDrawingPanel::getInstance()
{
	if (_pHandDrawing == nullptr) {
		_pHandDrawing = new (std::nothrow) CDrawingPanel();
		if (_pHandDrawing) {
			_pHandDrawing->autorelease();
			return _pHandDrawing;
		}
		CC_SAFE_DELETE(_pHandDrawing);
		return nullptr;
	}
	return _pHandDrawing;
}


void  CDrawingPanel::initDrawingPanel(Node &rootNode, cocos2d::Layer &parent)	// 設定初始內容
{
    i = 115;
	Sprite *pBtn = (Sprite *)rootNode.getChildByName("hand");
	Point pt = pBtn->getPosition();
	auto s = pBtn->getScale();
	_toolBtn[hand].setButtonInfo("tool_hand.png", "tool_hand_click.png", parent, pt, INTERFACE_LEVEL);
	_toolBtn[hand].setStatus(true);
	_toolBtn[hand].setScale(s);
	rootNode.removeChildByName("hand");

	pBtn = (Sprite *)rootNode.getChildByName("pen_red");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_toolBtn[redpen].setButtonInfo("tool_red.png", "tool_red_click.png", parent, pt, INTERFACE_LEVEL);
	_toolBtn[redpen].setScale(s);
	rootNode.removeChildByName("pen_red");

	pBtn = (Sprite *)rootNode.getChildByName("pen_black");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_toolBtn[blackpen].setButtonInfo("tool_black.png", "tool_black_click.png", parent, pt, INTERFACE_LEVEL);
	_toolBtn[blackpen].setScale(s);
	rootNode.removeChildByName("pen_black");

	pBtn = (Sprite *)rootNode.getChildByName("pen_blue");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_toolBtn[bluepen].setButtonInfo("tool_blue.png", "tool_blue_click.png", parent, pt, INTERFACE_LEVEL);
	_toolBtn[bluepen].setScale(s);
	rootNode.removeChildByName("pen_blue");

	pBtn = (Sprite *)rootNode.getChildByName("erease");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_toolBtn[eraser].setButtonInfo("tool_eraser.png", "tool_eraser_click.png", parent, pt, INTERFACE_LEVEL);
	_toolBtn[eraser].setScale(s);
	rootNode.removeChildByName("erease");

    // 設定清楚螢幕所有手繪圖型的按鈕
    pBtn = (Sprite *)rootNode.getChildByName("eraser_all");
    pt = pBtn->getPosition();
    s = pBtn->getScale();
    _eraserAllBtn.setButtonInfo("tool_clear.png", "tool_clear_click.png", parent, pt, INTERFACE_LEVEL);
    _eraserAllBtn.setScale(s);
    rootNode.removeChildByName("eraser_all");
    
	// 重置按鈕
    pBtn = (Sprite *)rootNode.getChildByName("reset");
    pt = pBtn->getPosition();
	s = pBtn->getScale();
    _clearAllBtn.setButtonInfo("tool_reset.png", "tool_reset_click.png", parent, pt, INTERFACE_LEVEL);
	_clearAllBtn.setScale(s);
    rootNode.removeChildByName("reset");

	_lineColor = _defaultColor[red] = color_red;
	_defaultColor[black] = color_black;
	_defaultColor[blue] = color_blue;

	_toolMode = HAND_MODE;

	// 建立白板
	Size size = rootNode.getContentSize();
	_pWhiteBoard = RenderTexture::create(size.width, size.height, Texture2D::PixelFormat::RGBA8888);
	_pWhiteBoard->retain();
	_pWhiteBoard->setPosition(Vec2(size.width / 2, size.height / 2));
	parent.addChild(_pWhiteBoard, WHITEBOARD_LEVEL);

	_pPenBrush = (Sprite *)Sprite::createWithSpriteFrameName("brush.png");
	_pPenBrush->retain();
	_pPenBrush->setColor(_lineColor);

	_pEraserBrush = (Sprite *)Sprite::createWithSpriteFrameName("eraser_body.png");
	_pEraserBrush->retain();

}


int CDrawingPanel::getMode()
{
	return(_toolMode);
}

void CDrawingPanel::doStep(float dt)
{

}


CDrawingPanel::CDrawingPanel()
{

}


void CDrawingPanel::drawing(Point &pt)
{


}


void CDrawingPanel::clearWhiteBoard()
{
	_pWhiteBoard->clear(0, 0, 0, 0);
}

void CDrawingPanel::setLineColor(Color3B color)
{
	_lineColor = color;
}


bool CDrawingPanel::touchesBegin(cocos2d::Point inPt)
{
	for (int i = 0; i < 5; i++) {
		if (_toolBtn[i].touchesBegin(inPt)) return(true);
	}

	if(_clearAllBtn.touchesBegin(inPt)) return(true);
    
    if(_eraserAllBtn.touchesBegin(inPt)) return(true);
	return(false);
}

bool CDrawingPanel::touchesMoved(Point inPt, Point inPrePt)
{
	bool bBtnOn = false;

	if (_clearAllBtn.touchesMoved(inPt)) bBtnOn = true;
    else if (_eraserAllBtn.touchesMoved(inPt)) bBtnOn = true;
    else {
        for (int i = 0; i < 5 && !bBtnOn; i++) if (_toolBtn[i].touchesMoved(inPt))bBtnOn = true;
    }
    

	// 產生手繪線
	if (!bBtnOn) {
		_pWhiteBoard->begin();
		float distance = inPt.getDistance(inPrePt);
		if (distance > 1) {
			if (_toolMode == PEN_MODE) {
				//_penBrushList.clear();
				for (int i = 0; i < distance; i++) {
					Sprite * sprite = Sprite::createWithSpriteFrameName("brush.png");;
					sprite->setColor(_lineColor);
					sprite->setScale(BRUSH_SIZE);
					_penBrushList.pushBack(sprite);
				}
				for (int i = 0; i < distance; i++) {
					float difx = inPrePt.x - inPt.x;
					float dify = inPrePt.y - inPt.y;
					float delta = (float)i / distance;
					_penBrushList.at(i)->setPosition(Point(inPt.x + (difx * delta), inPt.y + (dify * delta)));
					_penBrushList.at(i)->visit();
				}
			}
			else if (_toolMode == ERASER_MODE) {
				//_eraserBrushList.clear();
				for (int i = 0; i < distance; i++) {
					Sprite * sprite = Sprite::createWithSpriteFrameName("eraser_body.png");
					sprite->setColor(Color3B(250, 250, 250));
					BlendFunc blendFunc = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
					sprite->setBlendFunc(blendFunc);
					_eraserBrushList.pushBack(sprite);
				}
				for (int i = 0; i < distance; i++) {
					float difx = inPrePt.x - inPt.x;
					float dify = inPrePt.y - inPt.y;
					float delta = (float)i / distance;
					_eraserBrushList.at(i)->setPosition(Point(inPt.x + (difx * delta), inPt.y + (dify * delta)));
					_eraserBrushList.at(i)->visit();
				}
			}
		}
		_pWhiteBoard->end();
		if (!_penBrushList.empty()) _penBrushList.clear();
		if (!_eraserBrushList.empty()) _eraserBrushList.clear();
	}
	return(true);
}

bool CDrawingPanel::touchesEnded(cocos2d::Point inPt) //只有清除按鈕回傳true
{
	if (_toolBtn[redpen].touchesEnded(inPt)) {
		SetPen(_defaultColor[red]);
		SwitchButton(redpen);
        return(false);
	}
	if (_toolBtn[blackpen].touchesEnded(inPt)) {
		SetPen(_defaultColor[black]);
		SwitchButton(blackpen);
        return(false);
	}
	if (_toolBtn[bluepen].touchesEnded(inPt)) {
		SetPen(_defaultColor[blue]);
		SwitchButton(bluepen);
        return(false);
	}
	if (_toolBtn[eraser].touchesEnded(inPt)) {
		SwitchButton(eraser);
		_toolMode = ERASER_MODE;
        return(false);
	}
	if (_toolBtn[hand].touchesEnded(inPt)) {
		SwitchButton(hand);
		_toolMode = HAND_MODE;
        return(false);
	}
    if (_eraserAllBtn.touchesEnded(inPt)) {  // 清除螢幕上所有手繪的內容
        clearWhiteBoard();
        return(false);
    }
    if (_clearAllBtn.touchesEnded(inPt)) {
        clearWhiteBoard();
        return(true);
    }
    
	return(false);
}

void CDrawingPanel::changeToBlackPen() {
	SetPen(_defaultColor[black]);
	SwitchButton(blackpen);
}
void CDrawingPanel::changeToHand() {
    SwitchButton(hand);
    _toolMode = HAND_MODE;
}


void CDrawingPanel::SetPen(Color3B color = Color3B(0, 0, 0)) {
    _toolMode = PEN_MODE;
	_lineColor = color;
	_pPenBrush->setColor(_lineColor);

}
void CDrawingPanel::SwitchButton(int btn) {
	for (int i = 0; i < 5; i++)_toolBtn[i].setStatus(false);
	_toolBtn[btn].setStatus(true);
}
