#include "CHandDrawing.h"

#define BRUSH_SIZE 0.35f

CHandDrawing* CHandDrawing::_pHandDrawing = nullptr;

CHandDrawing *CHandDrawing::create()
{ // 建立物件的實體

	if (_pHandDrawing == nullptr) {
		_pHandDrawing = new (std::nothrow) CHandDrawing();
		if (_pHandDrawing) {
			_pHandDrawing->autorelease();
			return _pHandDrawing;
		}
		CC_SAFE_DELETE(_pHandDrawing);
		return nullptr;
	}
	else return _pHandDrawing;
}

CHandDrawing *CHandDrawing::getInstance()
{
	if (_pHandDrawing == nullptr) {
		_pHandDrawing = new (std::nothrow) CHandDrawing();
		if (_pHandDrawing) {
			_pHandDrawing->autorelease();
			return _pHandDrawing;
		}
		CC_SAFE_DELETE(_pHandDrawing);
		return nullptr;
	}
	return _pHandDrawing;
}


void  CHandDrawing::initHandDrawing(Node &rootNode, cocos2d::Layer &parent)	// 設定初始內容
{
	_colorBtn.setButtonInfo(rootNode, parent, INTERFACE_LEVEL);

	// 設定 畫筆與橡皮擦兩個按鈕
//    Sprite *pBtn = (Sprite *)rootNode.getChildByName("pen_on");
//    Point pt = pBtn->getPosition();
//    _penBtn.setButtonInfo("pen_off.png", "pen_on.png", parent, pt, INTERFACE_LEVEL);
//    _penBtn.setButtonOn();
//    rootNode.removeChildByName("pen_on");

	Sprite *pBtn = (Sprite *)rootNode.getChildByName("erease_on");
	Point pt = pBtn->getPosition();
	_eraserBtn.setButtonInfo("erease.png", "erease.png", parent, pt, INTERFACE_LEVEL);
	rootNode.removeChildByName("pen_on");

	// 設定清楚螢幕所有手繪圖型的按鈕
//    pBtn = (Sprite *)rootNode.getChildByName("clearall_nl");
//    pt = pBtn->getPosition();
//    _clearAllBtn.setButtonInfo("clearall_nl.png", "clearall_on.png", parent, pt, INTERFACE_LEVEL);
//    rootNode.removeChildByName("clearall_nl");

	// 設定移動物件的按鈕
	pBtn = (Sprite *)rootNode.getChildByName("hand_on");
	pt = pBtn->getPosition();
	_handBtn.setButtonInfo("select.png", "select.png", parent, pt, INTERFACE_LEVEL);
	rootNode.removeChildByName("hand_on");

	_lineColor = _colorBtn.getColor();
	_drawingMode = DRAWING_MODE;
	
	// 建立白板
	Size size = rootNode.getContentSize();
	_pWhiteBoard = RenderTexture::create(size.width, size.height, Texture2D::PixelFormat::RGBA8888);
	_pWhiteBoard->retain();
	_pWhiteBoard->setPosition(Vec2(size.width / 2, size.height / 2));
	parent.addChild(_pWhiteBoard, DRAWING_LEVEL);

	_pPenBrush = Sprite::createWithSpriteFrameName("brush.png");
	_pPenBrush->retain();
	_pPenBrush->setColor(_lineColor);

	_pEraserBrush = Sprite::createWithSpriteFrameName("eraser_body.png");
	_pEraserBrush->retain();

}


int CHandDrawing::getMode()
{
	return(_drawingMode);
}

void CHandDrawing::doStep(float dt) 
{

}


CHandDrawing::CHandDrawing()
{

}


void CHandDrawing::drawing(Point &pt)
{


}

void CHandDrawing::clear()
{

}

void CHandDrawing::removeAll()
{
	_pWhiteBoard->clear(0, 0, 0, 0);
}

void CHandDrawing::setLineColor(Color3B color)
{
	_lineColor = color;
}


