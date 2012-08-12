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

// EffectorDoc.cpp : CEffectorDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Effector.h"
#endif

#include "EffectorDoc.h"
#include "EffectorFile.h"
#include "MainFrm.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CEffectorDoc

IMPLEMENT_DYNCREATE(CEffectorDoc, CDocument)

BEGIN_MESSAGE_MAP(CEffectorDoc, CDocument)

END_MESSAGE_MAP()


// CEffectorDoc ����/����

CEffectorDoc::CEffectorDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_pFile	=	NULL;
}

CEffectorDoc::~CEffectorDoc()
{
	delete m_pFile;
	m_pFile	=	NULL;
}

BOOL CEffectorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	if(m_pFile==NULL){
		CMainFrame*	pMF	=	((CMainFrame*)theApp.GetMainWnd());

		m_pFile	=	new	EffectorFile(pMF->GetFileTreeCtrl());
	}
	m_pFile->New();
	return TRUE;
}




// CEffectorDoc ���л�

void CEffectorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CEffectorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CEffectorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CEffectorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CEffectorDoc ���

#ifdef _DEBUG
void CEffectorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEffectorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

BOOL CEffectorDoc::OnOpenDocument( LPCTSTR lpszPathName )
{
	if(m_pFile==NULL){
		CMainFrame*	pMF	=	((CMainFrame*)theApp.GetMainWnd());

		m_pFile	=	new	EffectorFile(pMF->GetFileTreeCtrl());
	}
	m_pFile->Open(lpszPathName);
	return	CDocument::OnOpenDocument(lpszPathName);
}

BOOL CEffectorDoc::OnSaveDocument( LPCTSTR lpszPathName )
{
	CDocument::OnSaveDocument(lpszPathName);
	
	return	m_pFile->SaveAs(lpszPathName);
}

void CEffectorDoc::OnCloseDocument()
{
	m_pFile->Destroy();
	delete m_pFile;
	m_pFile	=	NULL;
	CDocument::OnCloseDocument();
}

EffectorFile* CEffectorDoc::GetEffectorFile()
{
	return	m_pFile;
}

#endif //_DEBUG


// CEffectorDoc ����

