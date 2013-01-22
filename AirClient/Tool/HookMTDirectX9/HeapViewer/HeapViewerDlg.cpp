
// HeapViewerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HeapViewer.h"
#include "HeapViewerDlg.h"
#include "afxdialogex.h"
#include "ProcessSelect.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool bExit	=	false;

void UpdateBMP(void* pCtrl){
	CHeapViewerDlg* pDlg = (CHeapViewerDlg*)pCtrl;
	while(!pDlg->IsNeedExitThread()){
		Sleep(1000);
		pDlg->OnUpdateHeap();
	}
	bExit	=	true;
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHeapViewerDlg �Ի���




CHeapViewerDlg::CHeapViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHeapViewerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	iPID	=	0;
	m_hFileMapping	=	NULL;
	m_pFile			=	NULL;
	m_BMP			=	NULL;
	m_pBMPData		=	NULL;
	m_iWidth		=	2048*256;
	m_iWndWidth		=	512;
	m_iWndHeight	=	64;
	m_bNeedExitThread	=	false;

	pTemp			=	(unsigned char*)malloc(1048576);
}

CHeapViewerDlg::~CHeapViewerDlg(){
	if(m_pBMPData!=NULL){
		delete[] m_pBMPData;
		m_pBMPData=NULL;
	}
	if(m_BMP!=NULL){
		DeleteObject(m_BMP);
		m_BMP=NULL;
	}
	if(m_CacheData!=NULL){
		delete m_CacheData;
		m_CacheData=NULL;
	}
	if(pTemp!=NULL){
		free(pTemp);
		pTemp=NULL;
	}
}

void CHeapViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHeapViewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHeapViewerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CHeapViewerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CHeapViewerDlg ��Ϣ�������

BOOL CHeapViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	

	



	if(m_pBMPData==NULL){
		m_pBMPData	=	new DWORD[2048*256];
	}

	RECT r;
	GetDlgItem(IDC_PREVIEW_PICTURE)->GetWindowRect(&r);
	m_iWndWidth		=	2048;//r.right		-	r.left;
	m_iWndHeight	=	256;//r.bottom	-	r.top;

	//pCSliderCtrl->SetThumbLength(1024);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_CacheData	=	new DWORD[m_iWndWidth*m_iWndHeight];


	_beginthread(UpdateBMP,1048576,this);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHeapViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHeapViewerDlg::OnPaint()
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
HCURSOR CHeapViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHeapViewerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	ProcessSelect select;
	if(select.DoModal()==IDOK){
		iPID	=	select.GetPID();

		//InjectDll(iPID);

		if(m_hFileMapping!=NULL){
			if(m_pFile!=NULL){
				UnmapViewOfFile(m_pFile);
				m_pFile=NULL;
			}
			CloseHandle(m_hFileMapping);
			m_hFileMapping=NULL;
		}

		wchar_t strFileMappingName[256];
#ifdef DEBUG_VIEW
		wsprintf(strFileMappingName,L"HeapView%d",GetCurrentProcessId());
#else
		wsprintf(strFileMappingName,L"HeapView%d",iPID);
#endif
		m_hFileMapping	=	OpenFileMappingW(FILE_MAP_ALL_ACCESS,0,strFileMappingName);
		if(m_hFileMapping==NULL){
			InjectDll(iPID);
			//�ȴ�dll�������
			HANDLE	hMutex=NULL;
			char strMutexName[256];
			sprintf_s(strMutexName,256,"HeapViewMutex%d",iPID);
			while(hMutex==NULL){
				hMutex	=	OpenMutexA(MUTEX_ALL_ACCESS,TRUE,strMutexName);
				Sleep(500);
			}
			m_hFileMapping	=	OpenFileMappingW(FILE_MAP_ALL_ACCESS,0,strFileMappingName);
		}

		if(m_hFileMapping!=NULL){
			m_pFile	=	MapViewOfFile(m_hFileMapping,FILE_MAP_ALL_ACCESS,0,0,1048576);
			if(m_pFile!=NULL){

				OnUpdateHeap();
				//��ʼ��ʼ��Viewer
				//CWnd* pViewBar	=	m_HeapViewDlg.GetDlgItem(IDC_STATIC_VIEW);

				
			}
		}
	}

	//CDialogEx::OnOK();
}


