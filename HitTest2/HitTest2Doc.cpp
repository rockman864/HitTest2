
// HitTest2Doc.cpp : implementation of the CHitTest2Doc class
//

#include "pch.h"
#include "framework.h"
#include "RectangleObj.h"
#include "CircleObj.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HitTest2.h"
#endif

#include "HitTest2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHitTest2Doc

IMPLEMENT_DYNCREATE(CHitTest2Doc, CDocument)

BEGIN_MESSAGE_MAP(CHitTest2Doc, CDocument)
END_MESSAGE_MAP()


// CHitTest2Doc construction/destruction

CHitTest2Doc::CHitTest2Doc() noexcept
{
	// TODO: add one-time construction code here

}

CHitTest2Doc::~CHitTest2Doc()
{
	for (size_t i = 0; i < m_ShapeList.size(); i++)
	{
		delete m_ShapeList[i];
		m_ShapeList[i] = nullptr;
	}
}

BOOL CHitTest2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


// CHitTest2Doc serialization

void CHitTest2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		if (m_obArray_shape.GetSize() != 0)//case of modifying data
		{
			m_obArray_shape.RemoveAll();//delete orginal data
		}
		for (size_t i = 0; i < m_ShapeList.size(); i++)
		{
			m_obArray_shape.Add(m_ShapeList[i]);

		}
		m_obArray_shape.Serialize(ar);
	}
	else
	{
		// TODO: add loading code here
		m_obArray_shape.Serialize(ar);
		for (size_t i = 0; i < m_obArray_shape.GetSize(); i++)//use stored data to restore ShapeObjects
		{
			switch (((ShapeObj*)m_obArray_shape.GetAt(i))->GetShapeType())
			{
			case ShapeObj::Type_Rect:
			{
				RectangleObj* recti = (RectangleObj*)m_obArray_shape.GetAt(i);
				RectangleObj* rectObj =new RectangleObj(recti->GetBasePoint(), recti->GetWidth(), recti->GetHeight());
				m_ShapeList.push_back(rectObj);
				delete recti;
				recti = nullptr;
				break;
			}
			case ShapeObj::Type_Circle:
			{
				CircleObj* circlei = (CircleObj*)m_obArray_shape.GetAt(i);
				CircleObj* circleObj = new CircleObj(circlei->GetBasePoint(), circlei->GetRadius());
				m_ShapeList.push_back(circleObj);
				delete circlei;
				circlei = nullptr;
				break;
			}
			default:
				break;
			}

		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CHitTest2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CHitTest2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CHitTest2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CHitTest2Doc diagnostics

#ifdef _DEBUG
void CHitTest2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHitTest2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHitTest2Doc commands
