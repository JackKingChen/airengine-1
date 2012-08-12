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

// EffectorView.cpp : CEffectorView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Effector.h"
#endif

#include "EffectorDoc.h"
#include "EffectorView.h"
#include "EngineManager.h"
#include "EffectorFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEffectorView

IMPLEMENT_DYNCREATE(CEffectorView, CView)

BEGIN_MESSAGE_MAP(CEffectorView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEffectorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_COMMAND(ID_ADD_EFFECT, &CEffectorView::OnAddEffect)
	ON_COMMAND(ID_ADD_PHASE, &CEffectorView::OnAddPhase)
	ON_COMMAND(ID_RENDERSTATE_RS, &CEffectorView::OnRenderstateRs)
	ON_COMMAND(ID_RENDERSTATE_DS, &CEffectorView::OnRenderstateDs)
	ON_COMMAND(ID_RENDERSTATE_BS, &CEffectorView::OnRenderstateBs)
END_MESSAGE_MAP()

// CEffectorView ����/����

CEffectorView::CEffectorView()
{
	// TODO: �ڴ˴���ӹ������

}

CEffectorView::~CEffectorView()
{
}

BOOL CEffectorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	
	
	return CView::PreCreateWindow(cs);
}

// CEffectorView ����

void CEffectorView::OnDraw(CDC* /*pDC*/)
{
	CEffectorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
//  	EngineManager::GetSingleton()->Init(GetSafeHwnd());
//  	HWND	hWnd	=	GetSafeHwnd();
//  	RECT r;
//  	GetClientRect(&r);
//  	EngineManager::GetSingleton()->ResizeWindow(r.right	-	r.left,r.bottom-r.top);
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	//EngineManager::GetSingleton()->RenderOneFrame();
}


// CEffectorView ��ӡ


void CEffectorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEffectorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CEffectorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CEffectorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CEffectorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEffectorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEffectorView ���

#ifdef _DEBUG
void CEffectorView::AssertValid() const
{
	CView::AssertValid();
}

void CEffectorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEffectorDoc* CEffectorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEffectorDoc)));
	return (CEffectorDoc*)m_pDocument;
}
int CEffectorView::OnCreate(LPCREATESTRUCT lpcs)
{
	//EngineManager::GetSingleton()->Init(GetSafeHwnd());
	OutputDebugString(_T("OnCreate\n"));
	return	CView::OnCreate(lpcs);
}

#endif //_DEBUG


void CEffectorView::OnAddEffect()
{
	CEffectorDoc*	pDoc	=	GetDocument();
	if(pDoc!=NULL){
		EffectorFile*	pFile	=	pDoc->GetEffectorFile();
		if(pFile!=NULL){
			CTreeCtrl*	pTree	=	pFile->GetTree();
			HTREEITEM	item	=	pTree->GetSelectedItem();
			TreeObj*	pObj	=	(TreeObj*)pTree->GetItemData(item);
			if(pObj!=NULL){
				pFile->AddEffect(_T("Effect"));
			}
		}
	}
}


void CEffectorView::OnAddPhase()
{
	// TODO: Add your command handler code here
	CEffectorDoc*	pDoc	=	GetDocument();
	if(pDoc!=NULL){
		EffectorFile*	pFile	=	pDoc->GetEffectorFile();
		if(pFile!=NULL){
			CTreeCtrl*	pTree	=	pFile->GetTree();
			HTREEITEM	item	=	pTree->GetSelectedItem();
			TreeObj*	pObj	=	(TreeObj*)pTree->GetItemData(item);
			if(pObj!=NULL){
				if(pObj->GetType()	==	enTOT_Effect){
					Effect*	pEffect	=	(Effect*)pObj;
					pEffect->AddPhase(_T("Phase"));
				}
			}
		}
	}
}


void CEffectorView::OnRenderstateRs()
{
	// TODO: Add your command handler code here
}


void CEffectorView::OnRenderstateDs()
{
	// TODO: Add your command handler code here
}


void CEffectorView::OnRenderstateBs()
{
	// TODO: Add your command handler code here
}

// CEffectorView ��Ϣ�������
