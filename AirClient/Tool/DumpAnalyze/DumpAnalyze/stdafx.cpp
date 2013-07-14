// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// DumpAnalyze.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������

U1 LoadFile( const wchar_t* strName,void*& pData,U32& uiSize )
{
	HANDLE	hFile	=	CreateFile(strName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL);
	if(hFile!=INVALID_HANDLE_VALUE){
		uiSize	=	GetFileSize(hFile,0);
		pData		=	malloc(uiSize);
		DWORD uiReadSize=0;
		if(pData!=NULL){	
			ReadFile(hFile,pData,uiSize,&uiReadSize,NULL);
		}
		CloseHandle(hFile);
		return true;
	}else{
		pData=NULL;
		uiSize=0;
		return false;
	}
}
