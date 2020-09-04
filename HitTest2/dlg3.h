#pragma once


// dlg3 dialog

class dlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(dlg3)

public:
	dlg3(CWnd* pParent = nullptr);   // standard constructor
	virtual ~dlg3();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_edit_num;
};
