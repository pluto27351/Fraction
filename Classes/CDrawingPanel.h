#pragma once

#include <Vector>
#include "cocos2d.h"
#include "Common/CButton.h"
#include "Common/CSwitch.h"

using namespace std;
using namespace cocos2d;

enum tool { hand, redpen, blackpen, bluepen, eraser };
enum color { red, black, blue};

class CDrawingPanel : public Ref
{

protected:
	// for hand drawing
	RenderTexture *_pWhiteBoard;
	Sprite* _pPenBrush;
	Sprite* _pEraserBrush;

	Vector <Sprite*> _penBrushList;
	Vector <Sprite*> _eraserBrushList;

	Color3B _lineColor, _defaultColor[3];
	int     _toolMode;

	static CDrawingPanel* _pHandDrawing;
	CButton _clearAllBtn,_eraserAllBtn;
	CSwitch _toolBtn[5];

	void SetPen(Color3B color);
	void SwitchButton(int btn);
    int i=0;
public:
	static CDrawingPanel *create();		// 建立物件的實體
	static CDrawingPanel *getInstance();	// 取得 CDrawingPanel 的實體
	void   initDrawingPanel(Node &rootNode, cocos2d::Layer &parent);	// 設定初始內容

	void setLineColor(Color3B color);
	void drawing(Point &pt);

	void clearWhiteBoard();	// 清除所有繪製在畫面上的線條
	int  getMode();	// 取得目前的狀態
	void changeToBlackPen();
    void changeToHand();
	bool touchesBegin(Point inPt);
	bool touchesMoved(Point inPt, Point inPrePt);
	bool touchesEnded(Point inPt);
	void doStep(float dt);
	CDrawingPanel();
    ~CDrawingPanel();
};
