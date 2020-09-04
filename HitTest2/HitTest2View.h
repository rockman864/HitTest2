
// HitTest2View.h : interface of the CHitTest2View class
//
#include<vector>
#include<iostream>
#include"RectangleObj.h"
#include"CircleObj.h"
using namespace Gdiplus;
using namespace std;
#pragma once


class CHitTest2View : public CView
{
protected: // create from serialization only
	CHitTest2View() noexcept;
	DECLARE_DYNCREATE(CHitTest2View)

	// Attributes
public:
	CHitTest2Doc* GetDocument() const;

	// Operations

private:

	BOOL m_drawingSignal;  //signal to draw 
	BOOL m_MoveSignal; //signal to move
	int m_shapType;//shape type-1:rectangle,2:circle

	CPoint m_mousePt1; //click down point1
	CPoint m_mousePt2;//click up point2

	CPoint m_OldRectEndPoint;//for drawing motion effect of rectangle
	CPoint m_OldCircleStartPoint; //for drawing motion effect of circle
	CPoint m_OldCircleEndPoint; 

	double m_width;//rectangle width
	double m_height;//rectangle height
	double m_radius;//radius

	//vector<RectangleObj> m_RectangleList;//Rectangles container
	//vector<CircleObj> m_CircleList;//circles container
	//vector<ShapeObj> m_ShapeList;
	vector<RectangleObj> m_RectangleMoveList;//Rectangles container


	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CHitTest2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRect();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCircle();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in HitTest2View.cpp
inline CHitTest2Doc* CHitTest2View::GetDocument() const
{
	return reinterpret_cast<CHitTest2Doc*>(m_pDocument);
}
#endif
