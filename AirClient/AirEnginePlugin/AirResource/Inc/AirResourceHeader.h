#ifndef RESOURCEHEADER_HEAD_FILE
#define RESOURCEHEADER_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirInterfaceResourceSystem.h"

#include "AirGlobalSetting.h"


namespace Air{
	
	
	namespace Client{
	
		namespace	Resource{
	
			struct FileInfo{
				/// Compressed size
				size_t compressedSize;
				/// Uncompressed size
				size_t uncompressedSize;
			};
			typedef std::map<AString,FileInfo> FileInfoMap;
	
			class	IPackage	:
				public	IProduct{
			public:
				IPackage(CAString&	strName):IProduct(strName){
	
				};
	
				virtual	~IPackage(){};
	
				/**	\brief	������Դ
				*   
				*	@remarks 	������Դ
				*	@see		Package
				*	@return   	U1
				*	@param		AString & strName
				*	@param		Data&	data
				*	@note
				*
				**/
				virtual	U32			Find(CAString&	strName,Data&	data)	=	NULL;
	
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
				virtual	void		FindWithPostfix(CAString&	strPostfix,IFindFileListener*	pListener)	=	NULL;
	
				/**	\brief	��ѯ��Դ�Ƿ����
				*   
				*	@remarks 	��ѯ��Դ�Ƿ����
				*	@see		Package
				*	@return   	U32
				*	@param		AString & strName
				*	@note
				*
				**/
				virtual	U32		IsExist(CAString&	strName){
					FileInfoMap::iterator	i	=	m_mapFileInfo.find(strName.c_str());
					if(i!=m_mapFileInfo.end()){
						return	i->second.uncompressedSize;
					}else{
						return	0;
					}
				};
	
	
	
				FileInfoMap		m_mapFileInfo;
			};
	
		};
	
	};
};
#endif // RESOURCEHEADER_HEAD_FILE