bool CHandDrawing::touchesBegin(cocos2d::Point inPt)
{
	_colorBtn.touchesBegin(inPt);
	//_penBtn.touchesBegin(inPt);
	_eraserBtn.touchesBegin(inPt);
	_handBtn.touchesBegin(inPt);
	//_clearAllBtn.touchesBegin(inPt);
	return(true);
}

bool CHandDrawing::touchesMoved(Point inPt, Point inPrePt)
{
	bool bBtnOn = false;
	// 按在按鈕上時，不產生線條
	if( _colorBtn.touchesMoved(inPt) ) bBtnOn = true;
	//else if( _penBtn.touchesMoved(inPt) ) bBtnOn = true;
	else if( _eraserBtn.touchesMoved(inPt) ) bBtnOn = true;
	//else if( _clearAllBtn.touchesMoved(inPt)) bBtnOn = true;
	else if (_handBtn.touchesMoved(inPt)) bBtnOn = true;

	// 產生手繪線
	if (!bBtnOn) {
		_pWhiteBoard->begin();
		float distance = inPt.getDistance(inPrePt);
		if( distance > 1) {
			if (_drawingMode == DRAWING_MODE) {
				//_penBrushList.clear();
				for (int i = 0; i < distance; i++ ) {
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
			else if(_drawingMode == ERASER_MODE){
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
		if(!_penBrushList.empty() ) _penBrushList.clear();
		if(!_eraserBrushList.empty()) _eraserBrushList.clear();
	}
	return(true);
}

bool CHandDrawing::touchesEnded(cocos2d::Point inPt) 
{

	if (_colorBtn.touchesEnded(inPt)) { // 有切換顏色顯示按鈕
		_lineColor = _colorBtn.getColor();
		_pPenBrush->setColor(_lineColor);
		// 如果目前是在橡皮擦模式，按下顏色按鈕則自動切換到畫筆模式
		if ( _drawingMode == ERASER_MODE || _drawingMode == MOVEINGOBJ_MODE ) { // 切換到畫筆模式
			_eraserBtn.setButtonOff(); // 設定橡皮擦圖示關閉
			_handBtn.setButtonOff(); // 設定移動物件圖示關閉
			//_penBtn.setButtonOn();
			_drawingMode = DRAWING_MODE;
		}
		return(true);
	}
//    if ( _penBtn.touchesEnded(inPt) ) { // 按下的是 pen button
//        if (_drawingMode == ERASER_MODE || _drawingMode == MOVEINGOBJ_MODE ) { // 前一次是在橡皮擦模式
//            _eraserBtn.setButtonOff(); // 設定橡皮擦圖示關閉
//            _handBtn.setButtonOff(); // 設定移動物件圖示關閉
//            _drawingMode = DRAWING_MODE;
//        }
//        return(true);
//    }

	if ( _eraserBtn.touchesEnded(inPt)  ) { // 按下的是 eraser button
		if ( _drawingMode == DRAWING_MODE || _drawingMode == MOVEINGOBJ_MODE) { // 前一次是在畫筆模式
			//_penBtn.setButtonOff();		// 切換畫筆圖示關閉
			_handBtn.setButtonOff(); // 設定移動物件圖示關閉
			_drawingMode = ERASER_MODE;
		}
		return(true);
	}

	if (_handBtn.touchesEnded(inPt)) {
		if (_drawingMode == DRAWING_MODE || _drawingMode == ERASER_MODE) { // 前一次是在畫筆模式
			//_penBtn.setButtonOff();		// 切換畫筆圖示關閉
			_eraserBtn.setButtonOff(); // 設定橡皮擦圖示關閉
			_handBtn.setButtonOn(); // 設定移動物件圖示關閉
			_drawingMode = MOVEINGOBJ_MODE;
		}
		return(true);
	}

//    if (_clearAllBtn.touchesEnded(inPt)) { // 確認被按下
//        // 清除螢幕上所有手繪的內容
//        removeAll();
//        return(true);
//    }
	return(false);
}
