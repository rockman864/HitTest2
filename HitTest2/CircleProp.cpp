// CircleProp.cpp : implementation file
//

#include "pch.h"
#include "HitTest2.h"
#include "CircleProp.h"
#include "afxdialogex.h"


// CircleProp dialog

IMPLEMENT_DYNAMIC(CircleProp, CDialogEx)

CircleProp::CircleProp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_radius(0)
{

}

CircleProp::~CircleProp()
{
}

void CircleProp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_radius, m_radius);
}


BEGIN_MESSAGE_MAP(CircleProp, CDialogEx)
	ON_BN_CLICKED(IDOK, &CircleProp::OnBnClickedOk)
END_MESSAGE_MAP()


// CircleProp message handlers


void CircleProp::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}



