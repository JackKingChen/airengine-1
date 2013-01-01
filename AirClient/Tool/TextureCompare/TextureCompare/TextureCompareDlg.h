
// TextureCompareDlg.h : ͷ�ļ�
//

#pragma once


// CTextureCompareDlg �Ի���
class CTextureCompareDlg : public CDialogEx
{
// ����
public:
	CTextureCompareDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEXTURECOMPARE_DIALOG };

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
	afx_msg void OnLvnItemActivateListTextureName(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickListTextureName(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickListTextureCompare(NMHDR *pNMHDR, LRESULT *pResult);
	bool bLoad;

	bool bUpdateCompare;

	HBITMAP m_BMP;
	HBITMAP m_BMPCOMPARE;
	afx_msg void OnLvnColumnclickListTextureName(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListTextureCompare(NMHDR *pNMHDR, LRESULT *pResult);
};
