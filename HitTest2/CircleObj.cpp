#include "pch.h"
#include "CircleObj.h"
#include "Gdiplus.h"
#include "ShapeObj.h"
IMPLEMENT_SERIAL(CircleObj, ShapeObj, 1)
CircleObj::CircleObj()
{
	m_radius = 0;
}
CircleObj::CircleObj(CPoint pt, double r):ShapeObj(r)
{
	SetBasePoint(pt);
	m_radius = r;
	m_shapeType = ShapeObj::Type_Circle;
	UpdateObj();
}

void CircleObj::SetRadius(double r)
{
	m_radius = r;
	UpdateObj();

}

void CircleObj::SetRect()
{
	CPoint m_centerPt = GetBasePoint();
	m_rect = RectF(m_centerPt.x - m_radius, m_centerPt.y - m_radius,m_radius*2,m_radius*2);

}
double CircleObj::GetRadius()
{
	return m_radius;
}
void CircleObj::SetPath()
{
	m_path = new GraphicsPath();
	m_path->AddEllipse(m_rect);
	m_path->Widen(&Pen(Color::Blue, 5));
	m_path->Outline();
}

void CircleObj::Drawing(Graphics& gh)
{
	gh.DrawEllipse(&Pen(Color::Blue, 2), m_rect);
}

void CircleObj::Serialize(CArchive& ar)
{
	ShapeObj::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_radius;
	}
	else
	{
		ar >> m_radius;
	}

}
