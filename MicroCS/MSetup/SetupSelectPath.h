#pragma once


// CSetupSelectPath �Ի���

class CSetupSelectPath : public CDialog
{
	DECLARE_DYNAMIC(CSetupSelectPath)

public:
	CSetupSelectPath(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetupSelectPath();

// �Ի�������
	enum { IDD = IDD_DIALOG_SELECT_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	wchar_t			m_strSetupPath[1024];
	DWORD			m_dwLength;
	afx_msg void OnLvnItemchangedListHd(NMHDR *pNMHDR, LRESULT *pResult);
};
