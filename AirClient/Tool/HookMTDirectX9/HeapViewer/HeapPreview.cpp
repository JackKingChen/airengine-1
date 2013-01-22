// HeapPreview.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HeapViewer.h"
#include "HeapPreview.h"
#include "afxdialogex.h"


// CHeapPreview �Ի���

IMPLEMENT_DYNAMIC(CHeapPreview, CDialog)

CHeapPreview::CHeapPreview(CWnd* pParent /*=NULL*/)
	: CDialog(CHeapPreview::IDD, pParent)
{

}

CHeapPreview::~CHeapPreview()
{
}

void CHeapPreview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHeapPreview, CDialog)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_VIEW, &CHeapPreview::OnTRBNThumbPosChangingSliderView)
END_MESSAGE_MAP()


// CHeapPreview ��Ϣ�������


void CHeapPreview::OnTRBNThumbPosChangingSliderView(NMHDR *pNMHDR, LRESULT *pResult)
{
	// �˹���Ҫ�� Windows Vista ����߰汾��
	// _WIN32_WINNT ���ű��� >= 0x0600��
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
