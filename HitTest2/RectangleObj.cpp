#include "pch.h"
#include "RectangleObj.h"
#include "Gdiplus.h"
IMPLEMENT_SERIAL(RectangleObj, ShapeObj, 1)
RectangleObj::RectangleObj()
{
	m_width = 100;
	m_height = 100;
}
RectangleObj::RectangleObj(CPoint pt, double w, double h):ShapeObj(pt)
{
	m_basePt = CPoint(pt.x, pt.y);
	m_width = w;
	m_height = h;
	m_shapeType = ShapeObj::Type_Rect;
	UpdateObj();
}

void RectangleObj::SetWidth(double width)
{
	m_width = width;
	UpdateObj();

}

void RectangleObj::SetHeight(double height)
{
	m_height = height;
	UpdateObj();
}

void RectangleObj::SetRect()
{
	m_rect = RectF(m_basePt.x, m_basePt.y, m_width, m_height);
}

void RectangleObj::SetPath()
{
	m_path = new GraphicsPath();
	m_path->Reset();
	m_path->AddRectangle(m_rect);
	m_path->Widen(&Pen(Color::Blue, 5));
	m_path->Outline();

}


double RectangleObj::GetWidth()
{
	return m_width;
}
double RectangleObj::GetHeight()
{
	return m_height;
}


void RectangleObj::Drawing(Graphics& gh)
{
	//gh.TranslateTransform(xdist, ydist, MatrixOrderAppend);
	gh.DrawRectangle(&Pen(Color::Blue, 2),m_rect);
	//gh.DrawPath(&Pen(Color::Red, 1), m_path);

}
void RectangleObj::Moving(Graphics& gh, double x, double y)
{
	gh.TranslateTransform(x, y, MatrixOrderAppend);
	Drawing(gh);

 }

void RectangleObj::Serialize(CArchive& ar)
{
	ShapeObj::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_height << m_width;
	}
	else
	{
		ar >> m_height >> m_width;
	}
}



