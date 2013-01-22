
// HeapViewerDlg.h : ͷ�ļ�
//

#pragma once

#include "HeapPreview.h"

//#define DEBUG_VIEW



// CHeapViewerDlg �Ի���
class CHeapViewerDlg : public CDialogEx
{
// ����
public:
	CHeapViewerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual	~CHeapViewerDlg();
// �Ի�������
	enum { IDD = IDD_HEAPVIEWER_DIALOG };
	bool		IsNeedExitThread();
	void		OnUpdateHeap();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	void		InjectDll(int iProcessID);

	afx_msg	virtual	void	OnSize(UINT nType, int cx, int cy);
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
	afx_msg void OnBnClickedCancel();

	int iPID;
	HANDLE	m_hFileMapping;
	void*	m_pFile;
	CHeapPreview	m_HeapViewDlg;
	HBITMAP	m_BMP;
	DWORD*	m_pBMPData;
	int		m_iWidth;
	int		m_iWndWidth;
	int		m_iWndHeight;
	bool	m_bNeedExitThread;
	DWORD*	m_CacheData;//[512*64];
	unsigned char* pTemp;
};
