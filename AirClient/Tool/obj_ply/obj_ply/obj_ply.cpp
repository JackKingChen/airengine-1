// obj_ply.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ObjLoader.h"
#include "rply.h"

int _tmain(int argc, _TCHAR* argv[])
{

	CMeshLoader obj;
	obj.Create(L"1.obj");

	 p_ply oply	= ply_create("1.ply",PLY_LITTLE_ENDIAN, NULL, 0, NULL);
	

	 ply_close(oply);

	return 0;
}

