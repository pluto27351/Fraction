#pragma once

// 
// 本身包含狀態的切換按鈕，根據傳入的觸控點位置去改變按鈕的狀態，同時切換繪圖的模式
//

#include <Vector>
#include "cocos2d.h"
#include "Object/CSwitchButton.h"
#include "Object/CButton.h"
#include "const.h"

using namespace std;
using namespace cocos2d;

class CHandDrawing : public Ref
{

protected:
	// for hand drawing
	RenderTexture *_pWhiteBoard;
	Sprite* _pPenBrush;
	Sprite* _pEraserBrush;

	Vector <Sprite*> _penBrushList;
	Vector <Sprite*> _eraserBrushList;

	Color3B _lineColor;
	int     _drawingMode;
	
	static CHandDrawing* _pHandDrawing;
	CSwitchButton _colorBtn;
	COnButton  _penBtn, _eraserBtn, _handBtn;
	CButton    _clearAllBtn;

public:
	static CHandDrawing *create();		// 建立物件的實體
	static CHandDrawing *getInstance();	// 取得 CHandDrawing 的實體
	void   initHandDrawing(Node &rootNode, cocos2d::Layer &parent);	// 設定初始內容

	void setLineColor(Color3B color);
	void drawing(Point &pt);
	void clear();	// 清除所有繪製在畫面上的線條
	void removeAll();	// 清除所有繪製在畫面上的線條
	int  getMode();	// 取得目前的狀態

	bool touchesBegin(Point inPt);
	bool touchesMoved(Point inPt, Point inPrePt);
	bool touchesEnded(Point inPt);
	void doStep(float dt);
	CHandDrawing();

};