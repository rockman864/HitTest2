#include "pch.h"
#include "ShapeObj.h"
IMPLEMENT_SERIAL(ShapeObj, CObject, 1)

ShapeObj::ShapeObj()
{
	m_basePt = CPoint(0, 0);
	m_region = NULL;
	m_path = NULL;
	m_shapeType = 0;

}

ShapeObj::ShapeObj(const CPoint& pt)
{
	m_basePt = pt;
	m_region = NULL;
	m_path = NULL;
	m_shapeType = 0;
}

ShapeObj::ShapeObj(const ShapeObj& src)
{
	m_basePt = src.m_basePt;
	m_rect = src.m_rect;
	m_path = src.m_path->Clone();
	m_region= src.m_region->Clone();
	m_shapeType = src.m_shapeType;

}

int ShapeObj::GetShapeType()
{
	return m_shapeType;
}

void ShapeObj::SetShapeType(int type)
{
	m_shapeType = type;
}

void ShapeObj::UpdateObj()
{
	SetRect();
	SetPath();
	SetRegion();
}

void ShapeObj::SetBasePoint(const CPoint& pt)
{
	m_basePt = pt;
	UpdateObj();
}

void ShapeObj::SetRegion()
{
	m_region = new Region(m_path);
}

void ShapeObj::SetPath()
{
}

void ShapeObj::SetRect()
{
}

Region* ShapeObj::GetRegion()
{
	return m_region;
}

GraphicsPath* ShapeObj::GetPath()
{
	return m_path;
}

CPoint ShapeObj::GetBasePoint()
{
	return m_basePt;
}

bool ShapeObj::IsinRegion(PointF& pt, Graphics& gh)
{
	bool b = m_region->IsVisible(pt, &gh);
	return b;
}

void ShapeObj::Drawing(Graphics& gh) 
{
}

void ShapeObj::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_basePt << m_shapeType;
	}
	else
	{
		ar >> m_basePt >> m_shapeType;
	}
}
