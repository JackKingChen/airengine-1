// CppScript.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "AirCppScriptCompiler.h"
int _tmain(int argc, _TCHAR* argv[])
{
	if(argc	<	2){
		wprintf(L"CppScript *.cpp\n");
		getchar();
		return -1;
	}
	Air::CppScript::Compiler c;
	c.Initialization();

	c.Compile(argv[1]);
	getchar();
	return 0;
}

