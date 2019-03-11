#include "CDrawingPanel.h"
#include "Data.h"

#define BRUSH_SIZE 0.35f

CDrawingPanel* CDrawingPanel::_pHandDrawing = nullptr;

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
	Sprite *pBtn = (Sprite *)rootNode.getChildByName("hand");
	Point pt = pBtn->getPosition();
	auto s = pBtn->getScale();
	_toolBtn[hand].setButtonInfo("select.png", "select.png", parent, pt, INTERFACE_LEVEL);
	_toolBtn[hand].setStatus(true);
	_toolBtn[hand].setScale(s);
	rootNode.removeChildByName("hand");

	pBtn = (Sprite *)rootNode.getChildByName("pen_red");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_toolBtn[redpen].setButtonInfo("red.png", "red.png", parent, pt, INTERFACE_LEVEL);
	_toolBtn[redpen].setScale(s);
	rootNode.removeChildByName("pen_red");

	pBtn = (Sprite *)rootNode.getChildByName("pen_green");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_toolBtn[blackpen].setButtonInfo("green.png", "green.png", parent, pt, INTERFACE_LEVEL);
	_toolBtn[blackpen].setScale(s);
	rootNode.removeChildByName("pen_green");

	pBtn = (Sprite *)rootNode.getChildByName("pen_blue");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_toolBtn[bluepen].setButtonInfo("blue.png", "blue.png", parent, pt, INTERFACE_LEVEL);
	_toolBtn[bluepen].setScale(s);
	rootNode.removeChildByName("pen_blue");

	pBtn = (Sprite *)rootNode.getChildByName("erease");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_toolBtn[eraser].setButtonInfo("erease.png", "erease.png", parent, pt, INTERFACE_LEVEL);
	_toolBtn[eraser].setScale(s);
	rootNode.removeChildByName("erease");

	// 設定清楚螢幕所有手繪圖型的按鈕
    pBtn = (Sprite *)rootNode.getChildByName("reset");
    pt = pBtn->getPosition();
	s = pBtn->getScale();
    _clearAllBtn.setButtonInfo("reset.png", "reset.png", parent, pt, INTERFACE_LEVEL);
	_clearAllBtn.setScale(s);
    rootNode.removeChildByName("reset");

	_lineColor = _defaultColor[red] = Color3B(250, 0, 0);
	_defaultColor[black] = Color3B(  0, 0, 0);   
	_defaultColor[blue] = Color3B(  0, 0, 250);

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
	return(false);
}

bool CDrawingPanel::touchesMoved(Point inPt, Point inPrePt)
{
	bool bBtnOn = false;

	if (_clearAllBtn.touchesMoved(inPt)) bBtnOn = true;
	else 
		for (int i = 0; i < 5; i++)
			if (_toolBtn[i].touchesMoved(inPt))bBtnOn = true;

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

bool CDrawingPanel::touchesEnded(cocos2d::Point inPt)
{
	if (_toolBtn[redpen].touchesEnded(inPt)) {
		SetPen(_defaultColor[red]);
		SwitchButton(redpen);
	}
	else if (_toolBtn[blackpen].touchesEnded(inPt)) {
		SetPen(_defaultColor[black]);
		SwitchButton(blackpen);
	}
	else if (_toolBtn[bluepen].touchesEnded(inPt)) {
		SetPen(_defaultColor[blue]);
		SwitchButton(bluepen);
	}

	else if (_toolBtn[eraser].touchesEnded(inPt)) { // 按下的是 eraser button
		SwitchButton(eraser);
		_toolMode = ERASER_MODE;
	}

	else if (_toolBtn[hand].touchesEnded(inPt)) {
		SwitchButton(hand);
		_toolMode = HAND_MODE;
	}

	else if (_clearAllBtn.touchesEnded(inPt)) { // 確認被按下
	    // 清除螢幕上所有手繪的內容
	    clearWhiteBoard();
	    return(true);
	}
	return(false);
}

void CDrawingPanel::changeToBlackPen() {
	SetPen(_defaultColor[black]);
	SwitchButton(blackpen);
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
