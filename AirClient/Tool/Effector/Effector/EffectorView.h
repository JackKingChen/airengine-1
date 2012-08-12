// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// EffectorView.h : CEffectorView ��Ľӿ�
//

#pragma once


class CEffectorView : public CView
{
protected: // �������л�����
	CEffectorView();
	DECLARE_DYNCREATE(CEffectorView)

// ����
public:
	CEffectorDoc* GetDocument() const;
	//CEffectorView::o
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//virtual BOOL PostCreateWindow(CREATESTRUCT& cs);
	
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
// ʵ��
public:
	virtual ~CEffectorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
	afx_msg void OnAddEffect();
	afx_msg void OnAddPhase();
	afx_msg void OnRenderstateRs();
	afx_msg void OnRenderstateDs();
	afx_msg void OnRenderstateBs();
protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // EffectorView.cpp �еĵ��԰汾
inline CEffectorDoc* CEffectorView::GetDocument() const
   { return reinterpret_cast<CEffectorDoc*>(m_pDocument); }
#endif

