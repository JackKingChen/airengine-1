
// MSetupDlg.h : ͷ�ļ�
//

#pragma once

#include "AirCommonNet.h"

namespace	Air{
	namespace	Common{
		class	NetClient;
	}
}
struct NT_FS_FileData;

// CMSetupDlg �Ի���
class CMSetupDlg : public CDialogEx,public Air::Common::NetListener
{
// ����
public:
	CMSetupDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual	~CMSetupDlg();
// �Ի�������
	enum { IDD = IDD_MSETUP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	void			ThreadFunc();
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();

	virtual	U1	OnConnected(U32	socket,CAString&	strIP,CAString&	strPort);
	virtual	U1	OnClose(U32	uiSocket);
	virtual	U1	OnReceive(U32	uiSocket,AChar*	pData,U32	uiSize);

	wchar_t		m_strSetupPath[1024];
	int			m_dwPathLength;
protected:

	void		OnDownloading(NT_FS_FileData* pFileData);

	Air::Common::NetClient*	m_pClient;
	HANDLE					m_Event;

	CListBox*				m_pLog;
	
	FILE*					m_pNakedClinet;
	U32						m_Total;
	U32						m_Complated;
	U32						m_PkgSize[16];
};
