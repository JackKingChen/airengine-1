#pragma once


// ProcessSelect �Ի���

class ProcessSelect : public CDialog
{
	DECLARE_DYNAMIC(ProcessSelect)

public:
	ProcessSelect(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProcessSelect();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_PROCESSSELECT };

	int GetPID(){
		return iPID;
	};

	void	Refresh(CListCtrl*	pCtrl);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	int iPID;
};
