
// MSetup.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MSetup.h"
#include "MSetupDlg.h"
#include "SetupBegin.h"
#include "SetupSelectPath.h"
#include "SetupFinshed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMSetupApp

BEGIN_MESSAGE_MAP(CMSetupApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMSetupApp ����

CMSetupApp::CMSetupApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMSetupApp ����

CMSetupApp theApp;

BOOL   EnableDebugPrivilege(BOOL   fEnable   =TRUE   )
{   
	BOOL   fOK =   FALSE;   
	HANDLE hToken =   NULL;   
	if(OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken))
	{   
		TOKEN_PRIVILEGES tp;   
		tp.PrivilegeCount =1;   
		LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&tp.Privileges[0].Luid);   
		tp.Privileges[0].Attributes =   fEnable   ?   SE_PRIVILEGE_ENABLED   :   0;   
		AdjustTokenPrivileges(hToken,FALSE,&tp,sizeof(tp),NULL,NULL);   
		fOK =   (GetLastError()==ERROR_SUCCESS);   
		CloseHandle(hToken);   
	}   
	return   fOK;   
}



// CMSetupApp ��ʼ��

BOOL CMSetupApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	EnableDebugPrivilege(TRUE);

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("SNDA"));

	CSetupBegin	dlgBegin;
	//m_pMainWnd = &dlgBegin;
	INT_PTR nResponse = dlgBegin.DoModal();
	if (nResponse == IDOK)
	{
		CSetupSelectPath	dlgPath;
		//m_pMainWnd = &dlgPath;
		nResponse = dlgPath.DoModal();
		if (nResponse == IDOK)
		{
			CMSetupDlg dlg;
			//m_pMainWnd = &dlg;
			nResponse = dlg.DoModal();
			if (nResponse == IDOK)
			{
				CSetupFinshed	dlgFinshed;
				//m_pMainWnd = &dlgFinshed;
				wcscpy_s(dlgFinshed.strGamePath,dlgPath.m_strSetupPath);
				nResponse = dlgFinshed.DoModal();
				if (nResponse == IDOK)
				{

				}
			}
		}

	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

