
// MToolDlg.h : ͷ�ļ�
//

#pragma once


// CMToolDlg �Ի���
class CMToolDlg : public CDialogEx
{
// ����
public:
	CMToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void		Build(ITaskbarList3 *pitl);
	CMFCEditBrowseCtrl* pBrow;		
	CProgressCtrl*		pProgress;	
	CListBox*			pList;		
	CStatic*			pTest;		
	CEdit*				pMaxBlock;
	afx_msg void OnBnClickedButton1();
};
