#ifndef RESOURCESYSTEM_HEAD_FILE
#define RESOURCESYSTEM_HEAD_FILE

#include "AirResourceHeader.h"
namespace Air{
	
	
	namespace Client{
	
		namespace	Resource{
			class	Package;
			/**	\brief	������Ϣ
			*
			*	������Ϣ
			*
			***/
	 		struct	FileDataInfo{
	 			FileDataInfo(){
	 				pData	=	NULL;
				};
	 			Data*	pData;
	 			AString		strName;
	 		};
			
			typedef	std::map<AString,Data*>	DataMap;
			typedef	std::map<Data*,AString>	DataRMap;
			typedef	DataMap::iterator				DataMapItr;
			typedef	DataRMap::iterator				DataRMapItr;
	
			typedef	std::list<Data*>			DataReleaseList;
			typedef	DataReleaseList::iterator		DataReleaseListItr;
	
	
			/**	\brief	��Դϵͳ��
			*
			*	��Դϵͳ��
			*
			***/
			class	System	:	
				public	ISystem{
			public:
				System();
	
				/**	\brief	��ʼ��
				*   
				*	@remarks 	��ʼ��
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			Initialization();
	
				/**	\brief	�ͷ�
				*   
				*	@remarks 	�ͷ�
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			Release();
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		System
				*	@return   	U32
				*	@param		AString & strName
				*	@param		Data&	data
				*	@note
				*
				**/
				virtual	U32	Find(CAString&	strName,Data&	data);
	
				/**	\brief	���Һ�׺���ļ�
				*   
				*	@remarks 	���Һ�׺���ļ�
				*	@see		ISystem
				*	@return   	void
				*	@param		AString strPostfix
				*	@param		IFindFileListener * pListener
				*	@note
				*
				**/
				virtual	void		FindWithPostfix(CAString&	strPostfix,IFindFileListener*	pListener);

	
				/**	\brief	�ͷŻ�����
				*   
				*	@remarks 	�ͷŻ�����
				*	@see		System
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1			ReleaseCache();
	
				/**	\brief	���û�������С
				*   
				*	@remarks 	���û�������С
				*	@see		System
				*	@return   	void
				*	@param		SInt uiSize
				*	@note
				*
				**/
				virtual	void		SetCacheSize(SInt	uiSize);
	
				/**	\brief	��ȡ��������С
				*   
				*	@remarks 	��ȡ��������С
				*	@see		System
				*	@return   	SInt
				*	@note
				*
				**/
				virtual	SInt		GetCacheSize();
	
				/**	\brief	��������
				*   
				*	@remarks 	��������
				*	@see		System
				*	@param   	Data*	pData
				*	@note
				*
				**/
				virtual	void			PushData2Cache(Data*	pData);
	
				/**	\brief	���һ����Դ��
				*   
				*	@remarks 	���һ����Դ��
				*	@see		ISystem
				*	@return   	U1
				*	@param		CAString& strPackageName
				*	@param		AString strType
				*	@note
				*
				**/
				virtual	U1			AddPackage(CAString&	strPackageName);
			
			private:
	
	
				DataMap			m_mapCache;				///<	������������
				DataRMap		m_mapRCache;			///<	����������������
				DataReleaseList	m_lstReleaseData;		///<	�Զ��ͷ��б�
				SInt			m_uiMaxCacheSize;		///<	���������ֵ
				SInt			m_uiCacheSize;			///<	��ǰ�����С
				IPackage*		m_pResource;			///<	������Դ��
				IPackage*		m_pCustom;				///<	�Զ�����Դ��
			private:
				Data*		m_pTempData;			///<	��ʱ����ָ��
				AString			m_strTempName;			///<	��ʱ������
	
				std::map<AString,IPackage*>	m_mapPackage;
			};
		}
	
	};
};
#endif // RESOURCESYSTEM_HEAD_FILE