//*****************************************************/
/* @All Right Reserved (C), 2009-2012, CLIENT TECO CO.


 \author    InfernalHell	Xinhe
 \date      2010/04/03
 \version   ver 0.6.0.0
 \filepath  f:\Air\AirCommon\Inc
 \filename  FileStream.h
 \note     
       
 \attention:
			�ļ���	�������ļ���ȡ���ļ��б��� 
					��Դ����ȡ����Դ������

					֧���ȱ������ڴ�
					������
					��󱣴浽ָ��λ��
 \remarks    created by InfernalHell version 0.6.0.0 
 \History:
   <author>      <time>      <version>         <desc>
******************************************************/
#ifndef COMMONFILE_HEAD_FILE
#define COMMONFILE_HEAD_FILE

#include "AirCommonData.h"

namespace Air{
	
	enum	enFileType{
		enBinary,
		enASCII,
	};
	namespace Common{
	
		class Package;


	
	
		/**	\brief	�ļ���
		*
		*	�ļ���
		*
		***/
		class COMMON_EXPORT	File{
		public:
			class COMMON_EXPORT	Info{
			public:
				Info(){
					memset(m_strName,0,MAX_NAME);
					_ZERO(m_uiFilePtr);
					_ZERO(m_uiCompressSize);
					_ZERO(m_uiOriginalSize);
				}
				Info(S8* strName,U32 uiFilePtr,U32 uiSize,U32	uiCompressSize){
					strcpy_s(m_strName,MAX_NAME,strName);
					m_uiFilePtr			= uiFilePtr;
					m_uiOriginalSize	= uiSize;
					m_uiCompressSize	= m_uiCompressSize;
				}
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ����
				*	@see		Info
				*	@return   	char*
				*	@note
				*
				**/
				inline S8*		GetFullName(){
					return m_strName;
				};
				/**	\brief	��ȡ����
				*   
				*	@remarks 	��ȡ����
				*	@see		Info
				*	@return   	char*
				*	@note
				*
				**/
				inline S8*		GetName(){
					UInt	iLength	= strlen(m_strName);
					for(UInt i=iLength-1;i>=0;i--){
						if(m_strName[i] == '\\' || m_strName[i] == '/'){
							return &m_strName[i+1];
						}
					}
					return m_strName;
				};
				/**	\brief	��������Դ���е���λ��
				*   
				*	@remarks 	��������Դ���е���λ��
				*	@see		Info
				*	@return   	void
				*	@param		U32 FilePtr
				*	@note
				*
				**/
				inline	void	SetNewPosition(U32 FilePtr){
					m_uiFilePtr	= FilePtr;
				}
				/**	\brief	���������ݰ��е�ƫ����
				*   
				*	@remarks 	���������ݰ��е�ƫ����
				*	@see		Info
				*	@return   	void
				*	@param		U32 FilePtrOffset
				*	@note
				*
				**/
				inline	void	SetPositionOffset(U32 FilePtrOffset){
					m_uiFilePtr	+=	FilePtrOffset;
				}
				S8			m_strName[MAX_NAME];///<	�ļ��� ����·��
				U32			m_uiOriginalSize;	///<	ԭʼ��С
				U32			m_uiCompressSize;	///<	ѹ��֮��Ĵ�С
				U32			m_uiFilePtr;		///<	�ļ���������Դ����λ��
			};
		public:
			File();
			File(CAString&	strName);
			virtual ~File();
	
			/**	\brief	����Դ���д�
			*   
			*	@remarks 	
			*	@see		File
			*	@return   	U1
			*	@param		Package * pPackage
			*	@note
			*
			**/
			U1		OpenFromPackage(Package*	pPackage);
			/**	\brief	���浽��Դ��
			*   
			*	@remarks 	���浽��Դ��
			*	@see		File
			*	@return   	U1
			*	@param		Package * pPackage
			*	@note
			*
			**/
			U1		SaveToPackage(Package*	pPackage);
	
