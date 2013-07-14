// DumpAnalyze.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "DumpFile.h"
#include "DumpSymbol.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc < 2){
		wprintf(L"DumpAnalyze.exe dumpfile\n");
		getchar();
		return -1;
	}


	HRESULT hr = CoInitialize(NULL);

	Dump::FileManager::GetSingleton()->Initialization();

	DumpFile	file;
	file.Open(argv[1]);

	Dump::FileManager::GetSingleton()->Release();
	Dump::FileManager::ReleaseSingleton();

	CoUninitialize();
	getchar();
	return 0;
}

