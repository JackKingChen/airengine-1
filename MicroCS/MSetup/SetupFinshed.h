#pragma once


// CSetupFinshed �Ի���

class CSetupFinshed : public CDialog
{
	DECLARE_DYNAMIC(CSetupFinshed)

public:
	CSetupFinshed(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetupFinshed();

// �Ի�������
	enum { IDD = IDD_DIALOG_FINISHED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	wchar_t strGamePath[1024];
};
