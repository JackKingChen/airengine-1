#include "AirCppScript.h"
#include <malloc.h>
#include <Windows.h>
namespace	Air{
	namespace	CppScript{


		void* __Alloc( U32 uiSize )
		{
			return malloc(uiSize);
		}

		void __Free( void* p )
		{
			return free(p);
		}
		void ToLower(wchar_t* str){
			int iLen=wcslen(str);

			static int iOffset = (L'A')-(L'a');
			for(int i=0;i<iLen;i++){
				if(str[i]>=(L'A') && str[i]<=(L'Z')){
					str[i]-=iOffset;
				}
			}
		}
		void ToLower(char* str){
			int iLen=strlen(str);

			static int iOffset = ('A')-('a');
			for(int i=0;i<iLen;i++){
				if(str[i]>=('A') && str[i]<=('Z')){
					str[i]-=iOffset;
				}
			}
		}

		bool SplitFilePath( const std::wstring& str, std::wstring* strPath /*= NULL*/, std::wstring* strFileName /*= NULL*/, std::wstring* strExe /*= NULL*/ )
		{
			if(str.empty())
				return	false;
			S32	uiStrSize	=	str.size();
			S32	uiPoint	=	uiStrSize;
			S32	uiSlash	=	0xffffffff;


			for(S32 i=uiStrSize-1;i>=0;i--){
				if(str[i]	==	'.'	&&	uiPoint	==	uiStrSize){
					uiPoint	=	i;
				}
				if(	str[i]	==	'/'	||
					str[i]	==	'\\'){
						uiSlash	=	i;
						break;
				}
			}

			if(	uiPoint	!=	uiStrSize	&&
				strExe	!=	NULL)
			{
				if(uiPoint!=uiStrSize-1)
					*strExe	=	&str[uiPoint+1];
			}

			if(	uiSlash	!=	0xffffffff		&&
				strPath	!=	NULL)
			{
				if(uiSlash<uiStrSize){
					strPath->resize(uiSlash+1);
					memcpy(&((*strPath)[0]),&str[0],(uiSlash+1)*sizeof(wchar_t));
				}else{
					*strPath	=	str;
				}
			}

			if(strFileName!=NULL){
				U32	uiFileNameSize	=	uiPoint;
				U32	uiFileNameStart	=	0;
				if(uiPoint==uiStrSize)
					uiFileNameSize--;

				if(uiSlash<uiStrSize){
					if(uiSlash!=0xffffffff){
						uiFileNameSize	-=		uiSlash+1;
						uiFileNameStart	=		uiSlash+1;
					}

					strFileName->resize(uiFileNameSize);
					memcpy(&((*strFileName)[0]),&str[uiFileNameStart],uiFileNameSize*sizeof(wchar_t));
				}
			}
			return	true;
		}

		bool LoadFile( const wchar_t* strName,void*& pBuffer,U32& uiSize )
		{
			HANDLE hFile	=	CreateFile(strName,GENERIC_READ,FILE_SHARE_READ |FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL );
			if(hFile==INVALID_HANDLE_VALUE){
				CloseHandle(hFile);
				return false;
			}
			uiSize	=	GetFileSize(hFile,0);
			if(uiSize==0){
				CloseHandle(hFile);
				return	true;
			}
			pBuffer =	__Alloc(uiSize);
			if(pBuffer==NULL){
				CloseHandle(hFile);
				return false;
			}
			DWORD	dwReadSize	=	0;
			if(!ReadFile(hFile,pBuffer,uiSize,&dwReadSize,NULL)){
				__Free(pBuffer);
				CloseHandle(hFile);
				return	false;
			}
			CloseHandle(hFile);
			hFile=NULL;
			
			return true;
		}

		bool SaveFile( const wchar_t* strName,void* pBuffer,U32 uiSize )
		{
			HANDLE hFile	=	CreateFile(strName,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,0,NULL );
			if(hFile==INVALID_HANDLE_VALUE){
				CloseHandle(hFile);
				return false;
			}
			DWORD	dwWriteSize	=	0;
			if(!WriteFile(hFile,pBuffer,uiSize,&dwWriteSize,NULL)){
				CloseHandle(hFile);
				return	false;
			}
			CloseHandle(hFile);
			hFile=NULL;

			return true;
		}

		void InitWorkDirectory()
		{
			wchar_t str[1024];
			GetCurrentDirectory(1024,str);
			std::wstring	strPath		=	str;
			GetModuleFileName(NULL,str,1024);
			Air::CppScript::SplitFilePath(str,&strPath,NULL,NULL);
			SetCurrentDirectory(strPath.c_str());
		}

	}

}