//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/03/29
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  Package.h
 \note     
       
 \attention:
			
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONPACKAGE_HEAD_FILE
#define COMMONPACKAGE_HEAD_FILE

#include "AirCommon.h"
#include "AirCommonHeader.h"
#include "AirCommonFile.h"


namespace Air{
	
	namespace Common{
		class COMMON_EXPORT	Package	:	public	MemoryObject{
		public:
			enum	enumVersion{
				enUnKnown,			//λ�ð汾
				enV_1_0,			//1�汾
				enMaxVersion		//���汾��
			};
			typedef	stdext::hash_map<AString,File::Info>				FileInfoMap;
			typedef stdext::hash_map<AString,File::Info>::iterator		FileInfoMapItr;
			typedef stdext::hash_map<AString,File::Info>::value_type	FileInfoMapPair;
	
			typedef	std::vector<File::Info>									FileInfoVector;
			typedef	std::vector<File::Info>::iterator						FileInfoVectorItr;
	
	
			Package();
			virtual	~Package();
	
			/**	\brief	������Դ����Ϣ
			*   
			*	@remarks 	������Դ����Ϣ
			*	@see		Package
			*	@return   	bool
			*	@param		S8 * strPackageName
			*	@note
			*
			**/
			virtual	bool			Load(S8*	strPackageName);
			/**	\brief	�½���Դ��
			*   
			*	@remarks 	�½���Դ��
			*	@see		Package
			*	@return   	bool
			*	@param		S8 * strPackageName
			*	@note
			*
			**/
			virtual	bool			New(S8*		strPackageName);
			/**	\brief	�����Դ
			*   
			*	@remarks 	�����Դ
			*	@see		Package
			*	@return   	bool
			*	@param		S8 * strName
			*	@note
			*
			**/
			virtual	bool			AddFile(S8*	strName);
			/**	\brief	���ڴ��������Դ
			*   
			*	@remarks 	���ڴ��������Դ
			*	@see		Package
			*	@return   	bool
			*	@param		S8 * strName
			*	@param		U8 * pData
			*	@param		U32 uiDataSize
			*	@note
			*
			**/
			virtual	bool			AddFileFromMemery(S8*	strName,U8*	pData,U32	uiDataSize);
			/**	\brief	�Ƴ���Դ
			*   
			*	@remarks 	�Ƴ���Դ
			*	@see		Package
			*	@return   	bool
			*	@param		S8 * strName
			*	@note
			*
			**/
			virtual bool			RemoveFile(S8*	strName);
			//virtual bool			AddFileList();
			//virtual	bool			MegrePackage(S8*	strPackageName);
			/**	\brief	ж��������Ϣ
			*   
			*	@remarks 	ж��������Ϣ
			*	@see		Package
			*	@return   	void
			*	@note
			*
			**/
			virtual	void			UnLoad();
	
			/**	\brief	�����Դ�Ƿ����
			*   
			*	@remarks 	�����Դ�Ƿ����
			*	@see		Package
			*	@return   	bool
			*	@param		S8 * strName
			*	@note
			*
			**/
			virtual	bool			Exist(S8*	strName);
			/**	\brief	��ȡ��Դ����
			*   
			*	@remarks 	��ȡ��Դ����
			*	@see		Package
			*	@return   	Data*
			*	@param		S8 * strName
			*	@note
			*
			**/
			virtual	Data*		GetFileData(S8*	strName);
			/**	\brief	��ȡ��Դ��Ϣ
			*   
			*	@remarks 	��ȡ��Դ��Ϣ
			*	@see		Package
			*	@return   	File::Info*
			*	@param		S8 * strName
			*	@note
			*
			**/
			virtual	File::Info*		GetFileInfo(S8*	strName);
		private:
			/**	\brief	���汾��Ϣ
			*   
			*	@remarks 	����Ƿ���֧�ֵİ汾
			*	@see		Package
			*	@return   	bool
			*	@param		enumVersion enVer
			*	@note
			*
			**/
			bool	CheckVersion(enumVersion	enVer);
			/**	\brief	������Դ�б���Ϣ
			*   
			*	@remarks 	������Դ�б���Ϣ
			*	@see		Package
			*	@return   	bool
			*	@param		enumVersion enVer
			*	@param		void * pFilePtr
			*	@note
			*
			**/
			bool	LoadFileInfo(enumVersion	enVer,void*	pFilePtr);
			/**	\brief	������Դ�б���Ϣ1������汾�ţ�
			*   
			*	@remarks 	������Դ�б���Ϣ1������汾�ţ�
			*	@see		Package
			*	@return   	bool
			*	@param		void * pFilePtr
			*	@note
			*
			**/
			bool	LoadFileInfo_1(void*	pFilePtr);
			/**	\brief	д����Դ�б���Ϣ
			*   
			*	@remarks 	д����Դ�б���Ϣ
			*	@see		Package
			*	@return   	bool
			*	@param		enumVersion enVer
			*	@param		void * pFilePtr
			*	@note
			*
			**/
			bool	WriteFileInfo(enumVersion	enVer,void*	pFilePtr);
			/**	\brief	д����Դ�б���Ϣ1������汾�ţ�
			*   
			*	@remarks 	д����Դ�б���Ϣ1������汾�ţ�
			*	@see		Package
			*	@return   	bool
			*	@param		void * pFilePtr
			*	@note
			*
			**/
			bool	WriteFileInfo_1(void*	pFilePtr);
			/**	\brief	��ȡ��Դ���ݵĽ���λ��
			*   
			*	@remarks 	��ȡ��Դ���ݵĽ���λ��
			*	@see		Package
			*	@return   	U32
			*	@param		enumVersion enVer
			*	@note
			*
			**/
			U32		GetDataEndPosition(enumVersion enVer);
			/**	\brief	��ȡ��Դ����λ��
			*   
			*	@remarks 	��ȡ��Դ����λ��
			*	@see		Package
			*	@return   	U32
			*	@note
			*
			**/
			U32		GetDataEndPosition_1();
	
			/**	\brief	д��汾��Ϣ1������汾�ţ�
			*   
			*	@remarks 	д��汾��Ϣ1������汾�ţ�
			*	@see		Package
			*	@return   	bool
			*	@param		void * pFilePtr
			*	@note
			*
			**/
			bool	WriteVersion(void*	pFilePtr);
			/**	\brief	��ȡ�汾��Ϣ
			*   
			*	@remarks 	��ȡ�汾��Ϣ
			*	@see		Package
			*	@return   	bool
			*	@param		void * pFilePtr
			*	@note
			*
			**/
			bool	ReadVersion(void*	pFilePtr);
	
		private:
			FileInfoMap				m_mapFileInfo;					///<	�����ļ���������	����
			FileInfoVector			m_vecFileInfo;					///<	��¼�ļ�˳��
			enumVersion				m_enVersion;					///<	��Դ���汾
			U32						m_uiSize;						///<	��Դ���ܴ�С
			void*					m_pFilePtr;						///<	�ļ�ָ��
		};
		
	
	};
};
#endif // PACKAGE_HEAD_FILE