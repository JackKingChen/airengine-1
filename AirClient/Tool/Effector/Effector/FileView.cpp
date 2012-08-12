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

#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "Effector.h"
#include "EffectorDoc.h"
#include "EffectorFile.h"
#include "ReNameDialog.h"
#include "TreeObjectBind.h"
#include "EngineRenderState.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CFileView::CFileView()
{
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_NOTIFY(TVN_SELCHANGED,4,&CFileView::OnSelectChaneged)
	ON_COMMAND(ID_ADD_EFFECT, &CFileView::OnAddEffect)
	ON_COMMAND(ID_ADD_PHASE, &CFileView::OnAddPhase)
	ON_COMMAND(ID_RENDERSTATE_RS, &CFileView::OnRenderstateRs)
	ON_COMMAND(ID_RENDERSTATE_DS, &CFileView::OnRenderstateDs)
	ON_COMMAND(ID_RENDERSTATE_BS, &CFileView::OnRenderstateBs)
	ON_COMMAND(ID_ADD_TEXTURE, &CFileView::OnAddTexture)
	ON_COMMAND(ID_ADD_RENDERTEXTURE, &CFileView::OnAddRendertexture)
	ON_COMMAND(ID_ADD_MESH, &CFileView::OnAddMesh)
	ON_COMMAND(ID_ADD_CAMERA, &CFileView::OnAddCamera)
	ON_COMMAND(ID_ADD_REMOVE, &CFileView::OnAddRemove)
	ON_COMMAND(ID_ADD_RENAME, &CFileView::OnAddRename)
	ON_NOTIFY(TVN_BEGINLABELEDIT,4,&CFileView::OnBeginLabelEdit)
	ON_NOTIFY(TVN_ENDLABELEDIT,4,&CFileView::OnEndLabelEdit)
	ON_COMMAND(ID_ADD_BIND, &CFileView::OnAddBind)
	ON_COMMAND(ID_ADD_RELOAD, &CFileView::OnAddReload)
	ON_COMMAND(ID_ADD_PASS, &CFileView::OnAddPass)
	ON_COMMAND(ID_SHADER_VERTEXSHADER, &CFileView::OnShaderVertexshader)
	ON_COMMAND(ID_SHADER_GEOMETRYSHADER, &CFileView::OnShaderGeometryshader)
	ON_COMMAND(ID_SHADER_PIXELSHADER, &CFileView::OnShaderPixelshader)
	ON_COMMAND(ID_SHADER_COMPUTESHADER, &CFileView::OnShaderComputeshader)
	ON_COMMAND(ID_SHADER_HULLSHADER, &CFileView::OnShaderHullshader)
	ON_COMMAND(ID_SHADER_DOMAINSHADER, &CFileView::OnShaderDomainshader)
	ON_COMMAND(ID_ADD_MODEL, &CFileView::OnAddModel)
	ON_COMMAND(ID_ADD_TEXTUREREF, &CFileView::OnAddTextureref)
	//ON_COMMAND(ID_ADD_MATERIAL, &CFileView::OnAddMaterial)
	//ON_COMMAND(ID_ADD_CONSTANTBUFFER, &CFileView::OnAddConstantbuffer)
	ON_COMMAND(ID_ADD_MODELREF, &CFileView::OnAddModelref)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar ��Ϣ�������

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ������ͼ:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_EDITLABELS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("δ�ܴ����ļ���ͼ\n");
		return -1;      // δ�ܴ���
	}

	// ������ͼͼ��:
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* ������*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// ����һЩ��̬����ͼ����(�˴�ֻ������������룬�����Ǹ��ӵ�����)
	FillFileView();
	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::FillFileView()
{
// 	HTREEITEM hRoot = m_wndFileView.InsertItem(_T("����"), 0, 0);
// 	m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
//  
//  	HTREEITEM hSrc = m_wndFileView.InsertItem(_T("Pass"), 0, 0, hRoot);
// 
// 	m_wndFileView.InsertItem(_T("FakeApp.cpp"), 1, 1, hSrc);
// 	m_wndFileView.InsertItem(_T("FakeApp.rc"), 1, 1, hSrc);
// 	m_wndFileView.InsertItem(_T("FakeAppDoc.cpp"), 1, 1, hSrc);
// 	m_wndFileView.InsertItem(_T("FakeAppView.cpp"), 1, 1, hSrc);
// 	m_wndFileView.InsertItem(_T("MainFrm.cpp"), 1, 1, hSrc);
// 	m_wndFileView.InsertItem(_T("StdAfx.cpp"), 1, 1, hSrc);
// 
// 	HTREEITEM hInc = m_wndFileView.InsertItem(_T("FakeApp ͷ�ļ�"), 0, 0, hRoot);
// 
// 	m_wndFileView.InsertItem(_T("FakeApp.h"), 2, 2, hInc);
// 	m_wndFileView.InsertItem(_T("FakeAppDoc.h"), 2, 2, hInc);
// 	m_wndFileView.InsertItem(_T("FakeAppView.h"), 2, 2, hInc);
// 	m_wndFileView.InsertItem(_T("Resource.h"), 2, 2, hInc);
// 	m_wndFileView.InsertItem(_T("MainFrm.h"), 2, 2, hInc);
// 	m_wndFileView.InsertItem(_T("StdAfx.h"), 2, 2, hInc);
// 
// 	HTREEITEM hRes = m_wndFileView.InsertItem(_T("FakeApp ��Դ�ļ�"), 0, 0, hRoot);
// 
// 	m_wndFileView.InsertItem(_T("FakeApp.ico"), 2, 2, hRes);
// 	m_wndFileView.InsertItem(_T("FakeApp.rc2"), 2, 2, hRes);
// 	m_wndFileView.InsertItem(_T("FakeAppDoc.ico"), 2, 2, hRes);
// 	m_wndFileView.InsertItem(_T("FakeToolbar.bmp"), 2, 2, hRes);
// 
// 	m_wndFileView.Expand(hRoot, TVE_EXPAND);
// 	m_wndFileView.Expand(hSrc, TVE_EXPAND);
// 	m_wndFileView.Expand(hInc, TVE_EXPAND);
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// ѡ���ѵ�������:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
			theApp.GetContextMenuManager()->ShowPopupMenu(IDR_MENU_ADD, point.x, point.y, this, TRUE);
			
		}
		//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_MENU_ADD, point.x, point.y, this, TRUE);
	}

	pWndTree->SetFocus();
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnProperties()
{
	AfxMessageBox(_T("����...."));

}

