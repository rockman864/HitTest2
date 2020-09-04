
// HitTest2Doc.h : interface of the CHitTest2Doc class
//


#pragma once
#include "ShapeObj.h"
#include "RectangleObj.h"
#include "CircleObj.h"
#include <vector>
using namespace std;

class CHitTest2Doc : public CDocument
{
protected: // create from serialization only
	CHitTest2Doc() noexcept;
	DECLARE_DYNCREATE(CHitTest2Doc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CHitTest2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	CObArray m_obArray_shape;
	//vector<RectangleObj> m_RectangleList;
	//vector<CircleObj> m_CircleList;
	vector<ShapeObj*> m_ShapeList;


#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
