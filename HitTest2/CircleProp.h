#pragma once


// CircleProp dialog

class CircleProp : public CDialogEx
{
	DECLARE_DYNAMIC(CircleProp)

public:
	CircleProp(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CircleProp();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_radius;
	afx_msg void OnBnClickedOk();
};