void CFileView::OnFileOpen()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnFileOpenWith()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnDummyCompile()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnEditCut()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnEditCopy()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnEditClear()
{
	// TODO: �ڴ˴���������������
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* ����*/);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("�޷�����λͼ: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}

void CFileView::OnSelectChaneged( NMHDR* pNMHDR, LRESULT* pResult )
{
	LPNMTREEVIEW   pHitTestInfo   =   (LPNMTREEVIEW)pNMHDR; 
	HTREEITEM   item =   pHitTestInfo->itemNew.hItem;
	//CString	str	=	m_wndFileView.GetItemText(item);
	//OutputDebugString(str.GetBuffer());
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		CMainFrame*	pMF	=	(CMainFrame*)theApp.GetMainWnd();
		pMF->GetPropertyWindow().ShowProperty(pObj);
	}
	*pResult	=	1;

}

void CFileView::OnRButtonUp( UINT nFlags, CPoint point )
{
	__super::OnRButtonUp(nFlags,point);

	HTREEITEM	h	=	m_wndFileView.HitTest(point);
	if(h!=NULL){
		CMenu m;
		m_wndFileView.SetFocus();
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_MENU_ADD, point.x, point.y, this, TRUE);
	}
}

CTreeCtrl* CFileView::GetTreeCtrl()
{
	return	&m_wndFileView;
}




void CFileView::OnAddEffect()
{
	// TODO: Add your command handler code here
	CMainFrame*	pMF	=	(CMainFrame*)theApp.GetMainWnd();
	CEffectorDoc*	pDoc	=	(CEffectorDoc*)pMF->GetActiveView()->GetDocument();
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


void CFileView::OnAddPhase()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		if(pObj->GetType()	==	enTOT_Effect){
			Effect*	pEffect	=	(Effect*)pObj;
			pEffect->AddPhase(_T("Phase"));
		}
	}
}


void CFileView::OnRenderstateRs()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		if(pObj->GetType()	==	enTOT_Pass	&&	pObj->GetChildCountByType(enTOT_RState)	==	0){
			TreeObj*	pState	=	new RenderState(_T("RasterState"),pObj,enTOT_RState);
			pState->Create();
			pObj->AddChild(pState);
		}
	}
}


void CFileView::OnRenderstateDs()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		if(pObj->GetType()	==	enTOT_Pass	&&	pObj->GetChildCountByType(enTOT_DState)	==	0){
			TreeObj*	pState	=	new RenderState(_T("DepthStencilState"),pObj,enTOT_DState);
			pState->Create();
			pObj->AddChild(pState);
		}
	}
}


void CFileView::OnRenderstateBs()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		if(pObj->GetType()	==	enTOT_Pass	&&	pObj->GetChildCountByType(enTOT_BState)	==	0){
			TreeObj*	pState	=	new RenderState(_T("BlendState"),pObj,enTOT_BState);
			pState->Create();
			pObj->AddChild(pState);
		}
	}
}


