// RectProp.cpp : implementation file
//

#include "pch.h"
#include "HitTest2.h"
#include "RectProp.h"
#include "afxdialogex.h"


// RectProp dialog

IMPLEMENT_DYNAMIC(RectProp, CDialogEx)

RectProp::RectProp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_width(0)
	, m_height(0)
{

}

RectProp::~RectProp()
{
}

void RectProp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Width, m_width);
	DDX_Text(pDX, IDC_Height, m_height);
}


BEGIN_MESSAGE_MAP(RectProp, CDialogEx)
END_MESSAGE_MAP()


// RectProp message handlers