			/**	\brief	���ļ�
			*   
			*	@remarks 	���ļ�
			*	@see		File
			*	@return   	U1
			*	@note
			*
			**/
			U1		Open(Package*	pPackage	= NULL,enFileType	iType	=	enBinary);
			/**	\brief	�����ļ�
			*   
			*	@remarks 	�����ļ�
			*	@see		File
			*	@return   	U1
			*	@note
			*
			**/
			U1		Save(Package*	pPackage	= NULL);
			/**	\brief	���Ϊ
			*   
			*	@remarks 	���Ϊ
			*	@see		File
			*	@return   	U1
			*	@param		CAString& strAnotherName
			*	@note
			*
			**/
			U1		SaveAs(CAString&	strAnotherName);
			/**	\brief	��ȡ����
			*   
			*	@remarks 	ע�⣺���ô˺���������������Ϊһ���������ڴ��
			*	@see		File
			*	@return   	Data*
			*	@note
			*
			**/
			Data*	GetData();
			/**	\brief	��������
			*   
			*	@remarks 	ע�⣺���������ʱ����ģ���std::list���洢���ѣ�ֻ�е���GetData�Ż�����
			*	@see		File
			*	@return   	U1
			*	@param		Data * pData
			*	@note
			*
			**/
			U1		PushData(Data* pData);
			/**	\brief	�ж��ļ����Ƿ���Ч
			*   
			*	@remarks 	�ж��ļ����Ƿ���Ч
			*	@see		File
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		NameIsValid(){return m_strName.empty();};
			/**	\brief	�ж��ļ����Ƿ���Ч
			*   
			*	@remarks 	�ж��ļ���  ���ж��Ƿ�������
			*	@see		File
			*	@return   	U1
			*	@note
			*
			**/
			inline	U1		IsValid(){return	NameIsValid() && m_uiLength > 0;};
			/**	\brief	������
			*   
			*	@remarks 	������
			*	@see		File
			*	@return   	void
			*	@param		CAString& strName
			*	@note
			*
			**/
			inline	void	ReName(CAString&	strName){m_strName	= strName;};
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		File
			*	@return   	U1
			*	@note
			*
			**/
			U1		Clear();
			
	
			/**	\brief	��������
			*   
			*	@remarks 	��������
			*	@see		File
			*	@return   	bool
			*	@param		T_Type * p
			*	@note
			*
			**/
			template	<typename	T_Type>
			bool	Push(T_Type*	p){
				if(p==NULL)
					return	false;
				return	PushData(new	Data(p));
			};
	
			/**	\brief	�����ļ�
			*   
			*	@remarks 	�����ļ� ���ļ���
			*	@see		File
			*	@return   	U1
			*	@param		CAString& strName
			*	@param		U8 * & pData
			*	@param		U32 & uiSize
			*	@note
			*
			**/
			static	U1	Load(CAString& strName,U8*&	pData,U32& uiSize);
			/**	\brief	�����ļ�
			*   
			*	@remarks 	�����ļ����ļ��� �������ļ�
			*	@see		File
			*	@return   	U1
			*	@param		AString strName
			*	@param		U8 * pData
			*	@param		U32 uiSize
			*	@note
			*
			**/
			static	U1	Save(CAString& strName,U8*	pData,U32 uiSize);
			/**	\brief	�����ļ�
			*   
			*	@remarks 	�����ļ� ���������ַ���
			*	@see		File
			*	@return   	U1
			*	@param		AString strName
			*	@param		AString & strContent
			*	@note
			*
			**/
			static	U1	Save(CAString& strName,AString&	strContent);

			/**	\brief	�����ص�
			*
			*	�����ص�
			*
			***/
			class	TraversalCallBack{
			public:
				/**	\brief	�����ҵ��ļ�֮��
				*   
				*	@remarks 	�����ҵ��ļ�֮��
				*	@see		TraversalCallBack
				*	@return   	Air::U1
				*	@param		CAString & strName
				*	@note
				*
				**/
				virtual	U1	OnFindFile(CAString&	strName)		=	NULL;
				/**	\brief	�����ҵ��ļ���֮��
				*   
				*	@remarks 	�����ҵ��ļ���֮��
				*	@see		TraversalCallBack
				*	@return   	Air::U1
				*	@param		CAString & strName
				*	@note
				*
				**/
				virtual	U1	OnFindDirectory(CAString&	strName)	=	NULL;
			};
	
			/**	\brief	�ļ��б���
			*   
			*	@remarks 	
			*	@see		File
			*	@return   	Air::U1
			*	@param		CAString & strPath
			*	@param		TraversalCallBack * pCB
			*	@note
			*
			**/
			static	U1	FolderTraversal(CAString&	strPath,TraversalCallBack*	pCB);
		protected:
	
		private:
			AString		m_strName;			///<	����
			U32			m_uiLength;			///<	����
			DataList	m_lstData;			///<	�����б�
		};
	
	};
};
#endif // FILESTREAM_HEAD_FILE