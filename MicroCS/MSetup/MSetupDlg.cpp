
// MSetupDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "net/AirCommonNetClient.h"
#include "MSetup.h"
#include "MSetupDlg.h"
#include "afxdialogex.h"

#include "MNetData.h"
#include "mmsystem.h"
#pragma comment(lib,"winmm")

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif


// CMSetupDlg �Ի���

void	DownloadFunc(void*	p){
	CMSetupDlg* pDlg	=	(CMSetupDlg*)p;
	if(pDlg!=NULL){
		pDlg->ThreadFunc();
	}
}


CMSetupDlg::CMSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMSetupDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pClient	=	NULL;
	m_Event		=	NULL;
	m_pLog		=	NULL;

	m_pNakedClinet		=	NULL;


	m_dwPathLength		=	0;
	memset(m_strSetupPath,0,sizeof(wchar_t)*1024);

	m_Total		=	100*104876;
	m_Complated	=	0;

	Air::Common::InitNet();
}

void CMSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMSetupDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CMSetupDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CMSetupDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMSetupDlg ��Ϣ�������

BOOL CMSetupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_Event	=	CreateEvent(0,0,0,0);
	m_pLog	=	(CListBox*)GetDlgItem(IDC_LIST_LOG);

	if(m_pLog!=NULL){
		m_pLog->InsertString(0,L"��ʼ��װ");
	}
	wchar_t temp0[1024];
	swprintf_s(temp0,L"%stemp",m_strSetupPath);
	m_pNakedClinet	=	_wfopen(temp0,L"wb");


	Air::Common::NetClient::Info info;
	info.strIP		=	"127.0.0.1";
	info.usPort		=	54322;
	info.pListener	=	this;
	AString strName	=	"Downloader";
	m_pClient		=	new Air::Common::NetClient(strName,&info);
	m_pClient->AddRef();

	_beginthread(DownloadFunc,1048576,this);

	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMSetupDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMSetupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMSetupDlg::OnBnClickedCancel()
{
	if(m_pNakedClinet!=NULL){
		fclose(m_pNakedClinet);
		m_pNakedClinet=NULL;
	}

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CMSetupDlg::OnBnClickedOk()
{
	if(m_pNakedClinet!=NULL){
		fclose(m_pNakedClinet);
		m_pNakedClinet=NULL;
	}


	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

CMSetupDlg::~CMSetupDlg()
{
	if(m_pClient!=NULL){
		m_pClient->ReleaseRef();
		m_pClient=NULL;
	}
}

void CMSetupDlg::ThreadFunc()
{
	
	int iCount	=	0;
	while(!m_pClient->IsConnected()){
		if(m_pClient!=NULL){
			Air::Common::NetClient::Info	info;
			info.pListener	=	this;
			info.strIP		=	"10.240.38.103";
			info.usPort		=	54322;
			if(m_pLog!=NULL){
				m_pLog->InsertString(0,L"���ӷ�������");
			}
			if(m_pClient->Connect(info)){
				if(m_pLog!=NULL){
					m_pLog->InsertString(0,L"���ӷ������ɹ�");
					m_pLog->InsertString(0,L"��ʼ������ͻ���");
				}
				enNetType	t=	enNT_FS_Hello;
				m_pClient->Send(&t,sizeof(t));
			}
		}
		Sleep(1000);
	}
	SYSTEMTIME startTime;
	GetLocalTime(&startTime);
	CProgressCtrl* pMain	=	(CProgressCtrl*)GetDlgItem(IDC_PROGRESS_MAIN);
	CProgressCtrl* pSub		=	(CProgressCtrl*)GetDlgItem(IDC_PROGRESS_SUB);

	U32			begin=timeGetTime();
	//SetEvent(m_Event);
	//���ؿͻ���
	while(1){
		if(m_pNakedClinet==NULL){
			break;
		}else{
			U32		end		=	timeGetTime();
			U32	usedTime	=	(end	-	begin)*0.001f;
			U32	usedHour	=	usedTime/3600;
			U32	usedMin		=	(usedTime%3600)/60;
			U32	usedSec		=	(usedTime%3600)%60;

			

			wchar_t strTime[1024];
			if(m_Complated==0){
				swprintf_s(strTime,L"0/2 ��ʹ��%02d:%02d:%02d ʣ��??:??:??",usedHour,usedMin,usedSec);
			}else{
				double	needTime	=	usedTime*((double)m_Total/(double)m_Complated) - usedTime;
				U32	uiNeedTime		=	needTime;
				U32	needHour		=	uiNeedTime/3600;
				U32	needMin			=	(uiNeedTime%3600)/60;
				U32	needSec			=	(uiNeedTime%3600)%60;
				swprintf_s(strTime,L"0/2 ��ʹ��%02d:%02d:%02d ʣ��%02d:%02d:%02d",usedHour,usedMin,usedSec,needHour,needMin,needSec);
			}
			//float	f	=	m_Complated
			GetDlgItem(IDC_STATIC_TIME)->SetWindowTextW(strTime);

			CProgressCtrl* pSub	=	(CProgressCtrl*)GetDlgItem(IDC_PROGRESS_SUB);
			float	fPercent	=	100*(float)m_Complated/(float)m_Total;
			pSub->SetPos((U32)fPercent);
		}
		Sleep(100);
	}
	pSub->SetPos(100);
	pMain->SetPos(25);


	//���ؿͻ���
}

U1 CMSetupDlg::OnConnected( U32 socket,CAString& strIP,CAString& strPort )
{
	
	return true;
}

U1 CMSetupDlg::OnClose( U32 uiSocket )
{
	//if(m_pLog!=NULL){
	//	m_pLog->InsertString(0,L"��������Ͽ�����");
	//}
	return true;
}

U1 CMSetupDlg::OnReceive( U32 uiSocket,AChar* pData,U32 uiSize )
{
	NetHeader*	pHeader	=	(NetHeader*)pData;
	switch(pHeader->t){
		case	enNT_Return:{
			NT_Return* pRet	=	(NT_Return*)pData;
			if(pRet->lastType	==	enNT_FS_Hello){
				NT_ReturnT<NT_SF_Hello>* pHello	=	(NT_ReturnT<NT_SF_Hello>*)pData;
				memcpy(m_PkgSize,pHello->data.pkgSize,sizeof(U32)*16);
				m_Total	=	m_PkgSize[15];
			}

			NT_Data<FileDataInfo> data(enNT_FS_LoadFile);
			data.t		=	enNT_FS_LoadFile;
			
			data.data.idx		=	15;
			data.data.uiOffset	=	0;
			data.data.uiSize	=	m_PkgSize[15];
			m_pClient->Send(&data,sizeof(data));

						  }break;
		case	enNT_SF_FileData:{
			NT_Data<NT_FS_FileData>* pFileData	=	(NT_Data<NT_FS_FileData>*)pData;
			OnDownloading(&pFileData->data);
						  }break;
	}
	return true;
}

void CMSetupDlg::OnDownloading( NT_FS_FileData* pFileData )
{

	long long uiOffset	=	pFileData->uiOffset;
	_fseeki64(m_pNakedClinet,uiOffset,SEEK_SET);
	m_Complated+=pFileData->uiSize;
	fwrite(pFileData->data,pFileData->uiSize,1,m_pNakedClinet);
	if(pFileData->uiComplated){
		if(m_pNakedClinet!=NULL){
			fclose(m_pNakedClinet);
			m_pNakedClinet=NULL;
		}
		if(m_pLog!=NULL){
			m_pLog->InsertString(0,L"��ͻ����������");
		}

	}

}
