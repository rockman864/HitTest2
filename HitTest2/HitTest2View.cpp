
// HitTest2View.cpp : implementation of the CHitTest2View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HitTest2.h"
#endif

#include "HitTest2Doc.h"
#include "HitTest2View.h"
#include "Gdiplus.h"
#include "RectProp.h"
#include "CircleProp.h"
#include "vector"
#include <Cmath>
using namespace Gdiplus;
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHitTest2View

IMPLEMENT_DYNCREATE(CHitTest2View, CView)

BEGIN_MESSAGE_MAP(CHitTest2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHitTest2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_Rect, &CHitTest2View::OnRect)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_Circle, &CHitTest2View::OnCircle)
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

//CHitTest2View construction/destruction


CHitTest2View::CHitTest2View() noexcept
{
	// TODO: add construction code here
	m_width = 0;
	m_height = 0;
	m_shapType = 0;
	m_drawingSignal = FALSE;
	m_MoveSignal = TRUE;
}

CHitTest2View::~CHitTest2View()
{
}

BOOL CHitTest2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CHitTest2View drawing

void CHitTest2View::OnDraw(CDC* pDC)
{
	//CClientDC dc(this);
	Graphics gh(*pDC);
	gh.SetSmoothingMode(SmoothingModeAntiAlias);
	CHitTest2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//gh.DrawRectangle(&Pen(Color::Blue, 2), 100, 100, 200, 200);
	// TODO: add draw code for native data here
	/*int nCount = pDoc->m_RectangleList.size();
	if (nCount != 0)
	{
		for (int i = 0; i < nCount; i++)
		{
			pDoc->m_RectangleList[i].Drawing(gh);
		}
	}
	int nCount2 = pDoc->m_CircleList.size();
	if (nCount2 != 0)
	{
		for (int i = 0; i < nCount2; i++)
		{
			pDoc->m_CircleList[i].Drawing(gh);
		}
	}*/
	int nCount = pDoc->m_ShapeList.size();
	if (nCount != 0)
	{
		for (int i = 0; i < nCount; i++)
		{
			pDoc->m_ShapeList[i]->Drawing(gh);
		}
	}
}


// CHitTest2View printing


void CHitTest2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHitTest2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHitTest2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHitTest2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


void CHitTest2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHitTest2View diagnostics

#ifdef _DEBUG
void CHitTest2View::AssertValid() const
{
	CView::AssertValid();
}

void CHitTest2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHitTest2Doc* CHitTest2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHitTest2Doc)));
	return (CHitTest2Doc*)m_pDocument;
}
#endif //_DEBUG


// CHitTest2View message handlers



void CHitTest2View::OnRect()
{
	m_shapType = 1;
}


void CHitTest2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_drawingSignal = TRUE;   //signal to draw 
	m_mousePt1 = point;

	m_OldRectEndPoint = point;

	m_OldCircleStartPoint = point;
	m_OldCircleEndPoint = point;

	CView::OnLButtonDown(nFlags, point);
}


void CHitTest2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CHitTest2Doc* pDoc = GetDocument();

	m_mousePt2 = point;
	CClientDC dc(this);
	Graphics gh(dc);
	gh.SetSmoothingMode(SmoothingModeAntiAlias);

	dc.SetROP2(R2_NOT);//for removing last frame of motion effect
	dc.SelectStockObject(NULL_BRUSH);

	PointF ptf(point.x, point.y);
	switch (m_shapType)
	{
	case 1:
	{
		m_width = (double)m_mousePt2.x - (double)m_mousePt1.x;
		m_height = (double)m_mousePt2.y - (double)m_mousePt1.y;
		RectangleObj *recti =new RectangleObj(m_mousePt1, m_width, m_height);
		//auto recti = make_unique<RectangleObj>();
		//recti->SetBasePoint(m_mousePt1);
		//recti->SetWidth(m_width);
		//recti->SetHeight(m_height);
		if (pDoc != NULL)
		{
			//pDoc->m_RectangleList.push_back(*recti);
			pDoc->m_ShapeList.push_back(recti);
		}
		dc.Rectangle(CRect(m_mousePt1, m_OldRectEndPoint));//remove last frame of rectangle motion effect
		//recti.Drawing(gh);//draw rectangle
		break;
	}
	case 2:
		m_radius = sqrt(pow(m_mousePt2.x - m_mousePt1.x, 2) + pow(m_mousePt2.y-m_mousePt1.y, 2));
		CircleObj *circlei = new CircleObj(m_mousePt1, m_radius);
		if (pDoc != NULL)
		{
			//pDoc->m_CircleList.push_back(*circlei);
			pDoc->m_ShapeList.push_back(circlei);
		}
		dc.Ellipse(CRect(m_OldCircleStartPoint, m_OldCircleEndPoint));
		//circlei.Drawing(gh);
		break;
	}
	m_drawingSignal = FALSE; //reset drawing signal
	m_shapType = 0;//reset drawing type

	if (m_MoveSignal = TRUE && m_RectangleMoveList.size() != 0)
	{
		for (size_t i = 0; i < m_RectangleMoveList.size(); i++)
		{
			m_RectangleMoveList[i].Moving(gh, (double)m_mousePt2.x - (double)m_mousePt1.x, (double)m_mousePt2.y - (double)m_mousePt1.y);
		}
	}
	Invalidate(TRUE);

	CView::OnLButtonUp(nFlags, point);
}
void CHitTest2View::OnRButtonUp(UINT nFlags, CPoint point)
{
	CView::OnRButtonUp(nFlags, point);

}

void CHitTest2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rc;
	GetClientRect(rc);
	Bitmap bmp(int(rc.right), int(rc.bottom));
	Graphics bmpGraphics(&bmp);
	PointF ptf(point.x, point.y);
	CHitTest2Doc* pDoc = GetDocument();
	for (size_t i = 0; i < pDoc->m_ShapeList.size(); i++)
	{
		if (pDoc->m_ShapeList[i]->IsinRegion(ptf, bmpGraphics))
		{
			switch (pDoc->m_ShapeList[i]->GetShapeType())
			{
			case ShapeObj::Type_Rect:
			{
				RectProp dlg;
				RectangleObj* tempi = (RectangleObj*)(pDoc->m_ShapeList[i]);
				dlg.m_width =(int) tempi->GetWidth();
				dlg.m_height = (int)tempi->GetHeight();

				//dlg.m_height = (int)((RectangleObj*)(pDoc->m_ShapeList[i]))->GetHeight();
				if (dlg.DoModal() == IDOK)
				{
					UpdateData(TRUE);
					tempi->SetWidth(dlg.m_width);//update parameters
					tempi->SetHeight(dlg.m_height);
					UpdateData(FALSE);
				}
				break;
			}
			case ShapeObj::Type_Circle:
			{
				CircleProp dlg;
				CircleObj* tempi = (CircleObj*)(pDoc->m_ShapeList[i]);
				dlg.m_radius = (int)tempi->GetRadius();
				if (dlg.DoModal() == IDOK)
				{
					UpdateData(TRUE);
					tempi->SetRadius(dlg.m_radius);//update parameters
					UpdateData(FALSE);
				}
				break;
			}
			default:
				break;
			}
		}
	}
	//for (size_t i = 0; i < pDoc->m_RectangleList.size(); i++)//check every rectangle which has been rightclicked
	//{
	//	if (pDoc->m_RectangleList[i].IsinRegion(ptf, bmpGraphics))//rectangle been picked
	//	{
	//		RectProp dlg;
	//		dlg.m_width = (int)pDoc->m_RectangleList[i].GetWidth();
	//		dlg.m_height = (int)pDoc->m_RectangleList[i].GetHeight();
	//		if (dlg.DoModal() == IDOK)
	//		{
	//			UpdateData(TRUE);
	//			pDoc->m_RectangleList[i].SetWidth(dlg.m_width);//update parameters
	//			pDoc->m_RectangleList[i].SetHeight(dlg.m_height);
	//			UpdateData(FALSE);
	//		}

	//	}

	//}

	//for (size_t i = 0; i < pDoc->m_CircleList.size(); i++)//check every circle which has been rightclicked
	//{
	//	if (pDoc->m_CircleList[i].IsinRegion(ptf, bmpGraphics))//circle been picked
	//	{
	//		CircleProp dlg;
	//		dlg.m_radius = (int)pDoc->m_CircleList[i].GetRadius();
	//		if (dlg.DoModal() == IDOK)
	//		{
	//			UpdateData(TRUE);
	//			pDoc->m_CircleList[i].SetRadius(dlg.m_radius);//update parameter
	//			UpdateData(FALSE);
	//		}

	//	}
	//}
	bmpGraphics.SetSmoothingMode(SmoothingModeAntiAlias);
	SolidBrush brush(Color::White);
	bmpGraphics.FillRectangle(&brush, 0, 0, rc.right, rc.bottom);//remove old drawing
	Graphics graphics(m_hWnd);
	for (size_t i = 0; i < pDoc->m_ShapeList.size(); i++)
	{
		pDoc->m_ShapeList[i]->Drawing(bmpGraphics);//drawing with updated parameters
	}
	CachedBitmap cacheBmp(&bmp, &graphics);
	graphics.DrawCachedBitmap(&cacheBmp, 0, 0);
	//Invalidate(TRUE);


	CView::OnRButtonDown(nFlags, point);
}


void CHitTest2View::OnCircle()
{
	// TODO: Add your command handler code here
	m_shapType = 2;

}


void CHitTest2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	dc.SetROP2(R2_NOT);
	dc.SelectStockObject(NULL_BRUSH);
	if (m_shapType == 1 && m_drawingSignal == TRUE)   // motion effect
	{
		dc.Rectangle(CRect(m_mousePt1, m_OldRectEndPoint));
		dc.Rectangle(CRect(m_mousePt1, point));
		m_OldRectEndPoint = point;
	}
	if (m_shapType == 2 && m_drawingSignal == TRUE)   // motion effect
	{
		m_radius = sqrt(pow(point.x - m_mousePt1.x, 2) + pow(point.y - m_mousePt1.y, 2));
		CPoint newEndPtCircle = CPoint(m_mousePt1.x + m_radius, m_mousePt1.y + m_radius);
		CPoint newStarPtCircle = CPoint(m_mousePt1.x - m_radius, m_mousePt1.y - m_radius);
		dc.Ellipse(CRect(m_OldCircleStartPoint, m_OldCircleEndPoint));
		dc.Ellipse(CRect(newStarPtCircle, newEndPtCircle));
		m_OldCircleStartPoint = newStarPtCircle;
		m_OldCircleEndPoint = newEndPtCircle;
	}



	CView::OnMouseMove(nFlags, point);
}


