//*****************************************************/
/* @All Right Reserved (C), 2008-2010, 82NET TECO CO.



 \author    InfernalHell	Xinhe
 \date      2009/10/22
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  IniFile.h
 \note     
       
 \attention:
			�����ļ���INI
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONINIFILE_HEAD_FILE
#define COMMONINIFILE_HEAD_FILE


#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonFile.h"
namespace Air{
	
	namespace Common{
	
	#ifndef MAX_NAME
	#define MAX_NAME 256
	#endif
	
	#ifndef READ_FILE
	#define READ_FILE(strName,strFile)	\
		{\
			FILE* file = fopen(strName,"rb");\
			fseek(file,0,SEEK_END);\
			int size = ftell(file) - 1;\
			fseek(file,0,SEEK_SET);\
			char* str = new char[size+1];\
			str[size]='\0';\
			fread(str,size,1,file);\
			strFile = str;\
			delete str;\
			fclose(file);\
		}
	
	#endif
	
	#ifndef WRITE_LINE
	#define WRITE_LINE(str,file)	\
		{\
			AString s = AString(str) + AString("\n");\
			fwrite((void*)s.c_str(),s.size(),1,file);\
		}
	#endif
	
	#ifndef WRITE_STR
	#define WRITE_STR
	#endif

	
		/** \brief �����ļ���
		*
		*	��Ҫ���ڻ��������ļ��Ľ���
		*	��������XML�������������
		*
		****/
	
		class COMMON_EXPORT	IniFile	:	public	MemoryObject{
		public:
	
		public:
			IniFile();
			virtual	~IniFile();
			/**	\brief	�����ļ�
			*   
			*	@remarks 	�����ļ� ���������������Թ���ѯ
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strFileName
			*	@note
			*
			**/
			bool LoadFile(CAString& strFileName);
			/**	\brief	���ڴ�������
			*   
			*	@remarks 	���ڴ�������
			*	@see		IniFile
			*	@return   	U1
			*	@param		AString strContent
			*	@note
			*
			**/
			U1	LoadFileFromMemory(U8*	pData,U32	uiSize);
			U1	LoadFileFromMemory(Data*	pData){
				if(pData==NULL)
					return	false;
				return	LoadFileFromMemory(pData->buff,pData->size);
			};
			/**	\brief	���ַ�������
			*   
			*	@remarks 	���ַ�������
			*	@see		IniFile
			*	@return   	U1
			*	@param		CAString& str
			*	@note
			*
			**/
			U1	LoadFileFromString(CAString&	str);
			/**	\brief	�½��ļ�
			*   
			*	@remarks 	�½��ļ�������
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strFileName
			*	@note
			*
			**/
			bool NewFile(AString strFileName);
			/**	\brief	�����ļ�����
			*   
			*	@remarks 	�������ļ��Ļ�������������
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strFileContent
			*	@note
			*
			**/
			bool Replace(AString strFileContent);
			/**	\brief	׷��һ��
			*   
			*	@remarks 	���ļ�β׷��һ��
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strStringLine
			*	@note
			*
			**/
			bool AddLine(AString strStringLine);
			/**	\brief	�޸�����
			*   
			*	@remarks 	�޸����Ӧ���� ��Ӧ���� ��Ӧ������ŵ�����
			*	@see		IniFile
			*	@return   	bool
			*	@param		char * strSortName
			*	@param		char * strName
			*	@param		char * strValue
			*	@param		int iIndex
			*	@note
			*
			**/
			bool Set(const char* strSortName,const char* strName,const char* strValue,int iIndex = 0);
			/**	\brief	����
			*   
			*	@remarks 	�����ļ�����
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strFileName
			*	@note
			*
			**/
			bool Save(AString strFileName = "");
		private:
			/**	\brief	����
			*   
			*	@remarks 	���������ļ�����
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strContent
			*	@note
			*
			**/
			bool Parse(S8*	strContent,UInt uiSize);
			/**	\brief	������
			*   
			*	@remarks 	�����ı��е���
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strLine
			*	@note
			*
			**/
			bool ParseLine(AString strLine);
			/**	\brief	����������
			*   
			*	@remarks 	����������   ��ʾ�� [Sort]  []
			*	@see		IniFile
			*	@return   	AString
			*	@param		AString strSort
			*	@note
			*
			**/
			AString ParseSort(AString strSort);
			/**	\brief	����������Ϣ
			*   
			*	@remarks 	�����������Ϣ  ��ʾ�� Name=Value  =
			*	@see		IniFile
			*	@return   	bool
			*	@param		AString strSource
			*	@param		AString & strName
			*	@param		AString & strValue
			*	@note
			*
			**/
			bool ParseNameAndValue(AString strSource,AString &strName,AString &strValue);
		public:
			/**	\brief	��ѯ
			*   
			*	@remarks 	ͨ�������� ������ ������� SortName Name Index
			*	@see		IniFile
			*	@return   	AString
			*	@param		const char * strSort
			*	@param		const char * strName
			*	@param		int iIndex
			*	@note
			*
			**/
			AString Get(const char* strSort,const char* strName,UInt iIndex = 0);
			/**	\brief	��ѯ��������
			*   
			*	@remarks 	���ݷ����� ������ ��ѯ��������
			*	@see		IniFile
			*	@return   	int
			*	@param		const char * strSort
			*	@param		const char * strName
			*	@note
			*
			**/
			int GetCount(const char* strSort,const char* strName);
			/**	\brief	��ѯ����
			*   
			*	@remarks 	��ѯ�Ƿ���ڸ����ķ���  ���û�з���NULL
			*	@see		IniFile
			*	@return   	SortMap*
			*	@param		const char * strSort
			*	@note
			*
			**/
			SortMap* GetSort(const char* strSort);
			/**	\brief	��ѯ����
			*   
			*	@remarks 	���������� �ڷ����б��в�ѯ����  ��������򷵻������б�
			*	@see		IniFile
			*	@return   	StringList*
			*	@param		const char * strName
			*	@param		SortMap * pMap
			*	@note
			*
			**/
			StringVector* GetStringList(const char* strName,SortMap* pMap);
			/**	\brief	��ѯ����
			*   
			*	@remarks 	���������� �ڷ����б��в�ѯ����  ��������򷵻������б�
			*	@see		IniFile
			*	@return   	StringList*
			*	@param		const char * strName
			*	@param		const char* strSort
			*	@note
			*
			**/
			StringVector* GetStringList(const char* strName,const char* strSort);

			SortList&		GetSortMap(){
				return	m_lstSort;
			};
		private:
	#ifdef _DEBUG
			AString						m_strFileContent;		///<	�����ļ�����	���ڵ���
	#endif
			AString						m_strFileName;			///<	�����ļ���
			SortList					m_lstSort;				///<	��Ϣ������
		};
	
	
	};
};


#endif