#pragma once
#include "ShapeObj.h"
using namespace std;
using namespace Gdiplus;
#pragma once
class RectangleObj:public ShapeObj
{
private:
	double m_width;
	double m_height;
public:
	DECLARE_SERIAL(RectangleObj);
	RectangleObj();
	RectangleObj(CPoint pt, double width, double height);
	void SetWidth(double width);
	double GetWidth();
	void SetHeight(double height);
	double GetHeight();
	void SetRect();
	void SetPath();
	void Drawing(Graphics& gh);
	void Moving(Graphics& gh, double x, double y);
	void Serialize(CArchive& ar);
};

