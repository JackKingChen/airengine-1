#pragma once


// CHeapPreview �Ի���

class CHeapPreview : public CDialog
{
	DECLARE_DYNAMIC(CHeapPreview)

public:
	CHeapPreview(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHeapPreview();

// �Ի�������
	enum { IDD = IDD_DIALOG_HEAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTRBNThumbPosChangingSliderView(NMHDR *pNMHDR, LRESULT *pResult);
};
