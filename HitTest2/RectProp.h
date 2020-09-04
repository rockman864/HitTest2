#pragma once


// RectProp dialog

class RectProp : public CDialogEx
{
	DECLARE_DYNAMIC(RectProp)

public:
	RectProp(CWnd* pParent = nullptr);   // standard constructor
	virtual ~RectProp();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_width;
	double m_height;
};
