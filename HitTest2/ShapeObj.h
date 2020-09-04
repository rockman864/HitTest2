#pragma once
#include <afx.h>
#include "Gdiplus.h"
using namespace std;
using namespace Gdiplus;
class ShapeObj : public CObject
{
protected:
	CPoint m_basePt;
	Region* m_region;
	GraphicsPath* m_path;
	RectF m_rect;
	int m_shapeType;
public:
	DECLARE_SERIAL(ShapeObj);
	enum
	{
		Type_Rect = 0,
		Type_Circle,
	};
	ShapeObj();
	ShapeObj(const CPoint& pt);
	ShapeObj(const ShapeObj& src);
	int GetShapeType();
	virtual void SetShapeType(int type);
	virtual void UpdateObj();
	virtual void SetBasePoint(const CPoint& pt);
	virtual void SetRegion();
	virtual void SetPath();
	virtual void SetRect();
	virtual Region* GetRegion();
	virtual GraphicsPath* GetPath();
	virtual CPoint GetBasePoint();
	virtual bool IsinRegion(PointF& pt, Graphics& gh);
	virtual void Drawing(Graphics& gh);
	virtual void Serialize(CArchive& ar);

};

