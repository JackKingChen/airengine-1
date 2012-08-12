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

#pragma once

#include "ViewTree.h"

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// ����
public:
	CFileView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CTreeCtrl*	GetTreeCtrl();

// ����
protected:

	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

protected:
	void FillFileView();

// ʵ��
public:
	virtual ~CFileView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg	void	OnSelectChaneged(NMHDR*   pNMHDR,   LRESULT*   pResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddEffect();
	afx_msg void OnAddPhase();
	afx_msg void OnRenderstateRs();
	afx_msg void OnRenderstateDs();
	afx_msg void OnRenderstateBs();
	afx_msg void OnAddTexture();
	afx_msg void OnAddRendertexture();
	afx_msg void OnAddMesh();
	afx_msg void OnAddCamera();
	afx_msg void OnAddRemove();
	afx_msg void OnAddRename();
	afx_msg	void	OnBeginLabelEdit(NMHDR*   pNMHDR,   LRESULT*   pResult);
	afx_msg	void	OnEndLabelEdit(NMHDR*   pNMHDR,   LRESULT*   pResult);
	afx_msg void OnAddBind();
	afx_msg void OnAddReload();
	afx_msg void OnAddPass();
	afx_msg void OnShaderVertexshader();
	afx_msg void OnShaderGeometryshader();
	afx_msg void OnShaderPixelshader();
	afx_msg void OnShaderComputeshader();
	afx_msg void OnShaderHullshader();
	afx_msg void OnShaderDomainshader();
	afx_msg void OnAddModel();
	afx_msg void OnAddTextureref();
	//afx_msg void OnAddMaterial();
	afx_msg void OnAddConstantbuffer();
	afx_msg void OnAddModelref();
};

