// SetupFinshed.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MSetup.h"
#include "SetupFinshed.h"
#include "afxdialogex.h"
#include "atlconv.h"

// CSetupFinshed �Ի���

IMPLEMENT_DYNAMIC(CSetupFinshed, CDialog)

CSetupFinshed::CSetupFinshed(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupFinshed::IDD, pParent)
{
	memset(strGamePath,0,sizeof(wchar_t)*1024);
}

CSetupFinshed::~CSetupFinshed()
{
}

void CSetupFinshed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetupFinshed, CDialog)
	ON_BN_CLICKED(IDOK, &CSetupFinshed::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetupFinshed ��Ϣ�������




bool CreatLinkToStartMenu(wchar_t * pszPeFileName)
{

	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		IShellLink *pisl;
		hr = CoCreateInstance(CLSID_ShellLink, NULL,
			CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pisl);
		if (SUCCEEDED(hr))
		{
			IPersistFile* pIPF;

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//����������Ҫ������ݷ�ʽ��ԭʼ�ļ���ַ
			pisl->SetPath(pszPeFileName);
			hr = pisl->QueryInterface(IID_IPersistFile, (void**)&pIPF);
			if (SUCCEEDED(hr))
			{
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//����������Ҫ������ݷ�ʽ��Ŀ���ַ
				wchar_t szStartPath[1024] = {0};
				SHGetSpecialFolderPath(NULL,szStartPath, CSIDL_DESKTOP, 0);
				wcscat(szStartPath,L"\\������.lnk");

				USES_CONVERSION;
				//LPCOLESTR lpOleStr = A2COLE(szStartPath);

				pIPF->Save(szStartPath, FALSE);

				pIPF->Release();
			}
			pisl->Release();
		}
		CoUninitialize();
	}

	return true;
}



void CSetupFinshed::OnBnClickedOk()
{
	wchar_t	strGameExe[1024];
	swprintf_s(strGameExe,L"%Autopatch.exe",strGamePath);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(IsDlgButtonChecked(IDC_CHECK_DESKTOP_SHOTCUT))
	{
		
		//if(SHGetSpecialFolderPathW(GetDesktopWindow()->m_hWnd,strDeskTop,CSIDL_DESKTOP,NULL))
		//{
		//	AfxMessageBox(strDeskTop);
		//}
		CreatLinkToStartMenu(L"F:\\wz\\Autopatch.exe");
		//CreatLinkToStartMenu(strGameExe);

	}
	if(IsDlgButtonChecked(IDC_CHECK_START_GAME)){
		swprintf_s(strGameExe,L"F:\\wz\\Autopatch.exe");
		swprintf_s(strGamePath,L"F:\\wz\\");
		STARTUPINFO si = { sizeof(si) };     
		PROCESS_INFORMATION pi;     
		si.dwFlags = STARTF_USESHOWWINDOW; // ָ��wShowWindow��Ա��Ч     
		si.wShowWindow = FALSE; // �˳�Ա��ΪTRUE�Ļ�����ʾ�½����̵�������     
		BOOL bRet = CreateProcess (     NULL,// ���ڴ�ָ����ִ���ļ����ļ���     
			strGameExe,//�����в���     
			NULL,// Ĭ�Ͻ��̰�ȫ��     
			NULL,// Ĭ�Ͻ��̰�ȫ��     
			FALSE,// ָ����ǰ�����ھ�������Ա��ӽ��̼̳�     
			0,// Ϊ�½��̴���һ���µĿ���̨����     
			NULL,// ʹ�ñ����̵Ļ�������     
			strGamePath,// ʹ�ñ����̵���������Ŀ¼     
			&si,     
			&pi) ;   
	}
	CDialog::OnOK();

}
