#pragma once
#include "Gdiplus.h"
#include "ShapeObj.h"
using namespace std;
using namespace Gdiplus;
class CircleObj:public ShapeObj
{
private:
	double m_radius;

public:
	DECLARE_SERIAL(CircleObj);

	CircleObj();
	CircleObj(CPoint center, double r);
	void SetRadius(double r);
	void SetPath();
	void SetRect();
	double GetRadius();
	void Drawing(Graphics& gh);
	void Serialize(CArchive& ar);

};