void CHeapViewerDlg::OnBnClickedCancel()
{
	//m_bNeedExitThread	=	true;
	//while(!bExit){
	//	Sleep(100);
	//}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void CHeapViewerDlg::InjectDll( int iProcessID )
{
	wchar_t strModuleName[512];
	DWORD dwLength	=	GetModuleFileNameW(NULL,strModuleName,512);
	for(int i=dwLength-1;i>=0;i--){
		if(strModuleName[i]==L'\\'){
			wcscpy(&strModuleName[i+1],L"HeapViewerDll.dll");
			break;
		}
	}
	//int iLen =	

	HMODULE hKernel	=	GetModuleHandleW(L"kernel32.dll");
	void*	pLoadLib	=	GetProcAddress(hKernel,"LoadLibraryW");

	//���Ŀ����̾���������õ�������̫���õĺ�������Ȼ����������߳�/���̵ȷ���� ��Ŀ�Ļ����ͺ�������
	HANDLE hProcess;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS,false,iProcessID); 
	//��Ŀ��������������ַ�ռ䣬�������Ƿ���10���ֽڣ������趨Ϊ���Զ�
	void *pDataRemote =(char*) VirtualAllocEx( hProcess, 0, 512, MEM_COMMIT, PAGE_READWRITE );
	//д���ݵ�Ŀ������з���ı����ռ�
	::WriteProcessMemory( hProcess, pDataRemote, strModuleName,512,NULL);

	//��Ŀ�������ִ�д���
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLib,pDataRemote, 0 , NULL);
	DWORD h;
	if (hThread)
	{
		::WaitForSingleObject( hThread, INFINITE );
		::GetExitCodeThread( hThread, &h );
		TRACE("run and return %d/n",h);
		::CloseHandle( hThread );
	}







}

enum enumHeapBlockType{
	enHBT_VirtualAlloc,
	enHBT_HeapRegion,
};

struct HeapBlock{
	VOID*					pAddress;
	int						iVirtualSize;
	int						iCommontSize;
	unsigned	short		iType;
	unsigned	short		iHeapIndex;
};

DWORD	dwColor[]={
	0xFF00FF00,0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,

	0xFFFF00FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,

	0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,

	0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,

	0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,

	0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,
};

void CHeapViewerDlg::OnUpdateHeap()
{
	if(m_pFile!=NULL){
		memcpy(pTemp,m_pFile,1048576);
		DWORD*	p	=	(DWORD*)pTemp;
		if(*p==1){
			return;
		}
		p++;

		memset(m_pBMPData,0,2048*256*sizeof(DWORD));

		

		

			DWORD	dwBlockCount	=	*p++;
			HeapBlock*	pBlock		=	(HeapBlock*)p;
			for(DWORD	j=0;j<dwBlockCount;j++,pBlock++){
				DWORD	idx			=	((DWORD)pBlock->pAddress)>>12;
				DWORD	iPixelSize	=	((DWORD)pBlock->iVirtualSize)>>12;
				for(DWORD k=0;k<iPixelSize;k++ ){
					m_pBMPData[idx+k]	=	dwColor[pBlock->iHeapIndex];
				}
				pBlock++;
			}


		int iPixel_DataCount = 2048*256/(m_iWndWidth*m_iWndHeight);
		
			for(DWORD	i=0;i<m_iWndWidth;i++){
				for(int j=0;j<m_iWndHeight;j++){
					DWORD iCount = 0;
					for(DWORD k=0;k<iPixel_DataCount;k++){
						iCount|=m_pBMPData[(i*m_iWndHeight+j)*iPixel_DataCount+k];
					}
					unsigned char c 	=	(255.0f*iCount)/(float)iPixel_DataCount;
					m_CacheData[j*m_iWndWidth+i]	=	iCount;//c<<24|c<<16|c<<8|c;
				}
			}

		if(m_BMP!=NULL){
			DeleteObject(m_BMP);
			m_BMP=NULL;
		}
		m_BMP	=	CreateBitmap(m_iWndWidth,m_iWndHeight,1,32,m_CacheData);


		CRect rt;
		GetClientRect(rt);
		rt.top	+=30;
		CClientDC dc(this);
		CPictureHolder ShowBmp;

		ShowBmp.CreateFromBitmap(m_BMP);
		ShowBmp.Render ((CDC*)&dc,&rt,0);

		

		//RECT rect;
		//m_HeapViewDlg.GetDlgItem(IDC_STATIC_VIEW)->GetWindowRect(&rect);
		//m_HeapViewDlg.ScreenToClient(&rect);
		//m_HeapViewDlg.RedrawWindow(&rect);
		//OutputDebugStringA("Update \n");
	}
}

bool CHeapViewerDlg::IsNeedExitThread()
{
	return m_bNeedExitThread;
}

void CHeapViewerDlg::OnSize( UINT nType, int cx, int cy )
{
	//GetDlgItem(IDC_PREVIEW_PICTURE)->MoveWindow(60,60,cx-60,cy-60);
	CDialogEx::OnSize(nType,cx,cy);
}