void CFileView::OnAddTexture()
{
	// TODO: Add your command handler code here

	CMainFrame*	pMF	=	(CMainFrame*)theApp.GetMainWnd();
	CEffectorDoc*	pDoc	=	(CEffectorDoc*)pMF->GetActiveView()->GetDocument();
	if(pDoc!=NULL){
		EffectorFile*	pFile	=	pDoc->GetEffectorFile();
		if(pFile!=NULL){
			CTreeCtrl*	pTree	=	pFile->GetTree();
			HTREEITEM	item	=	pTree->GetSelectedItem();
			TreeObj*	pObj	=	(TreeObj*)pTree->GetItemData(item);
			if(pObj!=NULL){
				pFile->AddChild(_T("Texture"),enTOT_Texture);
			}
		}
	}
}


void CFileView::OnAddRendertexture()
{
	// TODO: Add your command handler code here
	CMainFrame*	pMF	=	(CMainFrame*)theApp.GetMainWnd();
	CEffectorDoc*	pDoc	=	(CEffectorDoc*)pMF->GetActiveView()->GetDocument();
	if(pDoc!=NULL){
		EffectorFile*	pFile	=	pDoc->GetEffectorFile();
		if(pFile!=NULL){
			CTreeCtrl*	pTree	=	pFile->GetTree();
			HTREEITEM	item	=	pTree->GetSelectedItem();
			TreeObj*	pObj	=	(TreeObj*)pTree->GetItemData(item);
			if(pObj!=NULL){
				pFile->AddChild(_T("RenderTexture"),enTOT_RenderTexture);
			}
		}
	}

}


void CFileView::OnAddMesh()
{
	// TODO: Add your command handler code here
	CMainFrame*	pMF	=	(CMainFrame*)theApp.GetMainWnd();
	CEffectorDoc*	pDoc	=	(CEffectorDoc*)pMF->GetActiveView()->GetDocument();
	if(pDoc!=NULL){
		EffectorFile*	pFile	=	pDoc->GetEffectorFile();
		if(pFile!=NULL){
			CTreeCtrl*	pTree	=	pFile->GetTree();
			HTREEITEM	item	=	pTree->GetSelectedItem();
			TreeObj*	pObj	=	(TreeObj*)pTree->GetItemData(item);
			if(pObj!=NULL){
				pFile->AddMesh(_T("Mesh"));
			}
		}
	}
}


void CFileView::OnAddCamera()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	CMainFrame*	pMF	=	(CMainFrame*)theApp.GetMainWnd();
	CEffectorDoc*	pDoc	=	(CEffectorDoc*)pMF->GetActiveView()->GetDocument();
	if(pDoc!=NULL){
		EffectorFile*	pFile	=	pDoc->GetEffectorFile();
		if(pFile!=NULL){
			CTreeCtrl*	pTree	=	pFile->GetTree();
			HTREEITEM	item	=	pTree->GetSelectedItem();
			TreeObj*	pObj	=	(TreeObj*)pTree->GetItemData(item);
			if(pObj!=NULL){
				pFile->AddCamera(_T("Camera"));
			}
		}
	}
}


void CFileView::OnAddRemove()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		pObj->DeleteSelf();
	}
}


void CFileView::OnAddRename()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL	&&	pObj->IsEnableEdit()){
// 		ReNameDialog dlg(pObj->GetName().c_str(),this);
// 		if(dlg.DoModal()	==	IDOK)
// 		{
// 			pObj->SetName(dlg.strInitName.GetBuffer());
// 		}
		m_wndFileView.EditLabel(item);
	}
}

void CFileView::OnBeginLabelEdit( NMHDR* pNMHDR, LRESULT* pResult )
{
	TV_DISPINFO*   pTVDispInfo   =   (TV_DISPINFO*)pNMHDR; 

	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(pTVDispInfo->item.hItem);
	if(pObj!=NULL	&&	pObj->IsEnableEdit()	&& pTVDispInfo-> item.pszText   !=   NULL){
		*pResult   =   0;
	}else{
		*pResult	=	TRUE;
	}
}

void CFileView::OnEndLabelEdit( NMHDR* pNMHDR, LRESULT* pResult )
{
	TV_DISPINFO*   pTVDispInfo   =   (TV_DISPINFO*)pNMHDR;
	if(pTVDispInfo-> item.pszText   !=   NULL){
		TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(pTVDispInfo->item.hItem);
		pObj->SetName(pTVDispInfo->item.pszText);
		*pResult   =   TRUE;
	}
}

BOOL CFileView::PreTranslateMessage( MSG* pMsg )
{
	return	__super::PreTranslateMessage(pMsg);
}


void CFileView::OnAddBind()
{
	// TODO: Add your command handler code here

	CMainFrame*	pMF	=	(CMainFrame*)theApp.GetMainWnd();
	CEffectorDoc*	pDoc	=	(CEffectorDoc*)pMF->GetActiveView()->GetDocument();
	if(pDoc==NULL)
		return;
	EffectorFile*	pFile	=	pDoc->GetEffectorFile();
	if(pFile==NULL)
		return;

	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL	&&	pObj->IsEnableBind()){
		std::vector<TreeObj*>	vecObj;
		switch(pObj->GetType()){
			case enTOT_Phase:{
				vecObj	=	pFile->GetChildByType(enTOT_RenderTexture);
				break;}
			case enTOT_Model:{
				vecObj	=	pFile->GetChildByType(enTOT_Mesh);
				break;}
			case enTOT_ModelRef:{
				vecObj	=	pFile->GetChildByType(enTOT_Model);
				break;}
			case enTOT_CameraRef:{
				vecObj	=	pFile->GetChildByType(enTOT_Camera);
				break;}
			case enTOT_TextureRef:{
				vecObj	=	pFile->GetChildByType(enTOT_Texture);
				break;}
		}
		if(!vecObj.empty()){
			TreeObjectBind	dlg(vecObj,this);
			if(dlg.DoModal()==IDOK){
				TreeObj*	pSelectObj	=	dlg.GetSelectObj();
				if(pSelectObj!=NULL){
					pObj->SetBindObj(pSelectObj);
				}
			}
		}
	}
}


void CFileView::OnAddReload()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		pObj->ReLoad();
	}
}


void CFileView::OnAddPass()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		if(pObj->GetType()	==	enTOT_Phase){
			pObj->AddChild(_T("Pass"),enTOT_Pass);
		}
	}
}


void CFileView::OnShaderVertexshader()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		if(pObj->GetType()	==	enTOT_Pass	&&	pObj->GetChildCountByType(enTOT_VShader)	==	0){
			pObj->AddChild(_T("VertexShader"),enTOT_VShader);
		}
	}
}


void CFileView::OnShaderGeometryshader()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		if(pObj->GetType()	==	enTOT_Pass	&&	pObj->GetChildCountByType(enTOT_GShader)	==	0){
			pObj->AddChild(_T("GeometryShader"),enTOT_GShader);
		}
	}
}


void CFileView::OnShaderPixelshader()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		if(pObj->GetType()	==	enTOT_Pass	&&	pObj->GetChildCountByType(enTOT_PShader)	==	0){
			pObj->AddChild(_T("PixelShader"),enTOT_PShader);
		}
	}
}


void CFileView::OnShaderComputeshader()
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		if(pObj->GetType()	==	enTOT_Pass	&&	pObj->GetChildCountByType(enTOT_CShader)	==	0){
			pObj->AddChild(_T("ComputeShader"),enTOT_CShader);
		}
	}
}


void CFileView::OnShaderHullshader()
{
	// TODO: Add your command handler code here
}


void CFileView::OnShaderDomainshader()
{
	// TODO: Add your command handler code here
}


void CFileView::OnAddModel()
{
	// TODO: Add your command handler code here

	// TODO: Add your command handler code here
	CMainFrame*	pMF	=	(CMainFrame*)theApp.GetMainWnd();
	CEffectorDoc*	pDoc	=	(CEffectorDoc*)pMF->GetActiveView()->GetDocument();
	if(pDoc!=NULL){
		EffectorFile*	pFile	=	pDoc->GetEffectorFile();
		if(pFile!=NULL){
			CTreeCtrl*	pTree	=	pFile->GetTree();
			HTREEITEM	item	=	pTree->GetSelectedItem();
			TreeObj*	pObj	=	(TreeObj*)pTree->GetItemData(item);
			if(pObj!=NULL){
				pFile->AddChild(_T("Model(MeshRef)"),enTOT_Model);
			}
		}
	}
}


void CFileView::OnAddTextureref()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		if(pObj->GetType()	==	enTOT_Pass){
			pObj->AddChild(_T("TextureRef"),enTOT_TextureRef);
		}
	}
}


void CFileView::OnAddConstantbuffer()
{
	// TODO: Add your command handler code here
}


void CFileView::OnAddModelref()
{
	// TODO: Add your command handler code here
	HTREEITEM	item	=	m_wndFileView.GetSelectedItem();
	TreeObj*	pObj	=	(TreeObj*)m_wndFileView.GetItemData(item);
	if(pObj!=NULL){
		if(pObj->GetType()	==	enTOT_Pass){
			pObj->AddChild(_T("ModelRef"),enTOT_ModelRef);
		}
	}
}
