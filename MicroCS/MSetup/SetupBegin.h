#pragma once


// CSetupBegin �Ի���

class CSetupBegin : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupBegin)

public:
	CSetupBegin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetupBegin();

// �Ի�������
	enum { IDD = IDD_DIALOG_BEGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
